#ifndef ABOUT_APP_H
#define ABOUT_APP_H

#include <QWidget>

namespace Ui {
class AboutApp;
}

class AboutApp : public QWidget
{
    Q_OBJECT

public:
    explicit AboutApp(QWidget *parent = nullptr);
    ~AboutApp();

private:
    Ui::AboutApp *ui;
};

#endif // ABOUT_APP_H
