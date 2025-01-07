#include "wechat.h"
#include "ui_wechat.h"
#include "registerlogin.h"

WeChat::WeChat(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WeChat)
{
    ui->setupUi(this);

    socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1", 12345);
    uSocket = new QUdpSocket();

    baseUrl = "http://192.168.130.13:8080";

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/chang/CarSystemModule/Main/qtSqLite/sqlite1.db");
    if (!db.open()) {
        qDebug() << "Failed to connect to database:" << db.lastError();
    } else {
        qDebug() << "Database connected!";
    }

    connect(socket, &QTcpSocket::readyRead, this, &WeChat::onServerResponse);//获取服务器的信号
    connect(uSocket, &QUdpSocket::readyRead, this, &WeChat::onGroupResponse);
    connect(ui->groupSendBtn, &QPushButton::clicked, this, &WeChat::onGroupSendMessage);



    ui->chatWidget->hide();
    ui->groupWidget->hide();

    setWindowTitle("mychat");

    //    showLogin();
    ui->widget->hide();
    RegisterLogin *registerLogin = new RegisterLogin(this);
    connect(registerLogin, &RegisterLogin::loginSuccess, this, &WeChat::sendLoginRequest);
    connect(registerLogin, &RegisterLogin::registerSuccess, this, &WeChat::onRegisterLogin);
    connect(registerLogin, &RegisterLogin::tell_close, this, &WeChat::on_window_close);

    ////连接每个ui界面对应的控件的信息与槽
    //+按钮
    connect(ui->searchBar, &QLineEdit::returnPressed, this, &WeChat::onAddFriend);
    connect(ui->exitBtn, &QPushButton::clicked, this, &WeChat::onQuitBtnClicked);
    connect(ui->friendList, &QListWidget::itemClicked, this, &WeChat::onFriendlistSelected);
    connect(ui->sendBtn, &QPushButton::clicked, this, &WeChat::onSendMessageRequest);
    connect(ui->sendPic, &QPushButton::clicked, this, &WeChat::onSendPictureRequest);
    connect(this, &WeChat::aboutToClose, this, &WeChat::onQuitBtnClicked);
    connect(ui->createGroupbtn, &QPushButton::clicked, this, &WeChat::onCreateGroupChat);
    connect(ui->groupChatList, &QListWidget::itemClicked, this, &WeChat::onGroupChatListSelected);
    connect(ui->groupSendBtn, &QPushButton::clicked, this, &WeChat::onGroupSendMessage);
    connect(ui->groupSendPic, &QPushButton::clicked, this, &WeChat::onGroupSendPicture);
    connect(ui->exitGroup, &QPushButton::clicked, this, &WeChat::onExitGroup);
    connect(ui->gChtDisplay, &QListWidget::itemClicked, this, &WeChat::onItemClicked);
    connect(ui->groupSendFile, &QPushButton::clicked, this, &WeChat::onGroupSendFile);
}

WeChat::~WeChat()
{
    delete ui;
}

void WeChat::onExitGroup() {
    QJsonObject obj;
    obj["type"] = "text";
    obj["data"] = myUser.name + " 已退出群聊";
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    uSocket->writeDatagram(data, QHostAddress(multicastAddress), multicastPort);
    ui->groupChatList->clear();
    ui->gChtDisplay->clear();
    ui->gMsgInput->clear();
    ui->groupWidget->hide();
    ui->chatWidget->hide();
    uSocket->leaveMulticastGroup(QHostAddress(multicastAddress));
    uSocket->close();
    multicastAddress = "";
    multicastPort = 0;
}

void WeChat::onAddFriend() {
    QString searchText = ui->searchBar->text();
    if (!searchText.isEmpty()) {
        QString strURL = baseUrl + "/api/userInfo/getUserInfoByUserId?userId=" + searchText;
        QUrl url(strURL);
        QNetworkRequest request(url);

        // http request
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        // use get method request
        QNetworkReply *reply = manager->get(request);
        connect(manager, &QNetworkAccessManager::finished,
                this, [=]() {
            QByteArray result;
            if(reply->error() == QNetworkReply::NoError) {
                // handle no error
                result = reply->readAll();
            } else {
                // handle error
                QMessageBox::warning(this, "error", reply->errorString());
                return;
            }
            // 对于Json
            QJsonObject jsonObject;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(result);
            if(!jsonDoc.isNull() && jsonDoc.isObject()) {
                jsonObject = jsonDoc.object();
            }
            //        qDebug() << jsonObject;
            if(jsonObject["code"].toDouble() != 200) {
                QMessageBox::warning(this, "error", jsonObject["info"].toString());
                return;
            }
            QJsonObject jsonData = jsonObject["data"].toObject();
            QString name = jsonData["nickName"].toString();

            QJsonObject obj;
            obj["type"] = "addfriend";
            obj["userid"] = searchText;
            obj["username"] = name;
            qDebug() << searchText << endl;
            QJsonDocument doc(obj);
            QByteArray data = doc.toJson(QJsonDocument::Compact);
            socket->write(data);
        });
    }
}

void WeChat::closeEvent(QCloseEvent *event) {
    emit aboutToClose();  // 发出信号
    event->accept();  // 接受关闭事件并继续关闭窗口
}

void WeChat::onGroupSendMessage() {
    QString a = ui->gMsgInput->toPlainText();
    if (a.isEmpty()) {
        return;
    }
    QString message = myUser.name + ": " + a + "\n";
    QJsonObject json;
    json["type"] = "text";
    json["data"] = message;

    QJsonDocument doc(json);
    QByteArray dataToSend = doc.toJson();
    uSocket->writeDatagram(dataToSend, QHostAddress(multicastAddress),multicastPort);

    // 清空输入框
    ui->gMsgInput->clear();
}

