/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Main source file for the Keyboard demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "Keyboard.h"

/** Buffer to hold the previously generated Keyboard HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevKeyboardHIDReportBuffer[sizeof(USB_KeyboardReport_Data_t)];

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t Keyboard_HID_Interface =
 	{
		.Config =
			{
				.InterfaceNumber              = 0,
				.ReportINEndpoint             =
					{
						.Address              = KEYBOARD_EPADDR,
						.Size                 = KEYBOARD_EPSIZE,
						.Banks                = 1,
					},
				.PrevReportINBuffer           = PrevKeyboardHIDReportBuffer,
				.PrevReportINBufferSize       = sizeof(PrevKeyboardHIDReportBuffer),
			},
    };


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
	
	SetupHardware();
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
		HID_Device_USBTask(&Keyboard_HID_Interface);
		USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware()
{
	Picade_Init();
	
	USB_Init();
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= HID_Device_ConfigureEndpoints(&Keyboard_HID_Interface);

	USB_Device_EnableSOFEvents();
	
	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	HID_Device_ProcessControlRequest(&Keyboard_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
	HID_Device_MillisecondElapsed(&Keyboard_HID_Interface);
}

/*
	HID_KEYBOARD_SC_ERROR_ROLLOVER
	HID_KEYBOARD_SC_POST_FAIL
	HID_KEYBOARD_SC_ERROR_UNDEFINED
	HID_KEYBOARD_SC_A
	HID_KEYBOARD_SC_B
	HID_KEYBOARD_SC_C
	HID_KEYBOARD_SC_D
	HID_KEYBOARD_SC_E
	HID_KEYBOARD_SC_F
	HID_KEYBOARD_SC_G
	HID_KEYBOARD_SC_H
	HID_KEYBOARD_SC_I
	HID_KEYBOARD_SC_J
	HID_KEYBOARD_SC_K
	HID_KEYBOARD_SC_L
	HID_KEYBOARD_SC_M
	HID_KEYBOARD_SC_N
	HID_KEYBOARD_SC_O
	HID_KEYBOARD_SC_P
	HID_KEYBOARD_SC_Q
	HID_KEYBOARD_SC_R
	HID_KEYBOARD_SC_S
	HID_KEYBOARD_SC_T
	HID_KEYBOARD_SC_U
	HID_KEYBOARD_SC_V
	HID_KEYBOARD_SC_W
	HID_KEYBOARD_SC_X
	HID_KEYBOARD_SC_Y
	HID_KEYBOARD_SC_Z
	HID_KEYBOARD_SC_1_AND_EXCLAMATION
	HID_KEYBOARD_SC_2_AND_AT
	HID_KEYBOARD_SC_3_AND_HASHMARK
	HID_KEYBOARD_SC_4_AND_DOLLAR
	HID_KEYBOARD_SC_5_AND_PERCENTAGE
	HID_KEYBOARD_SC_6_AND_CARET
	HID_KEYBOARD_SC_7_AND_AND_AMPERSAND
	HID_KEYBOARD_SC_8_AND_ASTERISK
	HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS
	HID_KEYBOARD_SC__AND_CLOSING_PARENTHESIS
	HID_KEYBOARD_SC_ENTER
	HID_KEYBOARD_SC_ESCAPE
	HID_KEYBOARD_SC_BACKSPACE
	HID_KEYBOARD_SC_TAB
	HID_KEYBOARD_SC_SPACE
	HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE
	HID_KEYBOARD_SC_EQUAL_AND_PLUS
	HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE
	HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE
	HID_KEYBOARD_SC_BACKSLASH_AND_PIPE
	HID_KEYBOARD_SC_NON_US_HASHMARK_AND_TILDE
	HID_KEYBOARD_SC_SEMICOLON_AND_COLON
	HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE
	HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE
	HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN
	HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN
	HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK
	HID_KEYBOARD_SC_CAPS_LOCK
	HID_KEYBOARD_SC_F1
	HID_KEYBOARD_SC_F2
	HID_KEYBOARD_SC_F3
	HID_KEYBOARD_SC_F4
	HID_KEYBOARD_SC_F5
	HID_KEYBOARD_SC_F6
	HID_KEYBOARD_SC_F7
	HID_KEYBOARD_SC_F8
	HID_KEYBOARD_SC_F9
	HID_KEYBOARD_SC_F1
	HID_KEYBOARD_SC_F11
	HID_KEYBOARD_SC_F12
	HID_KEYBOARD_SC_PRINT_SCREEN
	HID_KEYBOARD_SC_SCROLL_LOCK
	HID_KEYBOARD_SC_PAUSE
	HID_KEYBOARD_SC_INSERT
	HID_KEYBOARD_SC_HOME
	HID_KEYBOARD_SC_PAGE_UP
	HID_KEYBOARD_SC_DELETE
	HID_KEYBOARD_SC_END
	HID_KEYBOARD_SC_PAGE_DOWN
	HID_KEYBOARD_SC_RIGHT_ARROW
	HID_KEYBOARD_SC_LEFT_ARROW
	HID_KEYBOARD_SC_DOWN_ARROW
	HID_KEYBOARD_SC_UP_ARROW
	HID_KEYBOARD_SC_NUM_LOCK
	HID_KEYBOARD_SC_KEYPAD_SLASH
	HID_KEYBOARD_SC_KEYPAD_ASTERISK
	HID_KEYBOARD_SC_KEYPAD_MINUS
	HID_KEYBOARD_SC_KEYPAD_PLUS
	HID_KEYBOARD_SC_KEYPAD_ENTER
	HID_KEYBOARD_SC_KEYPAD_1_AND_END
	HID_KEYBOARD_SC_KEYPAD_2_AND_DOWN_ARROW
	HID_KEYBOARD_SC_KEYPAD_3_AND_PAGE_DOWN
	HID_KEYBOARD_SC_KEYPAD_4_AND_LEFT_ARROW
	HID_KEYBOARD_SC_KEYPAD_5
	HID_KEYBOARD_SC_KEYPAD_6_AND_RIGHT_ARROW
	HID_KEYBOARD_SC_KEYPAD_7_AND_HOME
	HID_KEYBOARD_SC_KEYPAD_8_AND_UP_ARROW
	HID_KEYBOARD_SC_KEYPAD_9_AND_PAGE_UP
	HID_KEYBOARD_SC_KEYPAD__AND_INSERT
	HID_KEYBOARD_SC_KEYPAD_DOT_AND_DELETE
	HID_KEYBOARD_SC_NON_US_BACKSLASH_AND_PIPE
	HID_KEYBOARD_SC_APPLICATION
	HID_KEYBOARD_SC_POWER
	HID_KEYBOARD_SC_KEYPAD_EQUAL_SIGN
	HID_KEYBOARD_SC_F13
	HID_KEYBOARD_SC_F14
	HID_KEYBOARD_SC_F15
	HID_KEYBOARD_SC_F16
	HID_KEYBOARD_SC_F17
	HID_KEYBOARD_SC_F18
	HID_KEYBOARD_SC_F19
	HID_KEYBOARD_SC_F2
	HID_KEYBOARD_SC_F21
	HID_KEYBOARD_SC_F22
	HID_KEYBOARD_SC_F23
	HID_KEYBOARD_SC_F24
	HID_KEYBOARD_SC_EXECUTE
	HID_KEYBOARD_SC_HELP
	HID_KEYBOARD_SC_MANU
	HID_KEYBOARD_SC_SELECT
	HID_KEYBOARD_SC_STOP
	HID_KEYBOARD_SC_AGAIN
	HID_KEYBOARD_SC_UNDO
	HID_KEYBOARD_SC_CUT
	HID_KEYBOARD_SC_COPY
	HID_KEYBOARD_SC_PASTE
	HID_KEYBOARD_SC_FIND
	HID_KEYBOARD_SC_MUTE
	HID_KEYBOARD_SC_VOLUME_UP
	HID_KEYBOARD_SC_VOLUME_DOWN
	HID_KEYBOARD_SC_LOCKING_CAPS_LOCK
	HID_KEYBOARD_SC_LOCKING_NUM_LOCK
	HID_KEYBOARD_SC_LOCKING_SCROLL_LOCK
	HID_KEYBOARD_SC_KEYPAD_COMMA
	HID_KEYBOARD_SC_KEYPAD_EQUAL_SIGN_AS4
	HID_KEYBOARD_SC_INTERNATIONAL1
	HID_KEYBOARD_SC_INTERNATIONAL2
	HID_KEYBOARD_SC_INTERNATIONAL3
	HID_KEYBOARD_SC_INTERNATIONAL4
	HID_KEYBOARD_SC_INTERNATIONAL5
	HID_KEYBOARD_SC_INTERNATIONAL6
	HID_KEYBOARD_SC_INTERNATIONAL7
	HID_KEYBOARD_SC_INTERNATIONAL8
	HID_KEYBOARD_SC_INTERNATIONAL9
	HID_KEYBOARD_SC_LANG1
	HID_KEYBOARD_SC_LANG2
	HID_KEYBOARD_SC_LANG3
	HID_KEYBOARD_SC_LANG4
	HID_KEYBOARD_SC_LANG5
	HID_KEYBOARD_SC_LANG6
	HID_KEYBOARD_SC_LANG7
	HID_KEYBOARD_SC_LANG8
	HID_KEYBOARD_SC_LANG9
	HID_KEYBOARD_SC_ALTERNATE_ERASE
	HID_KEYBOARD_SC_SISREQ
	HID_KEYBOARD_SC_CANCEL
	HID_KEYBOARD_SC_CLEAR
	HID_KEYBOARD_SC_PRIOR
	HID_KEYBOARD_SC_RETURN
	HID_KEYBOARD_SC_SEPARATOR
	HID_KEYBOARD_SC_OUT
	HID_KEYBOARD_SC_OPER
	HID_KEYBOARD_SC_CLEAR_AND_AGAIN
	HID_KEYBOARD_SC_CRSEL_ANDPROPS
	HID_KEYBOARD_SC_EXSEL
	HID_KEYBOARD_SC_KEYPAD_
	HID_KEYBOARD_SC_KEYPAD_
	HID_KEYBOARD_SC_THOUSANDS_SEPARATOR
	HID_KEYBOARD_SC_DECIMAL_SEPARATOR
	HID_KEYBOARD_SC_CURRENCY_UNIT
	HID_KEYBOARD_SC_CURRENCY_SUB_UNIT
	HID_KEYBOARD_SC_KEYPAD_OPENING_PARENTHESIS
	HID_KEYBOARD_SC_KEYPAD_CLOSING_PARENTHESIS
	HID_KEYBOARD_SC_KEYPAD_OPENING_BRACE
	HID_KEYBOARD_SC_KEYPAD_CLOSING_BRACE
	HID_KEYBOARD_SC_KEYPAD_TAB
	HID_KEYBOARD_SC_KEYPAD_BACKSPACE
	HID_KEYBOARD_SC_KEYPAD_A
	HID_KEYBOARD_SC_KEYPAD_B
	HID_KEYBOARD_SC_KEYPAD_C
	HID_KEYBOARD_SC_KEYPAD_D
	HID_KEYBOARD_SC_KEYPAD_E
	HID_KEYBOARD_SC_KEYPAD_F
	HID_KEYBOARD_SC_KEYPAD_XOR
	HID_KEYBOARD_SC_KEYPAD_CARET
	HID_KEYBOARD_SC_KEYPAD_PERCENTAGE
	HID_KEYBOARD_SC_KEYPAD_LESS_THAN_SIGN
	HID_KEYBOARD_SC_KEYPAD_GREATER_THAN_SIGN
	HID_KEYBOARD_SC_KEYPAD_AMP
	HID_KEYBOARD_SC_KEYPAD_AMP_AMP
	HID_KEYBOARD_SC_KEYPAD_PIPE
	HID_KEYBOARD_SC_KEYPAD_PIPE_PIPE
	HID_KEYBOARD_SC_KEYPAD_COLON
	HID_KEYBOARD_SC_KEYPAD_HASHMARK
	HID_KEYBOARD_SC_KEYPAD_SPACE
	HID_KEYBOARD_SC_KEYPAD_AT
	HID_KEYBOARD_SC_KEYPAD_EXCLAMATION_SIGN
	HID_KEYBOARD_SC_KEYPAD_MEMORY_STORE
	HID_KEYBOARD_SC_KEYPAD_MEMORY_RECALL
	HID_KEYBOARD_SC_KEYPAD_MEMORY_CLEAR
	HID_KEYBOARD_SC_KEYPAD_MEMORY_ADD
	HID_KEYBOARD_SC_KEYPAD_MEMORY_SUBTRACT
	HID_KEYBOARD_SC_KEYPAD_MEMORY_MULTIPLY
	HID_KEYBOARD_SC_KEYPAD_MEMORY_DIVIDE
	HID_KEYBOARD_SC_KEYPAD_PLUS_AND_MINUS
	HID_KEYBOARD_SC_KEYPAD_CLEAR
	HID_KEYBOARD_SC_KEYPAD_CLEAR_ENTRY
	HID_KEYBOARD_SC_KEYPAD_BINARY
	HID_KEYBOARD_SC_KEYPAD_OCTAL
	HID_KEYBOARD_SC_KEYPAD_DECIMAL
	HID_KEYBOARD_SC_KEYPAD_HEXADECIMAL
	HID_KEYBOARD_SC_LEFT_CONTROL
	HID_KEYBOARD_SC_LEFT_SHIFT
	HID_KEYBOARD_SC_LEFT_ALT
	HID_KEYBOARD_SC_LEFT_GUI
	HID_KEYBOARD_SC_RIGHT_CONTROL
	HID_KEYBOARD_SC_RIGHT_SHIFT
	HID_KEYBOARD_SC_RIGHT_ALT
	HID_KEYBOARD_SC_RIGHT_GUI
*/
/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
 *
 *  \return Boolean \c true to force the sending of the report, \c false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{
	USB_KeyboardReport_Data_t* KeyboardReport = (USB_KeyboardReport_Data_t*)ReportData;
	*ReportSize = sizeof(USB_KeyboardReport_Data_t);
	
	uint8_t UsedKeyCodes = 0;

	// #################### JOYSTICK ####################
	uint8_t JoyStatus = Joystick_GetStatus();
	
	if (JoyStatus & JOY_UP)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_UP_ARROW;
	else if (JoyStatus & JOY_DOWN)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_DOWN_ARROW;

	if (JoyStatus & JOY_LEFT)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_LEFT_ARROW;
	else if (JoyStatus & JOY_RIGHT)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_RIGHT_ARROW;

	// #################### UTIL ####################
	uint8_t UtilStatus = Util_GetStatus();
	
	if (UtilStatus & UTIL_START)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_1_AND_EXCLAMATION;
	if (UtilStatus & UTIL_SELECT)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_5_AND_PERCENTAGE;
	if (UtilStatus & UTIL_ENTER)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_ENTER;
	if (UtilStatus & UTIL_ESC)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_ESCAPE;
	
	// #################### BUTTON ####################
	uint8_t ButtonStatus = Buttons_GetStatus();
	
	if (ButtonStatus & BUTTON1)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_LEFT_CONTROL;
	if (ButtonStatus & BUTTON2)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_LEFT_ALT;
	if (ButtonStatus & BUTTON3)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_A;
	if (ButtonStatus & BUTTON4)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_Z;
	if (ButtonStatus & BUTTON5)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_S;
	if (ButtonStatus & BUTTON6)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_X;

	// #################### GPIO ####################
	uint8_t GPIODStatus = GPIOD_GetStatus();
	if (GPIODStatus & GPIO1)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_D;
	if (GPIODStatus & GPIO2)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_C;

	uint8_t GPIOBStatus = GPIOB_GetStatus();
	if (GPIOBStatus & GPIO3)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_I;
	if (GPIOBStatus & GPIO4)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_J;
	if (GPIOBStatus & GPIO5)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_K;
	
	uint8_t GPIOCStatus = GPIOC_GetStatus();
	if (GPIOCStatus & GPIO6)
		KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_L;


	//if (UsedKeyCodes)
	//	KeyboardReport->Modifier = HID_KEYBOARD_MODIFIER_LEFTSHIFT;
	
	return false;
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
	uint8_t  LEDMask   = LEDS_NO_LEDS;
	uint8_t* LEDReport = (uint8_t*)ReportData;

	if (*LEDReport & HID_KEYBOARD_LED_NUMLOCK)
		LEDMask |= LEDS_LED1;

	if (*LEDReport & HID_KEYBOARD_LED_CAPSLOCK)
		LEDMask |= LEDS_LED1;

	if (*LEDReport & HID_KEYBOARD_LED_SCROLLLOCK)
		LEDMask |= LEDS_LED1;

	LEDs_SetAllLEDs(LEDMask);
}

