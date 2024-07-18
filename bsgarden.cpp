#include "bsgarden.h"
#include "./ui_bsgarden.h"

#include<QGraphicsTextItem>
#include <QInputDialog>
#include <QMessageBox>
#include <QScrollBar>

BSGarden::BSGarden(QWidget *parent) : QMainWindow(parent), ui(new Ui::BSGarden) {
    ui->setupUi(this);
    ui->gv->setScene(new QGraphicsScene());

    srand(time(0));
    change_tree(&bst, "");
}

BSGarden::~BSGarden() {
    delete ui;
}

void draw_node(QGraphicsScene* scene, QRect pos, int value) {
    QPen pen = QPen();
    pen.setWidth(2);
    pen.setBrush(QColor::fromRgb(0, 64, 0));

    QGraphicsItem* node = scene->addEllipse(pos, pen, QColor::fromRgb(127, 192, 127));
    node->setFlag(QGraphicsItem::ItemIsSelectable);
    QGraphicsTextItem *text = scene->addText(QString::number(value), QFont("Consolas", 12));
    text->setPos(pos.center().x() - text->boundingRect().width() / 2, pos.center().y() - text->boundingRect().height() / 2);
    text->setParentItem(node);
    text->setDefaultTextColor(QColor::fromRgb(0, 64, 0));
}

void draw_arrow(QGraphicsScene* scene, QLine line) {
    QPen pen = QPen();
    pen.setWidth(2);

    float dist = sqrt(line.dx()*line.dx() + line.dy()*line.dy());

    float lcos = line.dx() / dist, lsin = line.dy() / dist;
    float dcos = 0.939692621, dsin = 0.342020143; // 20 degree

    float cos1 = lcos*dcos - lsin*dsin, sin1 = lsin*dcos + lcos*dsin;
    float cos2 = lcos*dcos + lsin*dsin, sin2 = lsin*dcos - lcos*dsin;
    QPoint p1 = QPoint(line.x2() - cos1 * 7, line.y2() - sin1 * 7),
           p2 = QPoint(line.x2() - cos2 * 7, line.y2() - sin2 * 7);

    scene->addLine(line, pen);

    QPolygon head;
    head << line.p2() << p1 << p2;
    scene->addPolygon(head, pen, pen.brush());
}

void BST::draw(node* t, QGraphicsScene* scene, QRect pos) {
    if(t == nullptr)
        return;

    draw_node(scene, pos, t->elem);

    if(t->left) {
        QRect lpos;
        int mc = 0;
        if(t->left->right)
            mc = count(t->left->right);
        lpos.setRect(pos.x() - (mc + 1.0) / 2 * pos.width(), pos.y() + pos.height() * 1.5, pos.width(), pos.height());

        draw_arrow(scene, QLine(pos.center().x(), pos.y() + pos.height(), lpos.center().x(), lpos.y()));
        draw(t->left, scene, lpos);
    }
    if(t->right) {
        QRect rpos;
        int mc = 0;
        if(t->right->left)
            mc = count(t->right->left);
        rpos.setRect(pos.x() + (mc + 1.0) / 2 * pos.width(), pos.y() + pos.height() * 1.5, pos.width(), pos.height());

        draw_arrow(scene, QLine(pos.center().x(), pos.y() + pos.height(), rpos.center().x(), rpos.y()));
        draw(t->right, scene, rpos);
    }
}

void draw_rb_node(QGraphicsScene* scene, QRect pos, int value, char col) {
    QPen pen = QPen();
    pen.setWidth(2);
    pen.setBrush(col == 'b' ? QColor::fromRgb(127, 127, 127) : QColor::fromRgb(16, 16, 16));

    QGraphicsItem* node = scene->addEllipse(pos, pen,(col == 'b' ? QColor::fromRgb(16, 16, 16) : QColor::fromRgb(192, 64, 64)));
    node->setFlag(QGraphicsItem::ItemIsSelectable);
    QGraphicsTextItem *text = scene->addText(QString::number(value), QFont("Consolas", 12));
    text->setPos(pos.center().x() - text->boundingRect().width() / 2, pos.center().y() - text->boundingRect().height() / 2);
    text->setParentItem(node);
    text->setDefaultTextColor(col == 'b' ? QColor::fromRgb(192, 192, 192) : QColor::fromRgb(16, 16, 16));
}

void RedBlackTree::draw(node* t, QGraphicsScene* scene, QRect pos) {
    if(t == TNULL)
        return;

    draw_rb_node(scene, pos, t->data, (t->color == 0 ? 'b' : 'r'));

    if(t->left != TNULL) {
        QRect lpos;
        int mc = 0;
        if(t->left->right)
            mc = count(t->left->right);
        lpos.setRect(pos.x() - (mc + 1.0) / 2 * pos.width(), pos.y() + pos.height() * 1.5, pos.width(), pos.height());

        draw_arrow(scene, QLine(pos.center().x(), pos.y() + pos.height(), lpos.center().x(), lpos.y()));
        draw(t->left, scene, lpos);
    }
    if(t->right != TNULL) {
        QRect rpos;
        int mc = 0;
        if(t->right->left)
            mc = count(t->right->left);
        rpos.setRect(pos.x() + (mc + 1.0) / 2 * pos.width(), pos.y() + pos.height() * 1.5, pos.width(), pos.height());

        draw_arrow(scene, QLine(pos.center().x(), pos.y() + pos.height(), rpos.center().x(), rpos.y()));
        draw(t->right, scene, rpos);
    }
}

