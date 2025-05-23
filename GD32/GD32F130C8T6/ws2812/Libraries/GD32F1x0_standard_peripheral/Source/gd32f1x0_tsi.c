/*!
    \file    gd32f1x0_tsi.c
    \brief   TSI driver

    \version 2025-01-01, V3.7.0, firmware update for GD32F1x0(x=3,5)
*/

/*
    Copyright (c) 2025, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/
#include "gd32f1x0_tsi.h"

/*!
    \brief      reset TSI peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tsi_deinit(void)
{
    rcu_periph_reset_enable(RCU_TSIRST);
    rcu_periph_reset_disable(RCU_TSIRST);
}

/*!
    \brief      initialize TSI pulse prescaler,charge pulse,transfer pulse,max cycle number
    \param[in]  prescaler: CTCLK clock division factor
                only one parameter can be selected which is shown as below:
      \arg        TSI_CTCDIV_DIV1:   fCTCLK = fHCLK
      \arg        TSI_CTCDIV_DIV2:   fCTCLK = fHCLK/2
      \arg        TSI_CTCDIV_DIV4:   fCTCLK = fHCLK/4
      \arg        TSI_CTCDIV_DIV8:   fCTCLK = fHCLK/8
      \arg        TSI_CTCDIV_DIV16:  fCTCLK = fHCLK/16
      \arg        TSI_CTCDIV_DIV32:  fCTCLK = fHCLK/32
      \arg        TSI_CTCDIV_DIV64:  fCTCLK = fHCLK/64
      \arg        TSI_CTCDIV_DIV128: fCTCLK = fHCLK/128
    \param[in]  charge_duration: charge state duration time
                only one parameter can be selected which is shown as below:
      \arg        TSI_CHARGE_xCTCLK(x=1..16): the duration time of charge state is x CTCLK
    \param[in]  transfer_duration: charge transfer state duration time
                only one parameter can be selected which is shown as below:
      \arg        TSI_TRANSFER_xCTCLK(x=1..16): the duration time of transfer state is x CTCLK
    \param[in]  max_number: max cycle number
                only one parameter can be selected which is shown as below:
      \arg        TSI_MAXNUM255:   the max cycle number of a sequence is 255
      \arg        TSI_MAXNUM511:   the max cycle number of a sequence is 511
      \arg        TSI_MAXNUM1023:  the max cycle number of a sequence is 1023
      \arg        TSI_MAXNUM2047:  the max cycle number of a sequence is 2047
      \arg        TSI_MAXNUM4095:  the max cycle number of a sequence is 4095
      \arg        TSI_MAXNUM8191:  the max cycle number of a sequence is 8191
      \arg        TSI_MAXNUM16383: the max cycle number of a sequence is 16383
    \param[out] none
    \retval     none
*/
void tsi_init(uint32_t prescaler, uint32_t charge_duration, uint32_t transfer_duration, uint32_t max_number)
{
    if(RESET == (TSI_CTL & TSI_CTL_TSIS)) {
        uint32_t ctl;
        ctl = TSI_CTL;
        /*configure TSI clock division factor,charge state duration time,charge transfer state duration time */
        ctl &= ~(TSI_CTL_CTCDIV | TSI_CTL_CTDT | TSI_CTL_CDT | TSI_CTL_MCN);
        ctl |= (prescaler | charge_duration | transfer_duration | max_number);
        TSI_CTL = ctl;
    }
}

/*!
    \brief      enable TSI module
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tsi_enable(void)
{
    TSI_CTL |= TSI_CTL_TSIEN;
}

/*!
    \brief      disable TSI module
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tsi_disable(void)
{
    TSI_CTL &= ~TSI_CTL_TSIEN;
}

/*!
    \brief      enable sample pin
    \param[in]  sample: sample pin
                one or more parameters can be selected which are shown as below:
      \arg        TSI_SAMPCFG_GxPy(x=0..5,y=0..3):pin y of group x is sample pin
    \param[out] none
    \retval     none
*/
void tsi_sample_pin_enable(uint32_t sample)
{
    if(RESET == (TSI_CTL & TSI_CTL_TSIS)) {
        TSI_SAMPCFG |= sample;
    }
}

