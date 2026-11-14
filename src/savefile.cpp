#include <cstdint>
#include <fstream>
#include <optional>

#include "savefile.hpp"
Miserable::SaveFile::SaveFile(uint64_t longest_run_milis_i, bool *achievements_i, char *name_i, unsigned int name_len_i) {

    longest_run_milis = longest_run_milis_i;
    for (size_t i = 0; i < ACHIEVEMENT_COUNT; i++)
        achievements[i] = achievements_i[i];
    name_len = name_len_i;
    name = (char*) malloc(name_len * sizeof(char));
    for(size_t i = 0; i < name_len; i++)
        name[i] = name_i[i];
}
Miserable::SaveFile::SaveFile(const SaveFile& other) {
    longest_run_milis = other.longest_run_milis;
    for (size_t i = 0; i < ACHIEVEMENT_COUNT; i++)
        achievements[i] = other.achievements[i];
    name_len = other.name_len;
    name = (char*) malloc(name_len * sizeof(char));
    for(size_t i = 0; i < name_len; i++)
        name[i] = other.name[i];
}
std::optional<Miserable::SaveFile> Miserable::SaveFile::open(char* filename) {
    std::fstream fs (filename, std::fstream::in);
    if (!fs.is_open())
        return std::nullopt;

    uint64_t longest_run_milis;
    bool achievements[ACHIEVEMENT_COUNT];
    unsigned int name_len;
    char *name;

    fs.read((char*)&longest_run_milis, sizeof(longest_run_milis));
    fs.read((char*)&achievements, sizeof(achievements));
    fs.read((char*)&name_len, sizeof(name_len));

    name = (char*) malloc(name_len * sizeof(*name));
    fs.read(name, name_len * sizeof(*name));

    fs.close();
    Miserable::SaveFile f = Miserable::SaveFile(longest_run_milis, achievements, name, name_len);
    free(name);
    return f;
}
int Miserable::SaveFile::save(char *filename) {
    std::fstream fs (filename, std::fstream::out);
    if (!fs.is_open())
    return -1;

    fs.write((char*)&longest_run_milis, sizeof(longest_run_milis));
    fs.write((char*)&achievements, sizeof(achievements));
    fs.write((char*)&name_len, sizeof(name_len));
    fs.write(name, name_len * sizeof(*name));

    fs.close();
    return 0;
}


std::pair<char*, unsigned int> Miserable::SaveFile::getName() {
    return std::pair(name, name_len);
}
bool* Miserable::SaveFile::getAchievments() {
    return achievements;
}
uint64_t Miserable::SaveFile::getLongestRun() {
    return longest_run_milis;
}
Miserable::SaveFile::~SaveFile()  {
    free(name);
}