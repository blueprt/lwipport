#include "mac.h"
#include <stdbool.h>
#include <string.h>

static void Reset_ETH_DMA_Reg(void);
static void ETHMAC_Config(void);
static void ETH_MACLocalAddress_Set(uint8_t *Addr);
static void SetMACSmiInterfaceClk(uint32_t SystemCoreClock);
static void Switch_ETH_Tx_Fun(config_stateTypeDef state);
static void Switch_ETH_Tx_Fun(config_stateTypeDef state);
static void ETH_FlushTransmitFIFO(void);

/**
 * @brief 重启以太网外设，并将所有寄存器复位成默认值
 * 
 */
static void Reset_ETH_DMA_Reg(void)
{
    ETHDMA->DMABMRbit.sr = 1;
    while(ETHDMA->DMABMRbit.sr);
}

/**
 * @brief 根据传入参数初始化网络接口，本函数初始化了以下寄存器：
 *          MACCR:MAC控制寄存器
 *          MACFFR:MAC过滤寄存器
 *          MACFCR:MAC流控寄存器
 *          MACIMR:MAC中断控制寄存器
 *          DMABMR:DMA总线模式寄存器
 *          DMAOMR:DMA工作模式寄存器
 * 
 * @param ETH_Config_Para
 */
static void ETHMAC_Config(void)
{
/**
 * @brief Ethernet MAC configuration register
 * 
 */
    ETHMAC->MACCR_bit.cstf = false;
    ETHMAC->MACCR_bit.wd = false;
    ETHMAC->MACCR_bit.jd = false;
    ETHMAC->MACCR_bit.ifg = ETH_INTERFRAMEGAP_96BIT;
    ETHMAC->MACCR_bit.csd = false;
    ETHMAC->MACCR_bit.rod = false;
    ETHMAC->MACCR_bit.lm = false;
#if CHECKSUM_BY_HARDWARE
    ETHMAC->MACCR_bit.ipco = true;
#else
    ETHMAC->MACCR_bit.ipco = false;
#endif /*CHECKSUM_BY_HARDWARE*/
    ETHMAC->MACCR_bit.rd = false;
    ETHMAC->MACCR_bit.apcs = false;
    ETHMAC->MACCR_bit.bl = ETH_BACKOFFLIMIT_10;
    ETHMAC->MACCR_bit.dc = false;

/**
 * @brief Ethernet MAC frame filter register
 * 
 */
    ETHMAC->MACFFRbit.ra = true;
    ETHMAC->MACFFRbit.hpf = false;
    ETHMAC->MACFFRbit.saf = false;
    ETHMAC->MACFFRbit.saif = false;
    ETHMAC->MACFFRbit.pcf = PreventAddressFault;
    ETHMAC->MACFFRbit.bfd = false;
    ETHMAC->MACFFRbit.pam = true;
    ETHMAC->MACFFRbit.daif = false;
    ETHMAC->MACFFRbit.hm = false;
    ETHMAC->MACFFRbit.hu = false;
    ETHMAC->MACFFRbit.pm = false;

/**
 * @brief Ethernet MAC flow control register
 * 
 */
    ETHMAC->MACFCRbit.pt = 0x00;
    ETHMAC->MACFCRbit.zqpd = true;
    ETHMAC->MACFCRbit.plt = ETH_PAUSELOWTHRESHOLD_MINUS4;
    ETHMAC->MACFCRbit.upfd = false;
    ETHMAC->MACFCRbit.rfce = false;
    ETHMAC->MACFCRbit.tfce = false;
    ETHMAC->MACFCRbit.fcb = false;

/**
 * @brief Ethernet MAC interrupt mask register
 * 
 */
    ETHMAC->MACIMRbit.tstim = true;
    ETHMAC->MACIMRbit.pmtim = true;

/**
 * @brief Ethernet DMA bus mode register
 * 
 */
    ETHDMA->DMABMRbit.mb = true;
    ETHDMA->DMABMRbit.aab = true;
    ETHDMA->DMABMRbit.fpm = false;
    ETHDMA->DMABMRbit.usp = true;
    ETHDMA->DMABMRbit.rdp = DMAPBL_32;
    ETHDMA->DMABMRbit.fb = true;
    ETHDMA->DMABMRbit.pm = RxDMAreq_2_TxDMAreq_1;
    ETHDMA->DMABMRbit.pbl = DMAPBL_32;
#if STM32
    ETHDMA->DMABMRbit.edfe = true;
#endif /*STM32*/
    ETHDMA->DMABMRbit.dsl = 0x00;
    ETHDMA->DMABMRbit.da = false;
    
/**
 * @brief Ethernet DMA operation mode register
 * 
 */
    ETHDMA->DMAOMRbit.dtcefd = false;
    ETHDMA->DMAOMRbit.rsf = true;
    ETHDMA->DMAOMRbit.dfrf = false;
    ETHDMA->DMAOMRbit.tsf = true;
    ETHDMA->DMAOMRbit.fef = false;
    ETHDMA->DMAOMRbit.fugf = false;
    ETHDMA->DMAOMRbit.osf = true;

#if ETH_RXINTERRUPT_MODE
    ETHDMA->DMAIERbit.rie = true;
    ETHDMA->DMAIERbit.nise = true;
#endif /*ETH_RXINTERRUPT_MODE*/

}

