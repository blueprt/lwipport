/**
  ******************************************************************************
  * @file    lwipopts.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    31-July-2013
  * @brief   lwIP Options Configuration.
  *          This file is based on Utilities\lwip_v1.4.1\src\include\lwip\opt.h 
  *          and contains the lwIP configuration for the STM32F4x7 demonstration.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

/* FreeRTOS??? */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "FreeRTOSConfig.h"

#define LWIP_STATS_DISPLAY      1

#define ETHARP_TRUST_IP_MAC     0
#define IP_REASSEMBLY           0
#define IP_FRAG                 0
#define ARP_QUEUEING            0
#define TCP_LISTEN_BACKLOG      1

/**
 * NO_SYS==1: Provides VERY minimal functionality. Otherwise,
 * use lwIP facilities.
 */
#define NO_SYS                  0
#define LWIP_SOCKET                (NO_SYS==0)
#define LWIP_NETCONN               (NO_SYS==0)
#define LWIP_NETIF_API             (NO_SYS==0)

/**
 * SYS_LIGHTWEIGHT_PROT==1: if you want inter-task protection for certain
 * critical regions during buffer allocation, deallocation and memory
 * allocation and deallocation.
 */
#define SYS_LIGHTWEIGHT_PROT     (NO_SYS==0)

#define LWIP_SINGLE_NETIF       0

/* ---------- Memory options ---------- */
/* MEM_ALIGNMENT: should be set to the alignment of the CPU for which
   lwIP is compiled. 4 byte alignment -> define MEM_ALIGNMENT to 4, 2
   byte alignment -> define MEM_ALIGNMENT to 2. */
#define MEM_ALIGNMENT           4

/* MEM_SIZE: the size of the heap memory. If the application will send
a lot of data that needs to be copied, this should be set high. */
#define MEM_SIZE                (5*1024)

/* MEMP_NUM_PBUF: the number of memp struct pbufs. If the application
   sends a lot of data out of ROM (or other static memory), this
   should be set high. */
#define MEMP_NUM_PBUF           25
/* MEMP_NUM_UDP_PCB: the number of UDP protocol control blocks. One
   per active UDP "connection". */
#define MEMP_NUM_UDP_PCB        6
/* MEMP_NUM_TCP_PCB: the number of simulatenously active TCP
   connections. */
#define MEMP_NUM_TCP_PCB        10
/* MEMP_NUM_TCP_PCB_LISTEN: the number of listening TCP
   connections. */
#define MEMP_NUM_TCP_PCB_LISTEN 5
/* MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP
   segments. */
#define MEMP_NUM_TCP_SEG        20
/* MEMP_NUM_SYS_TIMEOUT: the number of simulateously active
   timeouts. */
#define MEMP_NUM_SYS_TIMEOUT    10

/* ---------- Pbuf options ---------- */
/* PBUF_POOL_SIZE: the number of buffers in the pbuf pool. */
#define PBUF_POOL_SIZE          20

/* PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. */
#define PBUF_POOL_BUFSIZE       1536

/* ---------- TCP options ---------- */
#define LWIP_TCP                1
#define TCP_TTL                 255

/* Controls if TCP should queue segments that arrive out of
   order. Define to 0 if your device is low on memory. */
#define TCP_QUEUE_OOSEQ         0

/* TCP Maximum segment size. */
#define TCP_MSS                 (1500 - 40)    /* TCP_MSS = (Ethernet MTU - IP header size - TCP header size) */

/* TCP sender buffer space (bytes). */
#define TCP_SND_BUF             (2*TCP_MSS)

/*  TCP_SND_QUEUELEN: TCP sender buffer space (pbufs). This must be at least
  as much as (2 * TCP_SND_BUF/TCP_MSS) for things to work. */

#define TCP_SND_QUEUELEN        (4* TCP_SND_BUF/TCP_MSS)

/* TCP receive window. */
#define TCP_WND                 (2*TCP_MSS)

/* ---------- ICMP options ---------- */
#define LWIP_ICMP                       1

/* ---------- DHCP options ---------- */
/* Define LWIP_DHCP to 1 if you want DHCP configuration of
   interfaces. DHCP is not implemented in lwIP 0.5.1, however, so
   turning this on does currently not work. */
#define LWIP_DHCP               0

