#ifndef WECHAT_H
#define WECHAT_H

#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QBuffer>
#include <QListWidgetItem>
#include <QCloseEvent>
#include <QUdpSocket>
#include <QRandomGenerator>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QNetworkReply>
#include <QFileIconProvider>

QT_BEGIN_NAMESPACE
namespace Ui { class WeChat; }
QT_END_NAMESPACE

class User {
public:
    QString id;
    QString name;
    QString tel;
    QByteArray avatarData;
    QString status;

    User(){};
    User(QString id, const QString &name, const QString &tel, QByteArray avatarData) {
        this->id = id;
        this->name = name;
        this->tel = tel;
        this->avatarData = avatarData;
    }
};

class WeChat : public QWidget
{
    Q_OBJECT

public:
    WeChat(QWidget *parent = nullptr);
    ~WeChat();
    void loadUserInfo();
    //    void showLogin();
    void loadFriendList(QList<User>);
    void sendLoginRequest(QJsonObject);
    void sendRegisterRequest(const QString& userName, const QString& password, const QString& telNo, QByteArray avatarData);
    void getFriendListRequest();
    void processJsonObject(const QJsonObject &response);
    void processJsonArray(const QJsonArray &array);
    QString generateRandomMulticastAddress();
    quint16 generateRandomPort();
    QPixmap getUserAvatar();
    QString getUserName();

private slots:
    void onFriendlistSelected(QListWidgetItem* item);
    void onServerResponse();
    void onQuitBtnClicked();
    void onSendMessageRequest();
    void onSendPictureRequest();
    void onCreateGroupChat();
    void onGroupChatListSelected(QListWidgetItem* item);
    void onGroupResponse();
    void onGroupSendMessage();
    void onGroupSendPicture();
    void onAddFriend();
    void onExitGroup();
    void onRegisterLogin(QString, QByteArray);
    void on_window_close();
    void onItemClicked(QListWidgetItem* item);
    void onGroupSendFile();

signals:
    void aboutToClose();  // 定义一个信号
    void tell_close();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::WeChat *ui;
    QTcpSocket *socket;
    User myUser;
    QString friendName;
    QUdpSocket *uSocket;
    QString multicastAddress;  // 用于存储组播地址
    quint16 multicastPort;
    QSqlDatabase db;
    QString baseUrl;
};


#endif // WECHAT_H
