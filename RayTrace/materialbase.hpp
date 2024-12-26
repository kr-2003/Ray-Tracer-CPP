#ifndef MATERIALBASE_H
#define MATERIALBASE_H

#include <memory>
#include "objectbase.hpp"
#include "lightbase.hpp"
#include "./abLinearAlgebra/Vector.h"
#include "ray.hpp"

namespace abRT
{
    class MaterialBase
    {
    public:
        MaterialBase();

        virtual ~MaterialBase();

        virtual abVector<double> ComputeColor(const std::vector<std::shared_ptr<abRT::ObjectBase>> &objectList, const std::vector<std::shared_ptr<abRT::LightBase>> &lightList, const std::shared_ptr<abRT::ObjectBase> &currentObject, const abVector<double> &intPoint, const abVector<double> &localNormal, const abRT::Ray &cameraRay);

        static abVector<double> ComputeDiffuseColor(const std::vector<std::shared_ptr<abRT::ObjectBase>> &objectList, const std::vector<std::shared_ptr<abRT::LightBase>> &lightList, const std::shared_ptr<abRT::ObjectBase> &currentObject, const abVector<double> &intPoint, const abVector<double> &localNormal, const abVector<double> &baseColor);

        abVector<double> ComputeReflectionColor(const std::vector<std::shared_ptr<abRT::ObjectBase>> &objectList, const std::vector<std::shared_ptr<abRT::LightBase>> &lightList, const std::shared_ptr<abRT::ObjectBase> &currentObject, const abVector<double> &intPoint, const abVector<double> &localNormal, const abRT::Ray &incidentRay);

        bool CastRay(const abRT::Ray &castRay, const std::vector<std::shared_ptr<abRT::ObjectBase>> &objectList, const std::shared_ptr<abRT::ObjectBase> &thisObject, std::shared_ptr<abRT::ObjectBase> &closestObject, abVector<double> &closestIntPoint, abVector<double> &closestLocalNormal, abVector<double> &closestLocalColor);

    public:
        inline static int m_maxRefrectionRays;
        inline static int m_reflectionRayCount;

    private:
    };
};

#endif