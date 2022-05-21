#ifndef CALCULATE_H
#define CALCULATE_H

#include <QMainWindow>

namespace Ui {
    class Calculate;
}


class Calculate : public QMainWindow
{
    Q_OBJECT
public:
    explicit Calculate(QWidget *parent = 0);
    ~Calculate();

private:
    Ui::Calculate *ui;

private slots:
    void NumberPressed();
    void MathButtonPressed();      // + or -
    void EqualButtonPressed();
    void ClearPressed();
};

#endif // CALCULATE_H
