#-------------------------------------------------
#
# Project created by QtCreator 2017-02-28T21:01:44
#
#-------------------------------------------------

QT       += core gui
QT       += webkit network
QT       += widgets
QT       += webkitwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    robot.cpp \
    camerasetwidget.cpp \
    taskquerywidget.cpp \
    parcelquerywidget.cpp \
    teleoperation.cpp \
    boxinfowidget.cpp \
    vehicleinfowidget.cpp \
    taskplan.cpp \
    tasksetwidget.cpp \
    io.cpp

HEADERS  += mainwindow.h \
    robot.h \
    camerasetwidget.h \
    taskquerywidget.h \
    parcelquerywidget.h \
    teleoperation.h \
    boxinfowidget.h \
    vehicleinfowidget.h \
    taskplan.h \
    tasksetwidget.h \
    io.h


FORMS    += mainwindow.ui \
    camerasetwidget.ui \
    taskquerywidget.ui \
    parcelquerywidget.ui \
    teleoperation.ui \
    boxinfowidget.ui \
    vehicleinfowidget.ui \
    tasksetwidget.ui
DISTFILES += \
    htmlapi/baiduapi.html \
    vediohtml/vedioplay.html \
    vediohtml/rightmonicamera.html \
    vediohtml/rightcamera.html \
    vediohtml/realtimemap.html \
    vediohtml/leftmonicamera.html \
    vediohtml/leftcamera.html \
    vediohtml/frontcamera .html \
    vediohtml/backcamera.html \
    vediohtml/frontcamera .html \
    vediohtml/frontcamera .html \
    vediohtml/frontcamera.html \
    vediohtml/leftcamera1.html \
    vediohtml/frontcamera1.html \
    vediohtml/backcamera1.html \
    vediohtml/rightcameramain.html \
    vediohtml/leftcameramain.html \
    vediohtml/frontcameramain.html \
    vediohtml/backcameramain.html \
    vediohtml/rightcamera1.html

RESOURCES += \
    qss.qrc
