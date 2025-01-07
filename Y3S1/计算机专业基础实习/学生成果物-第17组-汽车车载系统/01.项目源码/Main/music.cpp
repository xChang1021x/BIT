#include "music.h"
#include "ui_music.h"
#include <QDir>
#include <QButtonGroup>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QPropertyAnimation>

Music::Music(QWidget *parent, QUrl current_path)
    : QWidget(parent)
    , ui(new Ui::Music)
    ,currentModeIndex(0)
{
    ui->setupUi(this);

    // 初始化playlist
    mediaPlayer = new QMediaPlayer();
    playlist = new QMediaPlaylist();  // 初始化播放列表
    mediaPlayer->setPlaylist(playlist);   // 将播放器与播放列表关联
    ui->btnPause->setFlat(true);
    ui->btnNext->setFlat(true);
    ui->btnAdd->setFlat(true);
    ui->btnBack->setFlat(true);
    ui->btnDelete->setFlat(true);
    ui->btnFavourites->setFlat(true);
    ui->btnPlaybackMode->setFlat(true);
    ui->btnPlaylist->setFlat(true);
    ui->btnPrevious->setFlat(true);

    //folder
    QString foldername = "/home/chang/CarSystemModule/Main/Joker Xue";
    QDir directory(foldername);
    files = directory.entryList(QDir::Files);
    foreach(QString filename, files){
        qDebug() << filename;
    }
    qDebug() << "Files in directory: " << files;

    // 获取文件夹中所有的音频文件
    QStringList filters;
    filters << "*.mp3" << "*.m4a";
    directory.setNameFilters(filters);
    files = directory.entryList(QDir::Files);

    if (current_path != QUrl("")){
        playlist->addMedia(current_path);
    }


    // 将所有音频文件添加到播放列表中
    foreach(const QString &filename, files) {
        QString filePath = directory.absoluteFilePath(filename);
        playlist->addMedia(QUrl::fromLocalFile(filePath));
        qDebug() << "Added to playlist: " << filePath;
    }


    // 在构造函数中加载 HTML 页面
//    QString htmlFilePath = "/home/chang/CarSystemModule/MusicPlayer/index(1).html";
//    ui->lyrics->setUrl(QUrl::fromLocalFile(htmlFilePath));

    // 设置默认播放模式为顺序播放
    playlist->setPlaybackMode(QMediaPlaylist::Sequential);
    currentModeIndex = 0;

    //视频长度改变，打印出来
    connect(mediaPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(onPlayerDurationChanged(qint64)));
    //进度条位置改变，打印出来
    connect(mediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(onPlayerPositionChanged(qint64)));
    // 连接当前索引变化的信号
    connect(playlist, &QMediaPlaylist::currentIndexChanged, this, &Music::updateSongName);
    // 连接进度条的槽函数
    connect(ui->progressBar, &QSlider::sliderReleased, this, &Music::on_musicSlider_sliderReleased);
    // 连接音量条的槽函数
    connect(ui->volumeBar, &QSlider::sliderReleased, this, &Music::on_volumeSlider_sliderReleased);

//    connect(ui->btnPlaybackMode, &QPushButton::clicked, this, &Music::on_btnPlaybackMode_clicked);


    // 设置默认音量
    int defaultVolume = 50;
    ui->volumeBar->setValue(defaultVolume);
    mediaPlayer->setVolume(defaultVolume);

    playlist->setCurrentIndex(0);
    mediaPlayer->play();

//    loadFavourites(); // 加载收藏数据
//    updatePlaylistIcons(); // 更新 UI 上的收藏状态
}

Music::~Music()
{
//    saveFavourites(); // 保存收藏数据
    delete ui;
}

void Music::updateSongName()
{
    // 获取当前播放的媒体项
    int currentIndex = playlist->currentIndex();
    if (currentIndex != -1) {
        // 获取当前歌曲的文件名
        QString currentSong = QFileInfo(playlist->media(currentIndex).canonicalUrl().toLocalFile()).fileName();
        // 更新 songName 文本框
        ui->songName->setText(currentSong);
    }
}

void Music::on_btnAdd_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "Add Songs", "", "Audio Files (*.mp3 *.m4a)");
    foreach(const QString &fileName, fileNames) {
        playlist->addMedia(QUrl::fromLocalFile(fileName));
        files.append(fileName); // 将文件添加到文件列表中
        qDebug() << "Added: " << fileName;
    }
}

void Music::on_btnPause_clicked()
{
    if(mediaPlayer->state() == QMediaPlayer::PlayingState) {
        mediaPlayer->pause();
        ui->btnPause->setIcon(QIcon(":/Pause.png"));
    }
    else if(mediaPlayer->state() == QMediaPlayer::PausedState) {
        mediaPlayer->play();
        ui->btnPause->setIcon(QIcon(":/Play.png"));
    }
}

void Music::on_btnPrevious_clicked()
{
    int currentIndex = playlist->currentIndex();
    ui->btnPause->setIcon(QIcon(":/Play.png"));
    if (playlist->playbackMode() != QMediaPlaylist::Sequential) {
        playlist->previous();
    } else {
        if(currentIndex) {
            playlist->previous();
        }
        else {
            playlist->setCurrentIndex(playlist->mediaCount() - 1);    // 回到最后一首歌
        }
    }
    mediaPlayer->play();
    isCurrentFavourite = false;
    ui->btnFavourites->setIcon(QIcon(":/Favourites.png"));  // 显示未收藏图标
}

