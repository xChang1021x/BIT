#include "cargps.h"
#include "ui_cargps.h"

#include <QStringListModel>

CarGPS::CarGPS(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CarGPS)
{

    ui->setupUi(this);
    ui->btnMenu->setFlat(true);
    ui->stackedWidget->setCurrentIndex(1);
    ui->widgetMenu->hide();
    ui->keyWordList->hide();
    ui->keywordWidget->hide();
    searchMode = SearchingMode::DIRECTION_MODE;
    ui->mapView->setUrl(QUrl("https://m.amap.com/navi/?start=116.403124,39.940693&dest=&destName=前往这里&key=34109fa4ffe916d6a8069f7c80b09811&jscode=fb3f824211d5cf58b17efbacf1d66c20"));
    connect(ui->keyWordList, SIGNAL(clicked(const QModelIndex)),
                this, SLOT(slotClicked(const QModelIndex)));
}

CarGPS::~CarGPS()
{
    delete ui;
}


void CarGPS::on_btnMenu_clicked()
{
    qDebug() << "Menu";
    if (ui->widgetMenu->isHidden()){
        ui->widgetMenu->show();
    }
    else{
        ui->widgetMenu->hide();
    }
}

void CarGPS::on_txtSearch_returnPressed()
{
    // http request
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    if (searchMode == SearchingMode::DIRECTION_MODE){
        QString strURL = "https://restapi.amap.com/v3/geocode/geo?key=56d764b33d43a413e390852cc7a1e457&address=" + ui->txtStart->text();
        QUrl url(strURL);
        QNetworkRequest request(url);

        // use get method request
        QNetworkReply *reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, [=](){
            QByteArray result = reply->readAll();
            if(reply->error() == QNetworkReply::NoError) {
                // handle no error
                QJsonDocument jsonDoc = QJsonDocument::fromJson(result);
                QJsonObject jsonObject;
                if(!jsonDoc.isNull() && jsonDoc.isObject()) {
                     jsonObject = jsonDoc.object();
                }
                QJsonObject geocodesFirst = jsonObject["geocodes"].toArray().at(0).toObject();
                startLocation = geocodesFirst["location"].toString();
                ui->mapView->setUrl(QUrl());
                ui->txtStart->setText("");
            } else {
                // handle error
                return;
            }
        });

        QString strURL_2 = "https://restapi.amap.com/v3/geocode/geo?key=56d764b33d43a413e390852cc7a1e457&address=" + ui->txtEnd->text();
        QUrl url_2(strURL);
        QNetworkRequest request_2(url_2);

        // use get method request
        QNetworkReply *reply_2 = manager->get(request);
        connect(reply_2, &QNetworkReply::finished, [=](){
            QByteArray result_2 = reply_2->readAll();
            if(reply_2->error() == QNetworkReply::NoError) {
                // handle no error
                QJsonDocument jsonDoc = QJsonDocument::fromJson(result_2);
                QJsonObject jsonObject;
                if(!jsonDoc.isNull() && jsonDoc.isObject()) {
                     jsonObject = jsonDoc.object();
                }
                QJsonObject geocodesFirst = jsonObject["geocodes"].toArray().at(0).toObject();
                endLocation = geocodesFirst["location"].toString();
                ui->txtEnd->setText("");
            } else {
                // handle error
                return;
            }
        });

        if (startLocation == ""){
            startLocation = "116.403124,39.940693";
        }
        finalStrUrl = "https://m.amap.com/navi/?start=" + startLocation + "&dest=" + endLocation +"&destName=一条驾车路线&key=34109fa4ffe916d6a8069f7c80b09811&jscode=fb3f824211d5cf58b17efbacf1d66c20";
        ui->mapView->setUrl(QUrl(finalStrUrl));
    }
    else if (searchMode == SearchingMode::NEARBY_MODE){
        QString strURL = "https://m.amap.com/around/?locations=116.470098,39.992838&keywords=" + ui->txtSearch->text() + ",美食,KTV,地铁站,公交站&defaultIndex=1&defaultView=map&searchRadius=5000&key=34109fa4ffe916d6a8069f7c80b09811&jscode=fb3f824211d5cf58b17efbacf1d66c20";
        ui->mapView->setUrl(QUrl(strURL));
        ui->txtSearch->setText("");
    }
    // define url request api

}

