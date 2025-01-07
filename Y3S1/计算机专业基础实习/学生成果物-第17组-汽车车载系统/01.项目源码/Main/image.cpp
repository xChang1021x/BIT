#include "image.h"
#include"imagelistwindow.h"
#include "ui_image.h"
#include <QPainter>
#include <QKeyEvent>
#include<QPushButton>
#include<QIcon>
#include<QVBoxLayout>
#include<QFrame>
#include<QDir>
#include <QFileDialog>
#include <QFileInfoList>
#include<QTimer>
#include <QPixmap>
#include<QMessageBox>

Image::Image(QWidget *parent): QWidget(parent),
    currentPhotoLabel(new QLabel(this)),// 初始化 QLabel
    ui(new Ui::Image),
    label_values(new QLabel(this)),
    button_max("", this),
    button_min("", this),
    button_left("", this),
    button_right("", this),
    button_up("", this),
    button_down("", this),
    button_resetpic("", this),
    button_rotateleft("", this),
    button_rotateright("", this),
    button_mirror("", this),
    button_previous("",this),
    button_next("",this),
    button_openfile("",this),
    button_quit("",this),
    ration(1.0), // 初始比例
    Alloffset(0, 0), // 初始化偏移量
    rotationAngle(0), // 初始化旋转角度
    mirror(true) // 初始化镜像状态
{
    ui->setupUi(this); // 设置 UI
    ui->widget->hide();
    loadImagesFromDesktop(); // 加载图片路径
    mainImageLabel = ui->image; // 确保 QLabel 被正确创建
    mainImageLabel->raise();
    QPushButton *mirrorButton = new QPushButton(this);
    QPushButton *maximizeButton = new QPushButton(this);
    QPushButton *minimizeButton = new QPushButton(this);
    QPushButton *upButton = new QPushButton(this);
    QPushButton *downButton = new QPushButton(this);
    QPushButton *leftButton = new QPushButton(this);
    QPushButton *rightButton = new QPushButton(this);
    QPushButton *resetButton = new QPushButton(this);
    QPushButton *rotateleftButton = new QPushButton(this);
    QPushButton *rotaterightButton = new QPushButton(this);
    QPushButton *previousButton = new QPushButton(this);
    QPushButton *nextButton = new QPushButton(this);
    QPushButton *openfileButton=new QPushButton(this);
    QPushButton *quitButton=new QPushButton(this);
    // 设置 QLabel 样式
    currentPhotoLabel->setAlignment(Qt::AlignCenter);
//    currentPhotoLabel->setStyleSheet("font-size: 16px;color:#C1003C");
    currentPhotoLabel->setGeometry(80,100,640,30);
    // 加载图片
        loadImagesFromDesktop();
    // 初始化显示
        updatePhotoLabel();


    // 设置按钮图标
    QIcon resetIcon(":/reset.png"); // 使用资源文件中的图标
    resetButton->setIcon(resetIcon);
    QIcon mirrorIcon(":/mirror.png"); // 使用资源文件中的图标
    mirrorButton->setIcon(mirrorIcon);
    QIcon maximizeIcon(":/maximize.png"); // 使用资源文件中的图标
    maximizeButton->setIcon(maximizeIcon);
    QIcon minimizeIcon(":/minimize.png"); // 使用资源文件中的图标
    minimizeButton->setIcon(minimizeIcon);
    QIcon upIcon(":/move_up.png"); // 使用资源文件中的图标
    upButton->setIcon(upIcon);
    QIcon downIcon(":/move_down.png"); // 使用资源文件中的图标
    downButton->setIcon(downIcon);
    QIcon leftIcon(":/move-left.png"); // 使用资源文件中的图标
    leftButton->setIcon(leftIcon);
    QIcon rightIcon(":/move-right.png"); // 使用资源文件中的图标
    rightButton->setIcon(rightIcon);
    QIcon rotateleftIcon(":/rotate-left.png"); // 使用资源文件中的图标
    rotateleftButton->setIcon(rotateleftIcon);
    QIcon rotaterightIcon(":/rotate-right.png"); // 使用资源文件中的图标
    rotaterightButton->setIcon(rotaterightIcon);
    QIcon previousIcon(":/Previous.png"); // 使用资源文件中的图标
    previousButton->setIcon(previousIcon);
    QIcon nextIcon(":/Next.png"); // 使用资源文件中的图标
    nextButton->setIcon(nextIcon);
    QIcon openfileIcon(":/OpenFile.png"); // 使用资源文件中的图标
    openfileButton->setIcon(openfileIcon);
    QIcon quitIcon(":/quit.png"); // 使用资源文件中的图标
    quitButton->setIcon(quitIcon);


    // 设置图标大小
    resetButton->setIconSize(QSize(80, 80));
    mirrorButton->setIconSize(QSize(80, 80));
    maximizeButton->setIconSize(QSize(80, 80));
    minimizeButton->setIconSize(QSize(80, 80));
    upButton->setIconSize(QSize(80, 80));
    downButton->setIconSize(QSize(80, 80));
    leftButton->setIconSize(QSize(80, 80));
    rightButton->setIconSize(QSize(80, 80));
    rotateleftButton->setIconSize(QSize(80, 80));
    rotaterightButton->setIconSize(QSize(80, 80));
    previousButton->setIconSize(QSize(80, 80));
    nextButton->setIconSize(QSize(80, 80));
    openfileButton->setIconSize(QSize(70,70));
    quitButton->setIconSize(QSize(70,70));

    // 连接按钮点击信号到相应的槽
    connect(resetButton, &QPushButton::clicked, this, &Image::Onbutton_resetpic_Clicked);
    connect(mirrorButton, &QPushButton::clicked, this, &Image::Onbutton_mirror_Clicked);
    connect(maximizeButton, &QPushButton::clicked, this, &Image::Onbutton_max_Clicked);
    connect(minimizeButton, &QPushButton::clicked, this, &Image::Onbutton_min_Clicked);
    connect(upButton, &QPushButton::clicked, this, &Image::Onbutton_up_Clicked);
    connect(downButton, &QPushButton::clicked, this, &Image::Onbutton_down_Clicked);
    connect(leftButton, &QPushButton::clicked, this, &Image::Onbutton_left_Clicked);
    connect(rightButton, &QPushButton::clicked, this, &Image::Onbutton_right_Clicked);
    connect(rotateleftButton, &QPushButton::clicked, this, &Image::Onbutton_rotateleft_Clicked);
    connect(rotaterightButton, &QPushButton::clicked, this, &Image::Onbutton_rotateright_Clicked);
    connect(previousButton, &QPushButton::clicked, this, &Image::Onbutton_previous_Clicked);
    connect(nextButton, &QPushButton::clicked, this, &Image::Onbutton_next_Clicked);
    connect(openfileButton, &QPushButton::clicked, this, &Image::Onbutton_openfile_Clicked);
    connect(quitButton, &QPushButton::clicked, this, &Image::Onbutton_quit_Clicked);

    // 设置样式
    resetButton->setStyleSheet("background-color:#F0F0F0;border-radius:5px;text-align: center;}"
                               "QPushButton:hover{background-color:#66ff11;}"
                               "QPushButton:pressed{background-color:#6600ff;}"
                               "QPushButton:disabled{background-color:#F0F0F0;"); // 透明背景，无边框

    mirrorButton->setStyleSheet("background-color:#F0F0F0;border-radius:5px;text-align: center;}"
                               "QPushButton:hover{background-color:#66ff11;}"
                               "QPushButton:pressed{background-color:#6600ff;}"
                               "QPushButton:disabled{background-color:#F0F0F0;"); // 透明背景，无边框

    maximizeButton->setStyleSheet("background-color:#F0F0F0;border-radius:5px;text-align: center;}"
                               "QPushButton:hover{background-color:#66ff11;}"
                               "QPushButton:pressed{background-color:#6600ff;}"
                               "QPushButton:disabled{background-color:#F0F0F0;"); // 透明背景，无边框

    minimizeButton->setStyleSheet("background-color:#F0F0F0;border-radius:5px;text-align: center;}"
                               "QPushButton:hover{background-color:#66ff11;}"
                               "QPushButton:pressed{background-color:#6600ff;}"
                               "QPushButton:disabled{background-color:#F0F0F0;"); // 透明背景，无边框

    upButton->setStyleSheet("background-color:#F0F0F0;border-radius:5px;text-align: center;}"
                               "QPushButton:hover{background-color:#66ff11;}"
                               "QPushButton:pressed{background-color:#6600ff;}"
                               "QPushButton:disabled{background-color:#F0F0F0;"); // 透明背景，无边框

    downButton->setStyleSheet("background-color:#F0F0F0;border-radius:5px;text-align: center;}"
                               "QPushButton:hover{background-color:#66ff11;}"
                               "QPushButton:pressed{background-color:#6600ff;}"
                               "QPushButton:disabled{background-color:#F0F0F0;"); // 透明背景，无边框

    leftButton->setStyleSheet("background-color:#F0F0F0;border-radius:5px;text-align: center;}"
                               "QPushButton:hover{background-color:#66ff11;}"
                               "QPushButton:pressed{background-color:#6600ff;}"
                               "QPushButton:disabled{background-color:#F0F0F0;"); // 透明背景，无边框

    rightButton->setStyleSheet("background-color:#F0F0F0;border-radius:5px;text-align: center;}"
                               "QPushButton:hover{background-color:#66ff11;}"
                               "QPushButton:pressed{background-color:#6600ff;}"
                               "QPushButton:disabled{background-color:#F0F0F0;"); // 透明背景，无边框

    rotateleftButton->setStyleSheet("background-color:#F0F0F0;border-radius:5px;text-align: center;}"
                               "QPushButton:hover{background-color:#66ff11;}"
                               "QPushButton:pressed{background-color:#6600ff;}"
                               "QPushButton:disabled{background-color:#F0F0F0;"); // 透明背景，无边框

    rotaterightButton->setStyleSheet("background-color:#F0F0F0;border-radius:5px;text-align: center;}"
                               "QPushButton:hover{background-color:#66ff11;}"
                               "QPushButton:pressed{background-color:#6600ff;}"
                               "QPushButton:disabled{background-color:#F0F0F0;"); // 透明背景，无边框

    previousButton->setStyleSheet("background-color:#F0F0F0;border-radius:5px;text-align: center;}"
                               "QPushButton:hover{background-color:#66ff11;}"
                               "QPushButton:pressed{background-color:#6600ff;}"
                               "QPushButton:disabled{background-color:#F0F0F0;"); // 透明背景，无边框

    nextButton->setStyleSheet("background-color:#F0F0F0;border-radius:5px;text-align: center;}"
                               "QPushButton:hover{background-color:#66ff11;}"
                               "QPushButton:pressed{background-color:#6600ff;}"
                               "QPushButton:disabled{background-color:#F0F0F0;"); // 透明背景，无边框

    openfileButton->setStyleSheet("background-color:#F0F0F0;border-radius:5px;text-align: center;}"
                               "QPushButton:hover{background-color:#66ff11;}"
                               "QPushButton:pressed{background-color:#6600ff;}"
                               "QPushButton:disabled{background-color:#F0F0F0;"); // 透明背景，无边框
    quitButton->setStyleSheet("background-color:#F0F0F0;border-radius:5px;text-align: center;}"
                               "QPushButton:hover{background-color:#66ff11;}"
                               "QPushButton:pressed{background-color:#6600ff;}"
                               "QPushButton:disabled{background-color:#F0F0F0;"); // 透明背景，无边框


    // 设置按钮位置和大小
    openfileButton->setGeometry(0,500,80,100);
    mirrorButton->setGeometry(80,500,80,100);
    maximizeButton->setGeometry(160,500,80,100);
    minimizeButton->setGeometry(240,500,80,100);
    upButton->setGeometry(320,500,80,100);
    downButton->setGeometry(400,500,80,100);
    leftButton->setGeometry(480,500,80,100);
    rightButton->setGeometry(560,500,80,100);
    resetButton->setGeometry(640,500,80,100);
    quitButton->setGeometry(720,500,80,100);
    rotateleftButton->setGeometry(0,0,400,100);
    rotaterightButton->setGeometry(400,0,400,100);
    previousButton->setGeometry(0,100,80,400);
    nextButton->setGeometry(720,100,80,400);


    // 设置窗口属性
    resize(800, 600);
    setWindowTitle("Picture Viewer");

    // 设置比例显示
//    label_values->setStyleSheet("font-size: 12pt;");
    label_values->setAlignment(Qt::AlignCenter); // 居中对齐
    label_values->move(630, 105); // 设置位置在上方
    label_values->setText("Ratio: 1.0"); // 设置初始文本
}

