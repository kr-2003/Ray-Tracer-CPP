#include "objsphere.hpp"
#include <cmath>

abRT::ObjSphere::ObjSphere()
{
}

abRT::ObjSphere::~ObjSphere()
{
}

// bool abRT::ObjSphere::TestIntersections(const abRT::Ray &castRay, abVector<double> &intPoint, abVector<double> &localNormal, abVector<double> &localColor) {
//     abVector<double> vhat = castRay.m_lab;
//     vhat = vhat.Normalized();

//     // a = v.v
//     // since |v| is 1, then a is always 1.
//     // a = 1.0

//     double b = 2.0 * abVector<double>::dot(castRay.m_point1, vhat);

//     double c = abVector<double>::dot(castRay.m_point1, castRay.m_point1) - 1.0;

//     double intTest = b * b - 4.0 * c;
//     if(intTest > 0.0) {
//         double numSQRT = sqrtf(intTest);
//         double t1 = (-b + numSQRT) / 2.0;
//         double t2 = (-b - numSQRT) / 2.0;

//         if(t1 < 0.0 || t2 < 0.0) {
//             return false;
//         } else {
//             if(t1 < t2) {
//                 intPoint = castRay.m_point1 + (vhat * t1);
//             } else {
//                 intPoint = castRay.m_point1 + (vhat * t2);
//             }

//             // computing the local normal(easy for sphere localed at origin)
//             localNormal = intPoint;
//             localNormal = localNormal.Normalized();
//         }
//         return true;
//     }
//     return false;
// }

bool abRT::ObjSphere::TestIntersections(const abRT::Ray &castRay, abVector<double> &intPoint, abVector<double> &localNormal, abVector<double> &localColor)
{

    abRT::Ray bckRay = m_transformMatrix.Apply(castRay, abRT::BCKTFORM);

    abVector<double> vhat = bckRay.m_lab;
    vhat = vhat.Normalized();

    // a = v.v
    // since |v| is 1, then a is always 1.
    // a = 1.0

    double b = 2.0 * abVector<double>::dot(bckRay.m_point1, vhat);

    double c = abVector<double>::dot(bckRay.m_point1, bckRay.m_point1) - 1.0;

    double intTest = b * b - 4.0 * c;

    abVector<double> poi;

    if (intTest > 0.0)
    {
        double numSQRT = sqrtf(intTest);
        double t1 = (-b + numSQRT) / 2.0;
        double t2 = (-b - numSQRT) / 2.0;

        if (t1 < 0.0 || t2 < 0.0)
        {
            return false;
        }
        else
        {
            if (t1 < t2)
            {
                poi = bckRay.m_point1 + (vhat * t1);
            }
            else
            {
                poi = bckRay.m_point1 + (vhat * t2);
            }

            intPoint = m_transformMatrix.Apply(poi, abRT::FWDTFORM);

            std::vector<double> tempdata = {0.0, 0.0, 0.0};
            abVector<double> objOrigin = abVector<double>{tempdata};
            abVector<double> newObjOrigin = m_transformMatrix.Apply(objOrigin, abRT::FWDTFORM);
            localNormal = intPoint - newObjOrigin;
            localNormal = localNormal.Normalized();

            localColor = m_baseColor;

            double x = poi.GetElement(0);
			double y = poi.GetElement(1);
			double z = poi.GetElement(2);
			double u = atan(sqrtf(pow(x, 2.0) + pow(y, 2.0)) / z);
			double v = atan(y/x);
			if (x < 0)
				v += M_PI;
				
			u /= M_PI;
			v /= M_PI;
			
			m_uvCoords.SetElement(0, u);
			m_uvCoords.SetElement(1, v);
        }
        return true;
    }
    return false;
}
