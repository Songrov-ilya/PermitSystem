#include "pageenter.h"

PageEnter::PageEnter() : PageBase()
{

}

Worker PageEnter::execPage()
{
    const QString id = QInputDialog::getText(nullptr, __FUNCTION__, "Please, enter your id");
    if (id.isEmpty()) {
        QMessageBox::information(nullptr, __FUNCTION__, "Id cannot be empty!");
        return {};
    }
    if (managerDb.workerExist(id)) {
        const auto worker   = managerDb.getWorker(id);
        if (!worker.isWorkerActive()) {
            const bool ret      = managerDb.updateStartWorkerTime(id, QDateTime::currentDateTime().toString(Worker::getDateTimeFormat()));
            if (ret) {
                return managerDb.getWorker(id);
            }
        }
    }
    else{
        QMessageBox::information(nullptr, __FUNCTION__, "Id does not exist!");
    }
    return {};
}
