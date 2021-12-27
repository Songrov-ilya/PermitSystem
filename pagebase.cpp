#include "pagebase.h"

ManagerDb PageBase::managerDb;

PageBase::PageBase(QObject *parent) : QObject(parent)
{

}

QVector<Worker> PageBase::getActiveWorkers()
{
    const QVector<Worker> vecAll = managerDb.getAllWorkers();
    QVector<Worker> vecActive;
    for (const auto &worker: vecAll) {
        qDebug() << "worker.getStartDateTime" << worker.getStartDateTime() << Qt::endl;
        qDebug() << "worker.getFinishDateTime" << worker.getFinishDateTime() << Qt::endl;
        if (worker.isWorkerActive()) {
            vecActive.append(worker);
        }
    }
    return vecActive;
}
