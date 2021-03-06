/**
 * @file	lpc2106.h
 * @brief	Header Containinig data structures for accessing LPC2106 peripherals only used modules are defined
 * @author  Hugo Reis
 * @date    10/2016
 ******************************************************************************/
#ifndef lpc2106_h_
#define lpc2106_h_
 
#include <stdint.h>
 
#define __IO volatile         // RW
#define __I  volatile const   // RO
#define __O  volatile         // WO
  
typedef struct{
	__IO    uint32_t    PIN;           /*!< Offset: 0x00 Pin Value Register                      */
    __IO    uint32_t    SET;           /*!< Offset: 0x04 Output Set Register                     */
    __IO    uint32_t    DIR;           /*!< Offset: 0x08 Direction Control Register              */
    __IO    uint32_t    CLR;           /*!< Offset: 0x0c Output Clear Register                   */
}GPIO_Type;

#define GPIO0_BASE      (0xE0028000UL)                     /*!< GPIO Port 0                      */
#define GPIO0           ((GPIO_Type *)GPIO0_BASE)          /*!< GPIO Port 0                      */

typedef struct{
	__IO    uint32_t    DIR;           /*!< Offset: 0x00 Direction Control Register              */           
	uint32_t reserved[3];
	__IO    uint32_t    MASK;          /*!< Offset: 0x10 Port Mask                               */
    __IO    uint32_t    PIN;           /*!< Offset: 0x14 Pin Value Register                      */
    __IO    uint32_t    SET;           /*!< Offset: 0x18 Output Set Register                     */
    __IO    uint32_t    CLR;           /*!< Offset: 0x1C Output Clear Register                   */
}FIO_Type;

#define FIO0_BASE       (0x3FFFC000UL)                     /*!< FPIO Port 0                      */
#define FIO0            ((FIO_Type *)FIO0_BASE)            /*!< FPIO Port 0                      */

typedef struct {	
	__IO    uint32_t    SPCR;            /*!< Offset: 0x00 Control Register                      */
    __I     uint32_t    SPSR;            /*!< Offset: 0x04 Status Register                       */
    __IO    uint32_t    SPDR;            /*!< Offset: 0x08 Data Register                         */
    __IO    uint32_t    SPCCR;           /*!< Offset: 0x0c Clock Counter Register                */
	uint32_t reserved[4];
    __IO    uint32_t    SPINT;           /*!< Offset: 0x1C Interrupt Flag Register               */
} SPI_Type;

#define SPI0_BASE       (0xE0020000UL)                     /*!< SPI Interface 0                  */
#define SPI0            ((SPI_Type *)SPI0_BASE)            /*!< SPI Interface 0                  */

typedef struct {
    __IO    uint32_t    IR;            /*!< Offset: 0x00 Interrupt Register                      */
    __IO    uint32_t    TCR;           /*!< Offset: 0x04 Timer Control Register                  */
    __IO    uint32_t    TC;            /*!< Offset: 0x08 Timer Counter                           */
    __IO    uint32_t    PR;            /*!< Offset: 0x0c Prescale Register                       */
    __IO    uint32_t    PC;            /*!< Offset: 0x10 Prescale Counter                        */
    __IO    uint32_t    MCR;           /*!< Offset: 0x14 Match Control Register                  */
    __IO    uint32_t    MR0;           /*!< Offset: 0x18 Match Register 0                        */
    __IO    uint32_t    MR1;           /*!< Offset: 0x1c Match Register 1                        */
    __IO    uint32_t    MR2;           /*!< Offset: 0x20 Match Register 2                        */
    __IO    uint32_t    MR3;           /*!< Offset: 0x24 Match Register 3                        */
    __IO    uint32_t    CCR;           /*!< Offset: 0x28 Capture Control Register                */
    __I     uint32_t    CR0;           /*!< Offset: 0x2c Capture Register 0                      */
    __I     uint32_t    CR1;           /*!< Offset: 0x30 Capture Register 1                      */
    __I     uint32_t    CR2;           /*!< Offset: 0x34 Capture Register 2                      */
    __I     uint32_t    CR3;           /*!< Offset: 0x38 Capture Register 3                      */
    __IO    uint32_t    EMR;           /*!< Offset: 0x3c External Match Register                 */
            uint32_t      Reserved16_27[12];
    __IO    uint32_t    CTCR;          /*!< Offset: 0x70 Count Control Register                  */
} TIMER_Type;