/**
 * @brief 设置本地MAC地址
 * 
 * @param Addr 
 */
static void ETH_MACLocalAddress_Set(uint8_t *Addr)
{

    ETHMAC->MACA0HRbit.maca0h = ((uint32_t)Addr[5] << 8) | (uint32_t)Addr[4];

    ETHMAC->MACA0LR = ((uint32_t)Addr[3] << 24) | ((uint32_t)Addr[2] << 16) | ((uint32_t)Addr[1] << 8) | Addr[0];

}

/**
 * @brief 设置以太网中SMI接口速率
 * 
 * @param SystemCoreClock 芯片主系统时钟频率，单位:Hz
 */
static void SetMACSmiInterfaceClk(uint32_t SystemCoreClock)
{
    uint8_t bits_value = 0;

    if((SystemCoreClock >= MAC_HCLK_BORDER_20MHZ) && (SystemCoreClock < MAC_HCLK_BORDER_35MHZ))
    {
        bits_value = MAC_SMI_CLK_20_TO_35;
    }
    else if ((SystemCoreClock >= MAC_HCLK_BORDER_35MHZ) && (SystemCoreClock <MAC_HCLK_BORDER_60MHZ))
    {
        bits_value = MAC_SMI_CLK_35_TO_60;
    }
    else if ((SystemCoreClock >= MAC_HCLK_BORDER_60MHZ) && (SystemCoreClock < MAC_HCLK_BORDER_100MHZ))
    {
        bits_value = MAC_SMI_CLK_60_TO_100;
    }
    else if ((SystemCoreClock >= MAC_HCLK_BORDER_100MHZ) && (SystemCoreClock < MAC_HCLK_BORDER_150MHZ))
    {
        bits_value = MAC_SMI_CLK_100_TO_150;
    }
    else if ((SystemCoreClock >= MAC_HCLK_BORDER_150MHZ) && (SystemCoreClock < MAC_HCLK_BORDER_250MHZ))
    {
        bits_value = MAC_SMI_CLK_150_TO_250;
    }
    else if ((SystemCoreClock >= MAC_HCLK_BORDER_250MHZ) && (SystemCoreClock <= MAC_HCLK_BORDER_288MHZ))
    {
        bits_value = MAC_SMI_CLK_250_TO_288;
    }
    ETHMAC->MACMIIARbit.cr = bits_value;
}

/**
 * @brief 开关网络发送功能
 * 
 * @param state     enable ：使能（打开）发送
 *                  disable：失能（关闭）发送
 */
static void Switch_ETH_Tx_Fun(config_stateTypeDef state)
{
    ETHMAC->MACCR_bit.te = state;

    volatile uint32_t tepreg = ETHMAC->MACCR;
    ETH_Delayms(1);
    ETHMAC->MACCR = tepreg;
}

/**
 * @brief 开关网络接收功能
 * 
 * @param state     enable ：使能（打开）接收
 *                  disable：失能（关闭）接收
 */
static void Switch_ETH_Rx_Fun(config_stateTypeDef state)
{
    ETHMAC->MACCR_bit.re = state;

    volatile uint32_t tepreg = ETHMAC->MACCR;
    ETH_Delayms(1);
    ETHMAC->MACCR = tepreg;
}

/**
 * @brief 刷新发送FIFO
 * 
 */
static void ETH_FlushTransmitFIFO(void)
{
    ETHDMA->DMAOMRbit.ftf = true;

    volatile uint32_t tmpreg = ETHDMA->DMAOMR;
    ETH_Delayms(1);
    ETHDMA->DMAOMR = tmpreg;
}

