#include "TimeDlg.h"
#include <QIcon>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QSettings>
#include <QTranslator>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QApplication>
#include "UITools/LineEdit.h"

//constructor
CTimeDlg::CTimeDlg(QWidget *parent)
    : QDialog(parent)
{
    createComponent();
    createLayout();
    init();
    updateText();
    setWindowOpacity(0.9);

    Qt::WindowFlags flags = windowFlags() - Qt::WindowContextHelpButtonHint;//delete question flag
    setWindowFlags(flags);

//    m_pToNowTime->setOpenExternalLinks();
}

void CTimeDlg::SaveTranslator(QTranslator *translator)
{
    m_pTranslator = translator;
}

//disctructor
CTimeDlg::~CTimeDlg()
{
    
}

//创建控件
void CTimeDlg::createComponent()
{
    for(int i = 0; i < TIME_COUNT; ++i)
    {
        m_pTimeText[i] = new QLabel;
        m_pStartTime[i] = new CLineEdit("0");
        m_pStartTime[i]->setAlignment(Qt::AlignCenter);
        m_pPassedTime[i] = new CLineEdit("0");
        m_pPassedTime[i]->setAlignment(Qt::AlignCenter);
    }

    for(int i = 0; i < DISP_COUNT; ++i)
    {
        m_pDispText[i] = new QLabel;
    }

    m_pDestinationTimeText = new QLabel;
    m_pToNowTime = new QLabel;

    for(int i = 0;i < BTN_COUNT; ++i)
    {
        m_pDefaultBtn[i] = new QPushButton;
    }

    m_pLanguageBtn = new QPushButton;
    m_pLanguageBtn->setObjectName("languageBtn");
    m_pLanguageBtn->setMinimumSize(40, 32);

}

//make a layout
void CTimeDlg::createLayout()
{
    QHBoxLayout *default_btns = new QHBoxLayout;
    for(int i = 0; i < BTN_COUNT; ++i)
    {
        default_btns->addWidget(m_pDefaultBtn[i]);
    }
    default_btns->addStretch(1);
    default_btns->addWidget(m_pLanguageBtn);

    QHBoxLayout *disp_time = new QHBoxLayout;
    disp_time->addStretch(1);
    for(int i = 0; i < TIME_COUNT; ++i)
    {
        disp_time->addWidget(m_pTimeText[i], 1, Qt::AlignCenter);
    }

    QHBoxLayout *start_time = new QHBoxLayout;
    start_time->addWidget(m_pDispText[DISP_START], 1);
    for(int i = 0; i < TIME_COUNT; ++i)
    {
        start_time->addWidget(m_pStartTime[i], 1, Qt::AlignCenter);
    }

    QHBoxLayout *pass_time = new QHBoxLayout;
    pass_time->addWidget(m_pDispText[DISP_FLY], 1);
    for(int i = 0; i < TIME_COUNT; ++i)
    {
        pass_time->addWidget(m_pPassedTime[i], 1, Qt::AlignCenter);
    }

    QHBoxLayout *destination_time = new QHBoxLayout;
    destination_time->addWidget(m_pDispText[DISP_DESTINATION], 1);
    destination_time->addWidget(m_pDestinationTimeText, 6);
    QFont font = m_pDestinationTimeText->font();
    font.setPixelSize(50);
    font.setBold(true);
    m_pDestinationTimeText->setFont(font);

    QHBoxLayout *to_now = new QHBoxLayout;
    to_now->addWidget(m_pDispText[DISP_TO_NOW], 1);
    to_now->addWidget(m_pToNowTime, 6);

    QVBoxLayout *time_layout = new QVBoxLayout;
    time_layout->addLayout(default_btns, 1);
    time_layout->addLayout(disp_time, 1);
    time_layout->addLayout(start_time, 1);
    time_layout->addLayout(pass_time, 1);
    time_layout->addLayout(destination_time, 1);
    time_layout->addLayout(to_now, 4);

    setLayout(time_layout);

    QFile file("images/darkorange.qss");
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
}

//init data
void CTimeDlg::init()
{
    m_pTranslator = NULL;

    QDate date = QDate::currentDate();
    m_pStartTime[YEAR]->setText(QString::number(date.year()));
    m_pStartTime[MONTH]->setText(QString::number(date.month()));
    m_pStartTime[DAY]->setText(QString::number(date.day()));

    m_defaultStyleSheet = m_pStartTime[YEAR]->styleSheet();
    m_redStyleSheet = "color:red";

    //connect signals and slots
    for(int i = 0; i < TIME_COUNT; ++i)
    {
        connect(m_pStartTime[i], SIGNAL(textChanged(QString)), this, SLOT(startTimeChanged(QString)));
        connect(m_pPassedTime[i], SIGNAL(textChanged(QString)), this, SLOT(passedTimeChanged(QString)));

    }

    m_passedSeconds = 0;

    QTimer *second = new QTimer(this);
    connect(second, SIGNAL(timeout()), SLOT(calculateToNowTime()));
    second->start(1000);

    connect(m_pLanguageBtn, SIGNAL(clicked(bool)), this , SLOT(pressBtn()));
    for(int i = 0; i < BTN_COUNT; ++i)
    {
        connect(m_pDefaultBtn[i], SIGNAL(clicked(bool)), this, SLOT(pressBtn()));
    }
}

