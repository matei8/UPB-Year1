#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "_utils/bst.h"

#define TASK_ALL 0
#define TASK_1 1
#define TASK_2 2
#define TASK_3 3
#define in_prefix "./in/bin-tree-0%d.in"
#define out_parc_prefix "./out/bin-tree-parc-0%d.out"
#define out_intruders_prefix "./out/bin-tree-intruders-0%d.out"
#define out_fixing_prefix "./out/bin-tree-fixing-0%d.out"
#define ref_parc_prefix "./ref/bin-tree-parc-0%d.ref"
#define ref_intruders_prefix "./ref/bin-tree-intruders-0%d.ref"
#define ref_fixing_prefix "./ref/bin-tree-fixing-0%d.ref"
#define TASK_1_STRING "INORDER_PARC"
#define TASK_2_STRING "INORDER_INTRUDER"
#define TASK_3_STRING "INORDER_FIXING"
#define TASK_1_VALUE 10
#define TASK_2_VALUE 10
#define TASK_3_VALUE 5
#define NR_TASKS 10

int results_1[NR_TASKS], results_2[NR_TASKS], results_3[NR_TASKS];

extern int inorder_array[LEN], intruders_array[LEN], inoder_idx;
extern void inorder_parc(struct node *node, int *array);
extern void inorder_intruders(struct node *node, struct node *parent, int *array);
extern void inorder_fixing(struct node *node, struct node *parent);

int array_idx_1 = 0, array_idx_2 = 0;
float score;

void exit_program(char *error_message)
{
    fprintf(stderr, "%s", error_message);
    exit(-1);
}


void read_data(int *len, int *array, int test_idx, char *prefix)
{
    char file_name[LEN];

    sprintf(file_name, prefix, test_idx);
    FILE *f = fopen(file_name, "r");

    if (!f) {
        exit_program("fopen() failed\n");
        exit(-1);
    }

    if (!strcmp(prefix, in_prefix)) {
        fscanf(f, "%d", len);
        for (int i = 0; i < *len; ++i) {
            fscanf(f, "%d", array + i);
        }
    } 
    else {
        int i = 0;
        while (fscanf(f, "%d", &array[i++])) {
            if (!array[i - 1]) {
                break;
            }
        }
    }

    fclose(f);
}

void write_data(int *len, int *array, int test_idx, char *prefix)
{
    char file_name[LEN];

    sprintf(file_name, prefix, test_idx);
    FILE *f = fopen(file_name, "w");

    if (!f) { 
        exit_program("fopen() failed\n");
        exit(-1);
    }

    int cnt = 0;
    for (int i = 0; i < LEN; ++i) {
        if (array[i]) {
            if (cnt > 0) {
                fprintf(f, " ");
            }
            ++cnt;
            fprintf(f, "%d", array[i]);
        } else {
            break;
        }
    }

    fclose(f);
}

int compare(int len, int *array_1, int *array_2)
{
    for (int i = 0; i < LEN; ++i) {
        if (array_1[i] != array_2[i]) {
            return 0;
        }
    }
    return 1;
}

void run_task_1(struct node *root, int len, int *array_out,
                    int *array_ref, int test_idx)
{
    memset(array_out, 0, LEN * sizeof(*array_out));
    array_idx_1 = 0, array_idx_2 = 0;

    inorder_parc(root, array_out);
    write_data(&len, array_out, test_idx, out_parc_prefix); 

    results_1[test_idx] = compare(len, array_out, array_ref);
}

void run_task_2(struct node *root, int len, int *array_out,
                    int *array_ref, int test_idx)
{
    memset(array_out, 0, LEN * sizeof(*array_out));
    array_idx_1 = 0, array_idx_2 = 0;
    
    do_some_mess(root, NULL, 0);
    inorder_intruders(root, NULL, array_out);
    write_data(&len, array_out, test_idx, out_intruders_prefix);

    results_2[test_idx] = compare(len, array_out, array_ref);
}

void run_task_3(struct node *root, int len,
                    int *array_out, int *array_ref, int test_idx, int did_mess)
{
    memset(array_out, 0, LEN * sizeof(*array_out));
    array_idx_1 = 0, array_idx_2 = 0;

    if (!did_mess) {
        do_some_mess(root, NULL, 0);
    }
    inorder_fixing(root, NULL);
    inorder_parc(root, array_out);
    write_data(&len, array_out, test_idx, out_fixing_prefix);

    results_3[test_idx] = compare(len, array_out, array_ref);
}

void add_data_to_bst(struct BST **tree, int len, int *array)
{
    *tree = malloc(sizeof(**tree));
    if (!(*tree)) {
        exit_program("malloc() failed\n");
    }

    (*tree)->root = NULL;
    (*tree)->size = 0;

    for (int i = 0; i < len; ++i) {
        add_node((*tree), array[i]);
    }
}

