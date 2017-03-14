#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QPainter>
#include <QTimer>

#define DIALOGPNG       "/usr/local/shencloud/image/DialogBack.png"

#define DIALOGOKPNG     "QPushButton{border-image: url(/usr/local/shencloud/image/DialogOK.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/DialogOKPress.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/DialogOK.png)}"

#define DIALOGCANCELPNG "QPushButton{border-image: url(/usr/local/shencloud/image/DialogCancel.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/DialogCancelPress.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/DialogCancel.png)}"

#define  SHUTDOWN   0
#define  PASSFAILD  3

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);
    ~MyDialog();
    void setText(QString Text);
    void setFlag(int flag){m_flag = flag;}
    void setNetOff(QString text, int flag);
    void setShow(bool show) {
        m_show = show;
    }
    bool getShow(){
        return m_show;
    }
private slots:
    void on_OKpushButton_clicked();
    void on_CancelpushButton_clicked();
    void exit_widget();
    void update();
private:
    Ui::MyDialog *ui;
    QLabel  *m_pTextLabel;
    QPushButton *m_pOKPushButton;
    QPushButton *m_pCancelPushButton;
    QFont   m_Font;
    int m_flag;
    QString  m_content;
    QTimer  *m_timer;
    int      m_nCount;
    bool     m_show;
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // MYDIALOG_H