void CarGPS::slotClicked(const QModelIndex &index){
    qDebug() << "SLOTCLICK";
    isFinish = 1;
    isSlotClick = true;
    if (txtMode == 1){
        ui->txtSearch->setText(index.data().toString());
        on_txtSearch_returnPressed();
    }
    else if (txtMode == 2){
        ui->txtStart->setText(index.data().toString());
    }
    else if (txtMode == 3){
        ui->txtEnd->setText(index.data().toString());
    }
    ui->keywordWidget->hide();
}

void CarGPS::on_btnDirectionMode_clicked()
{
    searchMode = SearchingMode::DIRECTION_MODE;
    ui->mapView->setUrl(QUrl("https://m.amap.com/navi/?start=116.403124,39.940693&dest="+ ui->txtSearch->text() +"&destName=一条驾车路线&key=34109fa4ffe916d6a8069f7c80b09811&jscode=fb3f824211d5cf58b17efbacf1d66c20"));
    ui->widgetMenu->hide();
    ui->keyWordList->hide();
    ui->keywordWidget->hide();
    ui->stackedWidget->setCurrentIndex(1);
}


void CarGPS::on_btnNearbyMode_clicked()
{
    searchMode = SearchingMode::NEARBY_MODE;
    ui->mapView->setUrl(QUrl("https://m.amap.com/around/?locations=116.470098,39.992838&keywords=美食,KTV,地铁站,公交站&defaultIndex=1&defaultView=map&searchRadius=5000&key=34109fa4ffe916d6a8069f7c80b09811&jscode=fb3f824211d5cf58b17efbacf1d66c20"));
    ui->widgetMenu->hide();
    ui->keyWordList->hide();
    ui->keywordWidget->hide();
    ui->stackedWidget->setCurrentIndex(0);
}


void CarGPS::on_pushButton_clicked()
{
    // http request
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QString strURL = "https://restapi.amap.com/v3/geocode/geo?key=56d764b33d43a413e390852cc7a1e457&address=" + ui->txtStart->text();
    QUrl url(strURL);
    QNetworkRequest request(url);

    // use get method request
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, [=](){
        QByteArray result = reply->readAll();
        if(reply->error() == QNetworkReply::NoError) {
            // handle no error
            QJsonDocument jsonDoc = QJsonDocument::fromJson(result);
            QJsonObject jsonObject;
            if(!jsonDoc.isNull() && jsonDoc.isObject()) {
                jsonObject = jsonDoc.object();
            }
            QJsonObject geocodesFirst = jsonObject["geocodes"].toArray().at(0).toObject();
            startLocation = geocodesFirst["location"].toString();
            ui->mapView->setUrl(QUrl());
        } else {
            // handle error
            return;
        }

        QString strURL_2 = "https://restapi.amap.com/v3/geocode/geo?key=56d764b33d43a413e390852cc7a1e457&address=" + ui->txtEnd->text();
        QUrl url_2(strURL_2);
        QNetworkRequest request_2(url_2);

        QNetworkReply *reply_2 = manager->get(request_2);
        connect(reply_2, &QNetworkReply::finished, [=](){
            QByteArray result_2 = reply_2->readAll();
            if(reply_2->error() == QNetworkReply::NoError) {
                // handle no error
                QJsonDocument jsonDoc = QJsonDocument::fromJson(result_2);
                QJsonObject jsonObject;
                if(!jsonDoc.isNull() && jsonDoc.isObject()) {
                    jsonObject = jsonDoc.object();
                }
                QJsonObject geocodesFirst = jsonObject["geocodes"].toArray().at(0).toObject();
                endLocation = geocodesFirst["location"].toString();
            } else {
                // handle error
                return;
            }

            if (startLocation == ""){
                startLocation = "116.403124,39.940693";
            }
            finalStrUrl = "https://m.amap.com/navi/?start=" + startLocation + "&dest=" + endLocation +"&destName=到这里去&key=34109fa4ffe916d6a8069f7c80b09811&jscode=fb3f824211d5cf58b17efbacf1d66c20";
            ui->mapView->setUrl(QUrl(finalStrUrl));
        });
    });
}

