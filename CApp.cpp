#include "CApp.h"
#include "./RayTrace/abLinearAlgebra/Vector.h"

CApp::CApp() {
    isRunning = true;
    pWindow = NULL;
    pRenderer = NULL;
}

bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    pWindow = SDL_CreateWindow("abRayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    if(pWindow != NULL) {
        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
        m_image.Initialise(1280, 720, pRenderer);

        // testing camera class
        abRT::Camera testCamera;
        std::vector<double> tempdata = {0.0, 0.0, 0.0};
        testCamera.SetPosition(abVector<double>(tempdata));
        tempdata = {0.0, 2.0, 0.0};
		testCamera.SetLookAt(abVector<double>(tempdata));
        tempdata = {0.0, 0.0, 1.0};
		testCamera.SetUp(abVector<double>(tempdata));
		testCamera.SetLength(1.0);
		testCamera.SetHorzSize(1.0);
		testCamera.SetAspect(1.0);
		testCamera.UpdateCameraGeometry();
		
		// Get the screen centre and U,V vectors and display.
		auto screenCentre = testCamera.GetScreenCentre();
		auto screenU = testCamera.GetU();
		auto screenV = testCamera.GetV();
		
		// And display to the terminal.
		std::cout << "Camera screen centre:" << std::endl;
        std::cout << screenCentre << std::endl;
		std::cout << "\nCamera U vector:" << std::endl;
        std::cout << screenU << std::endl;
		std::cout << "\nCamera V vector:" << std::endl;
        std::cout << screenV << std::endl;
    } else {
        return false;
    }

    return true;
}

int CApp::OnExecute() {
    SDL_Event event;

    if(OnInit() == false) {
        return -1;
    }

    while(isRunning) {
        while(SDL_PollEvent(&event) != 0) {
            OnEvent(&event);
        }
        OnLoop();
        OnRender();
    }

    OnExit();

    return 0;
}

void CApp::OnEvent(SDL_Event *event) {
    if(event->type == SDL_QUIT) {
        isRunning = false;
    }
}

void CApp::OnLoop() {
    
}

void CApp::OnRender() {
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(pRenderer);
    m_scene.Render(m_image);
    m_image.Display();
    SDL_RenderPresent(pRenderer);
}

void CApp::OnExit() {
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = NULL;
    SDL_Quit();
}