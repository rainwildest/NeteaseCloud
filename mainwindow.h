#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initTitle();
    void changeMaxPix();
protected:
    bool eventFilter(QObject *object, QEvent *event);

private:
    Ui::MainWindow *ui;
    QPoint dragPosition; /* 鼠标上一次的位置 */
    bool hasClick = false;
};
#endif // MAINWINDOW_H
