#include "bst.h"

int BST::height(node* t) {
    if(t == nullptr)
        return 0;
    else
        return t->height;
}
void BST::update_node(node* t) {
    t->height = std::max(height(t->left), height(t->right)) + 1;
}

BST::node*& BST::min(node*& t) {
    if(t->left == nullptr)
        return t;
    else
        return min(t->left);
}
BST::node*& BST::max(node*& t) {
    if(t->right == nullptr)
        return t;
    else
        return max(t->right);
}

int BST::count(node* t) {
    if(t == nullptr)
        return 0;

    return count(t->left) + count(t->right) + 1;
}

BST::node*& BST::find(node*& t, int64_t x) {
    if(t == nullptr)
        return t;

    if(x == t->elem)
        return t;

    if(x < t->elem)
        return find(t->left, x);
    else
        return find(t->right, x);
}
void BST::update(node* t, int64_t x) {
    if(t == nullptr)
        return;

    if(x < t->elem)
        update(t->left, x);
    else if(x > t->elem)
        update(t->right, x);

    update_node(t);
}

int64_t BST::min() {
    if(root == nullptr)
        return INT64_MAX;
    else
        return min(root)->elem;
}
int64_t BST::max() {
    if(root == nullptr)
        return -INT64_MAX;
    else
        return max(root)->elem;
}

int BST::count() {
    return count(root);
}

void BST::insert(int64_t x) {
    node** parent = &find(root, x);
    if(*parent == nullptr) {
        *parent = new node(x);
        update(root, x);
    }
}
void BST::remove(int64_t x) {
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
void BST::clear() {
    root = nullptr;
}

void BST::draw(QGraphicsScene* scene, QRect root_pos) {
    draw(root, scene, root_pos);
}
