#include "FileAVL.hpp"
#include "FileTrie.hpp"

// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp

/**
 * @brief Retrieves all files in the FileAVL whose file sizes are within [min, max]
 *
 * @param min The min value of the file size query range.
 * @param max The max value of the file size query range.
 * @return std::vector<File*> storing pointers to all files in the tree within the given range.
 * @note If the query interval is in descending order (ie. the given parameters min >= max),
        the interval from [max, min] is searched (since max >= min)
 */
std::vector<File *> FileAVL::query(size_t min, size_t max)
{
    std::vector<File *> result;
    // Your code here.
    std::vector<File *> fileArray = root_->files_;

    for (File *f : fileArray)
    {
        if (f->getSize() >= min && f->getSize() <= max)
        {
            result.push_back(f);
        }
    }
    return result;
}

FileTrie::FileTrie()
{
}

FileTrie::~FileTrie()
{
}