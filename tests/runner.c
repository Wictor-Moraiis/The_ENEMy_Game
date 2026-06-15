#include "test_macros.h"

int tests_run = 0;
int tests_passed = 0;
int tests_failed = 0;

// Protótipos das suítes de teste
void run_question_tests();
void run_player_tests();
void run_battle_tests();
void run_scenario_tests();
void run_character_tests();

int main() {
    printf("=======================================\n");
    printf("   THE ENEMy GAME - TESTING SUITE\n");
    printf("=======================================\n\n");

    run_question_tests();
    run_player_tests();
    run_battle_tests();
    run_scenario_tests();
    run_character_tests();

    printf("\n=======================================\n");
    printf("TEST SUMMARY:\n");
    printf("  Total Run:    %d\n", tests_run);
    printf("  Passed:       %d\n", tests_passed);
    printf("  Failed:       %d\n", tests_failed);
    printf("=======================================\n");

    return (tests_failed == 0) ? 0 : 1;
}
