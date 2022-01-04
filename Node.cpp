#include <string>

enum SCHEME
{
    LEFT = 10,
    RIGHT = 20
};

struct Node
{
    std::string streetName;
    std::string streetType;
    SCHEME scheme;
    int from;
    int to;
};

/*
    what i need is:
        -   STREET_NAME
        -   STREET TYPE
        -   SCHEMELEFT OR RIGHT(E, O, M)
        -   FROMLEFT-TOLEFT/FROMRIGHT-TORIGHT(BASED ON SCEHEMA)
*/