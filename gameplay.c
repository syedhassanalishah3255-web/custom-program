#include "raylib.h"
#include <math.h>

#define GRAVITY 0.8f
#define JUMP_FORCE -14.0f
#define MOVE_SPEED 6.0f
#define BULLET_SPEED 12.0f
#define MAX_BULLETS 20

typedef struct Bullet
{
    Rectangle rect;
    bool active;
    int direction;
} Bullet;

typedef enum
{
    STATE_IDLE,
    STATE_RUN,
    STATE_JUMP,
    STATE_CROUCH,
    STATE_SHOOT
} PlayerState;

int GetFrameCount(Texture2D tex)
{
    float ratio = (float)tex.width / tex.height;
    return (int)roundf(ratio);
}

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Sunset Rangers - Clean Background");
    SetTargetFPS(60);

    // === Load textures ===
    Texture2D bg = LoadTexture("assets/idea.png"); // full sprite sheet
    Texture2D idle = LoadTexture("Idle.png");
    Texture2D run = LoadTexture("Run.png");
    Texture2D jump = LoadTexture("Jump.png");
    Texture2D crouch = LoadTexture("Idle_2.png"); // can be crouch
    Texture2D shoot = LoadTexture("Shot.png");

    // === Auto-detect frames ===
    int idleFrames = GetFrameCount(idle);
    int runFrames = GetFrameCount(run);
    int jumpFrames = GetFrameCount(jump);
    int crouchFrames = GetFrameCount(crouch);
    int shootFrames = GetFrameCount(shoot);

    // === Animation control ===
    int currentFrame = 0;
    float frameTime = 0;
    const float frameSpeed = 0.12f;

    // === Player ===
    Vector2 pos = {200, 500};
    float velocityY = 0;
    bool grounded = true;
    bool facingRight = true;
    PlayerState state = STATE_IDLE;

    // === Shooting ===
    float shootTimer = 0;
    const float shootCooldown = 0.3f;
    Bullet bullets[MAX_BULLETS] = {0};

    // === Background scroll ===
    float bgScroll = 0;
    const float bgSpeed = 2.0f;

    while (!WindowShouldClose())
    {
        bool moving = false;

        // === Input ===
        if (IsKeyDown(KEY_RIGHT) && shootTimer <= 0)
        {
            pos.x += MOVE_SPEED;
            facingRight = true;
            moving = true;
            bgScroll -= bgSpeed;
        }
        if (IsKeyDown(KEY_LEFT) && shootTimer <= 0)
        {
            pos.x -= MOVE_SPEED;
            facingRight = false;
            moving = true;
            bgScroll += bgSpeed;
        }

        if (IsKeyPressed(KEY_SPACE) && grounded)
        {
            velocityY = JUMP_FORCE;
            grounded = false;
            state = STATE_JUMP;
        }

        if (IsKeyDown(KEY_DOWN))
        {
            state = STATE_CROUCH;
        }
        else if (IsKeyPressed(KEY_F) && shootTimer <= 0)
        {
            state = STATE_SHOOT;
            shootTimer = shootCooldown;

            for (int i = 0; i < MAX_BULLETS; i++)
            {
                if (!bullets[i].active)
                {
                    bullets[i].active = true;
                    bullets[i].direction = facingRight ? 1 : -1;
                    bullets[i].rect = (Rectangle){pos.x + (facingRight ? 60 : 0),
                                                  pos.y + 45, 15, 5};
                    break;
                }
            }
        }
        else if (!grounded)
            state = STATE_JUMP;
        else if (moving)
            state = STATE_RUN;
        else
            state = STATE_IDLE;

        // === Physics ===
        velocityY += GRAVITY;
        pos.y += velocityY;
        if (pos.y >= 500)
        {
            pos.y = 500;
            velocityY = 0;
            grounded = true;
        }

        // === Animation update ===
        frameTime += GetFrameTime();
        if (frameTime >= frameSpeed)
        {
            frameTime = 0;
            currentFrame++;

            int totalFrames = 1;
            switch (state)
            {
            case STATE_RUN:
                totalFrames = runFrames;
                break;
            case STATE_JUMP:
                totalFrames = jumpFrames;
                break;
            case STATE_CROUCH:
                totalFrames = crouchFrames;
                break;
            case STATE_SHOOT:
                totalFrames = shootFrames;
                break;
            case STATE_IDLE:
                totalFrames = idleFrames;
                break;
            default:
                totalFrames = idleFrames;
                break;
            }

            if (currentFrame >= totalFrames)
                currentFrame = 0;
        }

        if (shootTimer > 0)
            shootTimer -= GetFrameTime();

        // === Bullets ===
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (bullets[i].active)
            {
                bullets[i].rect.x += BULLET_SPEED * bullets[i].direction;
                if (bullets[i].rect.x < 0 || bullets[i].rect.x > screenWidth)
                    bullets[i].active = false;
            }
        }

        // === Background loop ===
        if (bgScroll <= -500 * 3.0f)
            bgScroll = 0;
        if (bgScroll >= 500 * 3.0f)
            bgScroll = 0;

        // === DRAW ===
        BeginDrawing();
        ClearBackground(BLACK);

        // ✅ Cropped clean desert background only
        Rectangle bgSource = {0, 0, 500, 180}; // crop top desert + sky
        float bgScale = 4.0f;
        float bgWidthScaled = bgSource.width * bgScale;

        DrawTexturePro(
            bg,
            bgSource,
            (Rectangle){bgScroll, 0, bgWidthScaled, bgSource.height * bgScale},
            (Vector2){0, 0},
            0.0f,
            WHITE);
        DrawTexturePro(
            bg,
            bgSource,
            (Rectangle){bgScroll + bgWidthScaled, 0, bgWidthScaled, bgSource.height * bgScale},
            (Vector2){0, 0},
            0.0f,
            WHITE);

        // === Player ===
        Texture2D tex = idle;
        int totalFrames = idleFrames;
        switch (state)
        {
        case STATE_RUN:
            tex = run;
            totalFrames = runFrames;
            break;
        case STATE_JUMP:
            tex = jump;
            totalFrames = jumpFrames;
            break;
        case STATE_CROUCH:
            tex = crouch;
            totalFrames = crouchFrames;
            break;
        case STATE_SHOOT:
            tex = shoot;
            totalFrames = shootFrames;
            break;
        default:
            tex = idle;
            totalFrames = idleFrames;
            break;
        }

        int frameWidth = tex.width / totalFrames;
        int frameHeight = tex.height;
        Rectangle src = {frameWidth * currentFrame, 0, frameWidth, frameHeight};
        if (!facingRight)
            src.width = -frameWidth;

        DrawTextureRec(tex, src, pos, WHITE);

        for (int i = 0; i < MAX_BULLETS; i++)
            if (bullets[i].active)
                DrawRectangleRec(bullets[i].rect, RED);

        DrawText("←/→ Move | SPACE Jump | ↓ Crouch | F Shoot", 20, 20, 20, RAYWHITE);

        EndDrawing();
    }

    // === Cleanup ===
    UnloadTexture(bg);
    UnloadTexture(idle);
    UnloadTexture(run);
    UnloadTexture(jump);
    UnloadTexture(crouch);
    UnloadTexture(shoot);
    CloseWindow();
    return 0;
}
