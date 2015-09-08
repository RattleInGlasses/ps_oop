#pragma once
#include "stdafx.h"

template <typename T>
class CMySet
{
public:
	CMySet() {};
	CMySet(std::initializer_list<T>);

	size_t GetSize()const;
	void Add(T const &value);

	bool IsEmpty()const;
	bool Contains(T const &value)const;
	bool ContainsSubset(CMySet<T> const &subSet)const;
	bool operator ==(CMySet<T> const &set2)const;
	T operator [](size_t index)const;

	void Unite(CMySet<T> const &set2);
	void Intersect(CMySet<T> const &set2);
	void Difference(CMySet<T> const &set2);
	void SymmetricDyfference(CMySet<T> set2);
public:
	std::vector<T> m_data;
};


template <typename T>
CMySet<T>::CMySet(std::initializer_list<T> il) :
m_data(il)
{
}


template <typename T>
size_t CMySet<T>::GetSize() const
{
	return m_data.size();
}


template <typename T>
void CMySet<T>::Add(T const &value)
{
	if (!this->Contains(value))
	{
		m_data.push_back(value);
	}
}


template <typename T>
bool CMySet<T>::IsEmpty() const
{
	return m_data.size() == 0;
}


template <typename T>
bool CMySet<T>::Contains(T const &value) const
{
	return std::find(m_data.begin(), m_data.end(), value) != m_data.end();
}


template <typename T>
bool CMySet<T>::ContainsSubset(CMySet<T> const &subSet) const
{
	for (auto el : subSet.m_data)
	{
		if (!Contains(el))
		{
			return false;
		}
	}
	return true;
}


template <typename T>
bool CMySet<T>::operator ==(CMySet<T> const &set2) const
{
	if (m_data.size() != set2.m_data.size())
	{
		return false;
	}

	for (auto el : m_data)
	{
		if (!set2.Contains(el))
		{
			return false;
		}
	}
	return true;
}


template <typename T>
T CMySet<T>::operator [](size_t index) const
{
	if (index >= GetSize())
	{
		throw range_error("set index out of range");
	}
	return m_data[index];
}


template <typename T>
void CMySet<T>::Unite(CMySet<T> const &set2)
{
	std::vector<T> result;
	copy(m_data.begin(), m_data.end(), back_inserter(result));
	copy_if(set2.m_data.begin(), set2.m_data.end(), back_inserter(result), [this](T const &el){ return !Contains(el); });

	m_data = move(result);
}


template <typename T>
void CMySet<T>::Intersect(CMySet<T> const &set2)
{
	std::vector<T> result;
	copy_if(m_data.begin(), m_data.end(), back_inserter(result), [this, &set2](T const &el){ return ((Contains(el)) && (set2.Contains(el))); });

	m_data = move(result);
}


template <typename T>
void CMySet<T>::Difference(CMySet<T> const &set2)
{
	std::vector<T> result;
	copy_if(m_data.begin(), m_data.end(), back_inserter(result), [this, &set2](T const &el){ return ((Contains(el)) && (!set2.Contains(el))); });

	m_data = move(result);
}


template <typename T>
void CMySet<T>::SymmetricDyfference(CMySet<T> set2)
{
	CMySet<T> resultSet;
	copy(m_data.begin(), m_data.end(), back_inserter(resultSet.m_data));

	resultSet.Difference(set2);
	set2.Difference(*this);
	resultSet.Unite(set2);

	m_data = move(resultSet.m_data);
}