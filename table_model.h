#pragma once

#include <QAbstractTableModel>
#include <QList>
#include "table_container.h"
#include <QStandardItemModel>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_SLOT void removeRow(QModelIndex index);
    Q_SLOT void removeColumn(QModelIndex index);
    Q_SLOT void addRowUnder(QModelIndex index);
    Q_SLOT void addRowBelow(QModelIndex index);
    Q_SLOT void addColumnBefore(QModelIndex index);
    Q_SLOT void addColumnAfter(QModelIndex index);
    Q_SLOT void cleanTable();
    Q_SLOT void createTable(int rows, int cols);

private:
    TableContainer model_;
};
