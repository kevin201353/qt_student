#ifndef WAITSTU2_H
#define WAITSTU2_H

#include <QWidget>

namespace Ui {
class waitstu2;
}

class waitstu2 : public QWidget
{
    Q_OBJECT

public:
    explicit waitstu2(QWidget *parent = 0);
    ~waitstu2();

private:
    Ui::waitstu2 *ui;
};

#endif // WAITSTU2_H
