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
    std::string streetName;
    std::string streetType;
    SCHEME scheme = SCHEME::MIXED;
    int from;
    int to;
};


class DataProcessor
{
    public:
        void init(const std::string path);
        void mapData();
        void searchForDuplicates();
        void printFoundDuplicates();
        ~DataProcessor() { free(fileLoader); }
    private:
        void ExtractDataFromLine(std::string line);
        std::vector<std::string> splitLine(const std::string &line, const std::string &delimiter) const;
        void addToCorrespondingList(const StreetSegment &segment);
        void searchForDuplicatesInSubsection(const std::vector<StreetSegment> &list);
        bool contains(const std::vector<StreetSegment> &list, const StreetSegment &instance);
        void CheckAndAdd(const std::vector<std::string> &lineArray, int &id, StreetSegment &segment, int startingIndex);

    private:
        FileLoader* fileLoader;
        std::vector<StreetSegment> odds;
        std::vector<StreetSegment> evens;
        std::vector<StreetSegment> mixed;
        std::vector<StreetSegment> duplicates;
};

#endif