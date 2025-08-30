#include "FileManager.h"

FileManager::FileManager() {

}

FileManager::~FileManager() {

}

std::string FileManager::readFile(const std::string& filePath)
{
    std::ifstream file;

    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    std::stringstream file_stream;

    try
    {
        file.open(filePath.c_str());
        file_stream << file.rdbuf();
        file.close();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "error reading shader" << std::endl;
    }
    return file_stream.str();
}
