#include "s21_desktop.h"

///координаты кнопок
#define H_BUTTON 30
#define W_BUTTON 30
#define COORD_X_CENTER -180 /// для позиционирования стрелок
#define COORD_Y_CENTER 20

#define ROTETE_DIAMETR 80
#define COORD_X_ROTATE 80 /// для позиционирования кнопки поворота
#define COORD_Y_ROTATE -100

#define RADIUS 20
#define COORD_X_START -210 /// для позиционирования паузы, мьюта и он-оффа
#define COORD_Y_START -130

namespace s21{

    desktop::desktop() {
        /* изменили размер приложения */
        resize(APP_WIDTH, APP_HEIGHT);
        setWindowTitle("BrickGame v.2.0");
        setStyleSheet("border: transparent;"); /// Убрал рамки внутри приложения (у виджетов и сцен)


        /*установка фона приложения*/
        QPixmap backgroundImage(":/img/images/background.jpg");
        QPalette pal;
        pal.setBrush(QPalette::Window, backgroundImage);
        setPalette(pal);

        /* устанока меню - справка - о программе */
        setMenuBar();

        /* Создаем слой для размещения кнопок и дисплея */
        QVBoxLayout *layout = new QVBoxLayout(this);

        /* установка дисплея */
        display *monitor = new display(this);
        layout->addWidget(monitor, 0, Qt::AlignHCenter); /// размещение по центру виджета по горизонтали

        /* установка кнопок */
        game_button *GameButton = new game_button(this);
        layout->addWidget(GameButton, 0, Qt::AlignHCenter);

        setLayout(layout);/// Устанавливаем макет
    }

    void desktop::setMenuBar(){
        /*Меню построено так:
         1. создали менюБар
         2. создади справка
         3. созади о программе
         4. настроили что елается при клике на о программе*/
        QMenuBar *menuBar = new QMenuBar(this);
        QMenu *helpMenu = new QMenu(tr("Справка"), this);

        QAction *aboutAct = new QAction(tr("О программе"), this);
        helpMenu->addAction(aboutAct);
        menuBar->addMenu(helpMenu);

        /// тестовка для "О программе"
        QLabel * label = new QLabel("\n\tСделано в муках и горьких мужских слезах на рукаве. \n"
                                   "\tЕсли кто-то сюда-таки залез, то молодец, это я пытался научиться делать меню через код.\t\n"
                                   "\n\tfrostdra@student.21-school.ru \n\n \t02.2025\n\n");
        connect(aboutAct, &QAction::triggered, this, [label]() { label->show(); });
    };


    display::display(QWidget *widget){
        QGraphicsScene *display =new QGraphicsScene(widget);
        setScene(display);

        /// устанавливаем цвет и размер этого виджета
        setBackgroundBrush(QBrush(Qt::darkGray));
        setFixedSize(DISPLAY_WIDTH+100, DISPLAY_HEIGHT+30);

        /// добавляем прямоугольник (экран GameBoy) внутри виджета
        display->addRect(95, 25, DISPLAY_WIDTH, DISPLAY_HEIGHT, QPen(Qt::black), QBrush(Qt::black));

    };


    game_button::game_button(QWidget *widget) {
        /// создаём сцену
        QGraphicsScene *scene = new QGraphicsScene(widget);
        setScene(scene);
        /// устанавливаем цвет и размер этого виджета (сцены)
        setBackgroundBrush(QBrush(QColor(252, 249, 233)));
        setFixedSize(APP_WIDTH, APP_HEIGHT - DISPLAY_HEIGHT - 30);


        /// создаём кнопки
        QPushButton *left = moveButton("←");
        QGraphicsProxyWidget * left_widget = scene->addWidget(left);
        QPushButton *right = moveButton("→");
        QGraphicsProxyWidget * right_widget = scene->addWidget(right);
        QPushButton *up = moveButton("↑");
        QGraphicsProxyWidget * up_widget = scene->addWidget(up);
        QPushButton *down = moveButton("↓");
        QGraphicsProxyWidget * down_widget = scene->addWidget(down);
        QPushButton *center = moveButton(" ");
        QGraphicsProxyWidget * center_widget = scene->addWidget(center);
        QPushButton *rotate=moveButton("rotate", true);
        QGraphicsProxyWidget * rotate_widget = scene->addWidget(rotate);
        QPushButton *pause = menuButton();
        QGraphicsProxyWidget * pause_widget = scene->addWidget(pause);
        QPushButton *mute = menuButton();
        QGraphicsProxyWidget * mute_widget = scene->addWidget(mute);
        QPushButton *on_off = menuButton(true);
        QGraphicsProxyWidget * on_off_widget = scene->addWidget(on_off);



        /// Перемещаем кнопки внутри сцены
        positionButton(left_widget,right_widget, center_widget, up_widget, down_widget, rotate_widget, pause_widget,mute_widget, on_off_widget);


        /// выполнение при нажатии
        workButton(left, right,  up, down, rotate, widget, pause, mute, on_off);

        /// украшательства
        /// логотип
        QPixmap pix(":/img/images/logo_s21.jpg");
        QLabel *logo_s21 = new QLabel();
        logo_s21->setPixmap(pix);
        QGraphicsProxyWidget * logo_widget = scene->addWidget(logo_s21);
        logo_widget->setPos(130, 60);
        logo_widget->setRotation(-45);

    };

