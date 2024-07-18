#include "qgraphicsscene.h"

#include "avltree.h"
#include "redblacktree.h"
#include "treap.h"
#include "splaytree.h"

#include <QMainWindow>

namespace Ui { class BSGarden; }

class BSGarden : public QMainWindow
{
    Q_OBJECT

public:
    BSGarden(QWidget *parent = nullptr);
    ~BSGarden();

private slots:
    void on_emplace_triggered();
    void on_emplace_random_triggered();
    void on_remove_triggered();
    void on_clear_triggered();
    void on_bst_triggered();
    void on_avl_triggered();
    void on_splay_triggered();
    void on_zoom_in_triggered();
    void on_zoom_out_triggered();

    void on_treap_triggered();

    void on_red_black_triggered();

private:
    Ui::BSGarden *ui;
    QGraphicsScene scene;

    BST bst;
    AvlTree avl;
    RedBlackTree rbt;
    Treap treap;
    SplayTree splay;
    Tree* tree;
    float scale = 1;

    void render();
    void draw_node(QRect pos, int value);
    void rescale();
    void change_tree(Tree *t, QString name);
};
