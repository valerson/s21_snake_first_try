# TEMPLATE = app
# CONFIG += console c++17
# CONFIG -= app_bundle
# CONFIG -= qt
QT += widgets # подключили возможность работы с QWidget


SOURCES += \
    brick_game/snake/s21_snake.cpp \
    gui/desktop/s21_desktop.cpp \
    main_desktop.cpp

HEADERS += \
    brick_game/snake/s21_snake.h \
    gui/desktop/s21_desktop.h

DISTFILES += \
    resource/background.jpg

RESOURCES += \
    resorce.qrc
