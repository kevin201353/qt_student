#include "pointoutframe.h"
#include "ui_pointoutframe.h"

PointOutFrame::PointOutFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PointOutFrame)
{
    ui->setupUi(this);
}

PointOutFrame::~PointOutFrame()
{
    delete ui;
}
