#include "table_model.h"
#include "table_container.h"


TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return model_.rows();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return model_.cols();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= model_.rows() || index.row() < 0)
        return QVariant();

    if (index.column() >= model_.cols() || index.column() < 0)
        return QVariant();

    if (role == Qt::DisplayRole)
        return model_(index.row(), index.column());

    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value && role == Qt::EditRole) {
        model_(index.row(), index.column()) = value.toString();
        emit dataChanged(index, index, QVector<int>() << role);

        // Table extention
        if (index.row() == model_.rows() - 1 && !model_.isRowEmpty(index.row())) {
            insertRows(index.row() + 1, 1);
        }
        if (index.column() == model_.cols() - 1 && !model_.isColumnEmpty(index.column())) {
            insertColumns(index.column() + 1, 1);
        }
        // Table reducing
        if (model_.cols() > 5 && model_.rows() > 5) {
            if (index.row() == model_.rows() - 2 && model_.isRowEmpty(index.row())) {
                removeRows(index.row() + 1, 1);
            }

            if (index.column() == model_.cols() - 2 && model_.isColumnEmpty(index.column())) {
                removeColumns(index.column() + 1, 1);
            }
        }

        return true;
    }
    return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(count)
    beginInsertRows(parent, row, row + count - 1);
    model_.insertRows(row, count);
    endInsertRows();
    return true;
}

bool TableModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    model_.insertColumns(column, count);
    endInsertColumns();
    return true;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    model_.removeRows(row, count);
    endRemoveRows();
    return true;
}

bool TableModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    model_.removeColumns(column, count);
    endRemoveColumns();
    return true;
}

void TableModel::removeRow(QModelIndex index)
{
    removeRows(index.row(), 1);
}

void TableModel::removeColumn(QModelIndex index)
{
    removeColumns(index.column(), 1);
}

void TableModel::addRowUnder(QModelIndex index)
{
    insertRows(index.row(), 1);
}

void TableModel::addRowBelow(QModelIndex index)
{
    insertRows(index.row() + 1, 1);
}

void TableModel::addColumnBefore(QModelIndex index)
{
    insertColumns(index.column(), 1);
}

void TableModel::addColumnAfter(QModelIndex index)
{
    insertColumns(index.column() + 1, 1);
}

void TableModel::cleanTable()
{
    beginResetModel();
    model_.clearTable();
    model_.createTable(TableContainer::kRowNumber, TableContainer::kColumnNumber);
    endResetModel();
}

void TableModel::createTable(int rows, int cols)
{
    beginResetModel();
    model_.clearTable();
    model_.createTable(rows, cols);
    endResetModel();
}
