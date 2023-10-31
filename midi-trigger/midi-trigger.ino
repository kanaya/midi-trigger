#include <MIDI.h>

// Simple tutorial on how to receive and send MIDI messages.
// Here, when receiving any message on channel 4, the Arduino
// will blink a led and play back a note for 1 second.

#define N 5

const int triggers[N] = { A0, 6, 9, 10, 12 };
static int status[N] = { LOW, LOW, LOW, LOW, LOW };

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
}

void status_change(int n) {
  MIDI.sendNoteOn(60 + n, 127, 1);    // Send a Note (pitch 42, velo 127 on channel 1)
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
      }
      status_change(i);
    }
  }
}

void loop() {
  check_status();
  delay(100);
}
