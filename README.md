# Industrial Safety Monitoring and Emergency Shutdown System

An embedded-systems mini-project built using the **LPC2129 ARM7
microcontroller**. The system monitors an industrial safety input and
demonstrates emergency motor shutdown using external interrupts. Motor
status is shown on a character LCD and transmitted through UART0.

## Table of Contents

-   [Overview](#overview)
-   [Objectives](#objectives)
-   [Hardware Components](#hardware-components)
-   [Software and Tools](#software-and-tools)
-   [System Block Diagram](#system-block-diagram)
-   [Software Architecture](#software-architecture)
-   [Working Principle](#working-principle)
-   [Peripheral Interfacing](#peripheral-interfacing)
-   [Learning Outcomes](#learning-outcomes)
-   [Important Implementation Note](#important-implementation-note)

## Overview

The project demonstrates how an external interrupt can trigger an
emergency motor-stop routine. The LPC2129 controls the motor-driver
inputs, displays the system state on an LCD, and sends status messages
over UART0. The software is separated into an application file and
peripheral driver modules to improve readability and maintainability.

## Objectives

-   Implement external interrupt handling on the LPC2129.
-   Demonstrate emergency motor shutdown through GPIO control.
-   Display motor status and emergency messages on an LCD.
-   Transmit system-status messages through UART0.
-   Organize Embedded C code into reusable driver modules.
-   Practise interrupt handling and peripheral interfacing on an ARM7
    microcontroller.

## Hardware Components

-   LPC2129 ARM7 microcontroller
-   DC motor
-   L293D motor driver
-   Character LCD
-   Active-low indicator LED
-   External interrupt switches (EINT1 and EINT2)
-   IR sensor (if used as an input in the current circuit)
-   UART0 serial interface / USB-to-TTL or suitable serial adapter
-   Power supply and supporting components

## Software and Tools

-   Embedded C
-   Keil µVision
-   LPC2129 device support and header files
-   UART serial terminal
-   Proteus (optional, for circuit simulation)

## System Block Diagram
file:///home/v25ce9a3/Downloads/linux%20notes/unnamed.png<img width="589" height="379" alt="image" src="https://github.com/user-attachments/assets/c9c25409-ee6f-43c8-89be-1d14e9807145" />



## Software Architecture

### 1. Main Application --- `mini_project.c`

Responsible for: - Configuring GPIO pins and external interrupts. -
Configuring the Vector Interrupt Controller (VIC). - Initializing LCD
and UART0. - Setting motor-control output states. - Updating the LCD and
UART status messages. - Handling emergency interrupt events in the ISR.

### 2. LCD Driver --- `lcd_header.h`

Provides functions for LCD initialization, command/data output, string
display, and title display:

-   `LCD_INIT()`
-   `LCD_COMMAND()`
-   `LCD_DATA()`
-   `LCD_STR()`
-   `LCD_TITLE()`

### 3. UART Driver --- `UART_header.h`

Provides serial communication and basic formatted-output functions:

-   `UART_CONFIG()`
-   `UART_TX()`
-   `UART_RX()`
-   `UART_STR()`
-   `UART_INTEGER()`
-   `UART_FLOAT()`

### 4. Delay Module --- `delay_ms.c`

-   `delay_ms()` implements a delay using Timer 0 registers according to
    the timer and peripheral-clock configuration.

## Working Principle

1.  The LPC2129 initializes GPIO, external interrupts, the VIC, LCD, and
    UART0.
2.  The project title is displayed on the LCD and transmitted through
    UART0.
3.  The firmware sets the motor-driver inputs to the configured running
    state. In a typical L293D arrangement, opposite logic levels on the
    two direction inputs drive the motor in one direction; equal levels
    make the output stop/brake or coast depending on the driver state
    and enable pin.
4.  The LCD and UART display `MOTOR RUNNING`.
5.  When a configured external interrupt occurs, the ISR identifies the
    interrupt source.
6.  The emergency routine changes the motor-control outputs to the stop
    state and updates the active-low indicator LED according to the
    circuit design.
7.  The LCD and UART report `MOTOR STOP!!`.
8.  A software flag records that an interrupt event occurred.
9.  The main application checks the flag. **If the code automatically
    restores the motor-running state, this is a demonstration behavior,
    not a fail-safe emergency-stop design.** In a real industrial
    system, restart should require an intentional, safe reset after the
    hazard is cleared.

## Peripheral Interfacing

### External Interrupts

-   EINT1 and EINT2 are configured as edge-sensitive, falling-edge
    interrupts.
-   The VIC is configured to route the enabled interrupt source to the
    appropriate ISR.
-   The ISR should clear the relevant external-interrupt flag and
    acknowledge the VIC according to the LPC2129 requirements.

### GPIO Motor Control

-   Motor-control signals: GPIO0 pins 21 and 22.
-   Indicator LED: GPIO0 pin 23.
-   The exact active levels must match the circuit and the L293D
    enable/input wiring.

### LCD Interface

-   LCD data bus: GPIO1 pins 23--30.
-   RS control: GPIO1 pin 19.
-   Enable control: GPIO1 pin 18.

### UART Communication

-   UART0 is used to transmit status messages to a serial terminal.
-   Terminal settings (baud rate, data bits, parity, and stop bits) must
    match the UART configuration in the firmware.

## Learning Outcomes

-   ARM7 LPC2129 peripheral programming
-   External interrupt configuration and ISR handling
-   Vector Interrupt Controller configuration
-   GPIO-based motor control
-   L293D motor-driver interfacing
-   Character LCD interfacing
-   UART0 serial communication
-   Timer-based delays
-   Modular Embedded C programming

## Important Implementation Note

This project is an educational prototype. A microcontroller interrupt
and software-controlled motor driver alone should not be treated as a
certified industrial emergency-stop system. Real machinery requires
appropriately rated safety hardware, a risk assessment, and a validated
restart procedure. Verify all pin mappings, interrupt-vector setup,
motor-driver enable wiring, and active-low LED logic against the actual
schematic and source code.
