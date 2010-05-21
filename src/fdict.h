#ifndef fdict_h
#define fdict_h

typedef struct Node {
    int              key;
    int              val;
    struct Node     *left;
    struct Node     *right;
    struct Node     *parent;
} Node;

typedef struct FDict {
    Node            *root;
} FDict;


FDict* fd_new();
int* fd_lookup(FDict *fd, int key);
int  fd_insert(FDict *fd, int key, int val);
int  fd_remove(FDict *fd, int key);
int  fd_each  (FDict *fd, int (*func)(int key, int val));

#endif