/*!
    \brief      disable sample pin
    \param[in]  sample: sample pin
                one or more parameters can be selected which are shown as below:
      \arg        TSI_SAMPCFG_GxPy(x=0..5,y=0..3): pin y of group x is sample pin
    \param[out] none
    \retval     none
*/
void tsi_sample_pin_disable(uint32_t sample)
{
    if(RESET == (TSI_CTL & TSI_CTL_TSIS)) {
        TSI_SAMPCFG &=  ~sample;
    }
}

/*!
    \brief      enable channel pin
    \param[in]  channel: channel pin
                one or more parameters can be selected which are shown as below:
      \arg        TSI_CHCFG_GxPy(x=0..5,y=0..3): pin y of group x
    \param[out] none
    \retval     none
*/
void tsi_channel_pin_enable(uint32_t channel)
{
    TSI_CHCFG |= channel;
}

/*!
    \brief      disable channel pin
    \param[in]  channel: channel pin
                one or more parameters can be selected which are shown as below:
      \arg        TSI_CHCFG_GxPy(x=0..5,y=0..3): pin y of group x
    \param[out] none
    \retval     none
*/
void tsi_channel_pin_disable(uint32_t channel)
{
    TSI_CHCFG &= ~channel;
}

/*!
    \brief      configure TSI triggering by software
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tsi_software_mode_config(void)
{
    if(RESET == (TSI_CTL & TSI_CTL_TSIS)) {
        TSI_CTL &= ~TSI_CTL_TRGMOD;
    }
}

/*!
    \brief      start a charge-transfer sequence when TSI is in software trigger mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tsi_software_start(void)
{
    TSI_CTL |= TSI_CTL_TSIS;
}

/*!
    \brief      stop a charge-transfer sequence when TSI is in software trigger mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tsi_software_stop(void)
{
    TSI_CTL &= ~TSI_CTL_TSIS;
}

/*!
    \brief      configure TSI triggering by hardware
    \param[in]  trigger_edge: the edge type in hardware trigger mode
                only one parameter can be selected which is shown as below:
      \arg        TSI_FALLING_TRIGGER: falling edge trigger TSI charge transfer sequence
      \arg        TSI_RISING_TRIGGER:  rising edge trigger TSI charge transfer sequence
    \param[out] none
    \retval     none
*/
void tsi_hardware_mode_config(uint8_t trigger_edge)
{
    if(RESET == (TSI_CTL & TSI_CTL_TSIS)) {
        /*enable hardware mode*/
        TSI_CTL |= TSI_CTL_TRGMOD;
        /*configure the edge type in hardware trigger mode*/
        if(TSI_FALLING_TRIGGER == (uint32_t)trigger_edge) {
            TSI_CTL &= ~TSI_CTL_EGSEL;
        } else {
            TSI_CTL |= TSI_CTL_EGSEL;
        }
    }
}

/*!
    \brief      configure TSI pin mode when charge-transfer sequence is IDLE
    \param[in]  pin_mode: pin mode when charge-transfer sequence is IDLE
                only one parameter can be selected which is shown as below:
      \arg        TSI_OUTPUT_LOW:     TSI pin will output low when IDLE
      \arg        TSI_INPUT_FLOATING: TSI pin will keep input_floating when IDLE
    \param[out] none
    \retval     none
*/
void tsi_pin_mode_config(uint8_t pin_mode)
{
    if(RESET == (TSI_CTL & TSI_CTL_TSIS)) {
        if(TSI_OUTPUT_LOW == pin_mode) {
            TSI_CTL &= ~TSI_CTL_PINMOD;
        } else {
            TSI_CTL |= TSI_CTL_PINMOD;
        }
    }
}

