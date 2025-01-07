#ifndef BG_H
#define BG_H

#include <QWebEngineView>
#include <QTabWidget>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Bg; }
QT_END_NAMESPACE

class Bg : public QWidget
{
    Q_OBJECT

public:
    Bg(QWidget *parent = nullptr, int i = 0);

    ~Bg();
//    void tabBarClicked();
signals:
    void tell_close();


private slots:
    void on_close_window();

private:
    Ui::Bg *ui;
//    QTabWidget *tabWidget;
};


#endif // BG_H
