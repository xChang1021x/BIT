#ifndef REGISTERLOGIN_H
#define REGISTERLOGIN_H

#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QWidget>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class RegisterLogin; }
QT_END_NAMESPACE

class RegisterLogin : public QWidget
{
    Q_OBJECT

public:
    RegisterLogin(QWidget *parent = nullptr);
    ~RegisterLogin();
    void requestCheckCodeImage(int);
    int clicked();

private slots:
    void on_loginBtn_clicked();

    void on_noAccBtn_clicked();

    void on_haveAccBtn_clicked();

    void on_getEmailCodeBtn_clicked();

    void on_registerBtn_clicked();

    bool eventFilter(QObject *watched, QEvent *event);

    void on_pushButton_clicked();

signals:
    void loginSuccess(QJsonObject);
    void registerSuccess(QString, QByteArray);
    void tell_close();

private:
    Ui::RegisterLogin *ui;
    QString checkCodeKey;
    QNetworkAccessManager *manager;
    QString baseUrl;
};
#endif // REGISTERLOGIN_H
