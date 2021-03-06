/***************************************
  This shows the use of the Snooze USB
  Serial driver when using Hibernate.
  The USB Serial driver does not wake the
  processor it only aids in using the USB
  Serial in sleeping appilcations.
 ****************************************/
#include <Snooze.h>
// Load drivers
SnoozeDigital   digital;
SnoozeCompare   compare;
SnoozeTimer     timer;
SnoozeTouch     touch;
SnoozeAlarm	    alarm;
SnoozeUSBSerial usb;

/***********************************************************
  Install drivers, timer to wake and USB Serial to fix printing
  to serial monitor after sleeping.
 ***********************************************************/
#if defined(__MK66FX1M0__)
SnoozeBlock config_teensy36(usb, timer);
#elif defined(__MK64FX512__)
SnoozeBlock config_teensy35(usb, timer;
#elif defined(__MK20DX256__)
SnoozeBlock config_teensy32(usb, timer);
#elif defined(__MKL26Z64__)
SnoozeBlock config_teensyLC(usb, timer);
#endif

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  while (!Serial);
  delay(100);
  Serial.println("Starting...");
  delay(100);
  /********************************************************
    Set Low Power Timer wake up in milliseconds.
   ********************************************************/
  timer.setTimer(1000);// milliseconds
}

void loop() {
  int who = 0;
  /********************************************************
    feed the sleep function its wakeup parameters. Then go
    into Hibernate.
   ********************************************************/
#if defined(__MK66FX1M0__)
  who = Snooze.hibernate( config_teensy36 );// return module that woke processor
#elif defined(__MK64FX512__)
  who = Snooze.hibernate( config_teensy35 );// return module that woke processor
#elif defined(__MK20DX256__)
  who = Snooze.hibernate( config_teensy32 );// return module that woke processor
#elif defined(__MKL26Z64__)
  who = Snooze.hibernate( config_teensyLC );// return module that woke processor
#endif
  // wait for serial monitor
  while (!Serial) {
    digitalWriteFast(LED_BUILTIN, HIGH);
    delay(30);
    digitalWriteFast(LED_BUILTIN, LOW);
    delay(30);
  }
  delay(200); // normal delay for Arduino Serial Monitor
  Serial.printf("Timer Driver number indicator: %i\n", who); // print who woke up, i.e. timer
  delay(1000);
}
