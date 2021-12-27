#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , pageRegistration(new PageRegistration)
    , pageEnter(new PageEnter)
    , pageExit(new PageExit)
    , listWidget(new QListWidget())
{
    createUi();
    setSize();
    loadActiveWorkers();
}

MainWindow::~MainWindow()
{
}

void MainWindow::onClickedRegistration()
{
    const Worker worker = pageRegistration->execPage();
    if (worker.isValid()) {
        listWidget->addItem(worker.getPublicInfo());
        QMessageBox::information(this, __FUNCTION__, "Your id: " + worker.id);
    }
}

void MainWindow::onClickedEnter()
{
    const Worker worker = pageEnter->execPage();
    if (worker.isValid()) {
        listWidget->addItem(worker.getPublicInfo());
        QMessageBox::information(this, __FUNCTION__,
                                 QString("Have a nice working day %1 %2!").arg(worker.name, worker.surname));
    }
}

void MainWindow::onClickedExit()
{
    const Worker worker = pageExit->execPage();
    if (worker.isValid()) {
        for (int var = 0; var < listWidget->count(); ++var) {
            if (listWidget->item(var)->text() == worker.getPublicInfo()){
                delete listWidget->takeItem(var);
                break;
            }
        }
        QMessageBox::information(this, __FUNCTION__,
                                 QString("Thanks for your work %1 %2!").arg(worker.name, worker.surname));
    }
}

void MainWindow::createUi()
{
    QPushButton *buttonRegistration = new QPushButton("Registration");
    QPushButton *buttonEnter        = new QPushButton("Enter");
    QPushButton *buttonExit         = new QPushButton("Exit");
    QHBoxLayout *hBoxLayout         = new QHBoxLayout();
    connect(buttonRegistration, &QPushButton::clicked, this, &MainWindow::onClickedRegistration);
    connect(buttonEnter,        &QPushButton::clicked, this, &MainWindow::onClickedEnter);
    connect(buttonExit,         &QPushButton::clicked, this, &MainWindow::onClickedExit);
    hBoxLayout->addWidget(buttonRegistration);
    hBoxLayout->addWidget(buttonEnter);
    hBoxLayout->addWidget(buttonExit);
    QVBoxLayout *vBoxLayout         = new QVBoxLayout();
    vBoxLayout->addWidget(listWidget.get());
    vBoxLayout->addLayout(hBoxLayout);
    QWidget *widget = new QWidget();
    widget->setLayout(vBoxLayout);
    setCentralWidget(widget);
    listWidget->setFont(QFont("Monospace"));
}

void MainWindow::setSize()
{
    const auto screens = QGuiApplication::screens();
    QRect rect = screens.isEmpty() ? QRect() : screens.back()->geometry();
    rect = QRect(rect.topLeft(), rect.size() / 2);
    resize(rect.size());
    move(rect.center());
}

void MainWindow::loadActiveWorkers()
{
    const auto vecActiveWorkers = PageBase::getActiveWorkers();
    for (const auto &worker: vecActiveWorkers) {
        listWidget->addItem(worker.getPublicInfo());
    }
}

