#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Code {
    char lhs[20];
    char rhs[50];
    int used;
};

int main() {
    FILE *fp;
    struct Code code[MAX];
    char line[100];
    int count = 0;

    fp = fopen("input.txt", "r");
    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }

    // Step 1: Read file and store into struct
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;
        sscanf(line, "%s = %[^\n]", code[count].lhs, code[count].rhs);
        code[count].used = 0;
        count++;
    }
    fclose(fp);

    // Step 2: Copy Propagation
    for (int i = 0; i < count; i++) {
        // Only handle simple copies like t1 = a
        if (strchr(code[i].rhs, '+') == NULL && strchr(code[i].rhs, '-') == NULL &&
            strchr(code[i].rhs, '*') == NULL && strchr(code[i].rhs, '/') == NULL) {

            for (int j = i + 1; j < count; j++) {
                char *pos = strstr(code[j].rhs, code[i].lhs);
                if (pos) {
                    char new_rhs[100];
                    strcpy(new_rhs, code[j].rhs);
                    // Replace LHS var in rhs
                    for (int x = 0; x < strlen(new_rhs); x++) {
                        if (strncmp(&new_rhs[x], code[i].lhs, strlen(code[i].lhs)) == 0) {
                            new_rhs[x] = '\0';
                            strcat(new_rhs, code[i].rhs);
                            strcat(new_rhs, &code[j].rhs[x + strlen(code[i].lhs)]);
                            break;
                        }
                    }
                    strcpy(code[j].rhs, new_rhs);
                }
            }
        }
    }

    // Step 3: Common Subexpression Elimination
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(code[i].rhs, code[j].rhs) == 0) {
                // Replace j's LHS in further lines with i's LHS
                for (int k = j + 1; k < count; k++) {
                    char *pos = strstr(code[k].rhs, code[j].lhs);
                    if (pos) {
                        char new_rhs[100];
                        strcpy(new_rhs, code[k].rhs);
                        for (int x = 0; x < strlen(new_rhs); x++) {
                            if (strncmp(&new_rhs[x], code[j].lhs, strlen(code[j].lhs)) == 0) {
                                new_rhs[x] = '\0';
                                strcat(new_rhs, code[i].lhs);
                                strcat(new_rhs, &code[k].rhs[x + strlen(code[j].lhs)]);
                                break;
                            }
                        }
                        strcpy(code[k].rhs, new_rhs);
                    }
                }
                // Eliminate duplicate
                strcpy(code[j].lhs, "");
                strcpy(code[j].rhs, "");
            }
        }
    }

    // Step 4: Dead Code Elimination
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (strstr(code[j].rhs, code[i].lhs)) {
                code[i].used = 1;
                break;
            }
        }
    }

    // Step 5: Write Optimized Code to Output File
    FILE *out = fopen("optimized.txt", "w");
    printf("\nOptimized Code:\n\n");
    for (int i = 0; i < count; i++) {
        if (strlen(code[i].lhs) == 0) continue; // Skipped due to CSE
        if (code[i].used || i == count - 1) {   // Last line always included
            printf("%s = %s\n", code[i].lhs, code[i].rhs);
            fprintf(out, "%s = %s\n", code[i].lhs, code[i].rhs);
        }
    }
    fclose(out);

    return 0;
}
