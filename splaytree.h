#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include "bst.h"

class SplayTree : public BST {
private:
    node*& find_parent(node*&, int64_t);

    void left_zig_zig(node*, node*, node*&);
    void right_zig_zig(node*, node*, node*&);
    void left_zig_zag(node*, node*, node*&);
    void right_zig_zag(node*, node*, node*&);
    void left_zig(node*, node*&);
    void right_zig(node*, node*&);

    void splay(node*&, node*);

    node* merge(node*&, node*&);
    std::pair<node*, node*> split(node*&, int64_t);
public:
    void splay(int64_t);
    void insert(int64_t);
    void remove(int64_t);
};


#endif
