#include "ray.hpp"

abRT::Ray::Ray() {
    std::vector<double> tempdata = {0.0, 0.0, 0.0};
    m_point1 = abVector<double> {tempdata};
    tempdata = {0.0, 0.0, 1.0};
    m_point2 = abVector<double> {tempdata};
    m_lab = m_point2 - m_point1;
}

abRT::Ray::Ray(const abVector<double>& point1, const abVector<double>& point2) {
    m_point1 = point1;
    m_point2 = point2;
    m_lab = m_point2 - m_point1;
}


abVector<double> abRT::Ray::GetPoint1() const {
    return m_point1;
}

abVector<double> abRT::Ray::GetPoint2() const {
    return m_point2;
}

abVector<double> abRT::Ray::GetRay() const {
    return m_lab;
}

