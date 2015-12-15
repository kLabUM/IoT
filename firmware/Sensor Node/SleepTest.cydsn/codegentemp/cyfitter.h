#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include <cydevice.h>
#include <cydevice_trm.h>

/* I2C_1_I2C_IRQ */
#define I2C_1_I2C_IRQ__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define I2C_1_I2C_IRQ__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define I2C_1_I2C_IRQ__INTC_MASK 0x01u
#define I2C_1_I2C_IRQ__INTC_NUMBER 0u
#define I2C_1_I2C_IRQ__INTC_PRIOR_NUM 7u
#define I2C_1_I2C_IRQ__INTC_PRIOR_REG CYREG_NVIC_PRI_0
#define I2C_1_I2C_IRQ__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define I2C_1_I2C_IRQ__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* I2C_1_I2C_FF */
#define I2C_1_I2C_FF__ADR CYREG_I2C_ADR
#define I2C_1_I2C_FF__CFG CYREG_I2C_CFG
#define I2C_1_I2C_FF__CLK_DIV CYREG_I2C_CLK_DIV
#define I2C_1_I2C_FF__CSR CYREG_I2C_CSR
#define I2C_1_I2C_FF__D CYREG_I2C_D
#define I2C_1_I2C_FF__MCSR CYREG_I2C_MCSR
#define I2C_1_I2C_FF__PM_ACT_CFG CYREG_PM_ACT_CFG5
#define I2C_1_I2C_FF__PM_ACT_MSK 0x04u
#define I2C_1_I2C_FF__PM_STBY_CFG CYREG_PM_STBY_CFG5
#define I2C_1_I2C_FF__PM_STBY_MSK 0x04u
#define I2C_1_I2C_FF__XCFG CYREG_I2C_XCFG

/* crustal */
#define crustal__0__MASK 0x08u
#define crustal__0__PC CYREG_PRT15_PC3
#define crustal__0__PORT 15u
#define crustal__0__SHIFT 3
#define crustal__AG CYREG_PRT15_AG
#define crustal__AMUX CYREG_PRT15_AMUX
#define crustal__BIE CYREG_PRT15_BIE
#define crustal__BIT_MASK CYREG_PRT15_BIT_MASK
#define crustal__BYP CYREG_PRT15_BYP
#define crustal__CTL CYREG_PRT15_CTL
#define crustal__DM0 CYREG_PRT15_DM0
#define crustal__DM1 CYREG_PRT15_DM1
#define crustal__DM2 CYREG_PRT15_DM2
#define crustal__DR CYREG_PRT15_DR
#define crustal__INP_DIS CYREG_PRT15_INP_DIS
#define crustal__LCD_COM_SEG CYREG_PRT15_LCD_COM_SEG
#define crustal__LCD_EN CYREG_PRT15_LCD_EN
#define crustal__MASK 0x08u
#define crustal__PORT 15u
#define crustal__PRT CYREG_PRT15_PRT
#define crustal__PRTDSI__CAPS_SEL CYREG_PRT15_CAPS_SEL
#define crustal__PRTDSI__DBL_SYNC_IN CYREG_PRT15_DBL_SYNC_IN
#define crustal__PRTDSI__OE_SEL0 CYREG_PRT15_OE_SEL0
#define crustal__PRTDSI__OE_SEL1 CYREG_PRT15_OE_SEL1
#define crustal__PRTDSI__OUT_SEL0 CYREG_PRT15_OUT_SEL0
#define crustal__PRTDSI__OUT_SEL1 CYREG_PRT15_OUT_SEL1
#define crustal__PRTDSI__SYNC_OUT CYREG_PRT15_SYNC_OUT
#define crustal__PS CYREG_PRT15_PS
#define crustal__SHIFT 3
#define crustal__SLW CYREG_PRT15_SLW

