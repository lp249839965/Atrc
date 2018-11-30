#include <vector>

#include "ParallelRenderer.h"

AGZ_NS_BEG(Atrc)

void ParallelRenderer::RenderSubarea(const Scene &scene, RenderTarget *rt, const SubareaRect &subarea) const
{
    AGZ::ObjArena<> arena;

    auto pw = rt->GetWidth(), ph = rt->GetHeight();
    Real xBaseCoef = Real(2) / pw, yBaseCoef = Real(2) / ph;
    auto cam = scene.GetCamera();
    for(uint32_t py = subarea.yBegin; py < subarea.yEnd; ++py)
    {
        Real yBase = 1 - Real(2) * py / ph;
        for(uint32_t px = subarea.xBegin; px < subarea.xEnd; ++px)
        {
            Real xBase = Real(2) * px / pw - 1;

            Spectrum pixel = SPECTRUM::BLACK;
            for(uint32_t i = 0; i < spp_; ++i)
            {
                Real xOffset = xBaseCoef * Rand();
                Real yOffset = -yBaseCoef * Rand();
                pixel += integrator_.Eval(
                    scene, cam->GetRay({ xBase + xOffset, yBase + yOffset }), arena);
            }
            rt->At(px, py) = pixel / spp_;

            if(arena.GetUsedBytes() > 16 * 1024 * 1024)
                arena.Clear();
        }
    }
}

ParallelRenderer::ParallelRenderer(int workerCount, uint32_t spp, const Integrator &integrator)
    : workerCount_(workerCount), spp_(spp), integrator_(integrator)
{

}

void ParallelRenderer::Render(const Scene &scene, RenderTarget *rt, ProgressReporter *reporter) const
{
    AGZ_ASSERT(rt->IsAvailable());

    std::queue<SubareaRect> tasks = GridDivider<uint32_t>::Divide(
        { 0, rt->GetWidth(), 0, rt->GetHeight() }, 16, 16);

    if(reporter)
        reporter->Begin();

    std::atomic<size_t> finishedCount = 0;
    size_t totalCount = tasks.size();

    auto func = [&](const SubareaRect &subarea, AGZ::NoSharedParam_t)
    {
        RenderSubarea(scene, rt, subarea);
        auto percent = 100.0 * ++finishedCount / totalCount;
        reporter->Report(percent);
    };

    AGZ::StaticTaskDispatcher<SubareaRect, AGZ::NoSharedParam_t> dispatcher(workerCount_);

    if(dispatcher.Run(func, AGZ::NO_SHARED_PARAM, tasks))
    {
        if(reporter)
            reporter->End();
    }
    else if(reporter)
    {
        for(auto &err : dispatcher.GetExceptions())
            reporter->Message(err.what());
    }
}

AGZ_NS_END(Atrc)
