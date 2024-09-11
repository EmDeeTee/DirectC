#include "pch.h"
#include "Util.h"

namespace DirectC {
	std::wstring Util::StringToLPCWSTR(const std::string& input) {
		return std::wstring(input.begin(), input.end());
	}
}
