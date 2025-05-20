#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TITLE 100
#define MAX_DATE 11
#define MAX_FIELD 100
#define MAX_QUALIFICATIONS 5
#define MAX_SOCIALS 5

typedef struct {
    int id;
    char title[MAX_TITLE];
    char postingDate[MAX_DATE];
    char deadline[MAX_DATE];
    int numHires;
    char jobField[MAX_FIELD];
    char *qualifications[MAX_QUALIFICATIONS];
    int numQualifications;
} JobPosting;

typedef struct {
    char name[20];
    char apiKey[50];
    char apiUrl[100];
} SocialNetwork;

JobPosting **jobList = NULL;
int jobCount = 0;
int nextId = 1;

SocialNetwork socials[MAX_SOCIALS] = {
    {"Facebook", "FB_KEY", "https://api.facebook.com/post"},
    {"Instagram", "IG_KEY", "https://api.instagram.com/post"},
    {"Thread", "TH_KEY", "https://api.thread.com/post"},
    {"LinkedIn", "LI_KEY", "https://api.linkedin.com/post"},
    {"X", "X_KEY", "https://api.x.com/post"}
};

int compareDates(const char *d1, const char *d2) {
    struct tm tm1 = {0}, tm2 = {0};
    sscanf(d1, "%d-%d-%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday);
    sscanf(d2, "%d-%d-%d", &tm2.tm_year, &tm2.tm_mon, &tm2.tm_mday);
    tm1.tm_year -= 1900; tm1.tm_mon -= 1;
    tm2.tm_year -= 1900; tm2.tm_mon -= 1;
    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);
    if (time1 < time2) return -1;
    if (time1 > time2) return 1;
    return 0;
}

char *getCurrentDate() {
    static char dateStr[MAX_DATE];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    snprintf(dateStr, MAX_DATE, "%04d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
    return dateStr;
}

void createJobPosting() {
    JobPosting *job = malloc(sizeof(JobPosting));
    job->id = nextId++;
    printf("Enter job title: "); fgets(job->title, MAX_TITLE, stdin); job->title[strcspn(job->title, "\n")] = 0;
    printf("Enter posting date (YYYY-MM-DD): "); fgets(job->postingDate, MAX_DATE, stdin); job->postingDate[strcspn(job->postingDate, "\n")] = 0;
    printf("Enter deadline (YYYY-MM-DD): "); fgets(job->deadline, MAX_DATE, stdin); job->deadline[strcspn(job->deadline, "\n")] = 0;
    printf("Enter number of hires: "); scanf("%d", &job->numHires); getchar();
    printf("Enter job field: "); fgets(job->jobField, MAX_FIELD, stdin); job->jobField[strcspn(job->jobField, "\n")] = 0;

    job->numQualifications = 0;
    while (job->numQualifications < MAX_QUALIFICATIONS) {
        printf("Enter qualification %d (or blank to finish): ", job->numQualifications + 1);
        char buffer[100];
        fgets(buffer, 100, stdin);
        if (buffer[0] == '\n') break;
        buffer[strcspn(buffer, "\n")] = 0;
        job->qualifications[job->numQualifications] = strdup(buffer);
        job->numQualifications++;
    }

    jobList = realloc(jobList, sizeof(JobPosting*) * (jobCount + 1));
    jobList[jobCount++] = job;
    printf("Job posting created with ID %d\n", job->id);
}

void viewJobPostings() {
    int active = 0;
    char *today = getCurrentDate();
    for (int i = 0; i < jobCount; i++) {
        if (compareDates(today, jobList[i]->deadline) <= 0) {
            printf("ID: %d, Title: %s, Deadline: %s\n", jobList[i]->id, jobList[i]->title, jobList[i]->deadline);
            active++;
        }
    }
    if (active == 0) {
        printf("No active postings.\nCreating new job posting...\n");
        createJobPosting();
        return;
    }
    printf("Enter job ID to view details: ");
    int id; scanf("%d", &id); getchar();
    for (int i = 0; i < jobCount; i++) {
        if (jobList[i]->id == id) {
            printf("Title: %s\nDate: %s - %s\nHires: %d\nField: %s\n", jobList[i]->title, jobList[i]->postingDate, jobList[i]->deadline, jobList[i]->numHires, jobList[i]->jobField);
            for (int q = 0; q < jobList[i]->numQualifications; q++) {
                printf("Qualification %d: %s\n", q + 1, jobList[i]->qualifications[q]);
            }
        }
    }
}

void postToSocialNetwork() {
    printf("Select Social Network:\n");
    for (int i = 0; i < MAX_SOCIALS; i++) {
        printf("%d. %s\n", i + 1, socials[i].name);
    }
    int choice;
    scanf("%d", &choice); getchar();
    if (choice < 1 || choice > MAX_SOCIALS) return;

    printf("Enter job ID to post: ");
    int id; scanf("%d", &id); getchar();
    for (int i = 0; i < jobCount; i++) {
        if (jobList[i]->id == id) {
            printf("Posting job ID %d to %s\n", id, socials[choice - 1].name);
            printf("API KEY: %s\nURL: %s\n", socials[choice - 1].apiKey, socials[choice - 1].apiUrl);
            printf("[Stub] Post successful.\n");
            return;
        }
    }
    printf("Job ID not found.\n");
}

void findSpecialist() {
    while (1) {
        printf("\n[Finding People Menu]\n1. Create Job Posting\n2. View Job Postings\n3. Post on Social Networks\n4. Exit\nChoose: ");
        char choice;
        scanf(" %c", &choice); getchar();
        switch (choice) {
            case '1': createJobPosting(); break;
            case '2': viewJobPostings(); break;
            case '3': postToSocialNetwork(); break;
            case '4': return;
            default: printf("Invalid input.\n"); break;
        }
    }
}

int main() {
    findSpecialist();
    for (int i = 0; i < jobCount; i++) {
        for (int q = 0; q < jobList[i]->numQualifications; q++) {
            free(jobList[i]->qualifications[q]);
        }
        free(jobList[i]);
    }
    free(jobList);
    return 0;
}
