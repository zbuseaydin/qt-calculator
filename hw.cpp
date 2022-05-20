#include "hw.h"
#include "ui_hw.h"

Hw::Hw(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Hw)
{
    ui->setupUi(this);
}

Hw::~Hw()
{
    delete ui;
}

