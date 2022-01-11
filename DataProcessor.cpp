#include <iostream>
#include "DataProcessor.h"
#include <chrono>

void DataProcessor::init(const std::string path)
{
    fileLoader = new FileLoader(path);
    try{
        fileLoader->OpenFile();
    }catch(LOADING_ERRORS e)
    {
        if(e == LOADING_ERRORS::WRONG_PATH) {
            std::cout << "File on path [" << path << "] does not exist\n";
        }
        else {
            std::cout << "Unhandled error";
        }
        exit(EXIT_FAILURE);
    }
}

void DataProcessor::printFoundDuplicates()
{
    for (int i = 0; i < duplicates.size(); ++i)
    {
        char scheme;
        switch (duplicates[i].scheme) {
            case SCHEME::EVEN: scheme = 'E'; break;
            case SCHEME::ODD: scheme = 'O'; break;
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

void DataProcessor::searchForDuplicates()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    searchForDuplicatesInSubsection(odds);
    searchForDuplicatesInSubsection(evens);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "\t\tTask Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;
}

void DataProcessor::searchForDuplicatesInSubsection(const std::vector<StreetSegment> &list)
{
    for(int i = 0; i < list.size(); i++)
    {
        for (int j = 0; j < list.size(); ++j) {
            if(i == j || list[i].streetName != list[j].streetName || list[i].streetType != list[j].streetType) continue;

            if(list[i].to >= list[j].from && list[i].from <= list[j].to && !contains(duplicates, list[i]))
            {
                duplicates.push_back(list[i]);
            }
        }
    }
}

bool DataProcessor::contains(const std::vector<StreetSegment> &list, const StreetSegment &instance)
{
    for(int i = 0; i < list.size(); i++)
        if(list[i] == instance)
            return true;
    return false;
}

void DataProcessor::mapData()
{
    std::vector<std::string> lines;
    try {
        if(fileLoader == nullptr)
            throw MAPPING_ERROR::FILE_LOADER_NO_INIT;
        lines = fileLoader->GetAllLinesFromFile();
    }catch(LOADING_ERRORS e){
        if(e == LOADING_ERRORS::NO_LOADED_FILE) {
            std::cout << "There are no files loaded\n";
        }
        exit(EXIT_FAILURE);
    }catch(MAPPING_ERROR e){
        if(e == MAPPING_ERROR::FILE_LOADER_NO_INIT)
            std::cout << "File loader failed to initialize\n";
        exit(EXIT_FAILURE);
    }

    for (std::string line : lines) {
        ExtractDataFromLine(line);
    }
}

void DataProcessor::ExtractDataFromLine(std::string line)
{
    StreetSegment segment;
    auto lineArray = splitLine(line, ",");
    segment.streetName = lineArray[16];
    segment.streetType = lineArray[17];
    if(segment.streetName == "" || segment.streetType == "") return;
    if(lineArray[20] != "")
    {
        CheckAndAdd(lineArray, segment, 20);
    }
    segment.scheme = SCHEME::MIXED;
    if(lineArray[23] != "")
    {
        CheckAndAdd(lineArray, segment, 23);
    }
}

void DataProcessor::CheckAndAdd(const std::vector<std::string> &lineArray, StreetSegment &segment, int startingIndex) {
    if(lineArray[startingIndex] != "M")
        segment.scheme = lineArray[startingIndex++] == "0" ? ODD : EVEN;
    segment.from = atoi(lineArray[startingIndex++].c_str());
    segment.to = atoi(lineArray[startingIndex].c_str());
    if(segment.from > 0 && segment.to > 0)
        addToCorrespondingList(segment);
}

void DataProcessor::addToCorrespondingList(const StreetSegment &segment) {
    switch (segment.scheme) {
        case ODD : odds.push_back(segment); break;
        case EVEN : evens.push_back(segment); break;
        case MIXED : odds.push_back(segment); evens.push_back(segment); break;
    }
}

std::vector<std::string> DataProcessor::splitLine(const std::string &line, const std::string &delimiter) const {
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
