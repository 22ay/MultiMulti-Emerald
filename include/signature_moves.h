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

enum SignatureTypeIgnore {
    SIG_IGNORE_NONE,
    SIG_IGNORE_IMMUNITY,
    SIG_IGNORE_RESISTANCE,
};

enum SignatureTypeChange
{
    SIG_TYPE_NONE,
    SIG_TYPE_NORMAL,
    SIG_TYPE_FIGHTING,
    SIG_TYPE_FLYING,
    SIG_TYPE_POISON,
    SIG_TYPE_GROUND,
    SIG_TYPE_ROCK,
    SIG_TYPE_BUG,
    SIG_TYPE_GHOST,
    SIG_TYPE_STEEL,
    SIG_TYPE_FIRE,
    SIG_TYPE_WATER,
    SIG_TYPE_GRASS,
    SIG_TYPE_ELECTRIC,
    SIG_TYPE_PSYCHIC,
    SIG_TYPE_ICE,
    SIG_TYPE_DRAGON,
    SIG_TYPE_DARK,
    SIG_TYPE_FAIRY,
};

struct SignatureMoveEntry
{
    u32 species;
    u32 move;
    u32 basePower;
    s32 priority;
    bool32 alwaysCrit;
    bool32 alwaysHit;
    enum SignatureTypeIgnore typeIgnore;
    enum SignaturePowerFormula powerFormula;
    enum SignatureAttackStatMode attackStatMode;
    enum SignatureEffect addedEffect;
    enum SignatureMultiHitMode multiHit;
    enum SignatureTypeChange typeChange;
};

const struct SignatureMoveEntry *GetSignatureMoveEntry(u32 species, u32 move);
u32 GetSignatureBasePower(u32 battler, u32 move, u32 basePower);
s32 GetSignaturePriority(u32 species, u32 move);


#endif // GUARD_SIGNATURE_MOVES_H