/* Pin_14 */
#define Pin_14__0__MASK 0x10u
#define Pin_14__0__PC CYREG_PRT12_PC4
#define Pin_14__0__PORT 12u
#define Pin_14__0__SHIFT 4
#define Pin_14__AG CYREG_PRT12_AG
#define Pin_14__BIE CYREG_PRT12_BIE
#define Pin_14__BIT_MASK CYREG_PRT12_BIT_MASK
#define Pin_14__BYP CYREG_PRT12_BYP
#define Pin_14__DM0 CYREG_PRT12_DM0
#define Pin_14__DM1 CYREG_PRT12_DM1
#define Pin_14__DM2 CYREG_PRT12_DM2
#define Pin_14__DR CYREG_PRT12_DR
#define Pin_14__INP_DIS CYREG_PRT12_INP_DIS
#define Pin_14__MASK 0x10u
#define Pin_14__PORT 12u
#define Pin_14__PRT CYREG_PRT12_PRT
#define Pin_14__PRTDSI__DBL_SYNC_IN CYREG_PRT12_DBL_SYNC_IN
#define Pin_14__PRTDSI__OE_SEL0 CYREG_PRT12_OE_SEL0
#define Pin_14__PRTDSI__OE_SEL1 CYREG_PRT12_OE_SEL1
#define Pin_14__PRTDSI__OUT_SEL0 CYREG_PRT12_OUT_SEL0
#define Pin_14__PRTDSI__OUT_SEL1 CYREG_PRT12_OUT_SEL1
#define Pin_14__PRTDSI__SYNC_OUT CYREG_PRT12_SYNC_OUT
#define Pin_14__PS CYREG_PRT12_PS
#define Pin_14__SHIFT 4
#define Pin_14__SIO_CFG CYREG_PRT12_SIO_CFG
#define Pin_14__SIO_DIFF CYREG_PRT12_SIO_DIFF
#define Pin_14__SIO_HYST_EN CYREG_PRT12_SIO_HYST_EN
#define Pin_14__SIO_REG_HIFREQ CYREG_PRT12_SIO_REG_HIFREQ
#define Pin_14__SLW CYREG_PRT12_SLW

/* Pin_15 */
#define Pin_15__0__MASK 0x20u
#define Pin_15__0__PC CYREG_PRT12_PC5
#define Pin_15__0__PORT 12u
#define Pin_15__0__SHIFT 5
#define Pin_15__AG CYREG_PRT12_AG
#define Pin_15__BIE CYREG_PRT12_BIE
#define Pin_15__BIT_MASK CYREG_PRT12_BIT_MASK
#define Pin_15__BYP CYREG_PRT12_BYP
#define Pin_15__DM0 CYREG_PRT12_DM0
#define Pin_15__DM1 CYREG_PRT12_DM1
#define Pin_15__DM2 CYREG_PRT12_DM2
#define Pin_15__DR CYREG_PRT12_DR
#define Pin_15__INP_DIS CYREG_PRT12_INP_DIS
#define Pin_15__MASK 0x20u
#define Pin_15__PORT 12u
#define Pin_15__PRT CYREG_PRT12_PRT
#define Pin_15__PRTDSI__DBL_SYNC_IN CYREG_PRT12_DBL_SYNC_IN
#define Pin_15__PRTDSI__OE_SEL0 CYREG_PRT12_OE_SEL0
#define Pin_15__PRTDSI__OE_SEL1 CYREG_PRT12_OE_SEL1
#define Pin_15__PRTDSI__OUT_SEL0 CYREG_PRT12_OUT_SEL0
#define Pin_15__PRTDSI__OUT_SEL1 CYREG_PRT12_OUT_SEL1
#define Pin_15__PRTDSI__SYNC_OUT CYREG_PRT12_SYNC_OUT
#define Pin_15__PS CYREG_PRT12_PS
#define Pin_15__SHIFT 5
#define Pin_15__SIO_CFG CYREG_PRT12_SIO_CFG
#define Pin_15__SIO_DIFF CYREG_PRT12_SIO_DIFF
#define Pin_15__SIO_HYST_EN CYREG_PRT12_SIO_HYST_EN
#define Pin_15__SIO_REG_HIFREQ CYREG_PRT12_SIO_REG_HIFREQ
#define Pin_15__SLW CYREG_PRT12_SLW

