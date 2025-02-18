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
        setFocus(); /// установка фокуса. без этой штуки не срабатывает считывание стрелок.

        /* подключение контроллера */
        control = new controller();
        control->sound_intro();

        /* изменили размер приложения и его фон */
        setAppStyle();

        /* устанока меню - справка - о программе */
        setMenuBar();

        /* Создаем слой для размещения кнопок и дисплея */
        QVBoxLayout *layout = new QVBoxLayout(this);

        /* установка дисплея */
        display *monitor = new display(this); /// сам монитор
        QWidget *monitorEdge = new QWidget(this); /// среая рамка вокруг монитора (чтобы красиво было)
        monitor->setMonitor(monitor, layout, monitorEdge);

        /* установка кнопок */
        game_button *GameButton = new game_button(this, control);
        layout->addWidget(GameButton, 0, Qt::AlignHCenter);

        setLayout(layout);/// Устанавливаем макет


        // monitor->startGif();
        // monitor->startPic();

        /* Запуск выбора игры */
        control->menuStartGame(5000); /// 5 секунд показывается стартовый экран, затем выбор игрый


    }

    void desktop::setAppStyle(){
        resize(APP_WIDTH, APP_HEIGHT);
        setWindowTitle("BrickGame v.2.0");
        setStyleSheet("border: transparent;"); /// Убрал рамки внутри приложения (у виджетов и сцен)

        /*установка фона приложения*/
        QPixmap backgroundImage(":/img/images/background.jpg");
        QPalette pal;
        pal.setBrush(QPalette::Window, backgroundImage);
        setPalette(pal);
    };

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
        QLabel * label = new QLabel("\n\t\t Привет-привет.\n"
                                   "\tСделано в муках и горьких мужских слезах на рукаве. \n"
                                   "\tЕсли кто-то сюда-таки залез, то молодец, это я пытался научиться делать меню через код.\t\n"
                                   "\tУдачи 🙈\t\n"
                                   "\n\tfrostdra@student.21-school.ru \n\n \t02.2025\n\n");
        connect(aboutAct, &QAction::triggered, this, [label]() { label->show(); });
    };

    void display::setMonitor(display *monitor, QVBoxLayout *layout, QWidget *monitorEdge){
        layout->addWidget(monitor, 0, Qt::AlignHCenter); /// размещение по центру виджета по горизонтали
        monitor->setStyleSheet("border-style: outset;"
                               "border-width: 2px;"
                               "border-color: black;");

        monitorEdge->setStyleSheet("background-color: grey;");
        monitorEdge->setFixedSize(DISPLAY_WIDTH + 100, DISPLAY_HEIGHT + 1.5 * PIXEL_HEIGHT);

        QVBoxLayout *monitorLayout = new QVBoxLayout(monitorEdge);
        monitorLayout->setAlignment(Qt::AlignCenter);
        monitorLayout->addWidget(monitor);
        layout->addWidget(monitorEdge, 0, Qt::AlignHCenter);

    };

    void desktop::keyPressEvent(QKeyEvent *Key){
        if (Key->key()==Qt::Key_M)
            control->sound_mute();
        if (Key->key()==Qt::Key_P)
            control->pause();
        if (Key->key()==Qt::Key_Q)
            control->quit();
        if (Key->key()==Qt::Key_Space)
            control->press_rotate();
        if (Key->key()==Qt::Key_Left)
            control->press_left();
        if (Key->key()==Qt::Key_Right)
            control->press_right();
        if (Key->key()==Qt::Key_Up)
            control->press_up();
        if (Key->key()==Qt::Key_Down)
            control->press_down();
    };

    display::display(QWidget *widget){
        QGraphicsScene *display =new QGraphicsScene(widget);
        setScene(display);
        // startGif();
        // startPic();

        /// устанавливаем цвет и размер этого виджета
        setBackgroundBrush(QBrush(Qt::black));
        setFixedSize(DISPLAY_WIDTH+8, DISPLAY_HEIGHT+8); /// 2 и 2 на рамку с каждой стороны + 4 на пробел - так симпотичнее (пропуск, чтобы дырка была короче между рамкой внешней и внутренней)

        display->addRect(-FIELD_WIDTH,0,FIELD_WIDTH,FIELD_HEIGHT, QPen(Qt::white)); /// само игровое поле
        display->addRect(0,0,DISPLAY_WIDTH-FIELD_WIDTH,FIELD_HEIGHT, QPen(Qt::white)); /// информационное поле (очки, уровень, скорость и т.п.

    };

    // void display::startGif(){
    //     QMovie *startGif=new QMovie(":/gif/gif/snake_tetris.gif");
    //     QLabel *this_label = new QLabel(this);
    //     this_label->setMovie(startGif);
    //     startGif->start();
    // };

    void display::startPic(){
        QPixmap StartImage(":/img/images/snake_pic.png");
        QLabel *this_label = new QLabel(this);
        this_label->setAlignment(Qt::AlignHCenter);
        this_label->setPixmap(StartImage);
    };



    game_button::game_button(QWidget *widget, controller *control) {
        /// создаём сцену
        QGraphicsScene *scene = new QGraphicsScene(widget);
        setScene(scene);
        /// устанавливаем цвет и размер этого виджета (сцены)
        setBackgroundBrush(QBrush(QColor(252, 249, 233)));
        setFixedSize(APP_WIDTH, APP_HEIGHT - DISPLAY_HEIGHT - 30);


        /// создаём кнопки
        QPushButton *left = moveButtonStyle("←");
        QGraphicsProxyWidget * left_widget = scene->addWidget(left);
        QPushButton *right = moveButtonStyle("→");
        QGraphicsProxyWidget * right_widget = scene->addWidget(right);
        QPushButton *up = moveButtonStyle("↑");
        QGraphicsProxyWidget * up_widget = scene->addWidget(up);
        QPushButton *down = moveButtonStyle("↓");
        QGraphicsProxyWidget * down_widget = scene->addWidget(down);
        QPushButton *center = moveButtonStyle(" ");
        QGraphicsProxyWidget * center_widget = scene->addWidget(center);
        QPushButton *rotate=moveButtonStyle("rotate\n(space)", true);
        QGraphicsProxyWidget * rotate_widget = scene->addWidget(rotate);
        QPushButton *pause = menuButtonStyle();
        QGraphicsProxyWidget * pause_widget = scene->addWidget(pause);
        QPushButton *mute = menuButtonStyle();
        QGraphicsProxyWidget * mute_widget = scene->addWidget(mute);
        QPushButton *on_off = menuButtonStyle(true);
        QGraphicsProxyWidget * on_off_widget = scene->addWidget(on_off);



        /// Перемещаем кнопки внутри сцены
        positionButton(left_widget,right_widget, center_widget, up_widget, down_widget, rotate_widget, pause_widget, mute_widget, on_off_widget);


        /// выполнение при нажатии
        workButton(left, right,  up, down, rotate, pause, mute, on_off, control);

        /// украшательства
        /// логотип
        QPixmap pix(":/img/images/logo_s21.jpg");
        QLabel *logo_s21 = new QLabel();
        logo_s21->setPixmap(pix);
        QGraphicsProxyWidget * logo_widget = scene->addWidget(logo_s21);
        logo_widget->setPos(130, 60);
        logo_widget->setRotation(-45);

    };

    QPushButton * game_button::moveButtonStyle(QString symbol, bool isRotate){
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


    QPushButton * game_button::menuButtonStyle(bool on_off){
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


        QLabel * name_pause = new QLabel("pause\n   (P)");
        name_pause->setStyleSheet("background-color: transparent;"
                                  "color: black;"
                                  "font-weight: bold;");
        QGraphicsProxyWidget * name_pause_widge = scene()->addWidget(name_pause);
        name_pause_widge->setPos(COORD_X_START - 8, COORD_Y_START + 30);

        QLabel * name_mute = new QLabel("mute\n (M)");
        name_mute->setStyleSheet("background-color: transparent;"
                                  "color: black;"
                                  "font-weight: bold;");
        QGraphicsProxyWidget * name_mute_widge = scene()->addWidget(name_mute);
        name_mute_widge->setPos(COORD_X_START + 60 - 6, COORD_Y_START + 30);

        QLabel * name_on_off = new QLabel("quit\n (Q)");
        name_on_off->setStyleSheet("background-color: transparent;"
                                  "color: black;"
                                  "font-weight: bold;");
        QGraphicsProxyWidget * name_on_off_widge = scene()->addWidget(name_on_off);
        name_on_off_widge->setPos(COORD_X_START + 60 + 60 - 3, COORD_Y_START + 30);


    };


    void game_button::workButton(QPushButton *left, QPushButton *right, QPushButton *up, QPushButton *down,
                                 QPushButton *rotate, QPushButton *pause, QPushButton *mute, QPushButton * on_off, controller *control){

        connect(left, &QPushButton::clicked, control, &controller::press_left);
        connect(right, &QPushButton::clicked, control, &controller::press_right);
        connect(up, &QPushButton::clicked, control, &controller::press_up);
        connect(down, &QPushButton::clicked, control, &controller::press_down);
        connect(rotate, &QPushButton::clicked, control, &controller::press_rotate);

        connect(pause, &QPushButton::clicked, control, &controller::pause);
        connect(mute, &QPushButton::clicked, control, &controller::sound_mute);
        connect(on_off, &QPushButton::clicked, control, &controller::quit);
    };





}; /// end namespace s21
