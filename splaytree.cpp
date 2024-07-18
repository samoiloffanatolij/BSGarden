#include "splaytree.h"

SplayTree::node*& SplayTree::find_parent(node*& t, int64_t x) {
    if(x < t->elem) {
        if(t->left == nullptr || t->left->elem == x)
            return t;
        else
            return find_parent(t->left, x);
    }
    else {
        if(t->right == nullptr || t->right->elem == x)
            return t;
        else
            return find_parent(t->right, x);
    }
}

void SplayTree::left_zig_zig(node* t, node* p, node*& g) {
    p->left = t->right;
    g->left = p->right;
    t->right = p;
    p->right = g;

    g = t;
}
void SplayTree::right_zig_zig(node* t, node* p, node*& g) {
    p->right = t->left;
    g->right = p->left;
    t->left = p;
    p->left = g;

    g = t;
}
void SplayTree::left_zig_zag(node* t, node* p, node*& g) {
    p->right = t->left;
    g->left = t->right;
    t->left = p;
    t->right = g;

    g = t;
}
void SplayTree::right_zig_zag(node* t, node* p, node*& g) {
    p->left = t->right;
    g->right = t->left;
    t->right = p;
    t->left = g;

    g = t;
}
void SplayTree::left_zig(node* t, node*& p) {
    p->left = t->right;
    t->right = p;
    p = t;
}
void SplayTree::right_zig(node* t, node*& p) {
    p->right = t->left;
    t->left = p;
    p = t;
}

void SplayTree::splay(node*& t, node* n) {
    while(n != t) {
        node** grandpa = &find_parent(t, n->elem);
        if(*grandpa == t) {
            if((*grandpa)->left == n)
                left_zig(n, *grandpa);
            else
                right_zig(n, *grandpa);
        }
        else {
            node* parent = *grandpa;
            node** grandpa = &find_parent(t, parent->elem);
            if((*grandpa)->left == parent) {
                if(parent->left == n)
                    left_zig_zig(n, parent, *grandpa);
                else
                    left_zig_zag(n, parent, *grandpa);
            }
            else {
                if(parent->right == n)
                    right_zig_zig(n, parent, *grandpa);
                else
                    right_zig_zag(n, parent, *grandpa);
            }
        }
    }
}

SplayTree::node* SplayTree::merge(node*& t1, node*& t2) {
    splay(t2, min(t2));
    t2->left = t1;
    return t2;
}
std::pair<SplayTree::node*, SplayTree::node*> SplayTree::split(node*& t, int64_t x) {
    if(t == nullptr)
        return {nullptr, nullptr};

    node** parent = &find(t, x);
    if(*parent == nullptr) {
        parent = &find_parent(t, x);
    }
    splay(t, *parent);

    if(t->elem > x) {
        node* t1 = t->left;
        t->left = nullptr;
        return {t1, t};
    }
    else {
        node* t2 = t->right;
        t->right = nullptr;
        return {t, t2};
    }
}
void SplayTree::splay(int64_t x) {
    splay(root, find(root, x));
}
void SplayTree::insert(int64_t x) {
    if(find(root, x) != nullptr)
        return;

    auto p = split(root, x);
    root = new node(x);
    root->left = p.first;
    root->right = p.second;
}
void SplayTree::remove(int64_t x) {
    node* rem = find(root, x);
    if(rem == nullptr)
        return;

    splay(root, rem);
    root = merge(root->left, root->right);

    rem->left = rem->right = nullptr;
    delete rem;
}
