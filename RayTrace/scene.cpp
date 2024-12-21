// scene.cpp
#include "scene.hpp"

abRT::Scene::Scene() {
    //configure the camera
    std::vector<double> tempdata = {0.0, -10.0, 0.0};
    m_camera.SetPosition(abVector<double>(tempdata));
    tempdata = {0.0, 0.0, 0.0};
    m_camera.SetLookAt(abVector<double>(tempdata));
    tempdata = {0.0, 0.0, 1.0};
    m_camera.SetUp(abVector<double>(tempdata));
    m_camera.SetHorzSize(0.25);
    m_camera.SetAspect(16.0 / 9.0);
    m_camera.UpdateCameraGeometry();
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
            
            bool validInt = m_testSphere.TestIntersections(cameraRay, intPoint, localNormal, localColor);

            if(validInt) {
                double dist = (intPoint - cameraRay.m_point1).Norm();
                if(dist > maxDist) maxDist = dist;
                if(dist < minDist) minDist = dist;
                outputImage.SetPixel(x, y, 0.0, 0.0, 255.0 - ((dist - 9.0) / 0.94605) * 255.0);
            } else {
                outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
            }
        }
    }

    std::cout << "Minimum distance: " << minDist << std::endl;
	std::cout << "Maximum distance: " << maxDist << std::endl;

    return 1;
} 