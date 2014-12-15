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
		List(const T* data, int count)
		{
			AddRange(data, count);
		}

		void Add(const T& item)
		{
			_data.push_back(item);
		}

		void AddRange(const T* data, int count)
		{
			_data.insert(_data.begin(), data, data + count);
		}

		int Count() const { return (int)_data.size(); }

		bool Empty() const { return _data.empty(); }

		void Clear()
		{
			_data.clear();
		}

		bool Equals(const List<T>& list) const
		{
			return std::equal(_data.begin(), _data.end(), list._data.begin());
		}

		T* GetData() { return _data.data(); }
		const T* GetData() const { return _data.data(); }

		T& operator[] (int index) { return _data[index]; }
		const T& operator[] (int index) const { return _data[index]; }

	protected:
		std::vector<T> _data;
	};
}