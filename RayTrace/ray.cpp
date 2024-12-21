#include "ray.hpp"

abRT::Ray::Ray(const abVector<double>& point1, const abVector<double>& point2) {
    m_point1 = point1;
    m_point2 = point2;
    m_lab = m_point2 - m_point1;
}

abVector<double> abRT::Ray::GetPoint1() {
    return m_point1;
}

abVector<double> abRT::Ray::GetPoint2() {
    return m_point2;
}

abVector<double> abRT::Ray::GetRay() {
    return m_lab;
}

