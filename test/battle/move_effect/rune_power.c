#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Rune Power uses a super-effective type against target species")
{
    u16 species;

    // Choose a few species with clear super-effective types
    PARAMETRIZE { species = SPECIES_BULBASAUR; } // Grass/Poison -> Fire is super
    PARAMETRIZE { species = SPECIES_CHARMANDER; } // Fire -> Water is super
    PARAMETRIZE { species = SPECIES_SQUIRTLE; } // Water -> Electric/Grass
    PARAMETRIZE { species = SPECIES_GOLEM; } // Rock/Ground -> Water/Grass/Ice

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        // no actions; check the party-level effectiveness helper
    } THEN {
        uq4_12_t mod = CalcPartyMonTypeEffectivenessMultiplier(MOVE_RUNE_POWER, species, ABILITY_NONE);
        EXPECT_TRUE(mod >= UQ_4_12(2.0));
    }
}
SINGLE_BATTLE_TEST("Rune Power displays message when type changes")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_BULBASAUR);
    } WHEN {
        TURN { MOVE(player, MOVE_RUNE_POWER); }
    } SCENE {
        MESSAGE("Rune Power changed to Fire type!");
    }
}