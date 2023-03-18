/**
 * @file
 * Ethernet Interface Skeleton
 *
 */

/*
 * This file is a skeleton for developing Ethernet network interface
 * drivers for lwIP. Add code to the low_level functions and do a
 * search-and-replace for the word "ethernetif" to replace it with
 * something that better describes your network interface.
 */
#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include "lwip/tcpip.h"
#include <lwip/stats.h>
#include <lwip/snmp.h>
#include "netif/etharp.h"
#include "lwip/err.h"
#include "ethernetif.h"

#include "RMII.h"
#include "mac.h"

#if LAN_8720_USED
    #include "lan8720.h"
#elif KSZ8863_USED
    #include "ksz8863.h"
    #include "spi.h"
#elif IP175LLF_USED
    #include "IP175LLF.h"
#endif // LAN_8720_USED

#include <string.h>

SemaphoreHandle_t PHY_RX_xSemaphore;

#define PHY_PRIO        30

#define PHY_STK_SIZE        2048

TaskHandle_t PHY_Handler;

static void low_level_init(struct netif *netif)
{
    ETH_HandleTypeDef *ETH_Handle = (ETH_HandleTypeDef *)netif->state;

    struct netif *xnetif = (struct netif *)ETH_Handle->netif;

#if LAN_8720_USED
    struct lan8720 *phy_dev = (struct lan8720 *)ETH_Handle->phy_dev;
#elif KSZ8863_USED
    struct ksz8863 *phy_dev = (struct ksz8863 *)ETH_Handle->phy_dev;
#elif IP175LLF_USED
    struct IP175LLF *phy_dev = (struct IP175LLF *)ETH_Handle->phy_dev;
#endif // LAN_8720_USED

    ETH_error_status ETH_status= ETH_Init(ETH_Handle->PHY_Init.MACAddr,ETH_Handle->PHY_Init.Speed,ETH_Handle->PHY_Init.DuplexMode,system_core_clock,RMII_Interface_Init);

#if LAN_8720_USED
    lan8720(phy_dev,ETH_Handle->PHY_Init.PHY_ADDRESS,hw_reset,SMI_PHY_Register_Write,SMI_PHY_Register_Read);

    bool status = 0;
    if(!(phy_dev->get_link_status(phy_dev,&status)))
    {
        if(status == 1)
        {
            if(!(phy_dev->Restart_AN(phy_dev,&ETH_Handle->PHY_Init.Speed,&ETH_Handle->PHY_Init.DuplexMode)))
            {
                ETH_MAC_Speed_Duplex(ETH_Handle->PHY_Init.Speed,ETH_Handle->PHY_Init.DuplexMode);
            }
            else
            {
                ETH_MAC_Speed_Duplex(1,1);
            }
            netif_set_flags(xnetif,NETIF_FLAG_LINK_UP);
        }
    }
#elif KSZ8863_USED

    ksz8863(phy_dev,hw_reset,NULL,SPI2_Init,hw_w,hw_r);

    if(phy_dev->set_port_def_speed_duplex(phy_dev,ksz8863_port3,1,1))
        return;
    if(phy_dev->get_port_speed_duplex(phy_dev,ksz8863_port3,&ETH_Handle->PHY_Init.Speed,&ETH_Handle->PHY_Init.DuplexMode))
        return;

    if(phy_dev->turn_on_off_TXQ_Split(phy_dev,ksz8863_port1,1))
        return;
    if(phy_dev->turn_on_off_TXQ_Split(phy_dev,ksz8863_port2,1))
        return;
    if(phy_dev->turn_on_off_TXQ_Split(phy_dev,ksz8863_port3,1))
        return;

    if(phy_dev->turn_on_off_802_1p_prio(phy_dev,ksz8863_port1,1))
        return;
    if(phy_dev->turn_on_off_802_1p_prio(phy_dev,ksz8863_port2,1))
        return;
    if(phy_dev->turn_on_off_802_1p_prio(phy_dev,ksz8863_port3,1))
        return;

    ETH_MAC_Speed_Duplex(ETH_Handle->PHY_Init.Speed,ETH_Handle->PHY_Init.DuplexMode);
    
    netif_set_flags(xnetif,NETIF_FLAG_LINK_UP);

#elif IP175LLF_USED

    IP175LLF_Init(phy_dev,SMI_PHY_Register_RW,NULL,hw_reset);

    IP175LLF_PortPowerDown(phy_dev,IP175LLF_Port0,true);
    IP175LLF_PortPowerDown(phy_dev,IP175LLF_Port2,true);

    IP175LLF_SetPHYSpeedDuplex(phy_dev,IP175LLF_Port1,true,true);
    IP175LLF_SetPHYSpeedDuplex(phy_dev,IP175LLF_Port3,true,true);

    IP175LLF_NwayEn(phy_dev,IP175LLF_Port1,true);
    IP175LLF_NwayEn(phy_dev,IP175LLF_Port3,true);

    IP175LLF_SetQOS_COSEn(phy_dev,0x02,true);
    IP175LLF_SetQOS_COSEn(phy_dev,0x08,true);

    IP175LLF_SetQOS_QueueScheduling(phy_dev,0x02,0x03);
    IP175LLF_SetQOS_QueueScheduling(phy_dev,0x08,0x03);

    IP175LLF_SetQOS_VLANPrioMap(phy_dev,0x00,0x00);
    IP175LLF_SetQOS_VLANPrioMap(phy_dev,0x01,0x00);
    IP175LLF_SetQOS_VLANPrioMap(phy_dev,0x02,0x01);
    IP175LLF_SetQOS_VLANPrioMap(phy_dev,0x03,0x01);
    IP175LLF_SetQOS_VLANPrioMap(phy_dev,0x04,0x02);
    IP175LLF_SetQOS_VLANPrioMap(phy_dev,0x05,0x02);
    IP175LLF_SetQOS_VLANPrioMap(phy_dev,0x06,0x03);
    IP175LLF_SetQOS_VLANPrioMap(phy_dev,0x07,0x03);

    IP175LLF_ReadPHYSpeedDuplexStatus(phy_dev,IP175LLF_Port5,&ETH_Handle->PHY_Init.Speed,&ETH_Handle->PHY_Init.DuplexMode);
    ETH_MAC_Speed_Duplex(ETH_Handle->PHY_Init.Speed,ETH_Handle->PHY_Init.DuplexMode);
    netif_set_flags(xnetif,NETIF_FLAG_LINK_UP);
#endif // LAN_8720_USED

    ETH_DMA_DescriptorsListInit(ETH_DMA_TRANSMIT,\
                                ETH_Handle->PHY_Init.ETH_TxDescprt,\
                                ETH_Handle->PHY_Init.TxBuff,\
                                ETH_Handle->PHY_Init.DMATxDescriptorsNum);

    ETH_DMA_DescriptorsListInit(ETH_DMA_RECEIVE,\
                                ETH_Handle->PHY_Init.ETH_RxDescprt,\
                                ETH_Handle->PHY_Init.RxBuff,\
                                ETH_Handle->PHY_Init.DMARxDescriptorsNum);

    /* set MAC hardware address length */
    netif->hwaddr_len = ETHARP_HWADDR_LEN;

    /* set MAC hardware address */
    netif->hwaddr[0] = ETH_Handle->ETH_Connect_Params.MACaddr[0];
    netif->hwaddr[1] = ETH_Handle->ETH_Connect_Params.MACaddr[1];
    netif->hwaddr[2] = ETH_Handle->ETH_Connect_Params.MACaddr[2];
    netif->hwaddr[3] = ETH_Handle->ETH_Connect_Params.MACaddr[3];
    netif->hwaddr[4] = ETH_Handle->ETH_Connect_Params.MACaddr[4];
    netif->hwaddr[5] = ETH_Handle->ETH_Connect_Params.MACaddr[5];

    /* maximum transfer unit */
    netif->mtu = 1500;

    /* device capabilities */
    /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;

    /* ����һ���ź������ڽ������ݱ���  ��ʼ���ź���20 */
    if(PHY_RX_xSemaphore == NULL)
    {
        PHY_RX_xSemaphore = xSemaphoreCreateCounting(20,0);
    }
    /* ������̫���ӿ���*/
    /* ����PHY���� */
    xTaskCreate((TaskFunction_t )ethernetif_input,
              (const char*    )"ETH_Input",
              (uint16_t       )PHY_STK_SIZE,
              (void*          )netif,
              (UBaseType_t    )PHY_PRIO,
              (TaskHandle_t*  )&PHY_Handler);

    /* Enable MAC and DMA transmission and reception */
    ETH_Start();
}

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
    struct pbuf *q;
    err_t errval;

    ETH_DMADESC_TypeDef *Descprt = (ETH_DMADESC_TypeDef *)ETHDMA->DMACHTDR;
    ETH_DMADESC_TypeDef *Descprt_old = (ETH_DMADESC_TypeDef *)ETHDMA->DMACHTDR;
    uint8_t *buffer =  (uint8_t *)ETHDMA->DMACHTBAR;
    uint32_t framelength = 0;
    uint32_t bufferoffset = 0;
    uint32_t byteslefttocopy = 0;
    uint32_t payloadoffset = 0;
    
    {
        while((Descprt->TxDESCstatus.own != false))
        {
            Descprt = (ETH_DMADESC_TypeDef *)Descprt-> buf2nextdescaddr;
            if(Descprt_old == Descprt)
                break;
        }

        for(q = p;q != NULL; q = q->next)
        {
            if(Descprt->TxDESCstatus.own != false)
            {
                errval = ERR_USE;
                goto error;
            }

            byteslefttocopy = q->len;
            payloadoffset = 0;
            
            while((byteslefttocopy + bufferoffset) > ETH_MAX_PACKET_SIZE)
            {
                memcpy((uint8_t *)((uint8_t *)buffer + bufferoffset), (uint8_t *)((uint8_t *)q->payload + payloadoffset), (ETH_MAX_PACKET_SIZE - bufferoffset));
                
                Descprt = (ETH_DMADESC_TypeDef *)Descprt->buf2nextdescaddr;
                
                if(Descprt->TxDESCstatus.own != false)
                {
                    errval = ERR_USE;
                    goto error;
                }
                
                buffer = (uint8_t *)Descprt->buf1addr;
                
                byteslefttocopy = byteslefttocopy - (ETH_MAX_PACKET_SIZE - bufferoffset);
                payloadoffset = payloadoffset + (ETH_MAX_PACKET_SIZE - bufferoffset);
                framelength = framelength + (ETH_MAX_PACKET_SIZE - bufferoffset);
                bufferoffset = 0;
            }
            memcpy((uint8_t *)((uint8_t *)buffer + bufferoffset), (uint8_t *)((uint8_t *)q->payload + payloadoffset), byteslefttocopy);
            bufferoffset = bufferoffset + byteslefttocopy;
            framelength = framelength + byteslefttocopy;
        }

        ETH_TransmitFrame(framelength);
        
        errval = ERR_OK;
    }

