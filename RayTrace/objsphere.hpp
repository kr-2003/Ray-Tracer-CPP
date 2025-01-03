#ifndef OBJSPHERE_H
#define OBJSPHERE_H

#include "objectbase.hpp"
#include "gtfm.hpp"

namespace abRT
{
    class ObjSphere : public ObjectBase
    {
    public:
        ObjSphere();

        virtual ~ObjSphere() override;

        virtual bool TestIntersections(const Ray &castRay, abVector<double> &intPoint, abVector<double> &localNormal, abVector<double> &localColor) override;

    private:
    };
};

#endif