/*******************************************************************************
* File Name: CyLib.h
* Version 5.0
*
*  Description:
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_BOOT_CYLIB_H)
#define CY_BOOT_CYLIB_H

#include "cytypes.h"
#include "cydevice_trm.h"
#include "CyLFClk.h"

#include <string.h>
#include <limits.h>
#include <ctype.h>


/***************************************
*    Function Prototypes
***************************************/

/* Clocks API */
void CySysClkImoStart(void);
void CySysClkImoStop(void);
void CySysClkWriteHfclkDirect(uint32 clkSelect);

#if (CY_PSOC4_4100M || CY_PSOC4_4200M)
    void CySysClkImoEnableWcoLock(void);
    void CySysClkImoDisableWcoLock(void);
#endif /* (CY_PSOC4_4100M || CY_PSOC4_4200M) */

#if !(CY_PSOC4_4100 || CY_PSOC4_4200)
    void CySysClkWriteHfclkDiv(uint32 divider);
#endif /* !(CY_PSOC4_4100 || CY_PSOC4_4200) */

void CySysClkWriteSysclkDiv(uint32 divider);
void CySysClkWriteImoFreq(uint32 freq);

#if (CY_PSOC4_4100BL || CY_PSOC4_4200BL)
    void CySysClkWriteEcoDiv(uint32 divider);
#endif /* (CY_PSOC4_4100BL || CY_PSOC4_4200BL) */



#if(CY_IP_SRSSV2)
    /* Low Voltage Detection */
    void   CySysLvdEnable(uint32 threshold);
    void   CySysLvdDisable(void);
    uint32 CySysLvdGetInterruptSource(void);
    void   CySysLvdClearInterrupt(void);
#endif  /* (CY_IP_SRSSV2) */


/* Interrupt Function Prototypes */
cyisraddress CyIntSetSysVector(uint8 number, cyisraddress address);
cyisraddress CyIntGetSysVector(uint8 number);

cyisraddress CyIntSetVector(uint8 number, cyisraddress address);
cyisraddress CyIntGetVector(uint8 number);

void   CyIntSetPriority(uint8 number, uint8 priority);
uint8  CyIntGetPriority(uint8 number);

void   CyIntEnable(uint8 number);
uint8  CyIntGetState(uint8 number);
void   CyIntDisable(uint8 number);

void   CyIntSetPending(uint8 number);
void   CyIntClearPending(uint8 number);

uint32 CyDisableInts(void);
void   CyEnableInts(uint32 mask);

/* System Function Prototypes */
void  CyDelay(uint32 milliseconds);
void  CyDelayUs(uint16 microseconds);
void  CyDelayFreq(uint32 freq);
void  CyDelayCycles(uint32 cycles);

/* General APIs */
void  CySoftwareReset(void);
uint8 CyEnterCriticalSection(void);
void  CyExitCriticalSection(uint8 savedIntrStatus);
void  CyHalt(uint8 reason);
uint32 CySysGetResetReason(uint32 reason);

/* Default interrupt handler */
CY_ISR_PROTO(IntDefaultHandler);

/* System tick timer APIs */
typedef void (*cySysTickCallback)(void);

void CySysTickStart(void);
void CySysTickInit(void);
void CySysTickEnable(void);
void CySysTickStop(void);
void CySysTickEnableInterrupt(void);
void CySysTickDisableInterrupt(void);
void CySysTickSetReload(uint32 value);
uint32 CySysTickGetReload(void);
uint32 CySysTickGetValue(void);
cySysTickCallback CySysTickSetCallback(uint32 number, cySysTickCallback function);
cySysTickCallback CySysTickGetCallback(uint32 number);

#if(!CY_PSOC3 && !CY_PSOC4_4000 && !CY_PSOC4_4100 && !CY_PSOC4_4200)
    void CySysTickSetClockSource(uint32 clockSource);
#endif /* (!CY_PSOC3 && !CY_PSOC4_4000 && !CY_PSOC4_4100 && !CY_PSOC4_4200) */

uint32 CySysTickGetCountFlag(void);
void CySysTickClear(void);
extern uint32 CySysTickInitVar;

/* Do not use these definitions directly in your application */
extern uint32 cydelayFreqHz;
extern uint32 cydelayFreqKhz;
extern uint8  cydelayFreqMhz;
extern uint32 cydelay32kMs;

#if (CY_PSOC4_4100BL || CY_PSOC4_4200BL)
    cystatus CySysClkEcoStart(uint32 timeoutUs);
    void     CySysClkEcoStop(void);
    uint32   CySysClkEcoReadStatus(void);
#endif  /* (CY_PSOC4_4100BL || CY_PSOC4_4200BL) */

void CyGetUniqueId(uint32* uniqueId);


/***************************************
* API Constants
***************************************/


/*******************************************************************************
* Clock API Constants
*******************************************************************************/

/* CySysClkWriteHfclkDirect() - implementation definitions */
#if(CY_IP_SRSSV2)
    #define CY_SYS_CLK_SELECT_DIRECT_SEL_MASK           (( uint32 ) 0x07u)
    #if (CY_PSOC4_4100BL || CY_PSOC4_4200BL)
        /* The ECO is the valid option */
        #define CY_SYS_CLK_SELECT_DIRECT_SEL_PARAM_MASK     (( uint32 ) 0x03u)
    #else
        #define CY_SYS_CLK_SELECT_DIRECT_SEL_PARAM_MASK     (( uint32 ) 0x01u)
    #endif  /* (CY_PSOC4_4100BL || CY_PSOC4_4200BL) */
