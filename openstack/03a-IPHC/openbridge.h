#ifndef OPENWSN_OPENBRIDGE_H
#define OPENWSN_OPENBRIDGE_H

/**
\addtogroup LoWPAN
\{
\addtogroup OpenBridge
\{
*/

//=========================== define ==========================================

//=========================== typedef =========================================

//=========================== variables =======================================

//=========================== prototypes ======================================

void openbridge_init(void);

void openbridge_triggerData(void);

void openbridge_sendDone(OpenQueueEntry_t *msg, owerror_t error);

void openbridge_receive(OpenQueueEntry_t *msg);

/**
\}
\}
*/

#endif /* OPENWSN_OPENBRIDGE_H */
