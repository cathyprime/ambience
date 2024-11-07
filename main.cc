#include <raylib.h>
#include <assert.h>
#include "data.hh"

const int WIDTH = 480;
const int HEIGHT = 640;
const int BUTTON_WIDTH = 160;

int row_len()
{
    int x = GetScreenWidth() / BUTTON_WIDTH;
    return x == 0 ? 1 : x;
}

void draw_record_row(std::vector<Sound_Record>* rec)
{
    assert(rec->size() > 0);
    int len = row_len();
    int button_side = (*rec)[0].width();

    float total_padding = GetScreenWidth() - button_side * len;
    float spacing = total_padding / (len + 1);

    for (size_t i = 0; i < rec->size(); ++i) {
        int col = i % len;

        float x = spacing + col * (button_side + spacing);
        float y = i / row_len() * 160;

        (*rec)[i].draw(x, y);
    }
}

int main()
{
    std::vector<Sound_Record> result = read_from_file("./test.csv");

    for (auto entry : result) {
        printf("%s\n", entry.c_str());
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIDTH, HEIGHT, "Ambience");
    SetTargetFPS(144);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKPURPLE);
        draw_record_row(&result);
        EndDrawing();
    }
    CloseWindow();
}