void WeChat::onGroupSendPicture() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!fileName.isEmpty()) {
        // 加载图片
        // 将图片转换为字节数据
        QPixmap pixmap(fileName);
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, "PNG"); // 将图片保存为 PNG 格式到字节数组中

        // 将图片数据编码为 Base64
        QString base64Image = QString::fromLatin1(byteArray.toBase64());

        // 构造 JSON 对象来包装图片数据
        QJsonObject json;
        json["type"] = "image";
        json["data"] = base64Image;
        json["sender"] = myUser.name + ": \n";

        // 序列化 JSON 对象
        QJsonDocument doc(json);
        QByteArray dataToSend = doc.toJson();

        // 通过 UDP 发送数据
        uSocket->writeDatagram(dataToSend, QHostAddress(multicastAddress), multicastPort);
        //        QListWidgetItem* item = new QListWidgetItem(ui->gChtDisplay);

        //        // 创建 QLabel 并设置图片
        //        QLabel* imageLabel = new QLabel();
        //        imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio)); // 调整图片大小

        //        // 将 QLabel 作为 QListWidgetItem 的 widget
        //        ui->gChtDisplay->setItemWidget(item, imageLabel);

        //        // 调整 QListWidgetItem 的大小以适应 QLabel
        //        item->setSizeHint(imageLabel->sizeHint());
    }
}

void WeChat::onGroupChatListSelected(QListWidgetItem* item) {
    ui->chatWidget->hide();
    ui->friendList->clearSelection();
    ui->groupWidget->show();
}

void WeChat::onCreateGroupChat() {
    if(multicastAddress != "" && multicastPort != 0) {
        QMessageBox::warning(this, "createGroup", "cannot create new Group");
        return;
    }

    multicastAddress = generateRandomMulticastAddress();
    multicastPort = generateRandomPort();


    QListWidgetItem* item = new QListWidgetItem(ui->groupChatList);

    QWidget* friendWidget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(friendWidget);

    QLabel* avatarLabel = new QLabel(friendWidget);
    QPixmap avatarPixmap(":/默认.png");
    avatarLabel->setPixmap(avatarPixmap.scaled(50, 50, Qt::KeepAspectRatio));
    avatarLabel->setObjectName("avatarLabel");  // 设置 objectName
    // 设置名称标签
    QLabel* nameLabel = new QLabel("new group chat", friendWidget);
    nameLabel->setObjectName("nameLabel");  // 设置 objectName
    QPushButton* addBtn = new QPushButton();
    layout->addWidget(avatarLabel);
    layout->addWidget(nameLabel);
    layout->addWidget(addBtn);
    friendWidget->setLayout(layout);
    item->setSizeHint(friendWidget->sizeHint());
    connect(addBtn, &QPushButton::clicked, [=](){
        // 创建一个新的弹出窗口
        QDialog* dialog = new QDialog(this);
        dialog->setWindowTitle("Add Friend to Group Chat");

        QVBoxLayout* layout = new QVBoxLayout(dialog);
        int count = ui->friendList->count();
        for (int i = 0; i < count; ++i) {
            QListWidgetItem* item = ui->friendList->item(i);  // 获取每个 QListWidgetItem

            QWidget* friendWidget = ui->friendList->itemWidget(item);  // 获取与该 item 关联的 QWidget

            if (friendWidget) {
                qDebug() << "FrienWidget" << endl;
                // 查找 friendWidget 中的 onlineLabel
                QLabel* statusLabel = friendWidget->findChild<QLabel*>("statusLabel");
                if (statusLabel) {
                    QString statusText = statusLabel->property("status").toString();
                    if (statusText == "Online") {
                        // 创建新的好友项
                        QWidget* newFriendWidget = new QWidget(dialog);
                        QHBoxLayout* friendLayout = new QHBoxLayout(newFriendWidget);

                        // 复制现有的好友信息
                        QLabel* nameLabel = friendWidget->findChild<QLabel*>("nameLabel");
                        QLabel* originalAvatarLabel = friendWidget->findChild<QLabel*>("avatarLabel");
                        if (originalAvatarLabel) {
                            const QPixmap* avatarPixmap = originalAvatarLabel->pixmap();
                            if (avatarPixmap) {
                                QLabel* newAvatarLabel = new QLabel(newFriendWidget);
                                newAvatarLabel->setPixmap(*avatarPixmap);
                                friendLayout->addWidget(newAvatarLabel); // 将新头像标签添加到布局中
                            }
                        }

                        QLabel* friendNameLabel = new QLabel(nameLabel->text(), newFriendWidget);
                        friendLayout->addWidget(friendNameLabel);

                        // 添加按钮
                        QPushButton* addButton = new QPushButton("Add", newFriendWidget);
                        connect(addButton, &QPushButton::clicked, [=]() {
                            QJsonObject obj;
                            obj["username"] = myUser.name;
                            obj["type"] = "creategroup";
                            obj["address"] = multicastAddress;
                            qDebug() << multicastAddress << multicastPort;
                            obj.insert("port", static_cast<int>(multicastPort));
                            QString name = nameLabel->text();
                            obj["friendname"] = name;
                            QJsonDocument doc(obj);
                            QByteArray data = doc.toJson(QJsonDocument::Compact);
                            socket->write(data);
                        });
                        // 将标签和按钮添加到布局
                        friendLayout->addWidget(addButton);
                        newFriendWidget->setLayout(friendLayout);

                        // 将新项添加到弹出窗口布局中
                        layout->addWidget(newFriendWidget);
                    }
                }
            }
        }
        // 设置弹出窗口的布局
        dialog->setLayout(layout);  // 确保设置了对话框的布局
        // 显示弹出窗口
        dialog->exec();  // 确保显示对话框
    });
    ui->groupChatList->setItemWidget(item, friendWidget);
    ui->groupWidget->show();
    // 发送群聊创建成功的广播消息
    QString message = myUser.name + " 创建群聊\n";
    QJsonObject obj;
    obj["type"] = "text";
    obj["data"] = message;
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    uSocket->bind(QHostAddress::AnyIPv4, multicastPort, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    qDebug() << "create" << multicastAddress << " " << multicastPort;
    uSocket->joinMulticastGroup(QHostAddress(multicastAddress));
    uSocket->writeDatagram(data, QHostAddress(multicastAddress), multicastPort);
}

void WeChat::onItemClicked(QListWidgetItem* item) {
    // 检查是否存在文件数据
    QVariant fileDataVariant = item->data(Qt::UserRole);
    QVariant fileSizeVariant = item->data(Qt::UserRole + 1);

    // 如果 UserRole 数据不为空，表示这是一个文件项
    if (!fileDataVariant.isNull() && !fileSizeVariant.isNull()) {
        // 提取文件数据和文件名
        QByteArray fileData = fileDataVariant.toByteArray();
        QString fileName = item->text(); // 文件名从 item 的文本中获取

        // 提示用户保存文件
        QString saveFileName = QFileDialog::getSaveFileName(this, tr("Save File"), fileName);
        if (!saveFileName.isEmpty()) {
            QFile file(saveFileName);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(fileData);
                file.close();
                QMessageBox::information(this, tr("Success"), tr("File downloaded successfully!"));
            } else {
                QMessageBox::warning(this, tr("Error"), tr("Failed to save the file."));
            }
        }
    }
}

