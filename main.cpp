#include <brawlermaker.h>
#include <iostream>
#include <csv.h>
#include <cstring>

void help()
{
    std::cout << "Usage: brawlermaker <mode> [arguments]\n\n";
    std::cout << "Modes:\n";
    std::cout << "  list                  - Lists all brawlers or a specific brawler if TID is provided.\n";
    std::cout << "  add                   - Adds a new brawler to the CSV files.\n";
    std::cout << "  remove                - Removes a brawler by TID from the CSV files.\n";
    std::cout << "  edit                  - Edits an existing brawler's details by TID.\n\n";
    std::cout << "Arguments (for 'list' mode):\n";
    std::cout << "  [TID]                 - If provided, only the brawler with the specified TID will be listed.\n";
    std::cout << "                        - If not provided, all brawlers will be listed.\n\n";
}

void printBrawler(const Brawler &brawler)
{
    std::cout << "*************************" << "\n";
    std::cout << "codename: " << brawler.codename << "\n";
    std::cout << "name: " << brawler.name << "\n";
    std::cout << "tid: " << brawler.tid << "\n";
    std::cout << "description: " << brawler.description << "\n";
    std::cout << "weaponName: " << brawler.weaponName << "\n";
    std::cout << "ultimateName: " << brawler.ultimateName << "\n";
    std::cout << "weaponDescription: " << brawler.weaponDescription << "\n";
    std::cout << "ultimateDescription: " << brawler.ultimateDescription << "\n";
    if (brawler.rarity == Rarity::TrophyRoad)
        std::cout << "rarity: Trophy Road" << "\n";
    else if (brawler.rarity == Rarity::Rare)
        std::cout << "rarity: Rare" << "\n";
    else if (brawler.rarity == Rarity::SuperRare)
        std::cout << "rarity: Super Rare" << "\n";
    else if (brawler.rarity == Rarity::Epic)
        std::cout << "rarity: Epic" << "\n";
    else if (brawler.rarity == Rarity::Mythic)
        std::cout << "rarity: Mythic " << "\n";
    else if (brawler.rarity == Rarity::Legendary)
        std::cout << "rarity: Legendary" << "\n";

    std::cout << "weaponSkill: " << brawler.weaponSkill << "\n";
    std::cout << "ultimateSkill: " << brawler.ultimateSkill << "\n";
    std::cout << "speed: " << (brawler.speed == UNDEFINED ? "undefined" : std::to_string(brawler.speed)) << "\n";
    std::cout << "health: " << (brawler.health == UNDEFINED ? "undefined" : std::to_string(brawler.health)) << "\n";
    std::cout << "iconSWF: " << brawler.iconSWF << "\n";
    std::cout << "icon: " << brawler.icon << "\n";
    std::cout << "pet: " << brawler.pet << "\n";
    std::cout << "summonedCharacter: " << brawler.summonedCharacter << "\n";
    std::cout << "scale: " << (brawler.scale == UNDEFINED ? "undefined" : std::to_string(brawler.scale)) << "\n";
    std::cout << "weaponRange: " << (brawler.weaponRange == UNDEFINED ? "undefined" : std::to_string(brawler.weaponRange)) << "\n";
    std::cout << "ultimateRange: " << (brawler.ultimateRange == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateRange)) << "\n";
    std::cout << "weaponReloadTime: " << (brawler.weaponReloadTime == UNDEFINED ? "undefined" : std::to_string(brawler.weaponReloadTime)) << "\n";
    std::cout << "ultimateReloadTime: " << (brawler.ultimateReloadTime == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateReloadTime)) << "\n";
    std::cout << "weaponAmmoCount: " << (brawler.weaponAmmoCount == UNDEFINED ? "undefined" : std::to_string(brawler.weaponAmmoCount)) << "\n";
    std::cout << "ultimateAmmoCount: " << (brawler.ultimateAmmoCount == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateAmmoCount)) << "\n";
    std::cout << "weaponDamage: " << (brawler.weaponDamage == UNDEFINED ? "undefined" : std::to_string(brawler.weaponDamage)) << "\n";
    std::cout << "ultimateDamage: " << (brawler.ultimateDamage == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateDamage)) << "\n";
    std::cout << "attackSpread: " << (brawler.attackSpread == UNDEFINED ? "undefined" : std::to_string(brawler.attackSpread)) << "\n";
    std::cout << "ultimateSpread: " << (brawler.ultimateSpread == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateSpread)) << "\n";
    std::cout << "attackProjectileCount: " << (brawler.attackProjectileCount == UNDEFINED ? "undefined" : std::to_string(brawler.attackProjectileCount)) << "\n";
    std::cout << "ultimateProjectileCount: " << (brawler.ultimateProjectileCount == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateProjectileCount)) << "\n";
    std::cout << "weaponTimeBetweenAttacks: " << (brawler.weaponTimeBetweenAttacks == UNDEFINED ? "undefined" : std::to_string(brawler.weaponTimeBetweenAttacks)) << "\n";
    std::cout << "ultimateTimeBetweenAttacks: " << (brawler.ultimateTimeBetweenAttacks == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateTimeBetweenAttacks)) << "\n";
    std::cout << "attackDuration: " << (brawler.attackDuration == UNDEFINED ? "undefined" : std::to_string(brawler.attackDuration)) << "\n";
    std::cout << "ultimateAttackDuration: " << (brawler.ultimateAttackDuration == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateAttackDuration)) << "\n";
    std::cout << "attackRechargeUltimateAmount: " << (brawler.attackRechargeUltimateAmount == UNDEFINED ? "undefined" : std::to_string(brawler.attackRechargeUltimateAmount)) << "\n";
    std::cout << "ultimateRechargeUltimateAmount: " << (brawler.ultimateRechargeUltimateAmount == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateRechargeUltimateAmount)) << "\n";
    std::cout << "number: " << (brawler.number == UNDEFINED ? "undefined" : std::to_string(brawler.number)) << "\n";
    std::cout << "attackProjectile: " << brawler.attackProjectile << "\n";
    std::cout << "ultimateProjectile: " << brawler.ultimateProjectile << "\n";
    std::cout << "weaponTID: " << brawler.weaponTID << "\n";
    std::cout << "ultimateTID: " << brawler.ultimateTID << "\n";
}

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        help();
        exit(1);
    }
    if (!strcmp("list", argv[1]))
    {
        BrawlerMaker handle;

        if (argc > 2)
        {
            std::string brawlerTID = argv[2];
            auto brawler = handle.getBrawler(brawlerTID, "baseCSVs/csv_logic/characters.csv", "baseCSVs/csv_logic/cards.csv", "baseCSVs/csv_logic/skills.csv", "baseCSVs/localization/texts.csv");
            printBrawler(brawler);
            std::cout << "*************************" << "\n";
        }
        else
        {
            auto brawlers = handle.getBrawlers("baseCSVs/csv_logic/characters.csv", "baseCSVs/csv_logic/cards.csv", "baseCSVs/csv_logic/skills.csv", "baseCSVs/localization/texts.csv", true);
            for (const auto &brawler : brawlers)
            {
                printBrawler(brawler);
            }
            std::cout << "*************************" << "\n";
        }
    }
    else
    {
        help();
    }

    return 0;
}
