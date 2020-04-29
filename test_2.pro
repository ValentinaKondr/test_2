QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about_app.cpp \
    c_table_view.cpp \
    create_new_table_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    manual.cpp \
    table_container.cpp \
    table_model.cpp

HEADERS += \
    about_app.h \
    c_table_view.h \
    create_new_table_dialog.h \
    mainwindow.h \
    manual.h \
    table_container.h \
    table_model.h

FORMS += \
    about_app.ui \
    create_new_table_dialog.ui \
    mainwindow.ui \
    manual.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    img/pug_life.jpg

RESOURCES += \
    rsc.qrc
