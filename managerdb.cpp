#include "managerdb.h"

ManagerDb::ManagerDb(QObject *parent) : QObject(parent)
  , db(QSqlDatabase::addDatabase("QSQLITE", __FUNCTION__))
  , key_workers("workers")
{
    const QString pathDb = "permitSystem.db";
    db.setDatabaseName(pathDb);
    if(!db.open()){
        qCritical() << "Database not opened!" << pathDb << Qt::endl;
        return;
    }
    createWorkerTable();
}

ManagerDb::~ManagerDb()
{
    if (db.isOpen()){
        db.close();
    }
}

Worker ManagerDb::createWorker(const QString &name, const QString &surname, const QString &age, const QString &speciality)
{
    if (name.isEmpty() || surname.isEmpty() || age.isEmpty() || speciality.isEmpty()){
        qWarning() << Q_FUNC_INFO << "failed: value cannot be empty" << Qt::endl;
        return {};
    }
    QSqlQuery query(db);
    query.prepare(QString("INSERT INTO %1 (name, surname, age, speciality) VALUES (:name, :surname, :age, :speciality)").arg(key_workers));
    query.bindValue(":name"             , name);
    query.bindValue(":surname"          , surname);
    query.bindValue(":age"              , age);
    query.bindValue(":speciality"       , speciality);
    if(query.exec()){
        return getWorker(name, surname, age, speciality);
    }
    qWarning() << Q_FUNC_INFO << "failed: " << query.lastError() << Qt::endl;
    return {};
}

Worker ManagerDb::getWorker(const QString &name, const QString &surname, const QString &age, const QString &speciality)
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + key_workers + " WHERE name = :name"
                                                        " AND surname = :surname"
                                                        " AND age = :age"
                                                        " AND speciality = :speciality");
    query.bindValue(":name"             , name);
    query.bindValue(":surname"          , surname);
    query.bindValue(":age"              , age);
    query.bindValue(":speciality"       , speciality);
    if(!query.exec()){
        qWarning() << Q_FUNC_INFO << "failed: " << query.lastError() << Qt::endl;
        return {};
    }
    const QSqlRecord record = query.record();
    return getWorkerFromRecord(record, query);
}

Worker ManagerDb::getWorker(const QString &id)
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + key_workers + " WHERE id = :id");
    query.bindValue(":id"             , id);
    if(!query.exec()){
        qWarning() << Q_FUNC_INFO << "failed: " << query.lastError() << Qt::endl;
        return {};
    }
    const QSqlRecord record = query.record();
    return getWorkerFromRecord(record, query);
}

QVector<Worker> ManagerDb::getAllWorkers()
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + key_workers);
    if(!query.exec()){
        qWarning() << Q_FUNC_INFO << "failed: " << query.lastError() << Qt::endl;
        return {};
    }
    const QSqlRecord record = query.record();
    const int id_id                 = record.indexOf("id");
    const int id_name               = record.indexOf("name");
    const int id_surname            = record.indexOf("surname");
    const int id_age                = record.indexOf("age");
    const int id_speciality         = record.indexOf("speciality");
    const int id_start_work_time    = record.indexOf("start_work_time");
    const int id_finish_work_time   = record.indexOf("finish_work_time");
    QVector<Worker> vec;
    while (query.next())
    {
        const QString str_id                = query.value(id_id).toString();
        const QString str_name              = query.value(id_name).toString();
        const QString str_surname           = query.value(id_surname).toString();
        const QString str_age               = query.value(id_age).toString();
        const QString str_speciality        = query.value(id_speciality).toString();
        const QString str_start_work_time   = query.value(id_start_work_time).toString();
        const QString str_finish_work_time  = query.value(id_finish_work_time).toString();
        vec.append(Worker(str_id, str_name, str_surname, str_age, str_speciality, str_start_work_time, str_finish_work_time));
    }
    return vec;
}

