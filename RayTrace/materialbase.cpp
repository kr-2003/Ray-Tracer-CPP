#include "materialbase.hpp"

abRT::MaterialBase::MaterialBase()
{
    m_maxRefrectionRays = 3;
    m_reflectionRayCount = 0;
}

abRT::MaterialBase::~MaterialBase()
{
}

abVector<double> abRT::MaterialBase::ComputeColor(const std::vector<std::shared_ptr<abRT::ObjectBase>> &objectList, const std::vector<std::shared_ptr<abRT::LightBase>> &lightList, const std::shared_ptr<abRT::ObjectBase> &currentObject, const abVector<double> &intPoint, const abVector<double> &localNormal, const abRT::Ray &cameraRay)
{
    abVector<double> matColor{3};
    return matColor;
}

abVector<double> abRT::MaterialBase::ComputeDiffuseColor(const std::vector<std::shared_ptr<abRT::ObjectBase>> &objectList, const std::vector<std::shared_ptr<abRT::LightBase>> &lightList, const std::shared_ptr<abRT::ObjectBase> &currentObject, const abVector<double> &intPoint, const abVector<double> &localNormal, const abVector<double> &baseColor)
{
    // compute the color due to diffused illumination.
    abVector<double> diffuseColor{3};
    double intensity;
    abVector<double> color{3};
    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;
    bool validIllum = false;
    bool illumFound = false;

    for (auto currentLight : lightList)
    {
        validIllum = currentLight->ComputeIllumination(intPoint, localNormal, objectList, currentObject, color, intensity);

        if (validIllum)
        {
            illumFound = true;
            red += color.GetElement(0) * intensity;
            green += color.GetElement(1) * intensity;
            blue += color.GetElement(2) * intensity;
        }
    }

    if (illumFound)
    {
        diffuseColor.SetElement(0, red * baseColor.GetElement(0));
        diffuseColor.SetElement(1, green * baseColor.GetElement(1));
        diffuseColor.SetElement(2, blue * baseColor.GetElement(2));
    }

    return diffuseColor;
}

abVector<double> abRT::MaterialBase::ComputeReflectionColor(const std::vector<std::shared_ptr<abRT::ObjectBase>> &objectList, const std::vector<std::shared_ptr<abRT::LightBase>> &lightList, const std::shared_ptr<abRT::ObjectBase> &currentObject, const abVector<double> &intPoint, const abVector<double> &localNormal, const abRT::Ray &incidentRay)
{
    abVector<double> reflectionColor{3};

    abVector<double> d = incidentRay.m_lab;
    abVector<double> reflectionVector = d - 2 * abVector<double>::dot(d, localNormal) * localNormal;

    abRT::Ray reflectionRay(intPoint, intPoint + reflectionVector);

    std::shared_ptr<abRT::ObjectBase> closestObject;
    abVector<double> closestIntPoint{3};
    abVector<double> closestLocalNormal{3};
    abVector<double> closestLocalColor{3};
    bool intersectionFound = CastRay(reflectionRay, objectList, currentObject, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);

    abVector<double> matColor{3};
    if (intersectionFound && m_reflectionRayCount < m_maxRefrectionRays)
    {
        m_reflectionRayCount++;

        if (closestObject->m_hasMaterial)
        {
            matColor = closestObject->m_pMaterial->ComputeColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, reflectionRay);
        }
        else
        {
            matColor = abRT::MaterialBase::ComputeDiffuseColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, closestObject->m_baseColor);
        }
    }
    else
    {
        // nothing
    }

    reflectionColor = matColor;
    return reflectionColor;
}

bool abRT::MaterialBase::CastRay(const abRT::Ray &castRay, const std::vector<std::shared_ptr<abRT::ObjectBase>> &objectList, const std::shared_ptr<abRT::ObjectBase> &thisObject, std::shared_ptr<abRT::ObjectBase> &closestObject, abVector<double> &closestIntPoint, abVector<double> &closestLocalNormal, abVector<double> &closestLocalColor)
{
    abVector<double> intPoint{3};
    abVector<double> localNormal{3};
    abVector<double> localColor{3};

    double minDist = 1e6;
    bool intersectionFound = false;
    for (auto currentObject : objectList)
    {
        if (currentObject != thisObject)
        {
            bool validInt = currentObject->TestIntersections(castRay, intPoint, localNormal, localColor);

            if (validInt)
            {
                intersectionFound = true;

                double dist = (intPoint - castRay.m_point1).Norm();

                if (dist < minDist)
                {
                    minDist = dist;
                    closestObject = currentObject;
                    closestIntPoint = intPoint;
                    closestLocalColor = localColor;
                    closestLocalNormal = localNormal;
                }
            }
        }
    }

    return intersectionFound;
}

void abRT::MaterialBase::AssignTexture(const std::shared_ptr<abRT::Texture::TextureBase> &inputTexture)
{
	m_textureList.push_back(inputTexture);
	m_hasTexture = true;
}