#include "cone.hpp"
#include <cmath>

// The default constructor.
abRT::Cone::Cone()
{
}

// The destructor.
abRT::Cone::~Cone()
{
}

// The function to test for intersections.
bool abRT::Cone::TestIntersections(const abRT::Ray &castRay, abVector<double> &intPoint,
                                   abVector<double> &localNormal, abVector<double> &localColor)
{
    // Copy the ray and apply the backwards transform.
    abRT::Ray bckRay = m_transformMatrix.Apply(castRay, abRT::BCKTFORM);

    // Copy the m_lab vector from bckRay and normalize it.
    abVector<double> v = bckRay.m_lab;
    v = v.Normalized();

    // Get the start point of the line.
    abVector<double> p = bckRay.m_point1;

    // Compute a, b and c.
    double a = std::pow(v.GetElement(0), 2.0) + std::pow(v.GetElement(1), 2.0) - std::pow(v.GetElement(2), 2.0);
    double b = 2 * (p.GetElement(0) * v.GetElement(0) + p.GetElement(1) * v.GetElement(1) - p.GetElement(2) * v.GetElement(2));
    double c = std::pow(p.GetElement(0), 2.0) + std::pow(p.GetElement(1), 2.0) - std::pow(p.GetElement(2), 2.0);

    // Compute b^2 - 4ac.
    double numSQRT = sqrtf(std::pow(b, 2.0) - 4 * a * c);

    std::array<abVector<double>, 3> poi;
    std::array<double, 3> t;
    bool t1Valid, t2Valid, t3Valid;
    if (numSQRT > 0.0)
    {
        // Compute the values of t.
        t.at(0) = (-b + numSQRT) / (2 * a);
        t.at(1) = (-b - numSQRT) / (2 * a);

        // Compute the points of intersection.
        poi.at(0) = bckRay.m_point1 + (v * t[0]);
        poi.at(1) = bckRay.m_point1 + (v * t[1]);

        if ((t.at(0) > 0.0) && (poi.at(0).GetElement(2) > 0.0) && (poi.at(0).GetElement(2) < 1.0))
        {
            t1Valid = true;
        }
        else
        {
            t1Valid = false;
            t.at(0) = 100e6;
        }

        if ((t.at(1) > 0.0) && (poi.at(1).GetElement(2) > 0.0) && (poi.at(1).GetElement(2) < 1.0))
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

    // And test the end cap.
    if (CloseEnough(v.GetElement(2), 0.0))
    {
        t3Valid = false;
        t.at(2) = 100e6;
    }
    else
    {
        // Compute values for t.
        t.at(2) = (bckRay.m_point1.GetElement(2) - 1.0) / -v.GetElement(2);

        // Compute points of intersection.
        poi.at(2) = bckRay.m_point1 + t.at(2) * v;

        // Check if these are valid.
        if ((t.at(2) > 0.0) && (sqrtf(std::pow(poi.at(2).GetElement(0), 2.0) + std::pow(poi.at(2).GetElement(1), 2.0)) < 1.0))
        {
            t3Valid = true;
        }
        else
        {
            t3Valid = false;
            t.at(2) = 100e6;
        }
    }

    // If no valid intersections found, then we can stop.
    if ((!t1Valid) && (!t2Valid) && (!t3Valid))
        return false;

    // Check for the smallest valid value of t.
    int minIndex = 0;
    double minValue = 10e6;
    for (int i = 0; i < 3; ++i)
    {
        if (t.at(i) < minValue)
        {
            minValue = t.at(i);
            minIndex = i;
        }
    }

    /* If minIndex is either 0 or 1, then we have a valid intersection
        with the cone itself. */
    abVector<double> validPOI = poi.at(minIndex);
    if (minIndex < 2)
    {
        // Transform the intersection point back into world coordinates.
        intPoint = m_transformMatrix.Apply(validPOI, abRT::FWDTFORM);

        // Compute the local normal.
        abVector<double> orgNormal{3};
        abVector<double> newNormal{3};
        abVector<double> localOrigin{std::vector<double>{0.0, 0.0, 0.0}};
        abVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin, abRT::FWDTFORM);
        double tX = validPOI.GetElement(0);
        double tY = validPOI.GetElement(1);
        double tZ = -sqrtf(pow(tX, 2.0) + pow(tY, 2.0));
        orgNormal.SetElement(0, tX);
        orgNormal.SetElement(1, tY);
        orgNormal.SetElement(2, tZ);
        newNormal = m_transformMatrix.Apply(orgNormal, abRT::FWDTFORM) - globalOrigin;
        newNormal = newNormal.Normalized();
        localNormal = newNormal;

        // Return the base color.
        localColor = m_baseColor;

        double x = validPOI.GetElement(0);
		double y = validPOI.GetElement(1);
		double z = validPOI.GetElement(2);
		double u = atan2(y,x) / M_PI;
		double v = (z * 2.0) + 1.0;
		m_uvCoords.SetElement(0, u);
		m_uvCoords.SetElement(1, v);

        return true;
    }
    else
    {
        // Check the end cap.
        if (!CloseEnough(v.GetElement(2), 0.0))
        {
            // Check if we are inside the disk.
            if (sqrtf(std::pow(validPOI.GetElement(0), 2.0) + std::pow(validPOI.GetElement(1), 2.0)) < 1.0)
            {
                // Transform the intersection point back into world coordinates.
                intPoint = m_transformMatrix.Apply(validPOI, abRT::FWDTFORM);

                // Compute the local normal.
                abVector<double> localOrigin{std::vector<double>{0.0, 0.0, 0.0}};
                abVector<double> normalVector{std::vector<double>{0.0, 0.0, 1.0}};
                abVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin, abRT::FWDTFORM);
                localNormal = m_transformMatrix.Apply(normalVector, abRT::FWDTFORM) - globalOrigin;
                localNormal = localNormal.Normalized();

                // Return the base color.
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