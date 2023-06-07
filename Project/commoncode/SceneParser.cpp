#include "SceneParser.h"

#include <codecvt>
#include <sstream>

//#include <rapidjson/rapidjson.h>
//#include <rapidjson/document.h>
//#include <rapidjson/stream.h>
//#include <rapidjson/istreamwrapper.h>
//#include <rapidjson/filereadstream.h>

#include "Utils.h"

using namespace aze;

bool aze::SceneParser::ReadJson(const std::wstring& inputFile)
{
	if (!aze::file_exists(inputFile))
	{
		printf("inputfile: '");
		wprintf(inputFile.c_str());
		printf("' does not exist.");
		return false;
	}

	/*if (std::ifstream is{ inputFile })
	{
		using namespace rapidjson;
		IStreamWrapper ism{ is };
		Document sceneDoc;
		sceneDoc.ParseStream(ism);

		if (sceneDoc.IsArray())
		{
			for (Value::ConstValueIterator it{ sceneDoc.Begin() }; it != sceneDoc.End(); ++it)
			{
				aze::Block block{};
				const Value& blockJson{ *it };

				if (blockJson.HasMember("opaque"))
				{
					const Value& isOpaque{ blockJson["opaque"] };
					if (isOpaque.IsBool()) block.isOpaque = isOpaque.GetBool();
				}
				if (blockJson.HasMember("layer"))
				{
					const Value& blockType{ blockJson["layer"] };
					if (blockType.IsString()) block.type = g_ConverterUtf8Utf16.from_bytes(blockType.GetString());
				}

				if (blockJson.HasMember("positions"))
				{
					const Value& positions{ blockJson["positions"] };
					if (positions.IsArray())
					{
						for (Value::ConstValueIterator posIt{ positions.Begin() }; posIt != positions.End(); ++posIt)
						{
							const Value& position{ *posIt };

							if (position.IsArray() && position.Size() == 3)
							{
								const Value& x{ position[1] };
								const Value& y{ position[2] };
								const Value& z{ position[0] };

								if (x.IsInt() && y.IsInt() && z.IsInt())
								{
									block.pos = aze::Vector3{ x.GetInt(),y.GetInt(),z.GetInt(), };
									m_Blocks.push_back(block);
								}
							}
						}
					}
				}
			}
		}
		return true;
	}*/
	return false;
}

bool aze::SceneParser::WriteObj(const std::wstring& outputFile)
{
	FILE* pOFile = nullptr;
	_wfopen_s(&pOFile, outputFile.c_str(), L"w+,ccs=UTF-8");
	if (pOFile != nullptr) {
		// it was possible to create the file for writing.
		const wchar_t* text = L"#∂ is the symbol for partial derivative.\n";
		fwrite(text, wcslen(text) * sizeof(wchar_t), 1, pOFile);

		fwprintf_s(pOFile, L"mtllib minecraftMats.mtl\n");

		// Vertex normals
		fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", 0.0f, 0.0f, 1.0f);
		fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", 0.0f, 0.0f, -1.0f);
		fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", 0.0f, 1.0f, 0.0f);
		fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", 0.0f, -1.0f, 0.0f);
		fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", 1.0f, 0.0f, 0.0f);
		fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", -1.0f, 0.0f, 0.0f);

		constexpr int amountOfIndices = 8;
		int idx = 0;
		for (const auto& block : m_Blocks)
		{
			std::wstringstream materialStr{};
			materialStr << L"usemtl " << block.type << "\n";
			fwprintf_s(pOFile, materialStr.str().c_str());
			WriteBlock(pOFile, block, idx);
			idx += amountOfIndices;
		}

		fclose(pOFile);
		return true;
	}
	return false;
}

std::vector<aze::Block>& aze::SceneParser::GetBlocks()
{
	return m_Blocks;
}

