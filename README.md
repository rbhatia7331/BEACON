# BEACON

## What It Does
B.E.A.C.O.N. (Binary Encoded Advanced Communication Over Networks) encrypts an English message using a Vigenère cipher, converts it into a binary string, and transmits it using laser pulses. The receiver detects the laser signals, decodes the binary, decrypts the message, and reconstructs the original text in English.

## How We Built It
- Used an Arduino to handle encryption, binary conversion, and laser transmission.
- Designed a light sensor-based receiver to detect and decode laser pulses.
- Implemented the Vigenère cipher for encryption and decryption.
- Tuned the binary transmission timing to ensure accurate signal detection.

## Challenges We Ran Into
- Synchronizing laser pulses with accurate binary detection to prevent errors.
- Adjusting the sensor’s sensitivity to correctly distinguish laser pulses from ambient light.
- Ensuring encryption robustness while keeping the system lightweight for Arduino processing.
- Managing signal interference and optimizing detection speed for real-time communication.

## Accomplishments That We're Proud Of
- Successfully implemented encrypted laser-based communication using an Arduino.
- Achieved reliable message transmission and decryption over light pulses.
- Developed a stealthy, low-detectability communication system with real-world naval applications.

## What We Learned
- How to integrate cryptography with hardware-based communication.
- The importance of precise timing in signal transmission and reception.
- Methods to reduce noise and interference in optical communication.
- How historical naval signaling methods can be enhanced with modern encryption.

## What's Next for B.E.A.C.O.N.
- Increasing range and accuracy by improving laser strength and sensor precision.
- Implementing error correction algorithms to handle signal disruptions.
- Adapting the system for underwater laser communication for submarines.
- Enhancing encryption with RSA or stronger encryption algorithms for future security.
- Exploring multi-channel laser transmission to send multiple signals simultaneously.
