#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("GetSupereffectiveTypeAgainstSpecies returns a type that is actually super effective")
{
    u16 species;

    PARAMETRIZE { species = SPECIES_CHARMANDER; }
    PARAMETRIZE { species = SPECIES_GEODUDE; }
    PARAMETRIZE { species = SPECIES_VENUSAUR; }
    PARAMETRIZE { species = SPECIES_WAILMER; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        // No actions required; we only call the helper
    } THEN {
        u8 atkType = GetSupereffectiveTypeAgainstSpecies(species);
        uq4_12_t mod = GetTypeModifier(atkType, GetSpeciesType(species, 0));
        if (GetSpeciesType(species, 1) != GetSpeciesType(species, 0) && GetSpeciesType(species, 1) != TYPE_MYSTERY)
            mod = uq4_12_multiply(mod, GetTypeModifier(atkType, GetSpeciesType(species, 1)));

        /* Either we returned TYPE_MYSTERY (meaning no super-effective type was found),
         * or the returned type truly is super-effective. */
        EXPECT_TRUE(atkType == TYPE_MYSTERY || mod >= UQ_4_12(2.0));
    }
}

SINGLE_BATTLE_TEST("GetSupereffectiveTypeAgainstSpecies randomizes among top-effective types")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        // No actions required; we only call the helper
    } THEN {
        /* Bulbasaur (GRASS/POISON) has multiple equally-effective counters
         * (Fire, Flying, Psychic, Ice). Ensure the helper returns values
         * among those and that it can return multiple different types over
         * repeated invocations. */
        SeedRng(123456);

        u8 seen[NUMBER_OF_MON_TYPES] = {0};
        int distinct = 0;

        for (int i = 0; i < 20; i++)
        {
            u8 t = GetSupereffectiveTypeAgainstSpecies(SPECIES_BULBASAUR);
            /* Confirm result is super-effective */
            uq4_12_t mod = GetTypeModifier(t, GetSpeciesType(SPECIES_BULBASAUR, 0));
            if (GetSpeciesType(SPECIES_BULBASAUR, 1) != GetSpeciesType(SPECIES_BULBASAUR, 0) && GetSpeciesType(SPECIES_BULBASAUR, 1) != TYPE_MYSTERY)
                mod = uq4_12_multiply(mod, GetTypeModifier(t, GetSpeciesType(SPECIES_BULBASAUR, 1)));

            EXPECT_TRUE(t == TYPE_MYSTERY || mod >= UQ_4_12(2.0));

            if (t != TYPE_MYSTERY && !seen[t])
            {
                seen[t] = 1;
                distinct++;
            }
        }

        /* With a deterministic seed the RNG should hit at least two distinct
         * top-effective types within 20 samples. */
        EXPECT_TRUE(distinct >= 2);
    }
}
