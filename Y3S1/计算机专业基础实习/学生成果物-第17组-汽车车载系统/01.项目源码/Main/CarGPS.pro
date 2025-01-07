QT       += core gui
QT       += multimedia
QT       += network
QT       += webenginewidgets
QT       += positioning

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    cargps.cpp

HEADERS += \
    cargps.h

FORMS += \
    cargps.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    BDMap.html \
    testMap.html

RESOURCES += \
    res.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../NlsCppSdk_Linux_3.2.0a_b2b0faa/NlsSdk3.X_LINUX/lib/release/ -lalibabacloud-idst-speech
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../NlsCppSdk_Linux_3.2.0a_b2b0faa/NlsSdk3.X_LINUX/lib/debug/ -lalibabacloud-idst-speech
else:unix: LIBS += -L$$PWD/../../NlsCppSdk_Linux_3.2.0a_b2b0faa/NlsSdk3.X_LINUX/lib/ -lalibabacloud-idst-speech

INCLUDEPATH += $$PWD/../../NlsCppSdk_Linux_3.2.0a_b2b0faa/NlsSdk3.X_LINUX/include
DEPENDPATH += $$PWD/../../NlsCppSdk_Linux_3.2.0a_b2b0faa/NlsSdk3.X_LINUX/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../NlsCppSdk_Linux_3.2.0a_b2b0faa/NlsSdk3.X_LINUX/lib/release/libalibabacloud-idst-speech.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../NlsCppSdk_Linux_3.2.0a_b2b0faa/NlsSdk3.X_LINUX/lib/debug/libalibabacloud-idst-speech.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../NlsCppSdk_Linux_3.2.0a_b2b0faa/NlsSdk3.X_LINUX/lib/release/alibabacloud-idst-speech.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../NlsCppSdk_Linux_3.2.0a_b2b0faa/NlsSdk3.X_LINUX/lib/debug/alibabacloud-idst-speech.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../NlsCppSdk_Linux_3.2.0a_b2b0faa/NlsSdk3.X_LINUX/lib/libalibabacloud-idst-speech.a
