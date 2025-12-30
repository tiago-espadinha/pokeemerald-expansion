#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("All Unown Prime forms have Power of Words as their ability")
{
    u16 species;
    u32 i;

    for (i = SPECIES_UNOWN_PRIME; i <= SPECIES_UNOWN_PRIME_QUESTION; i++)
        PARAMETRIZE { species = i; }

    GIVEN {
        PLAYER(species);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(GetAbilityBySpecies(species, 0), ABILITY_POWER_OF_WORDS);
    }
}
