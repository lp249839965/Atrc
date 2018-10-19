#pragma once

#include <Atrc/Core/Core.h>

AGZ_NS_BEG(Atrc)

class BlackMaterial : public Material
{
public:

    void Shade(const SurfacePoint &sp, ShadingPoint *dst) const override;
};

inline const BlackMaterial STATIC_BLACK_MATERIAL;

AGZ_NS_END(Atrc)
