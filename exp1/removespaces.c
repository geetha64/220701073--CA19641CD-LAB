#include <stdio.h>
#include <string.h>

int main() {
    char str[100], result[100];
    int j = 0;
    printf("Enter a string: ");
    gets(str);

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';  // Null-terminate the result string

    printf("String without spaces: %s\n", result);
    return 0;
}
