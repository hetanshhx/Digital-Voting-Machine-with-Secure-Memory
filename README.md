# Digital Voting Machine with Secure Memory

A comprehensive simulation of a secure digital voting machine built using an Arduino UNO in the Proteus Design Suite. This project fulfills all the core requirements of designing a basic electronic voting system, demonstrating key embedded systems concepts.

---

## Features & Guidelines Implemented

This project successfully implements the following guidelines:

* **State Machine for Vote Counting Logic:** The machine's operation is controlled by a robust state machine with distinct states (`VOTING_MODE`, `RESULTS_MODE`, `MESSAGE_MODE`). This ensures the program flows logically and prevents invalid operations, such as casting a vote while viewing results.

* **Secure Data Storage using EEPROM:** Vote counts are stored in non-volatile EEPROM. This secures the data against power loss, meaning the results are preserved even if the machine is turned off and on again.

* **Display Results on LCD:** A 16x2 LCD screen provides a clear user interface for real-time feedback, displaying welcome messages, vote confirmations, and final tabulated results.

* **Debouncing Logic for Tactile Switches:** All button inputs are debounced using a software timer (`millis()`). This prevents a single physical button press from being incorrectly registered as multiple votes, ensuring accurate counting.

---

## Key Components

This project is designed and simulated in Proteus. The required virtual components are:

* **Main Board:** Arduino UNO R3
* **Display:** 16x2 Alphanumeric LCD (LM016L)
* **Inputs:** 4x Tactile Push Buttons
* **Memory:** 24LC256 I2C EEPROM Chip

---

## Software & Tools

* **Simulation:** Proteus Design Suite (Version 8.6 or newer)
* **Firmware Development:** Arduino IDE (Version 1.8 or newer)

---

## Code Overview

The Arduino code is structured around the state machine. The main `loop()` function checks for debounced button presses and calls a central `handleButtonPress()` function. This function then determines the appropriate action based on the machine's current state, making the logic clean and easy to follow.
