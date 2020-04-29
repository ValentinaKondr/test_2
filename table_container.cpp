#include "table_container.h"
#include <algorithm>
#include <QDebug>

TableContainer::TableContainer() : rows_(kRowNumber), cols_(kColumnNumber)
{
    createTable(kRowNumber, kColumnNumber);
}

TableContainer::TableContainer(int rows, int columns) : rows_(rows), cols_(columns)
{
    createTable(rows, columns);
}

bool TableContainer::insertColumns(int col, int count)
{
    if (col > cols_ || col < 0 || count < 0)
        return false;


    for (int i = 0; i < count; i++) {
        for (auto it = table_.begin(); it < table_.end(); it++) {
            if (col == cols_) {
                (*it).append("");
            } else {
            (*it).insert(col, "");
            }
        }
    }
    cols_ += count;
    return true;

}

bool TableContainer::insertRows(int row, int count)
{
    if (row > rows_ || row < 0 || count < 0)
        return false;

    QStringList newRow;
    for (int j = 0; j < cols_; j++) {
        newRow << QStringLiteral();
    }

    if (row == rows_) {
        table_.append(newRow);
        rows_++;
        return true;
    }

    for (int i = 0; i < count; i++) {
        table_.insert(row, newRow);
    }
    rows_ += count;
    return true;
}


bool TableContainer::removeColumns(int col, int count)
{
    if ((count < 1) || (col < 0) || ((col + count) > cols_))
        return false;

    for(int i = 0; i < count; i++) {
        for(auto it = table_.begin(); it < table_.end(); it++) {
            (*it).removeAt(col);
        }
    }
    cols_ -= count;
    return true;
}

bool TableContainer::isColumnEmpty(int col) const
{
    for (auto it = table_.begin(); it < table_.end(); it++) {
        if (!(*it).at(col).isEmpty()) {
            return false;
        }
    }
    return true;
}

bool TableContainer::removeRows(int row, int count)
{
    if ((count < 1) || (row < 0) || ((row + count) > rows_))
        return false;

    for(int i = row; i < row + count; i++) {
        table_[row].clear();
        table_.removeAt(row);
    }
    rows_ -= count;
    return true;
}

bool TableContainer::isRowEmpty(int row) const
{
    auto it = table_.begin() + row;
    for (auto element: (*it)) {
        if (!element.isEmpty()) {
            return false;
        }
    }
    return true;
}

int TableContainer::rows() const
{
    return rows_;
}

int TableContainer::cols() const
{
    return cols_;
}

void TableContainer::clearTable()
{
    for(auto it = table_.begin(); it < table_.end(); it++) {
        (*it).clear();
    }
    table_.clear();
    rows_ = cols_ = 0;
}

void TableContainer::createTable(int rows, int cols)
{
    if (rows_ != 0 && cols_ != 0)
        clearTable();

    QList<QString> row;
    for( int i = 0; i < rows; i++) {
        for( int j = 0; j < cols; j++)
            row.append(QStringLiteral(""));
        table_.push_back(row);
        row.clear();
    }
    rows_ = rows;
    cols_ = cols;
}

QString &TableContainer::operator()(int row, int col)
{
      if (row >= rows_ || col >= cols_)
        throw std::out_of_range ("TableContainer out of range exception");
      return table_[row][col];
}

QString TableContainer::operator()(int row, int col) const
{
    if (row >= rows_ || col >= cols_)
      throw std::out_of_range ("TableContainer out of range exception");
    return table_[row][col];
}

TableContainer::~TableContainer()
{
    clearTable();
}

