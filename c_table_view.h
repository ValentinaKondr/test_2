#pragma once

#include <QObject>
#include <QTableView>
#include <QKeyEvent>
#include <QContextMenuEvent>

class CTableView : public QTableView
{
    Q_OBJECT
public:
    CTableView(QWidget* parent = nullptr);
    Q_SIGNAL void addRowUnderTriggered(QModelIndex index);
    Q_SIGNAL void addRowBelowTriggered(QModelIndex index);
    Q_SIGNAL void addColumnBeforeTriggered(QModelIndex index);
    Q_SIGNAL void addColumnAfterTriggered(QModelIndex index);
    Q_SIGNAL void deleteRowTriggered(QModelIndex index);
    Q_SIGNAL void deleteColumnTriggered(QModelIndex index);
    ~CTableView() = default;
protected:
    void keyPressEvent(QKeyEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
private:
    QMenu* popup_menu_ = nullptr;
    QModelIndex click_index_ = QModelIndex();
};
