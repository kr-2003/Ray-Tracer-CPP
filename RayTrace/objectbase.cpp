#include "objectbase.hpp"
#include <math.h>

#define EPSILON 1e-21f

abRT::ObjectBase::ObjectBase() {

}

abRT::ObjectBase::~ObjectBase() {
    
}

bool abRT::ObjectBase::TestIntersections(const Ray &castRay, abVector<double> &intPoint, abVector<double> &localNormal, abVector<double> &localColor) {
    return false;
}

bool abRT::ObjectBase::CloseEnough(const double f1, const double f2) {
    return fabs(f1 - f2) < EPSILON;
}