#else
    #define CY_SYS_CLK_SELECT_DIRECT_SEL_MASK           (( uint32 ) 0x03u)
    #define CY_SYS_CLK_SELECT_DIRECT_SEL_PARAM_MASK     (CY_SYS_CLK_SELECT_DIRECT_SEL_MASK)
#endif  /* (CY_IP_SRSSV2) */

/* CySysClkWriteHfclkDirect() - parameter definitions */
#define CY_SYS_CLK_HFCLK_IMO                            (0u)
#define CY_SYS_CLK_HFCLK_EXTCLK                         (1u)
#if (CY_PSOC4_4100BL || CY_PSOC4_4200BL)
    #define CY_SYS_CLK_HFCLK_ECO                        (2u)
#endif  /* (CY_PSOC4_4100BL || CY_PSOC4_4200BL) */

/* CySysClkWriteSysclkDiv() - parameter definitions */
#define CY_SYS_CLK_SYSCLK_DIV1                          (0u)
#define CY_SYS_CLK_SYSCLK_DIV2                          (1u)
#define CY_SYS_CLK_SYSCLK_DIV4                          (2u)
#define CY_SYS_CLK_SYSCLK_DIV8                          (3u)
#if(CY_IP_SRSSV2)
    #define CY_SYS_CLK_SYSCLK_DIV16                     (4u)
    #define CY_SYS_CLK_SYSCLK_DIV32                     (5u)
    #define CY_SYS_CLK_SYSCLK_DIV64                     (6u)
    #define CY_SYS_CLK_SYSCLK_DIV128                    (7u)
#endif  /* (CY_IP_SRSSV2) */


/* CySysClkWriteSysclkDiv() - implementation definitions */
#if(CY_IP_SRSSV2)
    #define CY_SYS_CLK_SELECT_SYSCLK_DIV_SHIFT          (19u)
    #define CY_SYS_CLK_SELECT_SYSCLK_DIV_MASK           (( uint32 )0x07u)
#else
    #define CY_SYS_CLK_SELECT_SYSCLK_DIV_SHIFT          (6u)
    #define CY_SYS_CLK_SELECT_SYSCLK_DIV_MASK           (( uint32 )0x03u)
#endif  /* (CY_IP_SRSSV2) */


/* CySysClkWriteImoFreq() - implementation definitions */
#if(CY_IP_SRSSV2)
    #define CY_SYS_CLK_IMO_MAX_FREQ_MHZ                 (48u)
    #define CY_SYS_CLK_IMO_MIN_FREQ_MHZ                 (3u)

    #define CY_SYS_CLK_IMO_TEMP_FREQ_MHZ                (24u)
    #define CY_SYS_CLK_IMO_TEMP_FREQ_TRIM2              (0x19u)     /* Corresponds to 24 MHz */

    #define CY_SYS_CLK_IMO_BOUNDARY_FREQ_MHZ            (43u)
    #define CY_SYS_CLK_IMO_BOUNDARY_FREQ_TRIM2          (0x30u)     /* Corresponds to 43 MHz */

    #define CY_SYS_CLK_IMO_FREQ_TIMEOUT_CYCLES          (5u)
    #define CY_SYS_CLK_IMO_TRIM_TIMEOUT_US              (5u)
    #define CY_SYS_CLK_IMO_FREQ_TABLE_SIZE              (46u)
    #define CY_SYS_CLK_IMO_FREQ_TABLE_OFFSET            (3u)
    #define CY_SYS_CLK_IMO_FREQ_BITS_MASK               (( uint32 )0x3Fu)
    #define CY_SYS_CLK_IMO_FREQ_CLEAR                   (( uint32 )(CY_SYS_CLK_IMO_FREQ_BITS_MASK << 8u))
	#define CY_SYS_CLK_IMO_TRIM4_GAIN_MASK				(( uint32 )0x1Fu)
	#define CY_SYS_CLK_IMO_TRIM4_GAIN					(( uint32 ) 12u)
#else
    #define CY_SYS_CLK_IMO_MIN_FREQ_MHZ                 (24u)
    #define CY_SYS_CLK_IMO_MAX_FREQ_MHZ                 (48u)
    #define CY_SYS_CLK_IMO_STEP_SIZE_MASK               (0x03u)
    #define CY_SYS_CLK_IMO_TRIM1_OFFSET_MASK            (( uint32 )(0xFFu))
    #define CY_SYS_CLK_IMO_TRIM2_FSOFFSET_MASK          (( uint32 )(0x07u))
    #define CY_SYS_CLK_IMO_TRIM3_VALUES_MASK            (( uint32 )(0x7Fu))
    #define CY_SYS_CLK_IMO_SELECT_FREQ_MASK             (( uint32 )(0x07u))
    #define CY_SYS_CLK_IMO_SELECT_24MHZ                 (( uint32 )(0x00u))

    #define CY_SYS_CLK_IMO_TRIM_DELAY_US                (( uint32 )(50u))
