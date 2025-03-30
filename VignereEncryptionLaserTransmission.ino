#include <Arduino.h>

#define laser 8
#define sensor A0

String originalText = "";  // User input text
String encryptedText = "";
String key = "";
String receivedText = "";
String decryptedText = "";
String binaryEncrypted = "";
String binaryRecorded = "";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(laser, OUTPUT);
  pinMode(sensor, INPUT);

  randomSeed(analogRead(A0));  // Initialize random generator

  Serial.println("Enter the message to transmit:");
  while (Serial.available() == 0) {}  // Wait for user input

  originalText = Serial.readString();
  Serial.println("Message to be sent: " + originalText);
  originalText.trim();
  originalText = cleanInput(originalText);
  Serial.println("Optimized message being sent: " + originalText);

  key = generateKey(originalText.length());
  Serial.println("Encryption key: " + key);
  encryptedText = vigenereEncrypt(originalText, key);
  Serial.println("Encrypted text: " + encryptedText);

  binaryEncrypted = textToBinary(encryptedText);
  Serial.println("Binary being transmitted: " + binaryEncrypted);

  binaryRecorded = transmitAndReceiveBinary(binaryEncrypted);
  Serial.println("Binary recieved: " + binaryRecorded);



  receivedText = binaryToText(binaryRecorded);
  Serial.println("Encrypted text being recieved: " + receivedText);

  decryptedText = vigenereDecrypt(receivedText, key);
  Serial.println("Decrypted text: " + decryptedText);

}

void loop() {
  // put your main code here, to run repeatedly:

}

//Cleans up input string
String cleanInput(String input) {
    String result = "";
    for (int i = 0; i < input.length(); i++) {
        char c = toupper(input[i]);
        if (c >= 'A' && c <= 'Z') {
            result += c;
        }
    }
    return result;
}

// Function to generate a random key of the same length as the text
String generateKey(int length) {
    String key = "";
    for (int i = 0; i < length; i++) {
        key += char('A' + random(26));  // Random capital letter
    }
    return key;
}


// Vigenère Cipher Encryption
String vigenereEncrypt(String text, String key) {
    String encrypted = "";
    for (int i = 0; i < text.length(); i++) {
        char c = ((text[i] - 'A') + (key[i] - 'A')) % 26 + 'A';
        encrypted += c;
    }
    return encrypted;
}


// Vigenère Cipher Decryption
String vigenereDecrypt(String text, String key) {
    String decrypted = "";
    for (int i = 0; i < text.length(); i++) {
        char c = ((text[i] - 'A') - (key[i] - 'A') + 26) % 26 + 'A';
        decrypted += c;
    }
    return decrypted;
}

//Converts encrypted text to binary
String textToBinary(String text) {
    String binaryString = "";
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        for (int j = 7; j >= 0; j--) {  // Convert each character to 8-bit binary
            binaryString += ((c >> j) & 1) ? '1' : '0';
        }
        binaryString += " ";  // Space between characters
    }
    return binaryString;
}

//Converts binary into encrypted text
String binaryToText(String binaryString) {
    String text = "";
    int len = binaryString.length();

    for (int i = 0; i < len; i += 9) {  // Process 8 bits at a time (skip spaces)
        char c = 0;
        for (int j = 0; j < 8; j++) {
            if (binaryString[i + j] == '1') {
                c |= (1 << (7 - j));  // Convert binary to character
            }
        }
        text += c;
    }
    return text;
}

//Sends and recieves binary
String transmitAndReceiveBinary(String binaryString) {
    String binaryReceived = "";
    int bitCount = 0;  // Track bits for spacing

    for (int i = 0; i < binaryString.length(); i++) {
        char bit = binaryString[i];

        if (bit == '1') {
            digitalWrite(laser, HIGH);  // Laser ON for 1
        } else if (bit == '0') {
            digitalWrite(laser, LOW);   // Laser OFF for 0
        } else {
            continue;  // Skip spaces in original transmission
        }

        delay(100);  // Small delay to stabilize laser output

        digitalWrite(sensor, HIGH);  // Activate sensor
        delay(50);  // Allow sensor to read

        int readBit = digitalRead(sensor);  // Read sensor input
        binaryReceived += (readBit == HIGH) ? '1' : '0';
        bitCount++;

        digitalWrite(sensor, LOW);  // Turn off sensor
        delay(50);  // Allow transition before next bit

        // Add space after every 8 bits for readability
        if (bitCount % 8 == 0) {
            binaryReceived += " ";
        }
    }

    binaryReceived.trim();  // Remove any leading/trailing spaces
    return binaryReceived;
}


