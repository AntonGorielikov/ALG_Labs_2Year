TEMPLATE = app

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

HEADERS += \
    mainwindow.h \
    vectormodel.h \
    algorithms.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    vectormodel.cpp