/**
 * @brief 设置mac连接速度和工作模式
 * 
 * @param speed 
 * @param duplex 
 */
void ETH_MAC_Speed_Duplex(bool speed, bool duplex)
{
    ETHMAC->MACCR_bit.dm = speed;
    ETHMAC->MACCR_bit.fes = duplex;
}

/**
 * @brief 启动网络
 * 
 */
void ETH_Start(void)
{
    Switch_ETH_Tx_Fun(enable);

    ETH_FlushTransmitFIFO();

    Switch_ETH_Rx_Fun(enable);

    ETHDMA->DMAOMRbit.st = true;

    ETHDMA->DMAOMRbit.sr = true;

}

/**
 * @brief 停止网络
 * 
 */
void ETH_Stop(void)
{
    ETHDMA->DMAOMRbit.st = false;

    ETHDMA->DMAOMRbit.sr = false;

    Switch_ETH_Rx_Fun(disable);

    ETH_FlushTransmitFIFO();

    Switch_ETH_Tx_Fun(disable);
}

/**
 * @brief 通过SMI接口写PHY寄存器
 * 
 * @param PHY_address 要写的PHY地址
 * @param reg 要写的PHY寄存器地址
 * @param data 要写入的数据
 * @return uint8_t  1:失败，0:成功
 */
