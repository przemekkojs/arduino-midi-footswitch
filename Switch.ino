#include "MIDIUSB.h"

/// Standard debounce time for buttons.
const unsigned long BOUNCE_TIME = 50;

/// Number of buttons in the board.
const int NUM_OF_BUTTONS = 16;

/// MIDI channel used.
const int CHANNEL = 0;

/// MIDI velocity used.
const int VELOCITY = 127;

/** 
 * MIDI NOTE TO PIN
 * ====================
 * 111 : 2
 * 112 : 3
 * 113 : 4
 * 114 : 5
 * 115 : 6
 * 116 : 8
 * 117 : 9
 * 118 : 10
 * 119 : 12
 * 120 : 13
 * 121 : A0
 * 122 : A1
 * 123 : A2
 * 124 : A3
 * 125 : A4
 * 126 : A5
 */

/**
 * Debounce times array for all buttons 1 - 16.
 */
unsigned long debounceTimes[NUM_OF_BUTTONS] = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};

/**
 * MIDI note pitches for buttons, to trigger actions.
 * Why 111-126? These pitches are not commonly used in organ MIDI (usually notes 32 - 96 are used).
 */
const byte notePitches[NUM_OF_BUTTONS] = {
    111, 112, 113, 114,
    115, 116, 117, 118,
    119, 120, 121, 122,
    123, 124, 125, 126
};

/**
 * Map of pins - only these are used.
 */
const uint8_t buttons[NUM_OF_BUTTONS] = {
    2, 3, 4, 5,
    6, 8, 9, 10,
    12, 13, A0, A1,
    A2, A3, A4, A5
};

/**
 * Array of current buttons pressed state - which buttons are currently on and which are not.
 */
bool pressed[NUM_OF_BUTTONS] = {
    false, false, false, false,
    false, false, false, false,
    false, false, false, false,
    false, false, false, false
};

/**
 * Current logical state of buttons.
 */
uint8_t currentStates[NUM_OF_BUTTONS] = {
    HIGH, HIGH, HIGH, HIGH,
    HIGH, HIGH, HIGH, HIGH,
    HIGH, HIGH, HIGH, HIGH,
    HIGH, HIGH, HIGH, HIGH
};

/**
 * Previous state, for debouncing.
 */
uint8_t oldStates[NUM_OF_BUTTONS] = {
    HIGH, HIGH, HIGH, HIGH,
    HIGH, HIGH, HIGH, HIGH,
    HIGH, HIGH, HIGH, HIGH,
    HIGH, HIGH, HIGH, HIGH
};

/**
 * Sends MIDI event, to turn on the note.
 * @param noteIndex Which MIDI note should be turned on.
 */
void noteOn(byte noteIndex) {
    midiEventPacket_t noteOn = { 0x09, 0x90 | CHANNEL, notePitches[noteIndex], VELOCITY };
    MidiUSB.sendMIDI(noteOn);
    MidiUSB.flush();
}

/** 
 * Sends MIDI event, to turn off the note.
 * 
 * @param noteIndex - which MIDI note should be turned off.
 */
void noteOff(byte noteIndex) {
    midiEventPacket_t noteOff = { 0x08, 0x80 | CHANNEL, notePitches[noteIndex], VELOCITY };
    MidiUSB.sendMIDI(noteOff);
    MidiUSB.flush();
}

/**
 * Main function - checks all buttons, if any got pressed.
 */
void readButtons() {
    for (int index = 0; index < NUM_OF_BUTTONS; index++) {
        int reading = digitalRead(buttons[index]);

        if (reading != oldStates[index])
            debounceTimes[index] = millis();

        if ((millis() - BOUNCE_TIME) > debounceTimes[index]) {  
            if (reading != currentStates[index]) {
                currentStates[index] = reading;

                if (currentStates[index] == LOW) {
                    pressed[index] = !pressed[index];
                    pressed[index] ? noteOn(index) : noteOff(index);
                }
            }            
        }

        oldStates[index] = reading;     
    }
}

/**
 * Arduinos built-in function setup() - for initialisation.
 */
void setup() {
    if (NUM_OF_PUSH_BUTTONS > NUM_OF_BUTTONS || NUM_OF_PUSH_BUTTONS < 1) {
        while(1) { // Just to stop the execution. There is no exception handling in C, so I had to do it like that. If you have any ideas how to do it other way, make an issue.
        }
    }

    for (int index = 0; index < NUM_OF_BUTTONS; index++)
        pinMode(buttons[index], INPUT_PULLUP);
}

/**
 * Arduinos built-in function loop() - for running the program.
 */
void loop() {
    readButtons();
}
