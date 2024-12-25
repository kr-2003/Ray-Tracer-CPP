#include "simplematerial.hpp"

abRT::SimpleMaterial::SimpleMaterial() {

}

abRT::SimpleMaterial::~SimpleMaterial() {

}

abVector<double> abRT::SimpleMaterial::ComputeColor(const std::vector<std::shared_ptr<abRT::ObjectBase>> &objectList, const std::vector<std::shared_ptr<abRT::LightBase>>& lightList, const std::shared_ptr<abRT::ObjectBase> &currentObject, const abVector<double> &intPoint, const abVector<double> &localNormal, const abRT::Ray &cameraRay) {
    abVector<double> matColor {3};
    abVector<double> refColor {3};
    abVector<double> difColor {3};
    abVector<double> spcColor {3};

    // Compute the diffused component
    difColor = ComputeDiffuseColor(objectList, lightList, currentObject, intPoint, localNormal, m_baseColor);

    if(m_reflectivity > 0.0) {
        refColor = ComputeReflectionColor(objectList, lightList, currentObject, intPoint, localNormal, cameraRay);

        matColor = refColor * m_reflectivity + difColor * (1 - m_reflectivity);
    }

    // compute the specular component
    if(m_shininess > 0.0) {
        spcColor = ComputeSpecular(objectList, lightList, intPoint, localNormal, cameraRay);
    }
    
    // add the specular component to the final color;
    matColor = matColor + spcColor;

    return matColor;
}

abVector<double> abRT::SimpleMaterial::ComputeSpecular(const std::vector<std::shared_ptr<abRT::ObjectBase>> &objectList, const std::vector<std::shared_ptr<abRT::LightBase>>& lightList, const abVector<double> &intPoint, const abVector<double> &localNormal, const abRT::Ray &cameraRay) {
    abVector<double> spcColor {3};
    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;

    for(auto currentLight : lightList) {
        double intensity = 0.0;
        abVector<double> lightDir = (currentLight->m_location - intPoint).Normalized();

        abVector<double> startPoint = intPoint + (lightDir * 0.001);

        abRT::Ray lightRay (startPoint, startPoint + lightDir);

        abVector<double> poi {3};
        abVector<double> poiNormal {3};
        abVector<double> poiColor {3};
        bool validInt = false;

        for(auto sceneObject : objectList) {
            if(sceneObject -> TestIntersections(lightRay, poi, poiNormal, poiColor)) {
                validInt = true;
                if(validInt) {
                    break;
                }
            }
        }

        if(!validInt) {
            abVector<double> d = lightRay.m_lab;
            abVector<double> r = d - 2 * abVector<double>::dot(d, localNormal) * localNormal;
            r = r.Normalized();

            abVector<double> v = cameraRay.m_lab;
            v = v.Normalized();

            double dotProduct = abVector<double>::dot(r, v);

            if(dotProduct > 0.0) {
                intensity = m_reflectivity * std::pow(dotProduct, m_shininess);
            }
        }

        red += currentLight->m_color.GetElement(0) * intensity;
        green += currentLight->m_color.GetElement(1) * intensity;
        blue += currentLight->m_color.GetElement(2) * intensity;
    }

    spcColor.SetElement(0, red);
    spcColor.SetElement(1, green);
    spcColor.SetElement(2, blue);

    return spcColor; 
}