#pragma once
#include "container/uutString.h"
#include "container/uutHashString.h"

namespace uut
{
	class UUT_API Path
	{
	public:
		static String Combine(const String& path1, const String& path2);
		static String GetDirectoryName(const String& path);
		static String GetExtension(const String& path);
		static String GetFileName(const String& path);
		static String GetFileNameWithoutExtension(const String& path);
		static bool HasExtension(const String& path);

	protected:
		static String PreparePath(const String& path);
	};
}