#include "redblacktree.h"

void RedBlackTree::initializeNULLNode(node* n, node* parent) {
    n->data = 0;
    n->parent = parent;
    n->left = nullptr;
    n->right = nullptr;
    n->color = 0;
}
RedBlackTree::node* RedBlackTree::searchTreeHelper(node* n, int64_t key) {
    if (n == TNULL || key == n->data) {
        return n;
    }
    if (key < n->data) {
        return searchTreeHelper(n->left, key);
    }
    return searchTreeHelper(n->right, key);
}
void RedBlackTree::fixDelete(node* x) {
    node* s;
    while (x != root && x->color == 0) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == 1) {
                s->color = 0;
                x->parent->color = 1;
                left_rotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == 0 && s->right->color == 0) {
                s->color = 1;
                x = x->parent;
            } else {
                if (s->right->color == 0) {
                    // case 3.3
                    s->left->color = 0;
                    s->color = 1;
                    right_rotate(s);
                    s = x->parent->right;
                }
                s->color = x->parent->color;
                x->parent->color = 0;
                s->right->color = 0;
                left_rotate(x->parent);
                x = root;
            }
        } else {
            s = x->parent->left;
            if (s->color == 1) {
                // case 3.1
                s->color = 0;
                x->parent->color = 1;
                right_rotate(x->parent);
                s = x->parent->left;
            }
            if (s->right->color == 0 && s->right->color == 0) {
                s->color = 1;
                x = x->parent;
            } else {
                if (s->left->color == 0) {
                    // case 3.3
                    s->right->color = 0;
                    s->color = 1;
                    left_rotate(s);
                    s = x->parent->left;
                }
                s->color = x->parent->color;
                x->parent->color = 0;
                s->left->color = 0;
                right_rotate(x->parent);
                x = root;
            }
        }
    }
    x->color = 0;
}
void RedBlackTree::rbTransplant(node* u, node* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}
void RedBlackTree::deleteNodeHelper(node* n, int64_t key) {
    node* z = TNULL;
    node* x, *y;
    while (n != TNULL) {
        if (n->data == key) {
            z = n;
        }
        if (n->data <= key) {
            n = n->right;
        } else {
            n = n->left;
        }
    }
    if (z == TNULL) {
        return;
    }
    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL) {
        x = z->right;
        rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
        x = z->left;
        rbTransplant(z, z->left);
    } else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (y_original_color == 0) {
        fixDelete(x);
    }
}

RedBlackTree::RedBlackTree() {
    TNULL = new node;
    TNULL->color = 0;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
}
void RedBlackTree::insert(node* k) {
    node* u;
    while (k->parent->color == 1) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left; // uncle
            if (u->color == 1) {
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    right_rotate(k);
                }
                k->parent->color = 0;
                k->parent->parent->color = 1;
                left_rotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right;
            if (u->color == 1) {
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    left_rotate(k);
                }
                k->parent->color = 0;
                k->parent->parent->color = 1;
                right_rotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = 0;
}

int64_t RedBlackTree::count() {
    return count(root);
}

int64_t RedBlackTree::count(node* t) {
    if(t == nullptr)
        return 0;

    return count(t->left) + count(t->right) + 1;
}

RedBlackTree::node* RedBlackTree::minimum(node* n) {
    while (n->left != TNULL) {
        n = n->left;
    }
    return n;
}
RedBlackTree::node* RedBlackTree::maximum(node* n) {
    while (n->right != TNULL) {
        n = n->right;
    }
    return n;
}

void RedBlackTree::left_rotate(node* x) {
    node* y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}
void RedBlackTree::right_rotate(node* x) {
    node* y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void RedBlackTree::insert(int64_t key) {
    node* n = new node;
    n->parent = nullptr;
    n->data = key;
    n->left = TNULL;
    n->right = TNULL;
    n->color = 1;
    node* y = nullptr;
    node* x = this->root;
    while (x != TNULL) {
        y = x;
        if (n->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    n->parent = y;
    if (y == nullptr) {
        root = n;
    } else if (n->data < y->data) {
        y->left = n;
    } else {
        y->right = n;
    }
    if (n->parent == nullptr){
        n->color = 0;
        return;
    }
    if (n->parent->parent == nullptr) {
        return;
    }
    insert(n);
}
void RedBlackTree::remove(int64_t data) {
    deleteNodeHelper(root, data);
}

int64_t RedBlackTree::min() {
    if(root == TNULL)
        return INT64_MAX;
    else
        return minimum(root)->data;
}
int64_t RedBlackTree::max() {
    if(root == TNULL)
        return INT64_MIN;
    else
        return maximum(root)->data;
}

void RedBlackTree::clear() {
    root = nullptr;
}

void RedBlackTree::draw(QGraphicsScene* scene, QRect root_pos) {
    draw(root, scene, root_pos);
}
