#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_STEPS 10
#define MAX_DANCES 6
#define MAX_MEMBERS 4
#define MAX_NAME_LEN 20
#define MAX_STEP_LEN 30
#define MAX_NICK_LEN 10

typedef struct {
    char koreanName[MAX_NAME_LEN];
    char englishName[MAX_NAME_LEN];
    int stepCount;
    char steps[MAX_STEPS][MAX_STEP_LEN];
} Dance;

typedef struct {
    char name[MAX_NAME_LEN];
    char nickname[MAX_NICK_LEN];
    int score;
} Member;

Member members[MAX_MEMBERS] = {
    {"박지연", "Ariel", 0},
    {"Ethan Smith", "Simba", 0},
    {"Helena Silva", "Belle", 0},
    {"Liam Wilson", "Aladdin", 0}
};

Dance dances[MAX_DANCES];

void clearStdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int randomInt(int max) {
    return rand() % max;
}

void writeDemoDanceSteps() {
    const char *demoData =
        "댄스1,Dance1,4\n"
        "Step Forward\n"
        "Step Back\n"
        "Turn Left\n"
        "Clap Hands\n"
        "댄스2,Dance2,3\n"
        "Jump\n"
        "Spin\n"
        "Bow\n"
        "댄스3,Dance3,5\n"
        "Slide Right\n"
        "Slide Left\n"
        "Step Forward\n"
        "Step Back\n"
        "Raise Hands\n"
        "댄스4,Dance4,2\n"
        "Snap Fingers\n"
        "Stomp Feet\n"
        "댄스5,Dance5,3\n"
        "Kick\n"
        "Jump\n"
        "Clap\n"
        "댄스6,Dance6,4\n"
        "Step Left\n"
        "Step Right\n"
        "Spin\n"
        "Jump\n";

    FILE *fp = fopen("dance_step.txt", "w");
    if (!fp) {
        printf("Error creating dance_step.txt\n");
        exit(1);
    }
    fputs(demoData, fp);
    fclose(fp);
}

int readDanceSteps(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Failed to open %s\n", filename);
        return 0;
    }

    for (int i = 0; i < MAX_DANCES; i++) {
        if (fscanf(fp, "%[^,],%[^,],%d\n", dances[i].koreanName, dances[i].englishName, &dances[i].stepCount) != 3) {
            printf("Error reading dance info for dance %d\n", i+1);
            fclose(fp);
            return 0;
        }

        if (dances[i].stepCount > MAX_STEPS) {
            printf("Too many steps for dance %s\n", dances[i].englishName);
            fclose(fp);
            return 0;
        }

        for (int j = 0; j < dances[i].stepCount; j++) {
            if (!fgets(dances[i].steps[j], MAX_STEP_LEN, fp)) {
                printf("Error reading step %d for dance %s\n", j+1, dances[i].englishName);
                fclose(fp);
                return 0;
            }
            dances[i].steps[j][strcspn(dances[i].steps[j], "\n")] = 0;
        }
    }

    fclose(fp);
    return 1;
}

int findMemberIndexByNickname(const char *nickname) {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(members[i].nickname, nickname) == 0) {
            return i;
        }
    }
    return -1;
}

void printSteps(const char steps[][MAX_STEP_LEN], int count) {
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, steps[i]);
    }
}

void shuffleSteps(char steps[][MAX_STEP_LEN], int count) {
    for (int i = count - 1; i > 0; i--) {
        int j = randomInt(i + 1);
        char temp[MAX_STEP_LEN];
        strcpy(temp, steps[i]);
        strcpy(steps[i], steps[j]);
        strcpy(steps[j], temp);
    }
}

int allMatch(char userSteps[][MAX_STEP_LEN], char correctSteps[][MAX_STEP_LEN], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(userSteps[i], correctSteps[i]) != 0) {
            return 0;
        }
    }
    return 1;
}

int allCorrectWrongOrder(char userSteps[][MAX_STEP_LEN], char correctSteps[][MAX_STEP_LEN], int count) {
    int matched[MAX_STEPS] = {0};
    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < count; j++) {
            if (!matched[j] && strcmp(userSteps[i], correctSteps[j]) == 0) {
                matched[j] = 1;
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

int atLeastOneCorrect(char userSteps[][MAX_STEP_LEN], char correctSteps[][MAX_STEP_LEN], int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (strcmp(userSteps[i], correctSteps[j]) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void waitSeconds(int seconds) {
#ifdef _WIN32
    char cmd[50];
    sprintf(cmd, "timeout /t %d >nul", seconds);
    system(cmd);
#else
    sleep(seconds);
#endif
}

void learnDanceStep() {
    char nickname[MAX_NICK_LEN];
    int memberIndex = -1;

    for (int attempts = 0; attempts < 3; attempts++) {
        printf("Enter your Milliways nickname: ");
        scanf("%9s", nickname);
        clearStdin();

        memberIndex = findMemberIndexByNickname(nickname);
        if (memberIndex != -1) break;
        printf("Nickname not found. Try again.\n");
    }
    if (memberIndex == -1) {
        printf("Failed to verify nickname after 3 attempts. Returning to upper menu.\n");
        return;
    }

    writeDemoDanceSteps();  // Write demo dance_step.txt before reading

    if (!readDanceSteps("dance_step.txt")) {
        printf("Failed to read dance step file.\n");
        return;
    }

    srand((unsigned int)time(NULL));
    int selectedDanceIndex = randomInt(MAX_DANCES);
    Dance *selectedDance = &dances[selectedDanceIndex];

    printf("Memorize the dance steps:\n");
    printf("%s (%s)\n", selectedDance->koreanName, selectedDance->englishName);
    printSteps(selectedDance->steps, selectedDance->stepCount);

    printf("\nSteps will be shown for 10 seconds...\n");
    waitSeconds(10);

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    char shuffledSteps[MAX_STEPS][MAX_STEP_LEN];
    for (int i = 0; i < selectedDance->stepCount; i++) {
        strcpy(shuffledSteps[i], selectedDance->steps[i]);
    }
    shuffleSteps(shuffledSteps, selectedDance->stepCount);

    printf("Enter the dance steps in correct order:\n");
    for (int i = 0; i < selectedDance->stepCount; i++) {
        printf("%d. ", i + 1);
        fgets(shuffledSteps[i], MAX_STEP_LEN, stdin);
        shuffledSteps[i][strcspn(shuffledSteps[i], "\n")] = 0;
    }

    int score = 0;
    if (allMatch(shuffledSteps, selectedDance->steps, selectedDance->stepCount)) {
        score = 100;
    } else if (allCorrectWrongOrder(shuffledSteps, selectedDance->steps, selectedDance->stepCount)) {
        score = 50;
    } else if (atLeastOneCorrect(shuffledSteps, selectedDance->steps, selectedDance->stepCount)) {
        score = 20;
    } else {
        score = 0;
    }

    printf("\nCorrect Steps:\n");
    printSteps(selectedDance->steps, selectedDance->stepCount);

    printf("\nYour Input:\n");
    printSteps(shuffledSteps, selectedDance->stepCount);

    printf("\nScore: %d\n", score);
    members[memberIndex].score = score;
}

int main() {
    learnDanceStep();
    return 0;
}
