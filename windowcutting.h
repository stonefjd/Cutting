#ifndef WINDOWCUTTING_H
#define WINDOWCUTTING_H

#include <QMainWindow>

namespace Ui {
class WindowCutting;
}

class WindowCutting : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowCutting(QWidget *parent = nullptr);
    ~WindowCutting();

private:
    Ui::WindowCutting *ui;
};

#endif // WINDOWCUTTING_H
