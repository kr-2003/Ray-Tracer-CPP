#ifndef CONE_H
#define CONE_H

#include "objectbase.hpp"
#include "gtfm.hpp"

namespace abRT
{
	class Cone : public ObjectBase
	{
		public:
			// Default constructor.
			Cone();
			
			// Override the destructor.
			virtual ~Cone() override;
			
			// Override the function to test for intersections.
			virtual bool TestIntersections(	const abRT::Ray &castRay, abVector<double> &intPoint,
																			abVector<double> &localNormal, abVector<double> &localColor) override;			
	};
}

#endif