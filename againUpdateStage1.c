#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MEMBERS 4
#define MAX_LEN 100

const char *member_names[MAX_MEMBERS] = {"박지연", "Ethan Smith", "Helena Silva", "Liam Wilson"};
const char *member_nicknames[MAX_MEMBERS] = {"Ariel", "Simba", "Belle", "Aladdin"};

const char *days[6] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const char *exercise_types[5][3] = {
    {"Running", "Cycling", "Fast Walking"},
    {"Push-ups", "Squats", ""},
    {"Leg Press", "Leg Curl", ""},
    {"Pull-ups", "Chin-ups", ""},
    {"Plank", "Crunches", ""}
};

char member_routine[MAX_MEMBERS][6][MAX_LEN];

void displayMemberList() {
    printf("\n--- Milliways Member List ---\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("%d. %s (%s)\n", i + 1, member_names[i], member_nicknames[i]);
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

    printf("\nSet workout for %s (%s):\n", member_names[index], member_nicknames[index]);

    for (int d = 0; d < 6; d++) {
        printf("\nDay: %s\n", days[d]);
        char routine[MAX_LEN] = "";

        printf("Choose a cardio exercise:\n");
        for (int i = 0; i < 3; i++) {
            printf("%d. %s\n", i + 1, exercise_types[0][i]);
        }
        int cardio_choice;
        scanf("%d", &cardio_choice);
        strcat(routine, exercise_types[0][cardio_choice - 1]);

        printf("Choose a strength/core category:\n1. Full-body\n2. Lower-body\n3. Upper-body\n4. Core\n");
        int category_choice;
        scanf("%d", &category_choice);

        if (category_choice == 4 && coreUsedThisWeek(index)) {
            printf("Core exercise already used this week. Choose another category.\n");
            d--;
            continue;
        }

        printf("Choose an exercise:\n");
        for (int i = 0; i < 2 && strlen(exercise_types[category_choice][i]) > 0; i++) {
            printf("%d. %s\n", i + 1, exercise_types[category_choice][i]);
        }
        int ex_choice;
        scanf("%d", &ex_choice);
        strcat(routine, ", ");
        strcat(routine, exercise_types[category_choice][ex_choice - 1]);

        strcpy(member_routine[index][d], routine);
    }
    printf("Workout routine saved for %s (%s).\n", member_names[index], member_nicknames[index]);
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
        if (strcmp(name, member_names[i]) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Member not found.\n");
        return;
    }

    printf("\nWorkout Routine for %s (%s):\n", member_names[index], member_nicknames[index]);
    for (int i = 0; i < 6; i++) {
        printf("%s: %s\n", days[i], member_routine[index][i]);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Milliways Gym Menu ---\n");
        printf("1. Set Workout Routine\n");
        printf("2. View Workout Routine\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                setExerciseRoutine();
                break;
            case 2:
                getExerciseRoutine();
                break;
            case 3:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
