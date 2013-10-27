Picade Alternative Firmware
===========================

This is alternative firmware for the Picade PCB. The Picade is a 'bartop arcade cabinet' kickstarter project from Pimoroni: http://www.pimoroni.com/ This code is a private project, and not endorsed or supported by Pimoroni.

The Picade PCB is an ATmega32U4 based breakout board sporting the Arduino 'Caterina-Leonardo' bootloader. This bootloader can be found here: https://github.com/arduino/Arduino

All Picade related designs and documents, including the original Arduino based firmware and schematics for the PCB can be found here: https://github.com/pimoroni/picade

This firmware uses Dean Camera's LUFA library (2013-09-01) and has 3 project directories:

- **Joystick**: a 3 axes/16 button Joystick (only 2 axes are used)
- **Keyboard**: a 162 keys/5 LED's multimedia keyboard (only 1 onboard LED is used)
- **KeyboardMouse**: actually 2 USB devices, a Keyboard and a 3 button Mouse (only 2 buttons used, LMB & RMB)

The latest version of the LUFA library can be found here: http://www.fourwalledcubicle.com/LUFA.php

The Picade has 1 digital Joystick (4 inputs / 2 axes) and 8+4=12 buttons on the Maxi (6+4=10 on the Mini). There are 4 free pins on the PCB available (6 on the Mini). In this firmware, these pins are being monitored as inputs and sent with the USB report. Add buttons to these pins, and they'll give a response.

Pinout
------

    Picade        ATmega Func      JoyValue     Key      Type           Usage

    JOYSTICK U    PB0    SS        -100 or 0    Up       digital in     Joy Y \__ Y / Mouse
    JOYSTICK D    PB1    SCLK      0 or 100     Down     digital in     Joy Y /
    JOYSTICK L    PB2    MOSI      -100 or 0    Left     digital in     Joy X \__ X / Mouse
    JOYSTICK R    PB3    MISO      0 or 100     Right    digital in     Joy X /

    UTIL START    PD0    SCL       0 or 1       1        digital in     START / LMB
    UTIL SELECT   PD1    SDA       0 or 1       5        digital in     SELECT / RMB
    UTIL ENTER    PD2    RXD       0 or 1       ENTER    digital in     ENTER
    UTIL ESC      PD3    TXD       0 or 1       ESC      digital in     ESC

    BUTTON #1     PF7    ADC7      0 or 1       LCTRL    digital in     BUTTON #1
    BUTTON #2     PF6    ADC6      0 or 1       LALT     digital in     BUTTON #2
    BUTTON #3     PF5    ADC5      0 or 1       A        digital in     BUTTON #3
    BUTTON #4     PF4    ADC4      0 or 1       Z        digital in     BUTTON #4
    BUTTON #5     PF1    ADC1      0 or 1       S        digital in     BUTTON #5
    BUTTON #6     PF0    ADC0      0 or 1       X        digital in     BUTTON #6

    GPIO #1       PD6    ADC9*     0 or 1       D        digital in     BUTTON #7 (Maxi)
    GPIO #2       PD7    ADC10*    0 or 1       C        digital in     BUTTON #8 (Maxi)
    GPIO #3       PB4    ADC11     0 or 1       I        digital in     - (free)
    GPIO #4       PB5    ADC12*    0 or 1       J        digital in     - (free)
    GPIO #5       PB6    ADC13*    0 or 1       K        digital in     - (free)
    GPIO #6       PC6    PWM       0 or 1       L        digital in     - (free)
    
    LEDS_LED1     PD5    XCK1/CTS  0 or 1       -        digital out    ONBOARD LED1
    // LEDS_LED2     PD7    ADC10*    0 or 1       -        digital out    ONBOARD LED2
                         * Also has PWM

At the moment, this firmware only drives the status LED on pin D5. The LED on pin D7 is also attached to (and used as) an input, so this LED is only useful in bootloader mode. In other words, LEDS_LED2 and GPIO #2 are on the same pin. LEDS_LED2 is disabled. It's assumed you're using all the available pins as inputs. Don't press any buttons while in bootloader mode and/or uploading firmware!

Getting started
---------------
This assumes you run a Debian based Linux OS, such as Raspbian on the Raspberry Pi or Ubuntu on an x86 or ARM machine. All tools needed are also available for Windows and Mac, but you're on your own there.

You are up to scratch with the latest fashion, aren't you?

    sudo apt-get update
    sudo apt-get upgrade

