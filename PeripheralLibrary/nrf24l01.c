#include "nrf24l01.h"

// layer 0

void nrf_cs_set(){
	GPIO_Write_Pin(nrf_cs_port, nrf_cs_pin, 1);
};
void nrf_cs_reset(){
	GPIO_Write_Pin(nrf_cs_port, nrf_cs_pin, 0);
};
void nrf_ce_set(){
	GPIO_Write_Pin(nrf_ce_port, nrf_ce_pin, 1);
};
void nrf_ce_reset(){
	GPIO_Write_Pin(nrf_ce_port, nrf_ce_pin, 0);
};

// layer 1

uint8_t nrf_read_reg(uint8_t reg){
	uint8_t data;
	uint8_t temp = R_REGISTER|reg;
	
	nrf_cs_reset();
	SPI1_Transmit(&temp, 1);
	SPI1_Receive(&data, 1);
	nrf_cs_set();
	
	return data;
};

void nrf_write_reg(uint8_t reg, uint8_t data){
	uint8_t temp[2];
	temp[0] = W_REGISTER|reg;
	temp[1] = data;
	
	nrf_cs_reset();
	SPI1_Transmit(temp, 2);
	nrf_cs_set();
};

void nrf_write_reg_buf(uint8_t reg, uint8_t* data, uint8_t length){
	uint8_t temp = W_REGISTER|reg;
	
	nrf_cs_reset();
	SPI1_Transmit(&temp, 1);
	SPI1_Transmit(data, length);
	nrf_cs_set();
};

// layer 2 - configuration

void nrf_set_power(nrf_typedef_power_tx power){
	uint8_t temp = nrf_read_reg(RF_SETUP);
	temp &= ~(0b11 << 1);
	temp |= ((uint8_t)power << 1);
	nrf_write_reg(RF_SETUP, temp);
};

void nrf_set_data_rate(nrf_typedef_data_rate data_rate){
	uint8_t temp = nrf_read_reg(RF_SETUP);
	temp &= ~(0b101 << 3);
	switch (data_rate){
		case dr_1mbps:
			break;
		case dr_2mbps:
			temp |= (1 << 3);
			break;
		case dr_250kbps:
			temp |= (1 << 5);
			break;
	}
	nrf_write_reg(RF_SETUP, temp);
};

void nrf_set_channel(uint8_t channel){
	nrf_write_reg(RF_CH, channel); ///<  0 <= channel <= 125
};

void nrf_set_tx_address(uint8_t *address){
	nrf_write_reg(SETUP_AW, 3);
	
	nrf_write_reg_buf(TX_ADDR, address, 5);
};

// pipe 0-1 -> 5byte, pipe 2-5 -> last byte
void nrf_set_rx_address(uint8_t *address, nrf_typedef_pipe pipe){ 
	nrf_write_reg(SETUP_AW, 3);
	
	switch (pipe){
		case pipe0:
			nrf_write_reg_buf(RX_ADDR_P0, address, 5);
			break;
		case pipe1:
			nrf_write_reg_buf(RX_ADDR_P1, address, 5);
			break;
		case pipe2:
			nrf_write_reg_buf(RX_ADDR_P2, address + 4, 1); ///< ex: uint8_t address[5] = {0xE0, 0xE0, 0xE0, 0xE0, 0xA1};
			break;
		case pipe3:
			nrf_write_reg_buf(RX_ADDR_P3, address + 4, 1);
			break;
		case pipe4:
			nrf_write_reg_buf(RX_ADDR_P4, address + 4, 1);
			break;
		case pipe5:
			nrf_write_reg_buf(RX_ADDR_P5, address + 4, 1);
			break;
	}
};

void nrf_set_auto_ack(nrf_typedef_pipe pipe, uint8_t enable){
	uint8_t temp = nrf_read_reg(EN_AA);
	
	if(enable){
		temp |= (1 << pipe);
	}else{
		temp &= ~(1 << pipe);
	}
	nrf_write_reg(EN_AA, temp);
};

void nrf_set_crc(nrf_typedef_crc_byte crc_byte){ ///< if EN_AA is active, must use crc
	uint8_t temp = nrf_read_reg(CONFIG);
	
	temp |= (1 << 3);
	
	if(crc_byte){
		temp |= (1 << 2);
	}else{
		temp &= ~(1 << 2);
	}
	nrf_write_reg(CONFIG, temp);
};

void nrf_set_pwr_up(nrf_typedef_power_state state){
	uint8_t temp = nrf_read_reg(CONFIG);
	if(state){
		temp |= (1 << 1);
	}else{
		temp &= ~(1 << 1);
	}
	nrf_write_reg(CONFIG, temp);
};

// without dynamic payload
void nrf_set_payload_width(nrf_typedef_pipe pipe, uint8_t width){
	nrf_write_reg(RX_PW_P0 + pipe, width);
};