//  xSemaphoreGive(PHY_TX_xSemaphore);
    return ERR_OK;

error:
    if(ETHDMA->DMASRbit.tus != false)
    {
        ETHDMA->DMASRbit.tus = true;

        ETHDMA->DMATPDR = 0;
    }
//  xSemaphoreGive(PHY_TX_xSemaphore);
    return errval;
}

/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
static struct pbuf *low_level_input(struct netif *netif)
{
    struct pbuf *p = NULL;
    struct pbuf *q = NULL;
    uint16_t len = 0;
    uint8_t *buffer;
    ETH_DMADESC_TypeDef *dmarxdesc;
    uint32_t bufferoffset = 0;
    uint32_t payloadoffset = 0;
    uint32_t byteslefttocopy = 0;
    uint32_t i = 0;
    FrameTypeDef frame;

    frame = ETH_GetReceivedFrame_IT();
    /* Obtain the size of the packet and put it into the "len"
        variable. */
    len = frame.length;

    buffer = (uint8_t *)frame.buffer;

    if(len > 0)
    {
    /* We allocate a pbuf chain of pbufs from the pool. */
        p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
    }
    
    if (p != NULL)
    {
        dmarxdesc = frame.FSdescriptor;
        bufferoffset = 0;
        for(q = p;q != NULL;q = q->next)
        {
            byteslefttocopy = q->len;
            payloadoffset = 0;
            
            while ((byteslefttocopy + bufferoffset) > ETH_MAX_PACKET_SIZE)
            {
                /* Copy data to pbuf */
                memcpy((uint8_t *)((uint8_t *)q->payload + payloadoffset), (uint8_t *)((uint8_t *)buffer + bufferoffset), (ETH_MAX_PACKET_SIZE - bufferoffset));

                /* Point to next descriptor */
                dmarxdesc = (ETH_DMADESC_TypeDef *)(dmarxdesc->buf2nextdescaddr);
                buffer = (uint8_t *)(dmarxdesc->buf1addr);

                byteslefttocopy = byteslefttocopy - (ETH_MAX_PACKET_SIZE - bufferoffset);
                payloadoffset = payloadoffset + (ETH_MAX_PACKET_SIZE - bufferoffset);
                bufferoffset = 0;
            }
            /* Copy remaining data in pbuf */
            memcpy((uint8_t *)((uint8_t *)q->payload + payloadoffset), (uint8_t *)((uint8_t *)buffer + bufferoffset), byteslefttocopy);
            bufferoffset = bufferoffset + byteslefttocopy;
        }
    }

