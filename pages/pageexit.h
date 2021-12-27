#ifndef PAGEEXIT_H
#define PAGEEXIT_H

#include "pagebase.h"

class PageExit : public PageBase
{
public:
    PageExit();

    virtual Worker execPage() override;
};

#endif // PAGEEXIT_H
