#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model_ =  new TableModel(this);
    auto createTableAction = new QAction("Create new table");
    auto clearTableAction = new QAction("Clear table");
    table_view_ = new CTableView(this);
    connect(ui->exitAction, &QAction::triggered, this, &MainWindow::closeApplication);
    connect(ui->manualAction, &QAction::triggered, this, &MainWindow::openManual);
    connect(ui->aboutApplicationAction, &QAction::triggered, this, &MainWindow::openAboutApp);
    table_view_->setModel(model_);
    setCentralWidget(table_view_);

    ui->tool_bar_->addAction(createTableAction);
    ui->tool_bar_->addAction(clearTableAction);

    connect(table_view_, &CTableView::addRowUnderTriggered, model_, &TableModel::addRowUnder);
    connect(table_view_, &CTableView::addRowBelowTriggered, model_, &TableModel::addRowBelow);
    connect(table_view_, &CTableView::addColumnBeforeTriggered, model_, &TableModel::addColumnBefore);
    connect(table_view_, &CTableView::addColumnAfterTriggered, model_, &TableModel::addColumnAfter);
    connect(table_view_, &CTableView::deleteRowTriggered, model_, &TableModel::removeRow);
    connect(table_view_, &CTableView::deleteColumnTriggered, model_, &TableModel::removeColumn);
    connect(clearTableAction, &QAction::triggered, model_, &TableModel::cleanTable);
    connect(createTableAction, &QAction::triggered, this, &MainWindow::createNewTableDialog);
}
void MainWindow::createNewTableDialog()
{
    if (dialog_ == nullptr) {
        dialog_ = new CreateNewTableDialog();
        dialog_->setWindowFlags (dialog_->windowFlags() & ~Qt::WindowContextHelpButtonHint);
        connect(dialog_, &CreateNewTableDialog::createNewTable, this->model_, &TableModel::createTable);
    }
    dialog_->show();
}

void MainWindow::closeApplication()
{
    QApplication::quit();
}

void MainWindow::openManual()
{
    if (manual_ == nullptr) {
        manual_ = new Manual();
    }
    manual_->show();
}

void MainWindow::openAboutApp()
{
    if (about_window_ == nullptr) {
        about_window_ = new AboutApp();
    }
    about_window_->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

