#ifndef DATA_PROCESSER_H
#define DATA_PROCESSER_H

#include <vector>
#include "FileLoader.h"

enum SCHEME
{
    ODD = 10,
    EVEN = 20,
    MIXED = 30
};

struct StreetSegment
{
    std::string streetName; // 16
    std::string streetType; // 17
    SCHEME scheme = SCHEME::MIXED; // 20 - 23
    int from;               // LEFT:21 | RIGHT:24
    int to;                 // LEFT:22 | RIGHT:25
};

class DataProcesser
{
    public:
        void init(const std::string path);
        void mapData();
        void searchForDuplicates();
        ~DataProcesser() { free(fileLoader); }
    private:
        void ExtractDataFromLine(std::string line);
        std::vector<std::string> splitLine(const std::string &line, const std::string &delimiter) const;
        void addToCorrespondingList(const StreetSegment &segment);

    private:
        FileLoader* fileLoader;
        std::vector<StreetSegment> odds;
        std::vector<StreetSegment> evens;
        std::vector<StreetSegment> mixed;
};

#endif