/* inbt2 */
#define inbt2__0__MASK 0x80u
#define inbt2__0__PC CYREG_PRT1_PC7
#define inbt2__0__PORT 1u
#define inbt2__0__SHIFT 7
#define inbt2__AG CYREG_PRT1_AG
#define inbt2__AMUX CYREG_PRT1_AMUX
#define inbt2__BIE CYREG_PRT1_BIE
#define inbt2__BIT_MASK CYREG_PRT1_BIT_MASK
#define inbt2__BYP CYREG_PRT1_BYP
#define inbt2__CTL CYREG_PRT1_CTL
#define inbt2__DM0 CYREG_PRT1_DM0
#define inbt2__DM1 CYREG_PRT1_DM1
#define inbt2__DM2 CYREG_PRT1_DM2
#define inbt2__DR CYREG_PRT1_DR
#define inbt2__INP_DIS CYREG_PRT1_INP_DIS
#define inbt2__LCD_COM_SEG CYREG_PRT1_LCD_COM_SEG
#define inbt2__LCD_EN CYREG_PRT1_LCD_EN
#define inbt2__MASK 0x80u
#define inbt2__PORT 1u
#define inbt2__PRT CYREG_PRT1_PRT
#define inbt2__PRTDSI__CAPS_SEL CYREG_PRT1_CAPS_SEL
#define inbt2__PRTDSI__DBL_SYNC_IN CYREG_PRT1_DBL_SYNC_IN
#define inbt2__PRTDSI__OE_SEL0 CYREG_PRT1_OE_SEL0
#define inbt2__PRTDSI__OE_SEL1 CYREG_PRT1_OE_SEL1
#define inbt2__PRTDSI__OUT_SEL0 CYREG_PRT1_OUT_SEL0
#define inbt2__PRTDSI__OUT_SEL1 CYREG_PRT1_OUT_SEL1
#define inbt2__PRTDSI__SYNC_OUT CYREG_PRT1_SYNC_OUT
#define inbt2__PS CYREG_PRT1_PS
#define inbt2__SHIFT 7
#define inbt2__SLW CYREG_PRT1_SLW

/* isr_1 */
#define isr_1__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define isr_1__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define isr_1__INTC_MASK 0x20u
#define isr_1__INTC_NUMBER 5u
#define isr_1__INTC_PRIOR_NUM 7u
#define isr_1__INTC_PRIOR_REG CYREG_NVIC_PRI_5
#define isr_1__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define isr_1__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* Pin_1 */
#define Pin_1__0__MASK 0x20u
#define Pin_1__0__PC CYREG_PRT3_PC5
#define Pin_1__0__PORT 3u
#define Pin_1__0__SHIFT 5
#define Pin_1__AG CYREG_PRT3_AG
#define Pin_1__AMUX CYREG_PRT3_AMUX
#define Pin_1__BIE CYREG_PRT3_BIE
#define Pin_1__BIT_MASK CYREG_PRT3_BIT_MASK
#define Pin_1__BYP CYREG_PRT3_BYP
#define Pin_1__CTL CYREG_PRT3_CTL
#define Pin_1__DM0 CYREG_PRT3_DM0
#define Pin_1__DM1 CYREG_PRT3_DM1
#define Pin_1__DM2 CYREG_PRT3_DM2
#define Pin_1__DR CYREG_PRT3_DR
#define Pin_1__INP_DIS CYREG_PRT3_INP_DIS
#define Pin_1__LCD_COM_SEG CYREG_PRT3_LCD_COM_SEG
#define Pin_1__LCD_EN CYREG_PRT3_LCD_EN
#define Pin_1__MASK 0x20u
#define Pin_1__PORT 3u
#define Pin_1__PRT CYREG_PRT3_PRT
#define Pin_1__PRTDSI__CAPS_SEL CYREG_PRT3_CAPS_SEL
#define Pin_1__PRTDSI__DBL_SYNC_IN CYREG_PRT3_DBL_SYNC_IN
#define Pin_1__PRTDSI__OE_SEL0 CYREG_PRT3_OE_SEL0
#define Pin_1__PRTDSI__OE_SEL1 CYREG_PRT3_OE_SEL1
#define Pin_1__PRTDSI__OUT_SEL0 CYREG_PRT3_OUT_SEL0
#define Pin_1__PRTDSI__OUT_SEL1 CYREG_PRT3_OUT_SEL1
#define Pin_1__PRTDSI__SYNC_OUT CYREG_PRT3_SYNC_OUT
#define Pin_1__PS CYREG_PRT3_PS
#define Pin_1__SHIFT 5
#define Pin_1__SLW CYREG_PRT3_SLW

