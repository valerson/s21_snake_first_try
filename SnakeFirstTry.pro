# TEMPLATE = app
# CONFIG += console c++17
# CONFIG -= app_bundle
# CONFIG -= qt
QT += widgets # подключил для возможности работы с QWidget
QT += multimedia #подключил для музыки в играх


SOURCES += \
    brick_game/snake/s21_snake.cpp \
    controller/controller.cpp \
    gui/desktop/s21_desktop.cpp \
    main_desktop.cpp

HEADERS += \
    brick_game/snake/s21_snake.h \
    controller/controller.h \
    gui/desktop/s21_desktop.h

RESOURCES += \
    resource/resource.qrc


# ICON = resource/logo_app.icns  # пытался изменить иконку. не сработало
# QMAKE_INFO_PLIST = resource/Info.plist  # подключаем Info.plist

