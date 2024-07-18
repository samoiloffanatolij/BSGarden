#ifndef BST_H
#define BST_H

#include "tree.h"

class BST : public Tree {
protected:
    struct node {
        int64_t elem;
        node* left = nullptr, *right = nullptr;

        int height = 1;

        node(int64_t elem) : elem(elem) {};
    };

    int height(node*);
    void update_node(node*);

    node*& min(node*&);
    node*& max(node*&);

    int count(node*);

    node*& find(node*&, int64_t);
    virtual void update(node*, int64_t);

    void draw(node*, QGraphicsScene*, QRect);

    node* root = nullptr;

public:
    int64_t min();
    int64_t max();

    int count();
    void insert(int64_t);
    void remove(int64_t);
    void clear();

    void draw(QGraphicsScene*, QRect);
};

#endif
