EnviroClock – Multifunction Alarm Clock with Room Temperature Display


Overview:
EnviroClock is a real-time embedded application developed using the ARM7 LPC2148 microcontroller. 
The system integrates timekeeping, alarm functionality, and environmental monitoring into a single interactive device.
It displays the current time, date, day, and room temperature on an LCD and allows users to configure time and alarms through a keypad-driven menu interface.
This project demonstrates practical implementation of RTC, ADC, GPIO, keypad interfacing, interrupt handling, and embedded C programming on real hardware


Key Features:
Real-time clock with date and day display using on-chip RTC
Room temperature measurement using LM35 sensor via ADC
Configurable alarm with buzzer notification
Interrupt-driven menu for editing RTC and alarm settings
Keypad-based user interaction with input validation
Alarm stop after we click the switch
Continuous real-time monitoring and display on LCD

System Architecture:
The system follows a super-loop embedded architecture:
Initialize peripherals (RTC, LCD, ADC, Keypad, GPIO, Interrupts).
Continuously read time from RTC and temperature from LM35.
Display real-time data on LCD.
Trigger buzzer when alarm time matches RTC.
External interrupt opens configuration menu for user input.

Hardware Components:
LPC2148 ARM7 Microcontroller
16x2 LCD Display
Matrix Keypad
LM35 Temperature Sensor
Buzzer
LEDs & Switches


Software & Tools:
Embedded C
Keil µVision IDE
Flash Magic Programmer

Technical Highlights:
Direct register-level programming (GPIO, RTC, ADC)
Interrupt-based user interface design
Sensor calibration and ADC data conversion
Input validation and menu navigation logic
Real-time embedded debugging and testing


Author:
Satwika Pedakota
Aspiring Embedded Systems Engineer.
