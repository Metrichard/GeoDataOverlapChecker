#include <iostream>
#include <chrono>
#include "DataProcessor.h"

int main(int argc, char* argv[])
{
    std::string filePath;
    if(argc > 1) filePath = argv[1];
    else std::getline(std::cin, filePath);

    DataProcessor processor;
    processor.init(filePath);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    processor.mapData();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "\t\tMap Data Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;
    processor.searchForDuplicates();
    processor.printFoundDuplicates();

    return 0;
}



