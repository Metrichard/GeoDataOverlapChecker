#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include <string>
#include <fstream>

enum LOADING_ERRORS
{
    NO_LOADED_FILE = 0,
    WRONG_PATH = 1
};

class FileLoader
{
    public:
        FileLoader(std::string filePath) { path = filePath; hasLoadedFile = false; }
        void OpenFile();
        void ReadLine();
        ~FileLoader(){ reader.close(); }
    private:
        void* file;
        std::ifstream reader;
        bool hasLoadedFile;
        std::string path;
};

#endif