/* Pin_2 */
#define Pin_2__0__MASK 0x01u
#define Pin_2__0__PC CYREG_PRT2_PC0
#define Pin_2__0__PORT 2u
#define Pin_2__0__SHIFT 0
#define Pin_2__AG CYREG_PRT2_AG
#define Pin_2__AMUX CYREG_PRT2_AMUX
#define Pin_2__BIE CYREG_PRT2_BIE
#define Pin_2__BIT_MASK CYREG_PRT2_BIT_MASK
#define Pin_2__BYP CYREG_PRT2_BYP
#define Pin_2__CTL CYREG_PRT2_CTL
#define Pin_2__DM0 CYREG_PRT2_DM0
#define Pin_2__DM1 CYREG_PRT2_DM1
#define Pin_2__DM2 CYREG_PRT2_DM2
#define Pin_2__DR CYREG_PRT2_DR
#define Pin_2__INP_DIS CYREG_PRT2_INP_DIS
#define Pin_2__LCD_COM_SEG CYREG_PRT2_LCD_COM_SEG
#define Pin_2__LCD_EN CYREG_PRT2_LCD_EN
#define Pin_2__MASK 0x01u
#define Pin_2__PORT 2u
#define Pin_2__PRT CYREG_PRT2_PRT
#define Pin_2__PRTDSI__CAPS_SEL CYREG_PRT2_CAPS_SEL
#define Pin_2__PRTDSI__DBL_SYNC_IN CYREG_PRT2_DBL_SYNC_IN
#define Pin_2__PRTDSI__OE_SEL0 CYREG_PRT2_OE_SEL0
#define Pin_2__PRTDSI__OE_SEL1 CYREG_PRT2_OE_SEL1
#define Pin_2__PRTDSI__OUT_SEL0 CYREG_PRT2_OUT_SEL0
#define Pin_2__PRTDSI__OUT_SEL1 CYREG_PRT2_OUT_SEL1
#define Pin_2__PRTDSI__SYNC_OUT CYREG_PRT2_SYNC_OUT
#define Pin_2__PS CYREG_PRT2_PS
#define Pin_2__SHIFT 0
#define Pin_2__SLW CYREG_PRT2_SLW

/* Pin_3 */
#define Pin_3__0__MASK 0x02u
#define Pin_3__0__PC CYREG_PRT2_PC1
#define Pin_3__0__PORT 2u
#define Pin_3__0__SHIFT 1
#define Pin_3__AG CYREG_PRT2_AG
#define Pin_3__AMUX CYREG_PRT2_AMUX
#define Pin_3__BIE CYREG_PRT2_BIE
#define Pin_3__BIT_MASK CYREG_PRT2_BIT_MASK
#define Pin_3__BYP CYREG_PRT2_BYP
#define Pin_3__CTL CYREG_PRT2_CTL
#define Pin_3__DM0 CYREG_PRT2_DM0
#define Pin_3__DM1 CYREG_PRT2_DM1
#define Pin_3__DM2 CYREG_PRT2_DM2
#define Pin_3__DR CYREG_PRT2_DR
#define Pin_3__INP_DIS CYREG_PRT2_INP_DIS
#define Pin_3__LCD_COM_SEG CYREG_PRT2_LCD_COM_SEG
#define Pin_3__LCD_EN CYREG_PRT2_LCD_EN
#define Pin_3__MASK 0x02u
#define Pin_3__PORT 2u
#define Pin_3__PRT CYREG_PRT2_PRT
#define Pin_3__PRTDSI__CAPS_SEL CYREG_PRT2_CAPS_SEL
#define Pin_3__PRTDSI__DBL_SYNC_IN CYREG_PRT2_DBL_SYNC_IN
#define Pin_3__PRTDSI__OE_SEL0 CYREG_PRT2_OE_SEL0
#define Pin_3__PRTDSI__OE_SEL1 CYREG_PRT2_OE_SEL1
#define Pin_3__PRTDSI__OUT_SEL0 CYREG_PRT2_OUT_SEL0
#define Pin_3__PRTDSI__OUT_SEL1 CYREG_PRT2_OUT_SEL1
#define Pin_3__PRTDSI__SYNC_OUT CYREG_PRT2_SYNC_OUT
#define Pin_3__PS CYREG_PRT2_PS
#define Pin_3__SHIFT 1
#define Pin_3__SLW CYREG_PRT2_SLW

