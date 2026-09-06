#include "global.h"
#include "battle.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "signature_moves.h"

/*  .species = The species of the Pokemon

    .move = The signature move

    .basePower = The new base power of the move. Leaving blank or 0 will default to vanilla base power

    .priority = The new priority of the move. Leaving blank or 0 will default to vanilla priority

    .alwaysCrit = If not blank or 0, the move will always crit, barring crit-blocking abilities

    .alwaysHit = If not blank or 0, the move will always hit

    .typeIgnore = If not blank or SIG_IGNORE_NONE, the move will either ignore type immunity (SIG_IGNORE_IMMUNITY) or type resistance (SIG_IGNORE_RESISTANCE)

    .powerFormula = If not blank or SIG_PWRFORMULA_NONE, the move will use different formulas for base power calculations (think Gyro Ball or Bolt Beak); look at signature_moves.h for
    all the formulas

    .attackStatMode = If not blank or SIG_ATKSTAT_NORMAL, the move will use different stats for damage calculations 
    (SIG_ATKSTAT_DEFENSIVE uses Defense or Special Defense, 
    SIG_ATKSTAT_HIGHEST_OFFENSIVE uses the higher of Attack and Special Attack
    and SIG_ATKSTAT_SPEED uses Speed)

    .addedEffect = If not blank or SIG_EFFECT_NONE, the move will trigger an additional effect (think an attack boost or summoning rain)
    If the move already has an additional effect, this signature effect will go after it. Look at signature_moves.h for all the effects

    .multiHit = If not blank or SIG_MULTI_NONE, the move will hit multiple times
    (SIG_MULTI_ALWAYS_2 hits twice, 
    SIG_MULTI_ALWAYS_3 hit thrice, 
    and SIG_MULTI_ALWAYS_5 hits five times)

    .typeChange = If not blank or SIG_TYPE_NONE, the move will change type depending on the macro.
    Look at signature_moves.h for the types
*/

static const struct SignatureMoveEntry sSignatureMoves[] =
{
    { SPECIES_SMEARGLE,   MOVE_TACKLE,        0, 0, FALSE, FALSE, SIG_IGNORE_NONE, SIG_PWRFORMULA_NORMAL,     SIG_ATKSTAT_NORMAL, SIG_EFFECT_ATK_PLUS_1, SIG_MULTI_ALWAYS_2, SIG_TYPE_NONE },
    { SPECIES_SCIZOR,     MOVE_TACKLE,        100, 0, FALSE, FALSE, SIG_IGNORE_RESISTANCE, SIG_PWRFORMULA_NORMAL,     SIG_ATKSTAT_NORMAL, SIG_EFFECT_NONE, SIG_MULTI_NONE, SIG_TYPE_GROUND },
    { SPECIES_TYPHLOSION, MOVE_ERUPTION,      0, 1, FALSE, FALSE, SIG_IGNORE_NONE, SIG_PWRFORMULA_REVERSAL,   SIG_ATKSTAT_NORMAL, SIG_EFFECT_NONE, SIG_MULTI_NONE, SIG_TYPE_NONE },
    { SPECIES_VENUSAUR,   MOVE_CHLOROBLAST,   0, 0, FALSE, FALSE, SIG_IGNORE_NONE, SIG_PWRFORMULA_NORMAL,     SIG_ATKSTAT_NORMAL, SIG_EFFECT_SUN, SIG_MULTI_NONE, SIG_TYPE_NONE },
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
