#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

typedef enum {
    SCREEN_MENU,
    SCREEN_GAMEPLAY,
    SCREEN_EXIT
} GameScreen;

// Safe function to execute a program and wait for it
int execute_program(const char *program_path) {
    pid_t pid = fork();
    
    if (pid < 0) {
        fprintf(stderr, "Error: Failed to fork process\n");
        return -1;
    }
    
    if (pid == 0) {
        // Child process
        char *args[] = {(char *)program_path, NULL};
        execv(program_path, args);
        // If execv returns, there was an error
        fprintf(stderr, "Error: Failed to execute %s\n", program_path);
        exit(1);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }
}

// Safe function to get user input
int get_yes_no_input(void) {
    char buffer[16];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0; // Default to no on error
    }
    
    // Trim newline
    buffer[strcspn(buffer, "\n")] = 0;
    
    if (strlen(buffer) == 0) {
        return 0;
    }
    
    // Check first character
    char first = buffer[0];
    return (first == 'y' || first == 'Y');
}

int main(void)
{
    GameScreen currentScreen = SCREEN_MENU;
    
    printf("===========================================\n");
    printf("  Sunset Rangers - Western Action Game\n");
    printf("===========================================\n\n");
    
    // Check if required programs exist
    if (access("./menu", X_OK) != 0) {
        fprintf(stderr, "Error: './menu' not found or not executable.\n");
        fprintf(stderr, "Please run 'make all' to build the game first.\n");
        return 1;
    }
    
    if (access("./gameplay", X_OK) != 0) {
        fprintf(stderr, "Error: './gameplay' not found or not executable.\n");
        fprintf(stderr, "Please run 'make all' to build the game first.\n");
        return 1;
    }
    
    printf("Starting game...\n");
    
    while (currentScreen != SCREEN_EXIT)
    {
        switch (currentScreen)
        {
            case SCREEN_MENU:
            {
                printf("Loading menu...\n");
                int result = execute_program("./menu");
                
                if (result != 0) {
                    fprintf(stderr, "Menu exited with code %d\n", result);
                }
                
                // For this simple version, after menu closes, ask user
                printf("\nDo you want to play the game? (y/n): ");
                if (get_yes_no_input()) {
                    currentScreen = SCREEN_GAMEPLAY;
                } else {
                    currentScreen = SCREEN_EXIT;
                }
                break;
            }
            case SCREEN_GAMEPLAY:
            {
                printf("Loading gameplay...\n");
                int result = execute_program("./gameplay");
                
                if (result != 0) {
                    fprintf(stderr, "Gameplay exited with code %d\n", result);
                }
                
                // After gameplay, return to menu
                currentScreen = SCREEN_MENU;
                break;
            }
            default:
                currentScreen = SCREEN_EXIT;
                break;
        }
    }
    
    printf("\nThank you for playing Sunset Rangers!\n");
    return 0;
}