/* ---------- UDP options ---------- */
#define LWIP_UDP                1
#define UDP_TTL                 255

/* ---------- Statistics options ---------- */
//#define LWIP_STATS 0
#define LWIP_PROVIDE_ERRNO 1

/* ---------- link callback options ---------- */
/* LWIP_NETIF_LINK_CALLBACK==1: Support a callback function from an interface
 * whenever the link changes (i.e., link down)
 */
#define LWIP_NETIF_LINK_CALLBACK        1

/*
   --------------------------------------
   ---------- Checksum options ----------
   --------------------------------------
*/

/* 
The STM32F4x7 allows computing and verifying the IP, UDP, TCP and ICMP checksums by hardware:
 - To use this feature let the following define uncommented.
 - To disable it and process by CPU comment the  the checksum.
*/
#define CHECKSUM_BY_HARDWARE        1

#ifdef CHECKSUM_BY_HARDWARE
  /* CHECKSUM_GEN_IP==0: Generate checksums by hardware for outgoing IP packets.*/
  #define CHECKSUM_GEN_IP                 0
  /* CHECKSUM_GEN_UDP==0: Generate checksums by hardware for outgoing UDP packets.*/
  #define CHECKSUM_GEN_UDP                0
  /* CHECKSUM_GEN_TCP==0: Generate checksums by hardware for outgoing TCP packets.*/
  #define CHECKSUM_GEN_TCP                0 
  /* CHECKSUM_CHECK_IP==0: Check checksums by hardware for incoming IP packets.*/
  #define CHECKSUM_CHECK_IP               0
  /* CHECKSUM_CHECK_UDP==0: Check checksums by hardware for incoming UDP packets.*/
  #define CHECKSUM_CHECK_UDP              0
  /* CHECKSUM_CHECK_TCP==0: Check checksums by hardware for incoming TCP packets.*/
  #define CHECKSUM_CHECK_TCP              0
  /* CHECKSUM_CHECK_ICMP==0: Check checksums by hardware for incoming ICMP packets.*/
//  #define CHECKSUM_CHECK_ICMP             0
  
  #define CHECKSUM_GEN_ICMP               0
#else
  /* CHECKSUM_GEN_IP==1: Generate checksums in software for outgoing IP packets.*/
  #define CHECKSUM_GEN_IP                 1
  /* CHECKSUM_GEN_UDP==1: Generate checksums in software for outgoing UDP packets.*/
  #define CHECKSUM_GEN_UDP                1
  /* CHECKSUM_GEN_TCP==1: Generate checksums in software for outgoing TCP packets.*/
  #define CHECKSUM_GEN_TCP                1
  /* CHECKSUM_CHECK_IP==1: Check checksums in software for incoming IP packets.*/
  #define CHECKSUM_CHECK_IP               1
  /* CHECKSUM_CHECK_UDP==1: Check checksums in software for incoming UDP packets.*/
  #define CHECKSUM_CHECK_UDP              1
  /* CHECKSUM_CHECK_TCP==1: Check checksums in software for incoming TCP packets.*/
  #define CHECKSUM_CHECK_TCP              1
  /* CHECKSUM_CHECK_ICMP==1: Check checksums by hardware for incoming ICMP packets.*/
  #define CHECKSUM_GEN_ICMP               1
#endif

/*
   -----------------------------------
   ---------- DEBUG options ----------
   -----------------------------------
*/
//#define UDP_DEBUG              LWIP_DBG_ON
//#define SOCKETS_DEBUG             LWIP_DBG_ON

#define LWIP_DEBUG                      0

#if LWIP_DEBUG
#define ETHARP_DEBUG             LWIP_DBG_ON
#define NETIF_DEBUG              LWIP_DBG_ON
#define PBUF_DEBUG               LWIP_DBG_ON
#define API_MSG_DEBUG               LWIP_DBG_ON
#define SOCKETS_DEBUG               LWIP_DBG_ON
#define ICMP_DEBUG               LWIP_DBG_ON
#define IGMP_DEBUG               LWIP_DBG_ON
#define INET_DEBUG               LWIP_DBG_ON

#define IP_DEBUG              LWIP_DBG_ON
#define IP_REASS_DEBUG              LWIP_DBG_ON
#define RAW_DEBUG             LWIP_DBG_ON
//#define MEM_DEBUG              LWIP_DBG_ON
//#define MEMP_DEBUG             LWIP_DBG_ON
#define SYS_DEBUG             LWIP_DBG_ON

