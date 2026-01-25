#ifndef GUARD_SIGNATURE_MOVES_H
#define GUARD_SIGNATURE_MOVES_H

#include "global.h"

struct SignatureMoveEntry
{
    u16 species;
    u16 move;
    u16 basePower;
    s8 priority;
    bool8 useReversalFormula;
    bool8 useHighestOffensiveStat;   // NEW FLAG
};

// Existing public APIs
u16 GetSignatureBasePower(u8 attacker, u16 move, u16 basePower);
s8 GetSignaturePriority(u16 species, u16 move);
bool8 IsSignatureMove(u16 species, u16 move);
const struct SignatureMoveEntry *GetSignatureMoveEntry(u16 species, u16 move);

#endif // GUARD_SIGNATURE_MOVES_H