#endif  /* (CY_IP_SRSSV2) */

#if(CY_IP_SRSSV2)
        /* Conversion between CySysClkWriteImoFreq() parameter and register's value */
        extern const uint8 cyImoFreqMhz2Reg[CY_SYS_CLK_IMO_FREQ_TABLE_SIZE];
#endif /* (CY_IP_SRSSV2) */


/* CySysClkImoStart()/CySysClkImoStop() - implementation definitions */
#define CY_SYS_CLK_IMO_CONFIG_ENABLE                    (( uint32 )(( uint32 )0x01u << 31u))



#if(CY_IP_SRSSLT)
    /* CySysClkWriteHfclkDiv() - parameter definitions */
    #define CY_SYS_CLK_HFCLK_DIV_NODIV                  (0u)
    #define CY_SYS_CLK_HFCLK_DIV_2                      (1u)
    #define CY_SYS_CLK_HFCLK_DIV_4                      (2u)
    #define CY_SYS_CLK_HFCLK_DIV_8                      (3u)

    /* CySysClkWriteHfclkDiv() - implementation definitions */
    #define CY_SYS_CLK_SELECT_HFCLK_DIV_SHIFT           (2u)
    #define CY_SYS_CLK_SELECT_HFCLK_DIV_MASK            (( uint32 )0x03u)
#endif  /* (CY_IP_SRSSLT) */


/* Operating source for Pump clock */
#if(CY_IP_SRSSV2)
    #define CY_SYS_CLK_IMO_CONFIG_PUMP_SEL_SHIFT        (25u)
    #define CY_SYS_CLK_IMO_CONFIG_PUMP_SEL_MASK         ((uint32) 0x07u)
    #define CY_SYS_CLK_IMO_CONFIG_PUMP_SEL_IMO          (1u)

	#define CY_SYS_CLK_IMO_CONFIG_PUMP_OSC              (( uint32 )(( uint32 )0x01u << 22u))
#else /* CY_IP_SRSSLT */
    #define CY_SYS_CLK_SELECT_PUMP_SEL_SHIFT            (4u)
    #define CY_SYS_CLK_SELECT_PUMP_SEL_MASK             ((uint32) 0x03u)
    #define CY_SYS_CLK_SELECT_PUMP_SEL_IMO              (1u)
#endif  /* (CY_IP_SRSSLT) */


#if (CY_PSOC4_4100BL || CY_PSOC4_4200BL)
    /* Radio configuration register */
    #define CY_SYS_XTAL_BLESS_RF_CONFIG_RF_ENABLE       (( uint32 )0x01u)

    /* RFCTRL mode transition control */
    #define CY_SYS_XTAL_BLERD_DBUS_XTAL_ENABLE          (( uint32 )(( uint32 )0x01u << 15u))

    /* XO is oscillating status */
    #define CY_SYS_XTAL_BLERD_FSM_XO_AMP_DETECT         (( uint32 )0x01u)

    /* BB bump configuration 2 */
    #define CY_SYS_XTAL_BLERD_BB_XO_CAPTRIM_X1_MASK     (( uint32 )(( uint32 )0x7Fu <<  8u))
    #define CY_SYS_XTAL_BLERD_BB_XO_CAPTRIM_X2_MASK     (( uint32 )(( uint32 )0x7Fu <<  0u))
    #define CY_SYS_XTAL_BLERD_BB_XO_CAPTRIM_X1_ADD_CAP  (( uint32 )(( uint32 )0x01u << 15u))
    #define CY_SYS_XTAL_BLERD_BB_XO_CAPTRIM_X2_ADD_CAP  (( uint32 )(( uint32 )0x01u <<  7u))

    /* BB bump configuration 1 */
    #define CY_SYS_XTAL_BLERD_BB_XO_TRIM                ((uint32) 0x2002u)

    /* CySysClkWriteEcoDiv() - parameter definitions */
    #define CY_SYS_CLK_ECO_DIV1                         ((uint32) 0x00)
    #define CY_SYS_CLK_ECO_DIV2                         ((uint32) 0x01)
    #define CY_SYS_CLK_ECO_DIV4                         ((uint32) 0x02)
    #define CY_SYS_CLK_ECO_DIV8                         ((uint32) 0x03)

    /* CySysClkWriteEcoDiv() - implementation definitions */
    #define CY_SYS_CLK_XTAL_CLK_DIV_MASK                ((uint32) 0x03)
#endif  /* (CY_PSOC4_4100BL || CY_PSOC4_4200BL) */


