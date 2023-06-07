#pragma once
#include <fstream>
#include <codecvt>

namespace aze
{
	bool file_exists(const std::wstring& name) 
	{
		std::ifstream f(name.c_str());
		return f.good();
	}

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> g_ConverterUtf8Utf16;
}