#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME 100
#define MAX_DETAIL 1000
#define NUM_SUBJECTS 7
#define MAX_STAGES 8

typedef struct Subjects {
    char name[MAX_NAME];
    char detail[MAX_DETAIL];
    struct Subjects *next;
} Subjects;

Subjects *head = NULL;
char *subjectNames[NUM_SUBJECTS] = {
    "Acting Theory",
    "Stage Theory",
    "Script Analysis",
    "Dialogue Interpretation and Emotional Expression",
    "Character Development",
    "Storytelling Theory",
    "Stage Movement and Poses"
};

char trainingResults[MAX_STAGES] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

void createSubjectList() {
    Subjects *temp, *tail = NULL;
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        temp = (Subjects *)malloc(sizeof(Subjects));
        strcpy(temp->name, subjectNames[i]);
        strcpy(temp->detail, "");
        temp->next = NULL;
        if (head == NULL)
            head = temp;
        else
            tail->next = temp;
        tail = temp;
    }
}

void updateSubjectInfo(char *line) {
    Subjects *cur = head;
    while (cur) {
        if (strstr(line, cur->name)) {
            strncpy(cur->detail, line, MAX_DETAIL - 1);
            return;
        }
        cur = cur->next;
    }
}

void loadContentFile() {
    FILE *fp = fopen("perform_stage.txt", "r");
    if (!fp) {
        printf("Could not open perform_stage.txt. Using dummy data.\n");
        for (int i = 0; i < NUM_SUBJECTS; i++) {
            Subjects *cur = head;
            for (int j = 0; j < i; j++) cur = cur->next;
            sprintf(cur->detail, "%s: This is a dummy explanation of the subject for training. It helps the trainee understand essential concepts.", cur->name);
        }
        return;
    }
    char line[MAX_DETAIL];
    while (fgets(line, sizeof(line), fp)) {
        updateSubjectInfo(line);
    }
    fclose(fp);
}

void printSubjectList() {
    Subjects *cur = head;
    int idx = 1;
    while (cur) {
        printf("%d. %s\n", idx++, cur->name);
        for (int i = 0; i < strlen(cur->detail); i++) {
            putchar(cur->detail[i]);
            if (cur->detail[i] == '.') putchar('\n');
        }
        printf("\n\n");
        cur = cur->next;
    }
}

void learnPerformanceStageTheory() {
    if (head == NULL) createSubjectList();
    loadContentFile();
    printSubjectList();
}

void showMainMenu();
void showTrainingMenu();

void showTrainingMenu() {
    int stage;
    printf("\n--- Training Menu ---\n");
    for (int i = 0; i < MAX_STAGES; i++) {
        printf("%d. Stage %d\n", i + 1, i + 1);
    }
    printf("Select training stage (1-8): ");
    scanf("%d", &stage);
    getchar();

    if (stage < 1 || stage > 8) return;
    if (stage > 2 && (trainingResults[0] != 'P' || trainingResults[1] != 'P')) {
        printf("\nAccess denied. Complete Stage 1 and 2 first.\n");
        return;
    }
    if (trainingResults[stage - 1] == 'P') {
        printf("\nStage already completed.\n");
        return;
    }

    char yn;
    printf("\nWould you like to enter the evaluation result? (Y/N): ");
    scanf(" %c", &yn);
    getchar();
    yn = toupper(yn);
    if (yn == 'Y') {
        char pass;
        printf("Did you complete the training and pass the certification? (P/F): ");
        scanf(" %c", &pass);
        getchar();
        pass = toupper(pass);
        if (pass == 'P' || pass == 'F') {
            trainingResults[stage - 1] = pass;
            if (stage == 7 && pass == 'P') {
                learnPerformanceStageTheory();
            }
        } else {
            printf("Invalid input.\n");
        }
    }
}

void showMainMenu() {
    char input[10];
    while (1) {
        printf("\n=== Magrathea System ===\n");
        printf("I. Audition Management\n");
        printf("II. Training\n");
        printf("III. Debut\n");
        printf("Enter choice (I/II/III or Q to quit): ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '0' || input[0] == 'Q' || input[0] == 'q' || input[0] == '\n') break;

        if (strncmp(input, "II", 2) == 0 || strncmp(input, "2", 1) == 0) {
            showTrainingMenu();
        } else {
            printf("Feature not implemented.\n");
        }
    }
    printf("Exiting Magrathea System.\n");
}

int main() {
    showMainMenu();
    return 0;
}
