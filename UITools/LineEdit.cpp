#include "LineEdit.h"
#include <QMouseEvent>
#include <QDebug>
CLineEdit::CLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    m_bFocusIn = false;
}

CLineEdit::CLineEdit(const QString &contents, QWidget *parent) :
    QLineEdit(contents, parent)
{
    m_bFocusIn = false;
}

QString CLineEdit::GetText()
{
    if(m_bFocusIn && text().isEmpty())
    {
        return m_text;
    }
    else
    {
        return text();
    }
}

void CLineEdit::focusInEvent(QFocusEvent *e)
{
    m_bFocusIn = true;
    m_text = text();
    clear();
    QLineEdit::focusInEvent(e);
}

void CLineEdit::focusOutEvent(QFocusEvent *e)
{
    m_bFocusIn = false;
    if(text().isEmpty())
    {
        if(m_text.isEmpty())
        {
            setText("0");
        }
        else
        {
            setText(m_text);
        }
    }
    QLineEdit::focusOutEvent(e);
}
