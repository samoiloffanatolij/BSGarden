#ifndef TREAP_H
#define TREAP_H

#include "tree.h"

class Treap : public Tree {
private:
    struct node {
      int64_t x, y;
      node* left = nullptr,* right = nullptr;

      node(int64_t x) : x(x), y(rand()) {}
    };

    node*& min(node*&);
    node*& max(node*&);

    int count(node*);

    std::pair<node*, node*> split(node*, int64_t);
    void merge(node*&, node*, node*);

    void insert(node*&, node*);
    void remove(node*&, int64_t);

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
