#ifndef PASSWORDUI_H
#define PASSWORDUI_H

#include <QWidget>
#include <QString>
#include <QDialog>

namespace Ui {
class PasswordUI;
}

class PasswordUI : public QWidget
{
    Q_OBJECT

public:
    explicit PasswordUI(QWidget *parent = 0);
    ~PasswordUI();
public:
    static bool isAdjustPass();
signals:
    void ShowPassUI();
private slots:
    void OnOk();
    void OnCancel();
    void exit_widget();
private:
    Ui::PasswordUI *ui;
    QString   m_strPassword;
    static bool   m_isAdjust;
    QDialog*     m_tmpDialog;
};
#endif // PASSWORDUI_H
