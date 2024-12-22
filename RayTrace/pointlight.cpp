#include "pointlight.hpp"

abRT::PointLight::PointLight() {
    std::vector<double> tempdata = {1.0, 1.0, 1.0};
    m_color = abVector<double> {tempdata};
    m_intensity = 1.0;
}

abRT::PointLight::~PointLight() {

}

bool abRT::PointLight::ComputeIllumination(const abVector<double> &intPoint, const abVector<double> &localNormal, 
                                          const std::vector<std::shared_ptr<abRT::ObjectBase>> &objectList, 
                                          const std::shared_ptr<abRT::ObjectBase> &currObject, 
                                          abVector<double> &color, double &intensity) 
{
    abVector<double> lightDir = (m_location - intPoint).Normalized();

    abVector<double> startPoint = intPoint;

    // assume local normal is unit vector
    double angle = acos(abVector<double>::dot(localNormal, lightDir));

    if(angle > M_PI / 2.0) {
        color = m_color;
        intensity = 0.0;
        return false;
    } else {
        color = m_color;
        intensity = m_intensity * (1.0 - (2.0 * angle / M_PI));
        return true;
    }
}