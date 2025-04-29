#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MEMBERS 4
#define MAX_LEN 100

const char *member_names[MAX_MEMBERS] = {"\uBC15\uC9C0\uC5F0", "Ethan Smith", "Helena Silva", "Liam Wilson"};
const char *member_nicknames[MAX_MEMBERS] = {"Ariel", "Simba", "Belle", "Aladdin"};
const char *member_allergies[MAX_MEMBERS] = {"Dairy", "Peanuts", "Fish", "Shellfish"};

const char *days[6] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const char *exercise_types[5][3] = {
    {"Running", "Cycling", "Fast Walking"},               // Cardio
    {"Push-ups", "Squats", ""},                           // Full-body Strength
    {"Leg Press", "Leg Curl", ""},                        // Lower-body Strength
    {"Pull-ups", "Chin-ups", ""},                         // Upper-body Strength
    {"Plank", "Crunches", ""}                             // Core Strength
};

char member_routine[MAX_MEMBERS][6][MAX_LEN];
char diet_plan[MAX_MEMBERS][6][MAX_LEN];

// Utility: Display member list
void displayMemberList() {
    printf("\n--- Milliways Member List ---\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("%d. %s (%s) | Allergy: %s\n", i + 1, member_names[i], member_nicknames[i], member_allergies[i]);
    }
}

int coreUsedThisWeek(int member_index) {
    for (int i = 0; i < 6; i++) {
        if (strstr(member_routine[member_index][i], "Plank") || strstr(member_routine[member_index][i], "Crunches")) {
            return 1;
        }
    }
    return 0;
}

void setExerciseRoutine() {
    printf("\n--- Set Basic Workout Routine ---\n");
    displayMemberList();
    int index;
    printf("Select a member (1-%d): ", MAX_MEMBERS);
    scanf("%d", &index);
    index--;
    getchar();
    if (index < 0 || index >= MAX_MEMBERS) {
        printf("Invalid member selected.\n");
        return;
    }
    for (int d = 0; d < 6; d++) {
        printf("\nDay: %s\n", days[d]);
        char routine[MAX_LEN] = "";
        printf("Choose a cardio exercise:\n");
        for (int i = 0; i < 3; i++) printf("%d. %s\n", i + 1, exercise_types[0][i]);
        int cardio_choice;
        scanf("%d", &cardio_choice);
        strcat(routine, exercise_types[0][cardio_choice - 1]);
        printf("Choose strength/core: 1.Full 2.Lower 3.Upper 4.Core\n");
        int cat;
        scanf("%d", &cat);
        if (cat == 4 && coreUsedThisWeek(index)) {
            printf("Core already used. Choose again.\n"); d--; continue;
        }
        for (int i = 0; i < 2 && strlen(exercise_types[cat][i]) > 0; i++)
            printf("%d. %s\n", i + 1, exercise_types[cat][i]);
        int ex_choice;
        scanf("%d", &ex_choice);
        strcat(routine, ", ");
        strcat(routine, exercise_types[cat][ex_choice - 1]);
        strcpy(member_routine[index][d], routine);
    }
    printf("Workout routine saved.\n");
}

void getExerciseRoutine() {
    printf("\n--- View Basic Workout Routine ---\n");
    displayMemberList();
    char name[MAX_LEN];
    printf("Enter member name: ");
    getchar();
    fgets(name, MAX_LEN, stdin);
    name[strcspn(name, "\n")] = 0;
    int index = -1;
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(name, member_names[i]) == 0) { index = i; break; }
    }
    if (index == -1) { printf("Member not found.\n"); return; }
    for (int i = 0; i < 6; i++) {
        printf("%s: %s\n", days[i], member_routine[index][i]);
    }
}

void setDietPlan() {
    printf("\n--- Set Diet Plan ---\n");
    displayMemberList();
    int index;
    printf("Select a member (1-%d): ", MAX_MEMBERS);
    scanf("%d", &index);
    index--;
    getchar();
    if (index < 0 || index >= MAX_MEMBERS) {
        printf("Invalid member selected.\n"); return;
    }
    for (int i = 0; i < 6; i++) {
        char food[MAX_LEN];
        printf("Day: %s\nEnter diet (avoid %s): ", days[i], member_allergies[index]);
        fgets(food, MAX_LEN, stdin);
        food[strcspn(food, "\n")] = 0;
        if (strstr(food, member_allergies[index])) {
            printf("Contains allergen! Try again.\n"); i--; continue;
        }
        strcpy(diet_plan[index][i], food);
    }
    printf("Diet plan saved.\n");
}

void viewDietPlan() {
    printf("\n--- View Diet Plan ---\n");
    displayMemberList();
    char name[MAX_LEN];
    printf("Enter member name: ");
    getchar();
    fgets(name, MAX_LEN, stdin);
    name[strcspn(name, "\n")] = 0;
    int index = -1;
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(name, member_names[i]) == 0) { index = i; break; }
    }
    if (index == -1) { printf("Member not found.\n"); return; }
    for (int i = 0; i < 6; i++) {
        printf("%s: %s\n", days[i], diet_plan[index][i]);
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n--- Milliways Health Management System ---\n");
        printf("1. Set Workout Routine\n2. View Workout Routine\n3. Set Diet Plan\n4. View Diet Plan\n5. Exit\n");
        printf("Select option: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: setExerciseRoutine(); break;
            case 2: getExerciseRoutine(); break;
            case 3: setDietPlan(); break;
            case 4: viewDietPlan(); break;
            case 5: return 0;
            default: printf("Invalid option.\n");
        }
    }
}
