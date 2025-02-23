#ifndef S21_DESKTOP_H
#define S21_DESKTOP_H

#include <QWidget> /// как родитеель для нашего приложения в целом
#include <QPalette> /// цветовые группы

///для подключения меню (для справка - о программе)
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include <QLabel> /// Для тестов

#include <QPushButton> /// добавдение кнопок

#include <QVBoxLayout> ///  Выстраивает виджеты вертикально (для подписи кнопок)
#include <QHBoxLayout> /// Выстраивает виджеты горизонтально

#include <QGraphicsScene> /// для отрисовки полей в приложениb - в том числе дисплея и в дисплее
#include <QGraphicsView> /// как родитель для QGraphicScene
#include <QGraphicsProxyWidget> /// для добавления в сцену виджетов

#include <QString> /// тип std::string в QT

#include <QPixmap> /// Для украшательства (картинки вставлять)

#include <QMovie> /// Для украшательства (для стартовой и конечной гифок)

#include <QKeyEvent> /// для считывания нажатия клавиатуры

#include <controller/controller.h> /// контроллер, лдя соблюдение требований задания - паттерн mvc


/*размеры клетки*/
#define PIXEL_WIDTH 20
#define PIXEL_HEIGHT 20
/*размеры игрового поля (пискелей)*/
#define FIELD_WIDTH 200
#define FIELD_HEIGHT 400
/*размеры дисплея (с очками, уровнем, скоростью и т.п.)*/
#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 400
/*размеры приложения*/
#define APP_WIDTH 450
#define APP_HEIGHT 675


namespace s21{
///класс desktop - это класс для визуала самого приложения - оболочка
class desktop: public QWidget{
    public:
        desktop();

        void setMenuBar(); /// установка менюбар
        void keyPressEvent(QKeyEvent *event); /// функция считывания нажатия клавиши клавиатуры
        void setAppStyle(); /// утсановка размеров и стиля окна приложения

    private:
        controller *control;
    }; /// end class desktop

///класс display - это класс для визуала игровго дисплея 10х20
class display: public QGraphicsView{
public:
    display(QWidget *widget);

    void setMonitor(display *monitor, QVBoxLayout *layout, QWidget *monitorEdge); /// установка монитора
    // void startGif();
    void startPic();
};///end class display


///класс game_button - это класс для визуала всех кнопок
class game_button: public QGraphicsView{
public:
    game_button(QWidget *widget, controller *control);

    QPushButton * moveButtonStyle(QString symbol, bool isRotate=false);
    void positionButton(QGraphicsProxyWidget * left_widget, QGraphicsProxyWidget * right_widget,
                        QGraphicsProxyWidget * center_widget, QGraphicsProxyWidget * up_widget,
                        QGraphicsProxyWidget * down_widget, QGraphicsProxyWidget * rotate_widget,
                        QGraphicsProxyWidget * pause_widget, QGraphicsProxyWidget * mute_widget,
                        QGraphicsProxyWidget * on_off_widget);
    void workButton(QPushButton *left, QPushButton *right, QPushButton *up,
                    QPushButton *down, QPushButton *rotate, QPushButton *pause,
                    QPushButton *mute, QPushButton * on_off, controller *control);

    QPushButton * menuButtonStyle(bool on_off=false);
};///end class display

};/// end namespace s21

#endif // S21_DESKTOP_H
