#include "lightbase.hpp"

abRT::LightBase::LightBase()
{
}

abRT::LightBase::~LightBase()
{
}

bool abRT::LightBase::ComputeIllumination(const abVector<double> &intPoint, const abVector<double> &localNormal,
                                          const std::vector<std::shared_ptr<abRT::ObjectBase>> &objectList,
                                          const std::shared_ptr<abRT::ObjectBase> &currObject,
                                          abVector<double> &color, double &intensity)
{
    return false;
}