#include "global.h"
#include "battle.h"
#include "constants/species.h"
#include "constants/moves.h"

static const struct SignatureMoveEntry sSignatureMoves[] =
{
    { SPECIES_SMEARGLE,   MOVE_TACKLE,        0, 0, FALSE, FALSE, SIG_PWRFORMULA_NORMAL,     SIG_ATKSTAT_NORMAL, SIG_EFFECT_ATK_PLUS_1, SIG_MULTI_ALWAYS_2 },
    { SPECIES_SCIZOR,     MOVE_BULLET_PUNCH, 60, 0, FALSE, FALSE, SIG_PWRFORMULA_NORMAL,     SIG_ATKSTAT_NORMAL, SIG_EFFECT_NONE, SIG_MULTI_NONE },
    { SPECIES_TYPHLOSION, MOVE_ERUPTION,      0, 1, FALSE, FALSE, SIG_PWRFORMULA_REVERSAL,   SIG_ATKSTAT_NORMAL, SIG_EFFECT_NONE, SIG_MULTI_NONE },
    { SPECIES_VENUSAUR,   MOVE_CHLOROBLAST,   0, 0, FALSE, FALSE, SIG_PWRFORMULA_NORMAL,     SIG_ATKSTAT_NORMAL, SIG_EFFECT_SUN, SIG_MULTI_NONE },
};

u16 GetSignatureBasePower(u8 attacker, u16 move, u16 basePower)
{
    u16 species = gBattleMons[attacker].species;
    u16 hp      = gBattleMons[attacker].hp;
    u16 maxHp   = gBattleMons[attacker].maxHP;

    for (u32 i = 0; i < ARRAY_COUNT(sSignatureMoves); i++)
    {
        const struct SignatureMoveEntry *entry = &sSignatureMoves[i];

        if (entry->species == species && entry->move == move)
        {
            switch (entry->powerFormula)
            {
                case SIG_PWRFORMULA_REVERSAL:
                {
                    u32 hpPercent = (hp * 100) / maxHp;

                    if (hpPercent <= 4)  return 200;
                    if (hpPercent <= 10) return 150;
                    if (hpPercent <= 20) return 100;
                    if (hpPercent <= 35) return 80;
                    if (hpPercent <= 70) return 40;
                    return 20;
                }

                case SIG_PWRFORMULA_WATERSPOUT:
                {
                    u32 scaled = (150 * hp) / maxHp;
                    if (scaled < 1)
                        scaled = 1;
                    return scaled;
                }

                case SIG_PWRFORMULA_ELECTRO_BALL:
                {
                    u32 atkSpeed = GetBattlerTotalSpeedStat(gBattlerAttacker);
                    u32 defSpeed = GetBattlerTotalSpeedStat(gBattlerTarget);

                    if (defSpeed == 0)
                        return 150;

                    u32 ratio = (atkSpeed * 100) / defSpeed;

                    if (ratio >= 400) return 150;
                    if (ratio >= 300) return 120;
                    if (ratio >= 200) return 80;
                    if (ratio >= 150) return 60;
                    return 40;
                }

                case SIG_PWRFORMULA_GYRO_BALL:
                {
                    u32 atkSpeed = GetBattlerTotalSpeedStat(gBattlerAttacker);
                    u32 defSpeed = GetBattlerTotalSpeedStat(gBattlerTarget);

                    if (atkSpeed == 0)
                        return 1;

                    u32 bp = (25 * defSpeed) / atkSpeed + 1;
                    if (bp > 150)
                        bp = 150;

                    return bp;
                }

                case SIG_PWRFORMULA_HEAVY_SLAM:
                {
                    u32 atkW = GetBattlerWeight(gBattlerAttacker);
                    u32 defW = GetBattlerWeight(gBattlerTarget);

                    if (atkW > defW * 5) return 120;
                    if (atkW > defW * 4) return 100;
                    if (atkW > defW * 3) return 80;
                    if (atkW > defW * 2) return 60;
                    return 40;
                }

                case SIG_PWRFORMULA_LOW_KICK:
                {
                    u32 w = GetBattlerWeight(gBattlerTarget);

                    if (w >= 2000) return 120;
                    if (w >= 1000) return 100;
                    if (w >= 500)  return 80;
                    if (w >= 250)  return 60;
                    if (w >= 100)  return 40;
                    return 20;
                }

                case SIG_PWRFORMULA_BOLT_BEAK:
                {
                    u16 bp = entry->basePower ? entry->basePower : basePower;

                    if (!HasBattlerActedThisTurn(gBattlerTarget)
                    || gDisableStructs[gBattlerTarget].isFirstTurn == 2)
                    {
                        return bp * 2;
                    }
                    return bp;
                }

                case SIG_PWRFORMULA_BRINE:
                {
                    u16 bp = entry->basePower ? entry->basePower : basePower;

                    if (gBattleMons[gBattlerTarget].hp <= (gBattleMons[gBattlerTarget].maxHP/2))
                    {
                        return bp * 2;
                    }
                    return bp;
                }

                case SIG_PWRFORMULA_NORMAL:
                default:
                    break;
            }

            if (entry->basePower != 0)
                return entry->basePower;
        }
    }

    return basePower;
}

s8 GetSignaturePriority(u16 species, u16 move)
{
    for (u32 i = 0; i < ARRAY_COUNT(sSignatureMoves); i++)
    {
        if (sSignatureMoves[i].species == species
         && sSignatureMoves[i].move == move)
        {
            return sSignatureMoves[i].priority;
        }
    }

    return 0; // default priority
}

const struct SignatureMoveEntry *GetSignatureMoveEntry(u16 species, u16 move)
{
    for (int i = 0; i < ARRAY_COUNT(sSignatureMoves); i++)
    {
        if (sSignatureMoves[i].species == species
         && sSignatureMoves[i].move == move)
            return &sSignatureMoves[i];
    }
    return NULL;
}
