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
    int editBrawler(int id, const Brawler &brawler);
    std::vector<Brawler> getBrawlers(std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath, bool ignoreNonHeros = false) const;
    Brawler getBrawler(std::string codename) const;

private:
    std::vector<Brawler> brawlers;
};

#endif