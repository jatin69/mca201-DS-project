# mca201-DS-project

Data Structure Project

## B+ Tree
- Insertion
- Deletion
- Traversal
- Search

### References

- [Intro](https://www.geeksforgeeks.org/b-tree-set-1-introduction-2/)
- [Insertion](https://www.geeksforgeeks.org/b-tree-set-1-insert-2/)
- [Deletion](https://www.geeksforgeeks.org/b-tree-set-3delete/)

### Tools

- CodeBlocks 16.01
- Default MingW compiler of codeblocks wiht option : `-std=c++11`
- Goto Setting > Compiler > Global Compiler Settings > Compiler Settings > Other compiler options, and then paste `-std=c++11` in the text box. Test by running the following code. It should run fine.
    ```cpp
    #include <iostream>
    using namespace std;
    int main() {
        cout << "Hello world!" << endl;
        int* n = nullptr;
        cout << "Bye world!" << endl;
        return 0;
    }
    ```
- Code Style : Google
- Goto Setting > Editor > source formatter and choose Google
- On code editor screen, Right click and `format use AStyle` to format.
- If you want to switch to dark color theme [follow this video](https://www.youtube.com/watch?v=H-7uVSrnrnU)