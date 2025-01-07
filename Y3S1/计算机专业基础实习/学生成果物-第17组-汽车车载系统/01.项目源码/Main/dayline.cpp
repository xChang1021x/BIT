#include "dayline.h"
#include <QJsonObject>
#include <QPainter>
#include <QJsonArray>
#include <QJsonArray>
#include <QDebug>

DayLine::DayLine(QWidget *parent) : QWidget(parent) {
    // 初始化代码
}

DayLine::DayLine(QJsonObject jsonObject) {
    // 初始化代码
    firstObject = jsonObject;
}

DayLine::DayLine(QJsonArray jsonDataArray) {
    // 初始化代码
    this->jsonDataArray = jsonDataArray;
}

void DayLine::paintEvent(QPaintEvent *event) {
    if(firstObject.isEmpty()) {
        QPainter painter(this);

        painter.setBrush(Qt::yellow);
        painter.setPen(Qt::yellow);

        int showLinePerDayCount = 7;
        int avgTem = 0;
        for(int i = 0; i < 7; ++i) {
            avgTem += jsonDataArray.at(i).toObject().value("tem").toString().toInt();
            qDebug() << jsonDataArray.at(i);
        }
        QPoint points[7];
        int per = this->width() / (showLinePerDayCount);
        avgTem /= showLinePerDayCount;
        for(int i = 0; i < showLinePerDayCount; ++i) {
            //        qDebug() << objectHours;
            points[i].setX(per * (i+1) - 50);
            //        qDebug() << points[i].x();
            points[i].setY(this->height()/2 + (avgTem - jsonDataArray.at(i).toObject().value("tem").toString().toInt()));
                    qDebug() << points[i].y();

            painter.drawEllipse(QPoint(points[i]), 2, 2);
            QFont font = this->font();
            font.setPointSize(12);
            painter.setFont(font);
            painter.drawText(QPoint(points[i].x()-10, points[i].y() - 10), jsonDataArray.at(i).toObject().value("tem").toString());
        }

        for(int i = 1; i < showLinePerDayCount; i++){
            painter.drawLine(points[i-1], points[i]);
        }
    } else {
        QPainter painter(this);
        // 您的绘制代码
        painter.setBrush(Qt::yellow);
        painter.setPen(Qt::yellow);
        //    painter.drawLine(QPoint(10,10), QPoint(700,20));
        //    ui->widgetDays->hide();
        //    ui->widgetCenter->hide();
        //    ui->widgetTop->hide();
        //    ui->dayLine->show();
        int showLinePerDayCount = 24;
        int avgTem = 0;
        for(int i = 0; i < 24; ++i) {
            QJsonObject objectHours = firstObject["hours"].toArray()[i].toObject();
            if(objectHours["tem"].toString() == "") {
                showLinePerDayCount = i;
                break;
            }
            avgTem += objectHours["tem"].toString().toInt();
        }
        QPoint points[24];
        int per = this->width() / (showLinePerDayCount + 1);
        avgTem /= showLinePerDayCount;
        for(int i = 0; i < showLinePerDayCount; ++i) {
            QJsonObject objectHours = firstObject["hours"].toArray()[i].toObject();
            //        qDebug() << objectHours;
            points[i].setX(per * (i+1));
            //        qDebug() << points[i].x();
            points[i].setY(this->height()/2 + (avgTem - objectHours["tem"].toString().toInt())*2);
//                    qDebug() << points[i].y();

            painter.drawEllipse(QPoint(points[i]), 2, 2);
            QFont font = this->font();
            font.setPointSize(12);
            painter.setFont(font);
            painter.drawText(QPoint(points[i].x()-10, points[i].y() - 10), objectHours["tem"].toString());
            painter.drawText(QPoint(points[i].x()-10, this->height()/2 + 40), objectHours["hours"].toString().left(2));
        }

        for(int i = 1; i < showLinePerDayCount; i++){
            //        qDebug() << points[i-1];
            //        qDebug() << points[i];
            painter.drawLine(points[i-1], points[i]);
        }
        //    resize(800, 601);
    }

}

