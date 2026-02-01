#ifndef GUARD_SIGNATURE_MOVES_H
#define GUARD_SIGNATURE_MOVES_H

#include "global.h"

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
};

struct SignatureMoveEntry
{
    u16 species;
    u16 move;
    u16 basePower;
    s8 priority;
    bool8 useReversalFormula;
    bool8 useHighestOffensiveStat;
    bool8 ignoreTypeImmunity; 
    bool8 alwaysCrit; 
    bool8 useDefensiveStatInstead; 
    bool8 useWaterSpoutFormula;
    enum SignatureEnvironmentEffect environmentEffect;
};

// Existing public APIs
u16 GetSignatureBasePower(u8 attacker, u16 move, u16 basePower);
s8 GetSignaturePriority(u16 species, u16 move);
bool8 IsSignatureMove(u16 species, u16 move);
const struct SignatureMoveEntry *GetSignatureMoveEntry(u16 species, u16 move);

#endif // GUARD_SIGNATURE_MOVES_H