// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <vector>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
	size_t sz;
	T* pMem = nullptr;
public:
	TDynamicVector(size_t size = 1) : sz(size)
	{
		if (sz == 0)
			throw out_of_range("Vector size must be greater than zero");
		if (sz <0 || sz>MAX_VECTOR_SIZE)
			throw 0;
		pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
	}
	TDynamicVector(T* arr, size_t s) : sz(s)
	{
		assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
		pMem = new T[sz];
		std::copy(arr, arr + sz, pMem);
	}
	TDynamicVector(std::vector<T> arr) :sz(arr.size())
	{
		pMem = new T[sz];
		for (int i = 0; i < sz; i++)
			pMem[i] = arr[i];
	}
	TDynamicVector(const TDynamicVector& v) : sz(v.sz)
	{
		pMem = new T[sz];
		for (int i = 0; i < sz; i++)
			pMem[i] = v.pMem[i];
	}
	TDynamicVector(TDynamicVector&& v) noexcept
	{
		pMem = nullptr;
		sz = 0;
		swap(*this, v);
	}
	~TDynamicVector()
	{
		delete[] pMem;
	}
	TDynamicVector& operator=(const TDynamicVector& v)
	{
		if (this == &v)
			return *this;
		if (sz != v.sz)
		{
			sz = v.sz;
			delete[] pMem;
			pMem = new T[sz];
		}
		std::copy(v.pMem, v.pMem + sz, pMem);
		return *this;
	}
	TDynamicVector& operator=(TDynamicVector&& v) noexcept
	{
		swap(*this, v);
		v.pMem = nullptr;
		v.sz = 0;
		return *this;
	}

	size_t size() const noexcept { return sz; }

	// индексация
	T& operator[](size_t ind)
	{
		return pMem[ind];
	}
	const T& operator[](size_t ind) const
	{
		return pMem[ind];
	}
	// индексация с контролем
	T& at(size_t ind)
	{
		if (ind >= sz)
			throw 0;
		else
			return pMem[ind];
	}
	const T& at(size_t ind) const
	{
		if (ind >= sz)
			throw 0;
		else
			return pMem[ind];
	}

	// сравнение
	bool operator==(const TDynamicVector& v) const noexcept
	{
		if (sz != v.sz) 
			return false;
		for (int i = 0; i < sz; i++)
		{
			if (pMem[i] != v.pMem[i])
				return false;
		}
		return true;
	}
	bool operator!=(const TDynamicVector& v) const noexcept
	{
		return !(*this == v);
	}

	// скалярные операции
	TDynamicVector operator+(T val)
	{
		TDynamicVector res(sz);

		for (int i = 0; i < sz; i++)
			res.pMem[i] = pMem[i] + val;
		return res;
	}
	TDynamicVector operator-(double val)
	{
		TDynamicVector res(sz);
		for (int i = 0; i < sz; i++)
			res.pMem[i] = pMem[i] - val;
		return res;
	}
	TDynamicVector operator*(double val)
	{
		TDynamicVector res(sz);
		for (int i = 0; i < sz; i++)
			res.pMem[i] = pMem[i] * val;
		return res;
	}

	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw 0;
		else
		{
			TDynamicVector<T> res(sz);
			for (int i = 0; i < sz; i++)
				res.pMem[i] = pMem[i] + v.pMem[i];
			return res;
		}

	}
	TDynamicVector operator-(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw 0;
		else
		{
			TDynamicVector res(sz);
			for (int i = 0; i < sz; i++)
				res.pMem[i] = pMem[i] - v.pMem[i];
			return res;
		}
	}
	T operator*(const TDynamicVector& v)
	{
		if (sz != v.sz) 
			throw 0;
		else
		{
			T res = 0;
			for (int i = 0; i < sz; i++)
				res += (pMem[i] * v.pMem[i]);
			return res;
		}
	}

	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			istr >> v.pMem[i]; // требуется оператор>> для типа T
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
		return ostr;
	}
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::sz;
public:
	TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
	{
		if (s > MAX_MATRIX_SIZE)
			throw 0;
		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz);
	}
	TDynamicMatrix(size_t s, size_t m) : TDynamicVector<TDynamicVector<T>>(s)
	{
		if (s<0 || s>MAX_MATRIX_SIZE)
			throw 0;
		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(m);
	}
	TDynamicMatrix(const TDynamicMatrix& m) :TDynamicVector<TDynamicVector<T>>(m.sz)
	{
		for (int i = 0; i < sz; i++)
			pMem[i] = m.pMem[i];
	}
	TDynamicMatrix(std::vector<vector<T>> v) :TDynamicVector<TDynamicVector<T>>(v.size())
	{
		for (size_t i = 0; i < sz; i++)
			pMem[i] = v[i];

	}

	using TDynamicVector<TDynamicVector<T>>::operator[];
	using TDynamicVector<TDynamicVector<T>>::size;
	using TDynamicVector<TDynamicVector<T>>::at;

	TDynamicMatrix(TDynamicMatrix&& m) noexcept
	{
		sz = m.sz;
		pMem = m.pMem;
		m.sz = 0;
		m.pMem = nullptr;
	}

	TDynamicMatrix& operator=(const TDynamicMatrix& m)
	{
		if (this == &m)
			return *this;
		if (sz != m.sz)
		{
			sz = m.sz;
			delete[] pMem;
			pMem = new TDynamicVector<T>[m.sz];
		}
		std::copy(m.pMem, m.pMem + sz, pMem);
		return *this;
	}
	TDynamicMatrix& operator=(TDynamicMatrix&& m) noexcept
	{
		if (this != &m)
		{
			pMem = m.pMem;
			m.pMem = nullptr;
			sz = m.sz;
			m.sz = 0;
		}
		return *this;
	}
	// сравнение
	bool operator==(const TDynamicMatrix& m) const noexcept
	{
		return TDynamicVector<TDynamicVector<T>>::operator==(m);
	}
	bool operator!=(const TDynamicMatrix& m) const noexcept
	{
		return !(*this == m);
	}

	// матрично-скалярные операции
	TDynamicMatrix operator*(const T& val)
	{
		TDynamicMatrix res(sz);
		for (int i = 0; i < sz; i++)
			res.pMem[i] = pMem[i] * val;
		return res;
	}

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v)
	{
		if (sz != v.size())
			throw 0;

		TDynamicVector<T> res(sz);

		for (int i = 0; i < sz; i++)
		{
			res[i] = 0;
			for (int j = 0; j < pMem[i].size(); j++)
				res[i] += pMem[i][j] * v[j];
		}
		return res;
	}

	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m)
	{
		if (sz != m.sz)
			throw 0;

		TDynamicMatrix<T> res(sz);
		for (int i = 0; i < sz; i++)
			res.pMem[i] = pMem[i] + m.pMem[i];
		return res;
	}
	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		if (sz != m.sz)
			throw 0;

		TDynamicMatrix<T> res(sz);
		for (int i = 0; i < sz; i++)
			res.pMem[i] = pMem[i] - m.pMem[i];
		return res;
	}
	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
		if (pMem[0].size() != m.sz)
			throw 0;
		TDynamicMatrix m2(sz, m.pMem[0].size());
		for (int i = 0; i < sz; i++)
		{
			for (int j = 0; j < m.pMem[i].size(); j++)
			{
				m2[i][j] = 0;
				for (int k = 0; k < sz; k++)
					m2[i][j] += pMem[i][k] * m.pMem[k][j];
			}
		}
		return m2;
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicMatrix& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			istr >> v.pMem[i];
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			ostr << v.pMem[i] << std::endl;
		return ostr;
	}
};

#endif