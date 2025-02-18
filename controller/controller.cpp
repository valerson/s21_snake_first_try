#include "controller.h"

namespace s21{
controller::controller() {
    sound = new QSoundEffect();

}

void controller::sound_intro(){
    ///делаем музыку интро
    sound->setSource(QUrl::fromLocalFile(":/audio/audio/intro.wav"));
    sound->setVolume(0.8);
    sound->play();
};

void controller::sound_mute(){
    if (Mute)
    {   sound->setMuted(false);
        Mute=false;
    }
    else
    {
        sound->setMuted(true);
        Mute=true;
    }
};

void controller::quit(){
    QLabel * label = new QLabel("QUIT!!!!");
    label->show();
};

void controller::pause(){
    QLabel * label = new QLabel("PAUSE!!!!");
    label->show();
};

void controller::press_left(){
    QLabel * label = new QLabel("LEFT!!!!");
    label->show();
};

void controller::press_right(){
    QLabel * label = new QLabel("RIGHT!!!!");
    label->show();
};

void controller::press_up(){
    QLabel * label = new QLabel("UO!!!!");
    label->show();
};

void controller::press_down(){
    QLabel * label = new QLabel("DOWN!!!!");
    label->show();
};

void controller::press_rotate(){
    QLabel * label = new QLabel("ROTATE!!!!");
    label->show();
};


void controller::menuStartGame(int msec){
    QTimer::singleShot(msec, this, []() {
        qDebug() << "MENUstartGAME";
        QLabel *temp = new QLabel("ЗАПУСКАЙ ВЫБОР ИГРЫ!!");
        temp->show();
    });

};





}; /// end namespace s21
