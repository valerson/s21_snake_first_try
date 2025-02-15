// #include <iostream>

#include <QApplication>
#include <gui/desktop/s21_desktop.h>

// using namespace std;

#include <QSoundEffect> /// для подклбчения музыки в игры



int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    s21::desktop brick_game;

    ///делаем музыку
    QSoundEffect *sound = new QSoundEffect();
    sound->setSource(QUrl::fromLocalFile(":/audio/audio/intro.wav"));
    sound->setVolume(0.8);
    sound->play();


    brick_game.show();
    return app.exec(); /// возвращает результат исполнениея
}
