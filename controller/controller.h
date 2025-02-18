#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QSoundEffect> /// для подклбчения музыки в игры
#include <QObject> /// родительский класс такой, чтобы connect (нажатие кнопок) срабатывал

#include <QLabel> /// тут тож использую текст ВРЕМЕННО!!!!!! ПОТОМ УДАЛИТЬ ИЛИ СКРЫТЬ!!!!!!!!!!

#include <QTimer> /// для отсчета времени

enum {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};

namespace s21{
class controller: public QObject
{
public:
    controller();

    void sound_intro();
    void sound_mute();
    void quit();
    void pause();
    void press_left();
    void press_right();
    void press_up();
    void press_down();
    void press_rotate();

    void menuStartGame(int msec);

private:
    bool Mute{false};
    QSoundEffect *sound; /// музыкальная дорожка
    // #ifdef SNAKE_H
    // int dir{UP};
    // #definfe SNAKE_H
    int dir{UP}; /// переменная для движения
    bool rotate{false}; /// кнопка переворота
};


};///end namespace s21

#endif // CONTROLLER_H
