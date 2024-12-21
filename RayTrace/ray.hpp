#ifndef RAY_H
#define RAY_H

#include "./abLinearAlgebra/Vector.h"

namespace abRT {
    class Ray {
        public:
            Ray(const abVector<double>& point1, const abVector<double>& point2);

            abVector<double> GetPoint1();
            abVector<double> GetPoint2();
            abVector<double> GetRay   ();

        public:
            abVector<double> m_point1 {3};
            abVector<double> m_point2 {3};
            abVector<double> m_lab    {3};
    };
};

#endif