/* CySysClkImoEnableWcoLock() / CySysClkImoDisableWcoLock() constants */
#if (CY_PSOC4_4100M || CY_PSOC4_4200M)
    /* Fimo = DPLL_MULT  * Fwco */

    #define CY_SYS_CLK_WCO_CONFIG_DPLL_ENABLE               (( uint32 )(( uint32 )0x01u << 30u))

    /* Rounding integer division: DPLL_MULT = (Fimo_in_khz + Fwco_in_khz / 2) / Fwco_in_khz */
    #define CY_SYS_CLK_WCO_DPLL_MULT_VALUE(frequencyMhz)    ((uint32) (((((frequencyMhz) * 1000000u) + 16384u) / 32768u) - 1u))
    #define CY_SYS_CLK_WCO_DPLL_MULT_MASK                   ((uint32) 0x7FFu)

    #define CY_SYS_CLK_WCO_CONFIG_DPLL_LF_IGAIN_SHIFT       (16u)
    #define CY_SYS_CLK_WCO_CONFIG_DPLL_LF_PGAIN_SHIFT       (19u)

    #define CY_SYS_CLK_WCO_CONFIG_DPLL_LF_IGAIN_MASK        (( uint32 )(( uint32 )0x07u << CY_SYS_CLK_WCO_CONFIG_DPLL_LF_IGAIN_SHIFT))
    #define CY_SYS_CLK_WCO_CONFIG_DPLL_LF_PGAIN_MASK        (( uint32 )(( uint32 )0x07u << CY_SYS_CLK_WCO_CONFIG_DPLL_LF_PGAIN_SHIFT))

    #define CY_SYS_CLK_WCO_CONFIG_DPLL_LF_IGAIN             (( uint32 )(( uint32 ) 4u << CY_SYS_CLK_WCO_CONFIG_DPLL_LF_IGAIN_SHIFT))
    #define CY_SYS_CLK_WCO_CONFIG_DPLL_LF_PGAIN             (( uint32 )(( uint32 ) 2u << CY_SYS_CLK_WCO_CONFIG_DPLL_LF_PGAIN_SHIFT))

#endif /* (CY_PSOC4_4100M || CY_PSOC4_4200M) */


/*******************************************************************************
* System API Constants
*******************************************************************************/

/* CySysGetResetReason() */
#define CY_SYS_RESET_WDT_SHIFT          (0u)
#define CY_SYS_RESET_PROTFAULT_SHIFT    (3u)
#define CY_SYS_RESET_SW_SHIFT           (4u)

#define CY_SYS_RESET_WDT                ((uint32)1u << CY_SYS_RESET_WDT_SHIFT      )
#define CY_SYS_RESET_PROTFAULT          ((uint32)1u << CY_SYS_RESET_PROTFAULT_SHIFT)
#define CY_SYS_RESET_SW                 ((uint32)1u << CY_SYS_RESET_SW_SHIFT       )


/* CySoftwareReset() - implementation definitions */

/* Vector Key */
#define CY_SYS_CM0_AIRCR_VECTKEY_SHIFT      (16u)
#define CY_SYS_CM0_AIRCR_VECTKEY            ((uint32)((uint32)0x05FAu << CY_SYS_CM0_AIRCR_VECTKEY_SHIFT))
#define CY_SYS_CM0_AIRCR_VECTKEY_MASK       ((uint32)((uint32)0xFFFFu << CY_SYS_CM0_AIRCR_VECTKEY_SHIFT))

/* System Reset Request */
#define CY_SYS_CM0_AIRCR_SYSRESETREQ_SHIFT  (2u)
#define CY_SYS_CM0_AIRCR_SYSRESETREQ        ((uint32)((uint32)1u << CY_SYS_CM0_AIRCR_SYSRESETREQ_SHIFT))


#if defined(__ARMCC_VERSION)

    #define CyGlobalIntEnable           do                      \
                                        {                       \
                                            __enable_irq();     \
                                        } while ( 0 )

    #define CyGlobalIntDisable          do                      \
                                        {                       \
                                            __disable_irq();    \
                                        } while ( 0 )

#elif defined(__GNUC__) || defined (__ICCARM__)

    #define CyGlobalIntEnable           do                      \
                                        {                       \
                                            __asm("CPSIE   i"); \
                                        } while ( 0 )

    #define CyGlobalIntDisable          do                      \
                                        {                       \
                                            __asm("CPSID   i"); \
                                        } while ( 0 )
#else
    #error No compiler toolchain defined
    #define CyGlobalIntEnable
    #define CyGlobalIntDisable
#endif  /* (__ARMCC_VERSION) */

/* System tick timer */
#define CY_SYS_SYST_CSR_ENABLE               ((uint32) (0x01u))
#define CY_SYS_SYST_CSR_ENABLE_INT           ((uint32) (0x02u))
#define CY_SYS_SYST_CSR_CLK_SOURCE_SHIFT     (0x02u)
#define CY_SYS_SYST_CSR_COUNTFLAG_SHIFT      (16u)
#define CY_SYS_SYST_CSR_CLK_SRC_SYSCLK       ((uint32) (1u))
#define CY_SYS_SYST_CSR_CLK_SRC_LFCLK        (0u)
#define CY_SYS_SYST_RVR_CNT_MASK             (0x00FFFFFFu)
#define CY_SYS_SYST_CVR_CNT_MASK             (0x00FFFFFFu)
#define CY_SYS_SYST_NUM_OF_CALLBACKS         (5u)


/*******************************************************************************
* Macro Name: CyAssert
********************************************************************************
* Summary:
*  Macro that evaluates the expression and, if it is false (evaluates to 0),
*  the processor is halted.
*
*  This macro is evaluated unless NDEBUG is defined.
*  If NDEBUG is defined, then no code is generated for this macro.
*  NDEBUG is defined by default for a Release build setting and not defined for
*  a Debug build setting.
*
* Parameters:
*  expr: Logical expression.  Asserts if false.
*
* Return:
*  None
*
*******************************************************************************/
#if !defined(NDEBUG)
    #define CYASSERT(x)                 do                              \
                                        {                               \
                                            if(0u == (x))               \
                                            {                           \
                                                CyHalt((uint8) 0u);     \
                                            }                           \
                                        } while ( 0u )
