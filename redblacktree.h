#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "tree.h"

class RedBlackTree : public Tree {
private:
    struct node {
        int data;
        node *parent, *left, *right;
        int color;
    };

    int64_t min(node*);
    int64_t max(node*);
    int64_t count(node*);

    void balance_insert(node*);
    void remove(node*, node*, int64_t);
    void balance_remove(node*);
    void left_rotate(node*);
    void right_rotate(node*);
    node* find(int64_t);
    void draw(node*, QGraphicsScene*, QRect);

    void initializeNULLNode(node*, node*);
    node* searchTreeHelper(node*, int64_t);
    void fixDelete(node*);
    void rbTransplant(node*, node*);
    void deleteNodeHelper(node*, int64_t);
    void insert(node*);
    node* minimum(node*);
    node* maximum(node*);

    node* root = nullptr;
    node* TNULL = nullptr;
public:
    RedBlackTree();
    int64_t min();
    int64_t max();
    int64_t count();
    void insert(int64_t);
    void remove(int64_t);
    void clear();

    void draw(QGraphicsScene*, QRect);
};

#endif
