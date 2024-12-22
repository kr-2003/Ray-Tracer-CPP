#include "gtfm.hpp"

abRT::GTForm::GTForm() {
    m_fwdtfm.GetIdentityMatrix();
    m_bcktfm.GetIdentityMatrix();
};

abRT::GTForm::~GTForm() {

};

abRT::GTForm::GTForm(const Matrix2<double> &fwd, const Matrix2<double> &bck) {
    if ((fwd.GetNumRows() != 4) || (fwd.GetNumCols() != 4) || (bck.GetNumRows() != 4) || (bck.GetNumCols() != 4)) {
		throw std::invalid_argument("Cannot construct GTform, inputs are not all 4x4.");
	}

    m_fwdtfm = fwd;
    m_bcktfm = bck;
};

Matrix2<double> abRT::GTForm::GetForward() {
    return m_fwdtfm;
};

Matrix2<double> abRT::GTForm::GetBackward() {
    return m_bcktfm;
};

void abRT::GTForm::SetTransform (const abVector<double> &translation, 
                               const abVector<double> &rotation,
                               const abVector<double> &scale)
{
    Matrix2<double> translationMatrix {4, 4};
    Matrix2<double> rotationMatrixX   {4, 4};
    Matrix2<double> rotationMatrixY   {4, 4};
    Matrix2<double> rotationMatrixZ   {4, 4};
    Matrix2<double> scaleMatrix       {4, 4};

    translationMatrix.GetIdentityMatrix();
    rotationMatrixX.GetIdentityMatrix();
    rotationMatrixY.GetIdentityMatrix();
    rotationMatrixZ.GetIdentityMatrix();
    scaleMatrix.GetIdentityMatrix();

    for(int i = 0; i < 3; i++) {
        translationMatrix.SetElement(i, 3, translation.GetElement(i));
    }
    for(int i = 0; i < 3; i++) {
        scaleMatrix.SetElement(i, i, scale.GetElement(i));
    }

    rotationMatrixX.SetElement(1, 1, cos(rotation.GetElement(0)));
    rotationMatrixX.SetElement(1, 2, -sin(rotation.GetElement(0)));
    rotationMatrixX.SetElement(2, 1, sin(rotation.GetElement(0)));
    rotationMatrixX.SetElement(2, 2, cos(rotation.GetElement(0)));

    rotationMatrixY.SetElement(0, 0, cos(rotation.GetElement(1)));
    rotationMatrixY.SetElement(0, 2, sin(rotation.GetElement(1)));
    rotationMatrixY.SetElement(2, 0, -sin(rotation.GetElement(1)));
    rotationMatrixY.SetElement(2, 2, cos(rotation.GetElement(1)));

    rotationMatrixZ.SetElement(0, 0, cos(rotation.GetElement(2)));
    rotationMatrixZ.SetElement(0, 1, -sin(rotation.GetElement(2)));
    rotationMatrixZ.SetElement(1, 0, sin(rotation.GetElement(2)));
    rotationMatrixZ.SetElement(1, 1, cos(rotation.GetElement(2)));

    // m_fwdtfm = translationMatrix * scaleMatrix;

    // std::cout << translationMatrix << std::endl;
    // std::cout << scaleMatrix << std::endl;
    // std::cout << rotationMatrixX << std::endl;
    // std::cout << rotationMatrixY << std::endl;
    // std::cout << rotationMatrixZ << std::endl;

    // m_fwdtfm = m_fwdtfm * rotationMatrixY * rotationMatrixZ;
    m_fwdtfm = translationMatrix * scaleMatrix * rotationMatrixX * rotationMatrixY * rotationMatrixZ;


    // m_fwdtfm = translationMatrix * scaleMatrix * rotationMatrixX * rotationMatrixY * rotationMatrixZ;

    m_bcktfm = m_fwdtfm;

    // std::cout << m_fwdtfm << std::endl;
    m_bcktfm.invertMatrix();
}

abRT::Ray abRT::GTForm::Apply(const abRT::Ray &inputRay, bool dirFlag) {
    abVector<double> point1 = inputRay.GetPoint1();
    abVector<double> point2 = inputRay.GetPoint2();
    abRT::Ray res;
    if(dirFlag) {
        res.m_point1 = this->Apply(point1, abRT::FWDTFORM);
        res.m_point2 = this->Apply(point2, abRT::FWDTFORM);
        res.m_lab = res.m_point2 - res.m_point1;
    } else {
        res.m_point1 = this->Apply(point1, abRT::BCKTFORM);
        res.m_point2 = this->Apply(point2, abRT::BCKTFORM);
        res.m_lab = res.m_point2 - res.m_point1;
    }
    return res;
};

abVector<double> abRT::GTForm::Apply(const abVector<double>& inputVector, bool dirFlag) {
    std::vector<double> tempdata = {inputVector.GetElement(0), inputVector.GetElement(1), inputVector.GetElement(2), 1.0};
    abVector<double> tempVector {tempdata};
    abVector<double> resultVector;
    if(dirFlag) {
        resultVector = m_fwdtfm * tempVector;
    } else {
        resultVector = m_bcktfm * tempVector;
    }

    tempdata = {resultVector.GetElement(0), resultVector.GetElement(1), resultVector.GetElement(2)};

    abVector<double> outputVector {tempdata};

    return outputVector;
};

namespace abRT {
    abRT::GTForm operator*(const abRT::GTForm &lhs, const abRT::GTForm &rhs) {
        Matrix2<double> fwdResult = lhs.m_fwdtfm * rhs.m_fwdtfm;
		
		// Compute the backward transform as the inverse of the forward transform.
		Matrix2<double> bckResult = fwdResult;
		bckResult.invertMatrix();
		
		// Form the final result.
		abRT::GTForm finalResult (fwdResult, bckResult);
		
		return finalResult;
    };
}


abRT::GTForm abRT::GTForm::operator=(const abRT::GTForm &rhs) {
    if (this != &rhs)
	{
		m_fwdtfm = rhs.m_fwdtfm;
		m_bcktfm = rhs.m_bcktfm;
	}
	
	return *this;
};

void abRT::GTForm::PrintMatrix(bool dirFlag) {
    if (dirFlag)
	{
		Print(m_fwdtfm);
	}
	else
	{
		Print(m_bcktfm);
	}
};

void abRT::GTForm::PrintVector(const abVector<double> &inputVector) {
    int nRows = inputVector.GetNumDims();
	for (int row = 0; row < nRows; ++row)
	{
		std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
	}
};

void abRT::GTForm::Print(const Matrix2<double> &matrix)
{
	int nRows = matrix.GetNumRows();
	int nCols = matrix.GetNumCols();
	for (int row = 0; row<nRows; ++row)
	{
		for (int col = 0; col<nCols; ++col)
		{
			std::cout << std::fixed << std::setprecision(3) << matrix.GetElement(row, col) << " ";
		}
		std::cout << std::endl;
	}
}




