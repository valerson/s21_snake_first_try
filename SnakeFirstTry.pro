# TEMPLATE = app
# CONFIG += console c++17
# CONFIG -= app_bundle
# CONFIG -= qt
QT += widgets # подключил для возможности работы с QWidget
QT += multimedia #подключил для музыки в играх


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
