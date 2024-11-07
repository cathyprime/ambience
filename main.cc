#include <raylib.h>
#include <assert.h>
#include "data.hh"
#include "ui.hh"

const int WIDTH = 480;
const int HEIGHT = 640;
const int BUTTON_WIDTH = 160;

#define BUTTON Button<BUTTON_WIDTH>

// TODO: make this shit responsive
void draw_record_row(std::vector<Sound_Record>* rec, float row_num = 0.f)
{
    assert(rec->size() > 0);
    float border_size = (WIDTH - (*rec)[0].width() * 3) / 4;
    float default_cell_padding = BUTTON_WIDTH - (*rec)[0].width();
    float offset = default_cell_padding - border_size;

    BUTTON button1{offset,  {BUTTON_WIDTH*0, row_num * 160}, &(*rec)[0 + 3 * row_num]};
    BUTTON button2{0,       {BUTTON_WIDTH*1, row_num * 160}, &(*rec)[1 + 3 * row_num]};
    BUTTON button3{-offset, {BUTTON_WIDTH*2, row_num * 160}, &(*rec)[2 + 3 * row_num]};
    button1.draw();
    button2.draw();
    button3.draw();
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
        draw_record_row(&result, 0);
        draw_record_row(&result, 1);
        draw_record_row(&result, 2);
        draw_record_row(&result, 3);
        EndDrawing();
    }
    CloseWindow();
}
