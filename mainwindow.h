#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QScreen>
#include <QMainWindow>
#include <QListView>
#include <QListWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QDebug>

#include "pageregistration.h"
#include "pageenter.h"
#include "pageexit.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onClickedRegistration();
    void onClickedEnter();
    void onClickedExit();

private:
    void createUi();
    void setSize();
    void loadActiveWorkers();

private:
    QScopedPointer<PageRegistration> pageRegistration;
    QScopedPointer<PageEnter> pageEnter;
    QScopedPointer<PageExit> pageExit;
    QScopedPointer<QListWidget> listWidget;
};
#endif // MAINWINDOW_H
