#include <Atrc/Editor/ResourceManagement/CameraCreator.h>
#include <Atrc/Editor/ResourceManagement/EntityCreator.h>
#include <Atrc/Editor/ResourceManagement/FresnelCreator.h>
#include <Atrc/Editor/ResourceManagement/GeometryCreator.h>
#include <Atrc/Editor/ResourceManagement/LightCreator.h>
#include <Atrc/Editor/ResourceManagement/MaterialCreator.h>
#include <Atrc/Editor/ResourceManagement/PathTracingIntegratorCreator.h>
#include <Atrc/Editor/ResourceManagement/RendererCreator.h>
#include <Atrc/Editor/ResourceManagement/SamplerCreator.h>
#include <Atrc/Editor/ResourceManagement/TextureCreator.h>

void RegisterResourceCreators(ResourceManager &rscMgr)
{
    RegisterCameraCreators(rscMgr);
    RegisterEntityCreators(rscMgr);
    RegisterFresnelCreators(rscMgr);
    RegisterGeometryCreators(rscMgr);
    RegisterLightCreators(rscMgr);
    RegisterMaterialCreators(rscMgr);
    RegisterPathTracingIntegratorCreators(rscMgr);
    RegisterRendererCreators(rscMgr);
    RegisterSamplerCreators(rscMgr);
    RegisterTextureCreators(rscMgr);
}
