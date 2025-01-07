#ifndef IMAGELISTWINDOW_H
#define IMAGELISTWINDOW_H

#include <QWidget>
#include <QListWidget>

class ImageListWindow : public QWidget {
    Q_OBJECT

public:
    explicit ImageListWindow(QWidget *parent = nullptr);
    void addImage(const QString &imagePath, const QString &imageName);
    void clearImages(); // 声明清空图像的方法

signals:
    void imageSelected(const QString &imagePath);
signals:
    void tell_close();
private:
    QListWidget *imageListWidget;
};

#endif // IMAGELISTWINDOW_H
