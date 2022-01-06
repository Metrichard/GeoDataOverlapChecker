#ifndef DATA_PROCESSER_H
#define DATA_PROCESSER_H

#include <vector>
#include "FileLoader.h"
#include <windows.h>

enum SCHEME
{
    ODD = 'O',
    EVEN = 'E',
    MIXED = 'M'
};

struct StreetSegment
{
    int id;
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
        void printFoundDuplicates();
        ~DataProcesser() { free(fileLoader); }
    private:
        void ExtractDataFromLine(std::string line);
        std::vector<std::string> splitLine(const std::string &line, const std::string &delimiter) const;
        void addToCorrespondingList(const StreetSegment &segment);
        void searchForDuplicates(const std::vector<StreetSegment> &list);
        bool contains(const std::vector<StreetSegment> &list, const StreetSegment &instance);

    private:
        FileLoader* fileLoader;
        std::vector<StreetSegment> odds;
        std::vector<StreetSegment> evens;
        std::vector<StreetSegment> mixed;
        std::vector<StreetSegment> duplicates;
};

#endif