#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Power of Words transforms Unown into its Prime form on switch in")
{
    GIVEN {
        PLAYER(SPECIES_UNOWN_PRIME) { Ability(ABILITY_POWER_OF_WORDS); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { ; }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_POWER_OF_WORDS);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, player);
        MESSAGE("Unown transformed!");
    } THEN {
        EXPECT_EQ(player->species, SPECIES_UNOWN_PRIME_FINAL);
    }
}

SINGLE_BATTLE_TEST("Power of Words can't be suppressed by Neutralizing Gas")
{
    GIVEN {
        PLAYER(SPECIES_UNOWN_PRIME) { Ability(ABILITY_POWER_OF_WORDS); }
        OPPONENT(SPECIES_KOFFING) { Ability(ABILITY_NEUTRALIZING_GAS); }
    } WHEN {
        TURN { ; }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_NEUTRALIZING_GAS);
        ABILITY_POPUP(player, ABILITY_POWER_OF_WORDS);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, player);
        MESSAGE("Unown transformed!");
    } THEN {
        EXPECT_EQ(player->species, SPECIES_UNOWN_PRIME_FINAL);
    }
}