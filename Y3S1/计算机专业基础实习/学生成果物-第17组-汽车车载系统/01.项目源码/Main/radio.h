#ifndef RADIO_H
#define RADIO_H

#include <QWidget>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class Radio; }
QT_END_NAMESPACE

class Radio : public QWidget
{
    Q_OBJECT

public:
    Radio(QWidget *parent = nullptr);
    ~Radio();
    void sliderStopedMove();
signals:
    void tell_close();
private slots:

    void on_dial_sliderReleased();

    void on_dial_valueChanged(int value);

    void on_pushButton_clicked();

private:
    Ui::Radio *ui;
    QMap<QString, QString> radioStation;
};
#endif // RADIO_H
