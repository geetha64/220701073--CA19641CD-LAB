#include <stdio.h>
#include <string.h>

void generate(char result[], char arg1[], char op[], char arg2[]) {
    if (strcmp(op, "+") == 0) {
        printf("MOV AX, [%s]\n", arg1);
        printf("ADD AX, [%s]\n", arg2);
        printf("MOV [%s], AX\n", result);
    }
    else if (strcmp(op, "-") == 0) {
        printf("MOV AX, [%s]\n", arg1);
        printf("SUB AX, [%s]\n", arg2);
        printf("MOV [%s], AX\n", result);
    }
    else if (strcmp(op, "*") == 0) {
        printf("MOV AX, [%s]\n", arg1);
        printf("MOV BX, [%s]\n", arg2);
        printf("MUL BX\n");
        printf("MOV [%s], AX\n", result);
    }
    else if (strcmp(op, "/") == 0) {
        printf("MOV AX, [%s]\n", arg1);
        printf("MOV DX, 0\n");
        printf("MOV BX, [%s]\n", arg2);
        printf("DIV BX\n");
        printf("MOV [%s], AX\n", result);
    }
}

int main() {
    FILE *fp = fopen("input.tac", "r");
    char line[50];
    char result[10], arg1[10], op[5], arg2[10];

    printf("Generated 8086 Assembly Code:\n\n");

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "+") || strstr(line, "-") || strstr(line, "*") || strstr(line, "/")) {
            sscanf(line, "%s = %s %s %s", result, arg1, op, arg2);
            generate(result, arg1, op, arg2);
        } else if (strstr(line, "=")) {
            sscanf(line, "%s = %s", result, arg1);
            printf("MOV AX, [%s]\n", arg1);
            printf("MOV [%s], AX\n", result);
        }
    }

    fclose(fp);
    return 0;
}
