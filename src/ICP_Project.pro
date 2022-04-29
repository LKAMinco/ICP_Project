QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = umleditor
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    classentity.cpp \
    clickmenu.cpp \
    main.cpp \
    UmlEditor.cpp \
    cpp/attribute.cpp \
    cpp/class.cpp \
    cpp/entity.cpp \
    cpp/erconnect.cpp \
    cpp/method.cpp \
    scene.cpp

HEADERS += \
    UmlEditor.h \
    classentity.h \
    clickmenu.h \
    cpp/attribute.h \
    cpp/class.h \
    cpp/entity.h \
    cpp/erconnect.h \
    cpp/method.h \
    scene.h

FORMS += \
    UmlEditor.ui \
    classentity.ui \
    clickmenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
