#include <iostream>
#include <string>
#include <windows.h>

#include "Utils.h"
#include "SceneParser.h"

namespace aze
{
	int InvalidArguments(int argc, wchar_t* argv[])
	{
		printf("Invalid argument. -i [inputFile] -o [outputFile] -s are the only ones supported\n");
		printf("When -s is detected, the output file will be opened if it is succesfully generated\n");
		printf("Current arguments:\n");
		for (int i{ 0 }; i < argc; ++i)
		{
			printf("[");
			printf(std::to_string(i).c_str());
			printf("] ");
			wprintf(argv[i]);
			printf("\n");
		}
		return -1;
	}
}

int wmain(int argc, wchar_t* argv[], wchar_t* envp[])
{
	std::wstring inputFile{ L"minecraftscene.json" };
	std::wstring outputFile{ L"minecraftscene.obj" };
	bool tryOpen{ false };
	if (argc > 1)
	{
		if (argc > 2)
		{
			if (wcscmp(argv[1], L"-i") == 0)
			{
				inputFile = argv[2];
			}
			else if (wcscmp(argv[1], L"-o") == 0)
			{
				outputFile = argv[2];
			}
			else if (wcscmp(argv[1], L"-s") == 0)
			{
				tryOpen = true;
			}
			else
			{
				return aze::InvalidArguments(argc, argv);
			}
		}
		else if (!(wcscmp(argv[1], L"-s") == 0))
		{
			return aze::InvalidArguments(argc, argv);
		}

		if (argc > 4)
		{
			if (wcscmp(argv[3], L"-i") == 0)
			{
				inputFile = argv[4];
			}
			else if (wcscmp(argv[3], L"-o") == 0)
			{
				outputFile = argv[4];
			}
			else if (wcscmp(argv[3], L"-s") == 0)
			{
				tryOpen = true;
			}
			else
			{
				return aze::InvalidArguments(argc, argv);
			}
		}

		if (tryOpen == false)
		{
			for (int i{ 1 }; i < argc; ++i)
			{
				if (wcscmp(argv[i], L"-s") == 0)
				{
					tryOpen = true;
				}
			}
		}
	}

	aze::SceneParser sceneParser{};

	if (sceneParser.ReadJson(inputFile) == false)
	{
		printf("Something went wrong with reading the inputfile: ");
		printf(aze::g_ConverterUtf8Utf16.to_bytes(inputFile.c_str()).c_str());
		printf("\n");
		return -1;
	}

	if (sceneParser.WriteObj(outputFile) == false)
	{
		printf("Something went wrong with reading the outputfile: ");
		printf(aze::g_ConverterUtf8Utf16.to_bytes(outputFile.c_str()).c_str());
		printf("\n");
		return -1;
	}
	
	printf("Success!\n");
	printf("Input: ");
	printf(aze::g_ConverterUtf8Utf16.to_bytes(inputFile.c_str()).c_str());
	printf("\n");
	printf("Output: ");
	printf(aze::g_ConverterUtf8Utf16.to_bytes(outputFile.c_str()).c_str());
	printf("\n");

	if (tryOpen)
	{
		ShellExecute(NULL, "open", "explorer.exe", aze::g_ConverterUtf8Utf16.to_bytes(outputFile.c_str()).c_str(), NULL, SW_SHOWDEFAULT);
	}
	return 0;
}