#//define TIMERS_DEBUG              LWIP_DBG_ON
#define TCP_DEBUG             LWIP_DBG_ON
#define TCP_INPUT_DEBUG             LWIP_DBG_ON
#define TCP_FR_DEBUG             LWIP_DBG_ON
#define TCP_RTO_DEBUG               LWIP_DBG_ON
#define TCP_CWND_DEBUG              LWIP_DBG_ON

#define TCP_WND_DEBUG               LWIP_DBG_ON
#define TCP_OUTPUT_DEBUG               LWIP_DBG_ON
#define TCP_RST_DEBUG               LWIP_DBG_ON
#define TCP_QLEN_DEBUG              LWIP_DBG_ON
#define UDP_DEBUG             LWIP_DBG_ON
#define TCPIP_DEBUG              LWIP_DBG_ON

#define SLIP_DEBUG               LWIP_DBG_ON
#define DHCP_DEBUG               LWIP_DBG_ON
#define AUTOIP_DEBUG             LWIP_DBG_ON
#define DNS_DEBUG             LWIP_DBG_ON
#define IP6_DEBUG             LWIP_DBG_ON
#define DHCP6_DEBUG              LWIP_DBG_ON

#endif /*LWIP_DEBUG*/
/*
   ---------------------------------
   ---------- OS options ----------
   ---------------------------------
*/

#define TCPIP_THREAD_NAME              "TCP/IP"
#define TCPIP_THREAD_STACKSIZE          1000
#define TCPIP_MBOX_SIZE                 5
#define DEFAULT_UDP_RECVMBOX_SIZE       2000
#define DEFAULT_TCP_RECVMBOX_SIZE       2000
#define DEFAULT_ACCEPTMBOX_SIZE         2000
#define DEFAULT_THREAD_STACKSIZE        500
#define TCPIP_THREAD_PRIO               24
//#define LWIP_COMPAT_MUTEX               1



#define LWIP_FREERTOS_THREAD_STACKSIZE_IS_STACKWORDS  1  /**/
#define LWIP_FREERTOS_SYS_ARCH_PROTECT_USES_MUTEX     1
#define LWIP_FREERTOS_SYS_ARCH_PROTECT_SANITY_CHECK      1
#define LWIP_FREERTOS_CHECK_QUEUE_EMPTY_ON_FREE       1

/*
   ---------------------------------
   ---------- Core Lock options ----------
   ---------------------------------
*/
#define LWIP_FREERTOS_CHECK_CORE_LOCKING           1
#define LWIP_TCPIP_CORE_LOCKING                    1
//#define LWIP_COMPAT_MUTEX_ALLOWED                1

#if !defined(NO_SYS) || !NO_SYS /* default is 0 */
void sys_check_core_locking(void);
#define LWIP_ASSERT_CORE_LOCKED()  sys_check_core_locking()
void sys_mark_tcpip_thread(void);
#define LWIP_MARK_TCPIP_THREAD()   sys_mark_tcpip_thread()

#if !defined(LWIP_TCPIP_CORE_LOCKING) || LWIP_TCPIP_CORE_LOCKING /* default is 1 */
void sys_lock_tcpip_core(void);
#define LOCK_TCPIP_CORE()          sys_lock_tcpip_core()
void sys_unlock_tcpip_core(void);
#define UNLOCK_TCPIP_CORE()        sys_unlock_tcpip_core()
#endif
#endif

/*----- Default Value for SO_REUSE: 0 ---*/
#define SO_REUSE 1
/*----- Default Value for LWIP_SNMP: 0 ---*/
#define LWIP_SNMP 1
/*----- Default Value for SNMP_USE_NETCONN: 0 ---*/
#define SNMP_USE_NETCONN 1
/*----- Default Value for SNMP_USE_RAW: 1 ---*/
#define SNMP_USE_RAW 0

#define MIB2_STATS                              1

#define LWIP_HOOK_FILENAME "lwip_hooks.h"
#define LWIP_HOOK_UNKNOWN_ETH_PROTOCOL lwip_hook_unknown_eth_protocol

#endif /* __LWIPOPTS_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


