/**
 * \file controller_feature.c
 * Description : This file includes API implementation for feature specific to Deep-sleep and and IR
 * for BT controller modules.
 *
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include "BT_common.h"
#include "fsl_common.h"
#include "controller_features.h"
#include "fsl_gpio.h"
#include "fsl_iomuxc.h"
#include "fsl_os_abstraction.h"
#ifdef ENABLE_BT_IND_RESET
#include "BT_hci_api.h"
#include "controller_hci_uart.h"
#include "fw_loader_uart.h"
#include "controller.h"
#endif /*ENABLE_BT_IND_RESET*/

#ifdef PCAL6408A_IO_EXP_ENABLE
#include "fsl_adapter_i2c.h"
#endif /*#PCAL6408A_IO_EXP_ENABLE*/
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BT_OP(ogf, ocf) 				((ocf) | ((ogf) << 10))
#define BT_OGF_VS       				0x3FU
#define PRINTF_E(...) 					printf(__VA_ARGS__)

#ifdef PCAL6408A_IO_EXP_ENABLE
/*PCAL6408A I2C Slave Address, 7-bit */
#define PCAL6408A_I2C_ADDR 				(0x20U)
#define PCAL6408A_I2C_BAUDRATE 			(400000U)

#if defined (WIFI_BT_USE_M2_INTERFACE) && defined (CPU_MIMXRT1176DVMAA_cm7)
#define PCAL6408A_I2C_INSTANCE 			(5U)
#define PCAL6408AC_I2C_CLOCK_FREQ 		(CLOCK_GetFreq(kCLOCK_OscRc48MDiv2))
#elif defined (WIFI_BT_USE_M2_INTERFACE) && defined (CPU_MIMXRT1062DVL6B_cm7)
#define PCAL6408A_I2C_INSTANCE 			(1U)
#define PCAL6408AC_I2C_CLOCK_FREQ  		(24000000U)
#else
#define PCAL6408A_I2C_INSTANCE 			(5U)
#define PCAL6408AC_I2C_CLOCK_FREQ 		(CLOCK_GetFreq(kCLOCK_OscRc48MDiv2))
#endif /*defined (WIFI_BT_USE_M2_INTERFACE) && defined (CPU_MIMXRT1176DVMAA_cm7)*/

#define PCAL6408A_CHECK_RET(x, status) 	   \
        (status) = (x);                    \
        if ((status) != kStatus_Success)   \
        {                                  \
            return (status);               \
        }

#endif /*#ifdef PCAL6408A_IO_EXP_ENABLE*/

#ifdef ENABLE_BT_IND_RESET

#ifdef ENABLE_IR_DBG
#define PRINTF_D(...) 					printf(__VA_ARGS__)
#else
#define PRINTF_D(...)
#endif /*ENABLE_IR_DBG*/

