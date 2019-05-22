// Copyright 2019 govyadkin <mgovyadkin@gmail.com>

#ifndef INCLUDE_POLYNOMIAL_HPP_
#define INCLUDE_POLYNOMIAL_HPP_

#include <algorithm>
#include <cstddef>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

template <typename T>
class Polinom
{
    std::vector<T> Data;
public:
    Polinom() {}

    explicit Polinom(const size_t& a)
    {
        Data.resize(a);
    }

    explicit Polinom(const std::vector<T>& v)
    {
        auto v2 = v;
        std::reverse(v2.begin(), v2.end());
        Data = v2;
        this->Cleaner();
    }

    Polinom(const Polinom<T>& pol)
    {
        Data = pol.Data;
    }

    size_t Degree() const
    {
        return (Data.size() - 1);
    }

    Polinom<T>& operator=(const Polinom<T>& pol)
    {
        Data = pol.Data;
        this->Cleaner();
        return *this;
    }

    Polinom<T>& operator+=(const Polinom<T>& pol)
    {
        this->Cleaner();
        if ((pol.Data).size() != 0)
        {
            Data.resize(std::max(this->Degree(), pol.Degree()) + 1);
            for (size_t i = 0; i <= pol.Degree(); ++i)
                Data[i] += pol[i];
        }
        this->Cleaner();
        return *this;
    }

    Polinom<T>& operator-=(const Polinom<T>& pol)
    {
        this->Cleaner();
        if ((pol.Data).size() != 0)
        {
            Data.resize(std::max(this->Degree(), pol.Degree()) + 1);
            for (size_t i = 0; i <= pol.Degree(); ++i)
                Data[i] -= pol[i];
        }
        this->Cleaner();
        return *this;
    }

    Polinom<T>& operator*=(const Polinom<T>& pol)
    {
        this->Cleaner();
        if ((pol.Data).size() != 0)
        {
            std::vector<T> pou(this->Degree() + pol.Degree() + 1);
            for (size_t i = 0; i <= pol.Degree(); ++i)
                for (size_t j = 0; j <= this->Degree(); ++j)
                    pou[i + j] += pol.Data[i] * Data[j];
            Data = pou;
        }else {
            *this *= 0;
        }
        this->Cleaner();
        return *this;
    }

    Polinom<T>& operator/=(const Polinom<T>& pol)
    {
        this->Cleaner();
        size_t a = this->Degree();
        size_t b = pol.Degree();
        std::vector<T> pou(a - b + 1);
        while (Data.size() >= (b + 1))
        {
            size_t i = this->Degree() - b;
            pou[i] = Data[this->Degree()] / pol.Data[b];
            Polinom<T> vec(i + 1);
            vec[i] = pou[i];
            *this -= pol * vec;
            if (this->Degree() == a)
                Data.pop_back();
            a = this->Degree();
        }
        Data = pou;
        this->Cleaner();
        return *this;
    }

    Polinom<T>& operator%=(const Polinom<T>& pol)
    {
        *this -= pol * (*this / pol);
        return *this;
    }

    Polinom<T>& operator*=(const T a)
    {
        for (size_t i = 0; i <= this->Degree(); ++i)
            Data[i] *= a;
        this->Cleaner();
        return *this;
    }

    T operator[](size_t index) const
    {
        return Data[index];
    }

    T& operator[](size_t index)
    {
        return Data[index];
    }

    T Count(T x) const
    {
        T count = 0;
        for (size_t i = 0; i <= this->Degree(); ++i)
            count += Data[i] * pow(x, i);
        return count;
    }

    bool operator==(const Polinom<T>& pol) const
    {
        if (Data.size() == (pol.Data).size())
        {
            if (Data.size() != 0 && (pol.Data).size() != 0)
            {
                for (size_t i = 0; i <= pol.Degree(); ++i)
                {
                    if (Data[i] != pol.Data[i])
                        return false;
                }
            }
            return true;
        }
        return false;
    }

    void Cleaner()
    {
        Data.resize(std::distance(
            std::find_if(Data.rbegin(), Data.rend(),
                            [](T& a) {return a != 0.; }),
            Data.rend()));
    }
};

template <typename T>
Polinom<T> operator+(const Polinom<T>& pol, const Polinom<T>& nogo)
{
    Polinom<T> a = pol;
    a += nogo;
    return a;
}

template <typename T>
Polinom<T> operator-(const Polinom<T>& pol, const Polinom<T>& nogo)
{
    Polinom<T> a = pol;
    a -= nogo;
    return a;
}

template <typename T>
Polinom<T> operator*(const Polinom<T>& pol, const Polinom<T>& nogo)
{
    Polinom<T> a = pol;
    a *= nogo;
    return a;
}

template <typename T>
Polinom<T> operator/(const Polinom<T>& pol, const Polinom<T>& nogo)
{
    Polinom<T> a = pol;
    a /= nogo;
    return a;
}

template <typename T>
Polinom<T> operator%(const Polinom<T>& pol, const Polinom<T>& nogo)
{
    Polinom<T> a = pol;
    a %= nogo;
    return a;
}

template <typename T>
Polinom<T> operator*(const T a, const Polinom<T>& pol)
{
    Polinom<T> g = pol;
    g *= a;
    return g;
}

template <typename T>
Polinom<T> operator*(const Polinom<T>& pol, const T a)
{
    Polinom<T> g = pol;
    g *= a;
    return g;
}

#endif // INCLUDE_POLYNOMIAL_HPP_
