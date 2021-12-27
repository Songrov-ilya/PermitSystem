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
        if (worker.isWorkerActive()) {
            vecActive.append(worker);
        }
    }
    return vecActive;
}
