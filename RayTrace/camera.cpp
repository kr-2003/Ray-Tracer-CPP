#include "camera.hpp"
#include "ray.hpp"

abRT::Camera::Camera() {
    std::vector<double> tempdata = {0.0, -10.0, 0.0};
    m_cameraPosition = abVector<double>	{tempdata};
    tempdata = {0.0, 0.0, 0.0};
    m_cameraLookAt = abVector<double> {tempdata};
    tempdata = {0.0, 0.0, 1.0};
    m_cameraUp = abVector<double> {tempdata};
    m_cameraLength = 1.0;
	m_cameraHorzSize = 1.0;
	m_cameraAspectRatio = 1.0;
}

void abRT::Camera::SetPosition(const abVector<double>& newPosition) {
    m_cameraPosition = newPosition;
}

void abRT::Camera::SetLookAt(const abVector<double>& newLookAt) {
    m_cameraLookAt = newLookAt;
}

void abRT::Camera::SetUp(const abVector<double>& upVector) {
    m_cameraUp = upVector;
}

void abRT::Camera::SetLength(double newLength) {
    m_cameraLength = newLength;
}

void abRT::Camera::SetHorzSize(double newSize) {
    m_cameraHorzSize = newSize;
}

void abRT::Camera::SetAspect(double newAspectRatio) {
    m_cameraAspectRatio = newAspectRatio;
}

abVector<double> abRT::Camera::GetPosition() {
    return m_cameraPosition;
}

abVector<double> abRT::Camera::GetLookAt() {
    return m_cameraLookAt;
}

abVector<double> abRT::Camera::GetUp() {
    return m_cameraUp;
}

abVector<double> abRT::Camera::GetU() {
    return m_projectionScreenU;
}

abVector<double> abRT::Camera::GetV() {
    return m_projectionScreenV;
}

abVector<double> abRT::Camera::GetScreenCentre() {
    return m_projectionScreenCentre;
}

double abRT::Camera::GetLength() {
    return m_cameraLength;
}

double abRT::Camera::GetHorzSize() {
    return m_cameraHorzSize;
}

double abRT::Camera::GetAspect() {
    return m_cameraAspectRatio;
}

void abRT::Camera::UpdateCameraGeometry() {
    m_alignmentVector = m_cameraLookAt - m_cameraPosition;
    m_alignmentVector = m_alignmentVector.Normalized();

    m_projectionScreenU = abVector<double>::cross(m_alignmentVector, m_cameraUp);
    m_projectionScreenU = m_projectionScreenU.Normalized();

    m_projectionScreenV = abVector<double>::cross(m_projectionScreenU, m_alignmentVector);
    m_projectionScreenV = m_projectionScreenV.Normalized();

    m_projectionScreenCentre = m_cameraPosition + (m_cameraLength * m_alignmentVector);

    m_projectionScreenU = m_projectionScreenU * m_cameraHorzSize;
	m_projectionScreenV = m_projectionScreenV * (m_cameraHorzSize / m_cameraAspectRatio);
}

abRT::Ray abRT::Camera::GenerateRay(double proScreenX, double proScreenY) {
    // arguments are in u, v coordinate system;
    abVector<double> screenWorldCoordinate = m_projectionScreenCentre + (m_projectionScreenU * proScreenX);
    screenWorldCoordinate = screenWorldCoordinate + (m_projectionScreenV * proScreenY);

    return abRT::Ray(m_cameraPosition, screenWorldCoordinate);
}