#ifndef MUSIC_H
#define MUSIC_H

#include "ui_music.h"
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWebEngineView>
//#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Music : public QWidget
{
    Q_OBJECT

public:
    Music(QWidget *parent = nullptr, QUrl current_path = QUrl(""));
    ~Music();
    bool isCurrentFavourite;

signals:
    void tell_close();

public slots:
    void updateSongName();

private slots:
    void on_btnAdd_clicked();
//    void updatePlaylistIcons();
//    void on_btnFavourites_clicked();
//    void saveFavourites();
//    void loadFavourites();
    void on_btnPause_clicked();
    void on_btnPrevious_clicked();
    void on_btnNext_clicked();
    void on_btnPlaylist_clicked();
//    void onSongItemClicked(QListWidgetItem *item);
    void on_btnPlaybackMode_clicked();
    void on_btnDelete_clicked();
    void deleteSong();
    void onPlayerPositionChanged(qint64);
    void onPlayerDurationChanged(qint64);
    void on_musicSlider_sliderReleased();
    void on_volumeSlider_sliderReleased();
    QString formatTime(qint64 time);

    void on_btnBack_clicked();

    void on_btnFavourites_clicked();

private:
    Ui::Music *ui;
    QMediaPlayer *mediaPlayer;
    QMediaPlaylist *playlist;
    QStringList files;
//    QListWidget songListWidget;
//    QStringList favouriteSongs;
    int currentModeIndex;
//    QSet<int> favouriteSongs;
};
#endif // MUSIC_H
