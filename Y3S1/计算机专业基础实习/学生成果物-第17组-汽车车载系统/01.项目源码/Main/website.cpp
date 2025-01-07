#include "website.h"
#include "ui_website.h"

#include <QUrl>
#include <QWebEngineView>

Website::Website(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Website)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);
    ui->backButton->setIcon(QIcon(":/back.png"));
    ui->forwardButton->setIcon(QIcon(":/forward.png"));
    ui->reflashButton->setIcon(QIcon(":/reflash.png"));
    ui->widgetWeb->setUrl(QUrl("https://www.baidu.com"));

    connect(ui->widgetWeb, &QWebEngineView::loadFinished, [=]{
            ui->widgetWeb->page()->runJavaScript("document.addEventListener('click', function (event) {console.log(event.target);if (event.target.hasAttribute('href')) {window.location.href=event.target.getAttribute('href'); }});");
        });

    QAbstractSocket::connect(ui->widgetWeb, &QWebEngineView::urlChanged, [&]() {
        ui->urlEdit->setText(ui->widgetWeb->url().toString());
    });

    QAbstractSocket::connect(ui->urlEdit, &QLineEdit::returnPressed, [&]() {
        QString realUrl = ui->urlEdit->text();
        if(ui->urlEdit->text().left(4) != "http") {
            realUrl = "http://" + realUrl;
        }
        ui->widgetWeb->setUrl(QUrl(realUrl));
    });
}

Website::~Website()
{
    delete ui;
}


void Website::on_backButton_clicked()
{
    ui->widgetWeb->back();
}

void Website::on_forwardButton_clicked()
{
    ui->widgetWeb->forward();
}

void Website::on_reflashButton_clicked()
{
    ui->widgetWeb->reload();
}
