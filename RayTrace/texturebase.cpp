#include "texturebase.hpp"
#include <cmath>

// Constructor / destructor.
abRT::Texture::TextureBase::TextureBase()
{
}

abRT::Texture::TextureBase::~TextureBase()
{
}

// Function to return the color at a given (U,V) location.
abVector<double> abRT::Texture::TextureBase::GetColor(const abVector<double> &uvCoords)
{
    // Setup the output vector.
    abVector<double> outputColor{4};

    // Return the output.
    return outputColor;
}

// Function to set the transform matrix.
void abRT::Texture::TextureBase::SetTransform(const abVector<double> &translation, const double &rotation, const abVector<double> &scale)
{
    // Build the transform matrix.
    Matrix2<double> rotationMatrix = {3, 3, std::vector<double>{cos(rotation), -sin(rotation), 0.0, sin(rotation), cos(rotation), 0.0, 0.0, 0.0, 1.0}};

    Matrix2<double> scaleMatrix = {3, 3, std::vector<double>{scale.GetElement(0), 0.0, 0.0, 0.0, scale.GetElement(1), 0.0, 0.0, 0.0, 1.0}};

    Matrix2<double> translationMatrix = {3, 3, std::vector<double>{1.0, 0.0, translation.GetElement(0), 0.0, 1.0, translation.GetElement(1), 0.0, 0.0, 1.0}};

    // And combine to form the final transform matrix.
    m_transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

// Function to blend colors.
abVector<double> abRT::Texture::TextureBase::BlendColors(const std::vector<abVector<double>> &inputColorList)
{
    // Setup the output color.
    abVector<double> outputColor{3};

    // Return the output.
    return outputColor;
}

// Function to apply the transform.
abVector<double> abRT::Texture::TextureBase::ApplyTransform(const abVector<double> &inputVector)
{
    // Copy the input vector and modify to have three elements.
    abVector<double> newInput{3};
    newInput.SetElement(0, inputVector.GetElement(0));
    newInput.SetElement(1, inputVector.GetElement(1));

    // Apply the transform.
    abVector<double> result = m_transformMatrix * newInput;

    // Produce the output.
    abVector<double> output{2};
    output.SetElement(0, result.GetElement(0));
    output.SetElement(1, result.GetElement(1));

    return output;
}