void WeChat::onGroupSendFile() {
    // 打开文件选择对话框
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select File to Send"), "", tr("All Files (*)"));
    QFile file(fileName);
    QByteArray fileData = file.readAll();
    file.close();
    QJsonObject jsonObject;
    jsonObject["type"] = "fileTransfer";
    jsonObject["fileName"] = QFileInfo(file.fileName()).fileName();
    jsonObject["fileSize"] = fileData.size();
    jsonObject["fileData"] = QString(fileData.toBase64());
    jsonObject["sender"] = myUser.name + ":";
    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Compact);
    uSocket->writeDatagram(jsonData, QHostAddress(multicastAddress),multicastPort);
}

void WeChat::onGroupResponse() {
    while (uSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(uSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        uSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        QJsonDocument doc = QJsonDocument::fromJson(datagram);
        QJsonObject json = doc.object();
        QString type = json["type"].toString();
        QString data = json["data"].toString();
        if (type == "image") {
            QString message = json["sender"].toString();
            QListWidgetItem* item = new QListWidgetItem(message, ui->gChtDisplay);
            ui->gChtDisplay->addItem(item);
            QListWidgetItem* pItem = new QListWidgetItem(ui->gChtDisplay);
            // 处理图片
            QByteArray imageData = QByteArray::fromBase64(data.toLatin1());
            QImage image;
            image.loadFromData(imageData);
            // 显示图片或其他处理
            QLabel* imageLabel = new QLabel;
            imageLabel->setPixmap(QPixmap::fromImage(image));
            // 将 QLabel 作为 QListWidgetItem 的 widget
            ui->gChtDisplay->setItemWidget(pItem, imageLabel);

            // 调整 QListWidgetItem 的大小以适应 QLabel
            pItem->setSizeHint(imageLabel->sizeHint());

        } else if (type == "text") {
            // 处理文本
            QListWidgetItem* item = new QListWidgetItem(data, ui->gChtDisplay);
            ui->gChtDisplay->addItem(item);
        } else {
            QString msg = json["sender"].toString();
            QListWidgetItem* item = new QListWidgetItem(msg, ui->gChtDisplay);
            ui->gChtDisplay->addItem(item);

            QString fileName = json["fileName"].toString();
            int fileSize = json["fileSize"].toInt();
            QByteArray fileData = QByteArray::fromBase64(json["fileData"].toString().toUtf8());
            // 创建 QWidget 作为容器
            QWidget* fileWidget = new QWidget(ui->gChtDisplay);
            QHBoxLayout* layout = new QHBoxLayout(fileWidget);

            // 创建 QLabel 以显示文件图标
            QLabel* iconLabel = new QLabel(fileWidget);
            QFileIconProvider iconProvider;
            QIcon fileIcon = iconProvider.icon(QFileInfo(fileName));
            iconLabel->setPixmap(fileIcon.pixmap(32, 32));

            // 创建 QLabel 以显示文件名
            QLabel* nameLabel = new QLabel(fileName, fileWidget);

            // 添加图标和文件名标签到布局
            layout->addWidget(iconLabel);
            layout->addWidget(nameLabel);

            // 设置小部件的布局
            fileWidget->setLayout(layout);

            // 创建 QListWidgetItem 并设置它的大小
            QListWidgetItem* fileItem = new QListWidgetItem(ui->gChtDisplay);
            fileItem->setSizeHint(fileWidget->sizeHint());

            // 将文件数据和大小存储在 item 中
            fileItem->setData(Qt::UserRole, fileData);
            fileItem->setData(Qt::UserRole + 1, fileSize);

            // 将自定义小部件设置为 QListWidgetItem 的显示组件
            ui->gChtDisplay->setItemWidget(fileItem, fileWidget);

            // 将文件项添加到 gChtDisplay 列表中
            ui->gChtDisplay->addItem(fileItem);
        }
    }
}

QString WeChat::generateRandomMulticastAddress() {
    // 组播地址范围：224.0.0.0 到 239.255.255.255
    int firstOctet = QRandomGenerator::global()->bounded(224, 240); // [224, 239]
    int secondOctet = QRandomGenerator::global()->bounded(0, 256);  // [0, 255]
    int thirdOctet = QRandomGenerator::global()->bounded(0, 256);   // [0, 255]
    int fourthOctet = QRandomGenerator::global()->bounded(1, 256);  // [1, 255]

    return QString("%1.%2.%3.%4").arg(firstOctet).arg(secondOctet).arg(thirdOctet).arg(fourthOctet);
}

quint16 WeChat::generateRandomPort() {
    return static_cast<quint16>(QRandomGenerator::global()->bounded(1024, 65535)); // 1024到65535之间的端口
}

//void WeChat::showLogin()
//{
//    ui->lTelLineEdit->setPlaceholderText("Tel");
//    ui->lPasswordLineEdit->setPlaceholderText("Password");
//    ui->lPasswordLineEdit->setEchoMode(QLineEdit::Password);

//    ////连接login窗口里对应的控件并且实现其功能
//    //login按钮
//    connect(ui->lLoginBtn, &QPushButton::clicked, [&]() {
//        QString telNo = ui->lTelLineEdit->text();
//        QString password = ui->lPasswordLineEdit->text();
//        ui->lPasswordLineEdit->clear();
//        if(telNo.isEmpty() || password.isEmpty()) {
//            QMessageBox::warning(this, "Login Error", "Telephone and password cannot be empty.");
//        }
//        else {
//            sendLoginRequest(telNo, password);
//        }
//    });
//    //register按钮
//    connect(ui->lRegisterBtn, &QPushButton::clicked, [&]() {
//        ui->stackedWidget_2->setCurrentIndex(1);

//        ui->rUsernameLineEdit->setPlaceholderText("Username");
//        ui->rTelLineEdit->setPlaceholderText("Tel");
//        ui->rPasswordLineEdit->setPlaceholderText("Password");
//        ui->rPasswordLineEdit->setEchoMode(QLineEdit::Password);
//        ui->rConfirmPassword->setPlaceholderText("Password");
//        ui->rConfirmPassword->setEchoMode(QLineEdit::Password);
//        ui->rAvatarLabel->installEventFilter(this);
//        QPixmap defaultAvatar(":/images/默认.png");
//        ui->rAvatarLabel->setPixmap(defaultAvatar.scaled(ui->rAvatarLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

//        connect(ui->rBackBtn, &QPushButton::clicked, [&]() {
//            ui->stackedWidget_2->setCurrentIndex(0); // 切换回登录页面
//        });

//        connect(ui->rConfirmBtn, &QPushButton::clicked, [&]() {
//            QString regUsername = ui->rUsernameLineEdit->text();
//            QString regTel = ui->rTelLineEdit->text();
//            QString regPassword = ui->rPasswordLineEdit->text();
//            QString regConfirmPassword = ui->rConfirmPassword->text();
//            QByteArray avatarData;
//            const QPixmap* avatarPixmap = ui->rAvatarLabel->pixmap();
//            QBuffer buffer(&avatarData);
//            buffer.open(QIODevice::WriteOnly);
//            avatarPixmap->save(&buffer, "PNG");  // 保存为PNG格式
//            if (!regUsername.isEmpty() && !regTel.isEmpty() && !regPassword.isEmpty() && !regConfirmPassword.isEmpty()) {
//                if(regPassword == regConfirmPassword) {
//                    sendRegisterRequest(regUsername, regPassword, regTel, avatarData);
//                }
//                else {
//                     QMessageBox::warning(this, "Register", "输入密码不一样");
//                }
//            } else {
//                QMessageBox::warning(this, "Register", "Username, telephone, or password cannot be empty!");
//            }
//        });
//    });
//}

void WeChat::loadFriendList(QList<User> friends) {
    ui->friendList->clear();
    for (const User& user : friends) {
        //        QListWidgetItem* item = new QListWidgetItem(ui->friendList);

        //            QWidget* friendWidget = new QWidget();
        //            QHBoxLayout* layout = new QHBoxLayout(friendWidget);

        //            // 主容器，用于放置头像和右上角的在线状态
        //            QWidget* avatarContainer = new QWidget(friendWidget);
        //            QVBoxLayout* avatarLayout = new QVBoxLayout(avatarContainer);

        //            QLabel* avatarLabel = new QLabel(avatarContainer);
        //            QPixmap avatarPixmap;
        //            QPixmap onlinePixmap;

        //            avatarPixmap.loadFromData(user.avatarData);
        //            onlinePixmap.loadFromData(user.online);

        //            avatarLabel->setPixmap(avatarPixmap.scaled(50, 50, Qt::KeepAspectRatio));
        //            avatarLabel->setObjectName("avatarLabel");

        //            // 放置在线状态图标的标签
        //            QLabel* onlineLabel = new QLabel(avatarContainer);
        //            onlineLabel->setPixmap(onlinePixmap.scaled(20, 20, Qt::KeepAspectRatio));
        //            onlineLabel->setObjectName("onlineLabel");

        //            // 设置在线状态图标在右上角
        //            QHBoxLayout* topLayout = new QHBoxLayout();
        //            topLayout->addStretch(); // 空白区域使得在线图标在右上角
        //            topLayout->addWidget(onlineLabel);

        //            avatarLayout->addLayout(topLayout);
        //            avatarLayout->addWidget(avatarLabel);

        //            avatarContainer->setLayout(avatarLayout);

        //            QLabel* nameLabel = new QLabel(user.name, friendWidget);
        //            nameLabel->setObjectName("nameLabel");

        //            layout->addWidget(avatarContainer);  // 添加头像容器
        //            layout->addWidget(nameLabel);
        //            friendWidget->setLayout(layout);
        //            item->setSizeHint(friendWidget->sizeHint());
        //            ui->friendList->setItemWidget(item, friendWidget);
        QListWidgetItem* item = new QListWidgetItem(ui->friendList);

        QWidget* friendWidget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(friendWidget);

        QLabel* avatarLabel = new QLabel(friendWidget);
        QPixmap avatarPixmap;
        avatarPixmap.loadFromData(user.avatarData);
        avatarLabel->setPixmap(avatarPixmap.scaled(50, 50, Qt::KeepAspectRatio));
        avatarLabel->setObjectName("avatarLabel");  // 设置 objectName
        QLabel* statusLabel = new QLabel(friendWidget);

        QString statusText;  // 状态文本
        QString s;
        if(user.status == "online") {
            s = ":/绿点.png";
            statusText = "Online";
        }
        else {
            s = ":/红点.png";
            statusText = "Offline";
        }
        QPixmap onlinePixmap(s);
        statusLabel->setPixmap(onlinePixmap.scaled(10, 10, Qt::KeepAspectRatio));
        statusLabel->setObjectName("statusLabel"); // 设置 objectName

        statusLabel->setProperty("status", statusText);  // 使用属性存储状态文本
        statusLabel->setVisible(true);  // 仅显示图标，不显示文本

        // 设置名称标签
        QLabel* nameLabel = new QLabel(user.name, friendWidget);
        nameLabel->setObjectName("nameLabel");  // 设置 objectName

        layout->addWidget(avatarLabel);
        layout->addWidget(nameLabel);
        layout->addWidget(statusLabel);
        friendWidget->setLayout(layout);
        item->setSizeHint(friendWidget->sizeHint());
        ui->friendList->setItemWidget(item, friendWidget);
    }
}


void WeChat::onFriendlistSelected(QListWidgetItem* item) {
    ui->groupWidget->hide();
    ui->groupChatList->clearSelection();
    ui->chatWidget->show();
    ui->chtDisplay->clear();
    QWidget* friendWidget = ui->friendList->itemWidget(item);
    QLabel* nameLabel = friendWidget->findChild<QLabel*>("nameLabel");
    QLabel* avatarLabel = friendWidget->findChild<QLabel*>("avatarLabel");
    QString friendName = nameLabel->text();
    // 在此处理点击事件，例如打开聊天窗口、显示好友详情等
    this->friendName = friendName;
    qDebug() << friendName << endl;
    QJsonObject obj;
    obj["type"] = "getid";
    obj["friendname"] = friendName;
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    socket->write(data);
    socket->flush();
}

void WeChat::onSendMessageRequest() {
    QString msg = ui->msgInput->toPlainText();
    if(msg == "") {
        return;
    }
    QJsonObject obj;
    obj["sendname"] = myUser.name;
    obj["type"] = "sendmessage";
    obj["typeItem"] = "text";
    obj["text"] = msg;
    obj["friendname"] = friendName;
    // 获取当前日期和时间
    QDateTime currentTime = QDateTime::currentDateTime();
    // 将时间转换为字符串格式（例如，"yyyy-MM-dd HH:mm:ss"）
    QString timestamp = currentTime.toString("yyyy-MM-dd HH:mm:ss");
    obj["time"] = timestamp;
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    socket->write(data);
    socket->flush();
    ui->msgInput->clear();
}

void WeChat::onSendPictureRequest() {
    // 打开文件选择对话框，选择图片文件
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!fileName.isEmpty()) {
        // 加载图片
        QPixmap pixmap(fileName);

        // 将图片转换为字节数据
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, "PNG"); // 保存为PNG格式
        QJsonObject obj;
        obj["type"] = "sendmessage";
        obj["typeItem"] = "picture";
        obj["sendname"] = myUser.name;
        QString base64String = QString::fromLatin1(byteArray.toBase64());
        obj["picture"] = base64String;
        obj["friendname"] = friendName;
        // 获取当前日期和时间
        QDateTime currentTime = QDateTime::currentDateTime();
        // 将时间转换为字符串格式（例如，"yyyy-MM-dd HH:mm:ss"）
        QString timestamp = currentTime.toString("yyyy-MM-dd HH:mm:ss");
        obj["time"] = timestamp;
        QJsonDocument doc(obj);
        QByteArray data = doc.toJson(QJsonDocument::Compact);
        socket->write(data);  // socket 是与服务器通信的 QTcpSocket 对象
        socket->flush();
    }
}

