# RTOS Scheduler Project

## Overview

This project implements a basic RTOS scheduler that can manage multiple tasks running on an STM32F103 microcontroller. The system uses PendSV and SysTick interrupts to achieve task switching between four tasks, each controlling GPIO pins. Each task toggles a specific GPIO pin with a different delay.

## Features

- **Multi-tasking**: Supports up to 4 user-defined tasks.
- **Task switching**: Uses PendSV for context switching and SysTick for task scheduling.
- **Task delays**: Tasks can enter a blocked state for a specified number of ticks.
- **Context saving and restoring**: Saves and restores CPU context (PSP) during task switches.
- **Idle Task**: An idle task is implemented to run when no other tasks are ready.

## Task Details

1. **Task 1**: Toggles GPIOA PIN1 every 1000 ticks (1 second).
2. **Task 2**: Toggles GPIOA PIN2 every 500 ticks (0.5 seconds).
3. **Task 3**: Toggles GPIOA PIN3 every 250 ticks (0.25 seconds).
4. **Task 4**: Toggles GPIOA PIN4 every 125 ticks (0.125 seconds).

## Code Structure

- **main.c**: Contains the main program logic, task initialization, and system configuration.
- **OSMCAL_interface.h / OSMCAL_private.h / OSMCAL_config.h**: Defines the interface and internal details of the scheduler.
- **STD_type.h & BIT_math.h**: Utility files that define standard types and bit manipulation macros.
- **DIO_interface.h**: Handles GPIO control (setting pin direction and toggling pins).
- **RCC_interface.h**: Initializes and configures the clock for the STM32.

## How It Works

1. **System Initialization**:
    - Initializes the RCC (Reset and Clock Control) to configure the system clock.
    - Configures GPIO pins for output to control the LEDs.
    - Initializes the SysTick timer for periodic interrupts and task scheduling.

2. **Scheduler Initialization**:
    - Initializes the stack for each task.
    - The PSP (Process Stack Pointer) is used for each task's stack.
    - The scheduler manages task switching using PendSV and SysTick interrupts.

3. **Task Switching**:
    - Each task's context (PSP and registers) is saved before switching to the next task.
    - Tasks enter a blocked state using the `TaskDelay` function and resume once the delay has expired.
    - The idle task runs if no other tasks are ready to execute.

## Files

- **main.c**: Contains the main application logic, task handlers, and scheduler initialization.
- **OSMCAL_interface.h**: Interface for the OS scheduler functions.
- **OSMCAL_private.h**: Contains private data structures and function declarations.
- **RCC_interface.h**: Functions for configuring the RCC peripheral.
- **DIO_interface.h**: Functions for configuring GPIO.
- **BIT_math.h**: Macros for bit manipulation.

## Requirements

- **Hardware**: STM32F103 microcontroller.
- **Tools**: ARM toolchain (for building), OpenOCD (for flashing), and a terminal for viewing output (optional).

## Usage

1. Clone the repository.
2. Set up your development environment (ARM toolchain, OpenOCD).
3. Build the project and flash it to your STM32 board.
4. Observe the GPIO pins (connected to LEDs) toggling at different intervals, as defined in the tasks.

## License

This project is licensed under the MIT License.

---

**Author**: Youssef Hamed  
**Version**: v01  
**Date**: 14 SEP 2024
