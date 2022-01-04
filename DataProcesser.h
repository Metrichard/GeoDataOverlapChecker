#ifndef DATA_PROCESSER_H
#define DATA_PROCESSER_H

#include "FileLoader.h"

enum SCHEME
{
    LEFT = 10,
    RIGHT = 20
};

struct Node
{
    std::string streetName;
    std::string streetType;
    SCHEME scheme;
    int from;
    int to;
};

class DataProcesser
{
    public:
        void init(const std::string path);
        void mapData();
    private:
        FileLoader* fileLoader;
};

#endif