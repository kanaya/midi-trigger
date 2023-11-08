// v0.0.4

#include <MIDI.h>

// Simple tutorial on how to receive and send MIDI messages.
// Here, when receiving any message on channel 4, the Arduino
// will blink a led and play back a note for 1 second.

#define N 5

#define OUTPUT_CHS OUTPUT_CHS1

const int DTCT0 = 6;
const int DTCT1 = 9;
const int DTCT2 = 10;
const int DTCT3 = 12;
const int ANLG0 = A0;
const int ANLG1 = A1;
const int ANLG2 = A2;
const int ANLG3 = A3;

const int OUTPUT_CHS1[N] = { 1, 2, 3, 4, 5 };
const int OUTPUT_CHS2[N] = { 6, 7, 8, 9, 10 };
const int OUTPUT_CHS3[N] = { 11, 12, 13, 14, 15 };

const int triggers[N] = { DTCT0, ANLG0, DTCT1, ANLG1, DTCT2 };
static int status[N] = { HIGH, HIGH, HIGH, HIGH, HIGH };

MIDI_CREATE_DEFAULT_INSTANCE();

void blink_led() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    for (int i = 0; i < N; ++i) {
      pinMode(triggers[i], INPUT_PULLUP);
    }
    MIDI.begin(4);                      // Launch MIDI and listen to channel 4
    for (int i = 0; i < N; ++i) {
      MIDI.sendNoteOff(60 + i, 0, 1);
    }
}

void status_change(int n) {
  MIDI.sendNoteOn(60 + n, 127, 1);
  blink_led();
}

void check_status() {
  for (int i = 0; i < N; ++i) {
    int s = digitalRead(triggers[i]);
    if (s != status[i]) {
      if (status[i] == LOW) {
        status[i] = HIGH;
      }
      else {
        status[i] = LOW;
        status_change(i);
      }
    }
  }
}

void loop() {
  check_status();
  delay(100);
}
