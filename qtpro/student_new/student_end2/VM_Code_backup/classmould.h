#ifndef CLASSMOULD_H
#define CLASSMOULD_H
#include <QLabel>
#include <QWidget>
#include <QString>
#include <QFont>
#include <QMouseEvent>

#define CLASS       "/usr/local/shencloud/image/ClassName1.png"
#define CLASSPRESS   "/usr/local/shencloud/image/ClassName1Press.png"

class ClassMould:public QLabel
{
    Q_OBJECT
public:
    explicit ClassMould(QWidget *parent,QString name);
    void SetChecked(bool flag);
    void SetClassName(QString name);
    bool IsChecked();
    void SetCheckedFlag(bool flag);
private:
    QLabel  *m_pShowName;
    QString  m_strClassName;
    bool  m_bIsChecked;
    QFont   m_Font;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
signals:
    void LabelChecked();
    void LabelDoubleclicked();
};

#endif // CLASSMOULD_H
