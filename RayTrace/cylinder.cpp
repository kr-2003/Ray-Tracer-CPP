#include "cylinder.hpp"
#include <cmath>

abRT::Cylinder::Cylinder()
{
}

abRT::Cylinder::~Cylinder()
{
}

bool abRT::Cylinder::TestIntersections(const abRT::Ray &castRay, abVector<double> &intPoint, abVector<double> &localNormal, abVector<double> &localColor)
{

    abRT::Ray bckRay = m_transformMatrix.Apply(castRay, abRT::BCKTFORM);

    abVector<double> vhat = bckRay.m_lab;
    vhat = vhat.Normalized();

    double a = vhat.GetElement(0) * vhat.GetElement(0) + vhat.GetElement(1) * vhat.GetElement(1);

    double b = 2.0 * (abVector<double>::dot(bckRay.m_point1, vhat) - bckRay.m_point1.GetElement(2) * vhat.GetElement(2));

    double c = bckRay.m_point1.GetElement(0) * bckRay.m_point1.GetElement(0) + bckRay.m_point1.GetElement(1) * bckRay.m_point1.GetElement(1) - 1.0;

    double intTest = b * b - 4.0 * c * a;

    std::array<abVector<double>, 4> poi;
    std::array<double, 4> t;
    bool t1Valid, t2Valid, t3Valid, t4Valid;

    // std::cout << intTest << std::endl;

    if (intTest > 0.0)
    {
        double numSQRT = sqrtf(intTest);
        t.at(0) = (-b + numSQRT) / (2.0 * a);
        t.at(1) = (-b - numSQRT) / (2.0 * a);

        poi.at(0) = bckRay.m_point1 + vhat * t.at(0);
        poi.at(1) = bckRay.m_point1 + vhat * t.at(1);

        if (t.at(0) > 0.0 && fabs(poi.at(0).GetElement(2)) < 1.0)
        {
            t1Valid = true;
        }
        else
        {
            t1Valid = false;
            t.at(0) = 100e6;
        }
        if (t.at(1) > 0.0 && fabs(poi.at(1).GetElement(2)) < 1.0)
        {
            t2Valid = true;
        }
        else
        {
            t2Valid = false;
            t.at(1) = 100e6;
        }
    }
    else
    {
        t1Valid = false;
        t2Valid = false;
        t.at(0) = 100e6;
        t.at(1) = 100e6;
    }

    if (CloseEnough(vhat.GetElement(2), 0.0))
    {
        t3Valid = false;
        t4Valid = false;
        t.at(2) = 100e6;
        t.at(3) = 100e6;
    }
    else
    {
        t.at(2) = (bckRay.m_point1.GetElement(2) - 1.0) / -vhat.GetElement(2);
        t.at(3) = (bckRay.m_point1.GetElement(2) + 1.0) / -vhat.GetElement(2);

        poi.at(2) = bckRay.m_point1 + t.at(2) * vhat;
        poi.at(3) = bckRay.m_point1 + t.at(3) * vhat;

        if ((t.at(2) > 0.0) && (sqrtf(std::pow(poi.at(2).GetElement(0), 2.0) + std::pow(poi.at(2).GetElement(1), 2.0)) < 1.0))
        {
            t3Valid = true;
        }
        else
        {
            t3Valid = false;
            t.at(2) = 100e6;
        }
        if ((t.at(3) > 0.0) && (sqrtf(std::pow(poi.at(3).GetElement(0), 2.0) + std::pow(poi.at(3).GetElement(1), 2.0)) < 1.0))
        {
            t4Valid = true;
        }
        else
        {
            t4Valid = false;
            t.at(3) = 100e6;
        }
    }

    if ((!t1Valid) && (!t2Valid) && (!t3Valid) && (!t4Valid))
        return false;

    int minIndex = 0;
    double minValue = 1e6;
    for (int i = 0; i < 4; i++)
    {
        if (t.at(i) < minValue)
        {
            minValue = t.at(i);
            minIndex = i;
        }
    }

    abVector<double> validPOI = poi.at(minIndex);

    if (minIndex < 2)
    {
        intPoint = m_transformMatrix.Apply(validPOI, abRT::FWDTFORM);

        abVector<double> orgNormal{3};
        abVector<double> newNormal{3};
        abVector<double> localOrigin{std::vector<double>{0.0, 0.0, 0.0}};
        abVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin, abRT::FWDTFORM);
        orgNormal.SetElement(0, validPOI.GetElement(0));
        orgNormal.SetElement(1, validPOI.GetElement(1));
        orgNormal.SetElement(2, 0.0);
        newNormal = m_transformMatrix.Apply(orgNormal, abRT::FWDTFORM) - globalOrigin;
        newNormal = newNormal.Normalized();
        localNormal = newNormal;

        localColor = m_baseColor;

        double x = validPOI.GetElement(0);
		double y = validPOI.GetElement(1);
		double z = validPOI.GetElement(2);
		double u = atan2(y, x) / M_PI;
		double v = z;
		m_uvCoords.SetElement(0, u);
		m_uvCoords.SetElement(1, v);

        return true;
    }
    else
    {
        if (!CloseEnough(vhat.GetElement(2), 0.0))
        {
            if (sqrtf(std::pow(validPOI.GetElement(0), 2.0) + std::pow(validPOI.GetElement(1), 2.0)) < 1.0)
            {
                intPoint = m_transformMatrix.Apply(validPOI, abRT::FWDTFORM);
                abVector<double> localOrigin{std::vector<double>{0.0, 0.0, 0.0}};
                abVector<double> normalVector{std::vector<double>{0.0, 0.0, 0.0 + validPOI.GetElement(2)}};
                abVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin, abRT::FWDTFORM);
                localNormal = m_transformMatrix.Apply(normalVector, abRT::FWDTFORM) - globalOrigin;
                localNormal = localNormal.Normalized();

                localColor = m_baseColor;

                double x = validPOI.GetElement(0);
				double y = validPOI.GetElement(1);
				double z = validPOI.GetElement(2);
				m_uvCoords.SetElement(0, x);
				m_uvCoords.SetElement(1, y);

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
}