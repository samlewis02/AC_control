
/*
   Read files from SPIFFS and form databuffer containing integers
   Return the length of the buffer
*/
#include "Arduino.h"
#include "FS.h"
#include <prepare_files.h>
#include <DebugMacros.h>

int fileToBuff (uint16_t buff[], String afile) {
  uint16_t s;
  long input;
  uint16_t idx = 0;
  File fname;

  fname = SPIFFS.open( afile, "r");
  if (!fname) {
    DPRINT("Could not open ");
    DPRINTLN(fname);
  } else {
    s = fname.size(); // only used for DEBUG
    DPRINT("Size= "); DPRINTLN(s);
    input = fname.parseInt(); // parse SPIFFS text file extracting integers
    while (input != 0) {
      buff[idx] = int(input);
      //Serial.printf("dataBuffer[%d]=%d\r\n", bufferLength[i], dataBuffer[i][bufferLength[i]]);
      input = fname.parseInt();
      idx++;
    }
    DPRINT("bufferLength = "); DPRINTLN(idx);
  }
  fname.close();
  return idx;
}
