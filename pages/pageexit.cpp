#include "pageexit.h"

PageExit::PageExit() : PageBase()
{

}

Worker PageExit::execPage()
{
    const QString id = QInputDialog::getText(nullptr, __FUNCTION__, "Please, enter your id");
    if (id.isEmpty()) {
        QMessageBox::information(nullptr, __FUNCTION__, "Id cannot be empty!");
        return {};
    }
    if (managerDb.workerExist(id)) {
        const bool ret = managerDb.updateFinishWorkerTime(id, QDateTime::currentDateTime().toString(Worker::getDateTimeFormat()));
        if (ret) {
            return managerDb.getWorker(id);
        }
    }
    return {};
}
