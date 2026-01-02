#ifndef GUARD_SIGNATURE_MOVES_H
#define GUARD_SIGNATURE_MOVES_H

#include "global.h"

// Main function that modifies base power for signature moves
u16 GetSignatureBasePower(u8 attacker, u16 move, u16 basePower);
s8 GetSignaturePriority(u16 species, u16 move);
bool8 IsSignatureMove(u16 species, u16 move);

#endif // GUARD_SIGNATURE_MOVES_H