#include <stdio.h>
#include <string.h>

#define MAX_MENU_ITEMS 11
#define MAX_LENGTH 60

void trainingMenu(char results[]);

int main() {
    char menu[MAX_MENU_ITEMS][MAX_LENGTH] = {
        "1. Audition Management",
        "2. Training",
        "3. Debut",
        "4. Physical Strength & Knowledge",
        "5. Self-Management & Teamwork",
        "6. Language & Pronunciation",
        "7. Vocal",
        "8. Dance",
        "9. Visual & Image",
        "10. Acting & Stage Performance",
        "11. Fan Communication"
    };

    char input[10];
    char results[8] = {'-', '-', '-', '-', '-', '-', '-', '-'};

    while (1) {
        printf("\n=== Magrathea System Menu ===\n");
        for (int i = 0; i < 3; i++) {
            printf("%s\n", menu[i]);
        }
        printf("Select a menu (1-3) or Q to quit: ");
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
                printf("Invalid option.\n");
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
    const char *labels[8] = {
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
        for (int i = 0; i < 8; i++) {
            printf("%s [%c]\n", labels[i], results[i]);
        }
        printf("Select a training stage (1–8) or Q to return: ");
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
            printf("Previous stages must be passed before accessing this one.\n");
            continue;
        }

        if (results[stage - 1] == 'P') {
            printf("Stage already passed.\n");
            continue;
        }

        printf("Enter evaluation result? (Y/N): ");
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'Y' || input[0] == 'y') {
            printf("Did you pass the certification? (Y for pass / N for fail): ");
            fgets(input, sizeof(input), stdin);
            if (input[0] == 'Y' || input[0] == 'y') {
                results[stage - 1] = 'P';
                printf("Marked as Passed.\n");
            } else {
                results[stage - 1] = 'F';
                printf("Marked as Failed.\n");
            }
        } else {
            printf("Back to training menu.\n");
        }
    }
}
