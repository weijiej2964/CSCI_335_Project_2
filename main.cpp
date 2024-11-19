#include "FileTrie.hpp"
#include "FileAVL.hpp"

int main()
{
    FileAVL avl = FileAVL();
    FileTrie f = FileTrie();

    File file1 = File("file1", "this is my first file ever yay");
    File file2 = File("file2", "this is my first file ever");
    File file3 = File("file3", "this is my first file");
    File file4 = File("file4", "this is my first");
    File file5 = File("file5", "this is my");
    File file6 = File("file6", "this is");
    File file7 = File("file7", "this");
    File file8 = File("file8", "this");

    avl.insert(&file1);
    avl.insert(&file2);
    avl.insert(&file3);
    avl.insert(&file4);
    avl.insert(&file5);
    avl.insert(&file6);
    avl.insert(&file7);
    avl.insert(&file8);

    avl.query(16, 7);

    // std::cout << file4.getSize();

    f.addFile(&file1);
    f.addFile(&file2);

    std::unordered_set<File *> f_set = f.getFilesWithPrefix("q");
    std::cout << "prefix search result" << "\n";
    for (File *file : f_set)
    {
        std::cout << file->getName() << "\n";
    }

    return 0;
}