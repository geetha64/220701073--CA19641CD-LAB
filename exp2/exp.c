#include <stdio.h>
#include <string.h>
#include <ctype.h>

// List of C keywords
const char *keywords[] = {
    "int", "float", "char", "double", "if", "else", "while", "for", "do", "return",
    "switch", "case", "break", "continue", "void", "static", "struct", "typedef", "union",
    "default", "sizeof", "const", "volatile", "enum", "extern", "register", "goto", "long", "short", "signed", "unsigned"
};

// List of C operators
const char *operators[] = {"+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "++", "--"};

// List of special symbols (delimiters)
const char special_symbols[] = {';', ',', '(', ')', '{', '}', '[', ']', '"', '\'', '#'};

// Function to check if a token is a keyword
int isKeyword(char *token) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(token, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// Function to check if a token is an operator
int isOperator(char *token) {
    for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); i++) {
        if (strcmp(token, operators[i]) == 0)
            return 1;
    }
    return 0;
}

// Function to check if a character is a special symbol
int isSpecialSymbol(char ch) {
    for (int i = 0; i < sizeof(special_symbols) / sizeof(special_symbols[0]); i++) {
        if (ch == special_symbols[i])
            return 1;
    }
    return 0;
}

// Function to check if a token is a valid identifier (variable/function name)
int isIdentifier(char *token) {
    if (!isalpha(token[0]) && token[0] != '_') // Identifiers must start with a letter or underscore
        return 0;
    for (int i = 1; token[i] != '\0'; i++) {
        if (!isalnum(token[i]) && token[i] != '_') // Identifiers can contain letters, digits, and underscores
            return 0;
    }
    return !isKeyword(token); // Should not be a keyword
}

// Main function
int main() {
    char code[500], token[50];
    int i = 0, j = 0;

    printf("Enter a C code snippet:\n");
    fgets(code, sizeof(code), stdin);

    printf("\nRecognized Tokens:\n");

    while (code[i] != '\0') {
        if (isspace(code[i]) || isSpecialSymbol(code[i])) {  
            if (j != 0) {  // If a token was being formed, process it
                token[j] = '\0';
                j = 0;

                if (isKeyword(token))
                    printf("Keyword: %s\n", token);
                else if (isOperator(token))
                    printf("Operator: %s\n", token);
                else if (isIdentifier(token))
                    printf("Identifier: %s\n", token);
                else
                    printf("Unknown Token: %s\n", token);
            }

            if (isSpecialSymbol(code[i]))  
                printf("Special Symbol: %c\n", code[i]);

        } else if (ispunct(code[i])) {  // Handling operators separately
            if (j != 0) {  
                token[j] = '\0';
                j = 0;
                if (isIdentifier(token))
                    printf("Identifier: %s\n", token);
            }

            char op[3] = {code[i], code[i + 1], '\0'};
            if (isOperator(op)) {
                printf("Operator: %s\n", op);
                i++; 
            } else {
                op[1] = '\0';
                if (isOperator(op))
                    printf("Operator: %s\n", op);
            }
        } else {  
            token[j++] = code[i];  
        }
        i++;
    }
    return 0;
}
