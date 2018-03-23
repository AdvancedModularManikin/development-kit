#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "spi_proto.h"

//SPI protocol testing

void
test_spi_proto_initialize(void)
{	
	struct spi_state master, slave;
	
	//need function because of some invariants
	spi_proto_initialize(&master);
	spi_proto_initialize(&slave);
	
	//create buffers
	struct spi_packet master_to_slave, slave_to_master;
	
	//prepare message
	int master_write_ret = spi_proto_prep_msg(&master, &master_to_slave, SPI_PACKET_LEN);
	int slave_write_ret = spi_proto_prep_msg(&slave, &slave_to_master, SPI_PACKET_LEN);
	
	//receive messages
	spi_proto_rcv_msg(&slave, &master_to_slave, NULL);
	spi_proto_rcv_msg(&master, &slave_to_master, NULL);
	
	//print out data structures
	print_spi_state(&master);
	print_spi_state(&slave);
}

void
test_spi_proto_one_round(unsigned char *m2s, unsigned char *s2m, int len)
{
	struct spi_state master, slave;
	
	//need function because of some invariants
	spi_proto_initialize(&master);
	spi_proto_initialize(&slave);
	
	
	puts("MASTER after init");
	print_spi_state_full(&master);
	
	//send m2s from master to slave, and vice versa.
	//crash if len > SPI_PACKET_LEN
	assert(len <= SPI_PACKET_LEN);

	//create buffers
	struct spi_packet master_to_slave, slave_to_master;
	
	puts("after creation");
	print_spi_packet(&master_to_slave);
	
	puts("after clear");
	memset(&master_to_slave, 0, sizeof(master_to_slave));
	print_spi_packet(&master_to_slave);
	
	int msend = spi_proto_send_msg(&master, m2s, len);
	int ssend = spi_proto_send_msg(&slave, s2m, len);
	
	puts("MASTER after send");
	print_spi_state_full(&master);
	
	assert(msend != -1);
	assert(ssend != -1);
	
	//prepare message
	int master_write_ret = spi_proto_prep_msg(&master, &master_to_slave, SPI_PACKET_LEN);
	int slave_write_ret = spi_proto_prep_msg(&slave, &slave_to_master, SPI_PACKET_LEN);
	
	puts("after write");
	print_spi_packet(&master_to_slave);
	
	//receive messages
	spi_proto_rcv_msg(&slave, &master_to_slave, NULL);
	spi_proto_rcv_msg(&master, &slave_to_master, NULL);
	
	//extract messages
	//TODO compare with sent messages
	
	puts("after sending");
	print_spi_packet(&master_to_slave);
	print_spi_packet(&slave_to_master);
	
	//print out data structures
	print_spi_state(&master);
	//print_spi_state(&slave);
	
}

int
test_spi_longer(unsigned int rounds)
{
	/*
		initialize
		begin loop
			feed messages into queue until queue full message received
			do a step
			handle results and do output
	*/
	
	struct spi_state master, slave;
	
	//need function because of some invariants
	spi_proto_initialize(&master);
	spi_proto_initialize(&slave);
	
	int N = 10;
	unsigned char m2s[10] = {1,2,3,4,5,6,7,8,9,10};
	unsigned char s2m[10] = {2,3,5,7,11,13,17,19,23, 29};
	while (rounds--) {
		//feed messages into each queue
		while(!spi_proto_send_msg(&master, m2s, N));
		while(!spi_proto_send_msg(&slave, s2m, N));
		
		//CHECK step transmission
		
		//create buffers
		struct spi_packet master_to_slave, slave_to_master;
	
		//prepare message
		int master_write_ret = spi_proto_prep_msg(&master, &master_to_slave, SPI_PACKET_LEN);
		int slave_write_ret = spi_proto_prep_msg(&slave, &slave_to_master, SPI_PACKET_LEN);
	
		//receive messages
		spi_proto_rcv_msg(&slave, &master_to_slave, NULL);
		spi_proto_rcv_msg(&master, &slave_to_master, NULL);
		
		//do output
		print_spi_state(&master);
		puts("------------------");
	}
}

int
test_spi_longer_some_noise(unsigned int rounds, float noise_chance)
{
	/*
		initialize
		begin loop
			feed messages into queue until queue full message received
			do a step
			handle results and do output
	*/
	srand(0x14411441);
	
	struct spi_state master, slave;
	
	//need function because of some invariants
	spi_proto_initialize(&master);
	spi_proto_initialize(&slave);
	
	int N = 10;
	unsigned char m2s[10] = {1,2,3,4,5,6,7,8,9,10};
	unsigned char s2m[10] = {2,3,5,7,11,13,17,19,23, 29};
	while (rounds--) {
		//feed messages into each queue
		while(!spi_proto_send_msg(&master, m2s, N));
		while(!spi_proto_send_msg(&slave, s2m, N));
		
		//CHECK step transmission
		
		//create buffers
		struct spi_packet master_to_slave, slave_to_master;
	
		//prepare message
		int master_write_ret = spi_proto_prep_msg(&master, &master_to_slave, SPI_PACKET_LEN);
		int slave_write_ret = spi_proto_prep_msg(&slave, &slave_to_master, SPI_PACKET_LEN);
	
		int rand_cap = ((float)RAND_MAX) * noise_chance;
		if (rand() < rand_cap) {
			master_to_slave.msg[5] ^= 0xff;
		}
		if (rand() < rand_cap) {
			slave_to_master.msg[5] ^= 0xff;
		}
		//receive messages
		spi_proto_rcv_msg(&slave, &master_to_slave, NULL);
		spi_proto_rcv_msg(&master, &slave_to_master, NULL);
		
		//do output
		print_spi_state(&master);
		puts("------------------");
	}
}

int
main(int argc, char *argv[])
{
	// run the tests
	
	//test_spi_proto_initialize();
	//puts("ayy");
	unsigned char m2s[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a};
	unsigned char s2m[10] = {0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01};
	int n = 10;
	
	/*
	puts("one round start:");
	test_spi_proto_one_round(m2s, s2m, n);
	puts("one round end.");
	*/
	
	//test_spi_longer(9);
	
	test_spi_longer_some_noise(90, 0.1);
}
