#ifndef BRAWLERMAKER_H
#define BRAWLERMAKER_H
#ifndef UNDEFINED
#define UNDEFINED 0
#endif

#include <vector>
#include <string>
#include <brawler.h>

class BrawlerMaker
{
public:
    int addBrawler(const Brawler &brawler);
    int editBrawler(int id, const Brawler &brawler);
    std::vector<Brawler> getBrawlers(std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath, bool ignoreNonHeros = false) const;
    Brawler getBrawler(std::string codename) const;

private:
    std::vector<Brawler> brawlers;
};

#endif