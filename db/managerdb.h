#ifndef MANAGERDB_H
#define MANAGERDB_H

#include <QObject>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "worker.h"

class ManagerDb : public QObject
{
    Q_OBJECT
public:
    explicit ManagerDb(QObject *parent = nullptr);
    ~ManagerDb();

    Worker createWorker(const QString &name, const QString &surname, const QString &age, const QString &speciality);
    Worker getWorker(const QString &name, const QString &surname, const QString &age, const QString &speciality);
    Worker getWorker(const QString &id);
    QVector<Worker> getAllWorkers();
    bool updateStartWorkerTime(const QString &id, const QString &start_work_time);
    bool updateFinishWorkerTime(const QString &id, const QString &finish_work_time);

    bool workerExist(const QString &name, const QString &surname, const QString &age, const QString &speciality);
    bool workerExist(const QString &id);

private:
    bool createWorkerTable();
    Worker getWorkerFromRecord(const QSqlRecord& record, QSqlQuery &query);

private:
    QSqlDatabase db;
    const QString key_workers;
};

#endif // MANAGERDB_H
