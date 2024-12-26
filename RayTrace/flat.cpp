#include "flat.hpp"

abRT::Texture::Flat::Flat()
{
	m_color = abVector<double>{std::vector<double> {1.0, 0.0, 0.0, 1.0}};
}

abRT::Texture::Flat::~Flat()
{

}

abVector<double> abRT::Texture::Flat::GetColor(const abVector<double> &uvCoords)
{
	return m_color;
}

void abRT::Texture::Flat::SetColor(const abVector<double> &inputColor)
{
	m_color = inputColor;
}