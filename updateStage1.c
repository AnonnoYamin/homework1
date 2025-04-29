#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MEMBERS 4
#define MAX_TESTS 7
#define MAX_LEN 100

char* main_menu[][2] = {
    {"I", "Audition Management"},
    {"II", "Training"},
    {"III", "Debut"}
};

char* training_menu[][2] = {
    {"1", "Physical Strength & Knowledge"},
    {"2", "Self-Management & Teamwork"},
    {"3", "Language & Pronunciation"},
    {"4", "Vocal"},
    {"5", "Dance"},
    {"6", "Visual & Image"},
    {"7", "Acting & Stage Performance"},
    {"8", "Fan Communication"}
};

char* test_names[MAX_TESTS] = {
    "1-Mile Running Test", "Speed Sprint", "Push-ups",
    "Squats", "Arm Strength (Push-ups)", "Swimming", "Weightlifting"
};

char* member_names[MAX_MEMBERS] = {"\uBC15\uC9C0\uC5F0", "Ethan Smith", "Helena Silva", "Liam Wilson"};
char* member_nicknames[MAX_MEMBERS] = {"Ariel", "Simba", "Belle", "Aladdin"};

char* health_scores[MAX_MEMBERS][MAX_TESTS + 1]; // nickname + 7 test scores
char training_status[8] = {'-', '-', '-', '-', '-', '-', '-', '-'}; // '-' = not started, 'P' = passed, 'F' = failed

void displayMainMenu() {
    printf("\n=== Main Menu ===\n");
    for (int i = 0; i < 3; i++) {
        printf("%s. %s\n", main_menu[i][0], main_menu[i][1]);
    }
    printf("0. Exit\n");
}

void displayTrainingMenu() {
    printf("\n=== Training Menu ===\n");
    for (int i = 0; i < 8; i++) {
        printf("%s. %s [%c]\n", training_menu[i][0], training_menu[i][1], training_status[i]);
    }
    printf("0. Back\n");
}

void enterEvaluation(int stage) {
    char input;
    printf("Would you like to enter the evaluation result? (Y/N): ");
    scanf(" %c", &input);

    if (input == 'Y' || input == 'y') {
        printf("Did you complete the training and pass the certification? (Y = P / N = F): ");
        scanf(" %c", &input);
        if (input == 'Y' || input == 'y') {
            training_status[stage] = 'P';
        } else {
            training_status[stage] = 'F';
        }
    }
}

void parseFitnessData(char* input, int member_index) {
    char* token = strtok(input, ",");
    int i = 0;
    health_scores[member_index][0] = member_nicknames[member_index];
    while (token != NULL && i < MAX_TESTS) {
        health_scores[member_index][i + 1] = strdup(token);
        token = strtok(NULL, ",");
        i++;
    }
}

void setHealth() {
    printf("\n--- Enter Fitness Data ---\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        char input[MAX_LEN];
        printf("Enter 7 test results for %s (%s), comma-separated:\n", member_names[i], member_nicknames[i]);
        scanf(" %[^\n]", input);
        parseFitnessData(input, i);
    }
}

void getHealth() {
    int option;
    printf("\n--- View Fitness Data ---\n");
    printf("1. View all members\n2. View one member\n3. View one test by one member\nEnter option: ");
    scanf(" %d", &option);

    if (option == 1) {
        for (int i = 0; i < MAX_MEMBERS; i++) {
            printf("%s: ", health_scores[i][0]);
            for (int j = 1; j <= MAX_TESTS; j++) {
                printf("%s%s", health_scores[i][j], j < MAX_TESTS ? ", " : "\n");
            }
        }
    } else if (option == 2) {
        char name[MAX_LEN];
        printf("Enter nickname: ");
        scanf(" %s", name);
        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(health_scores[i][0], name) == 0) {
                printf("%s: ", name);
                for (int j = 1; j <= MAX_TESTS; j++) {
                    printf("%s%s", health_scores[i][j], j < MAX_TESTS ? ", " : "\n");
                }
                break;
            }
        }
    } else if (option == 3) {
        char name[MAX_LEN];
        int test_num;
        printf("Enter nickname: ");
        scanf(" %s", name);
        printf("Select test (1-7): ");
        scanf(" %d", &test_num);
        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(health_scores[i][0], name) == 0 && test_num >= 1 && test_num <= 7) {
                printf("%s's %s: %s\n", name, test_names[test_num - 1], health_scores[i][test_num]);
                break;
            }
        }
    }
}

void handleStage1Submenu() {
    int choice;
    printf("\nA. Enter Fitness Data\nB. View Fitness Data\n0. Back\nSelect option: ");
    char option;
    scanf(" %c", &option);
    if (option == 'A' || option == 'a') {
        setHealth();
    } else if (option == 'B' || option == 'b') {
        getHealth();
    }
}

void trainingMenu() {
    while (1) {
        displayTrainingMenu();
        int choice;
        printf("Select training stage (0 to exit): ");
        scanf(" %d", &choice);
        if (choice == 0) return;
        if (choice < 1 || choice > 8) continue;

        int index = choice - 1;
        if (index == 0) {
            handleStage1Submenu();
            enterEvaluation(index);
        } else if (index == 1) {
            if (training_status[0] == 'P') {
                enterEvaluation(index);
            } else {
                printf("\nYou must pass Stage 1 first.\n");
            }
        } else {
            if (training_status[1] == 'P') {
                if (training_status[index] == '-') {
                    enterEvaluation(index);
                } else {
                    printf("\nStage already evaluated.\n");
                }
            } else {
                printf("\nYou must pass Stage 2 first.\n");
            }
        }
    }
}

int main() {
    while (1) {
        displayMainMenu();
        char input[MAX_LEN];
        printf("Select an option: ");
        scanf(" %s", input);

        if (strcmp(input, "0") == 0 || strcmp(input, "Q") == 0 || strcmp(input, "q") == 0 || strlen(input) == 0) {
            printf("Exiting...\n");
            break;
        } else if (strcmp(input, "II") == 0) {
            trainingMenu();
        } else {
            printf("\nOption not implemented yet.\n");
        }
    }
    return 0;
}
