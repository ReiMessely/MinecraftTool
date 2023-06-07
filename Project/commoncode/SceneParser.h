#pragma once
#include <string>
#include <vector>

#include "Block.h"

namespace aze
{
	class SceneParser final
	{
	public:
		SceneParser() = default;

		bool ReadJson(const std::wstring& inputFile = L"minecraftscene.json");
		bool WriteObj(const std::wstring& outputFile = L"minecraftscene.obj");
		std::vector<Block>& GetBlocks();

	private:
		void WriteBlock(FILE* pOFile, const Block& block, int startIdx);

		std::wstring m_InputFile{};
		std::vector<Block> m_Blocks{};
	};
}