void Music::on_btnNext_clicked()
{
    isCurrentFavourite = false;
    playlist->next();
    mediaPlayer->play();
    ui->btnPause->setIcon(QIcon(":/Play.png"));
    ui->btnFavourites->setIcon(QIcon(":/Favourites.png"));  // 显示未收藏图标
}

void Music::on_btnPlaylist_clicked()
{
    bool Isok;
    QStringList songNames;
    foreach(const QString &file, files) {
        songNames.append(QFileInfo(file).fileName());
    }

    QString selectedSong = QInputDialog::getItem(this, "Select Song", "Playlist:", songNames, 0, false, &Isok);
    if (Isok && !selectedSong.isEmpty()) {
        int index = songNames.indexOf(selectedSong);
        playlist->setCurrentIndex(index);
        qDebug()<<index;
        qDebug()<<songNames[index];
        mediaPlayer->play();
    }
}

//void Music::onSongItemClicked(QListWidgetItem *item)
//{
//    int index = songListWidget->row(item); // 获取点击项的索引
//    playlist->setCurrentIndex(index);
//    mediaPlayer->play(); // 播放点击的歌曲
//}

void Music::on_btnPlaybackMode_clicked()
{
    // 定义播放模式的选项
    QStringList modes;
    modes << "Sequential" << "Single Loop" << "Random";

    // 确定当前播放模式的默认选项
    QString defaultMode;
    switch (currentModeIndex) {
    case 2:
        defaultMode = "Sequential";
        currentModeIndex = 0;
        break;
    case 0:
        defaultMode = "Single Loop";
        currentModeIndex++;
        break;
    case 1:
        defaultMode = "Random";
        currentModeIndex++;
        break;
    }

    // 如果用户做出了选择，设置相应的播放模式
    if (defaultMode == "Sequential") {
        playlist->setPlaybackMode(QMediaPlaylist::Sequential);
        ui->btnPlaybackMode->setIcon(QIcon(":/Sequential.png"));
        qDebug() << "Playback Mode set to Sequential";
    } else if (defaultMode == "Single Loop") {
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        ui->btnPlaybackMode->setIcon(QIcon(":/Single Loop.png"));
        qDebug() << "Playback Mode set to Single Loop";
    } else if (defaultMode == "Random") {
        playlist->setPlaybackMode(QMediaPlaylist::Random);
        ui->btnPlaybackMode->setIcon(QIcon(":/Random.png"));
        qDebug() << "Playback Mode set to Random";
    }
}

void Music::on_btnDelete_clicked() {
    // 弹出确认对话框
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete Song", "Are you sure want to delete this song？",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        deleteSong();  // 如果用户点击“是”，调用删除函数
    }
}

// 删除歌曲的实现函数
void Music::deleteSong() {
    int currentIndex = playlist->currentIndex(); // 获取当前播放的歌曲索引

    if (currentIndex != -1) {
        playlist->removeMedia(currentIndex);  // 从播放列表中删除这首歌
        files.removeAt(currentIndex);         // 从文件列表中删除相应的文件

        // 如果列表中还有歌曲，更新UI并继续播放
        if (!playlist->isEmpty()) {
            mediaPlayer->play();
            updateSongName();  // 更新歌曲名显示
        } else {
            mediaPlayer->stop();
            ui->songName->clear();  // 清空歌曲名显示
//            ui->lyricsMusic->setText(""); // 清空歌词显示
        }
    }
}

// 位置变化槽函数
void Music::onPlayerPositionChanged(qint64 position)
{
    ui->progressBar->setValue(position);  // 更新进度条的当前位置
    ui->currentTime->setText(formatTime(position)); // 更新当前播放时间显示
}

// 持续时间变化槽函数
void Music::onPlayerDurationChanged(qint64 duration)
{
    ui->progressBar->setMaximum(duration);  // 更新进度条的最大值（总时长）
    ui->totalTime->setText(formatTime(duration)); // 更新总时长显示
}

// 用户拖动进度条时调用此槽函数
void Music::on_musicSlider_sliderReleased()
{
    mediaPlayer->setPosition(ui->progressBar->value());
}

// 用户拖动音量条时调用此槽函数
void Music::on_volumeSlider_sliderReleased()
{
    mediaPlayer->setVolume(ui->volumeBar->value());
}

//时间格式化函数
QString Music::formatTime(qint64 time) {
    int seconds = (time / 1000) % 60;
    int minutes = (time / 60000) % 60;
    return QString::asprintf("%02d:%02d", minutes, seconds);
}


void Music::on_btnBack_clicked()
{
    mediaPlayer->stop();
    deleteLater();
    emit tell_close();
}


void Music::on_btnFavourites_clicked()
{
    isCurrentFavourite = !isCurrentFavourite;
    if (isCurrentFavourite) {
        ui->btnFavourites->setIcon(QIcon(":/Favourited.png"));  // 显示已收藏图标
    } else {
        ui->btnFavourites->setIcon(QIcon(":/Favourites.png"));  // 显示未收藏图标
    }
}