/* Pin_4 */
#define Pin_4__0__MASK 0x04u
#define Pin_4__0__PC CYREG_PRT2_PC2
#define Pin_4__0__PORT 2u
#define Pin_4__0__SHIFT 2
#define Pin_4__AG CYREG_PRT2_AG
#define Pin_4__AMUX CYREG_PRT2_AMUX
#define Pin_4__BIE CYREG_PRT2_BIE
#define Pin_4__BIT_MASK CYREG_PRT2_BIT_MASK
#define Pin_4__BYP CYREG_PRT2_BYP
#define Pin_4__CTL CYREG_PRT2_CTL
#define Pin_4__DM0 CYREG_PRT2_DM0
#define Pin_4__DM1 CYREG_PRT2_DM1
#define Pin_4__DM2 CYREG_PRT2_DM2
#define Pin_4__DR CYREG_PRT2_DR
#define Pin_4__INP_DIS CYREG_PRT2_INP_DIS
#define Pin_4__LCD_COM_SEG CYREG_PRT2_LCD_COM_SEG
#define Pin_4__LCD_EN CYREG_PRT2_LCD_EN
#define Pin_4__MASK 0x04u
#define Pin_4__PORT 2u
#define Pin_4__PRT CYREG_PRT2_PRT
#define Pin_4__PRTDSI__CAPS_SEL CYREG_PRT2_CAPS_SEL
#define Pin_4__PRTDSI__DBL_SYNC_IN CYREG_PRT2_DBL_SYNC_IN
#define Pin_4__PRTDSI__OE_SEL0 CYREG_PRT2_OE_SEL0
#define Pin_4__PRTDSI__OE_SEL1 CYREG_PRT2_OE_SEL1
#define Pin_4__PRTDSI__OUT_SEL0 CYREG_PRT2_OUT_SEL0
#define Pin_4__PRTDSI__OUT_SEL1 CYREG_PRT2_OUT_SEL1
#define Pin_4__PRTDSI__SYNC_OUT CYREG_PRT2_SYNC_OUT
#define Pin_4__PS CYREG_PRT2_PS
#define Pin_4__SHIFT 2
#define Pin_4__SLW CYREG_PRT2_SLW

/* Pin_5 */
#define Pin_5__0__MASK 0x08u
#define Pin_5__0__PC CYREG_PRT2_PC3
#define Pin_5__0__PORT 2u
#define Pin_5__0__SHIFT 3
#define Pin_5__AG CYREG_PRT2_AG
#define Pin_5__AMUX CYREG_PRT2_AMUX
#define Pin_5__BIE CYREG_PRT2_BIE
#define Pin_5__BIT_MASK CYREG_PRT2_BIT_MASK
#define Pin_5__BYP CYREG_PRT2_BYP
#define Pin_5__CTL CYREG_PRT2_CTL
#define Pin_5__DM0 CYREG_PRT2_DM0
#define Pin_5__DM1 CYREG_PRT2_DM1
#define Pin_5__DM2 CYREG_PRT2_DM2
#define Pin_5__DR CYREG_PRT2_DR
#define Pin_5__INP_DIS CYREG_PRT2_INP_DIS
#define Pin_5__LCD_COM_SEG CYREG_PRT2_LCD_COM_SEG
#define Pin_5__LCD_EN CYREG_PRT2_LCD_EN
#define Pin_5__MASK 0x08u
#define Pin_5__PORT 2u
#define Pin_5__PRT CYREG_PRT2_PRT
#define Pin_5__PRTDSI__CAPS_SEL CYREG_PRT2_CAPS_SEL
#define Pin_5__PRTDSI__DBL_SYNC_IN CYREG_PRT2_DBL_SYNC_IN
#define Pin_5__PRTDSI__OE_SEL0 CYREG_PRT2_OE_SEL0
#define Pin_5__PRTDSI__OE_SEL1 CYREG_PRT2_OE_SEL1
#define Pin_5__PRTDSI__OUT_SEL0 CYREG_PRT2_OUT_SEL0
#define Pin_5__PRTDSI__OUT_SEL1 CYREG_PRT2_OUT_SEL1
#define Pin_5__PRTDSI__SYNC_OUT CYREG_PRT2_SYNC_OUT
#define Pin_5__PS CYREG_PRT2_PS
#define Pin_5__SHIFT 3
#define Pin_5__SLW CYREG_PRT2_SLW

