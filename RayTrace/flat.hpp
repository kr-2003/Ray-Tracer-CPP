#ifndef FLAT_H
#define FLAT_H

#include "texturebase.hpp"

namespace abRT
{
	namespace Texture
	{
		class Flat : public TextureBase
		{
			public:
				Flat();
				virtual ~Flat() override;
				
				virtual abVector<double> GetColor(const abVector<double> &uvCoords) override;
				
				void SetColor(const abVector<double> &inputColor);
				
			private:
				abVector<double> m_color {4};
				
		};
	}
}

#endif