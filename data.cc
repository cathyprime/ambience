#include <raylib.h>
#include <fstream>
#include <sstream>
#include "data.hh"

const char* Sound_Record::c_str() const
{
    auto pattern = "Sound_Record{ .name = %s, .path = %s, .icon = %s }";
    char* str = (char*)malloc(strlen(pattern) - 6 + name.size() + path.size() + icon.size());
    sprintf(str, pattern, name.c_str(), path.c_str(), icon.c_str());
    return str;
}

/* |-------|
 * | NAME  | <- name
 * | ***** | <- icon
 * | ***** | <- icon
 * | ===== | <- sound bar
 * |-------|
 */

void Sound_Record::draw(int x, int y) const
{
    const int font_size = 30;
    int width = MeasureText(name.c_str(), font_size);
    DrawRectangle(x, y, 140, 140, GREEN);
    DrawText(name.c_str(), x + (140 - width)/2, y + 140/2, font_size, RED);
}

float Sound_Record::width() const
{
    return 140.f;
}

std::vector<std::string> split(char delim, std::string& s)
{
    std::vector<std::string> res;
    std::string fragment;
    res.reserve(3);

    for (size_t i = 0; i < 2; ++i) {
        fragment = s.substr(0, s.find(delim));
        res.push_back(fragment);
        s.erase(0, s.find(delim) + 1);
    }

    res.push_back(s);

    return res;
}

bool string_to_sound_record(Sound_Record* result, std::string& line)
{
    // path, icon, name
    std::vector<std::string> splits = split(',', line);
    if (splits.size() != 3) {
        return false;
    }

    *result = (Sound_Record) {
        .name = splits[2],
        .path = splits[0],
        .icon = splits[1],
    };

    return true;
}

std::vector<Sound_Record> read_from_file(std::string_view path)
{
    std::vector<Sound_Record> results;
    std::ifstream file(path.data());
    for (std::string line; std::getline(file, line);) {
        Sound_Record sr;
        if (string_to_sound_record(&sr, line))
            results.push_back(sr);
    }
    return results;
}

void save_to_file(std::string_view path, std::vector<Sound_Record>& items)
{
    std::ofstream file(path.data());
    std::stringstream ss;
    for (auto item : items) {
        ss.clear();
        ss << item.path << "," << item.icon << "," << item.name << "\n";
        file << ss.str();
    }
}