/* Pin_6 */
#define Pin_6__0__MASK 0x10u
#define Pin_6__0__PC CYREG_PRT2_PC4
#define Pin_6__0__PORT 2u
#define Pin_6__0__SHIFT 4
#define Pin_6__AG CYREG_PRT2_AG
#define Pin_6__AMUX CYREG_PRT2_AMUX
#define Pin_6__BIE CYREG_PRT2_BIE
#define Pin_6__BIT_MASK CYREG_PRT2_BIT_MASK
#define Pin_6__BYP CYREG_PRT2_BYP
#define Pin_6__CTL CYREG_PRT2_CTL
#define Pin_6__DM0 CYREG_PRT2_DM0
#define Pin_6__DM1 CYREG_PRT2_DM1
#define Pin_6__DM2 CYREG_PRT2_DM2
#define Pin_6__DR CYREG_PRT2_DR
#define Pin_6__INP_DIS CYREG_PRT2_INP_DIS
#define Pin_6__LCD_COM_SEG CYREG_PRT2_LCD_COM_SEG
#define Pin_6__LCD_EN CYREG_PRT2_LCD_EN
#define Pin_6__MASK 0x10u
#define Pin_6__PORT 2u
#define Pin_6__PRT CYREG_PRT2_PRT
#define Pin_6__PRTDSI__CAPS_SEL CYREG_PRT2_CAPS_SEL
#define Pin_6__PRTDSI__DBL_SYNC_IN CYREG_PRT2_DBL_SYNC_IN
#define Pin_6__PRTDSI__OE_SEL0 CYREG_PRT2_OE_SEL0
#define Pin_6__PRTDSI__OE_SEL1 CYREG_PRT2_OE_SEL1
#define Pin_6__PRTDSI__OUT_SEL0 CYREG_PRT2_OUT_SEL0
#define Pin_6__PRTDSI__OUT_SEL1 CYREG_PRT2_OUT_SEL1
#define Pin_6__PRTDSI__SYNC_OUT CYREG_PRT2_SYNC_OUT
#define Pin_6__PS CYREG_PRT2_PS
#define Pin_6__SHIFT 4
#define Pin_6__SLW CYREG_PRT2_SLW

/* Pin_7 */
#define Pin_7__0__MASK 0x40u
#define Pin_7__0__PC CYREG_PRT2_PC6
#define Pin_7__0__PORT 2u
#define Pin_7__0__SHIFT 6
#define Pin_7__AG CYREG_PRT2_AG
#define Pin_7__AMUX CYREG_PRT2_AMUX
#define Pin_7__BIE CYREG_PRT2_BIE
#define Pin_7__BIT_MASK CYREG_PRT2_BIT_MASK
#define Pin_7__BYP CYREG_PRT2_BYP
#define Pin_7__CTL CYREG_PRT2_CTL
#define Pin_7__DM0 CYREG_PRT2_DM0
#define Pin_7__DM1 CYREG_PRT2_DM1
#define Pin_7__DM2 CYREG_PRT2_DM2
#define Pin_7__DR CYREG_PRT2_DR
#define Pin_7__INP_DIS CYREG_PRT2_INP_DIS
#define Pin_7__LCD_COM_SEG CYREG_PRT2_LCD_COM_SEG
#define Pin_7__LCD_EN CYREG_PRT2_LCD_EN
#define Pin_7__MASK 0x40u
#define Pin_7__PORT 2u
#define Pin_7__PRT CYREG_PRT2_PRT
#define Pin_7__PRTDSI__CAPS_SEL CYREG_PRT2_CAPS_SEL
#define Pin_7__PRTDSI__DBL_SYNC_IN CYREG_PRT2_DBL_SYNC_IN
#define Pin_7__PRTDSI__OE_SEL0 CYREG_PRT2_OE_SEL0
#define Pin_7__PRTDSI__OE_SEL1 CYREG_PRT2_OE_SEL1
#define Pin_7__PRTDSI__OUT_SEL0 CYREG_PRT2_OUT_SEL0
#define Pin_7__PRTDSI__OUT_SEL1 CYREG_PRT2_OUT_SEL1
#define Pin_7__PRTDSI__SYNC_OUT CYREG_PRT2_SYNC_OUT
#define Pin_7__PS CYREG_PRT2_PS
#define Pin_7__SHIFT 6
#define Pin_7__SLW CYREG_PRT2_SLW

