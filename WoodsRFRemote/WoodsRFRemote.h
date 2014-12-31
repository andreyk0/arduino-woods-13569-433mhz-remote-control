
// Woods power outlet RF remote 433mhz 

#ifndef WOODS_RF_REMOTE_H
#define WOODS_RF_REMOTE_H

#include <Arduino.h>

#define ON (true)
#define OFF (false)

#define NUM_RF_RC_OUTLETS 3

class WoodsRFRemote {
  public:
    // channel: 'F', 'D'
    WoodsRFRemote(const char channel, const byte outPin);
    void sendCommand(uint8_t outlet, bool isOn, uint8_t numTimes = 10);

  private:
    const char channel;
    const byte outPin;

    inline void sendPause() {
      delayMicroseconds(10000);
    }

    inline void sendBit0() {
      digitalWrite(outPin, HIGH);
      delayMicroseconds(522);
      digitalWrite(outPin, LOW);
      delayMicroseconds(1855);
    }

    inline void sendBit1() {
      digitalWrite(outPin, HIGH);
      delayMicroseconds(1735);
      digitalWrite(outPin, LOW);
      delayMicroseconds(647);
    }
};


#endif
