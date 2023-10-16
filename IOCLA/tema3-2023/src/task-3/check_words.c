#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void get_words(char *s, char **words, int number_of_words);
void sort(char **words, int number_of_words, int size);

const char *filler = "========================================";
const char *delim  = "........................................";

int read_input(int test_no, char *input)
{
    char file[16] = {};
    sprintf(file, "in/sort-%02d.in", test_no);

    FILE *in = fopen(file, "r");
    if (!in) {
        printf("Cannot find input file\n");
        exit(EXIT_FAILURE);
    }

    int n;
    fscanf(in, "%d", &n);
    fgetc(in);
    fgets(input, 1000, in);

    return n;
}

void read_ref(int test_no, char **ref, int size)
{
    char file[16] = {};
    sprintf(file, "ref/sort-%02d.ref", test_no);

    FILE *ref_file = fopen(file, "r");
    if (!ref_file) {
        printf("Cannot find ref file\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < size; i++) {
        fscanf(ref_file, "%s", ref[i]);
    }
}

void write_out(int test_no, char **out, int size)
{
    char file[16] = {};
    sprintf(file, "out/sort-%02d.out", test_no);

    FILE *out_file = fopen(file, "w");
    if (!out_file) {
        printf("Cannot create out file\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        fprintf(out_file, "%s ", out[i]);
    }
}

void run_tests(int test_num, int silent_testing)
{
    float score = 0.0f;
    float score_per_test = 25.0f / test_num;

    int filler_size = (50 - strlen("Sortare de cuvinte") - 2) / 2;
    int delim_size = 50 - strlen("Test 00XXXXXX: 0.00");

    printf("%.*s Sortare de cuvinte %.*s\n\n", filler_size, filler, filler_size, filler);
    char *input = malloc(1000);
    char **ref = malloc(100 * sizeof(char *));
    char **res = malloc(100 * sizeof(char *));
    for (size_t i = 0; i < 100; i++) {
        res[i] = calloc(1, 100);
        ref[i] = calloc(1, 100);
    }

    for (size_t i = 0; i < test_num; i++) {
        int passed = 1;
        int n = read_input(i, input);
        read_ref(i, ref, n);

        get_words(input, res, n);
        sort(res, n, sizeof(char *));

        write_out(i, res, n);

        for (int j = 0; j < n; j++) {
            if (strcmp(res[j], ref[j])) {
                printf("Test %02d%.*sFAILED: %.2f\n", i, delim_size, delim, 0.0);
                passed = 0;
                break;
            }
        }
        
        if (passed) {
            score += score_per_test;
            printf("Test %02d%.*sPASSED: %.2f\n", i, delim_size, delim, score_per_test);
        }
    }
    printf("\nTASK 3 SCORE: %.2f / 25.00\n", score);
}

int main(int argc, char **argv)
{
    int is_silent = 1;
    if (argc == 2 && 
        (strcmp(argv[1], "-o") == 0 || strcmp(argv[1], "--output") == 0)) {
        is_silent = 0;
    }

    run_tests(5, is_silent);

    return 0;
}
