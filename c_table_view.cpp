#include "c_table_view.h"
#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QMenu>
CTableView::CTableView(QWidget *parent) : QTableView(parent)
{
    popup_menu_ = new QMenu(this);
    auto addRowUnderAction = new QAction("Insert row under", this);
    auto addRowBelowAction = new QAction("Insert row below", this);
    auto addColumnBeforeAction = new QAction("Insert column before", this);
    auto addColumnAfterAction = new QAction("Insert column after", this);
    auto deleteRowAction = new QAction("Delete row", this);
    auto deleteColumnAction = new QAction("Delete column", this);

    popup_menu_->addAction(addRowUnderAction);
    popup_menu_->addAction(addRowBelowAction);
    popup_menu_->addAction(addColumnBeforeAction);
    popup_menu_->addAction(addColumnAfterAction);
    popup_menu_->addAction(deleteRowAction);
    popup_menu_->addAction(deleteColumnAction);

    connect(addRowUnderAction,      &QAction::triggered,    [=](){ emit addRowUnderTriggered(click_index_);     } );
    connect(addRowBelowAction,      &QAction::triggered,    [=](){ emit addRowBelowTriggered(click_index_);     } );
    connect(addColumnBeforeAction,  &QAction::triggered,    [=](){ emit addColumnBeforeTriggered(click_index_); } );
    connect(addColumnAfterAction,   &QAction::triggered,    [=](){ emit addColumnAfterTriggered(click_index_);  } );
    connect(deleteRowAction,        &QAction::triggered,    [=](){ emit deleteRowTriggered(click_index_);       } );
    connect(deleteColumnAction,     &QAction::triggered,    [=](){ emit deleteColumnTriggered(click_index_);    } );
}

void CTableView::keyPressEvent(QKeyEvent *event){
    QModelIndexList selectedRows = selectionModel()->selectedRows();

    if(!selectedRows.isEmpty()){
        if(event->key() == Qt::Key_Insert)
            model()->insertRows(selectedRows.at(0).row(),
                                selectedRows.size());
        else if(event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace)
            model()->removeRows(selectedRows.at(0).row(),
                                selectedRows.size());
    }

    if(!selectedIndexes().isEmpty()){
        if(event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace){
            foreach (QModelIndex index, selectedIndexes())
                model()->setData(index, QStringLiteral());
        }
        else if(event->matches(QKeySequence::Copy)){
                QString text;
                auto range = selectionModel()->selection().first();
                for (auto i = range.top(); i <= range.bottom(); i++)
                {
                    QStringList elements;
                    for (auto j = range.left(); j <= range.right(); j++)
                        elements << model()->index(i,j).data().toString();
                    text += elements.join("\t");
                    text += "\n";
                }
                QApplication::clipboard()->setText(text);
        }
        else if(event->matches(QKeySequence::Paste)) {
                 QString text = QApplication::clipboard()->text();
                 QStringList rows = text.split("\n", QString::SkipEmptyParts);

                 QModelIndex pasteIndex = selectedIndexes().at(0);
                 auto row = pasteIndex.row();
                 auto col = pasteIndex.column();

                 for (auto i = 0; i < rows.size(); i++) {
                     QStringList elements = rows.at(i).split("\t");
                     for (auto j = 0; j < elements.size(); j++) {
                         qDebug () << "||" << row + i << col + j;
                         model()->setData(model()->index(row + i, col + j), elements.at(j));
                     }
                 }
         }
         else
            QTableView::keyPressEvent(event);
    }
}

void CTableView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;
    click_index_ = selectedIndexes().at(0);
    popup_menu_->exec(event->globalPos());
}
