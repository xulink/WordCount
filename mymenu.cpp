#include "mymenu.h"
#include "QMenu"
#include "QMenuBar"
#include "QAction"
#include "QMessageBox"
#include <QApplication>
#include "QFileDialog"
#include "QDebug"
/****************************************
* Qt中创建菜单和工具栏需要如下步骤：
* 1. 建立行为Aciton
* 2. 创建菜单并使它与一个行为关联
* 3. 创建工具条并使它与一个行为关联
*****************************************/
mymenu::mymenu(QWidget *parent):QMainWindow(parent)
{
   createAction();
   createMenu();
   createContentMenu();
   this->resize(300,400);
   aaaa();
}
void mymenu::createAction()
{
    //创建打开文件动作
    fileOpenAction = new QAction(tr("打开文件"),this);
    //摄者打开文件的快捷方式
    fileOpenAction->setShortcut(tr("Ctrl+O"));
    //设置打开文件动作提示信息
    fileOpenAction->setStatusTip("打开一个文件");
    //关联打开文件动作的信号和槽
    connect(fileOpenAction,SIGNAL(triggered()),this,SLOT(fileOpenActionSlot()));
}
void mymenu::createMenu()
{
    menu = this->menuBar()->addMenu(tr("请选择一个程序文件或文本文件"));
    menu->addAction(fileOpenAction);
}

void mymenu::createContentMenu()
{
    this->addAction(fileOpenAction);
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void mymenu::fileOpenActionSlot()
{
    //QMessageBox::warning(this,tr("提示"),tr("打开文件"),QMessageBox::Yes|QMessageBox::No);
    selectFile();
}
/****************************************
* Qt中使用文件选择对话框步骤如下：
* 1. 定义一个QFileDialog对象
* 2. 设置路径、过滤器等属性
*****************************************/
void mymenu::selectFile()
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("选取文件"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("Images(*.c *.txt *.cpp)"));
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
    QStringList fileNames;
    if(fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
    }
    for(auto tmp:fileNames)
        qDebug()<<tmp<<endl;
}
void mymenu::aaaa()
{
}
