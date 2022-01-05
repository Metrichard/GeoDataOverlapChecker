#include "FileLoader.h"

#include <iostream>
#include <algorithm>

void FileLoader::OpenFile()
{
    reader.open(path, std::ios::in);
    if(!reader)
    {
        std::cout << "File on path [" << path << "] does not exist\n";
        throw LOADING_ERRORS::WRONG_PATH;
    }
    std::cout << "File has been opened.\n";
    hasLoadedFile = true;
}

std::vector<std::string> FileLoader::GetAllLinesFromFile()
{
    if(!hasLoadedFile)
    {
        std::cout << "There are no files loaded\n";
        throw LOADING_ERRORS::NO_LOADED_FILE;
    }
    std::vector<std::string> lines;
    std::string line;
    while(getline(reader, line))
    {
        line.erase(std::remove(line.begin(), line.end(), '\"'), line.end());
        lines.push_back(line);
    }
    return lines;
}