void WeChat::sendRegisterRequest(const QString &userName, const QString &password, const QString &telNo, QByteArray avatarData) {
    QJsonObject registerRequest;
    registerRequest["type"] = "Register";
    registerRequest["username"] = userName;
    registerRequest["tel"] = telNo;
    registerRequest["password"] = password;
    QString base64String = QString::fromLatin1(avatarData.toBase64());
    registerRequest["avatardata"] = base64String;

    QJsonDocument doc(registerRequest);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    socket->write(data);  // socket 是与服务器通信的 QTcpSocket 对象
    socket->flush();
}

void WeChat::sendLoginRequest(QJsonObject jsonData) {
    ui->widget->show();
    jsonData["type"] = "login";

    QJsonDocument doc(jsonData);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    socket->write(data);  // socket 是与服务器通信的 QTcpSocket 对象
    socket->flush();
}

void WeChat::getFriendListRequest() {
    QJsonObject response;
    response["type"] = "getFriendList";
    response["userid"] = myUser.id;
    QJsonDocument doc(response);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    socket->write(data);
    socket->flush();
}

void WeChat::onQuitBtnClicked() {

    QJsonObject response;
    response["type"] = "exit";
    response["userId"] = myUser.id;
    QJsonDocument doc(response);
    QByteArray data= doc.toJson(QJsonDocument::Compact);
    socket->write(data);
    socket->flush();

    RegisterLogin *registerLogin = new RegisterLogin(this);
    ui->widget->hide();
    registerLogin->show();
    connect(registerLogin, &RegisterLogin::loginSuccess, this, &WeChat::sendLoginRequest);
    connect(registerLogin, &RegisterLogin::registerSuccess, this, &WeChat::onRegisterLogin);
    connect(registerLogin, &RegisterLogin::tell_close, this, &WeChat::on_window_close);
}

