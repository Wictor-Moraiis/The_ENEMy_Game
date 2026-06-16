#ifndef TEST_MACROS_H
#define TEST_MACROS_H

#include <stdio.h>
#include <stdbool.h>

extern int tests_run;
extern int tests_passed;
extern int tests_failed;

#define ASSERT(condition, message) \
    do { \
        tests_run++; \
        if (!(condition)) { \
            printf("  [FAIL] %s:%d: %s\n", __FILE__, __LINE__, message); \
            tests_failed++; \
            return; \
        } else { \
            tests_passed++; \
        } \
    } while (0)

#define RUN_TEST(test_func) \
    do { \
        printf("Running %s...\n", #test_func); \
        test_func(); \
    } while (0)

#endif
