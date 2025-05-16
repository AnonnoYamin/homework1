/*
 * stage5.c - Dance Training System with Choreography Pattern Learning
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#define CLEAR "cls"
#else
#include <unistd.h>
#define CLEAR "clear"
#endif

#define MAX_LINE 256
#define MAX_PATTERN 6
#define MAX_DESC 150
#define MAX_NAME 30

// MilliWays members
const char *valid_nicknames[] = {"Ariel", "Simba", "Belle", "Aladdin"};
#define NUM_NICKNAMES 4

// Choreography Pattern Structure
typedef struct {
    char name[MAX_NAME];
    char description[MAX_DESC];
} ChoreoPattern;

// Song Choreography Node
typedef struct PatternNode {
    char pattern[MAX_NAME];
    struct PatternNode *next;
} PatternNode;

typedef struct SongTree {
    char songName[MAX_NAME];
    PatternNode *head;
    struct SongTree *next;
} SongTree;

ChoreoPattern patterns[MAX_PATTERN];
int totalPatterns = 0;

// Utility Functions
int is_valid_nickname(const char *name) {
    for (int i = 0; i < NUM_NICKNAMES; i++) {
        if (strcmp(valid_nicknames[i], name) == 0) return 1;
    }
    return 0;
}

char *random_substring(const char *src) {
    static char sub[11];
    int len = strlen(src);
    int count = 0, start;
    char temp[MAX_DESC];
    for (int i = 0; i < len; i++) {
        if (src[i] != ' ') temp[count++] = src[i];
    }
    if (count < 10) start = 0;
    else start = rand() % (count - 9);
    strncpy(sub, temp + start, 10);
    sub[10] = '\0';
    return sub;
}

void load_choreo_patterns() {
    FILE *fp = fopen("dance_pattern.txt", "r");
    if (!fp) {
        printf("Error: Cannot open dance_pattern.txt\n");
        return;
    }
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp) && totalPatterns < MAX_PATTERN) {
        line[strcspn(line, "\n")] = 0;
        char *comma = strchr(line, ',');
        if (comma) {
            *comma = '\0';
            strcpy(patterns[totalPatterns].name, line);
            strcpy(patterns[totalPatterns].description, comma + 1);
            totalPatterns++;
        }
    }
    fclose(fp);
}

SongTree *create_song_tree(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: Cannot open %s\n", filename);
        return NULL;
    }
    char line[MAX_LINE];
    fgets(line, sizeof(line), fp); // skip header
    SongTree *head = NULL, *tail = NULL;
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;
        char *token = strtok(line, ",");
        SongTree *song = (SongTree *)malloc(sizeof(SongTree));
        strcpy(song->songName, token);
        song->head = NULL;
        song->next = NULL;
        PatternNode *last = NULL;
        token = strtok(NULL, ",");
        char *p = strtok(token, ";");
        while (p) {
            PatternNode *node = (PatternNode *)malloc(sizeof(PatternNode));
            strcpy(node->pattern, p);
            node->next = NULL;
            if (!song->head) song->head = node;
            else last->next = node;
            last = node;
            p = strtok(NULL, ";");
        }
        if (!head) head = song;
        else tail->next = song;
        tail = song;
    }
    fclose(fp);
    return head;
}

void free_song_tree(SongTree *head) {
    while (head) {
        PatternNode *node = head->head;
        while (node) {
            PatternNode *tmp = node;
            node = node->next;
            free(tmp);
        }
        SongTree *tmp = head;
        head = head->next;
        free(tmp);
    }
}

void traverse_and_print(SongTree *head) {
    SongTree *curr = head;
    while (curr) {
        printf("%s: ", curr->songName);
        PatternNode *p = curr->head;
        while (p) {
            printf("%s ", p->pattern);
            p = p->next;
        }
        printf("\n");
        curr = curr->next;
    }
}

void bonus_song_quiz(SongTree *head) {
    SongTree *curr = head;
    int index = 1;
    printf("\nAvailable Songs:\n");
    while (curr) {
        printf("[%d] %s\n", index++, curr->songName);
        curr = curr->next;
    }
    printf("Choose a song number: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    curr = head;
    for (int i = 1; i < choice && curr; i++) curr = curr->next;
    if (!curr) return;

    PatternNode *p = curr->head;
    printf("\nStart with: %s\n", p->pattern);
    p = p->next;
    while (p) {
        char input[MAX_NAME];
        printf("Next pattern: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        if (strcmp(input, p->pattern) != 0) {
            printf("Incorrect. Returning to menu.\n");
            return;
        }
        p = p->next;
    }
    printf("\nCongratulations! You completed the song pattern!\n");
}

void learnDancePattern() {
    srand(time(NULL));
    load_choreo_patterns();
    if (totalPatterns < MAX_PATTERN) {
        printf("Not enough patterns loaded.\n");
        return;
    }
    int score = 0;
    for (int i = 0; i < 4; i++) {
        int idx = rand() % totalPatterns;
        char *substr = random_substring(patterns[idx].description);
        printf("\nPattern Description: %s\n", patterns[idx].description);
        printf("Hint Substring (10-char): %s\n", substr);
        printf("Enter pattern name: ");
        char input[MAX_NAME];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        if (strcmp(input, patterns[idx].name) == 0) score++;
    }
    if (score < 3) {
        printf("\nScore too low. Returning to menu.\n");
        return;
    }
    SongTree *tree = create_song_tree("analyz_dance-pattern.csv");
    if (!tree) return;
    system(CLEAR);
    printf("\nChoreography Patterns by Song:\n");
    traverse_and_print(tree);
    bonus_song_quiz(tree);
    free_song_tree(tree);
}

// Menu Stub
void danceTrainingMenu() {
    int option;
    while (1) {
        printf("\n[ Dance Training Menu ]\n");
        printf("1. Basic Dance Steps\n");
        printf("2. B. Choreography Patterns\n");
        printf("0. Back\n");
        printf("Choose an option: ");
        scanf("%d", &option);
        getchar();
        if (option == 1) {
            printf("\n(Not Implemented Here: Basic Dance Steps)\n");
        } else if (option == 2) {
            learnDancePattern();
        } else if (option == 0) return;
        else printf("Invalid input.\n");
    }
}

int main() {
    char nickname[20];
    printf("Enter your trainee nickname: ");
    fgets(nickname, sizeof(nickname), stdin);
    nickname[strcspn(nickname, "\n")] = 0;
    if (!is_valid_nickname(nickname)) {
        printf("Invalid nickname. Access denied.\n");
        return 1;
    }
    int mainOpt;
    while (1) {
        printf("\n[ Main Menu ]\n");
        printf("1. Training\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &mainOpt);
        getchar();
        if (mainOpt == 1) {
            danceTrainingMenu();
        } else if (mainOpt == 0) {
            printf("Goodbye!\n");
            break;
        } else {
            printf("Invalid input.\n");
        }
    }
    return 0;
}
