#ifndef CYLINDER_H
#define CYLINDER_H

#include "objectbase.hpp"
#include "gtfm.hpp"

namespace abRT
{
    class Cylinder : public ObjectBase
    {
    public:
        Cylinder();
        virtual ~Cylinder() override;
        virtual bool TestIntersections(const abRT::Ray &castRay, abVector<double> &intPoint, abVector<double> &localNormal, abVector<double> &localColor) override;

    private:
    };
};

#endif