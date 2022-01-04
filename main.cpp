#include <iostream>
#include "FileLoader.h"

int main(int argc, char* argv[])
{
    FileLoader loader("D:\\Github\\cautious-octo-barnacle\\resources\\network.mid");
    loader.OpenFile();
    loader.ReadLine();

    return 0;
}



