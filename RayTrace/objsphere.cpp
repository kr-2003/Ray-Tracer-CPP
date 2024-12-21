#include "objsphere.hpp"
#include <cmath>

abRT::ObjSphere::ObjSphere() {

}

abRT::ObjSphere::~ObjSphere() {
    
}

bool abRT::ObjSphere::TestIntersections(const abRT::Ray &castRay, abVector<double> &intPoint, abVector<double> &localNormal, abVector<double> &localColor) {
    abVector<double> vhat = castRay.m_lab;
    vhat = vhat.Normalized();

    // a = v.v
    // since |v| is 1, then a is always 1.
    // a = 1.0

    double b = 2.0 * abVector<double>::dot(castRay.m_point1, vhat);

    double c = abVector<double>::dot(castRay.m_point1, castRay.m_point1) - 1.0;

    double intTest = b * b - 4.0 * c;
    if(intTest > 0.0) {
        double numSQRT = sqrtf(intTest);
        double t1 = (-b + numSQRT) / 2.0;
        double t2 = (-b - numSQRT) / 2.0;

        if(t1 < 0.0 || t2 < 0.0) {
            return false;
        } else {
            if(t1 < t2) {
                intPoint = castRay.m_point1 + (vhat * t1);
            } else {
                intPoint = castRay.m_point1 + (vhat * t2);
            }
        }
        return true;
    }
    return false;
}




