#include "global.h"
#include "battle.h"
#include "constants/species.h"
#include "constants/moves.h"

static const struct SignatureMoveEntry sSignatureMoves[] =
{
    { SPECIES_SMEARGLE, MOVE_DIG, 0, 0, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, SIG_ENV_NONE },
    { SPECIES_SCIZOR, MOVE_BULLET_PUNCH, 60,  0, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, SIG_ENV_NONE },
    { SPECIES_TYPHLOSION, MOVE_ERUPTION, 0, 1, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, SIG_ENV_NONE },
    { SPECIES_VENUSAUR, MOVE_CHLOROBLAST, 0, 0, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, SIG_ENV_SUN },
};

u16 GetSignatureBasePower(u8 attacker, u16 move, u16 basePower)
{
    u16 species = gBattleMons[attacker].species;
    u16 hp = gBattleMons[attacker].hp;
    u16 maxHp = gBattleMons[attacker].maxHP;

    for (u32 i = 0; i < ARRAY_COUNT(sSignatureMoves); i++)
    {
        if (sSignatureMoves[i].species == species
         && sSignatureMoves[i].move == move)
        {
            // If using Reversal-style scaling
            if (sSignatureMoves[i].useReversalFormula)
            {
                // Reversal formula:
                // BP = 20, 40, 80, 100, 150, or 200 depending on HP%
                u32 hpPercent = (hp * 100) / maxHp;

                if (hpPercent <= 4)
                    return 200;
                else if (hpPercent <= 10)
                    return 150;
                else if (hpPercent <= 20)
                    return 100;
                else if (hpPercent <= 35)
                    return 80;
                else if (hpPercent <= 70)
                    return 40;
                else
                    return 20;
            }
            // Water Spout-style scaling
            if (sSignatureMoves[i].useWaterSpoutFormula)
            {
                // Formula: BP = basePower * currentHP / maxHP
                // Minimum 1
                u32 scaled = (150 * hp) / maxHp;
                if (scaled < 1)
                    scaled = 1;
                return scaled;
            }

            // Otherwise use static override
            if (sSignatureMoves[i].basePower != 0)
                return sSignatureMoves[i].basePower;
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

bool8 IsSignatureMove(u16 species, u16 move)
{
    for (u32 i = 0; i < ARRAY_COUNT(sSignatureMoves); i++)
    {
        if (sSignatureMoves[i].species == species
         && sSignatureMoves[i].move == move)
            return TRUE;
    }

    return FALSE;
}