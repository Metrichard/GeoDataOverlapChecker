#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include <string>
#include <fstream>
#include <vector>

enum LOADING_ERRORS
{
    NO_LOADED_FILE = 0,
    WRONG_PATH = 1
};

class FileLoader
{
    public:
        FileLoader(const std::string filePath) { path = filePath; hasLoadedFile = false; }
        void OpenFile();
        std::vector<std::string> GetAllLinesFromFile();
        ~FileLoader(){ reader.close(); }

    private:
        void* file;
        std::ifstream reader;
        bool hasLoadedFile;
        std::string path;
};

#endif