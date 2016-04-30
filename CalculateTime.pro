#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T10:02:27
#
#-------------------------------------------------

QT       += widgets

TARGET = CalculateTime
TEMPLATE = app


SOURCES += main.cpp\
        TimeDlg.cpp \
    UITools/LineEdit.cpp

HEADERS  += TimeDlg.h \
    UITools/LineEdit.h

RESOURCES += \
    resource.qrc

TRANSLATIONS = zh.ts

RC_FILE+= ./images/icon.rc

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
