#include <stdio.h>
#include <string.h>

#define MAIN_MENU_ITEMS 3
#define TRAINING_ITEMS 8
#define MAX_LENGTH 60

void trainingMenu(char results[]);

int main() {
    char mainMenu[MAIN_MENU_ITEMS][MAX_LENGTH] = {
        "1. Audition Management",
        "2. Training",
        "3. Debut"
    };

    char trainingMenuItems[TRAINING_ITEMS][MAX_LENGTH] = {
        "1. Physical Strength & Knowledge",
        "2. Self-Management & Teamwork",
        "3. Language & Pronunciation",
        "4. Vocal",
        "5. Dance",
        "6. Visual & Image",
        "7. Acting & Stage Performance",
        "8. Fan Communication"
    };

    char input[10];
    char results[8] = {'-', '-', '-', '-', '-', '-', '-', '-'};

    while (1) {
        printf("\n=== Magrathea Main Menu ===\n");
        for (int i = 0; i < MAIN_MENU_ITEMS; i++) {
            printf("%s\n", mainMenu[i]);
        }
        printf("Choose a menu (1-3) or Q to quit: ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == 'Q' || input[0] == 'q' || input[0] == '\n' || input[0] == '0') {
            printf("Exiting...\n");
            break;
        }

        switch (input[0]) {
            case '1':
                printf("\n[Audition Management]\n");
                break;
            case '2':
                trainingMenu(results);
                break;
            case '3':
                printf("\n[Debut]\n");
                break;
            default:
                printf("Invalid input.\n");
        }
    }

    return 0;
}

int isUnlocked(int stage, char results[]) {
    if (stage == 1) return 1;
    if (stage == 2) return results[0] == 'P';
    return results[0] == 'P' && results[1] == 'P';
}

void trainingMenu(char results[]) {
    char input[10];
    char trainingMenuItems[TRAINING_ITEMS][MAX_LENGTH] = {
        "1. Physical Strength & Knowledge",
        "2. Self-Management & Teamwork",
        "3. Language & Pronunciation",
        "4. Vocal",
        "5. Dance",
        "6. Visual & Image",
        "7. Acting & Stage Performance",
        "8. Fan Communication"
    };

    while (1) {
        printf("\n=== Training Menu ===\n");
        for (int i = 0; i < TRAINING_ITEMS; i++) {
            printf("%s [%c]\n", trainingMenuItems[i], results[i]);
        }
        printf("Choose a stage (1–8) or Q to return: ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == 'Q' || input[0] == 'q' || input[0] == '\n') {
            break;
        }

        int stage = input[0] - '0';
        if (stage < 1 || stage > 8) {
            printf("Invalid stage.\n");
            continue;
        }

        if (!isUnlocked(stage, results)) {
            printf("Must complete earlier required stages first.\n");
            continue;
        }

        if (results[stage - 1] == 'P') {
            printf("Stage already passed.\n");
            continue;
        }

        printf("Enter evaluation result? (Y/N): ");
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'Y' || input[0] == 'y') {
            printf("Did you pass the certification? (Y/N): ");
            fgets(input, sizeof(input), stdin);
            if (input[0] == 'Y' || input[0] == 'y') {
                results[stage - 1] = 'P';
                printf("Marked as Passed.\n");
            } else {
                results[stage - 1] = 'F';
                printf("Marked as Failed.\n");
            }
        }
    }
}