#define TIMER0_BASE     (0xE0004000UL)                     /*!< TIMER 0                   */
#define TIMER1_BASE     (0xE0008000UL)                     /*!< TIMER 1                   */
#define TIMER0          ((TIMER_Type *)TIMER0_BASE)        /*!< 32-Bit Timer 0                   */
#define TIMER1          ((TIMER_Type *)TIMER1_BASE)        /*!< 32-Bit Timer 1                   */

typedef struct {
    __IO    uint32_t    ILR;           /*!< Offset: 0x00 Interrupt Location Register             */
    __I     uint32_t    CTC;           /*!< Offset: 0x04 Clock Tick Counter                      */
    __IO    uint32_t    CCR;           /*!< Offset: 0x08 Clock Control Register                  */
    __IO    uint32_t    CIIR;          /*!< Offset: 0x0c Counter Increment Interrupt Register    */
    __IO    uint32_t    AMR;           /*!< Offset: 0x10 Alarm Mask Register                     */
    __I     uint32_t    CTIME0;        /*!< Offset: 0x14 Consolidated Time Register 0            */
    __I     uint32_t    CTIME1;        /*!< Offset: 0x18 Consolidated Time Register 1            */
    __I     uint32_t    CTIME2;        /*!< Offset: 0x1c Consolidated Time Register 2            */
    __IO    uint32_t    SEC;           /*!< Offset: 0x20 Seconds Counter                         */
    __IO    uint32_t    MIN;           /*!< Offset: 0x24 Minutes Register                        */
    __IO    uint32_t    HOUR;          /*!< Offset: 0x28 Hours Register                          */
    __IO    uint32_t    DOM;           /*!< Offset: 0x2c Day of Month Register                   */
    __IO    uint32_t    DOW;           /*!< Offset: 0x30 Day of Week Register                    */
    __IO    uint32_t    DOY;           /*!< Offset: 0x34 Day of Year Register                    */
    __IO    uint32_t    MONTH;         /*!< Offset: 0x38 Months Register                         */
    __IO    uint32_t    YEAR;          /*!< Offset: 0x3c Years Register                          */
            uint32_t      Reserved16_23[8];
    __IO    uint32_t    ALSEC;         /*!< Offset: 0x60 Alarm Seconds Value                     */
    __IO    uint32_t    ALMIN;         /*!< Offset: 0x64 Alarm Minutes Value                     */
    __IO    uint32_t    ALHOUR;        /*!< Offset: 0x68 Alarm Seconds Value                     */
    __IO    uint32_t    ALDOM;         /*!< Offset: 0x6c Alarm Day of Month Value                */
    __IO    uint32_t    ALDOW;         /*!< Offset: 0x70 Alarm Day of Week Value                 */
    __IO    uint32_t    ALDOY;         /*!< Offset: 0x74 Alarm Day of Year Value                 */
    __IO    uint32_t    ALMONTH;       /*!< Offset: 0x78 Alarm Months Value                      */
    __IO    uint32_t    ALYEAR;        /*!< Offset: 0x7c Alarm Years Value                       */
    __IO    uint32_t    PREINT;        /*!< Offset: 0x80 Prescaler Integer Value                 */
    __IO    uint32_t    PREFRAC;       /*!< Offset: 0x84 Prescaler Fraction Value                */
} RTC_Type;
#define RTC_BASE        (0xE0024000UL)                     /*!< Real Time Clock                  */
#define RTC             ((RTC_Type *)RTC_BASE)             /*!< Real Time Clock                  */

