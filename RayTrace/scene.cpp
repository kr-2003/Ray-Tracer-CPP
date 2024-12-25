// scene.cpp
#include "scene.hpp"
#include "materialbase.hpp"
#include "simplematerial.hpp"

abRT::Scene::Scene() {

    // creating some test materials
    auto testMaterial = std::make_shared<abRT::SimpleMaterial> (abRT::SimpleMaterial());
    testMaterial->m_baseColor = abVector<double> {std::vector<double>{0.25, 0.5, 0.8}};
    testMaterial->m_reflectivity = 0.1;
    testMaterial->m_shininess = 10.0;

    auto testMaterial2 = std::make_shared<abRT::SimpleMaterial> (abRT::SimpleMaterial());
    testMaterial2->m_baseColor = abVector<double> {std::vector<double>{1.0, 0.5, 0.0}};
    testMaterial2->m_reflectivity = 0.75;
    testMaterial2->m_shininess = 10.0;

    auto testMaterial3 = std::make_shared<abRT::SimpleMaterial> (abRT::SimpleMaterial());
    testMaterial3->m_baseColor = abVector<double> {std::vector<double>{1.0, 0.8, 0.0}};
    testMaterial3->m_reflectivity = 0.25;
    testMaterial3->m_shininess = 10.0;

    auto floorMaterial = std::make_shared<abRT::SimpleMaterial> (abRT::SimpleMaterial());
    floorMaterial->m_baseColor = abVector<double> {std::vector<double>{1.0, 1.0, 1.0}};
    floorMaterial->m_reflectivity = 0.5;
    floorMaterial->m_shininess = 0.0;

    //configure the camera
    std::vector<double> tempdata = {0.0, -10.0, -2.0};
    m_camera.SetPosition(abVector<double>(tempdata));
    tempdata = {0.0, 0.0, 0.0};
    m_camera.SetLookAt(abVector<double>(tempdata));
    tempdata = {0.0, 0.0, 1.0};
    m_camera.SetUp(abVector<double>(tempdata));
    m_camera.SetHorzSize(0.25);
    m_camera.SetAspect(16.0 / 9.0);
    m_camera.UpdateCameraGeometry();

    // test sphere
    m_objectList.push_back(std::make_shared<abRT::ObjSphere>(abRT::ObjSphere()));
    m_objectList.push_back(std::make_shared<abRT::ObjSphere>(abRT::ObjSphere()));
    m_objectList.push_back(std::make_shared<abRT::Cylinder>(abRT::Cylinder()));

    // test plane
    m_objectList.push_back(std::make_shared<abRT::ObjPlane>(abRT::ObjPlane()));
    m_objectList.at(3) -> m_baseColor = abVector<double> {std::vector<double>{0.5, 0.5, 0.5}};

    abRT::GTForm testMatrix1, testMatrix2, testMatrix3, planeMatrix;

    planeMatrix.SetTransform(
        abVector<double> {std::vector<double>{0.0, 0.0, 0.75}},
        abVector<double> {std::vector<double>{0.0, 0.0, 0.0}},
        abVector<double> {std::vector<double>{4.0, 4.0, 1.0}}
    );

    testMatrix1.SetTransform(
        abVector<double> {std::vector<double>{-1.5, 0.0, 0.0}},
        abVector<double> {std::vector<double>{0.0, 0.0, 0.0}},
        abVector<double> {std::vector<double>{0.5, 0.5, 0.5}}
    );

    testMatrix2.SetTransform(
        abVector<double> {std::vector<double>{0.0, 0.0, 0.0}},
        abVector<double> {std::vector<double>{0.0, 0.0, 0.0}},
        abVector<double> {std::vector<double>{0.5, 0.5, 0.5}}
    );

    testMatrix3.SetTransform(
        abVector<double> {std::vector<double>{1.5, 0.0, 0.0}},
        abVector<double> {std::vector<double>{0.0, 0.0, 0.0}},
        abVector<double> {std::vector<double>{0.5, 0.5, 0.5}}
    );

    m_objectList.at(0) -> SetTransformMatrix(testMatrix1);
    m_objectList.at(1) -> SetTransformMatrix(testMatrix2);
    m_objectList.at(2) -> SetTransformMatrix(testMatrix3);
    m_objectList.at(3) -> SetTransformMatrix(planeMatrix);

    m_objectList.at(0) -> m_baseColor = abVector<double>{std::vector<double>{0.25, 0.5, 0.8}};
	m_objectList.at(1) -> m_baseColor = abVector<double>{std::vector<double>{1.0, 0.5, 0.0}};
	m_objectList.at(2) -> m_baseColor = abVector<double>{std::vector<double>{1.0, 0.8, 0.0}};

    m_objectList.at(0) -> AssignMaterial(testMaterial3);
    m_objectList.at(1) -> AssignMaterial(testMaterial);
    m_objectList.at(2) -> AssignMaterial(testMaterial2);
    m_objectList.at(3) -> AssignMaterial(floorMaterial);
    // test light
    // Construct a test light.
	m_lightList.push_back(std::make_shared<abRT::PointLight> (abRT::PointLight()));
	m_lightList.at(0) -> m_location = abVector<double> {std::vector<double> {5.0, -10.0, -5.0}};
	m_lightList.at(0) -> m_color = abVector<double> {std::vector<double> {0.0, 0.0, 1.0}};
	
	m_lightList.push_back(std::make_shared<abRT::PointLight> (abRT::PointLight()));
	m_lightList.at(1) -> m_location = abVector<double> {std::vector<double> {-5.0, -10.0, -5.0}};
	m_lightList.at(1) -> m_color = abVector<double> {std::vector<double> {1.0, 0.0, 0.0}};
	
	m_lightList.push_back(std::make_shared<abRT::PointLight> (abRT::PointLight()));
	m_lightList.at(2) -> m_location = abVector<double> {std::vector<double> {0.0, -10.0, -5.0}};
	m_lightList.at(2) -> m_color = abVector<double> {std::vector<double> {0.0, 1.0, 0.0}};
}

