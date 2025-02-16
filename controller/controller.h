#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QSoundEffect> /// для подклбчения музыки в игры
#include <QObject> /// родительский класс такой, чтобы connect (нажатие кнопок) срабатывал

#include <QLabel> /// тут тож еиспользую текст ВРЕМЕННО!!!!!! ПОТОМ УДАЛИТЬ ИЛИ СКРЫТЬ!!!!!!!!!!

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


private:
    bool Mute{false};
    QSoundEffect *sound; /// музыкальная дорожка

};


};///end namespace s21

#endif // CONTROLLER_H
