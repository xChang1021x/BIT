#ifndef VIDEOPLAYERWIDGET_H
#define VIDEOPLAYERWIDGET_H

#include <QWidget>
#include <QObject>
#include <QTime>
#include <QtMultimedia>
#include <QVideoWidget>
#include <QSlider>
#include <QPushButton>
#include <QTextBrowser>
#include <QFileDialog>
#include <QFile>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QVideoWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class VideoPlayerWidget; }
QT_END_NAMESPACE

class VideoPlayerWidget : public QWidget
{
    Q_OBJECT

public:
    VideoPlayerWidget(QWidget *parent = nullptr, QUrl current_path = QUrl(""));
    ~VideoPlayerWidget();
    void ShowHideSliderBar();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
signals:
    void tell_close();
private:
    bool isHide;
    bool havingVideo;
    bool isLoop;
    int speedTime;
    Ui::VideoPlayerWidget *ui;
    QMediaPlayer *mediaPlayer;
    QUrl currentVideo_path;

private slots:
    void CloseVideo();
    void ChooseVideo();
    void RefreshMediaPlayer(qint64);
    void RefreshPlayerSlider(qint64);
    void ChangeMediaPlayerState();
    void SetVideoPosition(int position);

    void on_sliderMusic_sliderMoved(int position);
    void on_btnBack_clicked();
    void on_btnForward_clicked();
    void on_btnLoop_clicked();
    void on_btnSpeed_clicked();
    void on_pushButton_clicked();
};
#endif // VIDEOPLAYERWIDGET_H
