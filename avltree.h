#ifndef AVLTREE_H
#define AVLTREE_H

#include "bst.h"

class AvlTree : public BST {
private:
    void minor_left_rotate(node*&);
    void minor_right_rotate(node*&);
    void mayor_left_rotate(node*&);
    void mayor_right_rotate(node*&);

    void balance(node*&);
    void update(node*&, int64_t);
public:
    void insert(int64_t);
    void remove(int64_t);
};


#endif