    QPushButton * game_button::moveButton(QString symbol, bool isRotate){
        QPushButton *button = new QPushButton(symbol);
        if (isRotate)
        {
            button->setFixedSize(ROTETE_DIAMETR, ROTETE_DIAMETR);
            button->setStyleSheet(
                "background-color: transparent;"
                "border-radius: 40px;"  // Радиус = половина размера, делает кнопку круглой
                "border: 10px solid darkGrey;"
                "color: black;"
                "font-weight: bold;"
            );
        }
        else
        {
            button->resize(H_BUTTON,W_BUTTON);
            button->setStyleSheet("background-color: black;"
                                "border: 1px solid black;"
                                "border-radius: 8px;"
                                "border-color: gray;"
                                "border-style: outset;");
            };
        return button;
    };


    QPushButton * game_button::menuButton(bool on_off){
        QPushButton *button = new QPushButton();
        button->setFixedSize(RADIUS, RADIUS);
        if (on_off)
        {
            button->setStyleSheet(
                "border-radius: 10px;"
                "background-color: transparent;"
                "border: 10px solid red;");
        }
        else
        {
            button->setStyleSheet(
                "border-radius: 10px;"
                "background-color: transparent;"
                "border: 10px solid black;");
        }
        return button;
    };


    void game_button::positionButton(QGraphicsProxyWidget * left_widget,
                                         QGraphicsProxyWidget * right_widget,
                                         QGraphicsProxyWidget * center_widget,
                                         QGraphicsProxyWidget * up_widget,
                                         QGraphicsProxyWidget * down_widget,
                                         QGraphicsProxyWidget * rotate_widget,
                                         QGraphicsProxyWidget * pause_widget,
                                         QGraphicsProxyWidget * mute_widget,
                                         QGraphicsProxyWidget * on_off_widget){
        left_widget->setPos(COORD_X_CENTER, COORD_Y_CENTER);
        center_widget->setPos(COORD_X_CENTER+W_BUTTON, COORD_Y_CENTER);
        right_widget->setPos(COORD_X_CENTER+W_BUTTON+W_BUTTON, COORD_Y_CENTER);
        up_widget->setPos(COORD_X_CENTER+W_BUTTON, COORD_Y_CENTER-H_BUTTON);
        down_widget->setPos(COORD_X_CENTER+W_BUTTON, COORD_Y_CENTER+H_BUTTON);
        rotate_widget->setPos(COORD_X_ROTATE, COORD_Y_ROTATE);

        pause_widget->setPos(COORD_X_START, COORD_Y_START);
        mute_widget->setPos(COORD_X_START+60, COORD_Y_START);
        on_off_widget->setPos(COORD_X_START+60+60, COORD_Y_START);


        QLabel * name_pause = new QLabel("pause");
        name_pause->setStyleSheet("background-color: transparent;"
                                  "color: black;"
                                  "font-weight: bold;");
        QGraphicsProxyWidget * name_pause_widge = scene()->addWidget(name_pause);
        name_pause_widge->setPos(COORD_X_START - 4, COORD_Y_START + 30);

        QLabel * name_mute = new QLabel("mute");
        name_mute->setStyleSheet("background-color: transparent;"
                                  "color: black;"
                                  "font-weight: bold;");
        QGraphicsProxyWidget * name_mute_widge = scene()->addWidget(name_mute);
        name_mute_widge->setPos(COORD_X_START + 60 - 2, COORD_Y_START + 30);

        QLabel * name_on_off = new QLabel("on_off");
        name_on_off->setStyleSheet("background-color: transparent;"
                                  "color: black;"
                                  "font-weight: bold;");
        QGraphicsProxyWidget * name_on_off_widge = scene()->addWidget(name_on_off);
        name_on_off_widge->setPos(COORD_X_START + 60 + 60 - 3, COORD_Y_START + 30);


    };


    void game_button::workButton(QPushButton *left, QPushButton *right, QPushButton *up, QPushButton *down, QPushButton *rotate,
                                     QWidget * widget, QPushButton *pause, QPushButton *mute, QPushButton * on_off){
        QLabel * label_left = new QLabel("LEFT!!!!");
        QLabel * label_right = new QLabel("RIGHT!!!!");
        QLabel * label_up = new QLabel("UP!!!!");
        QLabel * label_down = new QLabel("DOWN!!!!");
        QLabel * label_rotate = new QLabel("ROTATE!!!!");
        QLabel * label_pause = new QLabel("pause");
        QLabel * label_mute = new QLabel("mute");
        QLabel * label_on_off = new QLabel("on_off");


        connect(left, &QPushButton::clicked, widget, [label_left]() { label_left->show(); });
        connect(right, &QPushButton::clicked, widget, [label_right]() { label_right->show(); });
        connect(up, &QPushButton::clicked, widget, [label_up]() { label_up->show(); });
        connect(down, &QPushButton::clicked, widget, [label_down]() { label_down->show(); });
        connect(rotate, &QPushButton::clicked, widget, [label_rotate]() { label_rotate->show(); });

        connect(pause, &QPushButton::clicked, widget, [label_pause]() { label_pause->show(); });
        connect(mute, &QPushButton::clicked, widget, [label_mute]() { label_mute->show(); });
        connect(on_off, &QPushButton::clicked, widget, [label_on_off]() { label_on_off->show(); });
    };





}; /// end namespace s21
