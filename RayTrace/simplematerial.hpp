#ifndef SIMPLEMATERIAL_H
#define SIMPLEMATERIAL_H

#include "materialbase.hpp"

namespace abRT
{
    class SimpleMaterial : public MaterialBase
    {
    public:
        SimpleMaterial();
        virtual ~SimpleMaterial() override;

        virtual abVector<double> ComputeColor(const std::vector<std::shared_ptr<abRT::ObjectBase>> &objectList, const std::vector<std::shared_ptr<abRT::LightBase>> &lightList, const std::shared_ptr<abRT::ObjectBase> &currentObject, const abVector<double> &intPoint, const abVector<double> &localNormal, const abRT::Ray &cameraRay) override;

        abVector<double> ComputeSpecular(const std::vector<std::shared_ptr<abRT::ObjectBase>> &objectList, const std::vector<std::shared_ptr<abRT::LightBase>> &lightList, const abVector<double> &intPoint, const abVector<double> &localNormal, const abRT::Ray &cameraRay);

    public:
        abVector<double> m_baseColor{std::vector<double>{1.0, 0.0, 1.0}};
        double m_reflectivity = 0.0;
        double m_shininess = 0.0;
    };
}

#endif