void draw_treap_node(QGraphicsScene* scene, QRect pos, int x, int y) {
    QPen pen = QPen();
    pen.setWidth(2);
    pen.setBrush(QColor::fromRgb(0, 64, 0));

    QGraphicsItem* node = scene->addEllipse(pos, pen, QColor::fromRgb(127, 192, 127));
    node->setFlag(QGraphicsItem::ItemIsSelectable);
    QGraphicsTextItem *text_x = scene->addText(QString::number(x), QFont("Consolas", 12));
    text_x->setPos(pos.center().x() - text_x->boundingRect().width() / 2, pos.center().y() - 3*text_x->boundingRect().height() / 4);
    text_x->setParentItem(node);
    text_x->setDefaultTextColor(QColor::fromRgb(0, 64, 0));

    QGraphicsTextItem *text_y = scene->addText(QString::number(y), QFont("Consolas", 12));
    text_y->setPos(pos.center().x() - text_y->boundingRect().width() / 2, pos.center().y() - text_y->boundingRect().height() / 4);
    text_y->setParentItem(node);
    text_y->setDefaultTextColor(QColor::fromRgb(255, 64, 0));
}

void Treap::draw(node* t, QGraphicsScene* scene, QRect pos) {
    if(t == nullptr)
        return;

    draw_treap_node(scene, pos, t->x, t->y);

    if(t->left) {
        QRect lpos;
        int mc = 0;
        if(t->left->right)
            mc = count(t->left->right);
        lpos.setRect(pos.x() - (mc + 1.0) / 2 * pos.width(), pos.y() + pos.height() * 1.5, pos.width(), pos.height());

        draw_arrow(scene, QLine(pos.center().x(), pos.y() + pos.height(), lpos.center().x(), lpos.y()));
        draw(t->left, scene, lpos);
    }
    if(t->right) {
        QRect rpos;
        int mc = 0;
        if(t->right->left)
            mc = count(t->right->left);
        rpos.setRect(pos.x() + (mc + 1.0) / 2 * pos.width(), pos.y() + pos.height() * 1.5, pos.width(), pos.height());

        draw_arrow(scene, QLine(pos.center().x(), pos.y() + pos.height(), rpos.center().x(), rpos.y()));
        draw(t->right, scene, rpos);
    }
}

void BSGarden::rescale() {
    ui->gv->fitInView(ui->gv->sceneRect(), Qt::KeepAspectRatio);
    ui->gv->scale(scale, scale);
}

void BSGarden::render() {
    ui->gv->scene()->clear();
    ui->gv->fitInView(ui->gv->sceneRect(), Qt::KeepAspectRatio);

    int size = 10 * qMax(QString::number(tree->min()).size(), QString::number(tree->max()).size());
    tree->draw(ui->gv->scene(), QRect(0, 0, qMax(size, 40), 40));

    rescale();
}

void BSGarden::on_emplace_triggered() {
    bool ok;
    int n = QInputDialog::getInt(this, "Ввод", "Введите добавляемое число", 0, INT_MIN, INT_MAX, 1, &ok);

    if(ok) {
        tree->insert(n);
        render();
    }
}

void BSGarden::on_emplace_random_triggered() {
    bool ok;
    int n = QInputDialog::getInt(this, "Ввод", "Введите кол-во добавляемых чисел", 1, 1, INT_MAX, 1, &ok);

    if(ok) {
        for(int i = 0; i < n; i++)
            tree->insert(rand());
        render();
    }
}

void BSGarden::on_remove_triggered() {
    if(ui->gv->scene()->selectedItems().empty())
        return;

    int rem = ((QGraphicsTextItem*)(ui->gv->scene()->selectedItems()[0]->childItems()[0]))->toPlainText().toInt();
    tree->remove(rem);
    render();
}

void BSGarden::on_clear_triggered() {
    QMessageBox msgBox;
    msgBox.setText("Вы уверены что хотите удалить это дерево?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    auto ret = msgBox.exec();

    if(ret == QMessageBox::Ok) {
        tree->clear();
        render();
    }
}

void BSGarden::change_tree(Tree* t, QString name) {
    tree = t;
    setWindowTitle("BSGarden " + name);
    render();
}

void BSGarden::on_bst_triggered() {
    change_tree(&bst, "");
}

void BSGarden::on_avl_triggered() {
    change_tree(&avl, "AVL");
}

void BSGarden::on_red_black_triggered() {
    change_tree(&rbt, "RedBlack");
}

void BSGarden::on_treap_triggered() {
    change_tree(&treap, "Treap");
}

void BSGarden::on_splay_triggered() {
    change_tree(&splay, "Splay");
}

void BSGarden::on_zoom_in_triggered() {
    scale *= 1.25;
    rescale();
}

void BSGarden::on_zoom_out_triggered() {
    scale *= 0.8;
    rescale();
}
