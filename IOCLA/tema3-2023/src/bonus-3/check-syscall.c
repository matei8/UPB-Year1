#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void replace_marco(const char *in_file, const char *out_file);

const char *filler = "========================================";
const char *delim  = "........................................";
const char *task_name = "Syscall";

#define MAX_FILENAME 10
#define MAX_COMMAND  ((MAX_FILENAME) * 2 + 30)

static void run_tests(int test_num)
{
	float score = 0.0f;
	float task_score = 10.0f;
    float score_per_test = task_score / test_num;

    int filler_size = (50 - strlen(task_name)) / 2;
    int delim_size = 50 - strlen("Test 00XXXXXX: 0.00");

    printf("%.*s %s %.*s\n\n", filler_size, filler, task_name, filler_size, filler);

    for (size_t i = 1; i <= test_num; i++)
	{
		char in_file_name[MAX_FILENAME], out_file_name[MAX_FILENAME], ref_file_name[MAX_FILENAME];

		snprintf(in_file_name, 10, "in/%d.in", i);
		snprintf(out_file_name, 10, "out/%d.out", i);
		snprintf(ref_file_name, 10, "ref/%d.ref", i);

		replace_marco(in_file_name, out_file_name);

		char command[MAX_COMMAND];
		snprintf(command, MAX_COMMAND, "diff %s %s > /dev/null 2> /dev/null", ref_file_name, out_file_name);

        if (system(command) == 0)
        {
            printf("Test %02d%.*sPASSED: %.2f\n", i, delim_size, delim, score_per_test);
            score += score_per_test;
        }
		else
            printf("Test %02d%.*sFAILED: %.2f\n", i, delim_size, delim, 0.0);
    }
    printf("\nBONUS 3 SCORE: %.2f / %.2f\n", score, task_score);
}

int main(void)
{
    run_tests(3);

	return 0;
}
