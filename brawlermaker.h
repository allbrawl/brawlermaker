#ifndef BRAWLERMAKER_H
#define BRAWLERMAKER_H
#include <limits>
constexpr int UNDEFINED = std::numeric_limits<int>::min();

#include <vector>
#include <string>
#include "brawler.h"

class BrawlerMaker
{
public:
    int addBrawler(const Brawler &brawler, std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath);
    int editBrawler(int tid, const Brawler &brawler, std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath);
    int removeBrawler(std::string codename, std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath);
    Brawler getBrawler(const std::string tid, const std::string charactersCSVPath, const std::string cardsCSVPath, const std::string skillsCSVPath, const std::string textsCSVPath) const;
    std::vector<Brawler> getBrawlers(std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath, bool ignoreNonHeros = false);

private:
    std::vector<Brawler> brawlers;
};

#endif