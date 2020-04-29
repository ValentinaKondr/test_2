#pragma once
#include <QList>

class TableContainer
{
public:
    static const int kRowNumber {5};
    static const int kColumnNumber {5};
    TableContainer();
    TableContainer(int rows, int cols);

    int  rows() const;
    bool insertRows(int row, int count);
    bool removeRows(int row, int count);
    bool isRowEmpty(int row) const;

    int  cols() const;
    bool insertColumns(int col, int count);
    bool removeColumns(int col, int count);
    bool isColumnEmpty(int col) const;

    void clearTable();
    void createTable(int rows, int cols);
    QString& operator() (int row, int col);
    QString  operator() (int row, int col) const;
    void show();
    ~TableContainer();
private:
    int rows_;
    int cols_;
    QList<QStringList> table_;
};