void aze::SceneParser::WriteBlock(FILE* pOFile, const Block& block, int startIdx)
{
	// Vertices
	fwprintf_s(pOFile, L"v %.4f %.4f %.4f\n", block.pos.x - 0.5f, block.pos.y - 0.5f, block.pos.z - 0.5f);
	fwprintf_s(pOFile, L"v %.4f %.4f %.4f\n", block.pos.x - 0.5f, block.pos.y - 0.5f, block.pos.z + 0.5f);
	fwprintf_s(pOFile, L"v %.4f %.4f %.4f\n", block.pos.x - 0.5f, block.pos.y + 0.5f, block.pos.z - 0.5f);
	fwprintf_s(pOFile, L"v %.4f %.4f %.4f\n", block.pos.x - 0.5f, block.pos.y + 0.5f, block.pos.z + 0.5f);
	fwprintf_s(pOFile, L"v %.4f %.4f %.4f\n", block.pos.x + 0.5f, block.pos.y - 0.5f, block.pos.z - 0.5f);
	fwprintf_s(pOFile, L"v %.4f %.4f %.4f\n", block.pos.x + 0.5f, block.pos.y - 0.5f, block.pos.z + 0.5f);
	fwprintf_s(pOFile, L"v %.4f %.4f %.4f\n", block.pos.x + 0.5f, block.pos.y + 0.5f, block.pos.z - 0.5f);
	fwprintf_s(pOFile, L"v %.4f %.4f %.4f\n", block.pos.x + 0.5f, block.pos.y + 0.5f, block.pos.z + 0.5f);

	// UV coords
	fwprintf_s(pOFile, L"vt %.4f %.4f\n", 0.f, 0.f); // A = G
	fwprintf_s(pOFile, L"vt %.4f %.4f\n", 1.f, 0.f); // B = H
	fwprintf_s(pOFile, L"vt %.4f %.4f\n", 0.f, 1.f); // C = E
	fwprintf_s(pOFile, L"vt %.4f %.4f\n", 1.f, 1.f); // D = F

	fwprintf_s(pOFile, L"vt %.4f %.4f\n", 0.f, 1.f); // E
	fwprintf_s(pOFile, L"vt %.4f %.4f\n", 1.f, 1.f); // F
	fwprintf_s(pOFile, L"vt %.4f %.4f\n", 0.f, 0.f); // G
	fwprintf_s(pOFile, L"vt %.4f %.4f\n", 1.f, 0.f); // H

	// Faces
	// 
	// Face/TexCoord/Normal
	fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", startIdx + 1, startIdx + 1, 2, startIdx + 7, startIdx + 7, 2, startIdx + 5, startIdx + 5, 2);
	fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", startIdx + 1, startIdx + 1, 2, startIdx + 3, startIdx + 3, 2, startIdx + 7, startIdx + 7, 2);

	fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", startIdx + 1, startIdx + 1, 6, startIdx + 4, startIdx + 4, 6, startIdx + 3, startIdx + 3, 6);
	fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", startIdx + 1, startIdx + 1, 6, startIdx + 2, startIdx + 2, 6, startIdx + 4, startIdx + 4, 6);

	fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", startIdx + 3, startIdx + 3, 3, startIdx + 8, startIdx + 8, 3, startIdx + 7, startIdx + 7, 3);
	fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", startIdx + 3, startIdx + 3, 3, startIdx + 4, startIdx + 4, 3, startIdx + 8, startIdx + 8, 3);

	fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", startIdx + 5, startIdx + 5, 5, startIdx + 7, startIdx + 7, 5, startIdx + 8, startIdx + 8, 5);
	fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", startIdx + 5, startIdx + 5, 5, startIdx + 8, startIdx + 8, 5, startIdx + 6, startIdx + 6, 5);

	fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", startIdx + 1, startIdx + 1, 4, startIdx + 5, startIdx + 5, 4, startIdx + 6, startIdx + 6, 4);
	fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", startIdx + 1, startIdx + 1, 4, startIdx + 6, startIdx + 6, 4, startIdx + 2, startIdx + 2, 4);

	fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", startIdx + 2, startIdx + 2, 1, startIdx + 6, startIdx + 6, 1, startIdx + 8, startIdx + 8, 1);
	fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", startIdx + 2, startIdx + 2, 1, startIdx + 8, startIdx + 8, 1, startIdx + 4, startIdx + 4, 1);
}