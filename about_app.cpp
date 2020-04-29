#include "about_app.h"
#include "ui_about_app.h"

AboutApp::AboutApp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutApp)
{
    ui->setupUi(this);
    QPixmap pMap(":/pf/img/pug_life.jpg");
    ui->pug_label->setPixmap(pMap);
}

AboutApp::~AboutApp()
{
    delete ui;
}
