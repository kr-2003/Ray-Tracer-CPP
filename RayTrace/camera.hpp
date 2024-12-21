#ifndef CAMERA_H
#define CAMERA_H

#include "./abLinearAlgebra/Vector.h"
#include "ray.hpp"

namespace abRT {
    class Camera {
        public:
            Camera();

            void SetPosition(const abVector<double>& newPosition);
            void SetLookAt(const abVector<double>& newLookAt);
            void SetUp(const abVector<double>& upVector);
            void SetLength(double newLength);
            void SetHorzSize(double newSize);
            void SetAspect(double newAspectRatio);

            abVector<double> GetPosition();
            abVector<double> GetLookAt();
            abVector<double> GetUp();
            abVector<double> GetU();
            abVector<double> GetV();
            abVector<double> GetScreenCentre();
            double GetLength();
            double GetHorzSize();
            double GetAspect();

            Ray GenerateRay(double proScreenX, double proScreenY);

            void UpdateCameraGeometry();

        private:
            abVector<double> m_cameraPosition               {3};
            abVector<double> m_cameraLookAt		            {3};
            abVector<double> m_cameraUp				        {3};
            double m_cameraLength;
            double m_cameraHorzSize;
            double m_cameraAspectRatio;
            
            abVector<double> m_alignmentVector				{3};
            abVector<double> m_projectionScreenU			{3};
            abVector<double> m_projectionScreenV			{3};
            abVector<double> m_projectionScreenCentre	    {3};
    };
};

#endif