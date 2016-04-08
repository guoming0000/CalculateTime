#ifndef TIMEDLG_H
#define TIMEDLG_H

#include <QDialog>
#include <QTranslator>
class QLabel;
class CLineEdit;
class QPushButton;
const int TIME_DISP_LINE_COUNT = 4;

#include <QDateTime>
#include <QFocusEvent>
class CTimeDlg : public QDialog
{
    Q_OBJECT
    
public:
    CTimeDlg(QWidget *parent = 0);
    void SaveTranslator(QTranslator *translator);
    ~CTimeDlg();

protected:
    enum{
        YEAR,
        MONTH,
        DAY,
        HOUR,
        MINUTE,
        SECOND,
        TIME_COUNT
    };

    enum
    {
        DISP_START,//start time
        DISP_FLY,//passed time
        DISP_DESTINATION,//destination time
        DISP_TO_NOW,
        DISP_COUNT
    };

    enum
    {
        BTN_100_DAY,
        BTN_1000_DAY,
        BTN_10000_DAY,
        BTN_100000_SECOND,
        BTN_1000000_SECOND,
        BTN_10000000_SECOND,
        BTN_COUNT
    };

private slots:
    void startTimeChanged(const QString &text);
    void passedTimeChanged(const QString &text);
    void calculateToNowTime();

    void pressBtn();

private:
    void createComponent();
    void createLayout();
    void init();
    void loadLanguage();
    void updateText();
    int getEditNum(CLineEdit *line_edit);

    QDateTime getStartTime();
    int getPassedSecond();

    void clearPassedTime();

    void calculateDestinationTime();

    QString getShowTime(const QDateTime &dateTime);

    QLabel *m_pTimeText[TIME_COUNT];//year hour day... text description
    QLabel *m_pDispText[DISP_COUNT];//left text description

    CLineEdit *m_pStartTime[TIME_COUNT];//input start time
    CLineEdit *m_pPassedTime[TIME_COUNT];//input passed time
    QLabel *m_pDestinationTimeText;//show destination time
    QLabel *m_pToNowTime;

    bool m_bNeedShowAns;
    QTranslator m_Translator;

    //change text color
    QString m_redStyleSheet;
    QString m_defaultStyleSheet;

    QDateTime m_destinationDateTime;
    int m_passedSeconds;

    //focus in
    QString m_saveStr;
    bool m_bFocusIn;

    //default btn state
    QPushButton *m_pDefaultBtn[BTN_COUNT];
    QPushButton *m_pLanguageBtn;
    QTranslator *m_pTranslator;
};

#endif // TIMEDLG_H
