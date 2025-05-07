#include <stdio.h>
#include <string.h>

int main() {
    char str1[100], str2[100];
    printf("Enter the first string: ");
    gets(str1);
    printf("Enter the second string: ");
    gets(str2);

    if (strcmp(str1, str2) == 0) {
        printf("The strings are the same.\n");
    } else {
        printf("The strings are different.\n");
    }

    return 0;
}
