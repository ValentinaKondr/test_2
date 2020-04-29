#pragma once

#include <QDialog>

namespace Ui {
class CreateNewTableDialog;
}

class CreateNewTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateNewTableDialog(QWidget *parent = nullptr);
    ~CreateNewTableDialog();
    Q_SIGNAL void createNewTable(int rows, int cols);

private:
    Ui::CreateNewTableDialog *ui;
};

