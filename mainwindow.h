#pragma once
#include <QMainWindow>
#include "c_table_view.h"
#include "table_model.h"
#include "create_new_table_dialog.h"
#include "manual.h"
#include "about_app.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Q_SLOT void createNewTableDialog();
    Q_SLOT void closeApplication();
    Q_SLOT void openManual();
    Q_SLOT void openAboutApp();
private:
    Ui::MainWindow *ui;
    CTableView* table_view_ = nullptr;
    TableModel* model_ = nullptr;
    CreateNewTableDialog* dialog_ = nullptr;
    Manual* manual_ = nullptr;
    AboutApp* about_window_ = nullptr;
};
