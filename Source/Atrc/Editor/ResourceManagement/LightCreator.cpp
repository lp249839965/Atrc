#include <Atrc/Editor/ResourceManagement/LightCreator.h>

namespace
{
    class SkyLightInstance : public LightInstance
    {
        Vec3f top_ = Vec3f(1);
        Vec3f bottom_ = Vec3f(1);

    public:

        using LightInstance::LightInstance;

        void Display(ResourceManager&) override
        {
            ImGui::ColorEdit3("top", &top_[0], ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_Float);
            ImGui::ColorEdit3("bottom", &bottom_[0], ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_Float);
        }

        void Export(const ResourceManager&, LauncherScriptExportingContext &ctx) const override
        {
            ctx.AddLine("type = Sky;");
            ctx.AddLine("top = ", AGZ::To<char>(top_), ";");
            ctx.AddLine("bottom = ", AGZ::To<char>(bottom_), ";");
        }
    };
}

void RegisterLightCreators(ResourceManager &rscMgr)
{
    static const SkyLightCreator iSkyLightCreator;
    rscMgr.AddCreator(&iSkyLightCreator);
}

std::shared_ptr<LightInstance> SkyLightCreator::Create(ResourceManager &rscMgr, std::string name) const
{
    return std::make_shared<SkyLightInstance>(std::move(name));
}