#include "classmould.h"

ClassMould::ClassMould(QWidget *parent,QString name):QLabel(parent),m_strClassName(name)
{
    m_bIsChecked = false;
    this->setPixmap(QPixmap(CLASS));
    this->setMinimumSize(264,355);
    this->setMaximumSize(264,355);
    m_pShowName = new QLabel(this);
    m_pShowName->setMinimumSize(264,80);
    m_pShowName->setMaximumSize(264,80);
    m_pShowName->move(0,230);
    m_pShowName->setAlignment(Qt::AlignCenter);
    m_Font.setPixelSize(30);
    m_pShowName->setFont(m_Font);
    m_pShowName->setText(m_strClassName);
   // m_pShowName->setStyleSheet("background-color:rgb(23,34,56)");
}

void ClassMould::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        if(m_bIsChecked)
        {
            //SetChecked(true);
        }
        else
        {
            //SetChecked(false);
        }
        m_bIsChecked = true;
        emit LabelChecked();
    }
}
void ClassMould::SetClassName(QString name)
{
    m_strClassName = name;
    m_pShowName->setText(m_strClassName);
}
void ClassMould::SetChecked(bool flag)
{
    if(flag)
    {
        this->setPixmap(QPixmap(CLASSPRESS));
    }
    else
    {
        this->setPixmap(QPixmap(CLASS));
    }
}
bool ClassMould::IsChecked()
{
    return m_bIsChecked;
}
void ClassMould::SetCheckedFlag(bool flag)
{
    m_bIsChecked = flag;
}
