#pragma once
#include "core/uutDefine.h"
#include "container/uutList.h"
#include "container/uutString.h"

namespace uut
{
	class UUT_API Directory
	{
	public:
		static List<String> GetDirectories(const String& path);
		static List<String> GetFiles(const String& path);
	};
}