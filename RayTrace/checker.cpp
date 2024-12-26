#include "checker.hpp"

// Constructor / destructor.
abRT::Texture::Checker::Checker()
{
	m_color1 = abVector<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}};
	m_color2 = abVector<double>{std::vector<double>{0.2, 0.2, 0.2, 1.0}};
}

abRT::Texture::Checker::~Checker()
{

}

// Function to return the color.
abVector<double> abRT::Texture::Checker::GetColor(const abVector<double> &uvCoords)
{
	// Apply the local transform to the (u,v) coordinates.
	abVector<double> inputLoc = uvCoords;
	abVector<double> newLoc = ApplyTransform(inputLoc);
	double newU = newLoc.GetElement(0);
	double newV = newLoc.GetElement(1);
	
	abVector<double> localColor {4};
	int check = static_cast<int>(floor(newU)) + static_cast<int>(floor(newV));
	
	if ((check % 2) == 0)
	{
		localColor = m_color1;
	}
	else
	{
		localColor = m_color2;
	}
	
	return localColor;
}

// Function to set the colors.
void abRT::Texture::Checker::SetColor(const abVector<double> &inputColor1, const abVector<double> &inputColor2)
{
	m_color1 = inputColor1;
	m_color2 = inputColor2;
}