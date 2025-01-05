#pragma once

#include <string>

#include "brawler.h"

class TUI
{
public:
    void mainMenu();
    void assetsFolderSelectionMenu();
    Brawler brawlerSelectionMenu();
    void addBrawlerMenu(Brawler &brawler);
    void editBrawlerMenu(Brawler &brawler);
    void removeBrawlerMenu(Brawler &brawler);
    void optionsMenu();
private:
    int menu(std::string tittle, const char *choices[]);
    std::string assetsFolder;
};