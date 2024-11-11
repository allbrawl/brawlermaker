#ifndef BRAWLERMAKER_H
#define BRAWLERMAKER_H

#include <vector>
#include <string>
#include <brawler.h>

class BrawlerMaker
{
public:
    void addBrawler(const Brawler &brawler);
    void editBrawler(int id, const Brawler &brawler);
    std::vector<Brawler> getBrawlers() const;

private:
    std::vector<Brawler> brawlers;
};

#endif