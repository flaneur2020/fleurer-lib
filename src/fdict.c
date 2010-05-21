#include <stdlib.h>
#include "fdict.h"

/*************************************************************/
Node* fnode(int key, int val, Node* pnode);
Node* fnode_prev(Node *node);
Node* fnode_succ(Node *node);
Node* fnode_max(Node *node);
Node* fnode_min(Node *node);
Node* fnode_lookup(Node *pnode, int key);
Node* fnode_insert(Node *pnode, int key, int val);
Node* fnode_remove(Node *root, Node *node);
int   fnode_replace_in_parent(Node *xnode, Node *node);
int   fnode_each(Node *pnode, int (*func)(int key, int val));
/*************************************************************/

Node* fnode(int key, int val, Node* pnode) {
    Node* node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->val = val;
    node->left   = NULL;
    node->right  = NULL;
    node->parent = pnode;
    return node;
}

// return NULL/0 on fail
Node* fnode_lookup(Node *pnode, int key) {
    if (pnode==NULL) {
        return NULL;
    }
    //
    int pkey = pnode->key;
    if (key == pkey) {
        return pnode;
    }
    else if (key > pkey) {
        return fnode_lookup(pnode->right, key);
    }
    else if (key < pkey) {
        return fnode_lookup(pnode->left, key);
    }
}

// return 0 on fails
Node* fnode_insert(Node *pnode, int key, int val){
    int pkey = pnode->key;
    if (key == pkey) {
        pnode->val = val;
        return pnode;
    }
    else if (key > pkey) {
        if (pnode->right==NULL) {
            pnode->right = fnode(key, val, pnode);
            return pnode->right;
        }
        return fnode_insert(pnode->right, key, val);
    }
    else if (key < pkey) {
        if (pnode->left==NULL) {
            pnode->left = fnode(key, val, pnode);
            return pnode->left;
        }   
        return fnode_insert(pnode->left, key, val);
    }
}

// if 0, node is the new root;
int fnode_replace_in_parent(Node *xnode, Node *node) {
    if (node) {
        node->parent = xnode->parent;
    }
    if (xnode->parent){
        if (xnode->parent->left==xnode){
            xnode->parent->left = node;
        }
        else {
            xnode->parent->right = node;
        }
        return 1;
    }
    else {
        return 0;
    }
}

Node* fnode_remove(Node *root, Node *node){
    Node *succ, *xnode;
    // two children
    if (node->right && node->left){
        Node *succ = fnode_succ(node);
        node->key = succ->key;
        node->val = succ->val;
        fnode_remove(root, succ);
    }
    // one child
    else if (node->left || node->right){
        if (node->left) { xnode = node->left; }
        else            { xnode = node->right; }
        if (fnode_replace_in_parent(node, xnode)==0) {
            root = xnode;
        }
    }
    // no child
    else {
        if (fnode_replace_in_parent(node, NULL)==0) {
            root = NULL;
        }
    }
    // free it and return a new root
    return root;
}

int fnode_each(Node *pnode, int (*func)(int key, int val)){
    func(pnode->key, pnode->val);
    if (pnode->right!=NULL){
        fnode_each(pnode->right, func);
    }
    if (pnode->left!=NULL){
        fnode_each(pnode->left, func);
    }
}

// helpers and blah~
// min & max
Node* fnode_min(Node *pnode) {
    if (pnode->left == NULL) {
        return pnode;
    }
    return fnode_min(pnode->left);
}

Node* fnode_max(Node *pnode) {
    if (pnode->right == NULL) {
        return pnode;
    }
    return fnode_max(pnode->right);
}

// succ & prev
Node* fnode_succ(Node *node) {
    if (node->right != NULL){
        return fnode_min(node->right);
    }    
    Node* pnode = node->parent;
    while (pnode!=NULL && node==pnode->right) {
        node = pnode;
        pnode = pnode->parent;
    }
    return pnode;
}

Node* fnode_prev(Node *node) {
    if (node->left != NULL) {
        return fnode_max(node->left);
    }
    Node* pnode = node->parent;
    while (pnode!=NULL && node==pnode->left) {
        node = pnode;
        pnode = pnode->parent;
    }
    return pnode;
}

/*************************************************************/
// now just a wrapper
FDict* fd_new(){
    FDict* fd = (FDict*)malloc(sizeof(FDict));
    fd->root = NULL;
    return fd;
}

int fd_insert(FDict *fd, int key, int val){
    if(fd->root==NULL) {
        fd->root = fnode(key, val, NULL);
    }
    else {
        fnode_insert(fd->root, key, val);
    }
    return 1;
}

int* fd_lookup(FDict *fd, int key){
    Node *node = fnode_lookup(fd->root, key);
    if (node==NULL){
        return NULL;
    }
    else {
        return &(node->val);
    }
}

int fd_remove(FDict *fd, int key){
    Node *node;
    node = fnode_lookup(fd->root, key);
    if (node==NULL) {
        return 0;
    }
    fd->root = fnode_remove(fd->root, node);
    return 1;
}

int fd_each(FDict *fd, int (*func)(int key, int val)){
    if (fd->root) {
        fnode_each(fd->root, func);
    }
    return 0;
}
