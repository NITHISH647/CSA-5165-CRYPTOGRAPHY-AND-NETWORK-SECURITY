#include <stdio.h>
#include <string.h>
int main() {
    char plaintext[100];
    char ciphertext[100];
    char key[27] = "qwertyuioplkjhgfdsazxcvbnm";
    int i, j;
    printf("Enter a lowercase string: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    for(i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];
        if(ch >= 'a' && ch <= 'z') {
            j = ch - 'a'; 
            ciphertext[i] = key[j];  
        } else {
            ciphertext[i] = ch;  
        }
    }
    ciphertext[i] = '\0';  
    printf("Encrypted text: %s\n", ciphertext);
    return 0;
}