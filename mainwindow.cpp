#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QAction>
#include <QMouseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->initTitle();

    /* 无边框 */
    this->setWindowFlag(Qt::FramelessWindowHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTitle()
{
    /* 为标题部分添加过滤器，用于双击最大化及还原 */
    ui->titleWidget->installEventFilter(this);

    /* 为搜索框添加搜索图标 */
    QAction *action = new QAction(this);
    action->setIcon(QIcon(":/resource/search-02.png"));

    ui->lineEdit_search->addAction(action, QLineEdit::LeadingPosition);
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if(object == ui->titleWidget)
    {
        qDebug() << event->type();
        /* 鼠标点击事件 */
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *e = static_cast<QMouseEvent*>(event);
            if(e->buttons() == Qt::LeftButton)
            {
                dragPosition = e->globalPosition().toPoint();
                hasClick = true;
            }
        }

        if(event->type() == QEvent::MouseButtonRelease)
        {
            if(hasClick) hasClick = false;
        }


        /* 鼠标拖动事件 */
        if(event->type() == QEvent::MouseMove && hasClick)
        {
            /* 最大化时不允许窗口拖动，返回 false 不执行此事件 */
            if(this->windowState() == Qt::WindowMaximized)
            {
                return false;
            }

            QMouseEvent *e = static_cast<QMouseEvent*>(event);
            if(e->buttons() == Qt::LeftButton)
            {
                QPoint temPos = e->globalPosition().toPoint() - dragPosition;
                this->move(this->pos() + temPos);

                /* 更新上一次的位置 */
                dragPosition = e->globalPosition().toPoint();
            }
        }

        /* 双击标题栏实现最大化和还原 */
        if(event->type() == QEvent::MouseButtonDblClick)
        {
            QMouseEvent *e = static_cast<QMouseEvent*>(event);
            if(e->buttons() == Qt::LeftButton)
            {
                if(this->windowState() == Qt::WindowNoState)
                {
                    this->showMaximized(); // 最大化
                    changeMaxPix();
                }
                else
                {
                    this->showNormal();
                    changeMaxPix();
                }
            }
        }
    }

   return QMainWindow::eventFilter(object, event);
}

/*  */
void MainWindow::changeMaxPix()
{

}
