#ifndef PAGEREGISTRATION_H
#define PAGEREGISTRATION_H

#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QMessageBox>
#include "pagebase.h"

class PageRegistration : public PageBase
{
public:
    PageRegistration();

    virtual Worker execPage() override;
};

#endif // PAGEREGISTRATION_H
