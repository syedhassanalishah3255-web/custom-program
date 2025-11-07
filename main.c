#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

// Forward declarations for external game functions
extern int RunMenu(void);
extern int RunGameplay(void);

typedef enum {
    SCREEN_MENU,
    SCREEN_GAMEPLAY,
    SCREEN_EXIT
} GameScreen;

int main(void)
{
    // Simple main launcher that can switch between menu and gameplay
    GameScreen currentScreen = SCREEN_MENU;
    
    printf("===========================================\n");
    printf("  Sunset Rangers - Western Action Game\n");
    printf("===========================================\n\n");
    printf("Starting game...\n");
    
    while (currentScreen != SCREEN_EXIT)
    {
        switch (currentScreen)
        {
            case SCREEN_MENU:
            {
                printf("Loading menu...\n");
                // For now, we'll just run the menu standalone
                // In the future, menu.c should be refactored to return a result
                system("./menu");
                // For this simple version, after menu closes, go to gameplay
                printf("\nDo you want to play the game? (y/n): ");
                char choice;
                scanf(" %c", &choice);
                if (choice == 'y' || choice == 'Y')
                    currentScreen = SCREEN_GAMEPLAY;
                else
                    currentScreen = SCREEN_EXIT;
                break;
            }
            case SCREEN_GAMEPLAY:
            {
                printf("Loading gameplay...\n");
                system("./gameplay");
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
