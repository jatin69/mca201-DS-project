# mca201-DS-project

Data Structure Project. B Plus Tree (In-memory)

## B+ Tree
- Insertion
- Deletion
- Traversal
- Search

### References

- [Intro](https://www.geeksforgeeks.org/b-tree-set-1-introduction-2/)
- [Insertion](https://www.geeksforgeeks.org/b-tree-set-1-insert-2/)
- [Deletion](https://www.geeksforgeeks.org/b-tree-set-3delete/)
- [BTree key-value pair - IN MEMORY](https://github.com/wymay/BplusTree-c-)
- [BTree for DBMS - IN MEMORY](https://github.com/parachvte/B-Plus-Tree)
- [Tutorial](http://sketchingdream.com/blog/b-plus-tree-tutorial/) with its [code](https://github.com/sayef/bplus-tree/)

### Tools

- CodeBlocks 16.01
- Default MingW compiler of codeblocks with option : `-std=c++11`
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
- Codeblocks is not auto-wrapping after 80 chars. So using VS code default formatting.
- If you want to switch to dark color theme [follow this video](https://www.youtube.com/watch?v=H-7uVSrnrnU)

## Future scope

- Implement on-disk B-Plus Tree
