QT       += core gui    #支持核心应用扩展库

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets     #支持组件编程扩展库， 当前Qt版本超过4

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS       #使用过期API QT将会抛出警告

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \        #源文件
    main.cpp \
    logindialog.cpp

HEADERS += \        #头文件
    logindialog.h

FORMS += \          #界面文件
    logindialog.ui

TRANSLATIONS += \   #
    ExamSys_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc \
    image.qrc
