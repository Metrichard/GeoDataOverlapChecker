#include <iostream>
#include "DataProcesser.h"

int main(int argc, char* argv[])
{
    DataProcesser processer;
    processer.init("D:\\Github\\cautious-octo-barnacle\\resources\\network.mid");
    processer.mapData();

    return 0;
}



