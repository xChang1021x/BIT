#include "imagelistwindow.h"
#include <QVBoxLayout>

ImageListWindow::ImageListWindow(QWidget *parent) : QWidget(parent) {
    imageListWidget = new QListWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(imageListWidget);
    setLayout(layout);
    setWindowTitle("Image List");

    connect(imageListWidget, &QListWidget::itemClicked, this, [this](QListWidgetItem *item) {
        emit imageSelected(item->data(Qt::UserRole).toString());
        close(); // 关闭窗口
    });
}

void ImageListWindow::addImage(const QString &imagePath, const QString &imageName) {
    QListWidgetItem *item = new QListWidgetItem(QIcon(imagePath), imageName);
    item->setData(Qt::UserRole, imagePath);
    imageListWidget->addItem(item);
}
void ImageListWindow::clearImages() {
    // 假设你使用一个 QListWidget 或类似控件来显示图像
    imageListWidget->clear(); // 清空显示的图像列表
}
