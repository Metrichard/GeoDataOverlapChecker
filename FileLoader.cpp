#include "FileLoader.h"

#include <iostream>
#include <algorithm>

void FileLoader::OpenFile()
{
    reader.open(path, std::ios::in);
    if(!reader)
    {
        throw LOADING_ERRORS::WRONG_PATH;
    }
    std::cout << "File has been opened.\n";
    hasLoadedFile = true;
}

std::vector<std::string> FileLoader::GetAllLinesFromFile()
{
    if(!hasLoadedFile)
        throw LOADING_ERRORS::NO_LOADED_FILE;
    std::vector<std::string> lines;
    std::string line;
    while(getline(reader, line))
    {
        line.erase(std::remove(line.begin(), line.end(), '\"'), line.end());
        lines.push_back(line);
    }
    return lines;
}