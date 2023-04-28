#pragma once
#include <string>
#include <vector>

#include "Block.h"

namespace aze
{
	class SceneParser final
	{
	public:
		SceneParser(const std::wstring& inputFile = L"minecraftscene.json");

		void WriteObj(const std::wstring& outputFile = L"minecraftscene.obj");
		std::vector<Block>& GetBlocks() const;

	private:
		std::wstring m_InputFile{};
		std::vector<Block> m_Blocks{};
	};
}