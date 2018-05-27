#ifndef _HAND_H_
extern IRsend irsend;
extern uint16_t dataBuffer[][500];
extern uint16_t bLength[];
void handleMessage(AdafruitIO_Data *);
#endif
