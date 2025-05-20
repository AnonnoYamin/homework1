#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME 50
#define MAX_DESC 200
#define MAX_LINE 300
#define MAX_QUEUE 4

typedef struct {
    char group[MAX_NAME];
    char concept[MAX_NAME];
    char description[MAX_DESC];
} ConceptInfo;

typedef struct Node {
    char data[MAX_NAME];
    struct Node *next;
} Node;

typedef struct {
    Node *front, *rear;
    int size;
} Queue;

typedef struct {
    char data[MAX_NAME];
} Stack;

ConceptInfo *concepts = NULL;
int conceptCount = 0;

void enqueue(Queue *q, const char *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->data, data);
    newNode->next = NULL;
    if (q->rear)
        q->rear->next = newNode;
    else
        q->front = newNode;
    q->rear = newNode;
    q->size++;
}

char *dequeue(Queue *q) {
    if (!q->front) return NULL;
    Node *temp = q->front;
    char *data = strdup(temp->data);
    q->front = q->front->next;
    if (!q->front)
        q->rear = NULL;
    free(temp);
    q->size--;
    return data;
}

void push(Stack *s, int *top, const char *data) {
    if (*top >= MAX_QUEUE) return;
    strcpy(s[*top].data, data);
    (*top)++;
}

char *pop(Stack *s, int *top) {
    if (*top <= 0) return NULL;
    (*top)--;
    return s[*top].data;
}

void shuffle(char arr[][MAX_NAME], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp[MAX_NAME];
        strcpy(temp, arr[i]);
        strcpy(arr[i], arr[j]);
        strcpy(arr[j], temp);
    }
}

void loadConcepts(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return;
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp))
        conceptCount++;
    fseek(fp, 0, SEEK_SET);
    concepts = (ConceptInfo *)malloc(sizeof(ConceptInfo) * conceptCount);
    int idx = 0;
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;
        char *group = strtok(line, "|");
        char *concept = strtok(NULL, "|");
        char *desc = strtok(NULL, "|");
        if (group && concept && desc) {
            strcpy(concepts[idx].group, group);
            strcpy(concepts[idx].concept, concept);
            strcpy(concepts[idx].description, desc);
            idx++;
        }
    }
    fclose(fp);
    conceptCount = idx;
}

void defineConcept() {
    loadConcepts("concept.txt");
    if (conceptCount == 0) {
        printf("No concept data available.\n");
        return;
    }

    int method;
    printf("Select data structure method:\n1. Queue\n2. Stack\n> ");
    scanf("%d", &method);
    if (method != 1 && method != 2) return;

    int n;
    printf("Enter number of data sets to extract (max %d): ", conceptCount < MAX_QUEUE ? conceptCount : MAX_QUEUE);
    scanf("%d", &n);
    if (n > conceptCount) n = conceptCount;
    if (n > MAX_QUEUE) n = MAX_QUEUE;

    char groups[n][MAX_NAME], conceptsOnly[n][MAX_NAME];
    srand(time(NULL));
    int used[conceptCount];
    memset(used, 0, sizeof(used));
    int count = 0;
    while (count < n) {
        int idx = rand() % conceptCount;
        if (!used[idx]) {
            strcpy(groups[count], concepts[idx].group);
            strcpy(conceptsOnly[count], concepts[idx].concept);
            used[idx] = 1;
            count++;
        }
    }

    shuffle(groups, n);
    shuffle(conceptsOnly, n);

    printf("\n## Mismatched Group and Concept ##\n");
    for (int i = 0; i < n; i++)
        printf("%d. %s: %s\n", i + 1, groups[i], conceptsOnly[i]);

    char *matchedGroup[n];
    char *matchedConcept[n];
    int matched = 0;

    clock_t start = clock();
    if (method == 1) {
        Queue groupQ = {NULL, NULL, 0}, conceptQ = {NULL, NULL, 0};
        for (int i = 0; i < n; i++) {
            enqueue(&groupQ, groups[i]);
            enqueue(&conceptQ, conceptsOnly[i]);
        }
        while (groupQ.size && conceptQ.size) {
            char *g = dequeue(&groupQ);
            char *c = dequeue(&conceptQ);
            printf("\nMatch: %s - %s\nIs this correct? (Y/N): ", g, c);
            char confirm;
            scanf(" %c", &confirm);
            if (confirm == 'Y' || confirm == 'y') {
                matchedGroup[matched] = g;
                matchedConcept[matched] = c;
                matched++;
            } else {
                free(g);
                free(c);
            }
        }
    } else {
        Stack groupS[MAX_QUEUE], conceptS[MAX_QUEUE];
        int topG = 0, topC = 0;
        for (int i = 0; i < n; i++) {
            push(groupS, &topG, groups[i]);
            push(conceptS, &topC, conceptsOnly[i]);
        }
        while (topG && topC) {
            char *g = pop(groupS, &topG);
            char *c = pop(conceptS, &topC);
            printf("\nMatch: %s - %s\nIs this correct? (Y/N): ", g, c);
            char confirm;
            scanf(" %c", &confirm);
            if (confirm == 'Y' || confirm == 'y') {
                matchedGroup[matched] = strdup(g);
                matchedConcept[matched] = strdup(c);
                matched++;
            }
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nTime spent matching: %.2f seconds\n", time_spent);
    printf("\nMatched Results:\n");
    for (int i = 0; i < matched; i++)
        printf("%s - %s\n", matchedGroup[i], matchedConcept[i]);

    if (concepts) free(concepts);
}

int main() {
    defineConcept();
    return 0;
}
