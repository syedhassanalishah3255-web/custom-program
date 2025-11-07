#include "raylib.h"
#include <stdio.h>

#define MAX_FRAMES 130 // safety buffer (you have 118 frames)

typedef enum
{
    MENU_PLAY,
    MENU_OPTIONS,
    MENU_HOWTO,
    MENU_QUIT
} MenuOption;

int main(void)
{
    InitWindow(1920, 1080, "Sunset Rangers - Cinematic Menu");
    InitAudioDevice();
    SetTargetFPS(30);

    // --- Load video frames ---
    Texture2D frames[MAX_FRAMES] = {0};
    int frameCount = 0;
    char path[128];

    for (int i = 1; i <= 118; i++) // ezgif-frame-001 → ezgif-frame-118
    {
        snprintf(path, sizeof(path), "frames/ezgif-frame-%03d.png", i);
        if (FileExists(path))
        {
            Image img = LoadImage(path);
            frames[frameCount++] = LoadTextureFromImage(img);
            UnloadImage(img);
        }
        else
            break;
    }

    if (frameCount == 0)
    {
        printf("❌ No frames found in 'frames/'!\n");
        CloseWindow();
        return 1;
    }

    // --- Load assets ---
    Image logoImg = LoadImage("images/logo.png");
    Texture2D logo = LoadTextureFromImage(logoImg);
    UnloadImage(logoImg);

    Image gunImg = LoadImage("images/revolver.png");
    Texture2D revolver = LoadTextureFromImage(gunImg);
    UnloadImage(gunImg);

    Font font = LoadFontEx("fonts/western.ttf", 64, 0, 0);
    if (font.texture.id == 0)
        font = GetFontDefault();

    Texture2D githubIcon = LoadTexture("images/github.png");
    Texture2D youtubeIcon = LoadTexture("images/youtube.png");

    // --- Variables ---
    MenuOption selected = MENU_PLAY;
    float alpha = 1.0f;

    // Icon animation
    float gitScale = 0.10f, ytScale = 0.10f;
    const float baseScale = 0.10f, hoverScale = 0.13f, speed = 0.08f;

    // Frame playback
    int currentFrame = 0;
    int frameDirection = 1; // 1 = forward, -1 = backward
    float frameTimer = 0.0f;
    float frameDelay = 1.0f / 24.0f; // ~24 FPS playback

    // --- Main loop ---
    while (!WindowShouldClose())
    {
        // --- Update background animation (ping-pong loop) ---
        frameTimer += GetFrameTime();
        if (frameTimer >= frameDelay)
        {
            frameTimer = 0.0f;
            currentFrame += frameDirection;

            if (currentFrame >= frameCount - 1)
            {
                currentFrame = frameCount - 1;
                frameDirection = -1;
            }
            else if (currentFrame <= 0)
            {
                currentFrame = 0;
                frameDirection = 1;
            }
        }

        Vector2 mouse = GetMousePosition();
        bool mouseClicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // Keyboard navigation
        if (IsKeyPressed(KEY_DOWN))
            selected = (selected + 1) % 4;
        if (IsKeyPressed(KEY_UP))
            selected = (selected + 3) % 4;

        BeginDrawing();
        ClearBackground(BLACK);

        // --- Draw background video frame ---
        DrawTexturePro(frames[currentFrame],
                       (Rectangle){0, 0, (float)frames[currentFrame].width, (float)frames[currentFrame].height},
                       (Rectangle){0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
                       (Vector2){0, 0}, 0, WHITE);

        // Subtle dark overlay for readability
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.45f));

        // --- Logo ---
        int logoX = (GetScreenWidth() - logo.width) / 2;
        DrawTextureEx(logo, (Vector2){logoX, 100}, 0.0f, 1.0f, Fade(WHITE, alpha));

        // --- Menu items ---
        const char *menuItems[4] = {"PLAY", "OPTIONS", "HOW TO PLAY", "QUIT"};
        int baseY = 575, spacing = 80;
        float fontSize = 60.0f;

        for (int i = 0; i < 4; i++)
        {
            Vector2 size = MeasureTextEx(font, menuItems[i], fontSize, 2);
            int textX = (GetScreenWidth() - size.x) / 2 - 20;
            int textY = baseY + i * spacing;

            Rectangle rect = {textX - 40, textY - 10, size.x + 80, size.y + 20};
            bool hover = CheckCollisionPointRec(mouse, rect);
            if (hover)
                selected = (MenuOption)i;

            Color color = (i == selected) ? GOLD : LIGHTGRAY;
            DrawTextEx(font, menuItems[i], (Vector2){textX, textY}, fontSize, 2, color);

            // Revolver beside selected
            if (i == selected)
            {
                float gunTargetH = fontSize * 0.9f;
                float gunScale = gunTargetH / revolver.height;
                float gunW = revolver.width * gunScale;
                float gunH = revolver.height * gunScale;
                float gunX = textX - gunW - 28;
                float gunY = textY + (fontSize - gunH) / 2.0f;
                DrawTextureEx(revolver, (Vector2){gunX, gunY}, 0.0f, gunScale, WHITE);
            }

            if (hover && mouseClicked)
            {
                if (i == MENU_PLAY)
                    printf("PLAY selected!\n");
                else if (i == MENU_OPTIONS)
                    printf("OPTIONS selected!\n");
                else if (i == MENU_HOWTO)
                    printf("HOW TO PLAY selected!\n");
                else if (i == MENU_QUIT)
                    goto EXIT_MENU;
            }
        }

        // --- Social icons ---
        int padding = 20;
        Vector2 gitPos = {GetScreenWidth() - githubIcon.width * baseScale * 2 - padding * 2,
                          GetScreenHeight() - githubIcon.height * baseScale - padding};
        Vector2 ytPos = {GetScreenWidth() - youtubeIcon.width * baseScale - padding,
                         GetScreenHeight() - youtubeIcon.height * baseScale - padding};

        Rectangle gitRect = {gitPos.x, gitPos.y, githubIcon.width * gitScale, githubIcon.height * gitScale};
        Rectangle ytRect = {ytPos.x, ytPos.y, youtubeIcon.width * ytScale, youtubeIcon.height * ytScale};

        bool hoverGit = CheckCollisionPointRec(mouse, gitRect);
        bool hoverYT = CheckCollisionPointRec(mouse, ytRect);

        gitScale += (hoverGit ? hoverScale - gitScale : baseScale - gitScale) * speed;
        ytScale += (hoverYT ? hoverScale - ytScale : baseScale - ytScale) * speed;

        Vector2 gitDrawPos = {gitPos.x - (githubIcon.width * (gitScale - baseScale)) / 2,
                              gitPos.y - (githubIcon.height * (gitScale - baseScale)) / 2};
        Vector2 ytDrawPos = {ytPos.x - (youtubeIcon.width * (ytScale - baseScale)) / 2,
                             ytPos.y - (youtubeIcon.height * (ytScale - baseScale)) / 2};

        DrawTextureEx(githubIcon, gitDrawPos, 0, gitScale, WHITE);
        DrawTextureEx(youtubeIcon, ytDrawPos, 0, ytScale, WHITE);

        EndDrawing();

        // --- Click detection for icons ---
        if (mouseClicked)
        {
            if (hoverGit)
                OpenURL("https://github.com/YourProfileHere");
            if (hoverYT)
                OpenURL("https://youtube.com/@YourChannelHere");
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            if (selected == MENU_QUIT)
                break;
            else
                printf("Selected: %d\n", selected);
        }
    }

EXIT_MENU:
    // --- Cleanup ---
    for (int i = 0; i < frameCount; i++)
        UnloadTexture(frames[i]);
    UnloadTexture(logo);
    UnloadTexture(revolver);
    UnloadTexture(githubIcon);
    UnloadTexture(youtubeIcon);
    UnloadFont(font);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