Good!

Upload prebuilt firmware
------------------------
Install avrdude (the tool that uploads the firmware to the microcontroller) from the default repository:

    sudo apt-get install avrdude

With a USB cable, plug the Picade PCB in the computer where you just installed avrdude and cd to the 'picade_lufa/bin/' directory where the prebuilt firmware is.

    cd path/to/picade_lufa/bin/

To upload prebuilt firmware to the Picade, run the 'upload' script in the 'bin' directory and supply the name of the firmware from that same directory (either 'Joystick.hex' or 'Keyboard.hex').

Press the reset button on the Picade PCB to start the bootloader. You have 10 seconds to run the script, before the bootloader times out. If that fails because you're slow (there's a complaint about /dev/ttyACM0), press enter or ctrl-c to return to a prompt, reset the board to bootloader mode and try again:

    sudo ./upload Joystick.hex

or, if you prefer the Picade PCB to behave as a keyboard:

    sudo ./upload Keyboard.hex

or both a mouse and a keyboard:

    sudo ./upload KeyboardMouse.hex

After successful uploading (avrdude done. Thank you.), you may have to unplug the USB cable and plug it back in, to make sure your new USB device actually enumerates. Usually it just works though.

You're done.

Build and upload firmware
-------------------------
To compile the firmware yourself, you need to install the AVR toolchain:

    sudo apt-get install binutils-avr gcc-avr avr-libc avrdude

To build the Joystick firmware, run the makefile in the Joystick project directory and upload with avrdude:

    cd path/to/picade_lufa/Joystick/
    make clean
    make
    [press reset button to enter bootloader]
    sudo make avrdude

The same applies to the Keyboard and KeyboardMouse firmware.

When you compile the firmware yourself, the hex file is NOT automatically copied to the 'bin' directory. So the hex files in the 'bin' directory are out of date.

Upload script
-------------
As seen above, the makefile handles the uploading with avrdude. An upload script is in the 'bin' directory to make uploading the prebuilt firmware easier. This is the call to avrdude in the upload script to communicate with the bootloader:

    avrdude -v -c avr109 -p atmega32u4 -P /dev/ttyACM0 -U flash:w:Firmware.hex:i

The ATmega32U4 on the Picade PCB has the default Arduino Leonardo fuse settings. An option in the upload script is to burn the fuses with a (hardware) programmer if you built your own PCB. I used the USBtinyISP from Adafruit. Change FUSEPROGRAMMER in the 'upload' script if you have a different one. Run 'avrdude -c foo' to see what programmers are supported.

    cd path/to/picade_lufa/bin/
    sudo ./upload fuse

To burn the Caterina-Leonardo bootloader (use your hardware programmer again):

    wget https://raw.github.com/arduino/Arduino/master/hardware/arduino/bootloaders/caterina/Caterina-Leonardo.hex
    sudo ./upload bootloader

Gordon's patched avrdude on Raspberry Pi
----------------------------------------
A little warning if you have used "Gordon's patched avrdude" with the Raspberry Pi GPIO pins to program Atmel microcontrollers (on a Gertboard maybe). Uploading using the USB bootloader doesn't work with (the otherwise awesome) patched avrdude on the Raspberry Pi. It seems to work, but it doesn't. Not when I tried, at least.

If you just followed the instructions above and installed avrdude from the repositories, your setup will work (also on a Raspberry Pi). 

Testing
-------
There are multiple ways to test that everything works. To see a list of USB devices:

    lsusb
    
In the list of USB devices you should see one of these lines:

    Bus xxx Device xxx: ID 03eb:2042 Atmel Corp. LUFA Keyboard Demo Application
    Bus xxx Device xxx: ID 03eb:2043 Atmel Corp. LUFA Joystick Demo Application
    Bus xxx Device xxx: ID 03eb:204d Atmel Corp. LUFA Combined Mouse and Keyboard Demo Application

When the device is in bootloader mode it will identify itself with:

    Bus xxx Device xxx: ID 2341:0036 Arduino SA

If you have burned the bootloader yourself, an 'empty' Leonardo identifies like this:

    Bus xxx Device xxx: ID 2341:8036 Arduino SA Leonardo (CDC ACM, HID)

Another option is to install 'evtest', to test input devices.
    
    sudo apt-get install evtest
    sudo evtest
    [choose input device]
    [press buttons and wiggle joystick]

Start your emulator and define control bindings!
