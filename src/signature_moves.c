#include "global.h"
#include "battle.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "signature_moves.h"

static const struct SignatureMoveEntry sSignatureMoves[] =
{
    { SPECIES_SMEARGLE,   MOVE_TACKLE,        0, 0, FALSE, SIG_TYPING_NONE, SIG_PWRFORMULA_NORMAL,     SIG_ATKSTAT_NORMAL, SIG_EFFECT_ATK_PLUS_1, SIG_MULTI_ALWAYS_2, SIG_TYPE_NONE },
    { SPECIES_SCIZOR,     MOVE_TACKLE, 100, 0, FALSE, SIG_TYPING_RESISTANCE, SIG_PWRFORMULA_NORMAL,     SIG_ATKSTAT_NORMAL, SIG_EFFECT_NONE, SIG_MULTI_NONE, SIG_TYPE_GROUND },
    { SPECIES_TYPHLOSION, MOVE_ERUPTION,      0, 1, FALSE, SIG_TYPING_NONE, SIG_PWRFORMULA_REVERSAL,   SIG_ATKSTAT_NORMAL, SIG_EFFECT_NONE, SIG_MULTI_NONE, SIG_TYPE_NONE },
    { SPECIES_VENUSAUR,   MOVE_CHLOROBLAST,   0, 0, FALSE, SIG_TYPING_NONE, SIG_PWRFORMULA_NORMAL,     SIG_ATKSTAT_NORMAL, SIG_EFFECT_SUN, SIG_MULTI_NONE, SIG_TYPE_NONE },
};

const struct SignatureMoveEntry *GetSignatureMoveEntry(u32 species, u32 move)
{
    for (int i = 0; i < ARRAY_COUNT(sSignatureMoves); i++)
    {
        if (sSignatureMoves[i].species == species
         && sSignatureMoves[i].move == move)
            return &sSignatureMoves[i];
    }
    return NULL;
}