/* Pin_8 */
#define Pin_8__0__MASK 0x20u
#define Pin_8__0__PC CYREG_PRT2_PC5
#define Pin_8__0__PORT 2u
#define Pin_8__0__SHIFT 5
#define Pin_8__AG CYREG_PRT2_AG
#define Pin_8__AMUX CYREG_PRT2_AMUX
#define Pin_8__BIE CYREG_PRT2_BIE
#define Pin_8__BIT_MASK CYREG_PRT2_BIT_MASK
#define Pin_8__BYP CYREG_PRT2_BYP
#define Pin_8__CTL CYREG_PRT2_CTL
#define Pin_8__DM0 CYREG_PRT2_DM0
#define Pin_8__DM1 CYREG_PRT2_DM1
#define Pin_8__DM2 CYREG_PRT2_DM2
#define Pin_8__DR CYREG_PRT2_DR
#define Pin_8__INP_DIS CYREG_PRT2_INP_DIS
#define Pin_8__LCD_COM_SEG CYREG_PRT2_LCD_COM_SEG
#define Pin_8__LCD_EN CYREG_PRT2_LCD_EN
#define Pin_8__MASK 0x20u
#define Pin_8__PORT 2u
#define Pin_8__PRT CYREG_PRT2_PRT
#define Pin_8__PRTDSI__CAPS_SEL CYREG_PRT2_CAPS_SEL
#define Pin_8__PRTDSI__DBL_SYNC_IN CYREG_PRT2_DBL_SYNC_IN
#define Pin_8__PRTDSI__OE_SEL0 CYREG_PRT2_OE_SEL0
#define Pin_8__PRTDSI__OE_SEL1 CYREG_PRT2_OE_SEL1
#define Pin_8__PRTDSI__OUT_SEL0 CYREG_PRT2_OUT_SEL0
#define Pin_8__PRTDSI__OUT_SEL1 CYREG_PRT2_OUT_SEL1
#define Pin_8__PRTDSI__SYNC_OUT CYREG_PRT2_SYNC_OUT
#define Pin_8__PS CYREG_PRT2_PS
#define Pin_8__SHIFT 5
#define Pin_8__SLW CYREG_PRT2_SLW

/* Pin_9 */
#define Pin_9__0__MASK 0x80u
#define Pin_9__0__PC CYREG_PRT2_PC7
#define Pin_9__0__PORT 2u
#define Pin_9__0__SHIFT 7
#define Pin_9__AG CYREG_PRT2_AG
#define Pin_9__AMUX CYREG_PRT2_AMUX
#define Pin_9__BIE CYREG_PRT2_BIE
#define Pin_9__BIT_MASK CYREG_PRT2_BIT_MASK
#define Pin_9__BYP CYREG_PRT2_BYP
#define Pin_9__CTL CYREG_PRT2_CTL
#define Pin_9__DM0 CYREG_PRT2_DM0
#define Pin_9__DM1 CYREG_PRT2_DM1
#define Pin_9__DM2 CYREG_PRT2_DM2
#define Pin_9__DR CYREG_PRT2_DR
#define Pin_9__INP_DIS CYREG_PRT2_INP_DIS
#define Pin_9__LCD_COM_SEG CYREG_PRT2_LCD_COM_SEG
#define Pin_9__LCD_EN CYREG_PRT2_LCD_EN
#define Pin_9__MASK 0x80u
#define Pin_9__PORT 2u
#define Pin_9__PRT CYREG_PRT2_PRT
#define Pin_9__PRTDSI__CAPS_SEL CYREG_PRT2_CAPS_SEL
#define Pin_9__PRTDSI__DBL_SYNC_IN CYREG_PRT2_DBL_SYNC_IN
#define Pin_9__PRTDSI__OE_SEL0 CYREG_PRT2_OE_SEL0
#define Pin_9__PRTDSI__OE_SEL1 CYREG_PRT2_OE_SEL1
#define Pin_9__PRTDSI__OUT_SEL0 CYREG_PRT2_OUT_SEL0
#define Pin_9__PRTDSI__OUT_SEL1 CYREG_PRT2_OUT_SEL1
#define Pin_9__PRTDSI__SYNC_OUT CYREG_PRT2_SYNC_OUT
#define Pin_9__PS CYREG_PRT2_PS
#define Pin_9__SHIFT 7
#define Pin_9__SLW CYREG_PRT2_SLW

