
#include "WoodsRFRemote.h"

// Channel 'F'
static const uint16_t woods_remote_outlet_codes[6] = {
  /* code1on  */ 0B0110100010000000,
  /* code1off */ 0B0110100001000000,
  /* code2on  */ 0B0110100000100000,
  /* code2off */ 0B0110100000010000,
  /* code3on  */ 0B0110100100000000,
  /* code3off */ 0B0110101000000000
};

WoodsRFRemote::WoodsRFRemote(byte outPin): outPin(outPin) {
  pinMode(outPin, OUTPUT);
}

void WoodsRFRemote::sendCommand(uint8_t outlet,
                                 bool isOn,
                                 uint8_t numTimes) {
  uint16_t code = woods_remote_outlet_codes[2*outlet + (isOn?0:1)];

  for(int i=0; i<numTimes; i++) {
    for (int shift=15; shift>=0; shift--) {
      if ((code>>shift)&1) {
        sendBit1();
      } else {
        sendBit0();
      }
    }
    sendPause();
  }
}
