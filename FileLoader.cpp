#include "FileLoader.h"

#include <iostream>

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

void FileLoader::ReadLine()
{
    if(!hasLoadedFile)
    {
        std::cout << "There are no files loaded\n";
        throw LOADING_ERRORS::NO_LOADED_FILE;
    }

    std::string line;
    while(getline(reader, line))
    {
        std::cout << line << std::endl;
    }
}