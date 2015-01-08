#include "uutFile.h"
#include <Shlwapi.h>

namespace uut
{
	bool File::Exist(const String& path)
	{
		return PathFileExistsA(path.GetData());
	}

}