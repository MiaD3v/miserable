#pragma once
#include <optional>
#include <utility>
#include <print>

constexpr int ACHIEVEMENT_COUNT = 3;

namespace Miserable {
    class SaveFile {
        uint64_t longest_run_milis;
        bool achievements[ACHIEVEMENT_COUNT];
        unsigned int name_len;
        char *name;

        public:
        SaveFile() = delete;
        SaveFile(const SaveFile& other);
        
        explicit SaveFile(uint64_t, bool*, char*, unsigned int);
        static std::optional<SaveFile> open(char*);
        int save(char*);

        std::pair<char*, unsigned int> getName();
        bool* getAchievments();
        uint64_t getLongestRun();

        ~SaveFile();
    };
}
