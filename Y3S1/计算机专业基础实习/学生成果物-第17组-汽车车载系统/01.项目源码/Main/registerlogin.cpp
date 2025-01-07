#include "registerlogin.h"
#include "ui_registerlogin.h"

#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
#include <QImage>
#include <QJsonObject>
#include <QTimer>
#include <QBuffer>

RegisterLogin::RegisterLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterLogin)
{
    ui->setupUi(this);
    ui->passwordText->setEchoMode(QLineEdit::Password);
    ui->RegisterPasswordText->setEchoMode(QLineEdit::Password);
    ui->rAvatarLabel->installEventFilter(this);
    QPixmap defaultAvatar(":/默认.png");
    ui->rAvatarLabel->setPixmap(defaultAvatar.scaled(ui->rAvatarLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    baseUrl = "http://192.168.130.13:8080";

    requestCheckCodeImage(1);
}

RegisterLogin::~RegisterLogin()
{
    delete ui;
}

QJsonObject convertJsonStringToObj(QByteArray result) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(result);
    if(!jsonDoc.isNull() && jsonDoc.isObject()) {
        return jsonDoc.object();
    }
    return {};
}

void RegisterLogin::on_loginBtn_clicked()
{
    QString email = ui->emailText->text();
    QString password = ui->passwordText->text();
    QString checkCode = ui->checkCodeText->text();

    QString MD5;
    QByteArray str;
    str = QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Md5);
    MD5.append(str.toHex());

    QString strURL = baseUrl + "/api/userInfo/login?email=" + email + "&password=" + MD5 + "&checkCode=" + checkCode + "&key=" + checkCodeKey;
    QUrl url(strURL);
    QNetworkRequest request(url);

    // http request
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // use get method request
    QNetworkReply *reply = manager->get(request);

    // 对reply进行绑定, invoke method readHttpReply
    QObject::connect(manager, &QNetworkAccessManager::finished,
                     this, [=]() {
        QByteArray result;
        if(reply->error() == QNetworkReply::NoError) {
            // handle no error
            result = reply->readAll();
        } else {
            // handle error
            QMessageBox::warning(this, "error", reply->errorString());
            return;
        }
        // 对于Json
        QJsonObject jsonObject = convertJsonStringToObj(result);

        //        qDebug() << jsonObject;
        if(jsonObject["code"].toDouble() != 200) {
            QMessageBox::warning(this, "error", jsonObject["info"].toString());
            return;
        }

        QJsonObject jsonData = jsonObject["data"].toObject();
        // TODO:do something when get result
        // {"createTime":"2024-08-26 23:56:28","email":"1820221050@bit.edu.cn","joinType":0,"lastLoginTime":"2024-08-27 13:46:00","lastOffTime":null,"nickName":"新世界的神","password":"0192023a7bbd73250516f069df18b500","personalSignature":null,"phone":"18111111112","sex":null,"userId":"4665322800"}
        //        qDebug() << jsonData;

        emit loginSuccess(jsonData);

        QTimer::singleShot(0, this, &QObject::deleteLater);
    });
}

void RegisterLogin::requestCheckCodeImage(int type) {
    // type == 0 : register, type == 1 : login

    // TODO:define url request api
    QString strURL = baseUrl + "/api/userInfo/checkCode";
    QUrl url(strURL);
    QNetworkRequest request(url);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // use get method request
    QNetworkReply *reply = manager->get(request);

    // 对reply进行绑定, invoke method readHttpReply
    QObject::connect(manager, &QNetworkAccessManager::finished,
                     this, [=]() {
        QByteArray result;
        if(reply->error() == QNetworkReply::NoError) {
            // handle no error
            result = reply->readAll();
        } else {
            // handle error
            QMessageBox::warning(this, "error", reply->errorString());
            return;
        }
        // 对于Json
        QJsonObject jsonObject = convertJsonStringToObj(result);
        // TODO:do something when get result
        //        qDebug() << jsonObject;
        QJsonObject jsonData = jsonObject["data"].toObject();
        //        qDebug() << jsonData;
        checkCodeKey = jsonData["check_code_key"].toString();
        QString checkCodeImage = jsonData["check_code"].toString();
        // 对于图片流
        QString base64String = checkCodeImage.remove("data:image/png;base64,");

        // 将Base64编码的字符串转换为QByteArray
        QByteArray base64Data = base64String.toUtf8();

        // 对Base64编码的QByteArray进行解码
        QByteArray imageBuffer = QByteArray::fromBase64(base64Data);

        QImage image;
        if(image.loadFromData(imageBuffer)) {
            // 显示图片
            if(type == 0) {
                ui->RegisterCheckCodeImg->setPixmap(QPixmap::fromImage(image).scaled(130, 38, Qt::KeepAspectRatio));
            } else if(type == 1) {
                ui->checkCodeImg->setPixmap(QPixmap::fromImage(image).scaled(130, 38, Qt::KeepAspectRatio));
            }
        } else {
            QMessageBox::warning(this, "Error", "Cannot load image from data.");
            return;
        }
    });
}


