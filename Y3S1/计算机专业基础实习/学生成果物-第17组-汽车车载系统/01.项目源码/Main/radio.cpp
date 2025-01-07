#include "radio.h"
#include "ui_radio.h"

#include <QPropertyAnimation>


Radio::Radio(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Radio)
{
    ui->setupUi(this);
//    ui->labelBackgroundPanel->setStyleSheet("background-image: url(:/radioTv.png); background-repeat: no-repeat;");

    QString fmId = "489";
    ui->FmPLayer->setUrl(QUrl("https://sao.fm/api/fm/?id=" + fmId));

    radioStation = {
        {"489","广东音乐之声"},
        {"490","广东文体广播"},
        {"491","广东城市之声"},
        {"492","广东珠江之声"},
        {"493","广东珠江经济台"},
        {"494","广东南方生活广播"},
        {"495","广东羊城交通广播"},
        {"497","深圳交通频率"},
        {"498","深圳电台 飞扬971"},
        {"499","深圳电台 生活942"},
        {"506","江西新闻广播"},
        {"507","江西财广播"},
        {"508","江西交通广播"},
        {"509","江西音乐广播"},
        {"510","江西都市广播"},
        {"512","江西民生广播"},
        {"513","江西农村广播"},
        {"516","山东交通广播"},
        {"520","山东体育休闲广播"},
        {"522","山东乡村广播"},
        {"523","湖南金鹰955"},
        {"524","芒果时空音乐台"},
        {"525","湖南新闻频道"},
        {"526","湖南电台潇湘之声"},
        {"527","湖北之声"},
        {"528","湖北农村广播"},
        {"529","楚天交通"},
        {"532","湖北经济广播"},
        {"533","湖北楚天音乐"},
        {"534","湖北经典音乐"},
        {"535","湖北城市之声"},
        {"541","海南新闻广播"},
        {"542","海南交通广播"},
        {"543","海南音乐广播"},
        {"544","吉林新闻综合广播"},
        {"545","吉林经济广播"},
        {"546","吉林交通广播"},
        {"547","吉林乡村广播"},
        {"548","延边新闻广播"},
        {"549","延边文艺生活广播"},
        {"550","黑龙江新闻广播"},
        {"551","黑龙江都市女性广播"},
        {"552","黑龙江音乐广播"},
        {"553","黑龙江高校广播"},
        {"554","黑龙江朝语广播"},
        {"555","黑龙江爱家频道广播"},
        {"557","黑龙江交通广播"},
        {"558","黑龙江私家车频道广播"},
        {"559","陕西新闻广播"},
        {"560","陕西经济广播"},
        {"561","陕西音乐广播"},
        {"562","陕西戏曲广播"},
        {"563","陕西交通广播"},
        {"564","陕西农村广播"},
        {"565","陕西青少广播"},
        {"566","陕西都市广播"},
        {"567","榆林新闻综合广播"},
        {"570","营口新闻综合广播"},
        {"571","内蒙古交通之声广播"},
        {"572","内蒙古音乐之声"},
        {"573","内蒙古评书曲艺广播"},
        {"574","内蒙古绿野之声广播"},
        {"575","内蒙古蒙古语广播"},
        {"576","内蒙古新闻综合广播"},
        {"577","内蒙古经济生活广播"},
        {"578","锡林郭勒汉语新闻综合广播"},
        {"579","锡林郭勒蒙语新闻综合广播"},
        {"580","阿拉善汉语广播"},
        {"581","阿拉善蒙语广播"},
        {"582","呼伦贝尔汉语广播"},
        {"583","呼伦贝尔蒙语广播"},
        {"584","鄂尔多斯新闻综合广播"},
        {"585","广西交通广播"},
        {"586","广西私家车930"},
        {"587","广西经济广播"},
        {"589","广西对外广播"},
        {"590","广西音乐台"},
        {"591","云南新闻广播"},
        {"592","云南音乐广播"},
        {"593","云南经济广播"},
        {"594","云南交通广播"},
        {"595","云南旅游广播"},
        {"596","云南民族广播"},
        {"597","云南国际广播"},
        {"598","云南教育广播"},
    };

    // 创建动画对象
    QPropertyAnimation *translationAnimation = new QPropertyAnimation(ui->labelMusic_1, "pos");
    // 设置动画的持续时间
    translationAnimation->setDuration(2000);
    // 设置动画的起始值（控件的当前位置）
    QPoint startPosition = ui->labelMusic_1->pos();
    translationAnimation->setStartValue(startPosition);
    // 设置动画的结束值
    QPoint endPosition = startPosition - QPoint(200, 200); // 向左移动200px，向上移动200px
    translationAnimation->setEndValue(endPosition);
    // 设置动画循环次数为无限
    translationAnimation->setLoopCount(-1);
    // 开始动画
    translationAnimation->start();


    QPropertyAnimation *translationAnimation2 = new QPropertyAnimation(ui->labelMusic_2, "pos");
    translationAnimation2->setDuration(2500);
    QPoint startPosition2 = ui->labelMusic_2->pos();
    translationAnimation2->setStartValue(startPosition2);
    QPoint endPosition2 = startPosition - QPoint(-700, 200);
    translationAnimation2->setEndValue(endPosition2);
    translationAnimation2->setLoopCount(-1);
    translationAnimation2->start();
}

Radio::~Radio()
{
    delete ui;
}

void Radio::sliderStopedMove() {
    QString fmId = QString::number(ui->dial->sliderPosition());
    if(!radioStation.contains(fmId)) {
        ui->label->setText("");
        ui->label_2->setText("");
        ui->label_3->setText("");
        ui->label_5->setText("");
        ui->widgetTV->setStyleSheet("background-color: none;");
        return;
    }
    ui->widgetTV->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0.498, y1:0, x2:0.651, y2:1, stop:0 rgba(224, 160, 0, 255), stop:1 rgba(255, 255, 255, 255));");
    ui->label->setText(radioStation.value(fmId));
    ui->label_3->setText("正在播放:");
    ui->label_5->setText("转台过程需要一点时间");
    ui->FmPLayer->setUrl(QUrl("https://sao.fm/api/fm/?id=" + fmId));
}

void Radio::on_dial_sliderReleased()
{
//    qDebug() << ui->dial->sliderPosition();
    Radio::sliderStopedMove();
}


void Radio::on_dial_valueChanged(int value)
{
    ui->label_2->setText(QString::number(value));
}

void Radio::on_pushButton_clicked()
{
    emit tell_close();
    deleteLater();
}

