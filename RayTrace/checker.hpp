#ifndef CHECKER_H
#define CHECKER_H

#include "texturebase.hpp"

namespace abRT
{
	namespace Texture
	{
		class Checker : public TextureBase
		{
			public:
				// Constructor / destructor.
				Checker();
				virtual ~Checker() override;
			
				// Function to return the color.
				virtual abVector<double> GetColor(const abVector<double> &uvCoords) override;
			
				// Function to set the colors.
				void SetColor(const abVector<double> &inputColor1, const abVector<double> &inputColor2);
			
		private:
			abVector<double> m_color1 {4};
			abVector<double> m_color2 {4};
			
		};
	}
}

#endif