void WeChat::processJsonObject(const QJsonObject &response) {
    QString type = response["type"].toString();
    qDebug() << type << endl;
    //判断type类型
    if (type == "login_response") {
        qDebug()<<response;
        QString userId =  response["userid"].toString();
        QString userName = response["username"].toString();
        QString telNo = response["tel"].toString();
        QString s = response["avatardata"].toString();
        QByteArray avatarData = QByteArray::fromBase64(s.toLatin1());

        User a(userId, userName, telNo, avatarData);
        myUser = a;
        qDebug() << a.id << endl;
        qDebug() << myUser.id << endl;

        loadUserInfo(); //左上角用户信息
        getFriendListRequest();

    }
    else if(type == "register_response") {
        QString status = response["status"].toString();
        qDebug() << status << endl;
        if(status == "success") {
            QMessageBox::information(this, "Register", "注册成功");

        }
        else {
            QMessageBox::warning(this, "Register", "用户名重复或电话号码存在");
        }
    }
    else if(type == "sendError") {
        QMessageBox::warning(this, "Send", "用户不在线上");
    }
    else if(type == "getmessage") {
        QString typeItem = response["typeItem"].toString();
        if(typeItem == "text") {
            QString sendName = response["sendname"].toString();
            QString text = response["text"].toString();
            QString time = response["time"].toString();
            QString friendId = response["friendid"].toString();
            QString receiveName = response["receivename"].toString();
            QString nameText;
            if(friendId != myUser.id) {
                QSqlQuery query;
                query.prepare("INSERT INTO messages VALUES(:userId, :friendId, :text, :type, :time)");
                query.bindValue(":userId", myUser.id);
                query.bindValue(":friendId", friendId);
                query.bindValue(":text", text);
                query.bindValue(":type", "text");
                query.bindValue(":time", time);
                query.exec();
                nameText = myUser.name + ": " + text + "\n";
                ui->chtDisplay->addItem(nameText);
            }
            else {
                QList<QListWidgetItem*> selectedItems = ui->friendList->selectedItems();
                for (QListWidgetItem *item : selectedItems) {
                    QWidget* friendWidget = ui->friendList->itemWidget(item);
                    QLabel* nameLabel = friendWidget->findChild<QLabel*>("nameLabel");
                    QString labelName = nameLabel->text();
                    if(labelName == sendName) {
                        nameText = sendName + ": " + text + "\n";
                        ui->chtDisplay->addItem(nameText);
                        return;
                    }
                }
            }
        }
        else if(typeItem == "picture") {
            QString friendId = response["friendid"].toString();
            QString sendName = response["sendname"].toString();
            QString receiveName = response["receivename"].toString();
            QByteArray imageData = QByteArray::fromBase64(response["picture"].toString().toUtf8());
            QString time = response["time"].toString();
            QString base64String = imageData.toBase64();
            QString nameText;
            if(friendId != myUser.id) {
                QSqlQuery query;
                query.prepare("INSERT INTO messages VALUES(:userId, :friendId, :text, :type, :time)");
                query.bindValue(":userId", myUser.id);
                query.bindValue(":friendId", friendId);
                query.bindValue(":text", base64String);
                query.bindValue(":type", "picture");
                query.bindValue(":time", time);
                query.exec();
                nameText = myUser.name + ": \n";
                ui->chtDisplay->addItem(nameText);
                QPixmap pixmap;
                pixmap.loadFromData(imageData);
                QListWidgetItem* item = new QListWidgetItem(ui->chtDisplay);
                QLabel* imageLabel = new QLabel();
                imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio)); // 调整图片大小
                ui->chtDisplay->setItemWidget(item, imageLabel);
                item->setSizeHint(imageLabel->sizeHint());
                ui->chtDisplay->addItem("\n");
            }

            else {
                QList<QListWidgetItem*> selectedItems = ui->friendList->selectedItems();
                for (QListWidgetItem *item : selectedItems) {
                    QWidget* friendWidget = ui->friendList->itemWidget(item);
                    QLabel* nameLabel = friendWidget->findChild<QLabel*>("nameLabel");
                    QString labelName = nameLabel->text();
                    if(labelName == sendName) {
                        nameText = sendName + ": \n";
                        ui->chtDisplay->addItem(nameText);
                        QPixmap pixmap;
                        pixmap.loadFromData(imageData);
                        QListWidgetItem* item = new QListWidgetItem(ui->chtDisplay);
                        QLabel* imageLabel = new QLabel();
                        imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio)); // 调整图片大小
                        ui->chtDisplay->setItemWidget(item, imageLabel);
                        item->setSizeHint(imageLabel->sizeHint());
                        ui->chtDisplay->addItem("\n");
                        return;
                    }
                }
            }
        }
    }
    else if(type == "friendStatus") {
        QString status = response["status"].toString();
        QString name = response["name"].toString();
        int count = ui->friendList->count();  // 获取 friendList 中的项数
        for (int i = 0; i < count; ++i) {
            QListWidgetItem* item = ui->friendList->item(i);  // 获取每个 QListWidgetItem

            QWidget* friendWidget = ui->friendList->itemWidget(item);  // 获取与该 item 关联的 QWidget

            if (friendWidget) {
                // 查找 friendWidget 中的 nameLabel
                QLabel* nameLabel = friendWidget->findChild<QLabel*>("nameLabel");
                if (nameLabel) {
                    QString n = nameLabel->text();  // 获取 nameLabel 的文本
                    if(n == name) {
                        // 查找 friendWidget 中的 onlineLabel
                        QLabel* statusLabel = friendWidget->findChild<QLabel*>("statusLabel");
                        if (statusLabel) {
                            QString s;
                            if(status == "online") {
                                statusLabel->setProperty("status", "Online");
                                s = ":/绿点.png";
                            }
                            else {
                                statusLabel->setProperty("status", "Offline");
                                s = ":/红点.png";
                            }
                            QPixmap onlinePixmap(s);
                            // 更新 statusLabel 的图像
                            statusLabel->setPixmap(onlinePixmap.scaled(10, 10, Qt::KeepAspectRatio));  // 调整大小以适应布局
                        }
                    }
                }
            }
        }
    }
    else if(type == "creategroup") {
        QString name = response["name"].toString();
        if(multicastAddress != "" && multicastPort != 0) {
            QJsonObject obj;
            obj["type"] = "grouprequest";
            obj["for"] = "havegroup";
            obj["toname"] = name;
            obj["fromname"] = myUser.name;
            QJsonDocument doc(obj);
            QByteArray data = doc.toJson(QJsonDocument::Compact);
            socket->write(data);
            return;
        }
        // 创建 QMessageBox 对象
        QMessageBox inviteBox;
        inviteBox.setWindowTitle("邀请进入群聊");
        inviteBox.setText(QString("%1 邀请你进入群聊").arg(name));
        inviteBox.setIcon(QMessageBox::Question); // 设置图标为问题

        // 添加按钮
        QPushButton *yesButton = inviteBox.addButton("是", QMessageBox::YesRole);
        QPushButton *noButton = inviteBox.addButton("否", QMessageBox::NoRole);

        // 显示对话框并等待用户选择
        inviteBox.exec();

        // 检查用户点击了哪个按钮
        if (inviteBox.clickedButton() == yesButton) {
            QListWidgetItem* item = new QListWidgetItem(ui->groupChatList);

            QWidget* friendWidget = new QWidget();
            QHBoxLayout* layout = new QHBoxLayout(friendWidget);

            QLabel* avatarLabel = new QLabel(friendWidget);
            QPixmap avatarPixmap(":/默认.png");
            avatarLabel->setPixmap(avatarPixmap.scaled(50, 50, Qt::KeepAspectRatio));
            avatarLabel->setObjectName("avatarLabel");  // 设置 objectName
            // 设置名称标签
            QLabel* nameLabel = new QLabel("new group chat", friendWidget);
            nameLabel->setObjectName("nameLabel");  // 设置 objectName
            layout->addWidget(avatarLabel);
            layout->addWidget(nameLabel);
            friendWidget->setLayout(layout);
            item->setSizeHint(friendWidget->sizeHint());ui->groupChatList->setItemWidget(item, friendWidget);
            ui->groupWidget->show();
            multicastAddress = response["address"].toString();
            multicastPort = static_cast<quint16>(response.value("port").toInt());
            uSocket->bind(QHostAddress::AnyIPv4, multicastPort, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
            uSocket->joinMulticastGroup(QHostAddress(multicastAddress));
            qDebug() << multicastAddress << " " << multicastPort;
            QString message = myUser.name + " 加入群聊";
            QJsonObject obj;
            obj["type"] = "text";
            obj["data"] = message;
            QJsonDocument doc(obj);
            QByteArray datagram = doc.toJson(QJsonDocument::Compact);
            uSocket->writeDatagram(datagram, QHostAddress(multicastAddress), multicastPort);
        } else if (inviteBox.clickedButton() == noButton) {
            QJsonObject obj;
            obj["type"] = "grouprequest";
            obj["for"] = "decline";
            obj["toname"] = name;
            obj["fromname"] = myUser.name;
            QJsonDocument doc(obj);
            QByteArray data = doc.toJson(QJsonDocument::Compact);
            socket->write(data);
        }
    }
    else if(type == "getfriendid") {
        QString friendId = response["friendid"].toString();
        QString name = response["friendname"].toString();
        QSqlQuery query;
        query.prepare("SELECT * FROM messages WHERE (sender_id = :user1_id AND receive_id = :user2_id) "
                      "OR (sender_id = :user2_id AND receive_id = :user1_id) ORDER BY time");
        query.bindValue(":user1_id", myUser.id);
        query.bindValue(":user2_id", friendId);
        query.bindValue(":user2_id", friendId);
        query.bindValue(":user1_id", myUser.id);
        query.exec();
        while(query.next()) {
            QString type = query.value(3).toString();
            QString senderId = query.value(0).toString();
            if(type == "text") {
                QString text = query.value(2).toString();

                QString nameText;
                if(senderId == friendId) {
                    nameText = name + ": " + text + "\n";
                }
                else {
                    nameText = myUser.name + ": " + text + "\n";
                }
                ui->chtDisplay->addItem(nameText);
            }
            else if(type == "picture"){
                QString nameText;
                if(senderId == friendId) {
                    nameText = name + ":\n";
                }
                else {
                    nameText = myUser.name + ":\n";
                }
                ui->chtDisplay->addItem(nameText);
                QString base64String = query.value(2).toString();
                QPixmap pixmap;
                QByteArray byteArray = QByteArray::fromBase64(base64String.toUtf8());
                pixmap.loadFromData(byteArray);
                QListWidgetItem* item = new QListWidgetItem(ui->chtDisplay);
                QLabel* imageLabel = new QLabel();
                imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio)); // 调整图片大小
                ui->chtDisplay->setItemWidget(item, imageLabel);
                item->setSizeHint(imageLabel->sizeHint());
                ui->chtDisplay->addItem("\n");
            }
        }
    }

    else if(type == "grouprequest") {
        QString a = response["for"].toString();
        QString name = response["fromname"].toString();
        if(a == "havegroup") {
            QMessageBox::information(this, "add group", name + "在群里或在另一个群聊");
        }
        else {
            QMessageBox::information(this, "add group", name + "拒绝加入群聊");
        }
    }

    else if(type == "addfriend") {
        QString name = response["username"].toString();
        QString base64String = response["avatar"].toString();
        QString uid = response["uid"].toString();
        QString status = response["status"].toString();

        // 好友信息显示区域
        QDialog *dialog = new QDialog(this);
        QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
        QWidget *friendInfoWidget = new QWidget(dialog);
        QHBoxLayout *friendLayout = new QHBoxLayout(friendInfoWidget);
        QLabel *avatarLabel = new QLabel(friendInfoWidget);
        QLabel *nameLabel = new QLabel(name, friendInfoWidget);
        QPushButton *addButton = new QPushButton("Add", friendInfoWidget);

        QPixmap pixmap;
        QByteArray byteArray = QByteArray::fromBase64(base64String.toUtf8());
        pixmap.loadFromData(byteArray);
        avatarLabel->setPixmap(pixmap.scaled(50, 50, Qt::KeepAspectRatio));

        avatarLabel->setFixedSize(50, 50);  // 设置头像大小
        friendLayout->addWidget(avatarLabel);
        friendLayout->addWidget(nameLabel);
        friendLayout->addWidget(addButton);
        mainLayout->addWidget(friendInfoWidget);
        dialog->setLayout(mainLayout);
        dialog->setFixedSize(dialog->sizeHint());
        connect(addButton, &QPushButton::clicked, [=]() {
            qDebug() << myUser.id << uid << myUser.name << name;

            QString strURL = baseUrl + "/api/friends/addFriend?userId="+ myUser.id +"&friendId="+uid+"&myName="+myUser.name+"&friendName="+name;
            QUrl url(strURL);
            QNetworkRequest request(url);

            // http request
            QNetworkAccessManager *manager = new QNetworkAccessManager(this);
            // use get method request
            QNetworkReply *reply = manager->get(request);
            connect(manager, &QNetworkAccessManager::finished,
                    this, [=]() {
                QByteArray result;
                if(reply->error() == QNetworkReply::NoError) {
                    // handle no error
                    result = reply->readAll();
                } else {
                    // handle error
                    QMessageBox::warning(this, "error", reply->errorString());
                    return;
                }
                // 对于Json
                QJsonObject jsonObject;
                QJsonDocument jsonDoc = QJsonDocument::fromJson(result);
                if(!jsonDoc.isNull() && jsonDoc.isObject()) {
                    jsonObject = jsonDoc.object();
                }
                //        qDebug() << jsonObject;
                if(jsonObject["code"].toDouble() != 200) {
                    QMessageBox::warning(this, "error", jsonObject["info"].toString());
                    return;
                }
                /////////
                QListWidgetItem* item = new QListWidgetItem(ui->friendList);

                QWidget* friendWidget = new QWidget();
                QHBoxLayout* layout = new QHBoxLayout(friendWidget);

                QLabel* avatarLabel = new QLabel(friendWidget);
                QPixmap avatarPixmap;
                avatarPixmap.loadFromData(byteArray);
                avatarLabel->setPixmap(avatarPixmap.scaled(50, 50, Qt::KeepAspectRatio));
                avatarLabel->setObjectName("avatarLabel");  // 设置 objectName
                QLabel* statusLabel = new QLabel(friendWidget);

                QString statusText;  // 状态文本
                QString s;
                if(status == "online") {
                    s = ":/绿点.png";
                    statusText = "Online";
                }
                else {
                    s = ":/红点.png";
                    statusText = "Offline";
                }
                QPixmap onlinePixmap(s);
                statusLabel->setPixmap(onlinePixmap.scaled(10, 10, Qt::KeepAspectRatio));
                statusLabel->setObjectName("statusLabel"); // 设置 objectName

                statusLabel->setProperty("status", statusText);  // 使用属性存储状态文本
                statusLabel->setVisible(true);  // 仅显示图标，不显示文本

                // 设置名称标签
                QLabel* nameLabel = new QLabel(name, friendWidget);
                nameLabel->setObjectName("nameLabel");  // 设置 objectName

                layout->addWidget(avatarLabel);
                layout->addWidget(nameLabel);
                layout->addWidget(statusLabel);
                friendWidget->setLayout(layout);
                item->setSizeHint(friendWidget->sizeHint());
                ui->friendList->setItemWidget(item, friendWidget);
                QJsonObject obj;
                obj["type"] = "getfriendlistwidgetitem";
                obj["name"] = myUser.name;
                obj["uid"] = myUser.id;
                obj["frienduid"] = uid;
                QJsonDocument doc(obj);
                QByteArray data = doc.toJson(QJsonDocument::Compact);
                socket->write(data);
            });
        });
        dialog->exec();
    }

    else if(type == "updatefriendlist") {
        QString name = response["name"].toString();
        QString base64String = response["avatar"].toString();
        QListWidgetItem* item = new QListWidgetItem(ui->friendList);

        QWidget* friendWidget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(friendWidget);

        QLabel* avatarLabel = new QLabel(friendWidget);
        QPixmap avatarPixmap;
        QByteArray byteArray = QByteArray::fromBase64(base64String.toUtf8());
        avatarPixmap.loadFromData(byteArray);
        avatarLabel->setPixmap(avatarPixmap.scaled(50, 50, Qt::KeepAspectRatio));
        avatarLabel->setObjectName("avatarLabel");  // 设置 objectName
        QLabel* statusLabel = new QLabel(friendWidget);

        QString statusText;  // 状态文本
        QString s;
        s = ":/绿点.png";
        statusText = "Online";
        QPixmap onlinePixmap(s);
        statusLabel->setPixmap(onlinePixmap.scaled(10, 10, Qt::KeepAspectRatio));
        statusLabel->setObjectName("statusLabel"); // 设置 objectName

        statusLabel->setProperty("status", statusText);  // 使用属性存储状态文本
        statusLabel->setVisible(true);  // 仅显示图标，不显示文本

        // 设置名称标签
        QLabel* nameLabel = new QLabel(name, friendWidget);
        nameLabel->setObjectName("nameLabel");  // 设置 objectName

        layout->addWidget(avatarLabel);
        layout->addWidget(nameLabel);
        layout->addWidget(statusLabel);
        friendWidget->setLayout(layout);
        item->setSizeHint(friendWidget->sizeHint());
        ui->friendList->setItemWidget(item, friendWidget);
    }

}

