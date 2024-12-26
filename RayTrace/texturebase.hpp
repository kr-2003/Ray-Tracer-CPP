#ifndef TEXTUREBASE_H
#define TEXTUREBASE_H

#include <memory>
#include "./abLinearAlgebra/Matrix2.h"
#include "./abLinearAlgebra/Vector.h"
#include "ray.hpp"

namespace abRT
{
	namespace Texture
	{
		class TextureBase
		{
			public:
				TextureBase();
				virtual ~TextureBase();
				virtual abVector<double> GetColor(const abVector<double> &uvCoords);
				void SetTransform(const abVector<double> &translation, const double &rotation, const abVector<double> &scale);
				static abVector<double> BlendColors(const std::vector<abVector<double>> &inputColorList);
				abVector<double> ApplyTransform(const abVector<double> &inputVector);
				
			private:
			
			private:
				Matrix2<double> m_transformMatrix {3, 3, std::vector<double>{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}};
		};
	}
}

#endif