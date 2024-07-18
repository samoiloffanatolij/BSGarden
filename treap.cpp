#include "treap.h"

Treap::node*& Treap::min(node*& t) {
    if(t->left == nullptr)
        return t;
    else
        return min(t->left);
}
Treap::node*& Treap::max(node*& t) {
    if(t->right == nullptr)
        return t;
    else
        return max(t->right);
}

int Treap::count(node* t) {
    if(t == nullptr)
        return 0;

    return count(t->left) + count(t->right) + 1;
}

std::pair<Treap::node*, Treap::node*> Treap::split(node* p, int64_t x) {
    node* p1, * p2;
    if (p == nullptr) {
        p1 = p2 = nullptr;
    }
    else if (p->x < x) {
        auto q = split(p->right, x);
        p->right = q.first;
        p2 = q.second;
        p1 = p;
    }
    else {
        auto q = split(p->left, x);
        p1 = q.first;
        p->left = q.second;
        p2 = p;
    }
    return { p1, p2 };
}

void Treap::merge(node*& p, node* p1, node* p2) {
    if (p1 == nullptr || p2 == nullptr) {
        if (p1 == nullptr) {
          p = p2;
        }
        else {
          p = p1;
        }
    }
    else if (p1->y > p2->y) {
        merge(p1->right, p1->right, p2);
        p = p1;
    }
    else {
        merge(p2->left, p1, p2->left);
        p = p2;
    }
}

void Treap::insert(node*& p, node* var) {
    if (p == nullptr) {
        p = var;
        return;
    }

    if (p->y < var->y) {
        auto q = split(p, var->x);
        var->left = q.first;
        var->right = q.second;
        p = var;
    }
    else if (p->x > var->x) {
        insert(p->left, var);
    }
    else if (p->x < var->x) {
        insert(p->right, var);
    }
    else {
        return;
    }
}

void Treap::remove(node*& t, int64_t x) {
    if (t == nullptr) {
        return;
    }
    if (x > t->x) {
        remove(t->right, x);
    }
    else if (x < t->x) {
        remove(t->left, x);
    }
    else {
        merge(t, t->left, t->right);
    }
}

int64_t Treap::min() {
    if(root == nullptr)
        return INT64_MAX;
    else
        return min(root)->x;
}
int64_t Treap::max() {
    if(root == nullptr)
        return -INT64_MAX;
    else
        return max(root)->x;
}

int Treap::count() {
    return count(root);
}

void Treap::insert(int64_t x) {
    insert(root, new node(x));
}
void Treap::remove(int64_t x) {
    remove(root, x);
}
void Treap::clear() {
    root = nullptr;
}

void Treap::draw(QGraphicsScene* scene, QRect root_pos) {
    root_pos.setHeight(root_pos.height() * 1.5);
    draw(root, scene, root_pos);
}
