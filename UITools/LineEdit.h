#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>
/*
    reconstruction the Class QLineEdit to get the signal
    focus in event and focus out event.
*/
class CLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit CLineEdit(QWidget *parent = 0);
    explicit CLineEdit(const QString &contents, QWidget* parent=0);
    QString GetText();
protected:
     void focusInEvent(QFocusEvent * e);
     void focusOutEvent(QFocusEvent *);

public slots:

private:
     QString m_text;
     bool m_bFocusIn;
    
};

#endif // LINEEDIT_H
