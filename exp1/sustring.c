#include <stdio.h>
#include <string.h>

int main() {
    char str[100], substr[100];
    printf("Enter the main string: ");
    gets(str);
    printf("Enter the substring: ");
    gets(substr);

    int found = 0;
    int str_len = strlen(str);
    int substr_len = strlen(substr);

    for (int i = 0; i <= str_len - substr_len; i++) {
        int j;
        for (j = 0; j < substr_len; j++) {
            if (str[i + j] != substr[j]) {
                break;
            }
        }
        if (j == substr_len) {
            printf("Substring found at index %d\n", i);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Substring not found.\n");
    }
    
    return 0;
}
