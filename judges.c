#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define MAX_INPUT 512
#define FIELD_COUNT 7

char *judges_array[MAX_JUDGES];  // One-dimensional array to store judge JSON-style data

int count_fields(const char *str) {
    int count = 1;
    for (int i = 0; str[i]; i++) {
        if (str[i] == ',') {
            count++;
        }
    }
    return count;
}

void display_judge(const char *data, int index) {
    char buffer[MAX_INPUT];
    strcpy(buffer, data);
    char *fields[FIELD_COUNT];
    char *token = strtok(buffer, ",");
    int i = 0;

    while (token != NULL && i < FIELD_COUNT) {
        while (*token == ' ') token++; // Trim leading space
        fields[i++] = token;
        token = strtok(NULL, ",");
    }

    if (i == FIELD_COUNT) {
        printf("[Judge %d]\n", index + 1);
        printf("Name: %s\n", fields[0]);
        printf("Gender: %s\n", fields[1]);
        printf("Affiliation: %s\n", fields[2]);
        printf("Title: %s\n", fields[3]);
        printf("Expertise: %s\n", fields[4]);
        printf("Email: %s\n", fields[5]);
        printf("Phone: %s\n", fields[6]);
        printf("-----------------------------------\n");
    }
}

int main() {
    char project_name[100];
    int total_judges = 0;
    int selected_members = 0;
    int current = 0;

    printf("####################################\n");
    printf("#      Judge List Data Entry      #\n");
    printf("####################################\n");

    printf("Participating Project: ");
    fgets(project_name, sizeof(project_name), stdin);
    project_name[strcspn(project_name, "\n")] = '\0'; // remove newline

    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);

    printf("Number of Selected Members: ");
    scanf("%d", &selected_members);
    getchar(); // consume leftover newline

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Starting to input information for %d judges.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    while (current < total_judges) {
        char input[MAX_INPUT];
        printf("Judge %d: ", current + 1);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline

        if (count_fields(input) != FIELD_COUNT) {
            printf("The input items are incorrect. Please enter them again.\n");
            continue;
        }

        judges_array[current] = (char *)malloc(strlen(input) + 1);
        if (judges_array[current] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
        strcpy(judges_array[current], input);
        current++;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("\"Should we check the judge information?\" (Y/N): ");

    char choice;
    scanf(" %c", &choice);
    getchar(); // Clear newline

    if (choice == 'Y') {
        printf("####################################\n");
        printf("#        Display Judge Data        #\n");
        printf("####################################\n");

        for (int i = 0; i < total_judges; i++) {
            display_judge(judges_array[i], i);
        }
    } else {
        printf("Program terminated.\n");
    }

    // Free memory
    for (int i = 0; i < total_judges; i++) {
        free(judges_array[i]);
    }

    return 0;
}