typedef struct {
    __IO    uint32_t    PINSEL0;       /*!< Offset: 0x00 Pin Function Select Register 0          */
	__IO    uint32_t    PINSEL1;       /*!< Offset: 0x04 Pin Function Select Register 1          */
} PINCON_Type;

#define PINCON_BASE     (0xE002C000UL)                     /*!< Pin Function Selection Block     */
#define PINCON          ((PINCON_Type *)PINCON_BASE)       /*!< Pin Function Selection Block     */

typedef struct {
    __IO    uint32_t    MAMCR;         /*!< Offset: 0x000 Mem Accel Control Register             */
    __IO    uint32_t    MAMTIM;        /*!< Offset: 0x004 Mem Accel Timing Control               */
    __IO    uint32_t    Reserved_2_15[14];
    __IO    uint32_t    MEMMAP;        /*!< Offset: 0x040 Memory Mapping Control                 */
            uint32_t    Reserved_17_31[15];
    __IO    uint32_t    PLLCON;        /*!< Offset: 0x080 PLL Control Register                   */
    __IO    uint32_t    PLLCFG;        /*!< Offset: 0x084 PLL Config Register                    */
    __I     uint32_t    PLLSTAT;       /*!< Offset: 0x088 PLL Status Register                    */
    __O     uint32_t    PLLFEED;       /*!< Offset: 0x08c PLL Feed Register                      */
            uint32_t    Reserved_36_47[12];
    __IO    uint32_t    PCON;          /*!< Offset: 0x0c0 Power Control Register                 */
    __IO    uint32_t    PCONP;         /*!< Offset: 0x0c4 Power Control for Peripherals          */		
            uint32_t    Reserved_50_63[14];
    __IO    uint32_t    APBDIV;        /*!< Offset: 0x100 APB Divider Control                    */
            uint32_t    Reserved_65_79[15];
    __IO    uint32_t    EXTINT;        /*!< Offset: 0x140 External Int Flag Register             */
    __IO    uint32_t    INTWAKE;       /*!< Offset: 0x144 External Int Wkup Register             */
    __IO    uint32_t    EXTMODE;       /*!< Offset: 0x148 External Int Mode Register             */
    __IO    uint32_t    EXTPOLAR;      /*!< Offset: 0x14c External Int Polarities                */
            uint32_t    Reserved_84_103[20];
    __IO    uint32_t    SCS;           /*!< Offset: 0x1a0 System Control & Status                */
} SYSCON_Type;

#define SYSCON_BASE     (0xE01FC000UL)                     /*!< System Control Block             */
#define SC              ((SYSCON_Type *)SYSCON_BASE)       /*!< System Control Block             */

/* flash block addresses

0 8 0x0000 0000 - 0x0000 1FFF
1 8 0x0000 2000 - 0x0000 3FFF
2 8 0x0000 4000 - 0x0000 5FFF
3 8 0x0000 6000 - 0x0000 7FFF
4 8 0x0000 8000 - 0x0000 9FFF
5 8 0x0000 A000 - 0x0000 BFFF
6 8 0x0000 C000 - 0x0000 DFFF
7 8 0x0000 E000 - 0x0000 FFFF
8 8 0x0001 0000 - 0x0001 1FFF
9 8 0x0001 2000 - 0x0001 3FFF
10 (0x0A) 8 0x0001 4000 - 0x0001 5FFF
11 (0x0B) 8 0x0001 6000 - 0x0001 7FFF
12 (0x0C) 8 0x0001 8000 - 0x0001 9FFF
13 (0x0D) 8 0x0001 A000 - 0x0001 BFFF
14 (0x0E) 8 0x0001 C000 - 0x0001 DFFF
15 (0x0F) 8 0x0001 E000 - 0x0001 FFFF
*/

#endif
