#ifndef _miniSniffer_h
#define _miniSniffer_h

#include "aq.h"
#ifdef USE_SNIFFER_BOX
#include "serial.h"
#include "comm.h"
#include "aq_mavlink.h"
#include "mavlink.h"
#include "../mavlink_types.h"
#define MAXCHARRECEIVE 5

typedef struct {
    uint8_t active;
    uint8_t cnt;
    char send_msg[5];
    mavlink_status_t mavlinkStatus;
    uint8_t recv_msg[MAXCHARRECEIVE];
    mavlink_detechtor_t send_mav_msg;
    uint8_t state;
    uint8_t valueCnt;
    uint8_t c;
    uint8_t newMessage;
    uint8_t aux;
    uint8_t trailer;
    uint8_t count;
} miniSniffer_t;

extern void SnifferSendToTX(void);
extern void SnifferInit(void);
void SnifferRecvTaskCode(commRcvrStruct_t *r);
extern miniSniffer_t MiniSnifferData;

#endif


#endif