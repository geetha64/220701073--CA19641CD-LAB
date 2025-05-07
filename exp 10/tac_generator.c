#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int tempCount = 1;

void printTemp(char op[], char arg1[], char arg2[], char result[]) {
    printf("%s = %s %s %s\n", result, arg1, op, arg2);
}

void processArithmetic(char line[]) {
    char left[10], arg1[10], op[5], arg2[10];
    int matched = sscanf(line, "%s = %s %s %s", left, arg1, op, arg2);

    if (matched == 4) {
        if (strchr(arg1, '*') || strchr(arg1, '/') || strchr(arg1, '+') || strchr(arg1, '-')) {
            // Already broken, just print
            printf("%s = %s %s %s\n", left, arg1, op, arg2);
            return;
        }

        if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0) {
            printf("t%d = %s %s %s\n", tempCount, arg1, op, arg2);
            printf("%s = t%d\n", left, tempCount);
            tempCount++;
        } else {
            // For addition/subtraction, check for priority
            printf("t%d = %s %s %s\n", tempCount, arg1, op, arg2);
            printf("%s = t%d\n", left, tempCount);
            tempCount++;
        }
    } else if (matched == 2) {
        sscanf(line, "%s = %s", left, arg1);
        printf("%s = %s\n", left, arg1);
    }
}

void processControlFlow(char line[]) {
    // Handle if, goto, labels, etc.
    if (strstr(line, "if") || strstr(line, "goto") || strchr(line, ':')) {
        printf("%s\n", line);
    }
}

int main() {
    FILE *fp;
    char line[100];

    fp = fopen("input.txt", "r");

    if (!fp) {
        printf("Cannot open file.\n");
        return 1;
    }

    printf("Three Address Code Output:\n\n");

    while (fgets(line, sizeof(line), fp)) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        if (strstr(line, "if") || strstr(line, "goto") || strchr(line, ':'))
            processControlFlow(line);
        else
            processArithmetic(line);
    }

    fclose(fp);
    return 0;
}
