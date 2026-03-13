#ifndef GUARD_SIGNATURE_MOVES_H
#define GUARD_SIGNATURE_MOVES_H

#include "global.h"

enum SignaturePowerFormula
{
    SIG_PWRFORMULA_NORMAL,
    SIG_PWRFORMULA_REVERSAL,
    SIG_PWRFORMULA_WATERSPOUT,
    SIG_PWRFORMULA_ELECTRO_BALL,
    SIG_PWRFORMULA_GYRO_BALL,
    SIG_PWRFORMULA_HEAVY_SLAM,
    SIG_PWRFORMULA_LOW_KICK,
    SIG_PWRFORMULA_BOLT_BEAK,
};

enum SignatureAttackStatMode
{
    SIG_ATKSTAT_NORMAL,              // Use Attack or Sp.Atk normally
    SIG_ATKSTAT_DEFENSIVE,           // Use Defense or Sp.Def
    SIG_ATKSTAT_HIGHEST_OFFENSIVE,   // Use whichever is higher: Atk or SpAtk
    SIG_ATKSTAT_SPEED,               // Use Speed
};

enum SignatureEffect
{
    SIG_EFFECT_NONE = 0,
    SIG_EFFECT_SUN,
    SIG_EFFECT_RAIN,
    SIG_EFFECT_SAND,
    SIG_EFFECT_SNOW,
    SIG_EFFECT_MISTY_TERRAIN,
    SIG_EFFECT_GRASSY_TERRAIN,
    SIG_EFFECT_ELECTRIC_TERRAIN,
    SIG_EFFECT_PSYCHIC_TERRAIN,
    SIG_EFFECT_GRAVITY,
    SIG_EFFECT_TRICK_ROOM,
    SIG_EFFECT_INVERSE_ROOM,
    SIG_EFFECT_TAILWIND,
    SIG_EFFECT_RAINBOW,
    SIG_EFFECT_SEA_OF_FIRE,
    SIG_EFFECT_SWAMP,
    SIG_EFFECT_ATK_PLUS_1,
    SIG_EFFECT_DEF_PLUS_1,
    SIG_EFFECT_SPD_PLUS_1,
    SIG_EFFECT_SPATK_PLUS_1,
    SIG_EFFECT_SPDEF_PLUS_1,
    SIG_EFFECT_RESTORE_HP,
};

struct SignatureMoveEntry
{
    u16 species;
    u16 move;
    u16 basePower;
    s8 priority;
    bool8 ignoreTypeImmunity;
    bool8 alwaysCrit;
    enum SignaturePowerFormula powerFormula;
    enum SignatureAttackStatMode attackStatMode;
    enum SignatureEffect addedEffect;
};

// Existing public APIs
u16 GetSignatureBasePower(u8 attacker, u16 move, u16 basePower);
s8 GetSignaturePriority(u16 species, u16 move);
bool8 IsSignatureMove(u16 species, u16 move);
const struct SignatureMoveEntry *GetSignatureMoveEntry(u16 species, u16 move);

#endif // GUARD_SIGNATURE_MOVES_H