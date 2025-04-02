#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // To get the current date

#define NUM_CANDIDATES 6

// Structure to hold candidate information
typedef struct {
    char name[50];
    char dob[11];    // Date of birth in "YYYY/MM/DD" format
    char gender;     // 'F' or 'M'
    char email[50];
    char nationality[50];
    float bmi;
    char primary_skill[50];
    char secondary_skill[50];
    int korean_proficiency;
    char mbti[5];
    char introduction[200];
} Candidate;

void get_current_year_and_month(int *current_year, int *current_month, int *current_day) {
    // Get current date from system
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    *current_year = tm.tm_year + 1900; // tm_year is years since 1900
    *current_month = tm.tm_mon + 1;    // tm_mon is months since January (0-11)
    *current_day = tm.tm_mday;
}

int calculate_age(const char *dob, int current_year, int current_month, int current_day) {
    int birth_year, birth_month, birth_day;
    sscanf(dob, "%4d/%2d/%2d", &birth_year, &birth_month, &birth_day);

    int age = current_year - birth_year;
    if (current_month < birth_month || (current_month == birth_month && current_day < birth_day)) {
        age--; // Adjust if the birthday hasn't occurred yet this year
    }
    return age;
}

int main() {
    Candidate candidates[NUM_CANDIDATES];
    char group_name[50];
    
    // Input audition group name
    printf("Enter the audition group name: ");
    fgets(group_name, sizeof(group_name), stdin);
    group_name[strcspn(group_name, "\n")] = '\0';  // Remove trailing newline
    
    // Get current date
    int current_year, current_month, current_day;
    get_current_year_and_month(&current_year, &current_month, &current_day);

    // Data input for 6 candidates
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        printf("\n####################################\n");
        printf("[%s] Audition Candidate Data Entry\n", group_name);
        printf("####################################\n");
        printf("Entering information for candidate %d.\n", i + 1);
        printf("---------------------------------\n");

        // Name
        printf("1. Name: ");
        fgets(candidates[i].name, sizeof(candidates[i].name), stdin);
        candidates[i].name[strcspn(candidates[i].name, "\n")] = '\0';  // Remove newline

        // Date of Birth
        printf("2. Date of Birth (YYYY/MM/DD format): ");
        fgets(candidates[i].dob, sizeof(candidates[i].dob), stdin);
        candidates[i].dob[strcspn(candidates[i].dob, "\n")] = '\0';

        // Gender
        printf("3. Gender (F for Female, M for Male): ");
        scanf(" %c", &candidates[i].gender); // Added space before %c to avoid newline issues
        getchar(); // Consume the trailing newline

        // Email
        printf("4. Email: ");
        fgets(candidates[i].email, sizeof(candidates[i].email), stdin);
        candidates[i].email[strcspn(candidates[i].email, "\n")] = '\0';  // Remove newline

        // Nationality
        printf("5. Nationality: ");
        fgets(candidates[i].nationality, sizeof(candidates[i].nationality), stdin);
        candidates[i].nationality[strcspn(candidates[i].nationality, "\n")] = '\0';  // Remove newline

        // BMI
        printf("6. BMI: ");
        scanf("%f", &candidates[i].bmi);
        getchar(); // Consume the trailing newline

        // Primary Skill
        printf("7. Primary Skill: ");
        fgets(candidates[i].primary_skill, sizeof(candidates[i].primary_skill), stdin);
        candidates[i].primary_skill[strcspn(candidates[i].primary_skill, "\n")] = '\0';  // Remove newline

        // Secondary Skill
        printf("8. Secondary Skill: ");
        fgets(candidates[i].secondary_skill, sizeof(candidates[i].secondary_skill), stdin);
        candidates[i].secondary_skill[strcspn(candidates[i].secondary_skill, "\n")] = '\0';  // Remove newline

        // Korean Proficiency Level
        printf("9. Korean Proficiency Level (TOPIK): ");
        scanf("%d", &candidates[i].korean_proficiency);
        getchar(); // Consume the trailing newline

        // MBTI
        printf("10. MBTI: ");
        fgets(candidates[i].mbti, sizeof(candidates[i].mbti), stdin);
        candidates[i].mbti[strcspn(candidates[i].mbti, "\n")] = '\0';  // Remove newline

        // Introduction
        printf("11. Introduction: ");
        fgets(candidates[i].introduction, sizeof(candidates[i].introduction), stdin);
        candidates[i].introduction[strcspn(candidates[i].introduction, "\n")] = '\0';  // Remove newline

        printf("=================================\n");
    }

    // Display candidate data
    printf("\n####################################\n");
    printf("[%s] Audition Candidate Data Review\n", group_name);
    printf("####################################\n");
    printf("=============================================================================================\n");
    printf("Name          | DOB       | Gender | Email                 | Nationality | BMI  | Primary Skill | Secondary Skill | TOPIK | MBTI | \n");
    printf("=============================================================================================\n");

    for (int i = 0; i < NUM_CANDIDATES; i++) {
        // Calculate age
        int age = calculate_age(candidates[i].dob, current_year, current_month, current_day);

        // Display candidate information
        printf("%-14s | %-10s | %-6c | %-20s | %-12s | %-4.1f | %-13s | %-15s | %-5d | %-4s |\n",
            candidates[i].name, candidates[i].dob, candidates[i].gender, candidates[i].email,
            candidates[i].nationality, candidates[i].bmi, candidates[i].primary_skill,
            candidates[i].secondary_skill, candidates[i].korean_proficiency, candidates[i].mbti);
        printf("-------------------------------------------------------------------------------------\n");
        printf("%s\n", candidates[i].introduction);
        printf("---------------------------------------------------------------------------------------------\n");
    }

    return 0;
}
