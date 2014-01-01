
// Woods power outlet RF remote 433mhz 

#ifndef WOODS_RF_REMOTE_H
#define WOODS_RF_REMOTE_H

#include <Arduino.h>

#define ON (true)
#define OFF (false)

#define NUM_RF_RC_OUTLETS 3

class WoodsRFRemote {
  public:
    WoodsRFRemote(byte outPin);
    void sendCommand(uint8_t outlet, bool isOn, uint8_t numTimes = 10);

  private:
    const byte outPin;

    inline void sendPause() {
      delayMicroseconds(11980);
    }

    inline void sendBit0() {
      digitalWrite(outPin, HIGH);
      delayMicroseconds(552);
      digitalWrite(outPin, LOW);
      delayMicroseconds(1862);
    }

    inline void sendBit1() {
      digitalWrite(outPin, HIGH);
      delayMicroseconds(1772);
      digitalWrite(outPin, LOW);
      delayMicroseconds(654);
    }
};


#endif
