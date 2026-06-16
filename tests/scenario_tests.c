#include "test_macros.h"
#include "scenario.h"
#include <string.h>

void test_scenario_initialization() {
    Scenario s = CreateScenario();
    ASSERT(s.actionCount == 0, "Scenario should start with 0 actions");
    ASSERT(s.completed == false, "Scenario should not be completed initially");
}

void test_scenario_add_actions() {
    Scenario s = CreateScenario();
    AddSpeak(&s, CHAR_VOZ_GRAVE, "Hello Test");
    
    ASSERT(s.actionCount == 1, "Should have 1 action");
    ASSERT(s.actions[0].type == ACTION_SPEAK, "First action should be Speak");
    ASSERT(strcmp(s.actions[0].data.speak.text, "Hello Test") == 0, "Text should match");
}

void test_scenario_add_question() {
    Scenario s = CreateScenario();
    const char* opts[] = {"A", "B", "C", "D"};
    AddQuestion(&s, "Test Q?", opts, 2, 1);
    
    ASSERT(s.actionCount == 1, "Should have 1 action");
    ASSERT(s.actions[0].type == ACTION_QUESTION, "Action should be Question");
    ASSERT(s.actions[0].data.question.correctIndex == 2, "Correct index should match");
}

void run_scenario_tests() {
    RUN_TEST(test_scenario_initialization);
    RUN_TEST(test_scenario_add_actions);
    RUN_TEST(test_scenario_add_question);
}
