#pragma once

#include <string>

#include "brawler.h"

class TUI
{
public:
    void mainMenu();
    void assetsFolderSelectionMenu();
    Brawler brawlerSelectionMenu();
    void addBrawlerMenu();
    void editBrawlerMenu();
    void removeBrawlerMenu();
    void optionsMenu();
    std::string assetsFolder;
private:
    int menu(std::string tittle, const char *choices[]);
};