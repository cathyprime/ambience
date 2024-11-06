#include <string> // meow :c
#include <string_view> // meow :c
#include <vector>

// TODO: icon type????? union maybe?
// TODO: make code better
struct Sound_Record {
    std::string name;
    std::string path; // actually make a path type
    std::string icon; // string or path; where string would be a builtin icon
};

std::vector<Sound_Record> read_from_file(std::string_view path); // TODO: use actual path
void save_to_file(std::string_view path, std::vector<Sound_Record>& items); // TODO: use actual path
