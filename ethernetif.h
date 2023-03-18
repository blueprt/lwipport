#ifndef __ETHERNETIF_H__
#define __ETHERNETIF_H__

#include "lwip/err.h"
#include "lwip/netif.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "mac.h"

#if (!LAN_8720_USED) && (!KSZ8863_USED) && (!IP175LLF_USED)
#error "Please select a network chip!"
#endif //(!LAN_8720_USED) && (!KSZ8863_USED) && (!IP175LLF_USED)

typedef struct
{
    char netifname[2];
    uint8_t MACaddr[6];
    uint8_t ip4addr[4];
    uint8_t netmask[4];
    uint8_t gw[4];
    uint8_t remoteip4addr[4];
    uint16_t remoteport;
    uint16_t localport;
}Lwip_ConnectPar_Type;

typedef struct
{
    uint8_t PHY_ADDRESS;
    bool AutoNegotiation;
    bool Speed;
    bool DuplexMode;
    uint8_t *MACAddr;
    ETH_DMADESC_TypeDef *ETH_RxDescprt;
    uint32_t DMARxDescriptorsNum;
    uint8_t *RxBuff;
    ETH_DMADESC_TypeDef *ETH_TxDescprt;
    uint32_t DMATxDescriptorsNum;
    uint8_t *TxBuff;
}PHY_InitTypeDef;

typedef struct
{
    void *netif;
    void *phy_dev;
    uint16_t link_status;
    PHY_InitTypeDef PHY_Init;
    Lwip_ConnectPar_Type ETH_Connect_Params;
}ETH_HandleTypeDef;

/* ����һ���ź�������PHY��������ͬ�� */
extern SemaphoreHandle_t PHY_RX_xSemaphore;

void ethernetif_input(void *argument);
err_t ethernetif_init(struct netif *netif);
void ETH_IRQ_CallBack(void);

#endif /*__ETHERNETIF_H__*/


