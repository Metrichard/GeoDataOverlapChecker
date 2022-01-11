#include <iostream>
#include "DataProcessor.h"

int main(int argc, char* argv[])
{
    std::string filePath;
    if(argc > 1) filePath = argv[1];
    else std::getline(std::cin, filePath);

    DataProcessor processor;
    processor.init(filePath);
    processor.mapData();
    processor.searchForDuplicates();
    processor.printFoundDuplicates();

    return 0;
}