Image::~Image(){
    delete ui;
}

void Image::moveImage(int deltaX, int deltaY) {
Alloffset += QPoint(deltaX, deltaY);
update(); // 请求重绘
}

void Image::keyPressEvent(QKeyEvent *event) {
switch (event->key()) {
case Qt::Key_Left:
moveImage(-10, 0);
break;
case Qt::Key_Right:
moveImage(10, 0);
break;
case Qt::Key_Up:
moveImage(0, -10);
break;
case Qt::Key_Down:
moveImage(0, 10);
break;
default:
QWidget::keyPressEvent(event);
}
}

void Image::updatePhotoLabel() {
    if (!images.isEmpty() && currentImageIndex < images.size()) {
        QFileInfo fileInfo(images[currentImageIndex]);
        currentPhotoLabel->setText(QString("当前照片：%1").arg(fileInfo.fileName()));
    } else {
        qDebug() << "Invalid currentImageIndex or images list is empty!";
    }
}

void Image::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // 根据当前比例计算缩放后的尺寸
    QSize scaledSize = QSize(image.size().width() * ration, image.size().height() * ration);

    // 获取窗口大小
    int windowWidth = width();
    int windowHeight = height();

//    this->setStyleSheet("background-color: #5e95e6"); // 设置背景

    // 计算绘制位置，使图片中心与窗口中心对齐
    int x = (windowWidth - scaledSize.width()) / 2;
    int y = (windowHeight - scaledSize.height()) / 2;

    // 应用镜像变换
    if (mirror) {
        painter.scale(-1, 1); // 水平镜像
        x = -x - scaledSize.width(); // 调整位置
    }
    // 应用旋转
    painter.translate(x + scaledSize.width() / 2, y + scaledSize.height() / 2); // 移动到中心
    painter.rotate(rotationAngle); // 旋转
    painter.translate(-scaledSize.width() / 2, -scaledSize.height() / 2); // 移动回原位置

    // 应用偏移
    painter.translate(Alloffset);

    // 绘制图像
    if (!image.isNull()) {
    // 绘制缩放后的图片
    painter.drawImage(QPoint(0, 0), image.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    // 更新比例值显示
    label_values->setText(QString("Ratio: %1").arg(ration, 0, 'f', 1)); // 更新比例显示
    label_values->raise(); // 确保比例值在最上方
}
//wheelincident
void Image:: wheelEvent(QWheelEvent*)
{

}

//panduanwheelcontrol
bool Image:: event(QEvent *event)
{
return QWidget::event(event);

}

void Image::Onbutton_min_Clicked()
{
    if (ration > 0.1) {
        ration -= 0.1;
        label_values->setText(QString("Ratio: %1").arg(ration, 0, 'f', 1)); // 更新比例显示
        update();
    }
}

void Image::Onbutton_max_Clicked()
{
    if (ration < 10.0) {
        ration += 0.1;
        label_values->setText(QString("Ratio: %1").arg(ration, 0, 'f', 1)); // 更新比例显示
        update();
    }
}

void Image:: Onbutton_left_Clicked()
{
Alloffset.setX(Alloffset.x() + 10);
update();
}

void Image:: Onbutton_right_Clicked()
{
Alloffset.setX(Alloffset.x() - 10);
update();
}

void Image:: Onbutton_up_Clicked()
{
Alloffset.setY(Alloffset.y() - 10);
update();
}

void Image:: Onbutton_down_Clicked()
{
Alloffset.setY(Alloffset.y() + 10);
update();
}

void Image::Onbutton_resetpic_Clicked()
{
Alloffset = QPoint(0, 0); // 重置偏移到原点
ration = 0.5; // 重置比例，如果需要
update(); // 重新绘制
}


void Image::Onbutton_rotateleft_Clicked()
{
rotationAngle += 90; // 左旋转90度
update(); // 刷新窗口
}

void Image::Onbutton_rotateright_Clicked()
{
rotationAngle -= 90; // 右旋转90度
update(); // 刷新窗口
}

void Image::Onbutton_mirror_Clicked()
{
mirror = !mirror; // 切换镜像状态
update(); // 刷新窗口
}
void Image::Onbutton_previous_Clicked()
{
    if (!images.isEmpty()) {
        currentImageIndex = (currentImageIndex - 1 + images.size()) % images.size(); // 循环到最后一张
        loadImage(currentImageIndex); // 加载图片
        update(); // 刷新窗口
    }
}
void Image::Onbutton_next_Clicked()
{
    if (!images.isEmpty()) {
        currentImageIndex = (currentImageIndex + 1) % images.size(); // 循环到第一张
        loadImage(currentImageIndex); // 加载图片
        update(); // 刷新窗口
    }
}
void Image::loadImage(int index) {
    if (images.isEmpty()) {
        qDebug() << "Images list is empty!";
        return;
    }

    currentImageIndex = index % images.size(); // 确保索引有效
    qDebug() << "Loading image at index:" << currentImageIndex;

    if (!image.load(images[currentImageIndex])) {
        qDebug() << "Failed to load image:" << images[currentImageIndex];
    }

    updatePhotoLabel(); // 更新标签显示
}

void Image::loadImagesFromDesktop() {
    QString desktopPath = QDir::homePath() + "/PictureViewPm/images";
    QDir dir(desktopPath);

    if (dir.exists()) {
        QStringList filters;
        filters << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp";
        QFileInfoList fileList = dir.entryInfoList(filters, QDir::Files);

        for (const QFileInfo &fileInfo : fileList) {
            images.append(fileInfo.absoluteFilePath());
            qDebug() << "Loaded image:" << fileInfo.absoluteFilePath();
        }
    } else {
        qDebug() << "Directory does not exist!";
    }

    if (!images.isEmpty()) {
        currentImageIndex = 0; // 重置索引
        loadImage(currentImageIndex);
    } else {
        qDebug() << "No images found in directory!";
    }
}
void Image::Onbutton_openfile_Clicked() {
    loadImagesFromDesktop(); // 确保调用此方法
    clickCount++;

    if (clickCount == 1) {
        QString desktopPath = QDir::homePath() + "/PictureViewPm/images";
        QDir dir(desktopPath);

        if (!dir.exists()) {
            qDebug() << "Directory does not exist!";
            return;
        }

        QStringList filters;
        filters << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp";
        dir.setNameFilters(filters);
        QFileInfoList fileList = dir.entryInfoList(QDir::Files);

        if (!imageListWindow) {
            imageListWindow = new ImageListWindow(this);
            connect(imageListWindow, &ImageListWindow::imageSelected, this, [this](const QString &imagePath) {
                updateMainImage(imagePath); // 更新主窗口的照片
            });
        }

        imageListWindow->clearImages(); // 清空之前的图片
        for (const QFileInfo &fileInfo : fileList) {
            imageListWindow->addImage(fileInfo.absoluteFilePath(), fileInfo.fileName());
        }
        imageListWindow->show();
    } else if (clickCount == 2) {
        if (imageListWindow) {
            imageListWindow->close(); // 关闭文件列表窗口
            imageListWindow = nullptr; // 重置指针
        }
    }

    // 重置计数器
    QTimer::singleShot(1000, [this]() { clickCount = 0; });
    qDebug() << "Click count:" << clickCount;
}

void Image::updateMainImage(const QString &imagePath) {
    if (imagePath.isEmpty()) {
        qDebug() << "Image path is empty!";
        return;
    }

    QPixmap pixmap(imagePath);
    if (pixmap.isNull()) {
        qDebug() << "Failed to load image from path:" << imagePath;
        QMessageBox::warning(this, "Error", "Could not load image. Please check the file.");
        return;
    }

    mainImageLabel->setPixmap(pixmap.scaled(mainImageLabel->size(), Qt::KeepAspectRatio));
    updatePhotoLabel(); // 更新当前照片标签
}

void Image::Onbutton_quit_Clicked() {
    close(); // 关闭窗口

    emit tell_close();
}