#define IR_INBAND_OPCODE 				0xFCFCU
#define ir_state_update(status)                  \
{                                                \
    ir_state = status;                           \
    PRINTF_D("IR status update: %s\n", #status); \
}
/* IR RESET INDICATION GPIO SETTINGS */
#if (defined(CPU_MIMXRT1062DVMAA_cm7) || defined(CPU_MIMXRT1062DVL6A_cm7) || defined (CPU_MIMXRT1062DVL6B_cm7))
#if CONTROLLER_IR_GPIO_PIN_TOGGLE
/* IR RST INDICATION I/P GPIO, J22 PIN2*/
/*TODO: Confirm if IR-RST-INDICATION feature required,
 * else remove all code under this flag*/
#define IR_RESET_INDICATION_GPIO      GPIO1
#define IR_RESET_INDICATION_GPIO_PIN  (2U)
#define IR_RESET_INDICATION_GPIO_NAME "GPIO1"
#define IR_RESET_INDICATION_GPIO_IRQ  GPIO1_Combined_0_15_IRQn
#define IR_RESET_IND_GPIO_IRQ_HANDLER GPIO1_Combined_0_15_IRQHandler
#define IOMUXC_GPIO_IR_RESET_IND      IOMUXC_GPIO_AD_B0_02_GPIO1_IO02
#endif /*#if CONTROLLER_IR_GPIO_PIN_TOGGLE*/

#if !defined(WIFI_IW612_BOARD_MURATA_2EL_M2)
/* IR-OOB TRIGGER PAD J17.PIN1 for 1XK-M2, 1ZM-M2*/
#define IR_OUTBAND_TRIGGER_GPIO			GPIO1
#define IR_OUTBAND_TRIGGER_GPIO_PIN		(3U)
#define IR_OUTBAND_TRIGGER_GPIO_NAME   "GPIO1"
#define IOMUXC_GPIO_IR_OUTBAND_TRIGGER IOMUXC_GPIO_AD_B0_03_GPIO1_IO03
#else
/* IR-OOB TRIGGER for 2EL-M2, Internal Routing to M2 Slot*/
#define IR_OUTBAND_TRIGGER_GPIO			GPIO1
#define IR_OUTBAND_TRIGGER_GPIO_PIN		(18U)
#define IR_OUTBAND_TRIGGER_GPIO_NAME   "GPIO1"
#define IOMUXC_GPIO_IR_OUTBAND_TRIGGER IOMUXC_GPIO_AD_B1_02_GPIO1_IO18
#endif /*!defined(WIFI_IW612_BOARD_MURATA_2EL_M2)*/

#elif defined(CPU_MIMXRT1176DVMAA_cm7) // For RT1170

#if CONTROLLER_IR_GPIO_PIN_TOGGLE
/* IR RST INDICATION I/P GPIO, J9 PIN2, IOMUXC_GPIO_DISP_B2_11*/
#define IR_RESET_INDICATION_GPIO  		GPIO5
#define IR_RESET_INDICATION_GPIO_PIN  	(12U)
#define IR_RESET_INDICATION_GPIO_NAME 	"GPIO5"
#define IR_RESET_INDICATION_GPIO_IRQ  	GPIO5_Combined_0_15_IRQn // TODO
#define IR_RESET_IND_GPIO_IRQ_HANDLER 	GPIO5_Combined_0_15_IRQHandler
#endif /*#if CONTROLLER_IR_GPIO_PIN_TOGGLE*/

/* IR OUT-BAND TRIGGER GPIO*/
#if !defined(WIFI_IW612_BOARD_MURATA_2EL_M2)
/*Output GPIO J9 PIN4 (IOMUXC_GPIO_DISP_B2_10) for RT1170-EVKA*/
#define IR_OUTBAND_TRIGGER_GPIO   		GPIO5
#define IR_OUTBAND_TRIGGER_GPIO_PIN   	(11U)
#define IR_OUTBAND_TRIGGER_GPIO_NAME  	"GPIO5"
#else
/*For 2EL-A1, internal M2 routing from GPIO_AD_15 to BT_RST line on M2 Slot*/
#define IR_OUTBAND_TRIGGER_GPIO			GPIO9
#define IR_OUTBAND_TRIGGER_GPIO_PIN		(14U)
#define IR_OUTBAND_TRIGGER_GPIO_NAME   "GPIO9"
#define IOMUXC_GPIO_IR_OUTBAND_TRIGGER IOMUXC_GPIO_AD_15_GPIO9_IO14
#endif /*!defined(WIFI_IW612_BOARD_MURATA_2EL_M2)*/

#endif /* (defined(CPU_MIMXRT1062DVMAA_cm7) || (CPU_MIMXRT1062DVL6A_cm7)) */
#endif /*ENABLE_BT_IND_RESET*/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#ifdef PCAL6408A_IO_EXP_ENABLE
static hal_i2c_master_handle_t handle;
static uint8_t is_PCAL6408A_Initialise = 0U;
#endif /*PCAL6408A_IO_EXP_ENABLE*/
/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
#ifdef PCAL6408A_IO_EXP_ENABLE
static status_t IOEXP_I2C_Init(void *handle, uint32_t i2cInstance, uint32_t i2cBaudrate, uint32_t i2cSourceClockHz);
static status_t IOEXP_I2C_Deinit(void *handle);
static status_t IOEXP_I2C_Send(void *handle,
                               uint8_t deviceAddress,
                               uint32_t subAddress,
                               uint8_t subaddressSize,
                               uint8_t *txBuff,
                               uint8_t txBuffSize);
static status_t IOEXP_I2C_Receive(void *handle,
                                  uint8_t deviceAddress,
                                  uint32_t subAddress,
                                  uint8_t subaddressSize,
                                  uint8_t *rxBuff,
                                  uint8_t rxBuffSize);

static status_t PCAL6408A_WriteReg(void *handle, uint8_t reg, uint8_t val);
static status_t PCAL6408A_ReadReg(void *handle, uint8_t reg, uint8_t *val);
static status_t PCAL6408A_readAllConfig(pcal6408a_pins_cfg_t *config);
static status_t PCAL6408A_ModifyReg(void *handle, uint8_t reg, uint8_t mask, uint8_t val);
#endif /*PCAL6408A_IO_EXP_ENABLE*/

#ifdef ENABLE_BT_IND_RESET
DECL_STATIC void configure_ir_reset_ind_gpio(void);
DECL_STATIC void controller_config_oob_ir_gpio(void);
DECL_STATIC void controller_trigger_oob_ir(void);
DECL_STATIC uint8_t controller_wait_for_ir_config_status(void);
DECL_STATIC UINT8 controller_trigger_inband_ir(void);
DECL_STATIC void controller_uart_tr_rx_cb(hal_uart_handle_t handle, hal_uart_status_t status, void *userData);
DECL_STATIC hal_uart_status_t controller_init_uart(hal_uart_handle_t handle, uint32_t u32BaudRate, bool flowControl);
DECL_STATIC hal_uart_status_t controller_deinit_uart(hal_uart_handle_t handle);
DECL_STATIC BT_THREAD_RETURN_TYPE controller_redownload_firmware(BT_THREAD_ARGS args);
DECL_STATIC void controller_create_uart_read_task(BT_THREAD_START_ROUTINE routine);
DECL_STATIC UART_HANDLE_DEFINE(s_uartHandle);
#endif /* ENABLE_BT_IND_RESET */

/*******************************************************************************
 * Variables
 ******************************************************************************/

#ifdef ENABLE_BT_IND_RESET
uint8_t g_ir_hci_cmd_status = 0xFFU;
AT_NONCACHEABLE_SECTION_ALIGN(static UCHAR uart_rx_data_buff[UART_RX_QUEUE_SIZE], 4);
DECL_STATIC uartMetaData_t uart_rx;
DECL_STATIC UCHAR uart_rx_state;
DECL_STATIC UINT16 uart_rx_bytes;
DECL_STATIC uint16_t uart_read_expected_len;
DECL_STATIC BT_thread_type btUartRdTask_tid = NULL;
DECL_STATIC ir_mode_t ir_mode               = IR_DISABLE;
DECL_STATIC ir_state_t ir_state;
OSA_SEMAPHORE_HANDLE_DEFINE(xStartIRThread);
OSA_SEMAPHORE_HANDLE_DEFINE(xUartTxSent);
OSA_SEMAPHORE_HANDLE_DEFINE(xUartRxRcvd);
OSA_SEMAPHORE_HANDLE_DEFINE(xWaitForBTDownload);
#endif /*ENABLE_BT_IND_RESET*/

/*******************************************************************************
 * Code
 ******************************************************************************/
#ifdef PCAL6408A_IO_EXP_ENABLE
/*!
 * brief IOEXP i2c bus initilization.
 *
 * param handle i2c master handle.
 * param i2CInstance instance number of the i2c bus, such as 0 is corresponding to I2C0.
 * param i2cBaudrate i2c baudrate.
 * param i2cSourceClockHz i2c source clock frequency.
 * return kStatus_HAL_I2cSuccess is success, else initial failed.
 */
static status_t IOEXP_I2C_Init(void *handle, uint32_t i2cInstance, uint32_t i2cBaudrate, uint32_t i2cSourceClockHz)
{
    hal_i2c_master_config_t masterConfig;

    masterConfig.enableMaster = true;
    masterConfig.baudRate_Bps = i2cBaudrate;
    masterConfig.srcClock_Hz  = i2cSourceClockHz;
    masterConfig.instance     = (uint8_t)i2cInstance;

    return (status_t)HAL_I2cMasterInit((hal_i2c_master_handle_t *)handle, &masterConfig);
}

/*!
 * brief IOEXP i2c de-initilization.
 *
 * param handle i2c master handle.
 * return kStatus_HAL_I2cSuccess is success, else deinitial failed.
 */
static status_t IOEXP_I2C_Deinit(void *handle)
{
    return (status_t)HAL_I2cMasterDeinit((hal_i2c_master_handle_t *)handle);
}

/*!
 * brief IOEXP i2c send function.
 *
 * param handle i2c master handle.
 * param deviceAddress IOEXP device address.
 * param subAddress register address.
 * param subaddressSize register address width.
 * param txBuff tx buffer pointer.
 * param txBuffSize tx buffer size.
 * return kStatus_HAL_I2cSuccess is success, else send failed.
 */
static status_t IOEXP_I2C_Send(void *handle,
                               uint8_t deviceAddress,
                               uint32_t subAddress,
                               uint8_t subaddressSize,
                               uint8_t *txBuff,
                               uint8_t txBuffSize)
{
    hal_i2c_master_transfer_t masterXfer;

    masterXfer.slaveAddress   = deviceAddress;
    masterXfer.direction      = kHAL_I2cWrite;
    masterXfer.subaddress     = (uint32_t)subAddress;
    masterXfer.subaddressSize = subaddressSize;
    masterXfer.data           = txBuff;
    masterXfer.dataSize       = txBuffSize;
    masterXfer.flags          = (uint32_t)kHAL_I2cTransferDefaultFlag;

    return (status_t)HAL_I2cMasterTransferBlocking((hal_i2c_master_handle_t *)handle, &masterXfer);
}

/*!
 * brief IOEXP i2c receive function.
 *
 * param handle i2c master handle.
 * param deviceAddress IOEXP device address.
 * param subAddress register address.
 * param subaddressSize register address width.
 * param rxBuff rx buffer pointer.
 * param rxBuffSize rx buffer size.
 * return kStatus_HAL_I2cSuccess is success, else receive failed.
 */
static status_t IOEXP_I2C_Receive(void *handle,
                                  uint8_t deviceAddress,
                                  uint32_t subAddress,
                                  uint8_t subaddressSize,
                                  uint8_t *rxBuff,
                                  uint8_t rxBuffSize)
{
    hal_i2c_master_transfer_t masterXfer;

    masterXfer.slaveAddress   = deviceAddress;
    masterXfer.direction      = kHAL_I2cRead;
    masterXfer.subaddress     = (uint32_t)subAddress;
    masterXfer.subaddressSize = subaddressSize;
    masterXfer.data           = rxBuff;
    masterXfer.dataSize       = (size_t)rxBuffSize;
    masterXfer.flags          = (uint32_t)kHAL_I2cTransferDefaultFlag;

    return (status_t)HAL_I2cMasterTransferBlocking((hal_i2c_master_handle_t *)handle, &masterXfer);
}

status_t PCAL6408A_Init(pcal6408a_pins_cfg_t *config)
{
    status_t ret = kStatus_Success;

    if (IOEXP_I2C_Init(&handle, PCAL6408A_I2C_INSTANCE, PCAL6408A_I2C_BAUDRATE, PCAL6408AC_I2C_CLOCK_FREQ) !=
        (status_t)kStatus_HAL_I2cSuccess)
    {
        return kStatus_Fail;
    }

    is_PCAL6408A_Initialise = 1U;

    PCAL6408A_CHECK_RET(PCAL6408A_WriteReg(&handle, PCAL6408A_REG_OUTPUT_PORT_CONFIGURATION, 0x08), ret);
    /*making p0, p3 as output*/
    PCAL6408A_CHECK_RET(PCAL6408A_WriteReg(&handle, PCAL6408A_REG_CONFIGURATION, 0xF6), ret);
    PCAL6408A_CHECK_RET(PCAL6408A_WriteReg(&handle, PCAL6408A_REG_OUTPUT_PORT, 0x00), ret);
    ret = PCAL6408A_readAllConfig(config);

    return ret;
}

status_t PCAL6408A_DeInit(void)
{
    status_t ret = IOEXP_I2C_Deinit(&handle);

    if(kStatus_Success == ret)
    {
        is_PCAL6408A_Initialise = 0;
    }

    return ret;
}

static status_t PCAL6408A_WriteReg(void *handle, uint8_t reg, uint8_t val)
{
    return IOEXP_I2C_Send(handle, PCAL6408A_I2C_ADDR, reg, 1U, (uint8_t *)&val, 1U);
}

static status_t PCAL6408A_ReadReg(void *handle, uint8_t reg, uint8_t *val)
{
    return IOEXP_I2C_Receive(handle, PCAL6408A_I2C_ADDR, reg, 1U, val, 1U);
}

static status_t PCAL6408A_ModifyReg(void *handle, uint8_t reg, uint8_t mask, uint8_t val)
{
    uint8_t reg_val = 0;
    status_t retval = PCAL6408A_ReadReg(handle, reg, &reg_val);

    if (retval != kStatus_Success)
    {
        return kStatus_Fail;
    }
    reg_val &= ~mask;
    reg_val |= val;
    printf("writing %02X on IO Port\n", reg_val);
    retval = PCAL6408A_WriteReg(handle, reg, reg_val);
    if (retval != kStatus_Success)
    {
        return kStatus_Fail;
    }
    return kStatus_Success;
}

static status_t PCAL6408A_readAllConfig(pcal6408a_pins_cfg_t *config)
{
    status_t ret = kStatus_Success;

    memset(config, 0, sizeof(*config));
    uint8_t value = 0;
    PCAL6408A_CHECK_RET(PCAL6408A_ReadReg(&handle, PCAL6408A_REG_CONFIGURATION, &value), ret);
    config->configured = value;
    PCAL6408A_CHECK_RET(PCAL6408A_ReadReg(&handle, PCAL6408A_REG_OUTPUT_PORT, &value), ret);
    config->output_port_value = value;
    PCAL6408A_CHECK_RET(PCAL6408A_ReadReg(&handle, PCAL6408A_REG_INPUT_PORT, &value), ret);
    config->input_port_value = value;
    PCAL6408A_CHECK_RET(PCAL6408A_ReadReg(&handle, PCAL6408A_REG_OUTPUT_PORT_CONFIGURATION, &value), ret);
    config->output_port_config = value;
    PCAL6408A_CHECK_RET(PCAL6408A_ReadReg(&handle, PCAL6408A_REG_PULL_UP_DOWN_ENABLE, &value), ret);
    config->pulls_enabled = value;
    PCAL6408A_CHECK_RET(PCAL6408A_ReadReg(&handle, PCAL6408A_REG_POLARITY_INVERSION, &value), ret);
    config->polarity = value;
    PCAL6408A_CHECK_RET(PCAL6408A_ReadReg(&handle, PCAL6408A_REG_OUTPUT_DRIVE_STRENGTH_0, &value), ret);
    config->ouput_drive_strength1 = value;
    PCAL6408A_CHECK_RET(PCAL6408A_ReadReg(&handle, PCAL6408A_REG_OUTPUT_DRIVE_STRENGTH_1, &value), ret);
    config->ouput_drive_strength2 = value;

    return ret;
}

status_t PCAL6408A_control_op_port(pcal6408a_op_port_e port_num, uint8_t signal)
{
	status_t ret = kStatus_Success;

    if(is_PCAL6408A_Initialise == 0)
    {
        pcal6408a_pins_cfg_t config;
        ret = PCAL6408A_Init(&config);

        if(kStatus_Success == ret)
        {
            uint8_t reg_val = 0;

            PCAL6408A_CHECK_RET(PCAL6408A_ModifyReg(&handle, PCAL6408A_REG_OUTPUT_PORT, (1U << port_num),
                    (signal << port_num)), ret);

            PCAL6408A_CHECK_RET(PCAL6408A_ReadReg(&handle, PCAL6408A_REG_OUTPUT_PORT, &reg_val), ret);
            reg_val = (reg_val >> port_num) & 1U;

            (signal == reg_val) ? (ret = kStatus_Success):(ret = kStatus_Fail);
            PCAL6408A_DeInit();
        }
        else
        {
        	PRINTF_E("IO-EXP init failure:%d\n", ret);
        }
    }

    return ret;
}

status_t PCAL6408A_read_op_port(pcal6408a_op_port_e port_num, uint8_t *value)
{
	status_t ret = kStatus_Success;

    if(is_PCAL6408A_Initialise == 0)
    {
        pcal6408a_pins_cfg_t config;
        ret = PCAL6408A_Init(&config);

        if(kStatus_Success == ret)
        {
            uint8_t reg_val = 0;

            PCAL6408A_CHECK_RET(PCAL6408A_ReadReg(&handle, PCAL6408A_REG_OUTPUT_PORT, &reg_val), ret);
            *value = (reg_val >> port_num) & 1U;
            ret = kStatus_Success;
            PCAL6408A_DeInit();
        }
        else
        {
            PRINTF_E("IO-EXP init failure:%d\n", ret);
        }
    }

    return ret;
}
#endif /*PCAL6408A_IO_EXP_ENABLE*/

#ifdef ENABLE_BT_IND_RESET
#ifdef CONTROLLER_IR_GPIO_PIN_TOGGLE
/*Todo: Confirm if GPIO toggle will be supported in future, else remove all code under this flag*/
DECL_STATIC void configure_ir_reset_ind_gpio(void)
{
    gpio_pin_config_t irRstIndGpioConfig = {
        .direction = kGPIO_DigitalInput, .outputLogic = 0U, .interruptMode = kGPIO_IntRisingOrFallingEdge};

    GPIO_PinInit(IR_RESET_INDICATION_GPIO, IR_RESET_INDICATION_GPIO_PIN, &irRstIndGpioConfig);
    GPIO_ClearPinsInterruptFlags(IR_RESET_INDICATION_GPIO, 1U << IR_RESET_INDICATION_GPIO_PIN);
    GPIO_EnableInterrupts(IR_RESET_INDICATION_GPIO, 1U << IR_RESET_INDICATION_GPIO_PIN);
    EnableIRQ(IR_RESET_INDICATION_GPIO_IRQ);
    // GPC_EnableWakeupSource(IR_RESET_INDICATION_GPIO_IRQ);
#if defined(IOMUXC_GPIO_IR_RESET_IND)
    IOMUXC_SetPinMux(IOMUXC_GPIO_IR_RESET_IND, /* GPIO_AD_B0_11 is configured as GPIO1_IO11 */
                     0U);
#endif
    return;
}
#endif

DECL_STATIC void controller_config_oob_ir_gpio(void)
{
    gpio_pin_config_t out_config = {
        kGPIO_DigitalOutput,
        1, /*By default HIGH on the GPIO line*/
        kGPIO_NoIntmode,
    };
    ir_state_update(IR_CONFIG_OOB_GPIO);
#if defined(IOMUXC_GPIO_IR_OUTBAND_TRIGGER)
    IOMUXC_SetPinMux(IOMUXC_GPIO_IR_OUTBAND_TRIGGER, /* GPIO_AD_B0_10 is configured as GPIO1_IO10 */
                     0U);
#endif
    GPIO_PinInit(IR_OUTBAND_TRIGGER_GPIO, IR_OUTBAND_TRIGGER_GPIO_PIN, &out_config);
    return;
}

DECL_STATIC uint8_t controller_wait_for_ir_config_status()
{
    uint8_t retry_count = 10;
    uint8_t status;
    ir_state_update(IR_CONFIG_RESP_STATUS);
    while ((g_ir_hci_cmd_status == 0xFF) && (--retry_count > 0))
    {
        PRINTF_D("wait_for_IR_config_event:0x%02X\n", g_ir_hci_cmd_status);
        OSA_TimeDelay(1);
    }
    status              = g_ir_hci_cmd_status;
    g_ir_hci_cmd_status = 0xFFU;

    return status;
}

void controler_config_ir(ir_mode_t ir_option)
{
    static UINT8 oneTimeInit = BT_TRUE;

    ir_state_update(IR_CONFIG_IR);
    if ((ir_option == IR_DISABLE) || (ir_option == IR_OOB) || (ir_option == IR_INBAND))
    {
        UCHAR ir_payload[2];
        if ((oneTimeInit == BT_TRUE) && (ir_option == IR_OOB))
        {
            /* Configure RESET-INDICATION GPIO(controller's GPIO-22) to read IR Status from Controller! */
#if CONTROLLER_IR_GPIO_PIN_TOGGLE
            configure_ir_reset_ind_gpio();
#endif
            /* Configure GPIO1 IO0 for OUTBAND OUTPUT TRIGGER*/
            controller_config_oob_ir_gpio();
            oneTimeInit = BT_FALSE;
        }

        ir_payload[0] = ir_option;
        ir_payload[1] = 0xFFU; /*default GPIO will be used by controller for IR*/
        ir_state_update(IR_CONFIG_SEND_CMD);
        (void)BT_hci_vendor_specific_command(INDEPENDENT_RESET_VENDOR_CMD_ENABLE_IR, ir_payload, 2U);
        uint8_t status = controller_wait_for_ir_config_status();
        if (status != 0x00)
        {
            ir_state_update(IR_CONFIG_GET_RSP_ERR);
            PRINTF_E("Error: IR configure hci response ir_state = %d for ir_mode:%d\n", ir_state, ir_option);
        }
        else
        {
            ir_mode = ir_option;
            printf("IR configured successfully for mode %d, ir_state = %d\n", ir_mode, ir_state);
            ir_state_update(IR_CONFIG_CMPLT);
        }
    }
    else
    {
        PRINTF_E("Error: Unsupported IR mode entered, %d, ir_state = %d\n", ir_mode, ir_state);
        ir_state_update(IR_UNSUPPORTED_MODE);
    }

    return;
}

DECL_STATIC BT_THREAD_RETURN_TYPE controller_redownload_firmware(BT_THREAD_ARGS args)
{
    while (1)
    {
        OSA_SemaphoreWait(xStartIRThread, osaWaitForever_c);
        ir_state_update(IR_BT_FW_DNLD_START);
        controller_init();
        ir_state_update(IR_BT_FW_DNLD_COMPELTED);
        OSA_SemaphorePost(xWaitForBTDownload);
    }
}

DECL_STATIC void controller_trigger_oob_ir(void)
{
    /*since, controller's isr registered with falling edge trigger,
     * there is no need to maintain pulse interval more than 10ms*/
	printf("Sending Out of Band IR Trigger\n");
	ir_state_update(IR_OOB_TRIGGER_IR);
    GPIO_PinWrite(IR_OUTBAND_TRIGGER_GPIO, IR_OUTBAND_TRIGGER_GPIO_PIN, 0);
    OSA_TimeDelay(10);
    GPIO_PinWrite(IR_OUTBAND_TRIGGER_GPIO, IR_OUTBAND_TRIGGER_GPIO_PIN, 1);
}

DECL_STATIC UINT8 controller_trigger_inband_ir(void)
{
    hal_uart_status_t error;
    UINT8 ret            = BT_FALSE;
    uint8_t sendingBuffer[5];
    uint8_t inbandStatusIndex = 6U;
    uint16_t resp_opcode;
    printf("Sending Inband IR Trigger\n");
    ir_state_update(IR_INBAND_TRIGGER_START);
    memset(sendingBuffer, 0, sizeof(sendingBuffer));

    if ((error = controller_init_uart((hal_uart_handle_t)s_uartHandle, 3000000U, true)) != kStatus_HAL_UartSuccess)
    {
        PRINTF_E("fw_loader_init_uart Failed for UART Instance: %X\n", error);
        ir_state_update(IR_UART_INIT_FAILURE);
        return ret;
    }
    ir_state_update(IR_INBAND_SEND_TRIGGER);
    /* sending ir-inband trigger command!!*/
    sendingBuffer[0] = 0x01U;
    uint16_t *opcode = (uint16_t *)&sendingBuffer[1];
    *opcode          = (uint16_t)BT_OP(BT_OGF_VS, INDEPENDENT_RESET_VENDOR_CMD_TRIGGER_IR);
    sendingBuffer[3] = 0; /* no data, so 0 parameter length*/

    PRINTF_D("IR INBAND CMD:%02X %02X %02X %02X\n", sendingBuffer[0], sendingBuffer[1], sendingBuffer[2],
             sendingBuffer[3]);
    error = HAL_UartSendNonBlocking((hal_uart_handle_t)s_uartHandle, &sendingBuffer[0], 4U);
    if (error != kStatus_HAL_UartSuccess)
    {
        PRINTF_E("HAL_UartSendNonBlocking Failed for UART Instance: %X\n", error);
        ir_state_update(IR_UART_SEND_FAILURE);
        return ret;
    }
    OSA_SemaphoreWait(xUartTxSent, 10);
    ir_state_update(IR_INBAND_CHECK_TRIGGER_RSP);
    uart_read_expected_len = 7U;
    uart_rx.dataSize       = uart_read_expected_len;
    error = HAL_UartReceiveNonBlocking((hal_uart_handle_t)s_uartHandle, uart_rx.data, uart_rx.dataSize);
    if (error != kStatus_HAL_UartSuccess)
    {
        PRINTF_E("HAL_UartReceiveNonBlocking Failed for UART Instance: %X\n", error);
        ir_state_update(IR_CONFIG_RESP_STATUS_ERR);
        return ret;
    }
    ir_state_update(IR_INBAND_TRIGGER_WAIT_RSP);
    OSA_SemaphoreWait(xUartRxRcvd, 10);
    resp_opcode = (uart_rx.data[4] << 8) | uart_rx.data[5];
    PRINTF_D("IR INBAND RSP (0x%04X):%02X %02X %02X %02X %02X %02X %02X\n", resp_opcode, uart_rx.data[0],
             uart_rx.data[1], uart_rx.data[2], uart_rx.data[3], uart_rx.data[4], uart_rx.data[5], uart_rx.data[6]);

    if ((resp_opcode == IR_INBAND_OPCODE) && (uart_rx.data[inbandStatusIndex] == 0x00))
    {
        ir_state_update(IR_TRIGGER_COMPLETE);
        ret = BT_TRUE;
    }
    else
    {
        ir_state_update(IR_TRIGGER_FAIL);
    }

    if ((error = controller_deinit_uart((hal_uart_handle_t)s_uartHandle)) != kStatus_HAL_UartSuccess)
    {
        PRINTF_E("HAL_UartDeInit Failed for UART Instance: %X\n", error);
        ir_state_update(IR_UART_DEINIT_FAILURE);
    }
    return ret;
}

void controller_trigger_ir(void)
{
    UINT8 ir_triggered = BT_FALSE;
    if ((ir_mode != IR_INBAND) && (ir_mode != IR_OOB))
    {
        PRINTF_E("IR not configured, use option 255 ir_state = %d\n", ir_state);
        ir_state_update(IR_NOT_CONFIGURED);
        return;
    }
    ir_state_update(IR_BT_OFF);
    printf("EtherMind: Bluetooth OFF ...\n");
    (void)BT_bluetooth_off();
    OSA_TimeDelay(10);

    if (ir_mode == IR_INBAND)
    {
        ir_triggered = controller_trigger_inband_ir();
    }
    else if (ir_mode == IR_OOB)
    {
        controller_trigger_oob_ir();
        ir_triggered = BT_TRUE;
    }
    ir_mode = IR_DISABLE;
    if (ir_triggered == BT_TRUE)
    {
        static UINT8 oneTimeInit = BT_TRUE;
        if (oneTimeInit == BT_TRUE)
        {
            OSA_SemaphoreCreate(xWaitForBTDownload, 0);
            OSA_SemaphoreCreate(xStartIRThread, 0);
            controller_create_uart_read_task(controller_redownload_firmware);
            oneTimeInit = BT_FALSE;
        }
        OSA_SemaphorePost(xStartIRThread);
        OSA_SemaphoreWait(xWaitForBTDownload, (1000U * 20U));
    }
    printf("IR exit with state = %d\n", ir_state);
    return;
}

DECL_STATIC void controller_create_uart_read_task(BT_THREAD_START_ROUTINE routine)
{
    BT_thread_attr_type btUartRd_attr;

    /* Initialize the Write Task Attributes */
    btUartRd_attr.thread_name       = (DECL_CONST CHAR *)"BTURTRD";
    btUartRd_attr.thread_stack_size = BT_TASK_STACK_DEPTH;
    btUartRd_attr.thread_priority   = BT_TASK_PRIORITY;

    if (BT_thread_create(&btUartRdTask_tid, &btUartRd_attr, routine, NULL) < 0)
    {
        PRINTF_E("failed to Create btUartRead_task_create\n");
    }
}

DECL_STATIC hal_uart_status_t controller_init_uart(hal_uart_handle_t handle, uint32_t u32BaudRate, bool flowControl)
{
    hal_uart_config_t config;
    controller_hci_uart_config_t hciUartConfig;
    hal_uart_status_t status = kStatus_HAL_UartSuccess;

    memset(&hciUartConfig, 0, sizeof(hciUartConfig));
    memset(&config, 0, sizeof(config));
    controller_hci_uart_get_configuration(&hciUartConfig);

    /* Set the HCI-UART Configuration parameters */
    config.srcClock_Hz  = hciUartConfig.clockSrc;
    config.parityMode   = kHAL_UartParityDisabled;
    config.stopBitCount = kHAL_UartOneStopBit;
    config.enableRx     = 1;
    config.enableTx     = 1;
    config.instance     = hciUartConfig.instance;
    config.baudRate_Bps = u32BaudRate;
    config.enableRxRTS  = 0;
    config.enableTxCTS  = 0;
#if (defined(HAL_UART_ADAPTER_FIFO) && (HAL_UART_ADAPTER_FIFO > 0u))
    config.txFifoWatermark = 0U;
    config.rxFifoWatermark = 0U;
#endif

    if (flowControl)
    {
        config.enableRxRTS = hciUartConfig.enableRxRTS;
        config.enableTxCTS = hciUartConfig.enableTxCTS;
    }

    status = HAL_UartInit((hal_uart_handle_t)handle, &config);
    if (status != kStatus_HAL_UartSuccess)
    {
        PRINTF_E("Failed to initialize BT UART, %x!\r\n", status);
    }
    else
    {
        /* Install the UART TX-RX Callback */
        status = HAL_UartInstallCallback((hal_uart_handle_t)handle, controller_uart_tr_rx_cb, NULL);
        if (status != kStatus_HAL_UartSuccess)
        {
            PRINTF_E("Failed to install uart callbacks, %x!\r\n", status);
        }
    }

    if (status == kStatus_HAL_UartSuccess)
    {
        /* Initialize the UART RX DS to be used in the Platform API */
        memset(uart_rx_data_buff, 0, sizeof(uart_rx_data_buff));
        uart_rx_bytes = 0;
        uart_rx.data  = &uart_rx_data_buff[uart_rx_bytes];

        OSA_SemaphoreCreate(xUartRxRcvd, 0);
        OSA_SemaphoreCreate(xUartTxSent, 0);
        uart_rx_state = BT_TRUE;

        OSA_TimeDelay(50U);
    }

    return status;
}

DECL_STATIC hal_uart_status_t controller_deinit_uart(hal_uart_handle_t handle)
{
    hal_uart_status_t status = kStatus_HAL_UartSuccess;

    if (uart_rx_state == BT_TRUE)
    {
        (void)HAL_UartAbortReceive(handle);
        (void)HAL_UartAbortSend(handle);
        status = HAL_UartDeinit(handle);

        if (status != kStatus_HAL_UartSuccess)
        {
            PRINTF_E("UARTDeinit Failed for UART Instance: %x\n", status);
        }
        else
        {
            OSA_SemaphoreDestroy(xUartRxRcvd);
            OSA_SemaphoreDestroy(xUartTxSent);
            uart_rx_state = BT_FALSE;
        }
        OSA_TimeDelay(100);
    }
    return status;
}

DECL_STATIC void controller_uart_tr_rx_cb(hal_uart_handle_t handle, hal_uart_status_t status, void *userData)
{
    /* Data Received? */
    if (NULL != handle)
    {
        int ret;

        if ((hal_uart_status_t)kStatus_HAL_UartRxIdle == status)
        {
            /* Increment the rx Bytes marker */
            uart_rx_bytes += uart_rx.dataSize;

            if (uart_rx.dataSize == uart_read_expected_len)
            {
                PRINTF_D("RX %d\r\n", uart_read_expected_len);

                ret = OSA_SemaphorePost(xUartRxRcvd);
                if (0U != ret)
                {
                    PRINTF_E("rx signal failed with ret %d\r\n", ret);
                }
            }
            else
            {
                /* Point the place holder for next data reception */
                uart_rx.data     = &uart_rx_data_buff[uart_rx_bytes];
                uart_rx.dataSize = uart_rx.dataSize - uart_rx_bytes;
                /* Invoke Receive Non-Blocking over UART again for expected length */
                (BT_IGNORE_RETURN_VALUE)
                    HAL_UartReceiveNonBlocking((hal_uart_handle_t)handle, uart_rx.data, uart_rx.dataSize);
            }
        }
        else if ((hal_uart_status_t)kStatus_HAL_UartTxIdle == status)
        {
            ret = OSA_SemaphorePost(xUartTxSent);
            if (0U != ret)
            {
                PRINTF_E("tx signal failed with ret %d\r\n", ret);
            }
        }
        else
        {
            //
        }
    }
}

#endif /*ENABLE_BT_IND_RESET*/
