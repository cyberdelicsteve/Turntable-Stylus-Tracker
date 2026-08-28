/*
* Turntable Stylus Hour Tracker
* Arduino software for tracking turntable stylus usage. It will save the time used
* (to the most recent minute) to track the hours on a stylus. Button 1 will 
* start and stop the timer while holding Button 2 for 5 seconds will reset it.
*
* Copyright (C) 2026 cyberdelicsteve
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation.
* Current version: GPL-3.0
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <https://wwww.gnu.org/licenses/>.
*/
#include <Wire.h>
#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

#define START_BUTTON 2
#define RESET_BUTTON 3

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

unsigned long totalSeconds = 0;

unsigned long lastSecondTime = 0;
unsigned long lastSaveTime = 0;

bool timerRunning = false;

bool lastStartButtonState = HIGH;

unsigned long resetPressStart = 0;
bool resetHeld = false;

// Save accumulated time

void saveTime() {
EEPROM.put(0, totalSeconds);
}

// Load accumulated time

void loadTime() {

EEPROM.get(0, totalSeconds);

// Protect against uninitialized EEPROM
if (totalSeconds > 100000000UL) {
totalSeconds = 0;
}
}

// Reset

void resetTimer() {

timerRunning = false;
totalSeconds = 0;

saveTime();
}

// OLED display

void updateDisplay() {

unsigned long hours = totalSeconds / 3600UL;

unsigned int minutes =
(totalSeconds % 3600UL) / 60UL;

unsigned int seconds =
totalSeconds % 60UL;


display.clearDisplay();

display.setTextColor(SSD1306_WHITE);


// Title
display.setTextSize(1);
display.setCursor(18, 0);
display.println("STYLUS HOURS");


// Hours and minutes
display.setTextSize(2);
display.setCursor(10, 18);

display.print(hours);
display.print("h ");

if (minutes < 10) {
display.print("0");
}

display.print(minutes);
display.print("m");


// Seconds
display.setTextSize(1);
display.setCursor(49, 42);

if (seconds < 10) {
display.print("0");
}

display.print(seconds);
display.print(" sec");


// Status
display.setCursor(40, 54);

if (timerRunning) {
display.print("RUNNING");
}
else {
display.print("STOPPED");
}


display.display();
}

// Setup

void setup() {

pinMode(START_BUTTON, INPUT_PULLUP);
pinMode(RESET_BUTTON, INPUT_PULLUP);


if (!display.begin(
SSD1306_SWITCHCAPVCC,
OLED_ADDRESS)) {

while (true) {
// Stop if OLED initialization fails
}
}


loadTime();


display.clearDisplay();
display.setTextColor(SSD1306_WHITE);

display.setTextSize(1);
display.setCursor(20, 22);
display.println("STYLUS TRACKER");

display.setCursor(38, 38);
display.println("Starting...");

display.display();

delay(1000);


lastSecondTime = millis();
lastSaveTime = millis();
}

// Main loop

void loop() {

// START / STOP BUTTON

bool startButtonState =
digitalRead(START_BUTTON);


if (startButtonState == LOW &&
lastStartButtonState == HIGH) {

delay(30);

// Check that button is still pressed
if (digitalRead(START_BUTTON) == LOW) {

timerRunning = !timerRunning;


if (timerRunning) {

// Establish a fresh timing reference when starting.
lastSecondTime = millis();
lastSaveTime = millis();

}
else {

// Save immediately when stopping
saveTime();
}
}
}


lastStartButtonState =
startButtonState;

// Get current time AFTER button handling.
// This is important because the debounce delay above
// means millis() may have advanced.
unsigned long currentTime = millis();

// TIMER

if (timerRunning) {

if (currentTime - lastSecondTime >= 1000UL) {

totalSeconds++;

lastSecondTime += 1000UL;
}


// Save every minute while running
if (currentTime - lastSaveTime >= 60000UL) {

saveTime();

lastSaveTime = currentTime;
}
}


// RESET BUTTON
// Hold for 5 seconds

bool resetButtonState =
digitalRead(RESET_BUTTON);


if (resetButtonState == LOW) {

if (!resetHeld) {

resetPressStart = currentTime;

resetHeld = true;
}


if (currentTime - resetPressStart >= 5000UL) {

resetTimer();

resetHeld = false;


// Reset confirmation screen
display.clearDisplay();

display.setTextColor(SSD1306_WHITE);

display.setTextSize(2);
display.setCursor(26, 20);
display.println("RESET");

display.setTextSize(1);
display.setCursor(33, 45);
display.println("0 HOURS");

display.display();

delay(1000);


// Wait for button release
while (digitalRead(RESET_BUTTON) == LOW) {
delay(10);
}


// Reset timing references after the delay
lastSecondTime = millis();
lastSaveTime = millis();
}
}
else {

resetHeld = false;
}

// OLED

updateDisplay();

delay(20);
}