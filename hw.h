#ifndef HW_H
#define HW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Hw; }
QT_END_NAMESPACE

class Hw : public QMainWindow
{
    Q_OBJECT

public:
    Hw(QWidget *parent = nullptr);
    ~Hw();

private:
    Ui::Hw *ui;
};
#endif // HW_H
