#include "FileAVL.hpp"
#include "FileTrie.hpp"
#include <algorithm>
#include <cctype>
// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp

void queryHelper(std::vector<File *> *out, Node *t, size_t min, size_t max)
{
    // std::cout << t->size_ << "\n";
    if (t->size_ > max)
    {
        if (t->left_ == nullptr)
        {
            return;
        }
        queryHelper(out, t->left_, min, max);
    }
    else if (t->size_ < min)
    {
        if (t->right_ == nullptr)
        {
            return;
        }
        queryHelper(out, t->right_, min, max);
    }
    else
    {
        if (t->left_ != nullptr)
        {
            queryHelper(out, t->left_, min, max);
        }
        for (File *f : t->files_)
        {
            out->push_back(f);
        }
        if (t->right_ != nullptr)
        {
            queryHelper(out, t->right_, min, max);
        }
    }
}

void addFileHelper(File *f, FileTrieNode *t, size_t index)
{
    if (index > f->getName().size())
    {
        return;
    }
    t->matching.insert(f);
    // std::cout << "Prefix: " << t->stored << " \n";
    // for (auto it = t->matching.begin(); it != t->matching.end(); it++)
    // {
    //     std::cout << *it << "\n";
    // }

    std::string filename = f->getName();
    transform(filename.begin(), filename.end(), filename.begin(), ::tolower);
    if (auto search = t->next.find(filename[index]); search == t->next.end())
    {
        t->next[filename[index]] = new FileTrieNode(filename[index]);
    }
    FileTrieNode *nextNode = t->next[filename[index]];

    addFileHelper(f, nextNode, index + 1);
}

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
    if (min > max)
    {
        size_t temp = min;
        min = max;
        max = temp;
    }
    queryHelper(&result, root_, min, max);

    return result;
}

// FileTrie::FileTrie()
// {
//     head = new FileTrieNode();
// }

void FileTrie::addFile(File *f)
{
    addFileHelper(f, head, 0);
}

std::unordered_set<File *> FileTrie::getFilesWithPrefix(const std::string &prefix) const
{
    FileTrieNode *cur_node = head;
    std::string prefixName = prefix;
    transform(prefixName.begin(), prefixName.end(), prefixName.begin(), ::tolower);

    for (auto it = prefixName.begin(); it != prefixName.end(); it++)
    {
        if (cur_node->next.find(*it) == cur_node->next.end())
        {
            return std::unordered_set<File *>();
        }
        cur_node = cur_node->next[*it];
    }

    return cur_node->matching;
}

// FileTrie::~FileTrie() {}