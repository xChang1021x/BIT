QT       += core gui
QT       += webenginewidgets
QT       += multimedia
QT       += multimediawidgets
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bg.cpp \
    image.cpp \
    imagelistwindow.cpp \
    dayline.cpp \
    main.cpp \
    mainpage.cpp \
    music.cpp \
    radio.cpp \
    registerlogin.cpp \
    videoplayerwidget.cpp \
    weather.cpp \
    website.cpp \
    websitewidget.cpp \
    cargps.cpp \
    wechat.cpp

HEADERS += \
    bg.h \
    image.h \
    imagelistwindow.h \
    dayline.h \
    mainpage.h \
    music.h \
    radio.h \
    registerlogin.h \
    videoplayerwidget.h \
    weather.h \
    website.h \
    websitewidget.h \
    cargps.h \
    wechat.h

FORMS += \
    bg.ui \
    image.ui \
    mainpage.ui \
    music.ui \
    radio.ui \
    registerlogin.ui \
    videoplayerwidget.ui \
    weather.ui \
    website.ui \
    websitewidget.ui \
    cargps.ui \
    wechat.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

SUBDIRS += \
    PictureViewPm.pro \
    RegisterLogin.pro \
    VideoPlayer.pro \
    fm.pro \
    untitled.pro \
    website.pro \
    website.pro \
    CarGps.pro \
    MusicPlayerApp.pro \
    qtProject01.pro

DISTFILES += \
    untitled.pro.user \
    back.png \
    forward.png \
