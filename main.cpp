#include <QApplication>
#include <QTranslator>
#include "TimeDlg.h"
#include <QDebug>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator *translator = new QTranslator;
    translator->load(":/zh.qm");
    a.installTranslator(translator);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    CTimeDlg w;
    w.SaveTranslator(translator);
    w.show();
    
    return a.exec();
}
