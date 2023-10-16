#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

extern void vectorial_ops(int s, int A[], int B[], int C[], int n, int D[]);

const char *filler = "========================================";
const char *delim  = "........................................";
const char *task_name = "Vectorial Operations";

#define MAX_FILENAME 10
#define MAX_COMMAND  ((MAX_FILENAME) * 2 + 18)

static void run_tests(int test_num)
{
	float score = 0.0f;
	float task_score = 15.0f;
    float score_per_test = task_score / test_num;

    int filler_size = (50 - strlen(task_name)) / 2;
    int delim_size = 50 - strlen("Test 00XXXXXX: 0.00");

    printf("%.*s %s %.*s\n\n", filler_size, filler, task_name, filler_size, filler);

    for (size_t i = 1; i <= test_num; i++)
	{
        int *A, *B, *C, *D;
		int n, s;
		char in_file_name[MAX_FILENAME], out_file_name[MAX_FILENAME], ref_file_name[MAX_FILENAME];

		snprintf(in_file_name, 10, "in/%ld.in", i);
		snprintf(out_file_name, 10, "out/%ld.out", i);
		snprintf(ref_file_name, 10, "ref/%ld.ref", i);

		FILE *in = fopen(in_file_name, "r");
		if (!in)
		{
			fprintf(stderr, "fopen failed: %s", strerror(errno));
			return;
		}

		fscanf(in, "%d\n", &n);
		fscanf(in, "%d\n", &s);

		A = malloc(n * sizeof(*A));
		if (!A)
		{
			fprintf(stderr, "malloc failed: %s", strerror(errno));
			goto close_in;
		}

		for (size_t j = 0; j < n; j++)
			fscanf(in, "%d", &A[j]);

		B = malloc(n * sizeof(*B));
		if (!B)
		{
			fprintf(stderr, "malloc failed: %s", strerror(errno));
			goto free_A;
		}

		for (size_t j = 0; j < n; j++)
			fscanf(in, "%d", &B[j]);

		C = malloc(n * sizeof(*C));
		if (!C)
		{
			fprintf(stderr, "malloc failed: %s", strerror(errno));
			goto free_B;
		}

		for (size_t j = 0; j < n; j++)
			fscanf(in, "%d", &C[j]);

		D = malloc(n * sizeof(*D));
		if (!D)
		{
			fprintf(stderr, "malloc failed: %s", strerror(errno));
			goto free_C;
		}

		vectorial_ops(s, A, B, C, n, D);

		FILE *out = fopen(out_file_name, "w");
		if (!out)
		{
			fprintf(stderr, "fopen failed: %s", strerror(errno));
			goto free_D;
		}

		for (size_t j = 0; j < n; j++)
			fprintf(out, "%d ", D[j]);
		fprintf(out, "\n");

		fclose(out);

		char command[MAX_COMMAND];
		snprintf(command, MAX_COMMAND, "diff %s %s > /dev/null", ref_file_name, out_file_name);

        if (system(command) == 0)
		{
            printf("Test %02ld%.*sPASSED: %.2f\n", i, delim_size, delim, score_per_test);
            score += score_per_test;
        }
		else
            printf("Test %02ld%.*sFAILED: %.2f\n", i, delim_size, delim, 0.0);

free_D:
		free(D);
free_C:
		free(C);
free_B:
		free(B);
free_A:
		free(A);
close_in:
		fclose(in);
    }
    printf("\nBONUS 4 SCORE: %.2f / %.2f\n", score, task_score);
}

int main(void)
{
    run_tests(3);

	return 0;
}
