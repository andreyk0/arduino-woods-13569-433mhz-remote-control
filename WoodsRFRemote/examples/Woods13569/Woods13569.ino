
#include <WoodsRFRemote.h>

// connected digital pin (2) to 433mhz transmitter data pin
WoodsRFRemote woodsRf(2);

void setup() {
  // debugging and sensors data back to host
  Serial.begin(115200);
  Serial.println("Remote control started.");
}

void loop() {
  // 0-indexed outlets
  for(int i=0; i<3; i++) {
    Serial.print(i);
    Serial.println(" on");
    woodsRf.sendCommand(i, ON);
    delay(1000);

    Serial.print(i);
    Serial.println(" off");
    woodsRf.sendCommand(i, OFF);
    delay(1000);
  }
}
