#ifndef WORKER_H
#define WORKER_H

#include <QString>
#include <QDateTime>

struct Worker
{
    QString id              ;
    QString name            ;
    QString surname         ;
    QString age             ;
    QString speciality      ;
    QString start_work_time ;
    QString finish_work_time;

    Worker(){}
    Worker(const QString &i, const QString &na, const QString &su,
           const QString &ag, const QString &sp,
           const QString &swt, const QString &fwt)
        : id(i), name(na), surname(su), age(ag), speciality(sp)
        , start_work_time(swt), finish_work_time(fwt) {}

    bool isValid() const { return !id.isEmpty()
                && !name.isEmpty()
                && !surname.isEmpty()
                && !age.isEmpty()
                && !speciality.isEmpty()
                ; };
    QString getPublicInfo() const {
        return name.leftJustified(30 - name.size())
                + " " + surname.leftJustified(30 - surname.size())
                + " " + age.leftJustified(30 - age.size())
                + " " + speciality.leftJustified(30 - speciality.size())
                + " " + start_work_time.leftJustified(30 - start_work_time.size())
                ;
    }
    QDateTime getStartDateTime() const {return QDateTime::fromString(start_work_time, getDateTimeFormat());};
    QDateTime getFinishDateTime() const {return QDateTime::fromString(finish_work_time, getDateTimeFormat());};
    bool isWorkerActive() const { return getStartDateTime() > getFinishDateTime(); };

    static QString getDateTimeFormat(){
        return "yyyy-MM-dd_hh:mm:ss.zzz";
    }
};

#endif // WORKER_H
