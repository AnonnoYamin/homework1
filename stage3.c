#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_QUESTIONS 10
#define QUIZ_SIZE 5
#define MAX_TRAINEES 4

struct Question {
    int id;
    char content[100];
    char answer[100];
};

struct Trainee {
    char name[30];
    char nickname[30];
    char nationality[30];
    int quizScore;
    char passStatus;
};

struct Answer {
    int questionId;
    char correctness;
};

struct Question questionBank[MAX_QUESTIONS] = {
    {1, "What is \"hello\" in Korean?", "안녕하세요"},
    {2, "What is \"thank you\" in Korean?", "감사합니다"},
    {3, "What is \"goodbye\" in Korean?", "안녕히 가세요"},
    {4, "What is \"yes\" in Korean?", "네"},
    {5, "What is \"no\" in Korean?", "아니요"},
    {6, "What is \"sorry\" in Korean?", "죄송합니다"},
    {7, "What is \"I love you\" in Korean?", "사랑해요"},
    {8, "What is \"friend\" in Korean?", "친구"},
    {9, "What is \"food\" in Korean?", "음식"},
    {10, "What is \"water\" in Korean?", "물"}
};

struct Trainee trainees[MAX_TRAINEES] = {
    {"박지연", "Ariel", "Korean", 0, 'F'},
    {"Ethan Smith", "Simba", "American", 0, 'F'},
    {"Helena Silva", "Belle", "Brazilian", 0, 'F'},
    {"Liam Wilson", "Aladdin", "Canadian", 0, 'F'}
};

struct Answer quizAnswers[QUIZ_SIZE];

int isAnswer(int qid, const char *userAnswer) {
    for (int i = 0; i < MAX_QUESTIONS; i++) {
        if (questionBank[i].id == qid) {
            return strcmp(questionBank[i].answer, userAnswer) == 0;
        }
    }
    return 0;
}

int selectRandomTaker() {
    srand(time(NULL));
    int idx;
    do {
        idx = rand() % MAX_TRAINEES;
    } while (strcmp(trainees[idx].nationality, "Korean") == 0);
    printf("Welcome, %s, to the Korean quiz session!\n", trainees[idx].name);
    return idx;
}

void serveRandomQuiz(int traineeIndex) {
    int selected[QUIZ_SIZE] = {0};
    int score = 0;
    srand(time(NULL));

    printf("The quiz will start in 30 seconds. Please prepare...\n");
    sleep(30);

    for (int i = 0; i < QUIZ_SIZE; i++) {
        int qidx;
        do {
            qidx = rand() % MAX_QUESTIONS;
        } while (selected[qidx]);

        selected[qidx] = 1;
        struct Question q = questionBank[qidx];

        char userAnswer[100];
        printf("Q%d: %s\n", q.id, q.content);
        fgets(userAnswer, sizeof(userAnswer), stdin);
        userAnswer[strcspn(userAnswer, "\n")] = '\0';

        int correct = isAnswer(q.id, userAnswer);
        quizAnswers[i].questionId = q.id;
        quizAnswers[i].correctness = correct ? 'O' : 'X';

        if (correct) score += 20;
    }

    trainees[traineeIndex].quizScore = score;
    trainees[traineeIndex].passStatus = score >= 80 ? 'P' : 'F';

    printf("\nAnswer Sheet:\n");
    for (int i = 0; i < QUIZ_SIZE; i++) {
        printf("Question ID %d: %c\n", quizAnswers[i].questionId, quizAnswers[i].correctness);
    }
    printf("Total Score: %d\n", score);
    printf("Pass Status: %c\n", trainees[traineeIndex].passStatus);
}

void testKoreanLang() {
    int taker = selectRandomTaker();
    serveRandomQuiz(taker);
}

void trainingMenu();

void mainMenu() {
    char input[10];
    while (1) {
        printf("\n=== Main Menu ===\n");
        printf("1. Audition Management (I)\n");
        printf("2. Training (II)\n");
        printf("3. Debut (III)\n");
        printf("Select option (or Q to quit): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "Q") == 0 || strcmp(input, "q") == 0 || strcmp(input, "0") == 0 || strlen(input) == 0)
            break;

        if (strcmp(input, "1") == 0 || strcmp(input, "I") == 0 || strcmp(input, "i") == 0)
            continue;
        else if (strcmp(input, "2") == 0 || strcmp(input, "II") == 0 || strcmp(input, "ii") == 0)
            trainingMenu();
        else if (strcmp(input, "3") == 0 || strcmp(input, "III") == 0 || strcmp(input, "iii") == 0)
            continue;
        else
            printf("Invalid option. Please try again.\n");
    }
}

char stageStatus[8] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

void trainingMenu() {
    char input[10];
    while (1) {
        printf("\n--- Training Menu ---\n");
        for (int i = 0; i < 8; i++) {
            printf("%d. Training Stage %d [%c]\n", i + 1, i + 1, stageStatus[i]);
        }
        printf("Select stage (or Q to return): ");
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'Q' || input[0] == 'q') return;
        int choice = atoi(input);
        if (choice < 1 || choice > 8) continue;

        if ((choice > 2 && (stageStatus[0] != 'P' || stageStatus[1] != 'P')) || stageStatus[choice - 1] == 'P') continue;

        printf("Would you like to enter the evaluation result? (Y/N): ");
        fgets(input, sizeof(input), stdin);
        if (input[0] != 'Y' && input[0] != 'y') continue;

        printf("Did you complete the training and pass the certification? (Y/N): ");
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'Y' || input[0] == 'y') {
            stageStatus[choice - 1] = 'P';
            if (choice == 3) testKoreanLang();
        } else {
            stageStatus[choice - 1] = 'F';
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
