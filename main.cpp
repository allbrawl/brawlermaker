#include <iostream>
#include <cstring>

#include "tui.h"

int main(int argc, char **argv)
{
    TUI tui;
    if (argc == 2)
    {
        tui.assetsFolder = argv[1];
    }
    tui.mainMenu();

    return 0;
}
