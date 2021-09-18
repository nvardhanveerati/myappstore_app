# myappstore_app
This project implements `myAppStore` in which applications of various categories are indexed simultaneously by a hashtable, a max-heap and by a binary search tree(BST) for optimal support of various queries and updates of the store.
Here,
- The `myAppStore` is populated with data on application under various categories. The data is stored in both a hashtable (fast lookup), in a BST (for range search queries), and in a max-heap (for selection queries).
- Queries are then processed about the apps, updating the `myAppStore` when needed
This code is implemented in C++, with dynamic memory allocation `new()` and deallocation `free()`. No external libraries were used except standard libraries for I/O and string functions.
