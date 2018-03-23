/*
 * spi_proto_slave.h
 *
 *  Created on: Jul 6, 2017
 *      Author: gus
 */

#ifndef SOURCE_SPI_PROTO_SLAVE_HPP_
#define SOURCE_SPI_PROTO_SLAVE_HPP_
#define TRANSFER_SIZE SPI_PACKET_LEN
namespace spi_proto {

//variable-length messages junked
struct slave_spi_proto {
	uint8_t *sendbuf;
	uint8_t *getbuf;
	int buflen;

	struct spi_state proto;
};

uint32_t spi_transactions = 0;
struct slave_spi_proto p;
volatile bool ready;

int
slave_get_message(struct slave_spi_proto &p, unsigned char *buf, int len);
int
slave_send_message(struct slave_spi_proto &p, unsigned char *buf, int len);
//int
//slave_handle_spi_interrupt();
int
slave_do_tick(struct slave_spi_proto &p);
int
slave_spi_proto_rcv_msg(struct slave_spi_proto &p, unsigned char *buf, int len);

void
spi_proto_slave_initialize(struct slave_spi_proto *s);


}

#endif /* SOURCE_SPI_PROTO_SLAVE_HPP_ */
