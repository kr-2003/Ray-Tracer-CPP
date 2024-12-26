#ifndef OBJPLANE_H
#define OBJPLANE_H

#include "objectbase.hpp"
#include "gtfm.hpp"

namespace abRT
{
    class ObjPlane : public ObjectBase
    {
    public:
        ObjPlane();
        virtual ~ObjPlane() override;

        virtual bool TestIntersections(const Ray &castRay, abVector<double> &intPoint, abVector<double> &localNormal, abVector<double> &localColor) override;

    private:
    };
};

#endif