    dmarxdesc = frame.FSdescriptor;
    
    for(i = 0;i < frame.SegCount;i ++)
    {
        dmarxdesc->RxDESCstatus.own = true;
        dmarxdesc = (ETH_DMADESC_TypeDef *)(dmarxdesc->buf2nextdescaddr);
    }
    
    if(ETHDMA->DMASRbit.rbus != false)
    {
        ETHDMA->DMASRbit.rbus = true;

        ETHDMA->DMARPDR = 0;
    }

    return p;
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
void ethernetif_input(void *argument)
{
    struct pbuf *p;
    struct netif *netif = (struct netif *) argument;

    for (;;)
    {
        if (xSemaphoreTake(PHY_RX_xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            do
            {
                LOCK_TCPIP_CORE();
                p = low_level_input(netif);
                if (p != NULL)
                {
                    if (netif->input(p, netif) != ERR_OK)
                        pbuf_free(p);
                }
                UNLOCK_TCPIP_CORE();

            } while (p != NULL);
        }
    }
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t ethernetif_init(struct netif *netif)
{
    LWIP_ASSERT("netif != NULL", (netif != NULL));

    ETH_HandleTypeDef *ETHHandle = (ETH_HandleTypeDef *)netif->state;

#if LWIP_NETIF_HOSTNAME
    /* Initialize interface hostname */
    netif->hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */

    /*
    * Initialize the snmp variables and counters inside the struct netif.
    * The last argument should be replaced with your link speed, in units
    * of bits per second.
    */
    // NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, 100000000);

    netif->name[0] = ETHHandle->ETH_Connect_Params.netifname[0];
    netif->name[1] = ETHHandle->ETH_Connect_Params.netifname[1];
    /* We directly use etharp_output() here to save a function call.
    * You can instead declare your own function an call etharp_output()
    * from it if you have to do some checks before sending (e.g. if link
    * is available...) */
    netif->output = etharp_output;
    netif->linkoutput = low_level_output;

    /* initialize the hardware */
    low_level_init(netif);

    return ERR_OK;
}

__attribute((weak)) err_enum_t lwip_hook_unknown_eth_protocol(struct pbuf *pbuf, struct netif *netif)
{
    return -1;
}

void ETH_IRQ_CallBack(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    xSemaphoreGiveFromISR(PHY_RX_xSemaphore, &xHigherPriorityTaskWoken);

    /* clear the eth dma rx it pending bits */
    ETHDMA->DMASRbit.rs = true;
    ETHDMA->DMASRbit.nis = true;

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    
}

