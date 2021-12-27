#ifndef PAGEENTER_H
#define PAGEENTER_H

#include "pagebase.h"

class PageEnter : public PageBase
{
public:
    explicit PageEnter();

    virtual Worker execPage() override;
};

#endif // PAGEENTER_H
