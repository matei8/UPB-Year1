#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern void add_vect(int *v1, int *v2, int n, int *v);

const char *filler = "========================================";
const char *delim  = "........................................";
const char *task_name = "AT&T";

#define MAX_FILENAME 10
#define MAX_COMMAND  ((MAX_FILENAME) * 2 + 18)

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
        int *v1, *v2, *v;
		int n;
		char in_file_name[10], out_file_name[10], ref_file_name[10];

		snprintf(in_file_name, 10, "in/%d.in", i);
		snprintf(out_file_name, 10, "out/%d.out", i);
		snprintf(ref_file_name, 10, "ref/%d.ref", i);

		FILE *in = fopen(in_file_name, "r");
		if (!in)
		{
			fprintf(stderr, "fopen failed: %s", strerror(errno));
			return;
		}

		fscanf(in, "%d\n", &n);

		v1 = malloc(n * sizeof(*v1));
		if (!v1)
		{
			fprintf(stderr, "malloc failed: %s", strerror(errno));
			goto close_in;
		}

		for (size_t j = 0; j < n; j++)
			fscanf(in, "%d", &v1[j]);

		v2 = malloc(n * sizeof(*v2));
		if (!v2)
		{
			fprintf(stderr, "malloc failed: %s", strerror(errno));
			goto free_v1;
		}

		for (size_t j = 0; j < n; j++)
			fscanf(in, "%d", &v2[j]);

		v = malloc(n * sizeof(*v));
		if (!v)
		{
			fprintf(stderr, "malloc failed: %s", strerror(errno));
			goto free_v2;
		}

		add_vect(v1, v2, n, v);

		FILE *out = fopen(out_file_name, "w");
		if (!out)
		{
			fprintf(stderr, "fopen failed: %s", strerror(errno));
			goto free_v;
		}

		for (size_t j = 0; j < n; j++)
			fprintf(out, "%d ", v[j]);
		fprintf(out, "\n");

		fclose(out);

		char command[MAX_COMMAND];
		snprintf(command, MAX_COMMAND, "diff %s %s > /dev/null", ref_file_name, out_file_name);

        if (system(command) == 0)
		{
            printf("Test %02d%.*sPASSED: %.2f\n", i, delim_size, delim, score_per_test);
            score += score_per_test;
        }
		else
            printf("Test %02d%.*sFAILED: %.2f\n", i, delim_size, delim, 0.0);

free_v:
		free(v);
free_v2:
		free(v2);
free_v1:
		free(v1);
close_in:
		fclose(in);
    }
    printf("\nBONUS 2 SCORE: %.2f / %.2f\n", score, task_score);
}

int main(void)
{
    run_tests(3);

	return 0;
}
