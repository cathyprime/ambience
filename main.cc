#include "./data.hh"
#include <raylib.h>

int main()
{
    // std::vector<Sound_Record> result = read_from_file("./test.csv");
    //
    // for (auto entry : result) {
    //     printf("Sound_Record{ .name = %s, .path = %s, .icon = %s }\n",
    //             entry.name.c_str(), entry.path.c_str(), entry.icon.c_str());
    // }
    //
    // save_to_file("./test2.csv", result);

    InitWindow(600, 800, "Ambience");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKPURPLE);
        EndDrawing();
    }
    CloseWindow();
}
