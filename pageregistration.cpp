#include "pageregistration.h"

PageRegistration::PageRegistration() : PageBase()
{

}

Worker PageRegistration::execPage()
{
    QDialog dialog;
    QGridLayout gLayout;
    gLayout.addWidget(new QLabel("Name:"), 0, 0);
    auto *lineEditName = new QLineEdit();
    gLayout.addWidget(lineEditName, 0, 1);
    gLayout.addWidget(new QLabel("Surname:"), 1, 0);
    auto *lineEditSurname = new QLineEdit();
    gLayout.addWidget(lineEditSurname, 1, 1);
    gLayout.addWidget(new QLabel("Age:"), 2, 0);
    auto *lineEditAge = new QLineEdit();
    gLayout.addWidget(lineEditAge, 2, 1);
    gLayout.addWidget(new QLabel("Speciality:"), 3, 0);
    auto *lineEditSpeciality = new QLineEdit();
    gLayout.addWidget(lineEditSpeciality, 3, 1);

    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    gLayout.addWidget(buttonBox, 4, 1);
    dialog.setLayout(&gLayout);
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    if (dialog.exec() == QDialog::Rejected) {
        return Worker{};
    }

    const QString name        = lineEditName->text();
    const QString surname     = lineEditSurname->text();
    const QString age         = lineEditAge->text();
    const QString speciality  = lineEditSpeciality->text();

    if (name.isEmpty() || surname.isEmpty() || age.isEmpty() || speciality.isEmpty()){
        QMessageBox::information(nullptr, __FUNCTION__, "Error! Fields cannot be empty!");
        return {};
    }
    if (!managerDb.workerExist(name, surname, age, speciality)) {
        return managerDb.createWorker(name, surname, age, speciality);
    }
    QMessageBox::information(nullptr, __FUNCTION__, "Worker already exist!");
    return {};
}
