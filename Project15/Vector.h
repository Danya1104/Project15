#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;

// Динамический вектор - 
 //шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
public:
    size_t sz;
public:
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz < 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE) {
            throw "cant_create_too_large_vector";
        }
        pMem = new T[sz](); {};  У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        if (v.pMem == nullptr) {
            sz = 0;
            pMem = nullptr;
        }
        else {
            sz = v.sz;
            pMem = new T[sz];
            std::copy(v.pMem, v.pMem + sz, pMem);
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        sz = v.sz;
        pMem = v.pMem;

        v.sz = 0;
        v.pMem = nullptr;
    }
    ~TDynamicVector()
    {
        if (pMem != nullptr) {
            delete[] pMem;
            sz = 0;
        }
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this != &v) {
            if (pMem != nullptr) {
                delete[] pMem;
            }
            if (v.pMem == nullptr) {
                sz = 0;
                pMem = nullptr;
            }
            else {

                sz = v.sz;
                pMem = new T[sz];
                std::copy(v.pMem, v.pMem + sz, pMem);
            }
        }
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v) {
            if (pMem != nullptr) {
                delete[] pMem;
            }
            sz = v.sz;
            pMem = v.pMem;
            v.sz = 0;
            v.pMem = nullptr;
        }
        return *this;

    }

    size_t size() const noexcept {
        return sz;
    }

     //индексация
    T& operator[](int ind)
    {
        return this->pMem[ind];
    }

     //индексация с контролем
    T& at(size_t ind)
    {
        if (pMem == nullptr) {
            throw "error 0";
        }
        if (ind < 0 || ind >= sz) {
            throw "error";
        }
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        {
            if (pMem == nullptr) {
                throw "Error";
            }
            if (ind < 0 || ind >= sz) {
                throw "Error";
            }
            return pMem[ind];
        }
    }

     //сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) {
            return false;
        }
        for (int i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        {
            if (sz != v.sz) {
                return true;
            }
            for (int i = 0; i < sz; i++) {
                if (pMem[i] != v.pMem[i]) {
                    return true;
                }
            }
            return false;
        }
    }

     //скалярные операции
    TDynamicVector operator+(T val)
    {
        for (int i = 0; i < sz; i++) {
            pMem[i] += val;
        }
        return *this;
    }
    TDynamicVector operator-(T val)
    {
        for (int i = 0; i < sz; i++) {
            pMem[i] -= val;
        }
        return *this;
    }
    TDynamicVector operator*(T val)
    {
        for (int i = 0; i < sz; i++) {
            pMem[i] *= val;
        }
        return *this;
    }

     //векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw "sizes of Vectors are different";
        }
        else {
            TDynamicVector tmp(sz);
            for (int i = 0; i < sz; i++) {
                tmp[i] = pMem[i] + v.pMem[i];
            }
            return tmp;
        }
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw "sizes of Vectors are different";
        }
        else {
            TDynamicVector tmp(sz);
            for (int i = 0; i < sz; i++) {
                tmp[i] = pMem[i] - v.pMem[i];
            }
            return tmp;
        }
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz != v.sz) {
            throw "sizes of Vectors are different";
        }
        else {
            T sum = 0;
            for (int i = 0; i < sz; i++) {
                sum = sum + pMem[i] * v.pMem[i];
            }
            return sum;
        }
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

     //ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i];  требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' ';  требуется оператор<< для типа T
        return ostr;
    }
};