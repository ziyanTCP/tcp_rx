// Adapted from: https://github.com/DPDK/dpdk/blob/master/examples/skeleton/basicfwd.c
// by Thomas Edwards, Walt Disney Television

/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2010-2015 Intel Corporation
 */

#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <rte_mbuf.h>
#include <rte_udp.h>
#include <rte_ether.h>
#include <stdlib.h>
#include <unistd.h>

#include "/home/ziyan/Dropbox/mylibrary/dpdk_tools/lib/dpdk_utility.h"

uint64_t packet_count = 0;
void exit_stats(int sig)
{
	printf("Caught signal %d\n", sig);
	printf("Total received packets: %lu\n", packet_count);
	exit(0);
}


int main(int argc, char *argv[])
{
	unsigned nb_ports;

    int mac_flag=0,ip_src_flag=0,ip_dst_flag=0;

    signal (SIGINT, exit_stats);

    rte_be32_t ip_src_addr, ip_dst_addr;
    struct rte_ether_addr my_addr; // SRC MAC address of NIC
    struct rte_ether_addr eth_dst_addr;


    dpdk_init(&argc,&argv);


	signal(SIGINT, exit_stats);

    //printf("\nCore %u receiving packets. [Ctrl+C to quit]\n", rte_lcore_id());
    int c=0;
    while ((c = getopt(argc, argv, "m:s:d:h")) != -1)
        switch(c) {
            case 'm':
                eth_dst_addr=mac_string_to_rte_ether_addr(optarg);
                mac_flag=1;
                break;
            case 's':
                ip_src_addr= ip_string_to_rte_be32_t(optarg);
                ip_src_flag=1;
                break;
            case 'd':
                ip_dst_addr = ip_string_to_rte_be32_t(optarg);
                ip_dst_flag=1;
                break;
            case 'h':
                printf("usage -- -m [dst MAC] -s [src IP] -d [dst IP]\n");
                exit(0);
        }

    if(mac_flag==0) {
        fprintf(stderr, "missing -m for destination MAC adress\n");
        exit(1);
    }
    if(ip_src_flag==0) {
        fprintf(stderr, "missing -s for IP source adress\n");
        exit(1);
    }
    if(ip_dst_flag==0) {
        fprintf(stderr, "missing -d for IP destination adress\n");
        exit(1);
    }



    printf("allocate for recv_pkt\n");
    char data[]="hello world this is my tcp stack from song";


    struct tcp_cpu_context ctx;
    init_tcp_cpu_context(&ctx);
    //struct rte_mbuf * pkt= rte_mbuf_raw_alloc( ctx->dpc->pktmbuf_pool);
    struct rte_mbuf *recv_pkt =rte_mbuf_raw_alloc(ctx.dpc->pktmbuf_pool);

	while(1) {
	    //send packet to while
	    // payload memory management header
        rx_packets(&recv_pkt);

        tcp_action(ctx.tcpInstance,recv_pkt);
        //menu(pkt,data, ip_src_addr,ip_dst_addr,my_addr, eth_dst_addr);

        //tcp_action();

/*        prepare_response();
        send_packets();*/
    }
	return 0;
}