void nrf_set_mode(nrf_typedef_mode mode){
	uint8_t temp = nrf_read_reg(CONFIG);
	if(mode){
		temp |= (1 << 0);
	}else{
		temp &= ~(1 << 0);
	}
	nrf_write_reg(CONFIG, temp);
};

void nrf_set_enable_pipe(nrf_typedef_pipe pipe){ ///< dont need disable function
	uint8_t temp = nrf_read_reg(EN_RXADDR);
	temp |= (1<<pipe);
	nrf_write_reg(EN_RXADDR, temp);
};

void nrf_set_retr(void){ ///< disable retr
	nrf_write_reg(SETUP_RETR, 0x00);
};

// layer 3 - operation

void nrf_flush_tx(void){
	uint8_t temp = FLUSH_TX;
	nrf_cs_reset();
	SPI1_Transmit(&temp, 1);
	nrf_cs_set();
};

void nrf_flush_rx(void){
	uint8_t temp = FLUSH_RX;
	nrf_cs_reset();
	SPI1_Transmit(&temp, 1);
	nrf_cs_set();
};

uint8_t nrf_read_payload_width(void){ ///< when using dynamic payload
	uint8_t temp = R_RX_PL_WID;
	uint8_t width;
	
	nrf_cs_reset();
	SPI1_Transmit(&temp, 1);
	SPI1_Receive(&width, 1);
	nrf_cs_set();
	
	return width;
};

void nrf_write_tx_payload(uint8_t *data, uint8_t length){
	uint8_t temp = W_TX_PAYLOAD;
	
	nrf_cs_reset();
	SPI1_Transmit(&temp, 1);
	SPI1_Transmit(data, length);
	nrf_cs_set();
};

void nrf_send_payload(void){
	nrf_ce_set();
	Delay_us(11);
	nrf_ce_reset();
};

uint8_t nrf_get_status(void){
	uint8_t temp = nrf_read_reg(STATUS);
	return temp;
}

void nrf_clear_tx_ds(void){
    nrf_write_reg(STATUS, (1 << 5));
}

void nrf_clear_rx_dr(void){
    nrf_write_reg(STATUS, (1 << 6));
}

void nrf_clear_max_rt(void){
    nrf_write_reg(STATUS, (1 << 4));
}

// for example tx rx (just use pipe0)
void nrf_tx_init(void){
	GPIO_Config(nrf_cs_port,nrf_cs_pin,MODE_OPP);
	GPIO_Config(nrf_ce_port,nrf_ce_pin,MODE_OPP);
	nrf_ce_reset();
	uint8_t address[5] = {0xA0, 0xA0, 0xA0, 0xA0, 0xA1};
	
	nrf_set_power(pwr_0dbm);
	nrf_set_data_rate(dr_2mbps);
	nrf_set_channel(125);
	nrf_set_tx_address(address);
	
	nrf_set_auto_ack(pipe0, 0);
	nrf_set_auto_ack(pipe1, 0);
	
	nrf_set_crc(crc_1_byte);
	
	nrf_set_mode(tx);
	nrf_flush_tx();
	nrf_set_pwr_up(power_up);
	Delay_ms(2);
};

void nrf_rx_init(void){
	GPIO_Config(nrf_cs_port,nrf_cs_pin,MODE_OPP);
	GPIO_Config(nrf_ce_port,nrf_ce_pin,MODE_OPP);
	nrf_ce_reset();
	uint8_t address[5] = {0xA0, 0xA0, 0xA0, 0xA0, 0xA1};
	
	nrf_set_data_rate(dr_2mbps);
	nrf_set_channel(125);
	nrf_set_rx_address(address, pipe0);
	nrf_set_enable_pipe(pipe0);
	
	nrf_set_auto_ack(pipe0, 0);
	nrf_set_auto_ack(pipe1, 0);
	nrf_set_crc(crc_1_byte);
	nrf_set_mode(rx);
	nrf_flush_rx();
	nrf_set_payload_width(pipe0, 5); //5byte: byte 0 - basespeed, byte 1 - x, byte 2 - y, byte 3 - z, byte 4 - state, 1byte for test
	nrf_set_pwr_up(power_up);
	Delay_ms(2);
	nrf_ce_set();
};

void nrf_send_5_byte(uint8_t* data){
	nrf_flush_tx();
	nrf_write_tx_payload(data, 5);
	nrf_send_payload();
};

void nrf_read_payload(uint8_t* data, uint8_t length){ ///< use in interrupt
	uint8_t temp = R_RX_PAYLOAD;
	
	nrf_cs_reset();
	SPI1_Transmit(&temp, 1);
	SPI1_Receive(data, length);
	nrf_cs_set();
	nrf_clear_rx_dr();
	nrf_flush_rx();
};