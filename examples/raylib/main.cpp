#include <autorelease/AutoRelease.hpp>
#include <raylib.h>

inline bool operator!=(const Texture &lhs, const Texture &rhs)
{
    return lhs.id != rhs.id;
}

int main()
{
    AutoReleaseVoid<int, int, const char *> window(InitWindow, CloseWindow, 800, 450, "raylib");

    SetTargetFPS(60);
    const AutoRelease<Texture2D> texture = {LoadTexture("resources/red_square.png"), UnloadTexture};

    while (!WindowShouldClose())
    {
        AutoReleaseVoid<> drawing(BeginDrawing, EndDrawing);
        ClearBackground(RAYWHITE);

        DrawTexture(texture, 10, 10, WHITE);
    }

    return 0;
}