uint8_t SMI_PHY_Register_Write(uint8_t PHY_address,uint8_t reg,uint16_t data)
{
    uint32_t timeout = 0;
    ETHMAC->MACMIIDR = data;

    ETHMAC->MACMIIARbit.pa = PHY_address;
    ETHMAC->MACMIIARbit.mr = reg;

    ETHMAC->MACMIIARbit.mw = 1;
    ETHMAC->MACMIIARbit.mb = 1;

    do
    {
        timeout ++;
    } while ((ETHMAC->MACMIIARbit.mb) && (timeout < PHY_TIMEOUT));

    if(timeout == PHY_TIMEOUT)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief 通过SMI接口读PHY寄存器
 * 
 * @param PHY_address 要读的PHY地址
 * @param reg 要读的PHY寄存器地址
 * @param data 要读出的数据指针
 * @return uint8_t  1:失败，0:成功
 */
uint8_t SMI_PHY_Register_Read(uint8_t PHY_address,uint8_t reg,uint16_t *data)
{
    uint32_t timeout = 0;

    ETHMAC->MACMIIARbit.pa = PHY_address;
    ETHMAC->MACMIIARbit.mr = reg;

    ETHMAC->MACMIIARbit.mw = 0;
    ETHMAC->MACMIIARbit.mb = 1;

    do
    {
        timeout ++;
        *data = ETHMAC->MACMIIDR;
    } while ((ETHMAC->MACMIIARbit.mb) && (timeout < PHY_TIMEOUT));

    if(timeout == PHY_TIMEOUT)
    {
        return 1;
    }

    *data = ETHMAC->MACMIIDR;
    return 0;
}

/**
 * @brief 通过SMI接口读写PHY寄存器
 * 
 * @param rdInstruct true = write ; false = read
 * @param PHY_address 要读的PHY地址
 * @param reg 要读的PHY寄存器地址
 * @param rdData 要读出的数据指针
 * @param rdDataLen 要读出的数据length
 * @return uint8_t  1:失败，0:成功
 */
bool SMI_PHY_Register_RW(bool rdInstruct,uint8_t PHY_address,uint8_t reg,uint16_t *rdData,uint32_t rdDataLen)
{
    uint32_t timeout = 0;
    
    ETHMAC->MACMIIARbit.mw = rdInstruct ? 1 : 0;

    
    ETHMAC->MACMIIARbit.pa = PHY_address;
    
    
    while(rdDataLen)
    {
        ETHMAC->MACMIIARbit.mr = reg;
        ETHMAC->MACMIIDR = rdInstruct? *rdData : 0x00;
        
        ETHMAC->MACMIIARbit.mb = 1;
        do
        {
            timeout ++;
            
        } while ((ETHMAC->MACMIIARbit.mb) && (timeout < PHY_TIMEOUT));
        
        if(timeout == PHY_TIMEOUT)
        {
            return true;
        }
        
        if(!rdInstruct)
            *rdData = ETHMAC->MACMIIDR;
        
        reg ++;
        rdData ++;
        rdDataLen --;   
    }
    
    return false;
}

/**
 * @brief 从DMA描述符中取得数据,一次只会取出一包数据，如果进一次中断时接收到两次数据，需要多次取得数据
 * 
 * @return FrameTypeDef 
 */
FrameTypeDef ETH_GetReceivedFrame_IT(void)
{
    ETH_DMADESC_TypeDef *ETH_DMADescprt= (ETH_DMADESC_TypeDef *)ETHDMA->DMACHRDR;
    ETH_DMADESC_TypeDef *ETH_DMADescprt_old= (ETH_DMADESC_TypeDef *)ETHDMA->DMACHRDR;
    FrameTypeDef Frame = {0,0,0};
    uint32_t DescriptSacnCounter = 0;
    
    Frame.SegCount = 1;

    do{
        if(ETH_DMADescprt->RxDESCstatus.own == false)
        {
            if((ETH_DMADescprt->RxDESCstatus.fs == true) && (ETH_DMADescprt->RxDESCstatus.ls == true))
            {
                Frame.LSdescriptor = ETH_DMADescprt;
                Frame.SegCount = 1;
                Frame.FSdescriptor = ETH_DMADescprt;
                Frame.length = ETH_DMADescprt->RxDESCstatus.fl - 4;
                Frame.buffer = (uint8_t *)(Frame.FSdescriptor->buf1addr);
                return Frame;
            }
            else if((ETH_DMADescprt->RxDESCstatus.fs == true) && (ETH_DMADescprt->RxDESCstatus.ls == false))
            {
                Frame.FSdescriptor = ETH_DMADescprt;
                Frame.SegCount = 1;
            }
            else if((ETH_DMADescprt->RxDESCstatus.ls == false) && (ETH_DMADescprt->RxDESCstatus.fs == false))
            {
                Frame.SegCount ++;
            }
            else if((ETH_DMADescprt->RxDESCstatus.fs == false) && (ETH_DMADescprt->RxDESCstatus.ls == true))
            {
                Frame.LSdescriptor = ETH_DMADescprt;
                Frame.SegCount ++;
                Frame.length = ETH_DMADescprt->RxDESCstatus.fl - 4;
                Frame.buffer = (uint8_t *)(Frame.FSdescriptor->buf1addr);
                return Frame;
            }
        }
        else
        {
            ETH_DMADescprt = (ETH_DMADESC_TypeDef *)ETH_DMADescprt->buf2nextdescaddr;
        }
    }while(ETH_DMADescprt != ETH_DMADescprt_old);

    return (Frame);
}

/**
 * @brief 使用DMA将当前数据缓存区数据发送
 * 
 * @param FramLength 
 * @return ETH_error_status 
 *
 */
ETH_error_status ETH_TransmitFrame(uint16_t FrameLength)
{
    ETH_DMADESC_TypeDef *ETH_DMADescprt = (ETH_DMADESC_TypeDef *)ETHDMA->DMACHTDR;

    uint32_t bufcount = 0;
    if(FrameLength == 0)
    {
        return error;
    }
    
    if((ETH_DMADescprt->TxDESCstatus.own) != false)
    {
        return error;
    }
    
    if(FrameLength > ETH_MAX_PACKET_SIZE)
    {
        bufcount = FrameLength / ETH_MAX_PACKET_SIZE;
        if(FrameLength % ETH_MAX_PACKET_SIZE)
            bufcount ++;
    }
    else
        bufcount = 1;
    if(bufcount == 1)
    {
        ETH_DMADescprt->TxDESCConrtolSize.tbs1 = FrameLength;

        ETH_DMADescprt->TxDESCstatus.ls = true;
        ETH_DMADescprt->TxDESCstatus.fs = true;

        ETH_DMADescprt->TxDESCstatus.own = true;
    }
    else
    {
        for(uint32_t i = 0;i < bufcount; i++)
        {
            ETH_DMADescprt->TxDESCstatus.ls = false;
            ETH_DMADescprt->TxDESCstatus.fs = false;
            
            if(i == 0)
                ETH_DMADescprt->TxDESCstatus.fs = true;
            
            ETH_DMADescprt->TxDESCConrtolSize.tbs1 = ETH_MAX_PACKET_SIZE;
            
            if(i == (bufcount - 1))
            {
                ETH_DMADescprt->TxDESCstatus.ls = true;
                ETH_DMADescprt->TxDESCConrtolSize.tbs1 = FrameLength - (bufcount - 1) * ETH_MAX_PACKET_SIZE;
            }
            
            ETH_DMADescprt->TxDESCstatus.own = true;
            
            ETH_DMADescprt = (ETH_DMADESC_TypeDef *)ETH_DMADescprt->buf2nextdescaddr;
        }
    }

    if(ETHDMA->DMASRbit.tbus)
    {
        ETHDMA->DMASRbit.tbus = true;
    }
    if((ETHDMA->DMASRbit.tps == 0x06) || (ETHDMA->DMASRbit.tbus))
    {
        ETHDMA->DMATPDR = 0;
    }

    return success;
}

/**
 * @brief 初始化设置DMA描述符
 * 
 * @param ETH_DMA_tx_rx ETH_DMA_TRANSMIT:发送描述符；ETH_DMA_RECEIVE:接收描述符
 * @param ETH_DMA_Descriptors 描述符表
 * @param buff 发送/接收buffer
 * @param buffer_count 描述符个数
 */
void ETH_DMA_DescriptorsListInit(ETH_DMA_tx_rx_TypeDef ETH_DMA_tx_rx,ETH_DMADESC_TypeDef *ETH_DMA_Descriptors ,uint8_t *buff, uint32_t buffer_count)
{
    ETH_DMADESC_TypeDef *DMA_Descprt = NULL;
    switch(ETH_DMA_tx_rx)
    {
        case ETH_DMA_TRANSMIT:
        {
            for(uint32_t i = 0;i < buffer_count; i++)
            {
                DMA_Descprt = ETH_DMA_Descriptors + i;

                DMA_Descprt->TxDESCstatus.tch = true;

                DMA_Descprt->buf1addr = (uint32_t)(&buff[i * ETH_MAX_PACKET_SIZE]);

#if CHECKSUM_BY_HARDWARE
                DMA_Descprt->TxDESCstatus.cic = ETH_DMATXDESC_CHECKSUMTCPUDPICMPFULL;
#endif /*CHECKSUM_BY_HARDWARE*/

                if(i < (buffer_count - 1))
                {
                    DMA_Descprt->buf2nextdescaddr = (uint32_t)(ETH_DMA_Descriptors + i + 1);
                }
                else
                {
                    DMA_Descprt->buf2nextdescaddr = (uint32_t)ETH_DMA_Descriptors;
                }
            }
            ETHDMA->DMATDLAR = (uint32_t)ETH_DMA_Descriptors;
            break;
        }
        case ETH_DMA_RECEIVE:
        {
            for(uint32_t i = 0;i < buffer_count;i++)
            {
                DMA_Descprt = ETH_DMA_Descriptors + i;

                DMA_Descprt->RxDESCstatus.own = true;

                DMA_Descprt->RxDESCConrtolSize.rch = true;
                DMA_Descprt->RxDESCConrtolSize.rbs1 = ETH_MAX_PACKET_SIZE;

                DMA_Descprt->buf1addr = (uint32_t)(&buff[i * ETH_MAX_PACKET_SIZE]);

#if ETH_RXINTERRUPT_MODE
                DMA_Descprt->RxDESCConrtolSize.dic = false;
#else
                DMA_Descprt->RxDESCConrtolSize.dic = true;
#endif /*ETH_RXINTERRUPT_MODE*/

                if(i < (buffer_count - 1))
                {
                    DMA_Descprt->buf2nextdescaddr = (uint32_t)(ETH_DMA_Descriptors + i + 1);
                }
                else
                {
                    DMA_Descprt->buf2nextdescaddr = (uint32_t)ETH_DMA_Descriptors;
                }
            }
            ETHDMA->DMARDLAR =  (uint32_t)ETH_DMA_Descriptors;
            break;
        }
        default:
            break;
    }
}

/**
 * @brief 以太网初始化
 * 
 * @param MACAddr 
 * @param speed 
 * @param duplex 
 * @param SysCoreClock 
 * @param ETH_MspInit 
 * @return ETH_error_status 
 */
ETH_error_status ETH_Init(uint8_t *MACAddr,bool speed,bool duplex,uint32_t SysCoreClock,void (*ETH_MspInit)(void))
{
    uint16_t phyreg = 0,timeout = 0;

    if(ETH_MspInit != NULL)
        ETH_MspInit();

    Reset_ETH_DMA_Reg();

    SetMACSmiInterfaceClk(SysCoreClock);

    ETH_MACLocalAddress_Set(MACAddr);

    ETH_MAC_Speed_Duplex(speed,duplex);

    ETHMAC_Config();

    return success;
}

void ETH_Delayms(uint32_t ms)
{
    while( ms -- )
    {
        for(uint32_t i = 0;i <=ms ;i++)
        {
        }
    }
}