#else
    #define CYASSERT(x)
#endif  /* !defined(NDEBUG) */


/*******************************************************************************
* Interrupt API Constants
*******************************************************************************/
#define CY_NUM_INTERRUPTS                   (CY_IP_INT_NR)

#define CY_MIN_PRIORITY                     (3u)

#define CY_INT_IRQ_BASE                     (16u)
#define CY_INT_CLEAR_DISABLE_ALL            (0xFFFFFFFFu)
#define CY_INT_ENABLE_RANGE_MASK            (0x1Fu)

/* Register n contains priorities for interrupts N=4n .. 4n+3 */
#define CY_INT_PRIORITY_SHIFT(number)       (( uint32 )6u + (8u * (( uint32 )(number) % 4u)))

/* Mask to get valid range of system priority 0-3 */
#define CY_INT_PRIORITY_MASK                (( uint32 ) 0x03u)

/* CyIntSetSysVector()/CyIntGetSysVector() - parameter definitions */
#define CY_INT_NMI_IRQN                      ( 2u)      /* Non Maskable Interrupt      */
#define CY_INT_HARD_FAULT_IRQN               ( 3u)      /* Hard Fault Interrupt        */
#define CY_INT_SVCALL_IRQN                   (11u)      /* SV Call Interrupt           */
#define CY_INT_PEND_SV_IRQN                  (14u)      /* Pend SV Interrupt           */
#define CY_INT_SYSTICK_IRQN                  (15u)      /* System Tick Interrupt       */


#if(CY_IP_SRSSV2)


    /*******************************************************************************
    * Low Voltage Detection API Constants
    *******************************************************************************/

    /* CySysLvdEnable() - parameter definitions */
    #define CY_LVD_THRESHOLD_1_75_V             (( uint32 )  0u)
    #define CY_LVD_THRESHOLD_1_80_V             (( uint32 )  1u)
    #define CY_LVD_THRESHOLD_1_90_V             (( uint32 )  2u)
    #define CY_LVD_THRESHOLD_2_00_V             (( uint32 )  3u)
    #define CY_LVD_THRESHOLD_2_10_V             (( uint32 )  4u)
    #define CY_LVD_THRESHOLD_2_20_V             (( uint32 )  5u)
    #define CY_LVD_THRESHOLD_2_30_V             (( uint32 )  6u)
    #define CY_LVD_THRESHOLD_2_40_V             (( uint32 )  7u)
    #define CY_LVD_THRESHOLD_2_50_V             (( uint32 )  8u)
    #define CY_LVD_THRESHOLD_2_60_V             (( uint32 )  9u)
    #define CY_LVD_THRESHOLD_2_70_V             (( uint32 ) 10u)
    #define CY_LVD_THRESHOLD_2_80_V             (( uint32 ) 11u)
    #define CY_LVD_THRESHOLD_2_90_V             (( uint32 ) 12u)
    #define CY_LVD_THRESHOLD_3_00_V             (( uint32 ) 13u)
    #define CY_LVD_THRESHOLD_3_20_V             (( uint32 ) 14u)
    #define CY_LVD_THRESHOLD_4_50_V             (( uint32 ) 15u)

    /* CySysLvdEnable()  - implementation definitions */
    #define CY_LVD_PWR_VMON_CONFIG_LVD_EN           (( uint32 ) 0x01u)
    #define CY_LVD_PWR_VMON_CONFIG_LVD_SEL_SHIFT    (1u)
    #define CY_LVD_PWR_VMON_CONFIG_LVD_SEL_MASK     (( uint32 ) (0x0F << CY_LVD_PWR_VMON_CONFIG_LVD_SEL_SHIFT))
    #define CY_LVD_PROPAGATE_INT_TO_CPU             (( uint32 ) 0x02u)
    #define CY_LVD_STABILIZE_TIMEOUT_US             (1000u)

    /* CySysLvdGetInterruptSource()/ CySysLvdClearInterrupt()  - parameter definitions  */
    #define CY_SYS_LVD_INT                          (( uint32 ) 0x02u)
#endif  /* (CY_IP_SRSSV2) */

/* CyDelay()/CyDelayFreq()  - implementation definitions */
#define CY_DELAY_MS_OVERFLOW                    (0x8000u)
#define CY_DELAY_1M_THRESHOLD                   (1000000u)
#define CY_DELAY_1M_MINUS_1_THRESHOLD           (999999u)
#define CY_DELAY_1K_THRESHOLD                   (1000u)
#define CY_DELAY_1K_MINUS_1_THRESHOLD           (999u)


/***************************************
* Registers
***************************************/


/*******************************************************************************
* Clocks API Registers
*******************************************************************************/
#define CY_SYS_CLK_IMO_TRIM1_REG            (*(reg32 *) CYREG_CLK_IMO_TRIM1)
#define CY_SYS_CLK_IMO_TRIM1_PTR            ( (reg32 *) CYREG_CLK_IMO_TRIM1)

