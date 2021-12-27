#ifndef PAGEBASE_H
#define PAGEBASE_H

#include <QObject>
#include <QMessageBox>
#include <QInputDialog>

#include "managerdb.h"
#include "worker.h"

class PageBase : public QObject
{
    Q_OBJECT
public:
    explicit PageBase(QObject *parent = nullptr);

    virtual Worker execPage() = 0;

    static QVector<Worker> getActiveWorkers();

protected:
    static ManagerDb managerDb;
};

#endif // PAGEBASE_H