bool abRT::Scene::Render(abImage &outputImage) {
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();

    // loop over each pixel 
    abRT::Ray cameraRay;
    abVector<double> intPoint {3};
    abVector<double> localNormal {3};
    abVector<double> localColor {3};

    double xFact = (1.0 / static_cast<double>(xSize)) * 2.0;
    double yFact = (1.0 / static_cast<double>(ySize)) * 2.0;

    double minDist = 1e6;
    double maxDist = 0;

    for(int x = 0; x < xSize; x++) {
        for(int y = 0; y < ySize; y++) {
            float normX = (static_cast<double>(x) * xFact) - 1.0;
            float normY = (static_cast<double>(y) * yFact) - 1.0;

            m_camera.GenerateRay(normX, normY, cameraRay);

            std::shared_ptr<abRT::ObjectBase> closestObject;

            abVector<double> closestIntPoint {3};
            abVector<double> closestLocalNormal {3};
            abVector<double> closestLocalColor {3};

            bool intersectionFound = CastRay(cameraRay, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);


            if(intersectionFound) {
                if(closestObject -> m_hasMaterial) {
                    abRT::MaterialBase::m_reflectionRayCount = 0;

                    abVector<double> color = closestObject -> m_pMaterial -> ComputeColor(m_objectList, m_lightList, closestObject, closestIntPoint, closestLocalNormal, cameraRay);

                    outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));

                } else {
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


bool abRT::Scene::CastRay(abRT::Ray &castRay, std::shared_ptr<abRT::ObjectBase> &closestObject, abVector<double> &closestIntPoint, abVector<double> &closestLocalNormal, abVector<double> &closestLocalColor) {

    abVector<double> intPoint {3};
    abVector<double> localNormal {3};
    abVector<double> localColor {3};

    double minDist = 1e6;
    bool intersectionFound = false;
    for(auto currentObject : m_objectList) {
        bool validInt = currentObject -> TestIntersections(castRay, intPoint, localNormal, localColor);

        if(validInt) {
            intersectionFound = true;

            double dist = (intPoint - castRay.m_point1).Norm();

            if(dist < minDist) {
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