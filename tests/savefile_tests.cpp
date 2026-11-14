#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <cstdlib>
#include <cstring>

#include "savefile.hpp"

#define NUM_TESTS 100

int run_random_test() {
    unsigned int len = ((unsigned int)rand()) % 100 + 1;
    char* name = (char*)malloc(len);
    for (size_t i = 0; i < len; i++) {
        name[i] = (char)(rand() % 26) + 'a';
    }
    uint64_t longest_run_milis = (uint64_t) rand();
    bool achievements[] = {(bool)(rand() & 1), (bool)(rand() & 1), (bool)(rand() & 1)};
    Miserable::SaveFile file(longest_run_milis, achievements, name, len);
    file.save("test.misery");
    std::optional<Miserable::SaveFile> new_file = Miserable::SaveFile::open("test.misery");
    if (!new_file.has_value())
        return -1;

    if (file.getLongestRun() != new_file->getLongestRun())
        return -2;
    if (memcmp(file.getAchievments(), new_file->getAchievments(), ACHIEVEMENT_COUNT * sizeof(*new_file->getAchievments())) != 0)
        return -3;
    std::pair<char*, unsigned int> str_1 = file.getName();
    std::pair<char*, unsigned int> str_2 = new_file->getName();
    if (str_1.second != str_2.second)
        return -4;
    if (memcmp(str_1.first, str_2.first, str_2.second))
        return -5;

    return 0;
}
int main() {
    std::time_t seed = std::time(0);
    std::srand(seed);
    std::print("{0}\n", (int)seed);
    for(int i = 0; i < NUM_TESTS; i++){
        int res = run_random_test();
        if (res != 0) {
            std::print("test failed");
        }
    }
}