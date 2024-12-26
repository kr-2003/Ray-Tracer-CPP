#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "lightbase.hpp"

namespace abRT
{
    class PointLight : public LightBase
    {
    public:
        PointLight();
        virtual ~PointLight() override;

        virtual bool ComputeIllumination(const abVector<double> &intPoint, const abVector<double> &localNormal,
                                         const std::vector<std::shared_ptr<abRT::ObjectBase>> &objectList,
                                         const std::shared_ptr<abRT::ObjectBase> &currObject,
                                         abVector<double> &color, double &intensity) override;
    };
};

#endif