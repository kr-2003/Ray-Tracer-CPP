#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "./abLinearAlgebra/Vector.h"
#include "ray.hpp"
#include "gtfm.hpp"

namespace abRT {
    class ObjectBase {
        public:
            ObjectBase();
            virtual ~ObjectBase();

            virtual bool TestIntersections(const Ray &castRay, abVector<double> &intPoint, abVector<double> &localNormal, abVector<double> &localColor);
            void SetTransformMatrix(const abRT::GTForm &transformMatrix);
            bool CloseEnough(const double f1, const double f2);

        public:
            abVector<double> m_baseColor {3};
            abRT::GTForm m_transformMatrix;
    };
};

#endif