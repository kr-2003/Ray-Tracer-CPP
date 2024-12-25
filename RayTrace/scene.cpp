// scene.cpp
#include "scene.hpp"
#include "materialbase.hpp"
#include "simplematerial.hpp"

abRT::Scene::Scene()
{
    m_camera.SetPosition(abVector<double>{std::vector<double>{3.0, -5.0, -2.0}});
    m_camera.SetLookAt(abVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
    m_camera.SetUp(abVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
    m_camera.SetHorzSize(0.75);
    m_camera.SetAspect(16.0 / 9.0);
    // m_camera.SetAspect(1.0);
    m_camera.UpdateCameraGeometry();

    auto silverMetal = std::make_shared<abRT::SimpleMaterial>(abRT::SimpleMaterial());
    auto goldMetal = std::make_shared<abRT::SimpleMaterial>(abRT::SimpleMaterial());
    auto blueDiffuse = std::make_shared<abRT::SimpleMaterial>(abRT::SimpleMaterial());
    auto yellowDiffuse = std::make_shared<abRT::SimpleMaterial>(abRT::SimpleMaterial());
    auto orangeDiffuse = std::make_shared<abRT::SimpleMaterial>(abRT::SimpleMaterial());
    auto floorMaterial = std::make_shared<abRT::SimpleMaterial>(abRT::SimpleMaterial());
    auto wallMaterial = std::make_shared<abRT::SimpleMaterial>(abRT::SimpleMaterial());

    silverMetal->m_baseColor = abVector<double>{std::vector<double>{0.5, 0.5, 0.8}};
    silverMetal->m_reflectivity = 0.5;
    silverMetal->m_shininess = 20.0;

    goldMetal->m_baseColor = abVector<double>{std::vector<double>{0.8, 0.8, 0.3}};
    goldMetal->m_reflectivity = 0.25;
    goldMetal->m_shininess = 20.0;

    blueDiffuse->m_baseColor = abVector<double>{std::vector<double>{0.2, 0.2, 0.8}};
    blueDiffuse->m_reflectivity = 0.05;
    blueDiffuse->m_shininess = 5.0;

    yellowDiffuse->m_baseColor = abVector<double>{std::vector<double>{0.8, 0.8, 0.2}};
    yellowDiffuse->m_reflectivity = 0.05;
    yellowDiffuse->m_shininess = 5.0;

    orangeDiffuse->m_baseColor = abVector<double>{std::vector<double>{1.0, 0.5, 0.0}};
    orangeDiffuse->m_reflectivity = 0.05;
    orangeDiffuse->m_shininess = 5.0;

    floorMaterial->m_baseColor = abVector<double>{std::vector<double>{1.0, 1.0, 1.0}};
    floorMaterial->m_reflectivity = 0.3;
    floorMaterial->m_shininess = 2.0;

    wallMaterial->m_baseColor = abVector<double>{std::vector<double>{1.0, 0.1, 0.1}};
    wallMaterial->m_reflectivity = 0.75;
    wallMaterial->m_shininess = 1.0;

    auto cone = std::make_shared<abRT::Cone>(abRT::Cone());
    cone->SetTransformMatrix(abRT::GTForm{abVector<double>{std::vector<double>{0.0, 0.0, -0.5}},
                                          abVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                                          abVector<double>{std::vector<double>{1.0, 1.0, 2.0}}});
    cone->AssignMaterial(silverMetal);

    auto leftSphere = std::make_shared<abRT::ObjSphere>(abRT::ObjSphere());
    leftSphere->SetTransformMatrix(abRT::GTForm{abVector<double>{std::vector<double>{1.5, -2.0, 0.5}},
                                                abVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                                                abVector<double>{std::vector<double>{0.5, 0.5, 0.5}}});
    leftSphere->AssignMaterial(blueDiffuse);

    auto rightSphere = std::make_shared<abRT::ObjSphere>(abRT::ObjSphere());
    rightSphere->SetTransformMatrix(abRT::GTForm{abVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
                                                 abVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                                                 abVector<double>{std::vector<double>{1.0, 1.0, 1.0}}});
    rightSphere->AssignMaterial(yellowDiffuse);

    auto topSphere = std::make_shared<abRT::ObjSphere>(abRT::ObjSphere());
    topSphere->SetTransformMatrix(abRT::GTForm{abVector<double>{std::vector<double>{0.0, 0.0, -1.0}},
                                               abVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                                               abVector<double>{std::vector<double>{0.5, 0.5, 0.5}}});
    topSphere->AssignMaterial(orangeDiffuse);

    auto floor = std::make_shared<abRT::ObjPlane>(abRT::ObjPlane());
    floor->SetTransformMatrix(abRT::GTForm{abVector<double>{std::vector<double>{0.0, 0.0, 1.0}},
                                           abVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                                           abVector<double>{std::vector<double>{16.0, 16.0, 1.0}}});
    floor->AssignMaterial(floorMaterial);

    auto leftWall = std::make_shared<abRT::ObjPlane>(abRT::ObjPlane());
    leftWall->SetTransformMatrix(abRT::GTForm{abVector<double>{std::vector<double>{-4.0, 0.0, 0.0}},
                                              abVector<double>{std::vector<double>{0.0, -M_PI / 2.0, 0.0}},
                                              abVector<double>{std::vector<double>{16.0, 16.0, 1.0}}});
    leftWall->AssignMaterial(wallMaterial);

    auto backWall = std::make_shared<abRT::ObjPlane>(abRT::ObjPlane());
    backWall->SetTransformMatrix(abRT::GTForm{abVector<double>{std::vector<double>{0.0, 4.0, 0.0}},
                                              abVector<double>{std::vector<double>{-M_PI / 2.0, 0.0, 0.0}},
                                              abVector<double>{std::vector<double>{16.0, 16.0, 1.0}}});
    backWall->AssignMaterial(wallMaterial);


    auto cylinder1 = std::make_shared<abRT::Cylinder>(abRT::Cylinder());
    cylinder1->SetTransformMatrix(abRT::GTForm{abVector<double>{std::vector<double>{-1.5, -2.0, 1.0}},
                                               abVector<double>{std::vector<double>{0.0, -M_PI / 2.0, 0.0}},
                                               abVector<double>{std::vector<double>{0.25, 0.25, 1.0}}});
    cylinder1->AssignMaterial(goldMetal);

    auto cylinder2 = std::make_shared<abRT::Cylinder>(abRT::Cylinder());
    cylinder2->SetTransformMatrix(abRT::GTForm{abVector<double>{std::vector<double>{-1.0, -2.0, 0.0}},
                                               abVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                                               abVector<double>{std::vector<double>{0.25, 0.25, 1.0}}});
    cylinder2->AssignMaterial(silverMetal);

    auto cone2 = std::make_shared<abRT::Cone>(abRT::Cone());
    cone2->SetTransformMatrix(abRT::GTForm{abVector<double>{std::vector<double>{0.0, -1.0, 0.0}},
                                           abVector<double>{std::vector<double>{M_PI / 4.0, 0.0, 0.0}},
                                           abVector<double>{std::vector<double>{0.5, 0.5, 1.0}}});
    cone2->AssignMaterial(goldMetal);

    // // Put the objects into the scene.
    m_objectList.push_back(cone);
    m_objectList.push_back(leftSphere);
    m_objectList.push_back(rightSphere);
    m_objectList.push_back(topSphere);
    m_objectList.push_back(floor);
    m_objectList.push_back(leftWall);
    m_objectList.push_back(backWall);
    m_objectList.push_back(cylinder1);
    m_objectList.push_back(cylinder2);
    m_objectList.push_back(cone2);

    // Construct and setup the lights.
    m_lightList.push_back(std::make_shared<abRT::PointLight>(abRT::PointLight()));
    m_lightList.at(0)->m_location = abVector<double>{std::vector<double>{3.0, -10.0, -5.0}};
    m_lightList.at(0)->m_color = abVector<double>{std::vector<double>{1.0, 1.0, 1.0}};

    m_lightList.push_back(std::make_shared<abRT::PointLight>(abRT::PointLight()));
    m_lightList.at(1)->m_location = abVector<double>{std::vector<double>{0.0, -10.0, -5.0}};
    m_lightList.at(1)->m_color = abVector<double>{std::vector<double>{1.0, 1.0, 1.0}};
}

bool abRT::Scene::Render(abImage &outputImage)
{
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();

    // loop over each pixel
    abRT::Ray cameraRay;
    abVector<double> intPoint{3};
    abVector<double> localNormal{3};
    abVector<double> localColor{3};

    double xFact = (1.0 / static_cast<double>(xSize)) * 2.0;
    double yFact = (1.0 / static_cast<double>(ySize)) * 2.0;

    double minDist = 1e6;
    double maxDist = 0;

    for (int x = 0; x < xSize; x++)
    {
        for (int y = 0; y < ySize; y++)
        {
            std::cout << x << " " << y << std::endl;
            float normX = (static_cast<double>(x) * xFact) - 1.0;
            float normY = (static_cast<double>(y) * yFact) - 1.0;

            m_camera.GenerateRay(normX, normY, cameraRay);

            std::shared_ptr<abRT::ObjectBase> closestObject;

            abVector<double> closestIntPoint{3};
            abVector<double> closestLocalNormal{3};
            abVector<double> closestLocalColor{3};

            bool intersectionFound = CastRay(cameraRay, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);

            if (intersectionFound)
            {
                if (closestObject->m_hasMaterial)
                {
                    abRT::MaterialBase::m_reflectionRayCount = 0;

                    abVector<double> color = closestObject->m_pMaterial->ComputeColor(m_objectList, m_lightList, closestObject, closestIntPoint, closestLocalNormal, cameraRay);

                    outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
                }
                else
                {
                    abVector<double> matColor = abRT::MaterialBase::ComputeDiffuseColor(m_objectList, m_lightList, closestObject, closestIntPoint, closestLocalNormal, closestObject->m_baseColor);

                    outputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
                }
            }
        }
    }

    std::cout << "Minimum distance: " << minDist << std::endl;
    std::cout << "Maximum distance: " << maxDist << std::endl;

    return 1;
}

bool abRT::Scene::CastRay(abRT::Ray &castRay, std::shared_ptr<abRT::ObjectBase> &closestObject, abVector<double> &closestIntPoint, abVector<double> &closestLocalNormal, abVector<double> &closestLocalColor)
{

    abVector<double> intPoint{3};
    abVector<double> localNormal{3};
    abVector<double> localColor{3};

    double minDist = 1e6;
    bool intersectionFound = false;
    for (auto currentObject : m_objectList)
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
                closestLocalNormal = localNormal;
                closestIntPoint = intPoint;
                closestLocalColor = localColor;
            }
        }
    }

    return intersectionFound;
}