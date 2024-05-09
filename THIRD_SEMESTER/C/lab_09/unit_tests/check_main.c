#include <stdlib.h>
#include <check.h>
#include "../inc/check_binary_search.h"

int main(void)
{
    int no_failed = 0;

    Suite *suites[] = {
        binary_search_title_suite(),
        binary_search_name_suite(),
        binary_search_year_suite()
    };

    for (int i = 0; i < sizeof(suites) / sizeof(suites[0]); i++) {
        SRunner *runner = srunner_create(suites[i]);
        srunner_run_all(runner, CK_VERBOSE);
        no_failed += srunner_ntests_failed(runner);
        srunner_free(runner);
    }

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
