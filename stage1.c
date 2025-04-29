#include <stdio.h>
#include <string.h>

// Function prototypes
void showMainMenu();
void auditionManagement();
void training();
void debut();
void trainingMenu();
int isStageUnlocked(int stage, char results[]);
int allStagesCompleted(char results[]);

// Constants
const char *mainMenu[] = {
    "I. Audition Management",
    "II. Training",
    "III. Debut"
};

const char *trainingStages[] = {
    "1. Physical Strength & Knowledge",
    "2. Self-Management & Teamwork",
    "3. Language & Pronunciation",
    "4. Vocal",
    "5. Dance",
    "6. Visual & Image",
    "7. Acting & Stage Performance",
    "8. Fan Communication"
};

int main() {
    char input[10];

    while (1) {
        showMainMenu();
        printf("Select a menu option (1-3), or Q to quit: ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n' || input[0] == '0' || input[0] == 'Q' || input[0] == 'q') {
            printf("Exiting program...\n");
            break;
        }

        switch (input[0]) {
            case '1':
                auditionManagement();
                break;
            case '2':
                training();
                break;
            case '3':
                debut();
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}

void showMainMenu() {
    printf("\n=== Magrathea System Main Menu ===\n");
    for (int i = 0; i < 3; i++) {
        printf("%s\n", mainMenu[i]);
    }
    printf("===================================\n");
}

void auditionManagement() {
    printf("\n[Audition Management]\n");
    printf("This is a placeholder for audition management.\n");
}

void debut() {
    printf("\n[Debut]\n");
    printf("This is a placeholder for debut function.\n");
}

void training() {
    static char results[8] = {'-', '-', '-', '-', '-', '-', '-', '-'};
    char input[10];

    while (1) {
        printf("\n=== Training Menu ===\n");
        for (int i = 0; i < 8; i++) {
            printf("%s [%c]\n", trainingStages[i], results[i]);
        }
        printf("Select a training stage (1-8), or Q to return: ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n' || input[0] == 'Q' || input[0] == 'q') {
            break;
        }

        int stage = input[0] - '0';

        if (stage < 1 || stage > 8) {
            printf("Invalid stage number.\n");
            continue;
        }

        if (!isStageUnlocked(stage, results)) {
            printf("You must complete previous stages before accessing this one.\n");
            continue;
        }

        if (results[stage - 1] == 'P') {
            printf("Stage %d already completed and passed. Cannot re-select.\n", stage);
            continue;
        }

        printf("Would you like to enter the evaluation result? (Y/N): ");
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'Y' || input[0] == 'y') {
            printf("Did you complete the training and pass the certification? (Y for pass, N for fail): ");
            fgets(input, sizeof(input), stdin);
            if (input[0] == 'Y' || input[0] == 'y') {
                results[stage - 1] = 'P';
                printf("Stage %d marked as Passed.\n", stage);
            } else {
                results[stage - 1] = 'F';
                printf("Stage %d marked as Failed.\n", stage);
            }
        } else {
            printf("Returning to training menu.\n");
        }
    }
}

int isStageUnlocked(int stage, char results[]) {
    // Stages 1 and 2 must be completed in sequence
    if (stage == 1) {
        return 1;
    } else if (stage == 2) {
        return results[0] == 'P';
    } else {
        return results[0] == 'P' && results[1] == 'P';
    }
}
