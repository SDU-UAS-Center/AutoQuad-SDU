#include "miniSniffer.h"
#ifdef USE_SNIFFER_BOX
#include "string.h"
#include "mavlink.h"

miniSniffer_t MiniSnifferData __attribute__((section(".ccm")));


float GetFloat(void) {
    union {
      float f;
      uint8_t b[sizeof(float)];
    } u;

    u.b[3] = MiniSnifferData.recv_msg[3];
    u.b[2] = MiniSnifferData.recv_msg[2];
    u.b[1] = MiniSnifferData.recv_msg[1];
    u.b[0] = MiniSnifferData.recv_msg[0];
    return u.f;
}

void SnifferRecvTaskCode(commRcvrStruct_t *r) {
    if ( commAvailable(r) ) {
        MiniSnifferData.c = commReadChar(r);
        MiniSnifferData.count++;
        switch (MiniSnifferData.state) {

            //detect start
            case 0:
                if ( MiniSnifferData.c == 1 ) {
                    MiniSnifferData.state = 1;
                    MiniSnifferData.valueCnt = 0;
                }
                else {
                    MiniSnifferData.state = 0;
                    MiniSnifferData.count = 0;
                    MiniSnifferData.valueCnt = 0;
                }
            break;

            //float no2; ///< NO2 ppm
            case 1:
                    if ( MiniSnifferData.valueCnt > MAXCHARRECEIVE ) {
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 0;
                        break;
                    }

                    MiniSnifferData.recv_msg[MiniSnifferData.valueCnt++] = MiniSnifferData.c;
                    if ( MiniSnifferData.valueCnt == sizeof(float) ) {
                        MiniSnifferData.send_mav_msg.no2 = GetFloat();
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 2;
                    }
            break;

            //float no2_voltage; ///< NO2 mV
            case 2:
                    if ( MiniSnifferData.valueCnt > MAXCHARRECEIVE ) {
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 0;
                        break;
                    }

                    MiniSnifferData.recv_msg[MiniSnifferData.valueCnt++] = MiniSnifferData.c;
                    if ( MiniSnifferData.valueCnt == sizeof(float) ) {
                        MiniSnifferData.send_mav_msg.no2_voltage = GetFloat();
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 3;
                    }
            break;

            //float no2_aux_voltage; ///< NO2-AUX mV
            case 3:
                    if ( MiniSnifferData.valueCnt > MAXCHARRECEIVE ) {
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 0;
                        break;
                    }

                    MiniSnifferData.recv_msg[MiniSnifferData.valueCnt++] = MiniSnifferData.c;
                    if ( MiniSnifferData.valueCnt == sizeof(float) ) {
                        MiniSnifferData.send_mav_msg.no2_aux_voltage = GetFloat();
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 4;
                    }
            break;

            //float so2; ///< SO2 ppm
            case 4:
                    if ( MiniSnifferData.valueCnt > MAXCHARRECEIVE ) {
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 0;
                        break;
                    }

                    MiniSnifferData.recv_msg[MiniSnifferData.valueCnt++] = MiniSnifferData.c;
                    if ( MiniSnifferData.valueCnt == sizeof(float) ) {
                        MiniSnifferData.send_mav_msg.so2 = GetFloat();
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 5;
                    }
            break;

            //float so2_voltage; ///< SO2 mV
            case 5:
                    if ( MiniSnifferData.valueCnt > MAXCHARRECEIVE ) {
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 0;
                        break;
                    }

                    MiniSnifferData.recv_msg[MiniSnifferData.valueCnt++] = MiniSnifferData.c;
                    if ( MiniSnifferData.valueCnt == sizeof(float) ) {
                        MiniSnifferData.send_mav_msg.so2_voltage = GetFloat();
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 6;
                    }
            break;

            //float so2_aux_voltage; ///< SO2-AUX mV
            case 6:
                    if ( MiniSnifferData.valueCnt > MAXCHARRECEIVE ) {
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 0;
                        break;
                    }

                    MiniSnifferData.recv_msg[MiniSnifferData.valueCnt++] = MiniSnifferData.c;
                    if ( MiniSnifferData.valueCnt == sizeof(float) ) {
                        MiniSnifferData.send_mav_msg.so2_aux_voltage = GetFloat();
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 7;
                    }
            break;

            //float no; ///< 
            case 7:
                    if ( MiniSnifferData.valueCnt > MAXCHARRECEIVE ) {
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 0;
                        break;
                    }

                    MiniSnifferData.recv_msg[MiniSnifferData.valueCnt++] = MiniSnifferData.c;
                    if ( MiniSnifferData.valueCnt == sizeof(float) ) {
                        MiniSnifferData.send_mav_msg.no = GetFloat();
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 8;
                    }
            break;

            //float noVoltage; ///< no Voltage
            case 8:
                    if ( MiniSnifferData.valueCnt > MAXCHARRECEIVE ) {
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 0;
                        break;
                    }

                    MiniSnifferData.recv_msg[MiniSnifferData.valueCnt++] = MiniSnifferData.c;
                    if ( MiniSnifferData.valueCnt == sizeof(float) ) {
                        MiniSnifferData.send_mav_msg.no_voltage = GetFloat();
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 9;
                    }
            break;


            //float noAuxVoltage; ///< no AuxVoltage
            case 9:
                    if ( MiniSnifferData.valueCnt > MAXCHARRECEIVE ) {
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 0;
                        break;
                    }

                    MiniSnifferData.recv_msg[MiniSnifferData.valueCnt++] = MiniSnifferData.c;
                    if ( MiniSnifferData.valueCnt == sizeof(float) ) {
                        MiniSnifferData.send_mav_msg.no_aux_voltage = GetFloat();
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 10;
                    }
            break;


            //float co2; ///< co2
            case 10:
                    if ( MiniSnifferData.valueCnt > MAXCHARRECEIVE ) {
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 0;
                        break;
                    }

                    MiniSnifferData.recv_msg[MiniSnifferData.valueCnt++] = MiniSnifferData.c;
                    if ( MiniSnifferData.valueCnt == sizeof(float) ) {
                        MiniSnifferData.send_mav_msg.co2 = GetFloat();
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 11;
                    }
            break;


            //float temperature; ///< Temperature C
            case 11:
                    if ( MiniSnifferData.valueCnt > MAXCHARRECEIVE ) {
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 0;
                        break;
                    }

                    MiniSnifferData.recv_msg[MiniSnifferData.valueCnt++] = MiniSnifferData.c;
                    if ( MiniSnifferData.valueCnt == sizeof(float) ) {
                        MiniSnifferData.send_mav_msg.temperature = GetFloat();
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 12;
                    }
            break;

            //float humidity; ///< Humidity RH
            case 12:
                    if ( MiniSnifferData.valueCnt > MAXCHARRECEIVE ) {
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 0;
                        break;
                    }

                    MiniSnifferData.recv_msg[MiniSnifferData.valueCnt++] = MiniSnifferData.c;
                    if ( MiniSnifferData.valueCnt == sizeof(float) ) {
                        MiniSnifferData.send_mav_msg.humidity = GetFloat();
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 13;
                    }
            break;

            //uint8_t aux; ///< aux
            case 13:
                    if ( MiniSnifferData.valueCnt > MAXCHARRECEIVE ) {
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 0;
                        break;
                    }

                    MiniSnifferData.recv_msg[MiniSnifferData.valueCnt++] = MiniSnifferData.c;
                    if ( MiniSnifferData.valueCnt == sizeof(uint8_t) ) {
                        MiniSnifferData.aux = MiniSnifferData.recv_msg[0];
                        MiniSnifferData.valueCnt = 0;
                        MiniSnifferData.state = 14;
                    }
            break;


            //detect end of frame
            case 14:
                if ( MiniSnifferData.c == 153 ) {
                    MiniSnifferData.valueCnt = 0;
                    MiniSnifferData.state = 0;
                    MiniSnifferData.newMessage = 1;
                    MiniSnifferData.count = 0;
                }
                else {
                    MiniSnifferData.valueCnt = 0;
                    MiniSnifferData.state = 0;
                    MiniSnifferData.newMessage = 0;
                    MiniSnifferData.count = 0;
                }
            break;


            default:
                MiniSnifferData.state = 0;
                MiniSnifferData.valueCnt = 0;
            break;
        }
    }
}



