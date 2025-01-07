#include "bg.h"
#include "mainpage.h"
#include "ui_mainpage.h"
#include "website.h"
#include "websitewidget.h"

#include <QDebug>
#include <QTimer>

MainPage::MainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainPage)
{
    this->setFixedSize(800,600);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainPage::updateTime);
    timer->start(1000);
    ui->setupUi(this);
    QDateTime datetime = QDateTime::currentDateTime();
    QString now = datetime.toString("yyyy年MM月dd日");
    allAnimation = new QParallelAnimationGroup;
    QPropertyAnimation *browserAnimation = new QPropertyAnimation(ui->browser, "geometry");
    browserAnimation->setDuration(1000);
    browserAnimation->setStartValue(QRect(348, 255, 0, 0));
    browserAnimation->setEndValue(QRect(348, 13, 0, 0));
    browserAnimation->setEasingCurve(QEasingCurve::OutBounce);  // 缓和曲线风格
    allAnimation->addAnimation(browserAnimation);
    QPropertyAnimation *musicAnimation = new QPropertyAnimation(ui->music, "geometry");
    musicAnimation->setDuration(1000);
    musicAnimation->setStartValue(QRect(348, 255, 0, 0));
    musicAnimation->setEndValue(QRect(197, 131, 0, 0));
    musicAnimation->setEasingCurve(QEasingCurve::OutBounce);  // 缓和曲线风格
    allAnimation->addAnimation(musicAnimation);
    QPropertyAnimation *mapAnimation = new QPropertyAnimation(ui->map, "geometry");
    mapAnimation->setDuration(1000);
    mapAnimation->setStartValue(QRect(348, 255, 0, 0));
    mapAnimation->setEndValue(QRect(499, 131, 0, 0));
    mapAnimation->setEasingCurve(QEasingCurve::OutBounce);  // 缓和曲线风格
    allAnimation->addAnimation(mapAnimation);
    QPropertyAnimation *radioAnimation = new QPropertyAnimation(ui->radio, "geometry");
    radioAnimation->setDuration(1000);
    radioAnimation->setStartValue(QRect(348, 255, 0, 0));
    radioAnimation->setEndValue(QRect(46, 249, 0, 0));
    radioAnimation->setEasingCurve(QEasingCurve::OutBounce);  // 缓和曲线风格
    allAnimation->addAnimation(radioAnimation);
    QPropertyAnimation *chatAnimation = new QPropertyAnimation(ui->chat, "geometry");
    chatAnimation->setDuration(1000);
    chatAnimation->setStartValue(QRect(348, 255, 0, 0));
    chatAnimation->setEndValue(QRect(650, 249, 0, 0));
    chatAnimation->setEasingCurve(QEasingCurve::OutBounce);  // 缓和曲线风格
    allAnimation->addAnimation(chatAnimation);
    QPropertyAnimation *weatherAnimation = new QPropertyAnimation(ui->weather, "geometry");
    weatherAnimation->setDuration(1000);
    weatherAnimation->setStartValue(QRect(348, 255, 0, 0));
    weatherAnimation->setEndValue(QRect(197, 367, 0, 0));
    weatherAnimation->setEasingCurve(QEasingCurve::OutBounce);  // 缓和曲线风格
    allAnimation->addAnimation(weatherAnimation);
    QPropertyAnimation *videoAnimation = new QPropertyAnimation(ui->video, "geometry");
    videoAnimation->setDuration(1000);
    videoAnimation->setStartValue(QRect(348, 255, 0, 0));
    videoAnimation->setEndValue(QRect(499, 367, 0, 0));
    videoAnimation->setEasingCurve(QEasingCurve::OutBounce);  // 缓和曲线风格
    allAnimation->addAnimation(videoAnimation);
    QPropertyAnimation *pictureAnimation = new QPropertyAnimation(ui->picture, "geometry");
    pictureAnimation->setDuration(1000);
    pictureAnimation->setStartValue(QRect(348, 255, 0, 0));
    pictureAnimation->setEndValue(QRect(348, 485, 0, 0));
    pictureAnimation->setEasingCurve(QEasingCurve::OutBounce);  // 缓和曲线风格
    allAnimation->addAnimation(pictureAnimation);
    allAnimation->start();
    ui->date->setText(now);


}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::on_browser_clicked()
{
    websiteWidget = new WebsiteWidget(this);
    websiteWidget->show();
    connect(websiteWidget, &WebsiteWidget::tell_close, this, &MainPage::on_close_window);
}


void MainPage::on_weather_clicked()
{
    weather = new Weather(this);
    weather->show();
    connect(weather, &Weather::tell_close, this, &MainPage::on_close_window);
}


void MainPage::on_radio_clicked()
{
    radio = new Radio(this);
    radio->show();
    connect(radio, &Radio::tell_close, this, &MainPage::on_close_window);
}

void MainPage::updateTime() {
    QDateTime datetime = QDateTime::currentDateTime();
    QString now2 = datetime.toString("HH时mm分ss秒");
    ui->time->setText(now2);
}


void MainPage::on_video_clicked()
{
    videoPlayerWidget = new VideoPlayerWidget(this);
    videoPlayerWidget->show();
    connect(videoPlayerWidget, &VideoPlayerWidget::tell_close, this, &MainPage::on_close_window);
}


void MainPage::on_map_clicked()
{
    cargps = new CarGPS(this);
    cargps->show();
    connect(cargps, &CarGPS::tell_close, this, &MainPage::on_close_window);
}

void MainPage::on_folder_clicked()
{
    QUrl current_path = QFileDialog::getOpenFileUrl(NULL, "File Manager", QUrl("../"));
    if (current_path.isEmpty()){
        return;
    }
    QString str = current_path.toString().section(".", -1, -1);

    if (str == "jpg" || str == "png" || str == "jpeg"){
        bg = new Bg(this, 1);
        bg->show();
        connect(bg, &Bg::tell_close, this, &MainPage::on_close_window);
    }
    else if (str == "mp4" || str == "mov" || str == "flv" || str == "wmv"){
        videoPlayerWidget = new VideoPlayerWidget(this, current_path);
        videoPlayerWidget->show();
        connect(videoPlayerWidget, &VideoPlayerWidget::tell_close, this, &MainPage::on_close_window);

    }
    else if (str == "mp3" || str == "flac" || str == "wav" || str == "m4a"){
        music = new Music(this, current_path);
        music->show();
        connect(music, &Music::tell_close, this, &MainPage::on_close_window);
    }
    else {
        qDebug() << "Not Supported";
    }
}


void MainPage::on_picture_clicked()
{
//    QWidget *widget = new QWidget(this);
//    widget->setStyleSheet("background-color: #FFFFFF;");
//    widget->show();
    bg = new Bg(this, 1);
    bg->show();
    connect(bg, &Bg::tell_close, this, &MainPage::on_close_window);
//    image = new Image(this);
//    image->show();
}

void MainPage::on_close_window() {
    allAnimation->start();
}


void MainPage::on_music_clicked()
{
    music = new Music(this);
    music->show();
    connect(music, &Music::tell_close, this, &MainPage::on_close_window);
}

void MainPage::on_chat_clicked()
{
//    chat = new WeChat(this);
//    chat->show();
    bg = new Bg(this, 2);
    bg->show();
    connect(bg, &Bg::tell_close, this, &MainPage::on_close_window);
}

