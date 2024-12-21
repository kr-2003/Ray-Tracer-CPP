#include "objsphere.hpp"
#include <cmath>

abRT::ObjSphere::ObjSphere() {

}

abRT::ObjSphere::~ObjSphere() {
    
}

bool abRT::ObjSphere::TestIntersections(const Ray &castRay, abVector<double> &intPoint, abVector<double> &localNormal, abVector<double> &localColor) {
    abVector<double> vhat = castRay.m_lab;
    vhat = vhat.Normalized();

    // a = v.v
    // since |v| is 1, then a is always 1.
    // a = 1.0

    double b = 2.0 * abVector<double>::dot(castRay.m_point1, vhat);

    double c = abVector<double>::dot(castRay.m_point1, castRay.m_point1) - 1.0;

    double D_Sq = b * b - 4.0 * c;
    if(D_Sq < 0.0) return false;
    return true;
}




