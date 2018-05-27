// this function is called whenever an 'bedroom' feed message
// is received from Adafruit IO. it was attached to
// the 'bedroom' feed in the setup() function above.
#include "AdafruitIO_WiFi.h"
#include <IRsend.h>
#include "common.h"
#include "handler.h"
#include "DebugMacros.h"


void handleMessage(AdafruitIO_Data *data) {

  DPRINT("bedroom received <- ");

  if (data->toString() == "ON") {
    DPRINTLN("ON");
    DPRINTLN("Sending on data to IR led");
    irsend.sendRaw(dataBuffer[0], bLength[0], khz);
    digitalWrite(OFF_ON, HIGH);
  }
  else if (data->toString() == "OFF") {
    DPRINTLN("OFF");
    DPRINTLN("Sending off data to IR led");
    irsend.sendRaw(dataBuffer[1], bLength[1], khz);
    digitalWrite(OFF_ON, LOW);
  }
  digitalWrite(IR_PIN, HIGH);
}
