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

void DataProcesser::searchForDuplicates()
{
    
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
