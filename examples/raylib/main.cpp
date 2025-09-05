#include <autorelease/AutoRelease.hpp>
#include <raylib.h>

inline bool operator!=(const Texture &lhs, const Texture &rhs)
{
    return lhs.id != rhs.id;
}

int main()
{
    InitWindow(800, 450, "raylib - basic window");
    AutoRelease<int> window(1, [](const int &) { CloseWindow(); });

    SetTargetFPS(60);
    const AutoRelease<Texture2D> texture = {LoadTexture("resources/red_square.png"), UnloadTexture};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        AutoRelease<int> drawing(2, [](const int &) { EndDrawing(); });
        ClearBackground(RAYWHITE);

        DrawTexture(texture, 10, 10, WHITE);
    }

    return 0;
}
