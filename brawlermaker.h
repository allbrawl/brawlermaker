#pragma once

#include <string>
#include <vector>

#include "brawler.h"

class BrawlerMaker
{
public:
    int addBrawler(const Brawler &brawler, std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath);
    int editBrawler(std::string tid, const Brawler &brawler, std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath);
    int removeBrawler(std::string tid, std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath);
    int cloneBrawler(std::string tid, std::string newTID, std::string newName, std::string newWeaponName, std::string newUltimateName, std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath);
    Brawler getBrawler(const std::string tid, const std::string charactersCSVPath, const std::string cardsCSVPath, const std::string skillsCSVPath, const std::string textsCSVPath) const;
    std::vector<Brawler> getBrawlers(std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath, bool ignoreNonHeros = false);

private:
    std::vector<Brawler> brawlers;
};