#define CY_SYS_CLK_IMO_TRIM2_REG            (*(reg32 *) CYREG_CLK_IMO_TRIM2)
#define CY_SYS_CLK_IMO_TRIM2_PTR            ( (reg32 *) CYREG_CLK_IMO_TRIM2)

#define CY_SYS_CLK_IMO_TRIM3_REG            (*(reg32 *) CYREG_CLK_IMO_TRIM3)
#define CY_SYS_CLK_IMO_TRIM3_PTR            ( (reg32 *) CYREG_CLK_IMO_TRIM3)

#define CY_SYS_CLK_IMO_TRIM4_REG            (*(reg32 *) CYREG_CLK_IMO_TRIM4)
#define CY_SYS_CLK_IMO_TRIM4_PTR            ( (reg32 *) CYREG_CLK_IMO_TRIM4)

#define CY_SYS_CLK_IMO_CONFIG_REG           (*(reg32 *) CYREG_CLK_IMO_CONFIG)
#define CY_SYS_CLK_IMO_CONFIG_PTR           ( (reg32 *) CYREG_CLK_IMO_CONFIG)


#define CY_SYS_CLK_SELECT_REG               (*(reg32 *) CYREG_CLK_SELECT)
#define CY_SYS_CLK_SELECT_PTR               ( (reg32 *) CYREG_CLK_SELECT)

#if(CY_IP_SRSSV2)


    #if(CY_PSOC4_4100 || CY_PSOC4_4200)
        #define CY_SFLASH_IMO_TRIM_REG(number)      ( ((reg8 *) CYREG_SFLASH_IMO_TRIM00)[number])
        #define CY_SFLASH_IMO_TRIM_PTR(number)      (&((reg8 *) CYREG_SFLASH_IMO_TRIM00)[number])
    #else
        #define CY_SFLASH_IMO_TRIM_REG(number)      ( ((reg8 *) CYREG_SFLASH_IMO_TRIM0)[number])
        #define CY_SFLASH_IMO_TRIM_PTR(number)      (&((reg8 *) CYREG_SFLASH_IMO_TRIM0)[number])
    #endif /* (CY_PSOC4_4100 || CY_PSOC4_4200) */

    #define CY_SFLASH_IMO_MAXF0_REG             (*(reg8 *) CYREG_SFLASH_IMO_MAXF0)
    #define CY_SFLASH_IMO_MAXF0_PTR             ( (reg8 *) CYREG_SFLASH_IMO_MAXF0)

    #define CY_SFLASH_IMO_ABS0_REG              (*(reg8 *) CYREG_SFLASH_IMO_ABS0)
    #define CY_SFLASH_IMO_ABS0_PTR              ( (reg8 *) CYREG_SFLASH_IMO_ABS0)

    #define CY_SFLASH_IMO_TMPCO0_REG            (*(reg8 *) CYREG_SFLASH_IMO_TMPCO0)
    #define CY_SFLASH_IMO_TMPCO0_PTR            ( (reg8 *) CYREG_SFLASH_IMO_TMPCO0)

    #define CY_SFLASH_IMO_MAXF1_REG             (*(reg8 *) CYREG_SFLASH_IMO_MAXF1)
    #define CY_SFLASH_IMO_MAXF1_PTR             ( (reg8 *) CYREG_SFLASH_IMO_MAXF1)

    #define CY_SFLASH_IMO_ABS1_REG              (*(reg8 *) CYREG_SFLASH_IMO_ABS1)
    #define CY_SFLASH_IMO_ABS1_PTR              ( (reg8 *) CYREG_SFLASH_IMO_ABS1)

    #define CY_SFLASH_IMO_TMPCO1_REG            (*(reg8 *) CYREG_SFLASH_IMO_TMPCO1)
    #define CY_SFLASH_IMO_TMPCO1_PTR            ( (reg8 *) CYREG_SFLASH_IMO_TMPCO1)

    #define CY_SFLASH_IMO_MAXF2_REG             (*(reg8 *) CYREG_SFLASH_IMO_MAXF2)
    #define CY_SFLASH_IMO_MAXF2_PTR             ( (reg8 *) CYREG_SFLASH_IMO_MAXF2)

    #define CY_SFLASH_IMO_ABS2_REG              (*(reg8 *) CYREG_SFLASH_IMO_ABS2)
    #define CY_SFLASH_IMO_ABS2_PTR              ( (reg8 *) CYREG_SFLASH_IMO_ABS2)

    #define CY_SFLASH_IMO_TMPCO2_REG            (*(reg8 *) CYREG_SFLASH_IMO_TMPCO2)
    #define CY_SFLASH_IMO_TMPCO2_PTR            ( (reg8 *) CYREG_SFLASH_IMO_TMPCO2)

    #define CY_SFLASH_IMO_MAXF3_REG             (*(reg8 *) CYREG_SFLASH_IMO_MAXF3)
    #define CY_SFLASH_IMO_MAXF3_PTR             ( (reg8 *) CYREG_SFLASH_IMO_MAXF3)

    #define CY_SFLASH_IMO_ABS3_REG              (*(reg8 *) CYREG_SFLASH_IMO_ABS3)
    #define CY_SFLASH_IMO_ABS3_PTR              ( (reg8 *) CYREG_SFLASH_IMO_ABS3)

    #define CY_SFLASH_IMO_TMPCO3_REG            (*(reg8 *) CYREG_SFLASH_IMO_TMPCO3)
    #define CY_SFLASH_IMO_TMPCO3_PTR            ( (reg8 *) CYREG_SFLASH_IMO_TMPCO3)

    #define CY_SFLASH_IMO_ABS4_REG              (*(reg8 *) CYREG_SFLASH_IMO_ABS4)
    #define CY_SFLASH_IMO_ABS4_PTR              ( (reg8 *) CYREG_SFLASH_IMO_ABS4)

    #define CY_SFLASH_IMO_TMPCO4_REG            (*(reg8 *) CYREG_SFLASH_IMO_TMPCO4)
    #define CY_SFLASH_IMO_TMPCO4_PTR            ( (reg8 *) CYREG_SFLASH_IMO_TMPCO4)

    #define CY_PWR_BG_TRIM4_REG                 (*(reg32 *) CYREG_PWR_BG_TRIM4)
    #define CY_PWR_BG_TRIM4_PTR                 ( (reg32 *) CYREG_PWR_BG_TRIM4)

    #define CY_PWR_BG_TRIM5_REG                 (*(reg32 *) CYREG_PWR_BG_TRIM5)
    #define CY_PWR_BG_TRIM5_PTR                 ( (reg32 *) CYREG_PWR_BG_TRIM5)