void WeChat::onRegisterLogin(QString uid, QByteArray avatarData) {
    QJsonObject obj;
    QString base64String = QString::fromLatin1(avatarData.toBase64());
    obj["type"] = "Register";
    obj["avatardata"] = base64String;
    obj["uid"] = uid;
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    socket->write(data);
}

void WeChat::processJsonArray(const QJsonArray &array) {
    QString type;
    //        for(const QJsonValue &val : array) {
    QList<User> user;
    for(int i=0; i<array.size(); i++){
        qDebug() << i << endl;
        QJsonObject object = array[i].toObject();
        if(i == 0) {
            type = object["type"].toString();
            qDebug() << "Type:" << type << endl;
        }
        else {
            if(type == "getFriendList") {
                User a;
                a.name = object["username"].toString();
                qDebug() << a.name << endl;
                a.avatarData = QByteArray::fromBase64(object["avatar"].toString().toUtf8());
                a.status = object["status"].toString();
                user.append(a);
            }
        }
    }
    if(type == "getFriendList") {
        loadFriendList(user);
    }
}

//左上角用户栏
void WeChat::loadUserInfo() {
    // 获取当前用户的头像和用户名
    QPixmap pixmap;
    pixmap.loadFromData(myUser.avatarData);
    QString userName = myUser.name; // 获取用户名

    // 使用 UI 文件中的控件
    QLabel* avatarLabel = ui->avatarLabel;  // 通过 ui 指针访问 QLabel
    QLabel* usernameLabel = ui->usernameLabel;
    QLabel* uidLabel = ui->uidLabel;

    // 设置头像和用户名
    avatarLabel->setPixmap(pixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    usernameLabel->setText(userName);
    uidLabel->setText("UID " + myUser.id);
}

void WeChat::onServerResponse()
{
    static QByteArray buffer; // 用于暂存数据的缓冲区

    // 将新接收的数据追加到缓冲区
    buffer.append(socket->readAll());

    // 检查缓冲区中的数据是否包含至少4个字节（表示长度的字段）
    while (buffer.size() >= 4) {
        // 提取前4个字节作为长度字段
        qint32 dataLength;
        memcpy(&dataLength, buffer.constData(), sizeof(dataLength));

        // 检查缓冲区是否包含完整的数据包
        if (buffer.size() >= (4 + dataLength)) {
            // 从缓冲区中提取完整的数据包（去掉长度字段）
            QByteArray jsonData = buffer.mid(4, dataLength);
            qDebug() << "jsonData" << jsonData << endl;
            // 将剩余的数据保留在缓冲区中
            buffer.remove(0, 4 + dataLength);
            QJsonDocument doc = QJsonDocument::fromJson(jsonData);
            if(doc.isObject()) {
                QJsonObject response = doc.object();
                processJsonObject(response);
            }
            else if(doc.isArray()) {
                qDebug() << doc << endl;
                QJsonArray response = doc.array();
                processJsonArray(response);
            }
        }
        else {
            // 如果数据包不完整，等待接收更多数据
            break;
        }
    }
}


void WeChat::on_window_close(){
    emit tell_close();
    deleteLater();
}



