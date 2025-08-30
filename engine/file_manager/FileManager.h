#pragma once


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class FileManager
{
public:
    FileManager();
    ~FileManager();

    static std::string readFile(const std::string& filePath);
};
