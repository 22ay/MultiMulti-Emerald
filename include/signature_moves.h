#ifndef GUARD_SIGNATURE_MOVES_H
#define GUARD_SIGNATURE_MOVES_H

#include "global.h"

enum SignaturePowerFormula
{
    SIG_PWRFORMULA_NORMAL,     // No override
    SIG_PWRFORMULA_REVERSAL,   // Reversal / Flail formula
    SIG_PWRFORMULA_WATERSPOUT, // Water Spout / Eruption formula
};

enum SignatureAttackStatMode
{
    SIG_ATKSTAT_NORMAL,              // Use Attack or Sp.Atk normally
    SIG_ATKSTAT_DEFENSIVE,           // Use Defense or Sp.Def
    SIG_ATKSTAT_HIGHEST_OFFENSIVE,   // Use whichever is higher: Atk or SpAtk
    SIG_ATKSTAT_SPEED,               // Use Speed
};

enum SignatureEnvironmentEffect
{
    SIG_ENV_NONE,
    SIG_ENV_SUN,
    SIG_ENV_RAIN,
    SIG_ENV_SAND,
    SIG_ENV_SNOW,
    SIG_ENV_ELECTRIC_TERRAIN,
    SIG_ENV_GRASSY_TERRAIN,
    SIG_ENV_PSYCHIC_TERRAIN,
    SIG_ENV_MISTY_TERRAIN,
    SIG_ENV_GRAVITY,
    SIG_ENV_TRICK_ROOM,
    SIG_ENV_INVERSE_ROOM,
    SIG_ENV_TAILWIND
};

enum SignatureStatBoostMode
{
    SIG_STATBOOST_NONE,
    SIG_STATBOOST_ATK_PLUS_1,
    SIG_STATBOOST_DEF_PLUS_1,
    SIG_STATBOOST_SPD_PLUS_1,
    SIG_STATBOOST_SPATK_PLUS_1,
    SIG_STATBOOST_SPDEF_PLUS_1,
};

struct SignatureMoveEntry
{
    u16 species;
    u16 move;
    u16 basePower;
    s8 priority;
    bool8 ignoreTypeImmunity; 
    bool8 alwaysCrit;
    bool8 restoreHP;
    enum SignaturePowerFormula powerFormula; 
    enum SignatureAttackStatMode attackStatMode;
    enum SignatureEnvironmentEffect environmentEffect;
    enum SignatureStatBoostMode statBoostMode;
};

// Existing public APIs
u16 GetSignatureBasePower(u8 attacker, u16 move, u16 basePower);
s8 GetSignaturePriority(u16 species, u16 move);
bool8 IsSignatureMove(u16 species, u16 move);
const struct SignatureMoveEntry *GetSignatureMoveEntry(u16 species, u16 move);

#endif // GUARD_SIGNATURE_MOVES_H