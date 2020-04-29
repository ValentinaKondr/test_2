#include "create_new_table_dialog.h"
#include "ui_create_new_table_dialog.h"

CreateNewTableDialog::CreateNewTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNewTableDialog)
{
    ui->setupUi(this);
    connect(this, &QDialog::accepted, [=](){
        emit createNewTable(ui->lineEdit->text().toInt(), ui->lineEdit_2->text().toInt());
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
    });
}

CreateNewTableDialog::~CreateNewTableDialog()
{
    delete ui;
}
