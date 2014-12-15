#pragma once
#include "core/uutDefine.h"

namespace uut
{
	template<class T, int MaxCount>
	class UUT_API Array
	{
	public:

		int Count() const { return MaxCount; }

		T& operator[] (int index) { return _data[index]; }
		const T& operator[] (int index) const { return _data[index]; }

		T* GetData() { return _data; }
		const T* GetData() const { return _data; }

	private:
		T _data[MaxCount];
	};
}