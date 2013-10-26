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
 *  \brief Board specific LED driver header for the Picade.
 *  \copydetails Group_LEDs_PICADE
 *
 *  \note This file should not be included directly. It is automatically included as needed by the LEDs driver
 *        dispatch header located in LUFA/Drivers/Board/LEDs.h.
 */

/** \ingroup Group_LEDs
 *  \defgroup Group_LEDs_PICADE PICADE
 *  \brief Board specific LED driver header for the Picade.
 *
 *  Board specific LED driver header for the Picade.
 *
 *  @{
 */

#ifndef __LEDS_PICADE_H__
#define __LEDS_PICADE_H__

	/* Includes: */
		#include <LUFA/Common/Common.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_LEDS_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/LEDS.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			#define LEDS_LED1		(1 << 5)
			#define LEDS_LED2		(1 << 7)
			//#define LEDSD_MASK		(LEDS_LED1 | LEDS_LED2)
			#define LEDSD_MASK		(LEDS_LED1)

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void LEDs_Init(void)
			{
				DDRD  |=  LEDSD_MASK;
				PORTD &= ~LEDSD_MASK;
			}

			static inline void LEDs_Disable(void)
			{
				DDRD  &= ~LEDSD_MASK;
				PORTD &= ~LEDSD_MASK;
			}

			static inline void LEDs_TurnOnLEDs(const uint8_t LEDMask)
			{
				PORTD |= (LEDMask & LEDSD_MASK);
			}

			static inline void LEDs_TurnOffLEDs(const uint8_t LEDMask)
			{
				PORTD &= ~(LEDMask & LEDSD_MASK);
			}

			static inline void LEDs_SetAllLEDs(const uint8_t LEDMask)
			{
				PORTD |= (PORTD & ~LEDSD_MASK) | (LEDMask & LEDSD_MASK);
			}

		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

