#include <brawlermaker.h>
#include <iostream>


int main()
{
    BrawlerMaker handle;
    auto brawlers = handle.getBrawlers("baseCSVs/csv_logic/characters.csv", "baseCSVs/csv_logic/cards.csv", "baseCSVs/csv_logic/skills.csv", "baseCSVs/localization/texts.csv", true);
    for (auto brawler : brawlers)
    {
        std::cout << brawler.tid << std::endl;
    }
    return 0;
}