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
 *  \brief Board specific Buttons driver header for the Picade.
 *  \copydetails Group_Buttons_PICADE
 *
 *  \note This file should not be included directly. It is automatically included as needed by the Buttons driver
 *        dispatch header located in LUFA/Drivers/Board/Buttons.h.
 */

/** \ingroup Group_Buttons
 *  \defgroup Group_Buttons_PICADE PICADE
 *  \brief Board specific Buttons driver header for the Picade.
 *
 *  Board specific Buttons driver header for the Picade.
 *
 *  @{
 */

#ifndef __BUTTONS_PICADE_H__
#define __BUTTONS_PICADE_H__

	/* Includes: */
		#include <LUFA/Common/Common.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_BUTTONS_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/Buttons.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			#define BUTTON1			(1 << 7)
			#define BUTTON2			(1 << 6)
			#define BUTTON3			(1 << 5)
			#define BUTTON4			(1 << 4)
			#define BUTTON5			(1 << 1)
			#define BUTTON6			(1 << 0)
			#define BUTTONF_MASK	(BUTTON1 | BUTTON2 | BUTTON3 | BUTTON4 | BUTTON5 | BUTTON6)
			
			#define UTIL_START		(1 << 0)
			#define UTIL_SELECT		(1 << 1)
			#define UTIL_ENTER		(1 << 2)
			#define UTIL_ESC		(1 << 3)
			#define UTILD_MASK		(UTIL_START | UTIL_SELECT | UTIL_ENTER | UTIL_ESC)
			
			#define GPIO1			(1 << 6)
			#define GPIO2			(1 << 7)
			#define GPIO3			(1 << 4)
			#define GPIO4			(1 << 5)
			#define GPIO5			(1 << 6)
			#define GPIO6			(1 << 6)
			#define GPIOD_MASK		(GPIO1 | GPIO2)
			#define GPIOB_MASK		(GPIO3 | GPIO4 | GPIO5)
			#define GPIOC_MASK		(GPIO6)

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			// #################### BUTTON ####################
			static inline void Buttons_Init(void)
			{
				DDRF  &= ~BUTTONF_MASK;
				PORTF |=  BUTTONF_MASK;
			}

			static inline void Buttons_Disable(void)
			{
				DDRF  &= ~BUTTONF_MASK;
				PORTF &= ~BUTTONF_MASK;
			}

			static inline uint8_t Buttons_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t Buttons_GetStatus(void)
			{
				return ( ((uint8_t)~PINF & BUTTONF_MASK) );
			}
			
			// #################### UTIL ####################
			static inline void Util_Init(void)
			{
				DDRD  &= ~UTILD_MASK;
				PORTD |=  UTILD_MASK;
			}

			static inline void Util_Disable(void)
			{
				DDRD  &= ~UTILD_MASK;
				PORTD &= ~UTILD_MASK;
			}

			static inline uint8_t Util_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t Util_GetStatus(void)
			{
				return ( ((uint8_t)~PIND & UTILD_MASK) );
			}
			
			// #################### GPIO ####################
			static inline void GPIO_Init(void)
			{
				DDRD  &= ~GPIOD_MASK;
				PORTD |=  GPIOD_MASK;
				
				DDRB  &= ~GPIOB_MASK;
				PORTB |=  GPIOB_MASK;
							
				DDRC  &= ~GPIOC_MASK;
				PORTC |=  GPIOC_MASK;
			}

			static inline void GPIO_Disable(void)
			{
				DDRD  &= ~GPIOD_MASK;
				PORTD &= ~GPIOD_MASK;
				
				DDRB  &= ~GPIOB_MASK;
				PORTB &= ~GPIOB_MASK;
							
				DDRC  &= ~GPIOC_MASK;
				PORTC &= ~GPIOC_MASK;
			}

			static inline uint8_t GPIOD_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t GPIOD_GetStatus(void)
			{
				return ( ((uint8_t)~PIND & GPIOD_MASK) );
			}
			
			static inline uint8_t GPIOB_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t GPIOB_GetStatus(void)
			{
				return ( ((uint8_t)~PINB & GPIOB_MASK) );
			}
			
			static inline uint8_t GPIOC_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t GPIOC_GetStatus(void)
			{
				return ( ((uint8_t)~PINC & GPIOC_MASK) );
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

