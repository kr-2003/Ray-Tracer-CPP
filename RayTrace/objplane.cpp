#include "objplane.hpp"
#include <cmath>

abRT::ObjPlane::ObjPlane() {

};

abRT::ObjPlane::~ObjPlane() {

};

bool abRT::ObjPlane::TestIntersections(const Ray &castRay, abVector<double> &intPoint, abVector<double> &localNormal, abVector<double> &localColor)
{
    // copy the cast ray and apply backward transform

    abRT::Ray bckRay = m_transformMatrix.Apply(castRay, abRT::BCKTFORM);

    abVector<double> k = bckRay.m_lab;
    k = k.Normalized();

    if (!CloseEnough(k.GetElement(2), 0.0))
    {
        // there is an intersection
        double t = bckRay.m_point1.GetElement(2) / -k.GetElement(2);

        if (t > 0.0)
        {
            // compute the values for u and v
            double u = bckRay.m_point1.GetElement(0) + (k.GetElement(0) * t);
            double v = bckRay.m_point1.GetElement(1) + (k.GetElement(1) * t);

            if (fabs(u) < 1.0 && fabs(v) < 1.0)
            {
                abVector<double> poi = bckRay.m_point1 + k * t;
                intPoint = m_transformMatrix.Apply(poi, abRT::FWDTFORM);

                abVector<double> localOrigin{std::vector<double>{0.0, 0.0, 0.0}};
                abVector<double> normaVector{std::vector<double>{0.0, 0.0, -1.0}};

                abVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin, abRT::FWDTFORM);

                localNormal = m_transformMatrix.Apply(normaVector, abRT::FWDTFORM) - globalOrigin;
                localNormal = localNormal.Normalized();

                localColor = m_baseColor;

                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    return false;
};