#else

    #define CY_SYS_CLK_IMO_SELECT_REG           (*(reg32 *) CYREG_CLK_IMO_SELECT)
    #define CY_SYS_CLK_IMO_SELECT_PTR           ( (reg32 *) CYREG_CLK_IMO_SELECT)

    #define CY_SFLASH_IMO_TCTRIM_REG(number)    ( ((reg8 *) CYREG_SFLASH_IMO_TCTRIM_LT0)[number])
    #define CY_SFLASH_IMO_TCTRIM_PTR(number)    (&((reg8 *) CYREG_SFLASH_IMO_TCTRIM_LT0)[number])

    #define CY_SFLASH_IMO_TRIM_REG(number)      ( ((reg8 *) CYREG_SFLASH_IMO_TRIM_LT0)[number])
    #define CY_SFLASH_IMO_TRIM_PTR(number)      (&((reg8 *) CYREG_SFLASH_IMO_TRIM_LT0)[number])

#endif  /* (CY_IP_SRSSV2) */


#if (CY_PSOC4_4100BL || CY_PSOC4_4200BL)
    /* Radio configuration register */
    #define CY_SYS_XTAL_BLESS_RF_CONFIG_REG         (*(reg32 *) CYREG_BLE_BLESS_RF_CONFIG)
    #define CY_SYS_XTAL_BLESS_RF_CONFIG_PTR         ( (reg32 *) CYREG_BLE_BLESS_RF_CONFIG)

    /* RFCTRL mode transition control */
    #define CY_SYS_XTAL_BLERD_DBUS_REG              (*(reg32 *) CYREG_BLE_BLERD_DBUS)
    #define CY_SYS_XTAL_BLERD_DBUS_PTR              ( (reg32 *) CYREG_BLE_BLERD_DBUS)

    /* RFCTRL state information */
    #define CY_SYS_XTAL_BLERD_FSM_REG              (*(reg32 *) CYREG_BLE_BLERD_FSM)
    #define CY_SYS_XTAL_BLERD_FSM_PTR              ( (reg32 *) CYREG_BLE_BLERD_FSM)

    /* BB bump configuration 1 */
    #define CY_SYS_XTAL_BLERD_BB_XO_REG             (*(reg32 *) CYREG_BLE_BLERD_BB_XO)
    #define CY_SYS_XTAL_BLERD_BB_XO_PTR             ( (reg32 *) CYREG_BLE_BLERD_BB_XO)

    /* BB bump configuration 2 */
    #define CY_SYS_XTAL_BLERD_BB_XO_CAPTRIM_REG     (*(reg32 *) CYREG_BLE_BLERD_BB_XO_CAPTRIM)
    #define CY_SYS_XTAL_BLERD_BB_XO_CAPTRIM_PTR     ( (reg32 *) CYREG_BLE_BLERD_BB_XO_CAPTRIM)

    /* Crystal clock divider configuration register */
    #define CY_SYS_CLK_XTAL_CLK_DIV_CONFIG_REG      (*(reg32 *) CYREG_BLE_BLESS_XTAL_CLK_DIV_CONFIG)
    #define CY_SYS_CLK_XTAL_CLK_DIV_CONFIG_PTR      ( (reg32 *) CYREG_BLE_BLESS_XTAL_CLK_DIV_CONFIG)
#endif  /* (CY_PSOC4_4100BL || CY_PSOC4_4200BL) */


/* CySysClkImoEnableWcoLock() / CySysClkImoDisableWcoLock() registers */
#if (CY_PSOC4_4100M || CY_PSOC4_4200M)
    /* WCO DPLL Register */
    #define CY_SYS_CLK_WCO_DPLL_REG                 (*(reg32 *) CYREG_WCO_DPLL)
    #define CY_SYS_CLK_WCO_DPLL_PTR                 ( (reg32 *) CYREG_WCO_DPLL)
#endif /* (CY_PSOC4_4100M || CY_PSOC4_4200M) */


