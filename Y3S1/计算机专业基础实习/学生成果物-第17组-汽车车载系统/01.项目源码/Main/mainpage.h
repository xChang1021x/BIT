#ifndef MAINPAGE_H
#define MAINPAGE_H

#include "radio.h"
#include "videoplayerwidget.h"
#include "weather.h"
#include "websitewidget.h"
#include "cargps.h"
#include "image.h"
#include "bg.h"
#include "music.h"
#include "wechat.h"

#include <QWidget>
#include <ui_weather.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainPage; }
QT_END_NAMESPACE

class MainPage : public QWidget
{
    Q_OBJECT

public:
    MainPage(QWidget *parent = nullptr);
    ~MainPage();
    QParallelAnimationGroup *allAnimation;

private slots:
    void on_browser_clicked();
    void on_weather_clicked();
    void updateTime();
    void on_radio_clicked();

    void on_video_clicked();

    void on_map_clicked();

    void on_folder_clicked();

    void on_picture_clicked();
    void on_close_window();

    void on_music_clicked();

    void on_chat_clicked();

private:
    Ui::MainPage *ui;
    WebsiteWidget *websiteWidget;
    Weather *weather;
    Radio *radio;
    VideoPlayerWidget *videoPlayerWidget;
    CarGPS *cargps;
    Image *image;
    Music *music;
    Bg *bg;
    WeChat *chat;

};
#endif // MAINPAGE_H
