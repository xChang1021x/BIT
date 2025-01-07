#ifndef DAYLINE_H
#define DAYLINE_H

// dayline.h
#include <QJsonArray>
#include <QJsonObject>
#include <QWidget>

class DayLine : public QWidget {
    Q_OBJECT

public:
    explicit DayLine(QWidget *parent = nullptr);
    DayLine(QJsonObject);
    DayLine(QJsonArray);

protected:
    void paintEvent(QPaintEvent *event) override; // 实现绘制事件
signals:
    void tell_close();
private:
    QJsonObject firstObject;
    QJsonArray jsonDataArray;
};

#endif // DAYLINE_H

