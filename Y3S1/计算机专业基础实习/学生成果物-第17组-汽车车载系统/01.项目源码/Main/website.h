#ifndef WEBSITE_H
#define WEBSITE_H

#include <QWebEngineView>
#include <QTabWidget>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Website; }
QT_END_NAMESPACE

class Website : public QWidget
{
    Q_OBJECT
signals:
    void tell_close();
public:
    Website(QWidget *parent = nullptr);

    ~Website();
//    void tabBarClicked();

private slots:

    void on_backButton_clicked();

    void on_forwardButton_clicked();

    void on_reflashButton_clicked();

private:
    Ui::Website *ui;
//    QTabWidget *tabWidget;
};

#endif // WEBSITE_H
