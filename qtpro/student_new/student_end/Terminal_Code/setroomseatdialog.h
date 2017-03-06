#ifndef SETROOMSEATDIALOG_H
#define SETROOMSEATDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFont>

namespace Ui {
class SetRoomSeatDialog;
}

class SetRoomSeatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetRoomSeatDialog(QWidget *parent = 0);
    ~SetRoomSeatDialog();

private slots:
    void on_OKpushButton_clicked();

    void on_CancelpushButton_clicked();

private:
    Ui::SetRoomSeatDialog *ui;
    QPushButton *m_pOKPushButton;
    QPushButton *m_pCancelPushButton;
    QLineEdit   *m_pRoomNumLineEdit;
    QLineEdit   *m_pSeatNumLineEdit;
    QLabel      *m_pRoomNumLabel;
    QLabel      *m_pSeatNumLabel;
    QFont       m_Font;
};

#endif // SETROOMSEATDIALOG_H
