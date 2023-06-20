# MinecraftTool

This project was an introduction into CMake.
The program will take a json file and convert it to an obj. Using CMake, there is a console tool with a flag to open the output file using your default program (Windows 3D-viewer for example). The GUI version (made with [JUCE](https://juce.com/)) has the same functionality but has a graphical interface to interact with. Besides the normal functionality, you can also preview what blocks will be placed where in the obj file.

## CMake

The project consists of 4 parts:
- commoncode
- consoletool
- gui
- headeronlylib

The commoncode is the core code and consoletool and gui depend on it. Commoncode depends on [rapidjson](https://github.com/Tencent/rapidjson) to parse json which is in the headeronlylib.

## What I learned

CMake made me appreciate Visual Studio linker and compiler that I took for granted. Besides that, I learned that my code was way more tangled and monolithic before I seperated it in directories and specific functionalities. I will definitely think more about how dependent my classes and code is on other modules or pieces.
Besides this, I learned some basics of CMake like adding and linking libraries, making executables and making an installer.