#ifndef BRAWLER_H
#define BRAWLER_H

#include <vector>
#include <string>

enum class Rarity
{
    TrophyRoad, // common
    Rare,       // rare
    SuperRare,  // super_rare
    Epic,       // epic
    Mythic,     // mega_epic
    Legendary   // legendary
};

/*
enum class Speed
{
    VerySlow, // 0
    Slow, // 1
    Normal, // 2
    Fast, // 3
    VeryFast // 4
};
*/

class Brawler
{
public:
    std::string tid;
    std::string name;
    std::string codename;
    std::string description;
    std::string weaponName;
    std::string ultimateName;
    std::string weaponDescription;
    std::string ultimateDescription;
    Rarity rarity;
    std::string weaponSkill;
    std::string ultimateSkill;
    int speed;
    int health;
    std::string iconSWF;
    std::string icon;
    std::string pet;
    int scale;
    int weaponRange;
    int ultimateRange;
    int weaponReloadTime;
    int ultimateReloadTime;
    int weaponAmmoCount;
    int ultimateAmmoCount;
    int weaponDamage;
    int ultimateDamage;
    int attackSpread;
    int ultimateSpread;
    int weaponProjectileCount;
    int ultimateProjectileCount;
    int weaponTimeBetweenAttacks;
    int ultimateTimeBetweenAttacks;
    int attackDuration;
    int ultimateAttackDuration;
    int ultimateRechargeTime;

    Brawler(const std::string &tid, const std::string &name, const std::string &codename, const std::string &description,
            const std::string &weaponName, const std::string &ultimateName,
            const Rarity rarity,
            const std::string &weaponSkill, const std::string &weaponDescription, const std::string &ultimateDescription,
            const std::string &ultimateSkill,
            const int speed, const int health, const std::string &iconSWF, const std::string &icon, const std::string &pet,
            const int scale, const int range, const int weaponReloadTime, const int ultimateReloadTime, const int weaponAmmoCount, const int ultimateAmmoCount,
            const int weaponDamage, const int ultimateDamage, const int attackSpread, const int ultimateSpread, const int ultimateRange,
            const int weaponProjectileCount, const int ultimateProjectileCount, const int weaponTimeBetweenAttacks, const int ultimateTimeBetweenAttacks,
            const int attackDuration, const int ultimateAttackDuration)
        : tid(tid), name(name), codename(codename), description(description), rarity(rarity), weaponDescription(weaponDescription), ultimateDescription(ultimateDescription), 
          weaponName(weaponName), ultimateName(ultimateName), weaponSkill(weaponSkill), ultimateSkill(ultimateSkill),
          speed(speed), health(health), iconSWF(iconSWF), icon(icon), pet(pet),
          scale(scale), weaponRange(range), ultimateRange(ultimateRange), weaponReloadTime(weaponReloadTime), ultimateReloadTime(ultimateReloadTime),
          weaponAmmoCount(weaponAmmoCount), ultimateAmmoCount(ultimateAmmoCount), weaponDamage(weaponDamage), ultimateDamage(ultimateDamage), attackSpread(attackSpread),
          ultimateSpread(ultimateSpread), weaponProjectileCount(weaponProjectileCount), ultimateProjectileCount(ultimateProjectileCount), weaponTimeBetweenAttacks(weaponTimeBetweenAttacks), ultimateTimeBetweenAttacks(ultimateTimeBetweenAttacks), attackDuration(attackDuration), ultimateAttackDuration(ultimateAttackDuration), ultimateRechargeTime(0) {};
    Brawler() : tid(""), name(""), codename(""), description(""), weaponName(""), ultimateName(""), rarity(Rarity::TrophyRoad), weaponDescription(""), ultimateDescription(""), weaponSkill(""), ultimateSkill(""), speed(0), health(0), iconSWF(""), icon(""), pet(""), scale(0), weaponRange(0), ultimateRange(0), weaponReloadTime(0), ultimateReloadTime(0), weaponAmmoCount(0), ultimateAmmoCount(0), weaponDamage(0), ultimateDamage(0), attackSpread(0), ultimateSpread(0), weaponProjectileCount(0), ultimateProjectileCount(0), weaponTimeBetweenAttacks(0), ultimateTimeBetweenAttacks(0), attackDuration(0), ultimateAttackDuration(0) {}
};
#endif
