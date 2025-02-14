// #include <iostream>

#include <QApplication>
#include <gui/desktop/s21_desktop.h>

using namespace std;

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    s21::desktop brick_game;

    brick_game.show();
    return app.exec(); /// возвращает результат исполнениея
}
