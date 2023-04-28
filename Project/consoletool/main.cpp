#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <codecvt>
#include <sstream>

//#include <rapidjson/rapidjson.h>
//#include <rapidjson/document.h>
//#include <rapidjson/stream.h>
//#include <rapidjson/istreamwrapper.h>
//#include <rapidjson/filereadstream.h>
#include "headeronlylib/rapidjson/rapidjson.h"
#include "headeronlylib/rapidjson/document.h"
#include "headeronlylib/rapidjson/stream.h"
#include "headeronlylib/rapidjson/istreamwrapper.h"
#include "headeronlylib/rapidjson/filereadstream.h"

#include "Block.h"

namespace aze
{
	bool file_exists(const std::wstring& name) {
		std::ifstream f(name.c_str());
		return f.good();
	}

	void WriteBlock(FILE* pOFile, const Block& block, int startIdx)
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
		fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", startIdx + 1, startIdx + 1, 2, startIdx + 7, startIdx + 7, 2, startIdx + 5,startIdx + 5, 2);
		fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", startIdx + 1, startIdx + 1, 2, startIdx + 3, startIdx + 3, 2, startIdx + 7,startIdx + 7, 2);

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
}

// Globals
std::vector<aze::Block> g_Blocks;
std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> g_ConverterUtf8Utf16;

int wmain(int argc, wchar_t* argv[], wchar_t* envp[])
{
	std::wstring inputFile{ L"minecraftscene.json" };
	std::wstring outputFile{ L"minecraftscene.obj" };
	if (argc > 1)
	{
		if (argc > 2 && argv[1] == L"-i")
		{
			inputFile = argv[2];
		}
		else if (argc > 2 && argv[1] == L"-o")
		{
			outputFile = argv[2];
		}
		else 
		{
			printf("Invalid argument. -i [inputFile] -o [outputFile] are the only ones supported\n");
			printf("Current arguments:\n");
			for (int i{ 0 }; i < argc; ++i)
			{
				wprintf(argv[i]);
				printf("\n");
			}
			return -1;
		}

		if (argc > 4 && argv[3] == L"-i")
		{
			inputFile = argv[4];
		}
		else if (argc > 4 && argv[3] == L"-o")
		{
			outputFile = argv[4];
		}
		else
		{
			printf("Invalid argument. -i [inputFile] -o [outputFile] are the only ones supported\n");
			printf("Current arguments:\n");
			for (int i{ 0 }; i < argc; ++i)
			{
				wprintf(argv[i]);
				printf("\n");
			}
			return -1;
		}
	}

	if (!aze::file_exists(inputFile))
	{
		printf("inputfile: '");
		wprintf(inputFile.c_str());
		printf("' does not exist.");
		return -1;
	}

	if (std::ifstream is{ inputFile })
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
									block.pos = aze::Vector3{ x.GetInt(),y.GetInt(),z.GetInt(),};
									g_Blocks.push_back(block);
								}
							}
						}
					}
				}
			}
		}
	}

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
		for (const auto& block : g_Blocks)
		{
			/*if (idx > 1) break;*/
			std::wstringstream materialStr{};
			materialStr << L"usemtl " << block.type << "\n";
			fwprintf_s(pOFile, materialStr.str().c_str());
			aze::WriteBlock(pOFile, block, idx);
			idx += amountOfIndices;
		}

		/*fwprintf_s(pOFile, L"v %.4f %.4f %.4f\n", 0.0, 0.0, 0.0f);
		fwprintf_s(pOFile, L"v %.4f %.4f %.4f\n", 0.0, 0.0, 1.0f);
		fwprintf_s(pOFile, L"v %.4f %.4f %.4f\n", 0.0, 1.0, 0.0f);
		fwprintf_s(pOFile, L"v %.4f %.4f %.4f\n", 0.0, 1.0, 1.0f);
		fwprintf_s(pOFile, L"v %.4f %.4f %.4f\n", 1.0, 0.0, 0.0f);
		fwprintf_s(pOFile, L"v %.4f %.4f %.4f\n", 1.0, 0.0, 1.0f);
		fwprintf_s(pOFile, L"v %.4f %.4f %.4f\n", 1.0, 1.0, 0.0f);
		fwprintf_s(pOFile, L"v %.4f %.4f %.4f\n", 1.0, 1.0, 1.0f);

		fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", 0.0f, 0.0f, 1.0f);
		fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", 0.0f, 0.0f, -1.0f);
		fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", 0.0f, 1.0f, 0.0f);
		fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", 0.0f, -1.0f, 0.0f);
		fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", 1.0f, 0.0f, 0.0f);
		fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", -1.0f, 0.0f, 0.0f);

		fwprintf_s(pOFile, L"f %d//%d %d//%d %d//%d\n", 1, 2, 7, 2, 5, 2);
		fwprintf_s(pOFile, L"f %d//%d %d//%d %d//%d\n", 1, 2, 3, 2, 7, 2);

		fwprintf_s(pOFile, L"f %d//%d %d//%d %d//%d\n", 1, 6, 4, 6, 3, 6);
		fwprintf_s(pOFile, L"f %d//%d %d//%d %d//%d\n", 1, 6, 2, 6, 4, 6);

		fwprintf_s(pOFile, L"f %d//%d %d//%d %d//%d\n", 3, 3, 8, 3, 7, 3);
		fwprintf_s(pOFile, L"f %d//%d %d//%d %d//%d\n", 3, 3, 4, 3, 8, 3);

		fwprintf_s(pOFile, L"f %d//%d %d//%d %d//%d\n", 5, 5, 7, 5, 8, 5);
		fwprintf_s(pOFile, L"f %d//%d %d//%d %d//%d\n", 5, 5, 8, 5, 6, 5);

		fwprintf_s(pOFile, L"f %d//%d %d//%d %d//%d\n", 1, 4, 5, 4, 6, 4);
		fwprintf_s(pOFile, L"f %d//%d %d//%d %d//%d\n", 1, 4, 6, 4, 2, 4);

		fwprintf_s(pOFile, L"f %d//%d %d//%d %d//%d\n", 2, 1, 6, 1, 8, 1);
		fwprintf_s(pOFile, L"f %d//%d %d//%d %d//%d\n", 2, 1, 8, 1, 4, 1);*/

		fclose(pOFile);
		ShellExecute(NULL, "open", "explorer.exe", g_ConverterUtf8Utf16.to_bytes(outputFile.c_str()).c_str(), NULL, SW_SHOWDEFAULT);
		return 0;
	}
	else {
		return -1;
	}
}