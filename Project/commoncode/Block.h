#pragma once
#include "Vector3.h"

namespace aze
{
	struct Block final
	{
		Vector3 pos{};
		std::wstring type{};
		bool isOpaque{ false };
	};
}