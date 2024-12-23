// scene.cpp
#include "scene.hpp"

abRT::Scene::Scene() {
    //configure the camera
    std::vector<double> tempdata = {0.0, -10.0, -1.0};
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
    m_objectList.push_back(std::make_shared<abRT::ObjSphere>(abRT::ObjSphere()));

    // test plane
    m_objectList.push_back(std::make_shared<abRT::ObjPlane>(abRT::ObjPlane()));
    m_objectList.at(3) -> m_baseColor = abVector<double> {std::vector<double>{128.0, 128.0, 128.0}};

    abRT::GTForm testMatrix1, testMatrix2, testMatrix3;

    testMatrix1.SetTransform(
        abVector<double> {std::vector<double>{-1.5, 0.0, 0.0}},
        abVector<double> {std::vector<double>{0.0, 0.0, 0.0}},
        abVector<double> {std::vector<double>{0.5, 0.5, 0.75}}
    );

    testMatrix2.SetTransform(
        abVector<double> {std::vector<double>{0.0, 0.0, 0.0}},
        abVector<double> {std::vector<double>{0.0, 0.0, 0.0}},
        abVector<double> {std::vector<double>{0.75, 0.5, 0.5}}
    );

    testMatrix3.SetTransform(
        abVector<double> {std::vector<double>{1.5, 0.0, 0.0}},
        abVector<double> {std::vector<double>{0.0, 0.0, 0.0}},
        abVector<double> {std::vector<double>{0.75, 0.75, 0.75}}
    );

    m_objectList.at(0) -> SetTransformMatrix(testMatrix1);
    m_objectList.at(1) -> SetTransformMatrix(testMatrix2);
    m_objectList.at(2) -> SetTransformMatrix(testMatrix3);

    m_objectList.at(0) -> m_baseColor = abVector<double> {std::vector<double>{64.0, 128.0, 200.0}};
    m_objectList.at(1) -> m_baseColor = abVector<double> {std::vector<double>{255.0, 128.0, 0.0}};
    m_objectList.at(2) -> m_baseColor = abVector<double> {std::vector<double>{255.0, 200.0, 0.0}};

    // test light
    m_lightList.push_back(std::make_shared<abRT::PointLight>(abRT::PointLight()));
    tempdata = {5.0, -10.0, -5.0};
    m_lightList.at(0) -> m_location = abVector<double> {tempdata};
    tempdata = {255.0, 255.0, 255.0};
    m_lightList.at(0) -> m_color = abVector<double> {tempdata};
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

            for(auto &currObject : m_objectList) {
                            
                bool validInt = currObject->TestIntersections(cameraRay, intPoint, localNormal, localColor);

                if(validInt) {
                    double intensity;
                    abVector<double> color{3};
                    bool validIllum = false;
                    for(auto &currentLight : m_lightList) {
                        validIllum = currentLight->ComputeIllumination(intPoint, localNormal, m_objectList, currObject, color, intensity);
                    }
                    double dist = (intPoint - cameraRay.m_point1).Norm();
                    if(dist > maxDist) maxDist = dist;
                    if(dist < minDist) minDist = dist;
                    if(validIllum) {
                        outputImage.SetPixel(x, y, 255.0 * intensity, localColor.GetElement(1) * intensity, localColor.GetElement(2) * intensity);
                    } else {
                        // nothing
                    }
                    
                } else {
                    // nothing
                }
            }
        }
    }

    std::cout << "Minimum distance: " << minDist << std::endl;
	std::cout << "Maximum distance: " << maxDist << std::endl;

    return 1;
} 