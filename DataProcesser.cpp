#include "DataProcesser.h"

void DataProcesser::init(const std::string path)
{
    fileLoader = new FileLoader(path);
    try{
        fileLoader->OpenFile();
    }catch(LOADING_ERRORS e)
    {
        exit(EXIT_FAILURE);
    }
}