/*******************************************************************************
* System API Registers
*******************************************************************************/
#define CY_SYS_CM0_AIRCR_REG                (*(reg32 *) CYREG_CM0_AIRCR)
#define CY_SYS_CM0_AIRCR_PTR                ( (reg32 *) CYREG_CM0_AIRCR)

/* Reset Cause Observation Register */
#define CY_SYS_RES_CAUSE_REG                (*(reg32 *) CYREG_RES_CAUSE)
#define CY_SYS_RES_CAUSE_PTR                ( (reg32 *) CYREG_RES_CAUSE)

#if(CY_IP_SRSSV2)

    /*******************************************************************************
    * Low Voltage Detection
    *******************************************************************************/

    /* Voltage Monitoring Trim and Configuration */
    #define CY_LVD_PWR_VMON_CONFIG_REG          (*(reg32 *) CYREG_PWR_VMON_CONFIG)
    #define CY_LVD_PWR_VMON_CONFIG_PTR          ( (reg32 *) CYREG_PWR_VMON_CONFIG)

    /* Power System Interrupt Mask Register */
    #define CY_LVD_PWR_INTR_MASK_REG            (*(reg32 *) CYREG_PWR_INTR_MASK)
    #define CY_LVD_PWR_INTR_MASK_PTR            ( (reg32 *) CYREG_PWR_INTR_MASK)

    /* Power System Interrupt Register */
    #define CY_LVD_PWR_INTR_REG                 (*(reg32 *) CYREG_PWR_INTR)
    #define CY_LVD_PWR_INTR_PTR                 ( (reg32 *) CYREG_PWR_INTR)

#endif  /* (CY_IP_SRSSV2) */


/*******************************************************************************
* Interrupt API Registers
*******************************************************************************/
#define CY_INT_VECT_TABLE                   ( (cyisraddress **) CYDEV_SRAM_BASE)

#define CY_INT_PRIORITY_REG(number)         ( ((reg32 *) CYREG_CM0_IPR0)[(number)/4u])
#define CY_INT_PRIORITY_PTR(number)         (&((reg32 *) CYREG_CM0_IPR0)[(number)/4u])

#define CY_INT_ENABLE_REG                   (*(reg32 *) CYREG_CM0_ISER)
#define CY_INT_ENABLE_PTR                   ( (reg32 *) CYREG_CM0_ISER)

#define CY_INT_CLEAR_REG                    (*(reg32 *) CYREG_CM0_ICER)
#define CY_INT_CLEAR_PTR                    ( (reg32 *) CYREG_CM0_ICER)

#define CY_INT_SET_PEND_REG                 (*(reg32 *) CYREG_CM0_ISPR)
#define CY_INT_SET_PEND_PTR                 ( (reg32 *) CYREG_CM0_ISPR)

#define CY_INT_CLR_PEND_REG                 (*(reg32 *) CYREG_CM0_ICPR)
#define CY_INT_CLR_PEND_PTR                 ( (reg32 *) CYREG_CM0_ICPR)


/*******************************************************************************
* System tick API Registers
*******************************************************************************/
#define CY_SYS_SYST_CSR_REG                 (*(reg32 *) CYREG_CM0_SYST_CSR)
#define CY_SYS_SYST_CSR_PTR                 ( (reg32 *) CYREG_CM0_SYST_CSR)

#define CY_SYS_SYST_RVR_REG                 (*(reg32 *) CYREG_CM0_SYST_RVR)
#define CY_SYS_SYST_RVR_PTR                 ( (reg32 *) CYREG_CM0_SYST_RVR)

#define CY_SYS_SYST_CVR_REG                 (*(reg32 *) CYREG_CM0_SYST_CVR)
#define CY_SYS_SYST_CVR_PTR                 ( (reg32 *) CYREG_CM0_SYST_CVR)

#define CY_SYS_SYST_CALIB_REG               (*(reg32 *) CYREG_CM0_SYST_CALIB)
#define CY_SYS_SYST_CALIB_PTR               ( (reg32 *) CYREG_CM0_SYST_CALIB)




/*******************************************************************************
* The following code is OBSOLETE and must not be used.
*
* If the obsoleted macro definitions are intended for use in the application,
* use the following scheme, redefine your own versions of these definitions:
*    #ifdef <OBSOLETED_DEFINE>
*        #undef  <OBSOLETED_DEFINE>
*        #define <OBSOLETED_DEFINE>      (<New Value>)
*    #endif
*
* Note: Redefine obsoleted macro definitions with caution. They might still be
*       used in the application and their modification might lead to unexpected
*       consequences.
*******************************************************************************/
#define CYINT_IRQ_BASE                     (CY_INT_IRQ_BASE)

/* SFLASH0 block has been renamed to SFLASH */
#if (CY_PSOC4_4100 || CY_PSOC4_4200)
    #if !defined(CYREG_SFLASH_IMO_TRIM21)
        #define CYREG_SFLASH_IMO_TRIM21         (CYREG_SFLASH0_IMO_TRIM21)
    #endif  /* !defined(CYREG_SFLASH_IMO_TRIM21) */
#endif /* (CY_PSOC4_4100 || CY_PSOC4_4200) */

#endif  /* CY_BOOT_CYLIB_H */


/* [] END OF FILE */
