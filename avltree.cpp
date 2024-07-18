#include "avltree.h"

void AvlTree::minor_left_rotate(node*& t) {
    node* p = t->left, * m = p->right;

    t->height = height(m) + 1;
    p->height = height(t) + 1;

    p->right = t;
    t->left = m;
    t = p;
}
void AvlTree::minor_right_rotate(node*& t) {
    node* p = t->right, * m = p->left;

    t->height = height(m) + 1;
    p->height = height(t) + 1;

    p->left = t;
    t->right = m;
    t = p;
}
void AvlTree::mayor_left_rotate(node*& t) {
    node* p = t->left, *q = p->right, *k = q->right, *n = q->left;

    p->height = t->height = height(t->right) + 1;
    q->height = height(t) + 1;

    q->left = p;
    q->right = t;
    t->left = k;
    p->right = n;
    t = q;
}
void AvlTree::mayor_right_rotate(node*& t) {
    node* p = t->right, *q = p->left, *k = q->left, *n = q->right;

    p->height = t->height = height(t->left) + 1;
    q->height = height(t) + 1;

    q->right = p;
    q->left = t;
    t->right = k;
    p->left = n;
    t = q;
}

void AvlTree::balance(node*& t) {
    if(t == nullptr)
        return;

    if (height(t->left) - height(t->right) > 1) {
        if (height(t->left->right) <= height(t->left->left))
            minor_left_rotate(t);
        else
            mayor_left_rotate(t);
    }
    else if (height(t->right) - height(t->left) > 1) {
        if (height(t->right->left) <= height(t->right->right))
            minor_right_rotate(t);
        else
            mayor_right_rotate(t);
    }
}
void AvlTree::update(node*& t, int64_t x) {
    if(t == nullptr)
        return;

    if(x < t->elem)
        update(t->left, x);
    else if(x > t->elem)
        update(t->right, x);

    balance(t);
    update_node(t);
}

void AvlTree::insert(int64_t x) {
    node** parent = &find(root, x);
    if(*parent == nullptr) {
        *parent = new node(x);
        update(root, x);
    }
}
void AvlTree::remove(int64_t x) {
    node** parent = &find(root, x), *rem = *parent;
    if(rem == nullptr)
        return;

    if(rem->right != nullptr) {
        node** m_parent = &min((*parent)->right), *m = *m_parent;
        *m_parent = m->right;
        m->left = rem->left;
        m->right = rem->right;
        *parent = m;
        update(root, m->elem + 1);
    }
    else {
        *parent = rem->left;
        update(root, rem->elem);
    }

    delete rem;
}
