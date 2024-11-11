#ifndef BRAWLER_H
#define BRAWLER_H

#include <vector>
#include <string>

enum class Rarity
{
    Rare,
    SuperRare,
    Epic,
    Mythic,
    Legendary
};

enum class Speed
{
    VerySlow, // 0
    Slow, // 1
    Normal, // 2
    Fast, // 3
    VeryFast // 4
};

class Projectile
{
public:
    std::string name;

    Projectile(const std::string &projectileName) : name(projectileName) {}
};

class Brawler
{
public:
    std::string name;
    std::string codename;
    Rarity rarity;
    std::string attackName;
    std::string attackDescription;
    std::string ultiName;
    std::string ultiDescription;
    Speed speed;
    int health;
    std::string icon;
    float scale;
    float range;
    float reloadTime;
    int ammoCount;
    int damage;
    float attackSpread;
    float superSpread;
    int projectileCount;
    float timeBetweenAttacks;
    float attackDuration;
    Projectile projectile;

    Brawler(const std::string &brawlerName, const std::string &brawlerCodename, Rarity brawlerRarity,
            const std::string &brawlerAttackName, const std::string &brawlerAttackDescription,
            const std::string &brawlerUltiName, const std::string &brawlerUltiDescription,
            Speed brawlerSpeed, int brawlerHealth, const std::string &brawlerIcon,
            float brawlerScale, float brawlerRange, float brawlerReloadTime, int brawlerAmmoCount,
            int brawlerDamage, float brawlerAttackSpread, float brawlerSuperSpread,
            int brawlerProjectileCount, float brawlerTimeBetweenAttacks, float brawlerAttackDuration,
            const Projectile &brawlerProjectile)
        : name(brawlerName), codename(brawlerCodename), rarity(brawlerRarity),
          attackName(brawlerAttackName), attackDescription(brawlerAttackDescription),
          ultiName(brawlerUltiName), ultiDescription(brawlerUltiDescription),
          speed(brawlerSpeed), health(brawlerHealth), icon(brawlerIcon),
          scale(brawlerScale), range(brawlerRange), reloadTime(brawlerReloadTime),
          ammoCount(brawlerAmmoCount), damage(brawlerDamage), attackSpread(brawlerAttackSpread),
          superSpread(brawlerSuperSpread), projectileCount(brawlerProjectileCount),
          timeBetweenAttacks(brawlerTimeBetweenAttacks), attackDuration(brawlerAttackDuration),
          projectile(brawlerProjectile) {}
};

#endif