#include <fstream>
#include <sstream>
#include "data.hh"

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
