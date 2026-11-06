#ifndef nrf24l01_h_
#define nrf24l01_h_

#include "stdint.h"
#include "GPIO.h"
#include "TIM.h"
#include "SPI.h"

#define nrf_cs_port GPIOA
#define nrf_cs_pin PIN_8
#define nrf_ce_port GPIOB
#define nrf_ce_pin PIN_6
#define nrf_irq_port GPIOC
#define nrf_irq_pin PIN_7

// define command

#define R_REGISTER 0x00 ///< R_REGISTER|REG_ADDRESS (5bit)
#define W_REGISTER 0x20 ///< W_REGISTER|REG_ADDRESS (5bit)

#define R_RX_PAYLOAD 0x61
#define W_TX_PAYLOAD 0xA0

#define FLUSH_TX 0xE1
#define FLUSH_RX 0xE2

#define REUSE_TX_PL 0xE3
#define R_RX_PL_WID 0x60
#define W_ACK_PAYLOAD 0xA8
#define W_TX_PAYLOAD_NOACK 0xB0 ///< W_TX_PAYLOAD_NOACK|PIPE_NUMBER (3bit)
#define NOP 0xFF

// define register address

#define CONFIG 0x00
#define EN_AA 0x01
#define EN_RXADDR 0x02
#define SETUP_AW 0x03
#define SETUP_RETR 0x04
#define RF_CH 0x05
#define RF_SETUP 0x06
#define STATUS 0x07
#define OBSERVE_TX 0x08
#define RPD 0x09
#define RX_ADDR_P0 0x0A
#define RX_ADDR_P1 0x0B
#define RX_ADDR_P2 0x0C
#define RX_ADDR_P3 0x0D
#define RX_ADDR_P4 0x0E
#define RX_ADDR_P5 0x0F
#define TX_ADDR 0x10
#define RX_PW_P0 0x11
#define RX_PW_P1 0x12
#define RX_PW_P2 0x13
#define RX_PW_P3 0x14
#define RX_PW_P4 0x15
#define RX_PW_P5 0x16
#define FIFO_STATUS 0x17
#define DYNPD 0x1C
#define FEATURE 0x1D

// prototype function

// enum

typedef enum {
	pipe0 = 0,
	pipe1 = 1,
	pipe2 = 2,
	pipe3 = 3,
	pipe4 = 4,
	pipe5 = 5
} nrf_typedef_pipe;

typedef enum {
	dr_1mbps = 0,
	dr_2mbps = 1,
	dr_250kbps = 2
} nrf_typedef_data_rate;

typedef enum {
	pwr_m18dbm = 0,
	pwr_m12dbm = 1,
	pwr_m6dbm = 2,
	pwr_0dbm = 3
} nrf_typedef_power_tx;

typedef enum {
	crc_1_byte = 0,
	crc_2_byte = 1
} nrf_typedef_crc_byte;

typedef enum {
	power_down = 0,
	power_up = 1
} nrf_typedef_power_state;

typedef enum {
	tx = 0,
	rx = 1
} nrf_typedef_mode;

// layer 0 - hw

void nrf_cs_set(void);
void nrf_cs_reset(void);
void nrf_ce_set(void);
void nrf_ce_reset(void);

// layer 1 - protocol

uint8_t nrf_read_reg(uint8_t reg);
void nrf_write_reg(uint8_t reg, uint8_t data);
void nrf_write_reg_buf(uint8_t reg, uint8_t* data, uint8_t length);

// layer 2 - configuration

void nrf_set_power(nrf_typedef_power_tx power);
void nrf_set_data_rate(nrf_typedef_data_rate data_rate);
void nrf_set_channel(uint8_t channel);
void nrf_set_tx_address(uint8_t *address); ///< 5byte address
void nrf_set_rx_address(uint8_t *address, nrf_typedef_pipe pipe);
void nrf_set_auto_ack(nrf_typedef_pipe pipe, uint8_t enable);
void nrf_set_crc(nrf_typedef_crc_byte crc_byte);
void nrf_set_pwr_up(nrf_typedef_power_state state);
void nrf_set_payload_width(nrf_typedef_pipe pipe, uint8_t width);
void nrf_set_mode(nrf_typedef_mode mode);
void nrf_set_enable_pipe(nrf_typedef_pipe pipe);
void nrf_set_retr(void);

// layer 3 - operation

void nrf_flush_tx(void);
void nrf_flush_rx(void);
uint8_t nrf_read_payload_width(void);
void nrf_write_tx_payload(uint8_t *data, uint8_t length);
void nrf_read_payload(uint8_t* data, uint8_t length);
void nrf_send_payload(void);
uint8_t nrf_get_status(void);

void nrf_clear_tx_ds(void);
void nrf_clear_rx_dr(void);
void nrf_clear_max_rt(void);

void nrf_tx_init(void);
void nrf_rx_init(void);
void nrf_send_5_byte(uint8_t* data);

#endif