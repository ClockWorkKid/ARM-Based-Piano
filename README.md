# ARM-Based-Piano
STM32 based digital piano project for EEE416 Microprocessor and Embedded Systems Laboratory

Demonstration video <a href="https://youtu.be/l-ic4qlintA">link</a>

## Contents
- [Repository Overview](#repository-overview)
- [Materials Used](#materials-used)
- [Softwares Used](#softwares-used)
- [Useful Links](#useful-links)
- [Working Procedure](#working-procedure)
- [Resampling Implementation in MATLAB](#resampling-implementation-in-matlab)
- [Resampling Implementation in C](#resampling-implementation-in-c)
- [DAC Simulation and Design Using Proteus](#dac-simulation-and-design-using-proteus)
- [Keyboard Interfacing Using Arduino DUE and Interrupt](#keyboard-interfacing-using-arduino-due-and-interrupt)
- [STM32 Code](#stm32-code)
- [Hardware Setup](#hardware-setup)
- [Conclusion](#conclusion)
- [Team](#team)

## Repository Overview

## Materials Used

- STM32F746 Discovery Board
- Arduino Due Board
- Arduino Uno Proto Shield
- Screws (for key contact + body)
- Female-Female jumpers (A lot!)
- 26 AWG wires (connects screws with circuit board)
- Aluminium foil (positive rail)
- 3.5mm headphone jack female
- Veroboard, soldering tools
- AWEI Y220 speaker with auxiliary cable
- Micro SD Card

## Softwares Used

- STM32CubeIDE
- Arduino IDE
- Proteus
- Matlab
- Codeblocks

## Useful Links

- <a href="https://www.youtube.com/playlist?list=PLc2rvfiptPSR0bzPjEsg5zmj0jvYMZLbV">A youtube playlist</a> containing useful videos for the STM32F746 Discovery Board

## Working Procedure


### Audio note synthesis from a single base note

A sample note of high resolution (44.1 KHz, 24 bit sample size) was downloaded. (The notes can be found at http://theremin.music.uiowa.edu/MISpiano.html). First we trimmed the note, and resampled it using MATLAB to see if the new note satisfies the frequency requirements of the target note. Then the resample function of MATLAB was manually written using resample theory (upsampling, interpolation using sinc function, downsampling). This code also generated similar notes, implying the correct operation of resample function. Finally the resampling function was ported to C code for using with STM32 board

### Keyboard interfacing with a STM32 board

The designed hardware keyboard has 36 keys in total (3 octaves) and the keys are all connected to the Arduino DUE board (the STM32 discovery board did not have enough pins available as most of them were connected internally to other peripherals). Arduino DUE board reads the keypresses in polling mode with debouncing enabled. When a keypress is detected, DUE board sents an interrupt to the STM32 board along with the ID of the corresponding key being pressed.

### Note playback from STM32 board

The 36 piano notes are saved inside a micro SD card in binary format (8 kHz sampling rate, 8 bit resolution) and when a keypress is detected, the STM32 Discovery board reads the corresponding binary file, sends the audio samples to a buffer, and using the DAC circuit, these sample values are sent to the speaker device.


## Resampling Implementation in MATLAB

## Resampling Implementation in C

## Keyboard Interfacing Using Arduino DUE and Interrupt

## DAC Simulation and Design Using Proteus

## STM32 Code

## Hardware Setup

## Conclusion

## Team

- Mir Sayeed Mohammad (github - https://github.com/ClockWorkKid)
- Shafin Bin Hamid (github - https://github.com/shafinbinhamid)
- Ramit Dutta
- Himaddri Roy (github - https://github.com/himu587)
- Sujoy Mondal (github - https://github.com/sujoy-mondal)

