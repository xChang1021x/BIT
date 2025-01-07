#include "videoplayerwidget.h"
#include "ui_videoplayerwidget.h"


VideoPlayerWidget::VideoPlayerWidget(QWidget *parent, QUrl current_path)
    : QWidget(parent)
    , ui(new Ui::VideoPlayerWidget)
{
    ui->setupUi(this);
    this->setLayout(ui->mainLayout);
    //组件样式设置
    ui->btnPlay->setFlat(true);
    ui->btnEnd->setFlat(true);
    ui->btnChoose->setFlat(true);
    ui->btnBack->setFlat(true);
    ui->btnForward->setFlat(true);
    ui->btnLoop->setFlat(true);
    ui->btnSpeed->setFlat(true);
    ui->textStartTime->setStyleSheet("background-color: rgb(255, 255, 255, 0)");
    ui->textEndTime->setStyleSheet("background-color: rgb(255, 255, 255, 0)");
    setAttribute(Qt::WA_TranslucentBackground,false);
    ui->videoView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->widgetSlideBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    currentVideo_path = current_path;
    isHide = false;
    mediaPlayer = new QMediaPlayer;
    speedTime = 0;
    mediaPlayer->setVolume(ui->sliderMusic->value());

    //信号与槽的连接
    connect(ui->btnChoose, SIGNAL(clicked()), this, SLOT(ChooseVideo()));
    connect(ui->btnPlay, SIGNAL(clicked()), this, SLOT(ChangeMediaPlayerState()));
    connect(ui->btnEnd, SIGNAL(clicked()), this, SLOT(CloseVideo()));
    connect(ui->playerSlider, SIGNAL(sliderMoved(int)), this, SLOT(SetVideoPosition(int)));
    connect(mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(RefreshMediaPlayer(qint64)));
    connect(mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(RefreshPlayerSlider(qint64)));

    //判断是否从资源管理器打开
    if (currentVideo_path != QUrl("")){
        mediaPlayer->setMedia(QMediaContent(currentVideo_path));
        mediaPlayer->setVideoOutput(ui->videoView);
        mediaPlayer->play();
    }
}

void VideoPlayerWidget::ShowHideSliderBar(){    //隐藏/显示播放功能栏
    if (isHide){
        ui->widgetSlideBar->show();
        // 遍历 QVBoxLayout 中的所有项目
        for (int i = 0; i < ui->PlayerSliderBar->count(); ++i) {
            QLayoutItem *item = ui->PlayerSliderBar->itemAt(i);
            // 检查项目是否是 QHBoxLayout
            QHBoxLayout *hboxLayout = qobject_cast<QHBoxLayout *>(item->layout());
            if (hboxLayout) {
                // 遍历 QHBoxLayout 中的所有小部件，并将其隐藏
                for (int j = 0; j < hboxLayout->count(); ++j) {
                    QWidget *widget = hboxLayout->itemAt(j)->widget();
                    if (widget) {
                        widget->show();
                    }
                }
            }
        }
        isHide = false;
    }
    else {
        ui->widgetSlideBar->hide();
        // 遍历 QVBoxLayout 中的所有项目
        for (int i = 0; i < ui->PlayerSliderBar->count(); ++i) {
            QLayoutItem *item = ui->PlayerSliderBar->itemAt(i);
            // 检查项目是否是 QHBoxLayout
            QHBoxLayout *hboxLayout = qobject_cast<QHBoxLayout *>(item->layout());
            if (hboxLayout) {
                // 遍历 QHBoxLayout 中的所有小部件，并将其隐藏
                for (int j = 0; j < hboxLayout->count(); ++j) {
                    QWidget *widget = hboxLayout->itemAt(j)->widget();
                    if (widget) {
                        widget->hide();
                    }
                }
            }
        }
        isHide = true;
    }
}

void VideoPlayerWidget::mousePressEvent(QMouseEvent *event){
    // 调用基类方法以确保事件正常传播
    QWidget::mousePressEvent(event);
    ShowHideSliderBar();
}

void VideoPlayerWidget::ChangeMediaPlayerState(){   //暂停或继续播放
    if (currentVideo_path.isEmpty()){
        return;
    }
    if (mediaPlayer->state() == QMediaPlayer::PlayingState){
        mediaPlayer->pause();
        ui->btnPlay->setIcon(QIcon(":/play(1).png"));
        ui->btnPlay->setIconSize(QSize(48, 48));
    }
    else if (mediaPlayer->state() == QMediaPlayer::PausedState){
        mediaPlayer->play();
        ui->btnPlay->setIcon(QIcon(":/pause.png"));
        ui->btnPlay->setIconSize(QSize(48, 48));
    }
}

void VideoPlayerWidget::ChooseVideo(){  //从本地文件挑选视频
    currentVideo_path = QFileDialog::getOpenFileUrl(NULL, "Choose a video", QUrl("../") , "*.mp4");
    if (currentVideo_path.isEmpty()){
        return;
    }
    mediaPlayer->setMedia(QMediaContent(currentVideo_path));
    mediaPlayer->setVideoOutput(ui->videoView);
    mediaPlayer->play();
    ShowHideSliderBar();
    ShowHideSliderBar();
}