/*!
    \brief      configure extend charge state
    \param[in]  extend: enable or disable extend charge state
                only one parameter can be selected which is shown as below:
      \arg        ENABLE:  enable extend charge state
      \arg        DISABLE: disable extend charge state
    \param[in]  prescaler: ECCLK clock division factor
                only one parameter can be selected which is shown as below:
      \arg        TSI_EXTEND_DIV1: fECCLK = fHCLK
      \arg        TSI_EXTEND_DIV2: fECCLK = fHCLK/2
    \param[in]  max_duration: value range 1...128,extend charge state maximum duration time is 1*tECCLK~128*tECCLK
    \param[out] none
    \retval     none
*/
void tsi_extend_charge_config(ControlStatus extend, uint8_t prescaler, uint32_t max_duration)
{
    if(RESET == (TSI_CTL & TSI_CTL_TSIS)) {
        uint32_t ctl;
        if(DISABLE == extend) {
            /*disable extend charge state*/
            TSI_CTL &= ~TSI_CTL_ECEN;
        } else {
            /*configure extend charge state maximum duration time*/
            ctl = TSI_CTL;
            ctl &= ~TSI_CTL_ECDT;
            ctl |= TSI_EXTENDMAX((uint32_t)(max_duration - 1U));
            TSI_CTL = ctl;
            /*configure ECCLK clock division factor*/
            if(TSI_EXTEND_DIV1 == prescaler) {
                TSI_CTL &= ~TSI_CTL_ECDIV;
            } else {
                TSI_CTL |= TSI_CTL_ECDIV;
            }
            /*enable extend charge state*/
            TSI_CTL |= TSI_CTL_ECEN;
        }
    }
}

/*!
    \brief      configure charge pulse and transfer pulse
    \param[in]  prescaler: CTCLK clock division factor
                only one parameter can be selected which is shown as below:
      \arg        TSI_CTCDIV_DIV1:   fCTCLK = fHCLK
      \arg        TSI_CTCDIV_DIV2:   fCTCLK = fHCLK/2
      \arg        TSI_CTCDIV_DIV4:   fCTCLK = fHCLK/4
      \arg        TSI_CTCDIV_DIV8:   fCTCLK = fHCLK/6
      \arg        TSI_CTCDIV_DIV16:  fCTCLK = fHCLK/8
      \arg        TSI_CTCDIV_DIV32:  fCTCLK = fHCLK/32
      \arg        TSI_CTCDIV_DIV64:  fCTCLK = fHCLK/64
      \arg        TSI_CTCDIV_DIV128: fCTCLK = fHCLK/128
    \param[in]  charge_duration: charge state duration time
                only one parameter can be selected which is shown as below:
      \arg        TSI_CHARGE_xCTCLK(x=1..16): the duration time of charge state is x CTCLK
    \param[in]  transfer_duration: charge transfer state duration time
                only one parameter can be selected which is shown as below:
      \arg        TSI_TRANSFER_xCTCLK(x=1..16): the duration time of transfer state is x CTCLK
    \param[out] none
    \retval     none
*/
void tsi_pulse_config(uint32_t prescaler, uint32_t charge_duration, uint32_t transfer_duration)
{
    if(RESET == (TSI_CTL & TSI_CTL_TSIS)) {
        uint32_t ctl;
        ctl = TSI_CTL;
        /*configure TSI clock division factor,charge state duration time,charge transfer state duration time */
        ctl &= ~(TSI_CTL_CTCDIV | TSI_CTL_CTDT | TSI_CTL_CDT);
        ctl |= (prescaler | charge_duration | transfer_duration);
        TSI_CTL = ctl;
    }
}

