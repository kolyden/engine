#pragma once
#include "core/uutDefine.h"
#include <map>

namespace uut
{
	template<class TKey, class TValue>
	class Dictionary
	{
	public:
		Dictionary() {}

		void Add(const TKey& key, const TValue& data)
		{
			_data[key] = data;
		}

		int Count() const { return (int)_data.size(); }

		bool Contains(const TKey& key) const
		{
			DataType::const_iterator it = _data.find(key);
			return it != _data.end();
		}

		bool TryGetValue(const TKey& key, TValue* data) const
		{
			DataType::const_iterator it = _data.find(key);
			if (it == _data.end())
				return false;

			*data = it->second;
			return true;
		}

	protected:
		typedef std::map<TKey, TValue> DataType;

		DataType _data;
	};
}