void VideoPlayerWidget::CloseVideo(){   //关闭当前播放视频
    if (currentVideo_path.isEmpty()){
        return;
    }
    mediaPlayer->setMedia(QMediaContent());
    ui->label_3->show();
}

QString formatTime(qint64 milliseconds) {   //格式化时间为字符串
    int hours = (milliseconds / (1000 * 60 * 60)) % 24;
    int minutes = (milliseconds / (1000 * 60)) % 60;
    int seconds = (milliseconds / 1000) % 60;

    return QTime(hours, minutes, seconds).toString("hh:mm:ss");
}

void VideoPlayerWidget::RefreshMediaPlayer(qint64 duration){    //切换视频刷新功能栏信息
    ui->btnPlay->setIcon(QIcon(":/pause.png"));
    ui->btnPlay->setIconSize(QSize(48, 48));
    ui->playerSlider->setMaximum(duration);
    QString startTime = formatTime(mediaPlayer->position());
    QString endTime = formatTime(duration);
    ui->textStartTime->setText(startTime);
    ui->textEndTime->setText(endTime);
}

void VideoPlayerWidget::RefreshPlayerSlider(qint64 position){   //进度条与视频播放时间的同步
    ui->playerSlider->setValue(position);
    QString currentTime = formatTime(position);
    QString endTime = formatTime(mediaPlayer->duration());
    ui->textStartTime->setText(currentTime);
    ui->textEndTime->setText(endTime);
}

void VideoPlayerWidget::SetVideoPosition(int position){     //拖动进度条功能
    mediaPlayer->setPosition(position);
}

VideoPlayerWidget::~VideoPlayerWidget()
{
    delete ui;
}


void VideoPlayerWidget::on_sliderMusic_sliderMoved(int position){   //音量调节
    mediaPlayer->setVolume(position);
}

void VideoPlayerWidget::on_btnBack_clicked(){   //后退功能
    if (ui->playerSlider->value() < 10000){
        ui->playerSlider->setValue(0);
        mediaPlayer->setPosition(0);
    }
    else {
        int value = ui->playerSlider->value() - 10000;
        ui->playerSlider->setValue(value);
        mediaPlayer->setPosition(value);
    }
}


void VideoPlayerWidget::on_btnForward_clicked(){    //前进功能
    if (ui->playerSlider->value() > mediaPlayer->duration() - 11000){
        mediaPlayer->setPosition(mediaPlayer->duration());
        ui->playerSlider->setValue(mediaPlayer->duration());
    }
    else {
        int value = ui->playerSlider->value() + 10000;
        ui->playerSlider->setValue(value);
        mediaPlayer->setPosition(value);

    }
}

void VideoPlayerWidget::onMediaStatusChanged(QMediaPlayer::MediaStatus status){     //结束后重新播放
    if (status == QMediaPlayer::EndOfMedia) {
        mediaPlayer->setPosition(0);
        mediaPlayer->play();
    }
}

void VideoPlayerWidget::on_btnLoop_clicked(){   //循环播放功能
        if (isLoop) {
            ui->btnLoop->setFlat(true);
            ui->btnLoop->setStyleSheet("background-color: none;");
            // 取消循环播放模式
            disconnect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &VideoPlayerWidget::onMediaStatusChanged);
        } else {
            ui->btnLoop->setFlat(false);
            ui->btnLoop->setStyleSheet("background-color: rgb(205, 224, 255);");
            // 启用循环播放模式
            connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &VideoPlayerWidget::onMediaStatusChanged);
        }
        isLoop = !isLoop;
}


void VideoPlayerWidget::on_btnSpeed_clicked(){  //倍速功能
    mediaPlayer->setPosition(ui->playerSlider->value());

    switch (speedTime % 6) {
    case 0:
        speedTime++;
        mediaPlayer->setPlaybackRate(1.25);
        ui->btnSpeed->setIcon(QIcon(":/1.25倍速.png"));
        break;
    case 1:
        speedTime++;
        mediaPlayer->setPlaybackRate(1.5);
        ui->btnSpeed->setIcon(QIcon(":/1.5倍速.png"));
        break;
    case 2:
        speedTime++;
        mediaPlayer->setPlaybackRate(2);
        ui->btnSpeed->setIcon(QIcon(":/2倍速.png"));
        break;
    case 3:
        speedTime++;
        mediaPlayer->setPlaybackRate(3);
        ui->btnSpeed->setIcon(QIcon(":/3倍速.png"));
        break;
    case 4:
        speedTime++;
        mediaPlayer->setPlaybackRate(0.5);
        ui->btnSpeed->setIcon(QIcon(":/0.5倍速.png"));
        break;
    case 5:
        speedTime = 0;
        mediaPlayer->setPlaybackRate(1);
        ui->btnSpeed->setIcon(QIcon(":/1倍速.png"));
        break;
    }
}

void VideoPlayerWidget::on_pushButton_clicked(){    //返回主页面功能
    mediaPlayer->setMedia(QMediaContent());
    emit tell_close();
    deleteLater();
}

