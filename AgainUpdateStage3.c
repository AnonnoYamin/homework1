#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 4
#define MAX_SENTENCES 10
#define MAX_WORDS 12
#define MAX_LEN 100

typedef struct {
    char english[MAX_LEN];
    char korean[MAX_LEN];
} SentencePair;

typedef struct {
    char nickname[MAX_LEN];
    int score;
} GrammarResult;

SentencePair sentencePairs[MAX_SENTENCES] = {
    {"I am a student.", "나는 학생 입니다 ."},
    {"She likes Korean food.", "그녀 는 한국 음식 을 좋아합니다 ."},
    {"We go to school together.", "우리는 함께 학교 에 갑니다 ."},
    {"He plays the guitar well.", "그는 기타 를 잘 칩니다 ."},
    {"They study Korean every day.", "그들은 매일 한국어 를 공부합니다 ."},
    {"The weather is very cold today.", "오늘 은 날씨 가 매우 춥습니다 ."},
    {"I want to visit Seoul.", "나는 서울 을 방문 하고 싶습니다 ."},
    {"My mother cooks delicious food.", "우리 엄마 는 맛있는 음식을 요리 합니다 ."},
    {"This book is interesting.", "이 책 은 재미 있습니다 ."},
    {"We watched a movie last night.", "우리는 어젯밤 에 영화를 봤습니다 ."}
};

GrammarResult grammarResults[MAX_TRAINEES] = {
    {"Ariel", 0},
    {"Simba", 0},
    {"Belle", 0},
    {"Aladdin", 0}
};

int played = 0;

void quickSort(char *arr[], int left, int right) {
    if (left >= right) return;
    char *pivot = arr[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (strcmp(arr[i], pivot) < 0) i++;
        while (strcmp(arr[j], pivot) > 0) j--;
        if (i <= j) {
            char *temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++; j--;
        }
    }
    if (left < j) quickSort(arr, left, j);
    if (i < right) quickSort(arr, i, right);
}

void shuffleWords(char *words[], int count) {
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char *temp = words[i];
        words[i] = words[j];
        words[j] = temp;
    }
}

int splitSentence(char *sentence, char *words[]) {
    int count = 0;
    char *token = strtok(sentence, " ");
    while (token != NULL && count < MAX_WORDS) {
        words[count++] = token;
        token = strtok(NULL, " ");
    }
    return count;
}

void composeSentences(char *nickname) {
    int score = 0;
    int used[MAX_SENTENCES] = {0};
    srand(time(NULL));

    for (int q = 0; q < 5; q++) {
        int index;
        do {
            index = rand() % MAX_SENTENCES;
        } while (used[index]);
        used[index] = 1;

        printf("\nQ%d. English: %s\n", q + 1, sentencePairs[index].english);

        char koreanCopy[MAX_LEN];
        strcpy(koreanCopy, sentencePairs[index].korean);

        char *words[MAX_WORDS];
        int wordCount = splitSentence(koreanCopy, words);

        shuffleWords(words, wordCount);
        quickSort(words, 0, wordCount - 1);

        printf("Shuffled Korean words:\n");
        for (int i = 0; i < wordCount; i++) {
            printf("%s ", words[i]);
        }

        printf("\nEnter Korean sentence:\n> ");
        char answer[MAX_LEN];
        getchar();
        fgets(answer, MAX_LEN, stdin);
        answer[strcspn(answer, "\n")] = 0;

        if (strcmp(answer, sentencePairs[index].korean) == 0) {
            printf("Correct!\n");
            score += 20;
        } else {
            printf("Incorrect! Correct answer: %s\n", sentencePairs[index].korean);
        }
    }

    for (int i = 0; i < MAX_TRAINEES; i++) {
        if (strcmp(grammarResults[i].nickname, nickname) == 0) {
            grammarResults[i].score += score;
            break;
        }
    }
    played = 1;
}

void printScore(char *nickname) {
    if (!played) {
        printf("Please complete a grammar challenge first.\n");
        return;
    }

    printf("\n%s's Total Grammar Score: ", nickname);
    for (int i = 0; i < MAX_TRAINEES; i++) {
        if (strcmp(grammarResults[i].nickname, nickname) == 0) {
            printf("%d\n", grammarResults[i].score);
            break;
        }
    }

    GrammarResult sorted[MAX_TRAINEES];
    memcpy(sorted, grammarResults, sizeof(grammarResults));

    for (int i = 0; i < MAX_TRAINEES - 1; i++) {
        for (int j = i + 1; j < MAX_TRAINEES; j++) {
            if (sorted[i].score < sorted[j].score) {
                GrammarResult temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }

    printf("\n=== Rankings ===\n");
    for (int i = 0; i < MAX_TRAINEES; i++) {
        printf("%d. %s - %d points\n", i + 1, sorted[i].nickname, sorted[i].score);
    }
}

void learnKoreanGrammar() {
    char nickname[MAX_LEN];
    int found = 0, attempts = 0;

    while (attempts < 3 && !found) {
        printf("Enter your nickname: ");
        scanf("%s", nickname);
        for (int i = 0; i < MAX_TRAINEES; i++) {
            if (strcmp(grammarResults[i].nickname, nickname) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Nickname not found. Try again.\n");
            attempts++;
        }
    }

    if (!found) {
        printf("Returning to previous menu.\n");
        return;
    }

    while (1) {
        printf("\n1. Compose Korean Sentences\n2. Check Scores\n0. Back\nSelect: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                composeSentences(nickname);
                break;
            case 2:
                printScore(nickname);
                break;
            case 0:
                return;
            default:
                printf("Invalid option.\n");
        }
    }
}

void mainMenu() {
    char choice[MAX_LEN];
    while (1) {
        printf("\n=== Main Menu ===\n1. Audition Management\n2. Training\n3. Debut\nSelect option (or Q to quit): ");
        scanf("%s", choice);
        if (strcmp(choice, "Q") == 0 || strcmp(choice, "q") == 0)
            break;

        if (strcmp(choice, "2") == 0) {
            char subChoice[MAX_LEN];
            printf("\n--- Training ---\n1. Physical Training\n2. Dance Training\n3. Language and Pronunciation Training\nSelect: ");
            scanf("%s", subChoice);
            if (strcmp(subChoice, "3") == 0) {
                char langChoice[MAX_LEN];
                printf("\n--- Language & Pronunciation ---\nA. Pronunciation\nB. Hangul Jamo Learning\nC. Learning Korean Grammar\nSelect: ");
                scanf("%s", langChoice);
                if (strcmp(langChoice, "C") == 0 || strcmp(langChoice, "c") == 0) {
                    learnKoreanGrammar();
                }
            }
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
