/**
 * @file fshelf.h
 * @brief File Shelf (File Manager)
 */

#pragma once
#include <vector>

namespace PBRV {
    template <typename T>
    class FileShelf {
    public:
        FileShelf(const FileShelf&) = delete;
        FileShelf& operator=(const FileShelf&) = delete;

        // that max_file_num is set to -1 means auto-cg is disabled
        FileShelf(int max_file_num = -1): max_file(max_file_num) {}

        ~FileShelf() {
            clear();
        }

        // TODO useless std::move
        inline T& add(T&& file) {
            if (max_file > 0 && m_files.size() == max_file) {
                clear();
            }

            m_files.push_back(std::move(file));
            return m_files[m_files.size() - 1];
        }

        inline void clear() {
            for (T& f : m_files) {
                f.close();
            }
            m_files.clear();
        }

    private:
        std::vector<T> m_files{};
        int max_file = -1;
    };
}