#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include <memory>
#include "./abLinearAlgebra/Vector.h"
#include "ray.hpp"
#include "objectbase.hpp"

namespace abRT {
    class LightBase {
        public:
            LightBase();
            virtual ~LightBase();

            virtual bool ComputeIllumination(const abVector<double> &intPoint, const abVector<double> &localNormal, 
                                             const std::vector<std::shared_ptr<abRT::ObjectBase>> &objectList, 
                                             const std::shared_ptr<abRT::ObjectBase> &currObject, 
                                             abVector<double> &color, double &intensity);

        public:
            abVector<double> m_color {3};
            abVector<double> m_location {3};
            double m_intensity;
    };
};

#endif