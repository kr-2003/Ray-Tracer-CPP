#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "./abLinearAlgebra/Vector.h"
#include "ray.hpp"

namespace abRT {
    class ObjectBase {
        public:
            ObjectBase();
            virtual ~ObjectBase();

            virtual bool TestIntersections(const Ray &castRay, abVector<double> &intPoint, abVector<double> &localNormal, abVector<double> &localColor);
            bool CloseEnough(const double f1, const double f2);

        public:
            abVector<double> m_baseColor {3};
    };
};

#endif