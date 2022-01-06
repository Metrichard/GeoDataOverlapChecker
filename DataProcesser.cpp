#include <sstream>
#include <iostream>
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

void DataProcesser::printFoundDuplicates()
{
    for (int i = 0; i < duplicates.size(); ++i)
    {
        char scheme;
        switch (duplicates[i].scheme) {
            case SCHEME::EVEN: scheme = 'E';
            case SCHEME::ODD: scheme = 'O';
            default:
                scheme = 'M';
        }
        std::cout << duplicates[i].streetName << " "
                  << duplicates[i].streetType << ": "
                  << scheme << " "
                  << duplicates[i].from << " "
                  << duplicates[i].to << std::endl;
    }
}

void DataProcesser::searchForDuplicates()
{
    searchForDuplicates(odds);
    searchForDuplicates(evens);
}

void DataProcesser::searchForDuplicates(const std::vector<StreetSegment> &list)
{
    for(int i = 0; i < list.size(); i++)
    {
        for (int j = 0; j < list.size(); ++j) {
            if(i == j) continue;
            if(list[i].to >= list[j].from && list[i].from <= list[j].to && !contains(duplicates, list[j]))
            {
                duplicates.push_back(list[j]);
            }
        }
    }
}

bool DataProcesser::contains(const std::vector<StreetSegment> &list, const StreetSegment &instance)
{
    for(int i = 0; i < list.size(); i++)
        if(list[i].id == instance.id)
            return true;
    return false;
}

void DataProcesser::mapData()
{
    auto lines = fileLoader->GetAllLinesFromFile();
    for (std::string line : lines) {
        ExtractDataFromLine(line);
    }
}

void DataProcesser::ExtractDataFromLine(std::string line)
{
    static int id = 100;
    StreetSegment segment;
    auto lineArray = splitLine(line, ",");
    segment.streetName = lineArray[16];
    segment.streetType = lineArray[17];
    if(segment.streetName == "" || segment.streetType == "")
        return;
    if(lineArray[20] != "")
    {
        if(lineArray[20] != "M")
            segment.scheme = lineArray[20] == "O" ? SCHEME::ODD : SCHEME::EVEN;
        segment.id = id++;
        segment.from = atoi(lineArray[21].c_str());
        segment.to = atoi(lineArray[22].c_str());
        if(segment.from > 0 && segment.to > 0)
            addToCorrespondingList(segment);
    }
    segment.scheme = SCHEME::MIXED;
    if(lineArray[23] != "")
    {
        if(lineArray[23] != "M")
            segment.scheme = lineArray[23] == "0" ? SCHEME::ODD : SCHEME::EVEN;
        segment.id = id++;
        segment.from = atoi(lineArray[24].c_str());
        segment.to = atoi(lineArray[25].c_str());
        if(segment.from > 0 && segment.to > 0)
            addToCorrespondingList(segment);
    }
}

void DataProcesser::addToCorrespondingList(const StreetSegment &segment) {
    switch (segment.scheme) {
        case ODD : odds.push_back(segment); break;
        case EVEN : evens.push_back(segment); break;
        case MIXED : mixed.push_back(segment); break;
    }
}

std::vector<std::string> DataProcesser::splitLine(const std::string &line, const std::string &delimiter) const {
    int start = 0;
    int end = line.find(delimiter);
    std::vector<std::string> splitLine;
    while(end != -1)
    {
        splitLine.push_back(line.substr(start, end - start));
        start = end + delimiter.size();
        end = line.find(delimiter, start);
    }
    splitLine.push_back(line.substr(start, end - start));
    return splitLine;
}
