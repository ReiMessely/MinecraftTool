#pragma once
#include <fstream>
#include <codecvt>

namespace aze
{
	static inline bool file_exists(const std::wstring& name) 
	{
		std::ifstream f(name.c_str());
		return f.good();
	}

	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> g_ConverterUtf8Utf16;
}