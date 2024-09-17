
# DIY MIDI Footswitch  
**Author**: Przemysław Kojs  
**License**: GNU v3 Public License  
**Version**: v1.0 (Oct. 17, 2024)

## Introduction
This project was inspired by the lack of a 16-button MIDI footswitch available on the internet, which I needed for a handmade electronic pipe organ console. I already had some background in Arduino programming and know C/C++ well, so I decided to create one myself. The design took several days, but coding only took a few hours. Since we are on **GitHub**, I will focus solely on the Arduino and MIDI-related aspects of the project.

## Overview
The project uses the standard [Arduino MIDIUSB library](https://github.com/arduino-libraries/MIDIUSB). The code is designed for 16 buttons, requiring 16 pins. In my case, I used digital pins 2-6, 8-10, 12, 13, and all analog pins (A0-A5). If you need fewer pins, you can modify the necessary variables. All array lengths must match and be equal to the `NUM_OF_BUTTONS` constant. **Remember to also adjust the `NUM_OF_PUSH_BUTTONS` constant, ensuring its value is less than or equal to `NUM_OF_BUTTONS`.**

Most of the pins, once connected to the buttons, act as toggle switches. However, pins A2-A5 (buttons 12-15) function as push buttons. This configuration is specific to my needs and is available in the *ButtonSwitch.ino* file. In contrast, in the *Switch.ino* file, all pins behave like toggle buttons.

> **Which one should I choose?**  
If you need something like a **guitar pedalboard**—where all buttons are toggle buttons—use the *Switch.ino* file. If you need some buttons to behave as push buttons, use the *ButtonSwitch.ino* file.

The number of push buttons can be changed by modifying the `NUM_OF_PUSH_BUTTONS` constant, located at the beginning of the file (**line 10**).

MIDI notes used range from 111 to 126. If you want a specific button to trigger an action, assign it to a MIDI note. I suggest creating a reference scheme for which button is connected to which pin and which MIDI note, as you may want to make changes in the future.

### Electronics Used
1. Arduino Leonardo (with a Micro-USB cable). Alternatives include the *Zero*, *Due*, *101*, and *Micro*.
2. Wires
3. 16 arcade push buttons  
   **Important:** LEDs in the buttons are non-functional due to a lack of available pins and wires.

### Pin Mappings
Pins are arranged in ascending order, corresponding to the MIDI notes used. You can modify this arrangement if necessary, but **duplicate pin assignments may cause issues with the code**.

*Table 1. Pin to MIDI Note Mappings.*  
| Pin | MIDI Note |
| --- | --------- |
| 2   | 111       |
| 3   | 112       |
| 4   | 113       |
| 5   | 114       |
| 6   | 115       |
| 8   | 116       |
| 9   | 117       |
| 10  | 118       |
| 12  | 119       |
| 13  | 120       |
| A0  | 121       |
| A1  | 122       |
| A2  | 123       |
| A3  | 124       |
| A4  | 125       |
| A5  | 126       |

### Other Information
*Table 2. MIDI Information.*  
| MIDI Info | Value |
| --------- | ----- |
| Velocity  | 127   |
| Channel   | 0     |

**Note:** Multiple channels are not supported. If you need this functionality, **you will need to modify the code yourself**.

*Table 3. Default Settings.*  
| Setting                  | Value |
| ------------------------ | ----- |
| Button Debounce Time [ms] | 50    |
| Number of Toggle Buttons  | 12    |
| Number of Push Buttons    | 4     |
| Total Number of Buttons   | 16    |

You can change these values, but **remember to adjust all related arrays and variables accordingly**. I do not recommend setting the Button Debounce Time lower than 50 ms.