//when start time changed
void CTimeDlg::startTimeChanged(const QString &text)
{
    Q_UNUSED(text)
    CLineEdit *line_edit = qobject_cast<CLineEdit*>(sender());
    if(!m_bFocusIn || !text.isEmpty())
    {
        if(!getStartTime().isValid())
        {
            for(int i = 0; i < TIME_COUNT; ++i)
            {
                m_pStartTime[i]->setStyleSheet(m_redStyleSheet);
            }
        }
        else
        {
            if(m_defaultStyleSheet != line_edit->styleSheet())
            {
                for(int i = 0; i < TIME_COUNT; ++i)
                {
                    m_pStartTime[i]->setStyleSheet(m_defaultStyleSheet);
                }
            }
        }
    }

    calculateDestinationTime();
}

void CTimeDlg::passedTimeChanged(const QString &text)
{
    Q_UNUSED(text)
    m_passedSeconds = getPassedSecond();
    calculateDestinationTime();
}

//judge the language
void CTimeDlg::loadLanguage()
{
    QSettings set("Config.ini", QSettings::IniFormat);
    QString language_str = set.value("Language", "Chinese").toString();
    if("Chinese" == language_str)
    {
       QApplication::installTranslator(&m_Translator);
    }
    else
    {
        QApplication::removeTranslator(&m_Translator);
    }
}

//update displayed texts
void CTimeDlg::updateText()
{
    m_pTimeText[YEAR]->setText(tr("Year"));
    m_pTimeText[MONTH]->setText(tr("Month"));
    m_pTimeText[DAY]->setText(tr("Day"));
    m_pTimeText[HOUR]->setText(tr("Hour"));
    m_pTimeText[MINUTE]->setText(tr("Minute"));
    m_pTimeText[SECOND]->setText(tr("Second"));

    m_pDispText[DISP_START]->setText(tr("Start Time"));
    m_pDispText[DISP_FLY]->setText(tr("Passed Time"));
    m_pDispText[DISP_DESTINATION]->setText(tr("Destination Time"));
    m_pDispText[DISP_TO_NOW]->setText(tr("Destination To Now"));

    m_pDefaultBtn[BTN_100_DAY]->setText(tr("100 days"));
    m_pDefaultBtn[BTN_1000_DAY]->setText(tr("1000 days"));
    m_pDefaultBtn[BTN_10000_DAY]->setText(tr("10,000 days"));
    m_pDefaultBtn[BTN_100000_SECOND]->setText(tr("100,000 seconds"));
    m_pDefaultBtn[BTN_1000000_SECOND]->setText(tr("1,000,000 seconds"));
    m_pDefaultBtn[BTN_10000000_SECOND]->setText(tr("10,000,000 seconds"));

    setWindowTitle(tr("Time Calculator v1.0 (Developed by www.BrightGuo.com)"));
}

int CTimeDlg::getEditNum(CLineEdit *line_edit)
{
    return line_edit->GetText().toInt();
}

QDateTime CTimeDlg::getStartTime()
{
    QDate date = QDate(getEditNum(m_pStartTime[YEAR]), getEditNum(m_pStartTime[MONTH]), getEditNum(m_pStartTime[DAY]));
    QTime time = QTime(getEditNum(m_pStartTime[HOUR]), getEditNum(m_pStartTime[MINUTE]), getEditNum(m_pStartTime[SECOND]));;
    return QDateTime(date, time);
}

int CTimeDlg::getPassedSecond()
{
    int second = 0;
    if(0 == getEditNum(m_pPassedTime[YEAR]) && 0 == getEditNum(m_pPassedTime[MONTH]))//if year == 0
    {
        second = getEditNum(m_pPassedTime[DAY]) * 86400 + getEditNum(m_pPassedTime[HOUR]) * 3600
                + getEditNum(m_pPassedTime[MINUTE]) * 60 + getEditNum(m_pPassedTime[SECOND]);
    }
    else
    {
        second = -1;//不适合使用这种办法
    }

    return second;
}

void CTimeDlg::clearPassedTime()
{
    for(int i = 0; i < TIME_COUNT; ++i)
    {
        m_pPassedTime[i]->setText("0");
    }
}