/* int1 */
#define int1__0__MASK 0x40u
#define int1__0__PC CYREG_PRT1_PC6
#define int1__0__PORT 1u
#define int1__0__SHIFT 6
#define int1__AG CYREG_PRT1_AG
#define int1__AMUX CYREG_PRT1_AMUX
#define int1__BIE CYREG_PRT1_BIE
#define int1__BIT_MASK CYREG_PRT1_BIT_MASK
#define int1__BYP CYREG_PRT1_BYP
#define int1__CTL CYREG_PRT1_CTL
#define int1__DM0 CYREG_PRT1_DM0
#define int1__DM1 CYREG_PRT1_DM1
#define int1__DM2 CYREG_PRT1_DM2
#define int1__DR CYREG_PRT1_DR
#define int1__INP_DIS CYREG_PRT1_INP_DIS
#define int1__INTSTAT CYREG_PICU1_INTSTAT
#define int1__LCD_COM_SEG CYREG_PRT1_LCD_COM_SEG
#define int1__LCD_EN CYREG_PRT1_LCD_EN
#define int1__MASK 0x40u
#define int1__PORT 1u
#define int1__PRT CYREG_PRT1_PRT
#define int1__PRTDSI__CAPS_SEL CYREG_PRT1_CAPS_SEL
#define int1__PRTDSI__DBL_SYNC_IN CYREG_PRT1_DBL_SYNC_IN
#define int1__PRTDSI__OE_SEL0 CYREG_PRT1_OE_SEL0
#define int1__PRTDSI__OE_SEL1 CYREG_PRT1_OE_SEL1
#define int1__PRTDSI__OUT_SEL0 CYREG_PRT1_OUT_SEL0
#define int1__PRTDSI__OUT_SEL1 CYREG_PRT1_OUT_SEL1
#define int1__PRTDSI__SYNC_OUT CYREG_PRT1_SYNC_OUT
#define int1__PS CYREG_PRT1_PS
#define int1__SHIFT 6
#define int1__SLW CYREG_PRT1_SLW
#define int1__SNAP CYREG_PICU1_SNAP

/* Miscellaneous */
/* -- WARNING: define names containing LEOPARD or PANTHER are deprecated and will be removed in a future release */
#define CYDEV_DEBUGGING_DPS_SWD_SWV 6
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIG_FASTBOOT_ENABLED 0
#define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_MEMBER_5A 3u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_DIE_PANTHER 3u
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_DIE_PANTHER
#define BCLK__BUS_CLK__HZ 24000000U
#define BCLK__BUS_CLK__KHZ 24000U
#define BCLK__BUS_CLK__MHZ 24U
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_PSOC4A 2u
#define CYDEV_CHIP_DIE_PSOC5LP 4u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC5
#define CYDEV_CHIP_JTAG_ID 0x0E13C069u
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_MEMBER_4A 2u
#define CYDEV_CHIP_MEMBER_5B 4u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_5A
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_4A_ES0 17u
#define CYDEV_CHIP_REVISION_4A_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_5A_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REV_PANTHER_PRODUCTION
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REV_PANTHER_ES0 0u
#define CYDEV_CHIP_REV_PANTHER_ES1 1u
#define CYDEV_CHIP_REV_PSOC4A_ES0 17u
#define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_DMA 0
#define CYDEV_CONFIGURATION_ECC 1
#define CYDEV_CONFIGURATION_IMOENABLED CYDEV_CONFIG_FASTBOOT_ENABLED
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowButWarn
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_DATA_CACHE_ENABLED 0
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_SWD_SWV
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_DEBUGGING_REQXRES 1
#define CYDEV_DEBUGGING_XRES 0
#define CYDEV_DEBUG_ENABLE_MASK 0x01u
#define CYDEV_DEBUG_ENABLE_REGISTER CYREG_MLOGIC_DBG_DBE
#define CYDEV_DMA_CHANNELS_AVAILABLE 24u
#define CYDEV_ECC_ENABLE 0
#define CYDEV_HEAP_SIZE 0x1000
#define CYDEV_INSTRUCT_CACHE_ENABLED 1
#define CYDEV_INTR_RISING 0x00000001u
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_PROTECTION_ENABLE 0
#define CYDEV_STACK_SIZE 0x4000
#define CYDEV_USE_BUNDLED_CMSIS 1
#define CYDEV_VDDA 5
#define CYDEV_VDDA_MV 5000
#define CYDEV_VDDD 3.3
#define CYDEV_VDDD_MV 3300
#define CYDEV_VDDIO0 5.0
#define CYDEV_VDDIO0_MV 5000
#define CYDEV_VDDIO1 3.3
#define CYDEV_VDDIO1_MV 3300
#define CYDEV_VDDIO2 3.3
#define CYDEV_VDDIO2_MV 3300
#define CYDEV_VDDIO3 5.0
#define CYDEV_VDDIO3_MV 5000
#define CYDEV_VIO0 5
#define CYDEV_VIO0_MV 5000
#define CYDEV_VIO1 3.3
#define CYDEV_VIO1_MV 3300
#define CYDEV_VIO2 3.3
#define CYDEV_VIO2_MV 3300
#define CYDEV_VIO3 5
#define CYDEV_VIO3_MV 5000
#define DMA_CHANNELS_USED__MASK0 0x00000000u
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
