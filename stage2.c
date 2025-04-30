#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRAINEES 10
#define MAX_MENTORS 8

// Structure for trainees
typedef struct {
    char nickname[50];
    int ability;
    int parsedNickname;
} Trainee;

// Structure for mentors
typedef struct {
    int mentorID;
    char name[50];
    int menteeID;
} Mentor;

Trainee trainees[MAX_TRAINEES];
Mentor mentors[MAX_MENTORS];

// Function prototypes
void parseIntMember();
int getRandomAbility();
void initializeTrainees();
void inputMentors();
void shuffleTrainees();
void matchMentoring();
void printMentoringResults();

int main() {
    srand(time(NULL));
    initializeTrainees();
    inputMentors();
    matchMentoring();
    printMentoringResults();
    return 0;
}

void parseIntMember() {
    for (int i = 0; i < MAX_TRAINEES; i++) {
        int sum = 0;
        for (int j = 0; trainees[i].nickname[j] != '\0'; j++) {
            sum += trainees[i].nickname[j];
        }
        trainees[i].parsedNickname = sum;
    }
}

int getRandomAbility() {
    return (rand() % 901) + 100; // Random number between 100 and 1000
}

void initializeTrainees() {
    strcpy(trainees[0].nickname, "Ariel");
    strcpy(trainees[1].nickname, "Simba");
    strcpy(trainees[2].nickname, "Belle");
    strcpy(trainees[3].nickname, "Aladdin");

    for (int i = 0; i < MAX_TRAINEES; i++) {
        trainees[i].ability = getRandomAbility();
    }

    parseIntMember();
}

void inputMentors() {
    for (int i = 0; i < MAX_MENTORS; i++) {
        mentors[i].mentorID = i + 1;
        printf("Enter mentor %d name: ", i + 1);
        fgets(mentors[i].name, sizeof(mentors[i].name), stdin);
        mentors[i].name[strcspn(mentors[i].name, "\n")] = '\0';  // Remove newline
        mentors[i].menteeID = -1;
    }
}

void shuffleTrainees() {
    for (int i = 0; i < MAX_TRAINEES; i++) {
        int j = rand() % MAX_TRAINEES;
        Trainee temp = trainees[i];
        trainees[i] = trainees[j];
        trainees[j] = temp;
    }
}

void matchMentoring() {
    shuffleTrainees();

    for (int i = 0; i < MAX_TRAINEES; i++) {
        for (int j = 0; j < MAX_MENTORS; j++) {
            if (mentors[j].menteeID == -1) {
                mentors[j].menteeID = i;
                break;
            }
        }
    }
}

void printMentoringResults() {
    printf("\nMentor-Mentee Assignments:\n");
    for (int i = 0; i < MAX_MENTORS; i++) {
        printf("Mentor ID: %d, Mentor Name: %s, Trainee Nickname: %s\n",
               mentors[i].mentorID, mentors[i].name, trainees[mentors[i].menteeID].nickname);
    }
}
