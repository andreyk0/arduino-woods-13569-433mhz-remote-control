
#include "WoodsRFRemote.h"

#if (defined(__AVR__))
#include <avr\pgmspace.h>
#else
#include <pgmspace.h>
#endif

#define NUM_CODES (2*NUM_RF_RC_OUTLETS)

// measured
static const uint16_t woods_remote_outlet_codes_F [NUM_CODES] PROGMEM = {
  /* code1on  */ 0B0110100010000000,
  /* code1off */ 0B0110100001000000,
  /* code2on  */ 0B0110100000100000,
  /* code2off */ 0B0110100000010000,
  /* code3on  */ 0B0110100100000000,
  /* code3off */ 0B0110101000000000
};

// contributed by https://github.com/dkisselev
static const uint16_t woods_remote_outlet_codes_D [NUM_CODES] PROGMEM = {
  /* code1on  */ 0B0110100010000001,
  /* code1off */ 0B0110100001000001,
  /* code2on  */ 0B0110100000100001,
  /* code2off */ 0B0110100000010001,
  /* code3on  */ 0B0110100100000001,
  /* code3off */ 0B0110101000000001
};

WoodsRFRemote::WoodsRFRemote(const char channel,
                             const byte outPin): channel(channel),
                                                 outPin(outPin) {
  pinMode(outPin, OUTPUT);
}

void WoodsRFRemote::sendCommand(uint8_t outlet,
                                bool isOn,
                                uint8_t numTimes) {
  int idx = 2*outlet + (isOn?0:1);

  if (idx >= NUM_CODES) { // out of range
    return;
  }

  uint16_t code;

  switch (channel) {
    case 'D':
      code = pgm_read_word_near(&(woods_remote_outlet_codes_D[idx]));
      break;

    default:
      code = pgm_read_word_near(&(woods_remote_outlet_codes_F[idx])); // always init to something
      break;
  }

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