void CarGPS::getKeyWord(int mode){
    // http request
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QString strURL;
    qDebug() << "GETKEYWORD";
    if (isSlotClick){
        isSlotClick = false;
        return;
    }
//    QStringList nameList;
//    nameList.insert(0, "abc");
//    QStringListModel *listModel = new QStringListModel(nameList);
//    QFont font("Arial", 18);
//    ui->keyWordList->setModel(listModel);
//    ui->keyWordList->setFont(font);
//    ui->keyWordList->show();
//    ui->keywordWidget->show();
//    return;

    // define url request api
    if (mode == 0){
        strURL = "https://restapi.amap.com/v3/assistant/inputtips?output=json&city=010&keywords=" + ui->txtSearch->text() + "&key=00136427ed3a9ce94960c94af107cb38";
    }
    else if (mode == 1){
        strURL = "https://restapi.amap.com/v3/assistant/inputtips?output=json&city=010&keywords=" + ui->txtStart->text() + "&key=00136427ed3a9ce94960c94af107cb38";
    }
    else if (mode == 2){
        strURL = "https://restapi.amap.com/v3/assistant/inputtips?output=json&city=010&keywords=" + ui->txtEnd->text() + "&key=00136427ed3a9ce94960c94af107cb38";
    }
    QUrl url(strURL);
    QNetworkRequest request(url);

    // use get method request
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, [=](){
        QByteArray result = reply->readAll();
        if(reply->error() == QNetworkReply::NoError) {
            // handle no error
            QJsonDocument jsonDoc = QJsonDocument::fromJson(result);
            QJsonObject jsonObject;
            if(!jsonDoc.isNull() && jsonDoc.isObject()) {
                 jsonObject = jsonDoc.object();
            }
            QList<QJsonObject> tipsList;
            QStringList nameList;
            for (int i = 0; i < 6; i++){
                 tipsList.insert(i, jsonObject["tips"].toArray().at(i).toObject());
                 nameList.insert(i, tipsList[i]["name"].toString());
            }
            QStringListModel *listModel = new QStringListModel(nameList);
            QFont font("Arial", 18);
            ui->keyWordList->setModel(listModel);
            ui->keyWordList->setFont(font);
            ui->keyWordList->show();
            ui->keywordWidget->show();
        } else {
            // handle error
            return;
        }
    });
}

void CarGPS::on_txtSearch_textChanged(const QString &arg1)
{
    txtMode = 1;
    if (arg1.isEmpty()){
        ui->keyWordList->hide();
        ui->keywordWidget->hide();
        return;
    }
    if (arg1.length() % 2 == 0){
        return;
    }
    getKeyWord(0);

}

void CarGPS::on_txtStart_textChanged(const QString &arg1)
{
    qDebug() << "START";
    txtMode = 2;
    if (arg1.isEmpty()){
        ui->keyWordList->hide();
        ui->keywordWidget->hide();
        return;
    }
    if (arg1.length() % 2 == 0){
        return;
    }
    getKeyWord(1);
}


void CarGPS::on_txtEnd_textChanged(const QString &arg1)
{
    qDebug() << "END";
    txtMode = 3;
    if (arg1.isEmpty()){
        ui->keyWordList->hide();
        ui->keywordWidget->hide();
        return;
    }
    if (arg1.length() % 2 == 0){
        return;
    }
    getKeyWord(2);
}


void CarGPS::on_txtSearch_editingFinished()
{
    ui->keyWordList->hide();
    ui->keywordWidget->hide();
}


void CarGPS::on_txtStart_editingFinished()
{
    ui->keyWordList->hide();
    ui->keywordWidget->hide();
}


void CarGPS::on_txtEnd_editingFinished()
{
    ui->keyWordList->hide();
    ui->keywordWidget->hide();
}


void CarGPS::on_pushButton_2_clicked()
{
    emit tell_close();
    deleteLater();
}


