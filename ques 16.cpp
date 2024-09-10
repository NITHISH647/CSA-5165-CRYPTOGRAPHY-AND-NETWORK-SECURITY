#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const float englishFrequencies[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 
    4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 
    2.361, 0.150, 1.974, 0.074
};

typedef struct {
    int key;
    float score;
    char plaintext[100];
} DecryptionAttempt;

void calculateFrequencies(const char *text, float frequencies[]) {
    int count[26] = {0};
    int total = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            count[text[i] - 'a']++;
            total++;
        }
    }

    for (int i = 0; i < 26; i++) {
        frequencies[i] = (float)count[i] / total * 100.0;
    }
}

float compareFrequencies(float observed[], const float expected[]) {
    float score = 0.0;

    for (int i = 0; i < 26; i++) {
        score += (observed[i] - expected[i]) * (observed[i] - expected[i]) / expected[i];
    }

    return score;
}

void performSubstitution(char *ciphertext, char *plaintext, const int mapping[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = 'a' + mapping[ciphertext[i] - 'a'];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

void generateTopSubstitutions(char ciphertext[], DecryptionAttempt attempts[], int numAttempts) {
    char plaintext[100];
    float observedFrequencies[26];
    int defaultMapping[26];

    calculateFrequencies(ciphertext, observedFrequencies);

    for (int i = 0; i < numAttempts; i++) {
        for (int j = 0; j < 26; j++) {
            defaultMapping[j] = (i + j) % 26;
        }
        performSubstitution(ciphertext, plaintext, defaultMapping);
        float score = compareFrequencies(observedFrequencies, englishFrequencies);

        attempts[i].key = i;
        attempts[i].score = score;
        strcpy(attempts[i].plaintext, plaintext);
    }
}

int compare(const void *a, const void *b) {
    DecryptionAttempt *da = (DecryptionAttempt *)a;
    DecryptionAttempt *db = (DecryptionAttempt *)b;
    return (da->score > db->score) - (da->score < db->score);
}

int main() {
    char ciphertext[100];
    int topN;

    printf("Enter the ciphertext (lowercase letters only): ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);

    DecryptionAttempt attempts[26];

    generateTopSubstitutions(ciphertext, attempts, 26);

    qsort(attempts, 26, sizeof(DecryptionAttempt), compare);

    printf("\nTop %d possible plaintexts based on letter frequency analysis:\n", topN);
    for (int i = 0; i < topN && i < 26; i++) {
        printf("Key = %d: %s (Score = %.2f)\n", attempts[i].key, attempts[i].plaintext, attempts[i].score);
    }

    return 0;
}