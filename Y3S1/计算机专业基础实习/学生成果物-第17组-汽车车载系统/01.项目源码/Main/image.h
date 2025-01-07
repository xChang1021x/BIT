#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QImage>
#include <QPainter>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QFileDialog>
#include <QDebug>
#include <QPoint>
#include <QTransform>
#include<QRectF>
#include <QDir>
#include<QFileInfoList>
#include<QStringList>
#include<QFrame>
#include <QVBoxLayout>
#include<QListWidget>
#include "ui_image.h"
#include"imagelistwindow.h"

class Image : public QWidget {
    Q_OBJECT

public:
    explicit Image(QWidget *parent = nullptr);
    ~Image();
    void loadImage(int index);
    void updatePhotoLabel(); // 声明 updatePhotoLabel 函数
    void loadImagesFromDesktop();
    void updateMainImage(const QString &imagePath); // 声明

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *e) override;
    bool event(QEvent *event) override;

private:
    void moveImage(int deltaX, int deltaY);

int clickCount = 0; // 计数器
    ImageListWindow *imageListWindow = nullptr; // 文件列表窗口
    QLabel *mainImageLabel; // 假设你有一个 QLabel
    QStringList images; // 存储图片路径
    int currentImageIndex = 0; // 当前图片索引
    QListWidget *thumbnailList; // 缩略图列表
    QLabel *currentPhotoLabel; // 用于显示当前照片索引
    QLabel *photoNameLabel;     // 用于显示照片名称
    QLabel *imageLabel; // 用于显示图像
    QLabel *imageDisplay; // 用于显示图片的 QLabel
    Ui::Image *ui;
    // UI Components

    QLabel *label_values;
    QPushButton button_max;
    QPushButton button_min;
    QPushButton button_left;
    QPushButton button_right;
    QPushButton button_up;
    QPushButton button_down;
    QPushButton button_resetpic;
    QPushButton button_rotateleft;
    QPushButton button_rotateright;
    QPushButton button_mirror;
    QPushButton button_previous;
    QPushButton button_next;
    QPushButton button_openfile;
    QPushButton button_quit;

    // Image and display parameters
    QImage image;
    float ration;
    QPoint Alloffset;
    int rotationAngle;
    bool mirror;
signals:
    void tell_close();


private slots:
    void Onbutton_min_Clicked();
    void Onbutton_max_Clicked();
    void Onbutton_left_Clicked();
    void Onbutton_right_Clicked();
    void Onbutton_up_Clicked();
    void Onbutton_down_Clicked();
    void Onbutton_resetpic_Clicked();
    void Onbutton_rotateleft_Clicked();
    void Onbutton_rotateright_Clicked();
    void Onbutton_mirror_Clicked();
    void Onbutton_previous_Clicked();
    void Onbutton_next_Clicked();
    void Onbutton_openfile_Clicked();
    void Onbutton_quit_Clicked();


};

#endif // WIDGET_H
