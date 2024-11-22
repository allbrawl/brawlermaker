#include <brawler.h>
#include <brawlermaker.h>
#include <csv.h>
#include <stdexcept>
#include <iostream>

int toint(std::string s, int fallback)
{
    try
    {
        return stoi(s);
    }
    catch (const std::exception &e)
    {
        return fallback;
    }
}

std::vector<Brawler> BrawlerMaker::getBrawlers(const std::string charactersCSVPath, const std::string cardsCSVPath, const std::string skillsCSVPath, const std::string textsCSVPath, bool ignoreNonHeros) const
{
    CSVHandler handle;
    std::vector<Brawler> brawlers;
    auto rows = handle.getRows(charactersCSVPath);
    auto cardsRows = handle.getRows(cardsCSVPath);
    auto skillsRows = handle.getRows(skillsCSVPath);
    auto textsRows = handle.getRows(textsCSVPath);
    auto charactersColumns = handle.getColumns(charactersCSVPath);
    auto cardsColumns = handle.getColumns(cardsCSVPath);
    auto skillsColumns = handle.getColumns(skillsCSVPath);

    bool datatypes = true;

    for (auto &row : rows)
    {
        if (datatypes)
        {
            datatypes = false;
            continue;
        }
        Brawler brawler;
        std::string type = row[20];
        if (type != "Hero" && ignoreNonHeros == true)
        {
            continue;
        }
        brawler.codename = row[0];
        brawler.tid = row[77];

        brawler.weaponSkill = row[4];
        brawler.ultimateSkill = row[5];

        brawler.speed = toint(row[7], UNDEFINED);
        brawler.health = toint(row[8], UNDEFINED);

        brawler.iconSWF = row[80];
        brawler.icon = row[81];
        brawler.pet = row[6];

        brawler.scale = toint(row[61], UNDEFINED);

        brawler.attackRechargeUltimateAmount = toint(row[18], UNDEFINED);

        brawler.ultimateRechargeUltimateAmount = toint(row[19], UNDEFINED);

        for (auto &skillsRow : skillsRows)
        {
            if (skillsRow[0] == brawler.weaponSkill)
            {
                try
                {
                    brawler.ultimateReloadTime = toint(skillsRow[14], UNDEFINED);

                    brawler.weaponReloadTime = toint(skillsRow[14], UNDEFINED);
                    brawler.weaponAmmoCount = toint(skillsRow[15], UNDEFINED);
                    brawler.weaponDamage = toint(skillsRow[16], UNDEFINED);

                    brawler.attackSpread = toint(skillsRow[19], UNDEFINED);

                    brawler.weaponProjectileCount = toint(skillsRow[21], UNDEFINED);

                    brawler.weaponTimeBetweenAttacks = toint(skillsRow[18], UNDEFINED);

                    brawler.attackDuration = toint(skillsRow[7], UNDEFINED);

                    brawler.weaponRange = toint(skillsRow[9], UNDEFINED);
                }

                catch (const std::exception &e)
                {
                    std::cerr << "Error: " << e.what() << " at line " << __LINE__ << " indentifier " << skillsRow[0] << std::endl;
                    throw;
                }
            }
            if (skillsRow[0] == brawler.ultimateSkill)
            {
                try
                {

                    brawler.ultimateDamage = toint(skillsRow[16], UNDEFINED);

                    brawler.ultimateSpread = toint(skillsRow[19], UNDEFINED);

                    brawler.ultimateProjectileCount = 0;

                    brawler.ultimateProjectileCount = toint(skillsRow[21], UNDEFINED);

                    brawler.ultimateAttackDuration = toint(skillsRow[7], UNDEFINED);

                    brawler.summonedCharacter == skillsRow[handle.getColumnIndex(skillsColumns, "SummonedCharacter")];

                    brawler.ultimateRange = toint(skillsRow[9], UNDEFINED);
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Error: " << e.what() << " at line " << __LINE__ << " identifier " << skillsRow[0] << std::endl;
                    throw;
                }
            }
        }

        std::string weaponTID;
        std::string ultimateTID;
        for (auto &cardsRow : cardsRows)
        {
            if (cardsRow[3] == brawler.codename)
            {
                if (cardsRow[8] == "unlock")
                {
                    const std::string csvRarity = cardsRow[13];
                    if (csvRarity == "common")
                        brawler.rarity = Rarity::TrophyRoad;
                    else if (csvRarity == "rare")
                        brawler.rarity = Rarity::Rare;
                    else if (csvRarity == "super_rare")
                        brawler.rarity = Rarity::SuperRare;
                    else if (csvRarity == "epic")
                        brawler.rarity = Rarity::Epic;
                    else if (csvRarity == "mega_epic")
                        brawler.rarity = Rarity::Mythic;
                    else if (csvRarity == "legendary")
                        brawler.rarity = Rarity::Legendary;
                    break;
                }
                else if (cardsRow[9] == brawler.weaponSkill)
                {
                    weaponTID = cardsRow[14];
                }
                else if (cardsRow[9] == brawler.ultimateSkill)
                {
                    ultimateTID = cardsRow[14];
                }
            }
        }

        for (auto &textsRow : textsRows)
        {
            if (textsRow[0] == brawler.tid)
            {
                brawler.name = textsRow[1];
            }
            if (textsRow[0] == brawler.tid + "_DESC")
            {
                brawler.description = textsRow[1];
                break;
            }
            else if (textsRow[0] == weaponTID)
            {
                brawler.weaponName = textsRow[1];
                break;
            }
            else if (textsRow[0] == ultimateTID)
            {
                brawler.ultimateName = textsRow[1];
                break;
            }
            else if (textsRow[0] == weaponTID + "_DESC")
            {
                brawler.weaponDescription = textsRow[1];
                break;
            }
            else if (textsRow[0] == ultimateTID + "_DESC")
            {
                brawler.ultimateDescription = textsRow[1];
                break;
            }
        }
        brawlers.push_back(brawler);
    }
    return brawlers;
}
