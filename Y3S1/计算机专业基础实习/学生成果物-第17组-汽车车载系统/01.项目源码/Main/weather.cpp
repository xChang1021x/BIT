#include "weather.h"
#include "ui_weather.h"
#include "dayline.h"

#include <QButtonGroup>
#include <QJsonArray>
#include <QPainter>
#include <QPoint>

Weather::Weather(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Weather)
{
    ui->setupUi(this);



    qDebug() << "widget construct";

    //    ui->labelDayLine->hide();
    //    ui->labelDayLine_2->hide();

    // http request
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // define url request api
    this->strURL = "http://v0.yiketianqi.com/api?unescape=1&version=v9&appid=29488751&appsecret=2m1Jiltq";
    QUrl url(this->strURL);
    QNetworkRequest request(url);

    // use get method request
    QNetworkReply *reply = manager->get(request);

    // 对reply进行绑定, invoke method readHttpReply
    QObject::connect(manager, &QNetworkAccessManager::finished,
                     this, [this, reply]() {
        renderPage(reply);
    });
}

Weather::~Weather()
{
    delete ui;
}

void Weather::renderPage(QNetworkReply *reply) {
    // get result code
    // int resultCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray result;
    if(reply->error() == QNetworkReply::NoError) {
        // handle no error
        result = reply->readAll();
    } else {
        // handle error
        QMessageBox::warning(this, "error", reply->errorString());
        return;
    }
    jsonObject = convertJsonStringToObj(result);

    handleChangeDay(0);

    handle7DayRender();

    qDebug() << "renderPage";
}

QJsonObject Weather::convertJsonStringToObj(QByteArray result) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(result);
    if(!jsonDoc.isNull() && jsonDoc.isObject()) {
        return jsonDoc.object();
    }
    return {};
}

void Weather::on_searchButton_2_clicked()
{
    // get text on textEdit
    QString city = ui->searchText_2->toPlainText();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // strURL add param
    strURL += "&city=" + city;
    QUrl url(this->strURL);
    QNetworkRequest request(url);

    // use get method request
    QNetworkReply *reply = manager->get(request);

    // 对reply进行绑定, invoke method readHttpReply
    QObject::connect(manager, &QNetworkAccessManager::finished,
                     this, [this, reply]() {
        renderPage(reply);
    });

    // initialize strURL
    strURL = "http://v0.yiketianqi.com/api?unescape=1&version=v9&appid=29488751&appsecret=2m1Jiltq";
}

