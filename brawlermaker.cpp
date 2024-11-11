#include <brawler.h>
#include <brawlermaker.h>
#include <csv.h>
#include <stdexcept>

std::vector<Brawler> BrawlerMaker::getBrawlers(const std::string charactersCSVPath, const std::string cardsCSVPath, const std::string skillsCSVPath, const std::string textsCSVPath) const
{
    // REMEMBER
    CSVHandler handle;
    std::vector<Brawler> brawlers;
    auto rows = handle.getRows(charactersCSVPath);
    auto cardsRows = handle.getRows(cardsCSVPath);
    auto skillsRows = handle.getRows(skillsCSVPath);
    auto textsRows = handle.getRows(textsCSVPath);
    bool datatypes = true;

    for (auto row : rows)
    {
        // Skip row containing data types (string, int and boolean)
        if (datatypes)
        {
            datatypes = false;
            continue;
        }
        Brawler brawler;
        std::string type = row[20];
        // Skip non brawlers
        if (type != "Hero")
        {
            continue;
        }
        brawler.codename = row[0];
        brawler.tid = row[77];

        brawler.weaponSkill = row[4];
        brawler.ultimateSkill = row[5];
        try
        {
            brawler.speed = std::stoi(row[7]);
            brawler.health = std::stoi(row[8]);
        }
        catch (const std::invalid_argument &e)
        {
            throw std::runtime_error("Invalid argument in stoi for speed or health");
        }
        catch (const std::out_of_range &e)
        {
            throw std::runtime_error("Out of range in stoi for speed or health");
        }
        brawler.iconSWF = row[80];
        brawler.icon = row[81];
        brawler.pet = row[6];
        try
        {
            brawler.scale = std::stoi(row[61]);
        }
        catch (const std::invalid_argument &e)
        {
            throw std::runtime_error("Invalid argument in stoi for scale");
        }
        catch (const std::out_of_range &e)
        {
            throw std::runtime_error("Out of range in stoi for scale");
        }
        // brawler.autoAttackRange = stoi(row[18]);
        for (auto skillsRow : skillsRows)
        {
            if (skillsRow[0] == brawler.weaponSkill)
            {
                brawler.weaponReloadTime = std::stoi(row[16]);
                brawler.weaponAmmoCount = std::stoi(row[17]);
                brawler.weaponDamage = std::stoi(row[18]);
                brawler.attackSpread = std::stoi(row[21]);
                brawler.weaponProjectileCount = std::stoi(row[23]);    // NumBulletsInOneAttack
                brawler.weaponTimeBetweenAttacks = std::stoi(row[20]); // MsBetweenAttacks
                brawler.attackDuration = std::stoi(row[9]);            // ActiveTime
                brawler.weaponRange = std::stoi(row[11]);              // CastingRange
            }
            if (skillsRow[0] == brawler.ultimateSkill)
            {
                brawler.ultimateRechargeTime = std::stoi(row[16]);
                brawler.ultimateDamage = std::stoi(row[18]);
                brawler.ultimateSpread = std::stoi(row[21]);
                brawler.ultimateProjectileCount = std::stoi(row[23]);    // NumBulletsInOneAttack
                brawler.ultimateTimeBetweenAttacks = std::stoi(row[20]); // MsBetweenAttacks
                brawler.ultimateAttackDuration = std::stoi(row[9]);      // ActiveTime
                brawler.ultimateRange = std::stoi(row[11]);              // CastingRange
            }
        }

        std::string weaponTID;
        std::string ultimateTID;
        // 8th column in cards is type
        // 3rd column in cards is target
        for (auto cardsRow : cardsRows)
        {
            if (cardsRow[3] == brawler.codename)
            {
                if (cardsRow[8] == "unlock")
                {
                    const std::string csvRarity = cardsRow[13];
                    if (csvRarity == "common")
                    {
                        brawler.rarity = Rarity::TrophyRoad;
                    }
                    else if (csvRarity == "rare")
                    {
                        brawler.rarity = Rarity::Rare;
                    }
                    else if (csvRarity == "super_rare")
                    {
                        brawler.rarity = Rarity::SuperRare;
                    }
                    else if (csvRarity == "epic")
                    {
                        brawler.rarity = Rarity::Epic;
                    }
                    else if (csvRarity == "mega_epic")
                    {
                        brawler.rarity = Rarity::Mythic;
                    }
                    else if (csvRarity == "legendary")
                    {
                        brawler.rarity = Rarity::Legendary;
                    }
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

        for (auto textsRow : textsRows)
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
