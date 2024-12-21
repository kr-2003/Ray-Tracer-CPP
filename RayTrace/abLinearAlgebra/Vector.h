#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <vector>

template<class T>
class abVector{
    public:
        abVector();
        abVector(std::vector<T>& inputData);
        abVector(int numdims);
        ~abVector();

        int GetNumDims() const;

        T GetElement(int ind) const;
        bool SetElement(int ind, const T& val);

        T Norm() const;

        abVector<T> Normalized() const;

        abVector<T> operator+ (const abVector<T>& rhs);
        abVector<T> operator- (const abVector<T>& rhs);
        abVector<T> operator* (const T& rhs);

        template<class U>
        friend abVector<U> operator* (const U& lhs, const abVector<U>& rhs);

        template<class U> 
        friend std::ostream& operator<< (std::ostream& os, const abVector<U>& v);

        static T dot(const abVector<T>& a, const abVector<T>& b);
        static abVector<T> cross(const abVector<T>& a, const abVector<T>& b);

    private:
        std::vector<T> m_vectorData;
        int m_nDims;
};


template<class T>
abVector<T>::abVector() {
    m_nDims = 0;
    m_vectorData = std::vector<T>();
}

template<class T>
abVector<T>::abVector(std::vector<T>& inputData) {
    m_nDims = inputData.size();
    m_vectorData = inputData;
}

template<class T>
abVector<T>::abVector(int numdims) {
    m_nDims = numdims;
    m_vectorData = std::vector<T>(m_nDims, 0);
}

template<class T>
abVector<T>::~abVector() {
    // nothing, since vector(STL) class takes care of it
}

template<class T>
int abVector<T>::GetNumDims() const {
    return m_nDims;
}

template<class T>
T abVector<T>::GetElement(int ind) const {
    if(ind >= m_nDims) {
        throw std::invalid_argument("Index is out of range.");
    } else {
        return m_vectorData[ind];
    }
}

template<class T>
bool abVector<T>::SetElement(int ind, const T& val) {
    if(ind >= m_nDims) {
        throw std::invalid_argument("Index is out of range.");
    } else {
        m_vectorData[ind] = val;
        return true;
    }
}

template<class T>
T abVector<T>::Norm() const {
    int n = GetNumDims();
    T ans = 0;
    for(int i = 0; i < n; i++) {
        T x =  GetElement(i);
        ans += x * x;
    }
    ans = sqrt(ans);
    return ans;
}

template<class T>
abVector<T> abVector<T>::Normalized() const {
    T norm = Norm();
    int n = GetNumDims();
    std::vector<T> inputData;
    for(int i = 0; i < n; i++) {
        inputData.push_back(GetElement(i) / norm);
    }
    abVector<T> res(inputData);
    return res;
}


template<class T>
abVector<T> abVector<T>::operator+ (const abVector<T>& rhs) {
    if(GetNumDims() != rhs.GetNumDims()) {
        throw std::invalid_argument("Dimensions of lhs and rhs should be equal for addition.");
    } else {
        int n = rhs.GetNumDims();
        std::vector<T> res;
        for(int i = 0; i < n; i++) {
            res.push_back(GetElement(i) + rhs.GetElement(i));
        }

        abVector<T> resultData(res);
        return resultData;
    }
}

template<class T>
abVector<T> abVector<T>::operator- (const abVector<T>& rhs) {
    if(GetNumDims() != rhs.GetNumDims()) {
        throw std::invalid_argument("Dimensions of lhs and rhs should be equal for subtraction.");
    } else {
        int n = rhs.GetNumDims();
        std::vector<T> res;
        for(int i = 0; i < n; i++) {
            res.push_back(GetElement(i) - rhs.GetElement(i));
        }

        abVector<T> resultData(res);
        return resultData;
    }
}

template<class T>
abVector<T> abVector<T>::operator* (const T& rhs) {
    int n = GetNumDims();
    std::vector<T> res;
    for(int i = 0; i < n; i++) {
        res.push_back(GetElement(i) * rhs);
    }

    abVector<T> resultData(res);
    return resultData;
}


template<class T>
abVector<T> operator* (const T& lhs, const abVector<T>& rhs) {
    int n = rhs.GetNumDims();
    std::vector<T> res;
    for(int i = 0; i < n; i++) {
        res.push_back(lhs * rhs.GetElement(i));
    }

    abVector<T> resultData(res);
    return resultData;
}


template<class T>
T abVector<T>::dot(const abVector<T>& a, const abVector<T>& b) {
    if(a.GetNumDims() != b.GetNumDims()) {
        throw std::invalid_argument("Number of dimensions should be equal for dot product.");
    }
    int n = a.GetNumDims();

    T ans = 0.0;

    for(int i = 0; i < n; i++) {
        ans += (a.GetElement(i) * b.GetElement(i));
    }

    return ans;
}

template<class T>
abVector<T> abVector<T>::cross(const abVector<T>& a, const abVector<T>& b) {
    if(a.GetNumDims() != b.GetNumDims()) {
        throw std::invalid_argument("Number of dimensions should be equal for dot product.");
    }

    int n = a.GetNumDims();

    if(n != 3) {
        throw std::invalid_argument("Cross product can only be calculated for 3 dimensions.");
    }

    std::vector<T> inputData(3, 0);
    inputData[0] = a.GetElement(1) * b.GetElement(2) - b.GetElement(1) * a.GetElement(2);
    inputData[1] = a.GetElement(2) * b.GetElement(0) - b.GetElement(2) * a.GetElement(0);
    inputData[2] = a.GetElement(0) * b.GetElement(1) - b.GetElement(0) * a.GetElement(1);

    abVector<T> ans(inputData);

    return ans;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const abVector<T>& v) {
    int n = v.GetNumDims();
    
    os << "Vector (Dimensions = " << n << "):\n";
    for (int i = 0; i < n; ++i) {
        os << v.GetElement(i) << " ";
    }
    os << "\n";
    return os;
}

#endif

