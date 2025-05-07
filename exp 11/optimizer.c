#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Code {
    char lhs[20];
    char rhs[50];
    int used; // Flag to check if this line is useful
};

int main() {
    FILE *fp;
    struct Code code[MAX];
    char temp[100];
    int count = 0;

    fp = fopen("input.txt", "r");
    if (!fp) {
        printf("Cannot open input.txt\n");
        return 1;
    }

    // Read all lines
    while (fgets(temp, sizeof(temp), fp)) {
        temp[strcspn(temp, "\n")] = 0;
        sscanf(temp, "%s = %[^\n]", code[count].lhs, code[count].rhs);
        code[count].used = 0;
        count++;
    }
    fclose(fp);

    // Common Subexpression Elimination
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(code[i].rhs, code[j].rhs) == 0) {
                // Replace j's LHS with i's LHS in later code
                for (int k = j + 1; k < count; k++) {
                    char *pos = strstr(code[k].rhs, code[j].lhs);
                    if (pos) {
                        char new_rhs[100];
                        strcpy(new_rhs, code[k].rhs);
                        // Replace variable
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
                // Remove duplicate expression
                strcpy(code[j].lhs, ""); 
                strcpy(code[j].rhs, "");
            }
        }
    }

    // Dead Code Elimination
    for (int i = 0; i < count; i++) {
        // Check if lhs is used anywhere
        for (int j = 0; j < count; j++) {
            if (strstr(code[j].rhs, code[i].lhs)) {
                code[i].used = 1;
                break;
            }
        }
    }

    // Final Pass: Print optimized code
    printf("Optimized Code:\n\n");
    for (int i = 0; i < count; i++) {
        if (strlen(code[i].lhs) == 0) continue;  // CSE removed
        if (code[i].used || i == count - 1)      // DCE allowed last assignment
            printf("%s = %s\n", code[i].lhs, code[i].rhs);
    }

    return 0;
}