void SnifferSendToTX(void) {
    commTxBuf_t *txBuf;
    uint8_t *ptr;
    int i;
    sprintf(MiniSnifferData.send_msg, "%s\n", "VAL");
    MiniSnifferData.cnt = 4;
    txBuf = commGetTxBuf(COMM_STREAM_TYPE_OMAP_PPP, MiniSnifferData.cnt);
    // cannot block, must fail
    if (txBuf != 0) {
	ptr = &txBuf->buf;

	for (i = 0; i < MiniSnifferData.cnt; i++)
	    *ptr++ = MiniSnifferData.send_msg[i];

	commSendTxBuf(txBuf, MiniSnifferData.cnt);
    }
}


void SnifferInit() {
    memset((void *) &MiniSnifferData, 0, sizeof(MiniSnifferData));
    if (( p[COMM_STREAM_TYP1] == COMM_STREAM_TYPE_OMAP_PPP ) ||
        ( p[COMM_STREAM_TYP2] == COMM_STREAM_TYPE_OMAP_PPP ) ||
        ( p[COMM_STREAM_TYP3] == COMM_STREAM_TYPE_OMAP_PPP ) ||
        ( p[COMM_STREAM_TYP4] == COMM_STREAM_TYPE_OMAP_PPP ) ||
        ( p[COMM_STREAM_TYP5] == COMM_STREAM_TYPE_OMAP_PPP ) ||
        ( p[COMM_STREAM_TYP6] == COMM_STREAM_TYPE_OMAP_PPP ) ||
        ( p[COMM_STREAM_TYP7] == COMM_STREAM_TYPE_OMAP_PPP )) {
        MiniSnifferData.newMessage = 0;
        MiniSnifferData.active = 1;
        commRegisterRcvrFunc(COMM_STREAM_TYPE_OMAP_PPP, SnifferRecvTaskCode);
        AQ_NOTICE("Mini Sniffer init\n");
    }
    else {
        AQ_NOTICE("Mini Sniffer not activated\n");
    }
}


#endif