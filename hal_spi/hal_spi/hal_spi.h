/*
 * hal_spi.h
 *
 * Created: 11/15/2019 7:16:07 PM
 *  Author: H
 */ 


#ifndef HAL_SPI_H_
#define HAL_SPI_H_

#include "common.h"

typedef enum
{
	SPI_SLAVE,
	SPI_MASTER
}enum_spi_status_t;

typedef enum
{
	SPI_INT_OFF,
	SPI_INT_ON
}enum_spi_int_state_t;

typedef enum
{
	SPI_MSB_TRANS_FIRST,
	SPI_LSB_TRANS_FIRST
}enum_spi_data_order_t;

typedef enum
{
	SPI_TRANS_AT_RISING,
	SPI_TRANS_AT_FALLING
}enum_spi_operating_edge_t;

typedef enum
{
	SPI_HIGH_EDGE,
	SPI_LOW_EDGE
}enum_spi_polarity_edge_t;

typedef enum
{
	CLK_DIV_4 = 0b00,
	CLK_DIV_16 = 0b01,
	CLK_DIV_64 = 0b10,
	CLK_DIV_128 = 0b11,
}enum_spi_clock_select_t;

typedef enum
{
	SPI_DOUBLE_SPEED_OFF,
	SPI_DOUBLE_SPEED_ON 
}enum_spi_double_speed_t;

typedef struct
{
	enum_spi_status_t spi_state;
	enum_spi_int_state_t int_state;
	enum_spi_data_order_t data_order;
	enum_spi_operating_edge_t operating_edge;
	enum_spi_polarity_edge_t sampling_edge;
	enum_spi_clock_select_t spi_clock;
	enum_spi_double_speed_t double_speed;
	void(*spi_cb_func)(void);
}gcfg_hal_spi_t;



ecore_s8 hal_spi_init(gcfg_hal_spi_t* obj);
ecore_s8 hal_spi_trans(ecore_u16 data);
ecore_s8 hal_spi_receive(ecore_u16* data);
ecore_s8 hal_spi_deinit();

#endif /* HAL_SPI_H_ */