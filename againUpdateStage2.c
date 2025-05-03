#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct EasterEgg {
    char keyword[10];
    char message[256];
};

void convertToBinary(char character, char binary[9]) {
    for (int i = 7; i >= 0; i--) {
        binary[7 - i] = (character & (1 << i)) ? '1' : '0';
    }
    binary[8] = '\0';
}

void scrambleKeyword(char *keyword, char reversedBinaries[7][9]) {
    char scrambledKeyword[50];
    int j = 0;

    for (int i = 1; i < strlen(keyword); i += 2) {
        scrambledKeyword[j++] = keyword[i];
    }
    for (int i = 0; i < strlen(keyword); i += 2) {
        scrambledKeyword[j++] = keyword[i];
    }
    scrambledKeyword[j] = '\0';

    for (int i = 0; i < strlen(scrambledKeyword); i++) {
        convertToBinary(scrambledKeyword[i], reversedBinaries[i]);
    }
}

bool isRightChar(char input, char expected) {
    return input == expected;
}

bool isEasterEgg(char *inputWord) {
    return strcmp(inputWord, "specter") == 0;
}

void find_easter_egg() {
    struct EasterEgg egg = {
        "specter",
        "I confess. After graduating from university, I was blinded by the arrogance of starting a startup and recklessly blocked my friends' paths. I painfully learned that when I am the only one convinced by my idea, it leads to disastrous results. The past Arthur was a ghost of dogmatism and stubbornness."
    };

    printf("<<Arthur's Easter Egg>>\n");

    char reversedBinaries[7][9];
    scrambleKeyword(egg.keyword, reversedBinaries);

    for (int i = 6; i >= 0; i--) {
        printf("Binary: %s\n", reversedBinaries[i]);
    }

    char userInput[8];
    for (int i = 0; i < 7; i++) {
        printf("Enter the character corresponding to binary %s: ", reversedBinaries[i]);
        char inputChar;
        scanf(" %c", &inputChar);
        while (!isRightChar(inputChar, egg.keyword[i])) {
            printf("Incorrect. Try again: ");
            scanf(" %c", &inputChar);
        }
        userInput[i] = inputChar;
    }
    userInput[7] = '\0';

    if (isEasterEgg(userInput)) {
        printf("##Easter Egg Discovered!$$\n");
        printf("%s\n", egg.message);
    } else {
        printf("Wrong word. Returning to main menu.\n");
    }
}

int main() {
    int choice;
    printf("Select an option:\n");
    printf("II. Training > 2. Self-Management and Teamwork\n");
    printf("Enter 'Arthur' to unlock the Easter Egg: ");
    char input[10];
    scanf("%s", input);

    if (strcmp(input, "Arthur") == 0) {
        find_easter_egg();
    } else {
        printf("Returning to menu...\n");
    }

    return 0;
}
