#ifndef GUARD_SIGNATURE_MOVES_H
#define GUARD_SIGNATURE_MOVES_H

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
    SIG_PWRFORMULA_BRINE,
};

enum SignatureAttackStatMode
{
    SIG_ATKSTAT_NORMAL,           
    SIG_ATKSTAT_DEFENSIVE,        
    SIG_ATKSTAT_HIGHEST_OFFENSIVE,
    SIG_ATKSTAT_SPEED,            
};

enum SignatureEffect
{
    SIG_EFFECT_NONE,
    SIG_EFFECT_SUN,
    SIG_EFFECT_RAIN,
    SIG_EFFECT_SAND,
    SIG_EFFECT_SNOW,
    SIG_EFFECT_FOG,
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
    SIG_EFFECT_REFLECT,
    SIG_EFFECT_LIGHT_SCREEN,
    SIG_EFFECT_AURORA_VEIL,
    SIG_EFFECT_ATK_PLUS_1,
    SIG_EFFECT_DEF_PLUS_1,
    SIG_EFFECT_SPD_PLUS_1,
    SIG_EFFECT_SPATK_PLUS_1,
    SIG_EFFECT_SPDEF_PLUS_1,
    SIG_EFFECT_RESTORE_HP,
};

enum SignatureMultiHitMode {
    SIG_MULTI_NONE,
    SIG_MULTI_ALWAYS_2,
    SIG_MULTI_ALWAYS_3,
    SIG_MULTI_ALWAYS_5,
};

enum SignatureTypeMultiplier {
    SIG_TYPING_NONE,
    SIG_TYPING_IMMUNITY,
    SIG_TYPING_RESISTANCE,
};

struct SignatureMoveEntry
{
    u32 species;
    u32 move;
    u32 basePower;
    s32 priority;
    bool32 alwaysCrit;
    enum SignatureTypeMultiplier typeMultiplier;
    enum SignaturePowerFormula powerFormula;
    enum SignatureAttackStatMode attackStatMode;
    enum SignatureEffect addedEffect;
    enum SignatureMultiHitMode multiHit;
};

const struct SignatureMoveEntry *GetSignatureMoveEntry(u16 species, u16 move);
u32 GetSignatureBasePower(u32 battler, u32 move, u32 basePower);
s32 GetSignaturePriority(u32 species, u32 move);


#endif // GUARD_SIGNATURE_MOVES_H