/*!
    \brief      configure the max cycle number of a charge-transfer sequence
    \param[in]  max_number: max cycle number
                only one parameter can be selected which is shown as below:
      \arg        TSI_MAXNUM255:   the max cycle number of a sequence is 255
      \arg        TSI_MAXNUM511:   the max cycle number of a sequence is 511
      \arg        TSI_MAXNUM1023:  the max cycle number of a sequence is 1023
      \arg        TSI_MAXNUM2047:  the max cycle number of a sequence is 2047
      \arg        TSI_MAXNUM4095:  the max cycle number of a sequence is 4095
      \arg        TSI_MAXNUM8191:  the max cycle number of a sequence is 8191
      \arg        TSI_MAXNUM16383: the max cycle number of a sequence is 16383
    \param[out] none
    \retval     none
*/
void tsi_max_number_config(uint32_t max_number)
{
    if(RESET == (TSI_CTL & TSI_CTL_TSIS)) {
        uint32_t maxnum;
        maxnum = TSI_CTL;
        /*configure the max cycle number of a charge-transfer sequence*/
        maxnum &= ~TSI_CTL_MCN;
        maxnum |= max_number;
        TSI_CTL = maxnum;
    }
}

/*!
    \brief      switch on hysteresis pin
    \param[in]  group_pin: select pin which will be switched on hysteresis
                one or more parameters can be selected which are shown as below:
      \arg        TSI_PHM_GxPy(x=0..5,y=0..3): pin y of group x switch on hysteresis
    \param[out] none
    \retval     none
*/
void tsi_hysteresis_on(uint32_t group_pin)
{
    TSI_PHM |= group_pin;
}

/*!
    \brief      switch off hysteresis pin
    \param[in]  group_pin: select pin which will be switched off hysteresis
                one or more parameters can be selected which are shown as below:
      \arg        TSI_PHM_GxPy(x=0..5,y=0..3): pin y of group x switch off hysteresis
    \param[out] none
    \retval     none
*/
void tsi_hysteresis_off(uint32_t group_pin)
{
    TSI_PHM &= ~group_pin;
}

/*!
    \brief      switch on analog pin
    \param[in]  group_pin: select pin which will be switched on analog
                one or more parameters can be selected which are shown as below:
      \arg        TSI_ASW_GxPy(x=0..5,y=0..3):pin y of group x switch on analog
    \param[out] none
    \retval     none
*/
void tsi_analog_on(uint32_t group_pin)
{
    TSI_ASW |= group_pin;
}

/*!
    \brief      switch off analog pin
    \param[in]  group_pin: select pin which will be switched off analog
                one or more parameters can be selected which are shown as below:
      \arg        TSI_ASW_GxPy(x=0..5,y=0..3):pin y of group x switch off analog
    \param[out] none
    \retval     none
*/
void tsi_analog_off(uint32_t group_pin)
{
    TSI_ASW &= ~group_pin;
}

/*!
    \brief      enbale group
    \param[in]  group: select group to be enabled
                one or more parameters can be selected which are shown as below:
      \arg        TSI_GCTL_GEx(x=0..5): the x group will be enabled
    \param[out] none
    \retval     none
*/
void tsi_group_enable(uint32_t group)
{
    TSI_GCTL |= group;
}

/*!
    \brief      disbale group
    \param[in]  group: select group to be disabled
                one or more parameters can be selected which are shown as below:
      \arg        TSI_GCTL_GEx(x=0..5):the x group will be disabled
    \param[out] none
    \retval     none
*/
void tsi_group_disable(uint32_t group)
{
    TSI_GCTL &= ~group;
}

