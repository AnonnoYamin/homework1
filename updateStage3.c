#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 5
#define MAX_ATTEMPTS 3
#define NUM_CONSONANTS 14
#define NUM_VOWELS 10

typedef struct {
    char hangul[3];
    char english[2];
    char pronunciation[20];
} HangulChar;

typedef struct {
    char name[50];
    char challengeType[3];
    int totalScore;
    int attemptCount;
} Result;

HangulChar hangulData[NUM_CONSONANTS + NUM_VOWELS];
Result result;

void initializeHangulData() {
    const char *consonants[NUM_CONSONANTS][3] = {
        {"ㄱ", "g", "giyeok"}, {"ㄴ", "n", "nieun"}, {"ㄷ", "d", "digeut"}, {"ㄹ", "r", "rieul"},
        {"ㅁ", "m", "mieum"}, {"ㅂ", "b", "bieup"}, {"ㅅ", "s", "siot"}, {"ㅇ", "ng", "ieung"},
        {"ㅈ", "j", "jieut"}, {"ㅊ", "ch", "chieut"}, {"ㅋ", "k", "kieuk"}, {"ㅌ", "t", "tieut"},
        {"ㅍ", "p", "pieup"}, {"ㅎ", "h", "hieut"}
    };

    const char *vowels[NUM_VOWELS][3] = {
        {"ㅏ", "a", "a"}, {"ㅑ", "ya", "ya"}, {"ㅓ", "eo", "eo"}, {"ㅕ", "yeo", "yeo"},
        {"ㅗ", "o", "o"}, {"ㅛ", "yo", "yo"}, {"ㅜ", "u", "u"}, {"ㅠ", "yu", "yu"},
        {"ㅡ", "eu", "eu"}, {"ㅣ", "i", "i"}
    };

    for (int i = 0; i < NUM_CONSONANTS; i++) {
        strcpy(hangulData[i].hangul, consonants[i][0]);
        strcpy(hangulData[i].english, consonants[i][1]);
        strcpy(hangulData[i].pronunciation, consonants[i][2]);
    }

    for (int i = 0; i < NUM_VOWELS; i++) {
        strcpy(hangulData[NUM_CONSONANTS + i].hangul, vowels[i][0]);
        strcpy(hangulData[NUM_CONSONANTS + i].english, vowels[i][1]);
        strcpy(hangulData[NUM_CONSONANTS + i].pronunciation, vowels[i][2]);
    }
}

void playKor2EngGame() {
    srand(time(NULL));
    int score = 0;

    for (int i = 0; i < MAX_QUESTIONS; i++) {
        int randomIndex = rand() % (NUM_CONSONANTS + NUM_VOWELS);
        printf("Question %d: What is the English equivalent of %s (pronunciation: %s)?\n",
               i + 1, hangulData[randomIndex].hangul, hangulData[randomIndex].pronunciation);
        char answer[2];
        scanf("%s", answer);

        if (strcmp(answer, hangulData[randomIndex].english) == 0) {
            printf("Correct!\n");
            score += 10;
        } else {
            printf("Incorrect. The correct answer is %s.\n", hangulData[randomIndex].english);
        }
    }

    result.totalScore = score;
    result.attemptCount++;
    strcpy(result.challengeType, "KE");
}

void playEng2KorGame() {
    srand(time(NULL));
    int score = 0;

    for (int i = 0; i < MAX_QUESTIONS; i++) {
        int randomIndex = rand() % (NUM_CONSONANTS + NUM_VOWELS);
        printf("Question %d: What is the Hangul equivalent of %s (pronunciation: %s)?\n",
               i + 1, hangulData[randomIndex].english, hangulData[randomIndex].pronunciation);
        char answer[3];
        scanf("%s", answer);

        if (strcmp(answer, hangulData[randomIndex].hangul) == 0) {
            printf("Correct!\n");
            score += 10;
        } else {
            printf("Incorrect. The correct answer is %s.\n", hangulData[randomIndex].hangul);
        }
    }

    result.totalScore = score;
    result.attemptCount++;
    strcpy(result.challengeType, "EK");
}

void showResult() {
    printf("\nName: %s\n", result.name);
    printf("Challenge Type: %s\n", result.challengeType);
    printf("Total Score: %d\n", result.totalScore);
    printf("Attempts: %d\n", result.attemptCount);

    if (result.attemptCount > 0) {
        float avgScore = (float)result.totalScore / result.attemptCount;
        printf("Average Score: %.2f\n", avgScore);
    } else {
        printf("No attempts yet.\n");
    }
}

void learnHangul() {
    printf("Enter the name of the trainee: ");
    scanf("%s", result.name);

    int choice;
    do {
        printf("\n1. Hangul to English\n");
        printf("2. English to Hangul\n");
        printf("3. View Results\n");
        printf("Select an option (or 0 to quit): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                playKor2EngGame();
                break;
            case 2:
                playEng2KorGame();
                break;
            case 3:
                showResult();
                break;
            case 0:
                break;
            default:
                printf("Invalid choice, try again.\n");
        }
    } while (choice != 0);
}

void mainMenu() {
    char userChoice[3];
    int running = 1;

    do {
        printf("\n=== Main Menu ===\n");
        printf("I. Audition Management\n");
        printf("II. Training\n");
        printf("III. Debut\n");
        printf("Select option (or Q to quit): ");
        scanf("%s", userChoice);

        if (strcmp(userChoice, "I") == 0 || strcmp(userChoice, "i") == 0) {
            printf("Audition Management selected.\n");
        } else if (strcmp(userChoice, "II") == 0 || strcmp(userChoice, "ii") == 0) {
            printf("Training selected.\n");
            learnHangul();
        } else if (strcmp(userChoice, "III") == 0 || strcmp(userChoice, "iii") == 0) {
            printf("Debut selected.\n");
        } else if (strcmp(userChoice, "Q") == 0 || strcmp(userChoice, "q") == 0) {
            running = 0;
            printf("Exiting...\n");
        } else {
            printf("Invalid selection. Please try again.\n");
        }
    } while (running);
}

int main() {
    initializeHangulData();
    mainMenu();
    return 0;
}
