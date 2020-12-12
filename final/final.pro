QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attack.cpp \
    command.cpp \
    commandcontroller.cpp \
    controller.cpp \
    gameoverscene.cpp \
    genemy.cpp \
    ghealthpack.cpp \
    gotoxy.cpp \
    gpenemy.cpp \
    gprotagonist.cpp \
    gscene.cpp \
    gtile.cpp \
    gview.cpp \
    gxenemy.cpp \
    help.cpp \
    keypresscontroller.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    movedown.cpp \
    moveleft.cpp \
    moveright.cpp \
    moveup.cpp \
    node.cpp \
    pathfinder.cpp \
    point.cpp \
    take.cpp \
    tenemy.cpp \
    thealthpack.cpp \
    tprotagonist.cpp \
    tscene.cpp \
    ttile.cpp \
    xenemy.cpp

HEADERS += \
    attack.h \
    command.h \
    commandcontroller.h \
    config.h \
    controller.h \
    gameoverscene.h \
    genemy.h \
    ghealthpack.h \
    gotoxy.h \
    gpenemy.h \
    gprotagonist.h \
    gscene.h \
    gtile.h \
    gview.h \
    gxenemy.h \
    help.h \
    keypresscontroller.h \
    mainwindow.h \
    model.h \
    movedown.h \
    moveleft.h \
    moveright.h \
    moveup.h \
    node.h \
    pathfinder.h \
    point.h \
    take.h \
    tenemy.h \
    thealthpack.h \
    tprotagonist.h \
    tscene.h \
    ttile.h \
    xenemy.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../worldLib/ -lworld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../worldLib/ -lworld
unix:!macx: LIBS += -L$$PWD/../worldLib/ -lworld

INCLUDEPATH += $$PWD/../worldLib
DEPENDPATH += $$PWD/../worldLib
