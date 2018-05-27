//
// IR cotroller for bedroom A/C
// Uses input from MQTT at /io.adafruit.com/samlewis02/dashboards/buttons
// Uses two stage LED driver so IR PIN must be inverted
//
// Tested 13/5/18
//
/************************** Configuration ***********************************/
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "FS.h"
#include "config.h"
#include "DebugMacros.h"
#include "MySSID.h"
#include "AdafruitIO_WiFi.h"
#include "handler.h"
#include "prepare_files.h"
#include "common.h"


uint16_t dataBuffer[2][500];
uint16_t bLength[2];
bool ok;

IRsend irsend (IR_PIN, true, true);
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
// set up the feeds
AdafruitIO_Feed *bedroom = io.feed("bedroom"); // subscribe toggle switch input ("ON"/"OFF")

void setup() {
  pinMode(MQTT_ON, OUTPUT);
  pinMode(OFF_ON, OUTPUT);
  digitalWrite(IR_PIN, HIGH);

  digitalWrite(MQTT_ON, LOW);
  digitalWrite(OFF_ON, LOW);

  // start the serial connection
  Serial.begin(115200);
  irsend.begin();
  ok =  SPIFFS.begin();

  // Set up buffers for on and off IR sequence
  bLength[0] =  fileToBuff (dataBuffer[0], files[0]);
  bLength[1] =  fileToBuff (dataBuffer[1], files[1]);

  // connect to io.adafruit.com
  DPRINT("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'bedroom' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  bedroom->onMessage(handleMessage);

  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    DPRINT(".");
    delay(500);
  }

  // we are connected
  digitalWrite(MQTT_ON, HIGH);
  DPRINTLN();
  DPRINTLN(io.statusText());
}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

}
