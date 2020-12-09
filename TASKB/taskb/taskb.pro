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
    gotoxy.cpp \
    help.cpp \
    main.cpp \
    movedown.cpp \
    moveleft.cpp \
    moveright.cpp \
    moveup.cpp \
    node.cpp \
    pathfinder.cpp \
    point.cpp \
    take.cpp \
    tenemy.cpp \
    textscene.cpp \
    thealthpack.cpp \
    tprotagonist.cpp \
    ttile.cpp \
    widget.cpp

HEADERS += \
    attack.h \
    command.h \
    commandcontroller.h \
    controller.h \
    gotoxy.h \
    help.h \
    movedown.h \
    moveleft.h \
    moveright.h \
    moveup.h \
    node.h \
    pathfinder.h \
    point.h \
    take.h \
    tenemy.h \
    textscene.h \
    thealthpack.h \
    tprotagonist.h \
    ttile.h \
    widget.h


FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    taskb.pro.user

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../world_v4/ -lworl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../world_v4/ -lworld

INCLUDEPATH += $$PWD/../world_v4
DEPENDPATH += $$PWD/../world_v4

unix:!macx: LIBS += -L$$PWD/../world_v4/ -lworl

INCLUDEPATH += $$PWD/../world_v4
DEPENDPATH += $$PWD/../world_v4