void RegisterLogin::on_noAccBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    requestCheckCodeImage(0);
}


void RegisterLogin::on_haveAccBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    requestCheckCodeImage(1);
}


void RegisterLogin::on_getEmailCodeBtn_clicked()
{
    QString email = ui->RegisterEmailText->text();
    QString checkCode = ui->RegisterCheckCodeText->text();

    QString strURL = baseUrl + "/api/sendEmailCode?email=" + email + "&checkCode=" + checkCode + "&key=" + checkCodeKey;
    QUrl url(strURL);
    QNetworkRequest request(url);

    // http request
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // use get method request
    QNetworkReply *reply = manager->get(request);

    // 对reply进行绑定, invoke method readHttpReply
    QObject::connect(manager, &QNetworkAccessManager::finished,
                     this, [=]() {
        QByteArray result;
        if(reply->error() == QNetworkReply::NoError) {
            // handle no error
            result = reply->readAll();
        } else {
            // handle error
            QMessageBox::warning(this, "error", reply->errorString());
            return;
        }
        // 对于Json
        QJsonObject jsonObject = convertJsonStringToObj(result);

        //        qDebug() << jsonObject;
        if(jsonObject["code"].toDouble() != 200) {
            QMessageBox::warning(this, "error", jsonObject["info"].toString());
            return;
        } else {
            QMessageBox::information(this, "send success", jsonObject["info"].toString());
            return;
        }
    });
}


void RegisterLogin::on_registerBtn_clicked()
{
    QString email = ui->RegisterEmailText->text();
    QString password = ui->RegisterPasswordText->text();
    QString checkCode = ui->RegisterCheckCodeText->text();
    QString username = ui->RegisterNickNameText->text();
    QString phone = ui->RegisterPhoneText->text();
    QString emailCode = ui->RegisterEmailCodeText->text();
    QString MD5;
    QByteArray str;
    str = QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Md5);
    MD5.append(str.toHex());

    QString strURL = baseUrl + "/api/userInfo/register?email=" + email + "&password=" + MD5 + "&checkCode=" + checkCode + "&username="+ username+"&phone="+phone + "&emailCode=" +emailCode + "&key=" + checkCodeKey;
    QUrl url(strURL);
    QNetworkRequest request(url);

    QByteArray avatarData;
    const QPixmap* avatarPixmap = ui->rAvatarLabel->pixmap();
    QBuffer buffer(&avatarData);
    buffer.open(QIODevice::WriteOnly);
    avatarPixmap->save(&buffer, "PNG");  // 保存为PNG格式

    // http request
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // use get method request
    QNetworkReply *reply = manager->get(request);

    // 对reply进行绑定, invoke method readHttpReply
    QObject::connect(manager, &QNetworkAccessManager::finished,
                     this, [=]() {
        QByteArray result;
        if(reply->error() == QNetworkReply::NoError) {
            // handle no error
            result = reply->readAll();
        } else {
            // handle error
            QMessageBox::warning(this, "error", reply->errorString());
            return;
        }
        // 对于Json
        QJsonObject jsonObject = convertJsonStringToObj(result);

        //        qDebug() << jsonObject;
        if(jsonObject["code"].toDouble() != 200) {
            QMessageBox::warning(this, "error", jsonObject["info"].toString());
            return;
        }

        QString jsonData = jsonObject["data"].toString();

        emit registerSuccess(jsonData, avatarData);

        ui->stackedWidget->setCurrentIndex(0);
        requestCheckCodeImage(1);

        ui->RegisterCheckCodeText->clear();
        ui->RegisterEmailCodeText->clear();
        ui->RegisterEmailText->clear();
        ui->RegisterNickNameText->clear();
        ui->RegisterPasswordText->clear();
        ui->RegisterPhoneText->clear();
        ui->checkCodeText->clear();
    });
}

bool RegisterLogin::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->rAvatarLabel && event->type() == QEvent::MouseButtonPress) {
        // 弹出文件选择对话框
        QString fileName = QFileDialog::getOpenFileName(this, "Select Avatar", "", "Images (*.png *.jpg *.bmp)");
        if (!fileName.isEmpty()) {
            QPixmap avatarPixmap(fileName);
            ui->rAvatarLabel->setPixmap(avatarPixmap.scaled(ui->rAvatarLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        return true; // 事件已处理
    }
    return QWidget::eventFilter(watched, event);
}


void RegisterLogin::on_pushButton_clicked()
{
    emit tell_close();
    deleteLater();
}

