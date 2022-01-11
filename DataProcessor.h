#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <vector>
#include "FileLoader.h"

enum MAPPING_ERROR{
    FILE_LOADER_NO_INIT
};

enum SCHEME
{
    ODD = 'O',
    EVEN = 'E',
    MIXED = 'M'
};

struct StreetSegment
{
    std::string streetName;
    std::string streetType;
    SCHEME scheme = SCHEME::MIXED;
    int from;
    int to;

    bool operator==(const StreetSegment& other) const {
        if(to == other.to && from == other.from && streetName == other.streetName && streetType == other.streetType){
            return true;
        }
        return false;
    }

    bool operator!=(const StreetSegment& other) const {
        return !(*this == other);
    }
};


class DataProcessor
{
    public:
        DataProcessor() { fileLoader = nullptr; }
        void init(const std::string path);
        void mapData();
        void searchForDuplicates();
        void printFoundDuplicates();
        ~DataProcessor() { delete fileLoader; }
    private:
        void ExtractDataFromLine(std::string line);
        std::vector<std::string> splitLine(const std::string &line, const std::string &delimiter) const;
        void addToCorrespondingList(const StreetSegment &segment);
        void searchForDuplicatesInSubsection(const std::vector<StreetSegment> &list);
        bool contains(const std::vector<StreetSegment> &list, const StreetSegment &instance);
        void CheckAndAdd(const std::vector<std::string> &lineArray, StreetSegment &segment, int startingIndex);

    private:
        FileLoader* fileLoader;
        std::vector<StreetSegment> odds;
        std::vector<StreetSegment> evens;
        std::vector<StreetSegment> duplicates;
};

#endif