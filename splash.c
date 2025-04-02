#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep function

void display_splash_screen(const char *name, const char *date)
{
    // Clear the screen
    system("clear"); // Use "cls" on Windows

    // Display the splash screen with right-angled triangles
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    for (int i = 1; i <= 5; i++)
    {
        // Print left-side triangle
        for (int j = 0; j < i; j++)
        {
            printf("*");
        }
        // Print space for the main content
        printf("                                        [Magrathea ver 0.1]                                            ");
        // Print right-side inverted triangle
        for (int j = 0; j < (6 - i); j++)
        {
            printf("*");
        }
        printf("\n");
    }
    printf("***                   Magrathea, where a shining planet is created in a wasteland with no grass,          ***\n");
    printf("****           a place where unseen potential is discovered and gems are polished by the hands of experts, **  \n");
    printf("*****                                        Welcome to Magrathea.                                          *\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("[User]: %s                                   [Execution Time]: %s\n", name, date);
    printf("=============================================================================================================\n");
}

int main()
{
    char name[100];
    char date[11];

    // Get user input
    printf("[Please enter the current date in the \"yyyy-mm-dd\" format]: ");
    scanf("%10s", date);

    printf("[Please enter your name]: ");
    getchar(); // Consume the newline left by previous scanf
    scanf("%99[^\n]", name); // Read full name including spaces

    printf("**The input has been processed successfully.**\n");

    // Wait for 3 seconds
    sleep(3);

    // Display the splash screen
    display_splash_screen(name, date);

    return 0;
}