void CTimeDlg::calculateDestinationTime()
{
    QDateTime dateTime = getStartTime();
    if(dateTime.isValid())
    {
        if(-1 != m_passedSeconds)
        {
            m_destinationDateTime = dateTime.addSecs(m_passedSeconds);
        }
        else
        {
            m_destinationDateTime = dateTime.addYears(getEditNum(m_pPassedTime[YEAR]));
            m_destinationDateTime = m_destinationDateTime.addMonths(getEditNum(m_pPassedTime[MONTH]));
            m_destinationDateTime = m_destinationDateTime.addDays(getEditNum(m_pPassedTime[DAY]));

            m_destinationDateTime = m_destinationDateTime.addSecs(getEditNum(m_pPassedTime[HOUR]) * 3600 +
                                                                  getEditNum(m_pPassedTime[MINUTE]) * 60 +
                                                                  getEditNum(m_pPassedTime[SECOND]));
        }
        m_pDestinationTimeText->setText(getShowTime(m_destinationDateTime));
    }
}

void CTimeDlg::calculateToNowTime()
{
    QDateTime now = QDateTime::currentDateTime();
    //int days = now.daysTo(m_destinationDateTime);
    int seconds = now.secsTo(m_destinationDateTime);
    double minutes = seconds / 60.0;
    double hours = minutes / 60.0;
    double days = hours / 24.0;
    double years = days / 365.0;

    QString text;
    if(years > 1.0)
    {
        text = QString::number(years, 'f', 3) + tr(" Year");
        text += "\n" + QString::number(days, 'f', 3) + tr(" Day");
        text += "\n" + QString::number(hours, 'f', 3) + tr(" Hour");
        text += "\n" + QString::number(minutes, 'f', 3) + tr(" Minute");
        text += "\n" + QString::number(seconds, 'f', 3) + tr(" Second");
    }
    else if(days > 1.0)
    {
        text = QString::number(days, 'f', 3) + tr(" Day");
        text += "\n" + QString::number(hours, 'f', 3) + tr(" Hour");
        text += "\n" + QString::number(minutes, 'f', 3) + tr(" Minute");
        text += "\n" + QString::number(seconds, 'f', 3) + tr(" Second");
    }
    else if(hours > 1.0)
    {
        text = QString::number(hours, 'f', 3) + tr(" Hour");
        text += "\n" + QString::number(minutes, 'f', 3) + tr(" Minute");
        text += "\n" + QString::number(seconds, 'f', 3) + tr(" Second");
    }
    else if(minutes > 1.0)
    {
        text = QString::number(minutes, 'f', 3) + tr(" Minute");
        text += "\n" + QString::number(seconds, 'f', 3) + tr(" Second");
    }
    else
    {
        text = QString::number(seconds, 'f', 3) + tr(" Second");
    }

    m_pToNowTime->setText(text);
}

void CTimeDlg::pressBtn()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if(btn == m_pLanguageBtn)
    {
        static bool isChinese = true;
        isChinese = !isChinese;
        if(isChinese)
        {
            if(m_pTranslator)
            {
                QApplication::installTranslator(m_pTranslator);
                updateText();
            }
        }
        else
        {
            if(m_pTranslator)
            {
                QApplication::removeTranslator(m_pTranslator);
                updateText();
            }
        }
    }
    else if(m_pDefaultBtn[BTN_100_DAY] == btn)
    {
        clearPassedTime();
        m_pPassedTime[DAY]->setText("99");
    }
    else if(m_pDefaultBtn[BTN_1000_DAY] == btn)
    {
        clearPassedTime();
        m_pPassedTime[DAY]->setText("999");
    }
    else if(m_pDefaultBtn[BTN_10000_DAY] == btn)
    {
        clearPassedTime();
        m_pPassedTime[DAY]->setText("9999");
    }
    else if(m_pDefaultBtn[BTN_100000_SECOND] == btn)
    {
        clearPassedTime();
        m_pPassedTime[SECOND]->setText("99999");
    }
    else if(m_pDefaultBtn[BTN_1000000_SECOND] == btn)
    {
        clearPassedTime();
        m_pPassedTime[SECOND]->setText("999999");
    }
    else if(m_pDefaultBtn[BTN_10000000_SECOND] == btn)
    {
        clearPassedTime();
        m_pPassedTime[SECOND]->setText("9999999");
    }
}

QString CTimeDlg::getShowTime(const QDateTime &dateTime)
{
    const QString day_name[] = {tr("Mon"), tr("Tue"),
                                tr("Wed"), tr("Thu"),
                                tr("Fri"), tr("Sat"), tr("Sun")};

    QDate date = dateTime.date();
    QTime time = dateTime.time();
    return QString("%1/%2/%3 %5:%6:%7   %4").arg(date.year()).arg(date.month()).arg(date.day()).arg(day_name[date.dayOfWeek() - 1])
            .arg(time.hour()).arg(time.minute()).arg(time.second());
}