void Weather::handleChangeDay(int day) {
    ui->pushButton_8->setStyleSheet("background-color: none;");
    ui->pushButton_9->setStyleSheet("background-color: none;");
    ui->pushButton_10->setStyleSheet("background-color: none;");
    ui->pushButton_11->setStyleSheet("background-color: none;");
    ui->pushButton_12->setStyleSheet("background-color: none;");
    ui->pushButton_13->setStyleSheet("background-color: none;");
    ui->pushButton_14->setStyleSheet("background-color: none;");
    if(day == 0) {
        ui->pushButton_8->setStyleSheet("background-color: rgb(52, 101, 164);");
    } else if(day == 1) {
        ui->pushButton_9->setStyleSheet("background-color: rgb(52, 101, 164);");
    } else if(day == 2) {
        ui->pushButton_10->setStyleSheet("background-color: rgb(52, 101, 164);");
    }else if(day == 3) {
        ui->pushButton_11->setStyleSheet("background-color: rgb(52, 101, 164);");
    }else if(day == 4) {
        ui->pushButton_12->setStyleSheet("background-color: rgb(52, 101, 164);");
    }else if(day == 5) {
        ui->pushButton_13->setStyleSheet("background-color: rgb(52, 101, 164);");
    }else if(day == 6) {
        ui->pushButton_14->setStyleSheet("background-color: rgb(52, 101, 164);");
    }

    if(jsonObject.contains("data") && jsonObject["data"].isArray()) {
        jsonDataArray = jsonObject["data"].toArray();
    }
    firstObject = jsonDataArray.at(day).toObject();
    ui->dayLine->installEventFilter(this);
    if(!(jsonObject["city"].toString() == "")) {
        // render on showpage
        ui->labelDate_2->setText(firstObject["date"].toString());
        ui->labelWeek_2->setText(firstObject["week"].toString());
        ui->labelTem_2->setText(firstObject["tem"].toString() + "℃");
        ui->labelTemp1_2->setText(firstObject["tem1"].toString()+ "℃");
        ui->labelTemp2_2->setText(firstObject["tem2"].toString()+ "℃");
        ui->labelWin_2->setText(firstObject["win"].toArray()[0].toString());
        ui->labelWinSpeed_2->setText(firstObject["win_speed"].toString());
        ui->labelWinMeter_2->setText(firstObject["win_meter"].toString());
        ui->labelUpdateTime_2->setText(jsonObject["update_time"].toString().right(8));
        ui->labelAirTips_2->setText(firstObject["air_tips"].toString());
        ui->labelCity_2->setText(jsonObject["city"].toString());
        ui->labelCityEn_2->setText(jsonObject["cityEn"].toString());
        ui->labelHumidity_2->setText(firstObject["humidity"].toString());
        ui->labelUvDesc_2->setText(firstObject["pressure"].toString());
        ui->labelVisibility_2->setText(firstObject["visibility"].toString());
        ui->labelWea_2->setText(firstObject["wea"].toString());
        ui->labelAir_2->setText(firstObject["air"].toString());
        ui->labelAirPm_2->setText(firstObject["air_pm25"].toString());
        ui->labelAirLevel_2->setText(firstObject["air_level"].toString());
        QString wea = firstObject["wea_img"].toString();
        ui->weaImg_8->setPixmap(QPixmap(":/" + wea +".png"));

        QJsonObject jsonAqiObject = jsonObject["aqi"].toObject();

        ui->labelSafe1_2->setText(jsonAqiObject["kouzhao"].toString());
        ui->labelSafe2_2->setText(jsonAqiObject["yundong"].toString());
        ui->labelSafe3_2->setText(jsonAqiObject["waichu"].toString());
        ui->labelSafe4_2->setText(jsonAqiObject["kaichuang"].toString());

        DayLine *dayline = new DayLine(firstObject);
        ui->dayLine->setWidget(dayline);


        DayLine *dayline3 = new DayLine(jsonDataArray);
        ui->dayLine_3->setWidget(dayline3);



        QString avgTem = "温度：";
        QString time = "时间：";
        for(int i = 0; i < 24; ++i) {
            QJsonObject objectHours = firstObject["hours"].toArray()[i].toObject();
            avgTem += "   " + objectHours["tem"].toString();
            time += "   " + objectHours["hours"].toString().left(2);
        }
    } else {
        QMessageBox msgBox(this);
        msgBox.setStyleSheet("background-color: white;");
        msgBox.setWindowTitle("error");
        msgBox.setText("请输入正确的城市名");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
}

void Weather::handle7DayRender() {
    for(int i = 0; i < 7; ++i) {
        QJsonObject object7 = jsonDataArray.at(i).toObject();
        switch(i) {
        case 0: ui->pushButton_8->setText(object7["date"].toString().right(5));
            break;
        case 1: ui->pushButton_9->setText(object7["date"].toString().right(5));
            break;
        case 2: ui->pushButton_10->setText(object7["date"].toString().right(5));
            break;
        case 3: ui->pushButton_11->setText(object7["date"].toString().right(5));
            break;
        case 4: ui->pushButton_12->setText(object7["date"].toString().right(5));
            break;
        case 5: ui->pushButton_13->setText(object7["date"].toString().right(5));
            break;
        case 6: ui->pushButton_14->setText(object7["date"].toString().right(5));
            break;
        }
    }
    update();
}

void Weather::on_pushButton_8_clicked()
{
    handleChangeDay(0);
    update();
}

void Weather::on_pushButton_9_clicked()
{
    handleChangeDay(1);
    update();
}


void Weather::on_pushButton_10_clicked()
{
    handleChangeDay(2);
    update();
}



void Weather::on_pushButton_11_clicked()
{
    handleChangeDay(3);
    update();
}


void Weather::on_pushButton_12_clicked()
{
    handleChangeDay(4);
    update();
}


void Weather::on_pushButton_13_clicked()
{
    handleChangeDay(5);
    update();
}


void Weather::on_pushButton_14_clicked()
{
    handleChangeDay(6);
    update();
}

void Weather::on_logoReturn_2_clicked()
{
    emit tell_close();
    deleteLater();
}


