/*
 * spi_proto_slave.c
 *
 *  Created on: Jul 6, 2017
 *      Author: gus
 */
#include "stdint.h"
//#include <cstring>

#include "spi_proto.h"
#include "spi_proto_slave.h"

namespace spi_proto {

//this is a simple protocol, that doesn't support arbitrary length messages
int
slave_get_message(struct slave_spi_proto &p, unsigned char *buf, int len)
{
	//TODO parses the message and does any required processing

	/* //for debugging SPI (printf is blocking, it will destroy speed)
	for (int i = 0; i < len; i++) {
		PRINTF("%02x ", buf[i]);
	}
	PRINTF("\r\n");
	//*/
	
	return 0;

}

int
slave_send_message(struct slave_spi_proto &p, unsigned char *buf, int len)
{
	return spi_proto_send_msg(&p.proto, buf, len);
}

//do the things the normal interrupt handler did
//int
//slave_handle_spi_interrupt(){}

int
slave_do_tick(struct slave_spi_proto &p)
{
	//handles once-per-message-cycle events such as moving data in and out of buffers.

	spi_proto_prep_msg(&p.proto, p.sendbuf, TRANSFER_SIZE);
	return 0;
}

void
spi_proto_echo(struct spi_packet *pack)
{
	//send the message back
	spi_proto_send_msg(&spi_proto::p.proto, pack->msg, SPI_MSG_PAYLOAD_LEN);
}

int
slave_spi_proto_rcv_msg(struct slave_spi_proto &p, unsigned char *buf, int len)
{
	//parse an spi_packet out of getbuf

	//TODO confirm that any values larger than 16 bits are appropriately encoded to network order (nonlocal)
	if (len < sizeof(struct spi_packet)) return -1;
	struct spi_packet pack = *((struct spi_packet *)buf);

	spi_msg_callback_t msg_callback = spi_proto_echo;
	spi_proto_rcv_msg(&p.proto, &pack, msg_callback);
	return 0;
}

void
spi_proto_slave_initialize(struct slave_spi_proto *s)
{
	//TODO initialize the rest of slave_spi_proto (buffers, length)
	spi_proto_initialize(&s->proto);
}
}
