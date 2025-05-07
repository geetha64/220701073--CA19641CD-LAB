#include <stdio.h>

int main() {
    char str[100], oldChar, newChar;
    printf("Enter a string: ");
    gets(str);
    printf("Enter the character to replace: ");
    scanf("%c", &oldChar);
    getchar();  // Clear newline character
    printf("Enter the new character: ");
    scanf("%c", &newChar);

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == oldChar) {
            str[i] = newChar;
        }
    }

    printf("Modified String: %s\n", str);
    return 0;
}
