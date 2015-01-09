#pragma once
#include "core/uutDefine.h"
#include <vector>
#include <algorithm>

namespace uut
{
	template<class T>
	class UUT_API List
	{
	public:
		List() {}
		List(const T* data, int count) : _data(data, data + count) {}

		void Add(const T& item);

		void AddRange(const T* data, int count);

		int Count() const { return (int)_data.size(); }

		bool Empty() const { return _data.empty(); }
		void Clear() { _data.clear();}

		bool Equals(const List<T>& list) const { return std::equal(_data.begin(), _data.end(), list._data.begin()); }

		int Find(const T& item, int pos = 0) const;
		int FindLast(const T& item, int pos = 0) const;
		int Replace(const T& from, const T& to);

		List<T> Copy(int pos, int count = -1) const;

		T* GetData() { return _data.data(); }
		const T* GetData() const { return _data.data(); }

		T& operator[] (int index) { return _data[index]; }
		const T& operator[] (int index) const { return _data[index]; }

		static const int NPOS;
		static const List<T> EMPTY;

	protected:
		std::vector<T> _data;
	};

	//////////////////////////////////////////////////////////////////////////
	template<class T> const int List<T>::NPOS = -1;
	template<class T> const List<T> List<T>::EMPTY;

	template<class T>
	void List<T>::Add(const T& item)
	{
		_data.push_back(item);
	}

	template<class T>
	void List<T>::AddRange(const T* data, int count)
	{
		_data.insert(_data.begin(), data, data + count);
	}

	template<class T>
	int List<T>::Find(const T& item, int pos /*= 0*/) const
	{
		auto it = std::find(_data.begin() + pos, _data.end(), item);
		if (it == _data.end())
			return NPOS;

		return std::distance(_data.begin(), it);
	}

	template<class T>
	int uut::List<T>::FindLast(const T& item, int pos /*= 0*/) const
	{
		auto it = std::find(_data.rbegin() + pos, _data.rend(), item);
		if (it == _data.rend())
			return NPOS;

		return std::distance(_data.rbegin(), it);
	}

	template<class T>
	int List<T>::Replace(const T& from, const T& to)
	{
		std::replace(_data.begin(), _data.end(), from, to);
	}	

	template<class T>
	List<T> List<T>::Copy(int pos, int count /*= -1*/) const
	{
		count = Math::Min(count < 0 ? Count() : count, );

		List<T> list(count);
		std::copy(_data.begin() + pos, _data.begin() + pos + count, list._data.begin);
		return list;
	}

}