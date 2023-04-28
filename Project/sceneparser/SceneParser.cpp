#include "SceneParser.h"

using namespace aze;

SceneParser::SceneParser(const std::wstring& inputFile)
	:m_InputFile{inputFile}
{
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
									block.pos = aze::Vector3{ x.GetInt(),y.GetInt(),z.GetInt(), };
									g_Blocks.push_back(block);
								}
							}
						}
					}
				}
			}
		}
	}
}

void aze::SceneParser::WriteObj(const std::wstring& outputFile)
{
}

std::vector<aze::Block>& aze::SceneParser::GetBlocks() const
{
	return m_Blocks;
}