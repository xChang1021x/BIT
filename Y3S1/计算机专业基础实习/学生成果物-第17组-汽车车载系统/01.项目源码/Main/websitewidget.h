#ifndef WEBSITEWIDGET_H
#define WEBSITEWIDGET_H

#include <QTabWidget>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class WebsiteWidget; }
QT_END_NAMESPACE

class WebsiteWidget : public QWidget
{
    Q_OBJECT
signals:
    void tell_close();
public:
    WebsiteWidget(QWidget *parent = nullptr);
    ~WebsiteWidget();
//    void tabBarClicked();

private slots:
    void on_tabWidget_tabBarClicked(int index);

    void on_tabWidget_tabBarDoubleClicked(int index);

private:
    Ui::WebsiteWidget *ui;
    bool isOkDelete;
//    QTabWidget *tabWidget;
};
#endif // WEBSITEWIDGET_H
