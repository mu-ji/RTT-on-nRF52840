#ifndef __CWELLKNOWN_H
#define __CWELLKNOWN_H

/**
\addtogroup AppCoAP
\{
\addtogroup cwellknown
\{
*/

#include "config.h"
#include "coap.h"

//=========================== define ==========================================

//=========================== typedef =========================================

//=========================== variables =======================================

typedef struct {
    coap_resource_desc_t desc;
    uint8_t medType;
} cwellknown_vars_t;

//=========================== prototypes ======================================

void cwellknown_init(void);

/**
\}
\}
*/

#endif
