#ifndef WEATHER_H
#define WEATHER_H

#include "dayline.h"

#include <QWidget>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class Weather; }
QT_END_NAMESPACE

class Weather : public QWidget
{
    Q_OBJECT

public:
    Weather(QWidget *parent = nullptr);
    ~Weather();
    QJsonObject convertJsonStringToObj(QByteArray);
    void renderPage(QNetworkReply *reply);
    void handleChangeDay(int day);
    void handle7DayRender();


protected:
//    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void tell_close();
private slots:
    void on_searchButton_2_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_8_clicked();

    void on_logoReturn_2_clicked();

private:
    Ui::Weather *ui;
    QString strURL;
    QString strURL7;
    QJsonObject jsonObject;
    QJsonArray jsonDataArray;
    QJsonObject firstObject;
};
#endif // WEATHER_H