bool ManagerDb::updateStartWorkerTime(const QString &id, const QString &start_work_time)
{
    if (id.isEmpty() || start_work_time.isEmpty()){
        qWarning() << Q_FUNC_INFO << "failed: value cannot be empty" << Qt::endl;
        return false;
    }
    QSqlQuery query(db);
    query.prepare(QString("UPDATE %1 SET start_work_time = :start_work_time"
                                    " WHERE id = :id").arg(key_workers));
    query.bindValue(":id"               , id);
    query.bindValue(":start_work_time"  , start_work_time);
    if(query.exec()){
        return true;
    }
    qWarning() << Q_FUNC_INFO << "failed: " << query.lastError() << Qt::endl;
    return false;
}

bool ManagerDb::updateFinishWorkerTime(const QString &id, const QString &finish_work_time)
{
    if (id.isEmpty() || finish_work_time.isEmpty()){
        qWarning() << Q_FUNC_INFO << "failed: value cannot be empty" << Qt::endl;
        return false;
    }
    QSqlQuery query(db);
    query.prepare(QString("UPDATE %1 SET finish_work_time = :finish_work_time"
                                    " WHERE id = :id").arg(key_workers));
    query.bindValue(":id"               , id);
    query.bindValue(":finish_work_time"  , finish_work_time);
    if(query.exec()){
        return true;
    }
    qWarning() << Q_FUNC_INFO << "failed: " << query.lastError() << Qt::endl;
    return false;
}

bool ManagerDb::workerExist(const QString &name, const QString &surname, const QString &age, const QString &speciality)
{
    QSqlQuery query(db);
    query.prepare(QString("SELECT * FROM %1 WHERE name = :name"
                                            " AND surname = :surname"
                                            " AND age = :age"
                                            " AND speciality = :speciality").arg(key_workers));
    query.bindValue(":name"         , name);
    query.bindValue(":surname"      , surname);
    query.bindValue(":age"          , age);
    query.bindValue(":speciality"   , speciality);
    if (query.exec()){
        return query.next();
    }
    qWarning() << __FUNCTION__ << "failed: " << query.lastError() << Qt::endl;
    return false;
}

bool ManagerDb::workerExist(const QString &id)
{
    QSqlQuery query(db);
    query.prepare(QString("SELECT * FROM %1 WHERE id = :id").arg(key_workers));
    query.bindValue(":id"         , id);
    if (query.exec()){
        return query.next();
    }
    qWarning() << __FUNCTION__ << "failed: " << query.lastError() << Qt::endl;
    return false;
}

bool ManagerDb::createWorkerTable()
{
    QSqlQuery query(db);
    query.prepare("CREATE TABLE IF NOT EXISTS workers ("
            "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"
            "surname TEXT NOT NULL,"
            "age TEXT NOT NULL,"
            "speciality TEXT NOT NULL,"
            "start_work_time TEXT,"
            "finish_work_time TEXT "
            ");");

    if (query.exec()){
        return true;
    }
    qWarning() << __FUNCTION__ << "Couldn't create the table:" << query.lastError() << Qt::endl;
    return false;
}

Worker ManagerDb::getWorkerFromRecord(const QSqlRecord &record, QSqlQuery &query)
{
    const int id_id                 = record.indexOf("id");
    const int id_name               = record.indexOf("name");
    const int id_surname            = record.indexOf("surname");
    const int id_age                = record.indexOf("age");
    const int id_speciality         = record.indexOf("speciality");
    const int id_start_work_time    = record.indexOf("start_work_time");
    const int id_finish_work_time   = record.indexOf("finish_work_time");
    while (query.next())
    {
        const QString str_id                = query.value(id_id).toString();
        const QString str_name              = query.value(id_name).toString();
        const QString str_surname           = query.value(id_surname).toString();
        const QString str_age               = query.value(id_age).toString();
        const QString str_speciality        = query.value(id_speciality).toString();
        const QString str_start_work_time   = query.value(id_start_work_time).toString();
        const QString str_finish_work_time  = query.value(id_finish_work_time).toString();
        return Worker(str_id, str_name, str_surname, str_age, str_speciality, str_start_work_time, str_finish_work_time);
    }
    return {};
}