/*!
    \brief      get group complete status
    \param[in]  group: select group
                only one parameter can be selected which is shown as below:
      \arg        TSI_GCTL_GCx(x=0..5): get the complete status of group x
    \param[out] none
    \retval     FlagStatus: group complete status,SET or RESET
*/
FlagStatus tsi_group_status_get(uint32_t group)
{
    if(TSI_GCTL & group) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      get the cycle number for group0 as soon as a charge-transfer sequence completes
    \param[in]  none
    \param[out] none
    \retval     group0 cycle number
*/
uint16_t tsi_group0_cycle_get(void)
{
    return (uint16_t)TSI_G0CYCN;
}

/*!
    \brief      get the cycle number for group1 as soon as a charge-transfer sequence completes
    \param[in]  none
    \param[out] none
    \retval     group1 cycle number
*/
uint16_t tsi_group1_cycle_get(void)
{
    return (uint16_t)TSI_G1CYCN;
}

/*!
    \brief      get the cycle number for group2 as soon as a charge-transfer sequence completes
    \param[in]  none
    \param[out] none
    \retval     group2 cycle number
*/
uint16_t tsi_group2_cycle_get(void)
{
    return (uint16_t)TSI_G2CYCN;
}

/*!
    \brief      get the cycle number for group3 as soon as a charge-transfer sequence completes
    \param[in]  none
    \param[out] none
    \retval     group3 cycle number
*/
uint16_t tsi_group3_cycle_get(void)
{
    return (uint16_t)TSI_G3CYCN;
}

/*!
    \brief      get the cycle number for group4 as soon as a charge-transfer sequence completes
    \param[in]  none
    \param[out] none
    \retval     group4 cycle number
*/
uint16_t tsi_group4_cycle_get(void)
{
    return (uint16_t)TSI_G4CYCN;
}

/*!
    \brief      get the cycle number for group5 as soon as a charge-transfer sequence completes
    \param[in]  none
    \param[out] none
    \retval     group5 cycle number
*/
uint16_t tsi_group5_cycle_get(void)
{
    return (uint16_t)TSI_G5CYCN;
}

/*!
    \brief      get TSI flag
    \param[in]  flag:
                only one parameter can be selected which is shown as below:
      \arg        TSI_FLAG_CTCF: charge-transfer complete flag
      \arg        TSI_FLAG_MNERR:  max Cycle Number Error flag
    \param[out] none
    \retval     FlagStatus:SET or RESET
*/
FlagStatus tsi_flag_get(uint32_t flag)
{
    if(TSI_INTF & flag) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear TSI flag
    \param[in]  source: select flag which will be cleared
                only one parameter can be selected which is shown as below:
      \arg        TSI_FLAG_CTCF: clear charge-transfer complete flag
      \arg        TSI_FLAG_MNERR: clear max cycle number error flag
    \param[out] none
    \retval     none
*/
void tsi_flag_clear(uint32_t flag)
{
    TSI_INTC |= flag;
}

/*!
    \brief      enable TSI interrupt
    \param[in]  source: select interrupt which will be enabled
                only one parameter can be selected which is shown as below:
      \arg        TSI_INT_CTCF: charge-transfer complete flag interrupt enable
      \arg        TSI_INTEN_MNERR:  max cycle number error interrupt enable
    \param[out] none
    \retval     none
*/
void tsi_interrupt_enable(uint32_t source)
{
    TSI_INTEN |= source;
}

/*!
    \brief      disable TSI interrupt
    \param[in]  source: select interrupt which will be disabled
                only one parameter can be selected which is shown as below:
      \arg        TSI_INT_CTCF: charge-transfer complete flag interrupt disable
      \arg        TSI_INTEN_MNERR: max cycle number error interrupt disable
    \param[out] none
    \retval     none
*/
void tsi_interrupt_disable(uint32_t source)
{
    TSI_INTEN &= ~source;
}

/*!
    \brief      get TSI interrupt flag
    \param[in]  flag:
                only one parameter can be selected which is shown as below:
      \arg        TSI_INT_FLAG_CTCF: clear charge-transfer complete interrupt flag
      \arg        TSI_INT_FLAG_MNERR: clear max cycle number error interrupt flag
    \param[out] none
    \retval     FlagStatus:SET or RESET
*/
FlagStatus tsi_interrupt_flag_get(uint32_t flag)
{
    uint32_t interrupt_enable = 0U, interrupt_flag = 0U;
    interrupt_flag = (TSI_INTF & flag);
    interrupt_enable = (TSI_INTEN & flag);
    if(interrupt_flag && interrupt_enable) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear TSI interrupt flag
    \param[in]  flag: select flag which will be cleared
                only one parameter can be selected which is shown as below:
      \arg        TSI_INT_FLAG_CTCF: clear charge-transfer complete interrupt flag
      \arg        TSI_INT_FLAG_MNERR: clear max cycle number error interrupt flag
    \param[out] none
    \retval     none
*/
void tsi_interrupt_flag_clear(uint32_t flag)
{
    TSI_INTC |= flag;
}
