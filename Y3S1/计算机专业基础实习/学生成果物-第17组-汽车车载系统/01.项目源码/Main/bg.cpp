#include "bg.h"
#include "image.h"
#include "ui_bg.h"
#include "wechat.h"

Bg::Bg(QWidget *parent, int i)
    : QWidget(parent)
    , ui(new Ui::Bg)
{
    ui->setupUi(this);

    if (i == 1){
        Image *image = new Image(this);
        image->show();
        connect(image, &Image::tell_close,this, &Bg::on_close_window);
    }
    else if (i == 2){
        WeChat *wechat = new WeChat(this);
        wechat->show();
        connect(wechat, &WeChat::tell_close,this, &Bg::on_close_window);
    }

//    qDebug() << "akakaka";
}

Bg::~Bg()
{
    delete ui;
}

void Bg::on_close_window() {
    emit tell_close();
    deleteLater();
}


