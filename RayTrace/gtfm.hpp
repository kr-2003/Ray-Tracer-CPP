#ifndef GTFM_H
#define GTFM_H

#include "./abLinearAlgebra/Matrix2.h"
#include "./abLinearAlgebra/Vector.h"
#include "ray.hpp"

namespace abRT
{

    constexpr bool FWDTFORM = true;
    constexpr bool BCKTFORM = false;

    class GTForm
    {
    public:
        GTForm();
        ~GTForm();

        GTForm(const abVector<double> &translation, const abVector<double> &rotation, const abVector<double> &scale);

        GTForm(const Matrix2<double> &fwd, const Matrix2<double> &bck);

        void SetTransform(const abVector<double> &translation,
                          const abVector<double> &rotation,
                          const abVector<double> &scale);

        Matrix2<double> GetForward();
        Matrix2<double> GetBackward();

        abRT::Ray Apply(const abRT::Ray &inputRay, bool dirFlag);
        abVector<double> Apply(const abVector<double> &inputVector, bool dirFlag);

        friend abRT::GTForm operator*(const abRT::GTForm &lhs, const abRT::GTForm &rhs);

        abRT::GTForm operator=(const abRT::GTForm &rhs);

        void PrintMatrix(bool dirFlag);

        static void PrintVector(const abVector<double> &inputVector);

    private:
        void Print(const Matrix2<double> &matrix);

    private:
        Matrix2<double> m_fwdtfm{4, 4};
        Matrix2<double> m_bcktfm{4, 4};
    };
};

#endif