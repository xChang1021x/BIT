#ifndef CARGPS_H
#define CARGPS_H

#include <QWidget>
#include <QTimer>
#include <QWebChannel>
#include <QWebEngineView>
#include <QDebug>
#include <QNetworkReply>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGeoLocation>

QT_BEGIN_NAMESPACE
namespace Ui { class CarGPS; }
QT_END_NAMESPACE

enum SearchingMode {
    DIRECTION_MODE,
    NEARBY_MODE
};

class CarGPS : public QWidget
{
    Q_OBJECT

public:
    CarGPS(QWidget *parent = nullptr);
    ~CarGPS();
    int searchMode;
    int txtMode;
    int isFinish;
    bool isSlotClick;
    QString finalStrUrl;
    QString startLocation;
    QString endLocation;

private slots:
    void on_btnMenu_clicked();

    void on_txtSearch_returnPressed();

    void on_txtSearch_textChanged(const QString &arg1);

    void slotClicked(const QModelIndex&);

    void on_btnDirectionMode_clicked();

    void on_btnNearbyMode_clicked();

    void on_pushButton_clicked();

    void on_txtStart_textChanged(const QString &arg1);

    void on_txtEnd_textChanged(const QString &arg1);

    void getKeyWord(int mode);

    void on_txtSearch_editingFinished();

    void on_txtStart_editingFinished();

    void on_txtEnd_editingFinished();

    void on_pushButton_2_clicked();
signals:
    void tell_close();
private:
    Ui::CarGPS *ui;
};
#endif // CARGPS_H
