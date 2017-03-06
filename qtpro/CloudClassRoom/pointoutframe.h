#ifndef POINTOUTFRAME_H
#define POINTOUTFRAME_H

#include <QFrame>

namespace Ui {
class PointOutFrame;
}

class PointOutFrame : public QFrame
{
    Q_OBJECT

public:
    explicit PointOutFrame(QWidget *parent = 0);
    ~PointOutFrame();

private:
    Ui::PointOutFrame *ui;
};

#endif // POINTOUTFRAME_H
