#ifndef TREE_H
#define TREE_H

#include "QRect"
#include <QGraphicsScene>

class Tree
{
public:
    virtual int64_t min() = 0;
    virtual int64_t max() = 0;

    virtual void insert(int64_t) = 0;
    virtual void remove(int64_t) = 0;
    virtual void clear() = 0;

    virtual void draw(QGraphicsScene*, QRect) = 0;
};

#endif
