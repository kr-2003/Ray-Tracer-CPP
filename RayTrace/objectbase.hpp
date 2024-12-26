#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "./abLinearAlgebra/Vector.h"
#include "ray.hpp"
#include "gtfm.hpp"

namespace abRT
{

    class MaterialBase;

    class ObjectBase
    {
    public:
        ObjectBase();
        virtual ~ObjectBase();

        virtual bool TestIntersections(const Ray &castRay, abVector<double> &intPoint, abVector<double> &localNormal, abVector<double> &localColor);
        void SetTransformMatrix(const abRT::GTForm &transformMatrix);
        bool CloseEnough(const double f1, const double f2);
        bool AssignMaterial(const std::shared_ptr<abRT::MaterialBase> &objectMaterial);

    public:
        abVector<double> m_baseColor{3};
        abRT::GTForm m_transformMatrix;
        std::shared_ptr<abRT::MaterialBase> m_pMaterial;
        bool m_hasMaterial = false;
        abVector<double> m_uvCoords {2};
    };
};

#endif