void compute_feedback(int len, int *array, char *function_name, int value)
{
    char delim[] = "------------------------";
    char filler[] = "------------------------------------------------";
    if (array[0] != -1) {
        int sz = (50 - strlen(function_name)) / 2;
        printf("%s %s %s \n",
                delim + (26 - sz), function_name, delim + (26 - sz));
                
        float score_indiv = 0.0;
        for (int i = 0; i < NR_TASKS; ++i) {
            printf("Test %d %s ", i, filler + 21);
            if (array[i] == 1) {
                score_indiv += 1.0 * value / NR_TASKS;
                printf("PASSED: %.2fP", 1.0 * value / NR_TASKS);
            } else {
                printf("FAILED: %.2fP", 0.0);
            }
            printf("\n");
        }
        sz = 13;
        if (score_indiv >= 10) {
            ++sz;
        }
        sz = (50 - sz) / 2;
        printf("%s TOTAL: %.2fP %s\n\n",
                delim + (25 + (score_indiv >= 10) - sz), score_indiv, delim + (25 - sz));
        score += score_indiv;
    }
}

void compute_total()
{
    char delim[] = "------------------------";
    char filler[] = "------------------------------------------------";
    int sz = 50 - 20;
    if (score >= 10) {
        sz -= 2;
    }
    printf("%s\n", filler);
    printf("%s TASK 4 SCORE: %.2fP %s\n", delim + 25 + (score < 10) - sz / 2, score, delim + 25 - sz / 2);
    printf("%s\n", filler);
}

void run_tests(int task_type)
{
    struct BST *tree = NULL;
    int len, *array_in, *array_out;
    int *array_ref_parc, *array_ref_intruders, *array_ref_fixing;

    array_in = calloc(LEN, sizeof(*array_in));
    array_out = calloc(LEN, sizeof(*array_out));
    array_ref_parc = calloc(LEN, sizeof(*array_ref_parc));
    array_ref_intruders = calloc(LEN, sizeof(*array_ref_intruders));
    array_ref_fixing = calloc(LEN, sizeof(*array_ref_fixing));
    
    if (!array_in || !array_out || !array_ref_parc || !array_ref_intruders
        || !array_ref_fixing) {
        exit_program("malloc() failed\n");
    }

    memset(results_1, -1, sizeof(results_1));
    memset(results_2, -1, sizeof(results_2));
    memset(results_3, -1, sizeof(results_3));

    for (int i = 0; i < NR_TASKS; ++i) {
        memset(array_in, 0, LEN * sizeof(*array_in));
        memset(array_ref_parc, 0, LEN * sizeof(*array_ref_parc));
        memset(array_ref_intruders, 0, LEN * sizeof(*array_ref_intruders));
        memset(array_ref_fixing, 0, LEN * sizeof(*array_ref_fixing));

        read_data(&len, array_ref_parc, i, ref_parc_prefix);
        read_data(&len, array_ref_intruders, i, ref_intruders_prefix);
        read_data(&len, array_ref_fixing, i, ref_fixing_prefix);
        read_data(&len, array_in, i, in_prefix);

        add_data_to_bst(&tree, len, array_in);

        switch (task_type) {
            case TASK_ALL:
                run_task_1(tree->root, len, array_out, array_ref_parc, i);
                run_task_2(tree->root, len, array_out, array_ref_intruders, i);
                run_task_3(tree->root, len, array_out, array_ref_fixing, i, 1);
                break;

            case TASK_1:
                run_task_1(tree->root, len, array_out, array_ref_parc, i);
                break;

            case TASK_2:
                run_task_2(tree->root, len, array_out, array_ref_intruders, i);
                break;

            case TASK_3:
                run_task_3(tree->root, len, array_out, array_ref_fixing, i, 0);
                break;

            default:
                break;
        }
        free_tree(tree->root);
        free(tree);
    }

    compute_feedback(len, results_1, TASK_1_STRING, TASK_1_VALUE);
    compute_feedback(len, results_2, TASK_2_STRING, TASK_2_VALUE);
    compute_feedback(len, results_3, TASK_3_STRING, TASK_3_VALUE);
    compute_total();


    free(array_in);
    free(array_out);
    free(array_ref_parc);
    free(array_ref_intruders);
    free(array_ref_fixing);
}

int main(int argc, char *argv[])
{
    if (argc == 2) {
        if (strlen(argv[1]) > 1) {
            exit_program("Usage: ./checker [1/2/3]\n");
        }
        int test_type = atoi(argv[1]);

        if (test_type < 1 || test_type > 3) {
            exit_program("Usage: ./checker [1/2/3]\n");
        }
        run_tests(test_type);
    } else if (argc == 1) {
        run_tests(TASK_ALL);
    } else {
        exit_program("Usage: ./checker [1/2/3]\n");
    }

    srand(time(NULL));

    struct BST* tree = malloc(sizeof(*tree));
    if (!tree) {
        exit_program("malloc() failed\n");
    }
    tree->root = NULL;
    tree->size = 0;

    return 0;
}