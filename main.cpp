#include <brawlermaker.h>
#include <iostream>
#include <csv.h>
#include <cstring>

void help()
{
    std::cout << "Usage: brawlermaker <mode> [arguments]\n\n";
    std::cout << "Modes:\n";
    std::cout << "  list [TID]                 - Lists all brawlers or a specific brawler if TID is provided.\n";
    std::cout << "  add                        - Adds a new brawler to the CSV files.\n";
    std::cout << "  remove <TID>               - Removes a brawler by TID from the CSV files.\n";
    std::cout << "  edit <TID> <field>=<value> - Edits an existing brawler's details by TID.\n\n";
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
    std::cout << "speed: " << brawler.speed << "\n";
    std::cout << "health: " << brawler.health << "\n";
    std::cout << "iconSWF: " << brawler.iconSWF << "\n";
    std::cout << "icon: " << brawler.icon << "\n";
    std::cout << "pet: " << brawler.pet << "\n";
    std::cout << "summonedCharacter: " << brawler.summonedCharacter << "\n";
    std::cout << "scale: " << brawler.scale << "\n";
    std::cout << "weaponRange: " << brawler.weaponRange << "\n";
    std::cout << "ultimateRange: " << brawler.ultimateRange << "\n";
    std::cout << "weaponReloadTime: " << brawler.weaponReloadTime << "\n";
    std::cout << "weaponAmmoCount: " << brawler.weaponAmmoCount << "\n";
    std::cout << "ultimateAmmoCount: " << brawler.ultimateAmmoCount << "\n";
    std::cout << "weaponDamage: " << brawler.weaponDamage << "\n";
    std::cout << "ultimateDamage: " << brawler.ultimateDamage << "\n";
    std::cout << "attackSpread: " << brawler.attackSpread << "\n";
    std::cout << "ultimateSpread: " << brawler.ultimateSpread << "\n";
    std::cout << "attackProjectileCount: " << brawler.attackProjectileCount << "\n";
    std::cout << "ultimateProjectileCount: " << brawler.ultimateProjectileCount << "\n";
    std::cout << "weaponTimeBetweenAttacks: " << brawler.weaponTimeBetweenAttacks << "\n";
    std::cout << "ultimateTimeBetweenAttacks: " << brawler.ultimateTimeBetweenAttacks << "\n";
    std::cout << "attackDuration: " << brawler.attackDuration << "\n";
    std::cout << "ultimateAttackDuration: " << brawler.ultimateAttackDuration << "\n";
    std::cout << "attackRechargeUltimateAmount: " << brawler.attackRechargeUltimateAmount << "\n";
    std::cout << "ultimateRechargeUltimateAmount: " << brawler.ultimateRechargeUltimateAmount << "\n";
    std::cout << "number: " << brawler.number << "\n";
    std::cout << "attackCooldown: " << brawler.attackCooldown << "\n";
    std::cout << "ultimateCooldown:" << brawler.ultimateCooldown << "\n";
    std::cout << "attackProjectile: " << brawler.attackProjectile << "\n";
    std::cout << "ultimateProjectile: " << brawler.ultimateProjectile << "\n";
    std::cout << "weaponTID: " << brawler.weaponTID << "\n";
    std::cout << "ultimateTID: " << brawler.ultimateTID << "\n";
    std::cout << "defaultSkin: " << brawler.defaultSkin << "\n";
}

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        help();
    }
    else if (!strcmp("list", argv[1]))
    {
        BrawlerMaker bm;

        if (argc > 2)
        {
            const char *brawlerTID = argv[2];
            Brawler brawler = bm.getBrawler(brawlerTID, "baseCSVs/csv_logic/characters.csv", "baseCSVs/csv_logic/cards.csv", "baseCSVs/csv_logic/skills.csv", "baseCSVs/localization/texts.csv");
            printBrawler(brawler);
            std::cout << "*************************" << "\n";
        }
        else
        {
            std::vector<Brawler> brawlers = bm.getBrawlers("baseCSVs/csv_logic/characters.csv", "baseCSVs/csv_logic/cards.csv", "baseCSVs/csv_logic/skills.csv", "baseCSVs/localization/texts.csv", true);
            for (const auto &brawler : brawlers)
            {
                printBrawler(brawler);
            }
            std::cout << "*************************" << "\n";
        }
    }
    else if (!strcmp("remove", argv[1]) && argc > 2)
    {
        BrawlerMaker bm;

        bm.removeBrawler(argv[2], "baseCSVs/csv_logic/characters.csv", "baseCSVs/csv_logic/cards.csv", "baseCSVs/csv_logic/skills.csv", "baseCSVs/localization/texts.csv");
    }
    else
    {
        help();
    }

    return 0;
}
