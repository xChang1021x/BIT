#include "ui_websitewidget.h"
#include "website.h"
#include "websitewidget.h"

#include <QMainWindow>
#include <QTabBar>
#include <QWebEngineView>
#include <QObject>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCheckBox>

WebsiteWidget::WebsiteWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WebsiteWidget)
{
    ui->setupUi(this);

    ui->tabWidget->removeTab(0);

    isOkDelete = false;

    QWidget *tab = new QWidget;

    QVBoxLayout *layout1 = new QVBoxLayout;

    layout1->addWidget(new Website);
    tab->setLayout(layout1);

    ui->tabWidget->insertTab(0, tab, QStringLiteral("new tab"));
    ui->tabWidget->setCurrentIndex(0);

}

WebsiteWidget::~WebsiteWidget()
{
    delete ui;
}

void WebsiteWidget::on_tabWidget_tabBarClicked(int index)
{
    if(index == ui->tabWidget->count() - 1) {
        QWidget *tab = new QWidget;

        QVBoxLayout *layout1 = new QVBoxLayout;

        layout1->addWidget(new Website);
        tab->setLayout(layout1);

        ui->tabWidget->insertTab(index, tab, QStringLiteral("new tab"));
    }
}

void WebsiteWidget::on_tabWidget_tabBarDoubleClicked(int index)
{
    if(!isOkDelete) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("提示");
        msgBox.setText("你确定要关闭吗？");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setCheckBox(new QCheckBox("不再提示"));

        int ret = msgBox.exec();

        if (ret == QMessageBox::Ok) {
            ui->tabWidget->removeTab(index);
        } else if (ret == QMessageBox::Cancel) {
            msgBox.close();
            return;
        }

        // 检查复选框是否被选中
        QCheckBox *checkBox = msgBox.checkBox();
        if (checkBox->isChecked()) {
            isOkDelete = true;
        }
    } else {
        ui->tabWidget->removeTab(index);
    }

    if(ui->tabWidget->currentIndex() == ui->tabWidget->count() - 1) {
        if(ui->tabWidget->currentIndex() == 0 && ui->tabWidget->count() - 1 == 0) {
            emit tell_close();
            deleteLater();
            return;
        }
        ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex() - 1);
    }
}

