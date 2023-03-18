/**
 * @file IP175LLF.c
 * @author chentao
 * @brief 
 * @version 0.1 初稿
 * @date 2023-03-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "IP175LLF.h"

/**
 * @brief IP175LLF初始化,同时将IP175LLF端口设置成PHY+RMII接口
 * 
 * @param IP175LLF 
 * @param hw_rw 硬件SMI读写函数，用户实现
 * bool (*hw_rw)(bool rdInstruct,uint8_t PHY_addr,uint8_t reg_addr,uint16_t *rdData,uint32_t rdLen)
 * rdInstruct：false = 读；true = 写
 * PHY_addr：PHY ID
 * reg_addr:要读写的寄存器地址
 * rdData：要读写的数据地址
 * rdLen：读写的数据长度
 * 
 * @param hw_init 硬件初始化，可以传入NULL
 * @param hw_reset 硬件重置IP175LLF函数，应该是控制IP175LLF的reset引脚
 * @return true 初始化成功
 * @return false 初始化失败，无法读取chipID等
 */
bool IP175LLF_Init( IP175LLF_Def *IP175LLF, 
                    bool (*hw_rw)(bool rdInstruct,uint8_t PHY_addr,uint8_t reg_addr,uint16_t *rdData,uint32_t rdLen),
                    void (*hw_init)(void),
                    void (*hw_reset)(void))
{
    uint16_t temp[2];
    if(hw_init != NULL)
    {
        hw_init();
        IP175LLF->hw_init = hw_init;
    }

    if(hw_reset != NULL)
    {
        hw_reset();
        IP175LLF->hw_reset = hw_reset;
    }

    if(hw_rw != NULL)
    {
        IP175LLF->hw_rw = hw_rw;
    }
    else
    {
        return false;
    }

    IP175LLF->hw_rw(false,IP175LLF_Port0,IP175_PHY_ID1,temp,0x02);
    IP175LLF->IP175LLF_OUI_ID =  (((uint32_t )temp[0]) << 6) | ((temp[1] & IP175_PHY_Identifier) >> 0x0A);
    IP175LLF->IP175LLF_ID = (temp[1] & IP175_PHY_Identifier) >> 0x0A;
    IP175LLF->IP175LLF_Manu = (temp[1] & IP175_Manu_Model_Num) >> 0x04;
    IP175LLF->IP175LLF_Revision = (temp[1] & IP175_Revision_Num);

    if(!(IP175LLF->IP175LLF_ID) || !(IP175LLF->IP175LLF_Manu) || !(IP175LLF->IP175LLF_OUI_ID))
    {
        return false;
    }

    IP175LLF->hw_rw(false,IP175LLF_Sw_CR1,IP175_Chip_ID,&IP175LLF->IP175LLF_ChipID,0x01);

    if(!IP175LLF->IP175LLF_ChipID)
    {
        return false;
    }
    IP175LLF_SoftwareReset(IP175LLF);

    IP175LLF_SetPort5Par(IP175LLF, false,true);
    return true;
}

/**
 * @brief 芯片软件重置，不会从引脚读相应设置
 * 
 * @param IP175LLF 
 */
void IP175LLF_SoftwareReset(IP175LLF_Def *IP175LLF)
{
    uint16_t temp = 0x175D;
    IP175LLF->hw_rw(true,IP175LLF_Sw_CR1,IP175_Soft_Reset_R,&temp,0x01);
    for(volatile uint16_t i = 0;i < 0xffff;i++)
    {

    }

}

/**
 * @brief 端口重置
 * 
 * @param IP175LLF 
 * @param PHY_Portx 端口0...3
 */
void IP175LLF_PortReset(IP175LLF_Def *IP175LLF,IPLLF_PHYID PHY_Portx)
{
    if(PHY_Portx >= IP175LLF_Port5)
    {
        IP175LLF_Error("端口大于等于5无法单独重置,PHY = 0 ... 3;reg = 0.\r\n");
        return ;
    }
    uint16_t temp = 0x8000;

    IP175LLF->hw_rw(true,PHY_Portx,IP175_PHY_CR,&temp,0x01);
    for(volatile uint16_t i = 0;i < 0xffff;i++)
    {

    }
    do
    {
        IP175LLF->hw_rw(false,PHY_Portx,IP175_PHY_CR,&temp,0x01);
    } while (temp & IP175_P03_Reset);

}

/**
 * @brief 关闭端口n电源
 * 
 * @param IP175LLF 
 * @param PHY_Portx 
 * @param Enable 1 = 关闭电源 0 = 打开电源
 */
void IP175LLF_PortPowerDown(IP175LLF_Def *IP175LLF,IPLLF_PHYID PHY_Portx,bool Enable)
{
    if(PHY_Portx >= IP175LLF_Port5)
    {
        IP175LLF_Error("端口大于等于5无法单独重置,PHY = 0 ... 3;reg = 0.\r\n");
        return ;
    }
    uint16_t temp;

    IP175LLF->hw_rw(false,PHY_Portx,IP175_PHY_CR,&temp,0x01);

    temp &= ~IP175_P03_Power_D;
    temp |= Enable ? IP175_P03_Power_D : 0x00;

    IP175LLF->hw_rw(true,PHY_Portx,IP175_PHY_CR,&temp,0x01);
}

/**
 * @brief 读取端口0...3的速度和工作模式
 * 
 * @param IP175LLF 
 * @param PHY_Portx 待读取的端口0...3
 * @param Speed 0 = 10M , 1 = 100M
 * @param Duplex 0 = 半双工 , 1 = 全双工
 * @return true 读取成功
 * @return false 读取失败
 */
bool IP175LLF_ReadPHYSpeedDuplexStatus(IP175LLF_Def *IP175LLF,IPLLF_PHYID PHY_Portx,bool *Speed,bool *Duplex)
{
    if(PHY_Portx > IP175LLF_Port5)
    {
        IP175LLF_Error(" 端口大于5无特殊状态寄存器，PHY = 0 ... 3;reg = 18.\r\n");
        return false;
    }
    uint16_t temp;
    if(PHY_Portx != IP175LLF_Port5)
    {
        IP175LLF->hw_rw(false,PHY_Portx,IP175_PHY_SSR,&temp,0x01);
        *Speed = (temp & IP175_Speed_Mode) ? true:false;
        *Duplex = (temp & IP175_Duplex_Mode) ? true:false;
    }
    else
    {
        IP175LLF->hw_rw(false,PHY_Portx,IP175_PHY_CR,&temp,0x01);
        *Speed = (temp & IP175_Speed_Sel) ? true:false;
        *Duplex = (temp & IP175_Duplex_Sel) ? true:false;
    }
    
    return true;
}

/**
 * @brief 设置端口0...5的工作模式和速度，只有在自动协商未失能的情况下有效
 * 
 * @param IP175LLF 
 * @param PHY_Portx 端口0...5
 * @param Speed 0 = 10M, 1 = 100M
 * @param Duplex 0 = 半双工, 1 = 全双工
 * @return true 读取成功
 * @return false 读取失败
 */
bool IP175LLF_SetPHYSpeedDuplex(IP175LLF_Def *IP175LLF,IPLLF_PHYID PHY_Portx,bool Speed,bool Duplex)
{
    if(PHY_Portx >= IP175LLF_Port5)
    {
        IP175LLF_Error("只有物理端口可以设置默认速度和工作模式。PHY = 0 ... 3;reg = 00.\r\n");
        IP175LLF_Error("端口5工作默认速度和工作模式由硬件pin55和pin58脚确认\r\n");
        return false;
    }
    uint16_t temp;

    IP175LLF->hw_rw(false,PHY_Portx,IP175_PHY_CR,&temp,0x01);

    temp &= ~(uint16_t)(IP175_Speed_Sel | IP175_Duplex_Sel);
    temp |= Speed ? IP175_Speed_Sel : 0x0000;
    temp |= Duplex ? IP175_Duplex_Sel : 0x0000;

    IP175LLF->hw_rw(true,PHY_Portx,IP175_PHY_CR,&temp,0x01);
    return true;
}

/**
 * @brief 获取端口连接状态
 * 
 * @param IP175LLF 
 * @param PHY_Portx 
 * @return true 
 * @return false 
 */
bool IP175LLF_GetLinkStatus(IP175LLF_Def *IP175LLF,IPLLF_PHYID PHY_Portx)
{
    if(PHY_Portx >= IP175LLF_Port5)
    {
        IP175LLF_Error("只有物理端口0...5可以读取连接状态。PHY = 0 ... 5;reg = 01.\r\n");
        return false;
    }

    uint16_t temp;
    bool re;
    IP175LLF->hw_rw(false,PHY_Portx,IP175_PHY_SR,&temp,0x01);

    return re = (temp & IP175_Link_Status) ? true : false;
}

/**
 * @brief 设置端口0...3自动协商是否启用
 * 
 * @param IP175LLF 
 * @param PHY_Portx 
 * @param status 0 = 失能自动协商， 1 = 使能自动协商
 */
void IP175LLF_NwayEn(IP175LLF_Def *IP175LLF,IPLLF_PHYID PHY_Portx,bool status)
{
    if(PHY_Portx > IP175LLF_Port5)
    {
        IP175LLF_Error("只有物理端口0...3可以设置自动协商。PHY = 0 ... 3;reg = 00.\r\n");
        return ;
    }
    uint16_t temp;

    IP175LLF->hw_rw(false,PHY_Portx,IP175_PHY_CR,&temp,0x01);

    temp &= ~(uint16_t)IP175_Nway_En;
    temp |= status ? IP175_Nway_En : 0x0000;

    IP175LLF->hw_rw(true,PHY_Portx,IP175_PHY_CR,&temp,0x01);
}

/**
 * @brief 重启端口0...3自动协商
 * 
 * @param IP175LLF 
 * @param PHY_Portx 
 */
bool IP175LLF_NwayReset(IP175LLF_Def *IP175LLF,IPLLF_PHYID PHY_Portx)
{
    if(PHY_Portx > IP175LLF_Port3)
    {
        IP175LLF_Error("只有物理端口0...3可以设置自动协商。PHY = 0 ... 3;reg = 00.\r\n");
        return false;
    }
    uint16_t temp;


    IP175LLF->hw_rw(false,PHY_Portx,IP175_PHY_CR,&temp,0x01);

    if(!(temp & IP175_Nway_Ability))
    {
        IP175LLF_Error("端口%d无自动协商能力\r\n",PHY_Portx);
        return false;
    }
    if(!(temp & IP175_Link_Status))
    {
        IP175LLF_Error("端口%d无连接\r\n",PHY_Portx);
        return false;
    }

    temp |= IP175_P03_Re_Nway;
    IP175LLF->hw_rw(true,PHY_Portx,IP175_PHY_CR,&temp,0x01);

    for(volatile uint16_t i = 0;i < 0xffff;i++)
    {

    }

    do
    {
        IP175LLF->hw_rw(false,PHY_Portx,IP175_PHY_SR,&temp,0x01);
        if(temp & IP175_P03_Remote_Fault)
        {
            IP175LLF_Error("端口%d检测到远端故障\r\n",PHY_Portx);
            return false;
        }
    } while (!(temp & IP175_Nway_Complete));

    bool Speed,Duplex;
    IP175LLF_ReadPHYSpeedDuplexStatus(IP175LLF,PHY_Portx,&Speed,&Duplex);
    IP175LLF_Debug("自动协商成功,端口%d的速度为%d,工作模式为%d\r\n",PHY_Portx,Speed,Duplex);
    
}

/**
 * @brief 设置端口5工作模式和接口模式，端口5可以工作在MAC模式和PHY模式
 *          接口可以工作在RMII和MII模式
 * 
 * @param IP175LLF 
 * @param WorkMode 0 = PHY模式，1 = MAC模式
 * @param InterfaceMode 0 = MII模式，1 = RMII模式
 */
void IP175LLF_SetPort5Par(IP175LLF_Def *IP175LLF,bool WorkMode,bool InterfaceMode)
{
    uint16_t temp;
    IP175LLF->hw_rw(false,IP175LLF_Sw_CR2,IP175_MII_1CR,&temp,0x01);

    temp &= ~(uint16_t)(IP175_MII_MAC_Mode_En | IP175_MII_RMII_En);

    temp |= WorkMode ? IP175_MII_MAC_Mode_En:0x0000;
    temp |= InterfaceMode ? IP175_MII_RMII_En:0x0000;

    IP175LLF->hw_rw(true,IP175LLF_Sw_CR2,IP175_MII_1CR,&temp,0x01);
}

/**
 * @brief 设置端口0...5LED灯工作模式
 * 
 * @param IP175LLF 
 * @param mode 0x00 模式0     (1: 100M Link fail, 0: 100M Link ok and no activity, flash: 100M    Link ok and TX/RX activity)
 *              0x01 模式1
 *              0x02 模式2        (1: 100M Link fail, 0: 100M Link ok and no activity, flash: 100M    Link ok and TX/RX activity)
 *              0x03 模式3        (1: link fail, 0: link ok, flash: Link ok and TX/ RX activity)
 */
void IP175LLF_SetLEDMode(IP175LLF_Def *IP175LLF,uint8_t mode)
{
    uint16_t temp;
    IP175LLF->hw_rw(false,IP175LLF_Sw_CR1,IP175_LED_CR,&temp,0x01);

    temp &= ~IP175_LED_Sel;
    temp |= (mode & IP175_LED_Sel);
    IP175LLF->hw_rw(true,IP175LLF_Sw_CR1,IP175_LED_CR,&temp,0x01);
}

/*********
 * IP175默认优先级查找顺序是特殊标签(仅连接CPU的端口有效)>端口优先级>用户定义优先级(DMAC、SMAC、VID)>VLAN标记
 * > IP帧上的TOS/DSCP优先级>IP逻辑端口
 ********/

/**
 * @brief 设置TxSpecialTag后,cpu发送带VLAN标签的数据包，可以将VLAN(0x8100)中的低八位按如下设置
 *          bit 7 ：0 = 学习使能；1 = 学习失能
 *          bit6-5：优先级分配(2'b 00 == 禁用;2'b 01 == 队列1;2'b 10 == 队列2;2'b 11 == 队列3;)
 *          bit3  ：port3输出端口掩码
 *          bit2  ：port2输出端口掩码
 *          bit1  ：port1输出端口掩码
 *          bit0  ：port0输出端口掩码
 *      注意：使能后，cpu发送将不再根据MAC地址查找要发送的端口
 * @param IP175LLF 
 * @param Enalbe 
 */
void IP175LLF_SetQOS_TxSpecialTag(IP175LLF_Def *IP175LLF,bool Enalbe)
{
    uint16_t temp;
    IP175LLF->hw_rw(false,IP175LLF_Sw_CR2,IP175_MISC_CR1,&temp,0x01);
    temp &= ~IP175_STAG_TX_EN;
    temp |= Enalbe ? IP175_STAG_TX_EN : 0x00;
    IP175LLF->hw_rw(true,IP175LLF_Sw_CR2,IP175_MISC_CR1,&temp,0x01);
}

/**
 * @brief 设置TCP/UDP逻辑端口优先级是否大于TOS/DSCP优先级，如果使能，
 *          当一个包中包含的TCP/UDP逻辑端口已经设置优先级时，不管是否设置TOS/DSCP优先级或者优先级别多高，
 *          均低于TCP/UDP逻辑端口优先级。即先查找端口优先级。
 * 
 * @param IP175LLF 
 * @param Enalbe 
 */
void IP175LLF_SetQOS_LP_Over_DSCP(IP175LLF_Def *IP175LLF,bool Enalbe)
{
    uint16_t temp;
    IP175LLF->hw_rw(false,IP175LLF_Prio_Class,IP175_QOS_BCR,&temp,0x01);
    temp &= ~IP175_LP_OVER_DSCP;
    temp |= Enalbe ? IP175_LP_OVER_DSCP : 0x00;
    IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_QOS_BCR,&temp,0x01);
}

/**
 * @brief 设置TOS/DSCP优先级是否大于VLAN优先级，如果使能，
 *          当一个包中包含的TOS/DSCP已经设置优先级时，不管是否设置VLAN优先级或者优先级别多高，
 *          均低于TOS/DSCP优先级。即先查找TOS/DSCP优先级。
 * 
 * @param IP175LLF 
 * @param Enalbe 
 */
void IP175LLF_SetQOS_TOS_Over_VLAN_Prio(IP175LLF_Def *IP175LLF,bool Enalbe)
{
    uint16_t temp;
    IP175LLF->hw_rw(false,IP175LLF_Prio_Class,IP175_QOS_BCR,&temp,0x01);
    temp &= ~IP175_TOS_OVER_VLAN_PRI;
    temp |= Enalbe ? IP175_TOS_OVER_VLAN_PRI : 0x00;
    IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_QOS_BCR,&temp,0x01);
}

/**
 * @brief 启用基于VLAN802.1Q中VLAN 优先级字段。
 * 
 * @param IP175LLF 
 * @param portn 0x01 端口1
 *              0x02 端口2
 *              0x03 端口3
 *              0x04 端口4
 *              0x05 端口5
 *              传入参数可以使用逻辑或("|")
 * @param Enalbe true 使能
 *              false 失能
 */
void IP175LLF_SetQOS_COSEn(IP175LLF_Def *IP175LLF,uint8_t portn,bool Enalbe)
{
    uint16_t temp;

    IP175LLF->hw_rw(false,IP175LLF_Prio_Class,IP175_QOS_BCR,&temp,0x01);
    temp &= ~IP175_TOS_OVER_VLAN_PRI;
    temp |= Enalbe ? IP175_TOS_OVER_VLAN_PRI : 0x00;
    IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_QOS_BCR,&temp,0x01);
}

/**
 * @brief 设置QOS队列调度器工作模式
 * 
 * @param IP175LLF 
 * @param portn 0x00-0x05(端口0-端口5)
 * @param mode 0x00-0x03(对应关系如下)
 *                          Q3  Q2  Q1  Q0
                    2’b00:  WRR WRR WRR WRR
                    2’b01:  WFQ WFQ WFQ WFQ(BE)
                    2’b10:  SP  WFQ WFQ BE
                    2’b11:  SP  SP  SP  SP
                    WRR: 加权轮询调度
                    WFQ: 加权公平队列
                    BE: 尽力
                    SP: 严格优先级
 */
void IP175LLF_SetQOS_QueueScheduling(IP175LLF_Def *IP175LLF,uint8_t portn,uint8_t mode)
{
    uint16_t temp ;
    IP175LLF->hw_rw(false,IP175LLF_Prio_Class,IP175_Queue_Sch_Config_R,&temp,0x01);

    switch (portn)
    {
        case 0x00:
            temp &= ~IP175_P0_SCH_TYPE;
            temp |= (mode & IP175_P0_SCH_TYPE);
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_Queue_Sch_Config_R,&temp,0x01);
            break;

        case 0x01:
            temp &= ~IP175_P1_SCH_TYPE;
            temp |= ((mode << (portn << 1)) & IP175_P1_SCH_TYPE);
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_Queue_Sch_Config_R,&temp,0x01);
            break;

        case 0x02:
            temp &= ~IP175_P2_SCH_TYPE;
            temp |= ((mode << (portn << 1)) & IP175_P2_SCH_TYPE);
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_Queue_Sch_Config_R,&temp,0x01);
            break;
        
        case 0x03:
            temp &= ~IP175_P3_SCH_TYPE;
            temp |= ((mode << (portn << 1)) & IP175_P3_SCH_TYPE);
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_Queue_Sch_Config_R,&temp,0x01);
            break;

        case 0x04:
            temp &= ~IP175_P4_SCH_TYPE;
            temp |= ((mode << (portn << 1)) & IP175_P4_SCH_TYPE);
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_Queue_Sch_Config_R,&temp,0x01);
            break;

        case 0x05:
            temp &= ~IP175_P5_SCH_TYPE;
            temp |= ((mode << (portn << 1)) & IP175_P5_SCH_TYPE);
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_Queue_Sch_Config_R,&temp,0x01);
            break;

        default:
            break;
    }
}

/**
 * @brief 设置队列x加权轮询调度的权重，默认为8
 * 
 * @param IP175LLF 
 * @param Queue 0x00-0x03(队列0-队列3)
 * @param Weight 0x01-0x0f(1 packets - 15packets)
 */
void IP175_SetQOS_QueueSchWFR(IP175LLF_Def *IP175LLF,uint8_t Queue,uint8_t Weight)
{
    uint16_t temp ;
    if(Queue > 0x03 | Weight > 0x0f | Weight == 0x00)
        return ;
    IP175LLF->hw_rw(false,IP175LLF_Prio_Class,IP175_Queue_Sch_CR,&temp,0x01);

    switch(Queue)
    {
        case 0x00:
            temp &= ~IP175_Q0_WEIGHT;
            temp |= (Weight & IP175_Q0_WEIGHT);
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_Queue_Sch_CR,&temp,0x01);
            break;
        
        case 0x01:
            temp &= ~IP175_Q1_WEIGHT;
            temp |= ((Weight << (Queue << 2)) & IP175_Q1_WEIGHT);
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_Queue_Sch_CR,&temp,0x01);
            break;

        case 0x02:
            temp &= ~IP175_Q2_WEIGHT;
            temp |= ((Weight << (Queue << 2)) & IP175_Q2_WEIGHT);
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_Queue_Sch_CR,&temp,0x01);
            break;

        case 0x03:
            temp &= ~IP175_Q3_WEIGHT;
            temp |= ((Weight << (Queue << 2)) & IP175_Q3_WEIGHT);
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_Queue_Sch_CR,&temp,0x01);
            break;
        
        default:
            break;
    }
}

/**
 * @brief 设置VLAN优先级映射到的队列
 * 
 * @param IP175LLF 
 * @param VLANPrio 0x00-0x07(VLAN优先级0-7)
 * @param Queue 0x00-0x03(队列0-3)
 */
void IP175LLF_SetQOS_VLANPrioMap(IP175LLF_Def *IP175LLF,uint8_t VLANPrio,uint8_t Queue)
{
    uint16_t temp ;
    if(Queue > 0x03 | VLANPrio > 0x07)
        return ;
    IP175LLF->hw_rw(false,IP175LLF_Prio_Class,IP175_VLAN_PRI_Map_R,&temp,0x01);

    switch (VLANPrio)
    {
        case 0x00:
            temp &= ~IP175_VLAN_PRI0;
            temp |= (Queue << (VLANPrio << 1)) & IP175_VLAN_PRI0;
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_VLAN_PRI_Map_R,&temp,0x01);
            break;

        case 0x01:
            temp &= ~IP175_VLAN_PRI1;
            temp |= (Queue << (VLANPrio << 1)) & IP175_VLAN_PRI1;
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_VLAN_PRI_Map_R,&temp,0x01);
            break;
        
        case 0x02:
            temp &= ~IP175_VLAN_PRI2;
            temp |= (Queue << (VLANPrio << 1)) & IP175_VLAN_PRI2;
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_VLAN_PRI_Map_R,&temp,0x01);
            break;

        case 0x03:
            temp &= ~IP175_VLAN_PRI3;
            temp |= (Queue << (VLANPrio << 1)) & IP175_VLAN_PRI3;
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_VLAN_PRI_Map_R,&temp,0x01);
            break;

        case 0x04:
            temp &= ~IP175_VLAN_PRI4;
            temp |= (Queue << (VLANPrio << 1)) & IP175_VLAN_PRI4;
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_VLAN_PRI_Map_R,&temp,0x01);
            break;

        case 0x05:
            temp &= ~IP175_VLAN_PRI5;
            temp |= (Queue << (VLANPrio << 1)) & IP175_VLAN_PRI5;
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_VLAN_PRI_Map_R,&temp,0x01);
            break;

        case 0x06:
            temp &= ~IP175_VLAN_PRI6;
            temp |= (Queue << (VLANPrio << 1)) & IP175_VLAN_PRI6;
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_VLAN_PRI_Map_R,&temp,0x01);
            break;

        case 0x07:
            temp &= ~IP175_VLAN_PRI7;
            temp |= (Queue << (VLANPrio << 1)) & IP175_VLAN_PRI7;
            IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_VLAN_PRI_Map_R,&temp,0x01);
            break;

        default:
            break;
    }
}

/**
 * @brief 设置端口x优先级映射到QOS队列
 * 
 * @param IP175LLF 
 * @param PortPrio 0x00-0x05(端口0-5)
 * @param Queue 0x00-0x03(队列0-3)
 */
void IP175LLF_SetQOS_PortPrioMap(IP175LLF_Def *IP175LLF,uint8_t PortPrio,uint8_t Queue)
{
    uint16_t temp ;
    if(Queue > 0x03 | PortPrio > 0x07)
        return ;
    IP175LLF->hw_rw(false,IP175LLF_Prio_Class,IP175_VLAN_PRI_Map_R,&temp,0x01);

    switch (PortPrio)
    {
    case 0x00:
        temp &= ~IP175_P0_PRI;
        temp |= (Queue << (PortPrio << 1)) & IP175_P0_PRI;
        IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_VLAN_PRI_Map_R,&temp,0x01);
        break;
    
    case 0x01:
        temp &= ~IP175_P1_PRI;
        temp |= (Queue << (PortPrio << 1)) & IP175_P1_PRI;
        IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_VLAN_PRI_Map_R,&temp,0x01);
        break;

    case 0x02:
        temp &= ~IP175_P2_PRI;
        temp |= (Queue << (PortPrio << 1)) & IP175_P2_PRI;
        IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_VLAN_PRI_Map_R,&temp,0x01);
        break;

    case 0x03:
        temp &= ~IP175_P3_PRI;
        temp |= (Queue << (PortPrio << 1)) & IP175_P3_PRI;
        IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_VLAN_PRI_Map_R,&temp,0x01);
        break;

    case 0x04:
        temp &= ~IP175_P4_PRI;
        temp |= (Queue << (PortPrio << 1)) & IP175_P4_PRI;
        IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_VLAN_PRI_Map_R,&temp,0x01);
        break;

    case 0x05:
        temp &= ~IP175_P5_PRI;
        temp |= (Queue << (PortPrio << 1)) & IP175_P5_PRI;
        IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_VLAN_PRI_Map_R,&temp,0x01);
        break;

    default:
        break;
    }
}

/**
 * @brief 设置TOS/DSCP优先级映射到QOS队列
 * 
 * @param IP175LLF 
 * @param DSCPPrio 0x00-0x3F(DSCP优先级0-63)
 * @param Queue 0x00-0x03(队列0-3)
 */
void IP175LLF_SetQOS_DSCPMap(IP175LLF_Def *IP175LLF,uint8_t DSCPPrio,uint8_t Queue)
{
    uint16_t temp ;
    if(Queue > 0x03 | DSCPPrio > 0x63)
        return ;

    uint8_t RegAddr = IP175_TOS_PRI_Map_1R + (DSCPPrio >> 3);
    uint8_t Mask = 0x03 << (DSCPPrio & 0x07);

    IP175LLF->hw_rw(false,IP175LLF_Prio_Class,RegAddr,&temp,0x01);

    temp &= ~Mask;
    temp |= (Queue <<(DSCPPrio & 0x07)) & Mask;

    IP175LLF->hw_rw(true,IP175LLF_Prio_Class,RegAddr,&temp,0x01);
}

/**
 * @brief 设置基于逻辑端口优先级的工作模式
 * 
 * @param IP175LLF 
 * @param Mode  0x00 -- 失能
 *              0x01 -- 源逻辑端口优先级
 *              0x02 -- 目的逻辑端口优先级
 *              0x03 -- 源或目的逻辑锻炼优先级
 */
void IP175LLF_SetQOS_LPPrioMode(IP175LLF_Def *IP175LLF,uint8_t Mode)
{
    uint16_t temp ;
    if(Mode > 0x03)
        return ;

    IP175LLF->hw_rw(false,IP175LLF_Prio_Class,IP175_TCP_UDP_PRI_Map_1R,&temp,0x01);

    temp &= ~IP175_LP_TYPE;
    temp |= (Mode << 0x06 ) & IP175_LP_TYPE;

    IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_TCP_UDP_PRI_Map_1R,&temp,0x01);
}

/**
 * @brief 设置范围逻辑端口使能或者失能，共有两个范围逻辑端口优先级可以使用
 * 
 * @param IP175LLF 
 * @param Range 0x01 -- 范围逻辑端口0
 *              0x02 -- 范围逻辑端口1
 *              0x03 -- 范围逻辑端口0、1
 * @param Range_En 1 = 范围逻辑端口使能
 *                  0 = 失能
 */
void IP175LLF_SetQOS_RangeLP_En(IP175LLF_Def *IP175LLF,uint8_t Range,bool Range_En)
{
    uint16_t temp;
    if(Range > 0x03 | Range == 0x00)
        return ;

    IP175LLF->hw_rw(false,IP175LLF_Prio_Class,IP175_TCP_UDP_PRI_Map_1R,&temp,0x01);

    
    temp &= ~IP175_USERDEF_RANGE_EN;
    temp |= Range_En ? ((Range << 0x04) & IP175_USERDEF_RANGE_EN): 0x00;

    IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_TCP_UDP_PRI_Map_1R,&temp,0x01);
}

/**
 * @brief 设置逻辑锻炼使能或者失能，共有4个逻辑端口优先级可以使用
 * 
 * @param IP175LLF 
 * @param LogicPort 0x01 逻辑端口1
 *                  0x02 逻辑端口2
 *                  0x04 逻辑端口3
 *                  0x08 逻辑端口4
 *              注意：传入参数可以 逻辑或("|")
 * @param LogicPort_En 1 = 逻辑端口使能
 *                      0 = 失能
 */
void IP175LLF_SetQOS_LP_En(IP175LLF_Def *IP175LLF,uint8_t LogicPort,bool LogicPort_En)
{
    uint16_t temp;
    if(LogicPort > 0x0f | LogicPort == 0x00)
        return ;

    IP175LLF->hw_rw(false,IP175LLF_Prio_Class,IP175_TCP_UDP_PRI_Map_1R,&temp,0x01);

    
    temp &= ~IP175_PREDEF_PORT_EN;
    temp |= LogicPort_En ? (LogicPort & IP175_PREDEF_PORT_EN) : 0x00;

    IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_TCP_UDP_PRI_Map_1R,&temp,0x01);
}

/**
 * @brief 设置范围逻辑端口范围
 *
 * @param IP175LLF 
 * @param Range 0x01 -- 范围逻辑端口0
 *              0x02 -- 范围逻辑端口1
 * @param RangeLogicPortLow 范围逻辑端口下限
 * @param RangeLogicPortHigh 范围逻辑端口上限
 */
void IP175LLF_SetQOS_RangeLogicPort(IP175LLF_Def *IP175LLF,uint8_t Range,uint16_t RangeLogicPortLow,uint16_t RangeLogicPortHigh)
{
    uint16_t temp;
    if(Range > 0x02 | Range == 0x00)
        return ;

    uint8_t RegAddr = IP175_USERDEF_RANGE0_LOW_R + ((Range - 1) << 1);
    temp = RangeLogicPortLow;
    IP175LLF->hw_rw(true,IP175LLF_Prio_Class,RegAddr,&temp,0x01);

    RegAddr = IP175_USERDEF_RANGE0_HIGH_R + ((Range - 1) << 1);
    temp = RangeLogicPortHigh;
    IP175LLF->hw_rw(true,IP175LLF_Prio_Class,RegAddr,&temp,0x01);

}

/**
 * @brief 设置逻辑端口端口号
 * 
 * @param IP175LLF 
 * @param LogicPort 0x01-0x04(逻辑端口优先级0-3)
 * @param LogicPortValue 16位端口号
 */
void IP175LLF_SetQOS_LogicPort(IP175LLF_Def *IP175LLF,uint8_t LogicPort,uint16_t LogicPortValue)
{
    uint16_t temp;
    if(LogicPort > 0x04 | LogicPort == 0x00)
        return ;

    uint8_t RegAddr = IP175_PREDEF_PORT_0_R + LogicPort - 1;
    temp = LogicPortValue;
    IP175LLF->hw_rw(true,IP175LLF_Prio_Class,RegAddr,&temp,0x01);

}

/**
 * @brief 设置范围逻辑端口优先级映射到QOS队列
 * 
 * @param IP175LLF 
 * @param Range 0x01 -- 范围逻辑端口0
 *              0x02 -- 范围逻辑端口1 
 * @param Queue 0x00-0x03(队列0-3)
 */
void IP175LLF_SetQOS_RangeLPPrioMap(IP175LLF_Def *IP175LLF,uint8_t Range,uint8_t Queue)
{
    uint16_t temp;
    if(Range > 0x02 | Range == 0x00)
        return;

    IP175LLF->hw_rw(false,IP175LLF_Prio_Class,IP175_Trans_PRI_Map_R,&temp,0x01);
    
    if(Range == 0x01)
    {
        temp |= ~IP175_USERDEF_RANGE_1Q;
        temp &= Queue << 0x0A;
    }   
    else
    {
        temp |= ~IP175_USERDEF_RANGE_0Q;
        temp &= Queue << 0x08;
    }

    IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_Trans_PRI_Map_R,&temp,0x01);
}

/**
 * @brief 设置逻辑端口优先级映射到QOS队列
 * 
 * @param IP175LLF 
 * @param LogicPort 0x01 逻辑端口1
 *                  0x02 逻辑端口2
 *                  0x04 逻辑端口3
 *                  0x08 逻辑端口4
 * @param Queue 0x00-0x03(队列0-3)
 */
void IP175LLF_SetQOS_LogicPortPrioMap(IP175LLF_Def *IP175LLF,uint8_t LogicPort,uint8_t Queue)
{
    uint16_t temp;
    if(LogicPort > 0x02 | LogicPort == 0x00)
        return;

    IP175LLF->hw_rw(false,IP175LLF_Prio_Class,IP175_Trans_PRI_Map_R,&temp,0x01);
    
    switch (LogicPort)
    {
    case 0x01:
        temp |= ~IP175_PREDEF_PORT_0Q;
        temp &= ((Queue << 0x00) & IP175_PREDEF_PORT_0Q);
        IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_Trans_PRI_Map_R,&temp,0x01);
        break;
    
    case 0x02:
        temp |= ~IP175_PREDEF_PORT_1Q;
        temp &= ((Queue << 0x02) & IP175_PREDEF_PORT_1Q);
        IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_Trans_PRI_Map_R,&temp,0x01);
        break;

    case 0x04:
        temp |= ~IP175_PREDEF_PORT_2Q;
        temp &= ((Queue << 0x04) & IP175_PREDEF_PORT_2Q);
        IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_Trans_PRI_Map_R,&temp,0x01);
        break;

    case 0x08:
        temp |= ~IP175_PREDEF_PORT_3Q;
        temp &= ((Queue << 0x06) & IP175_PREDEF_PORT_3Q);
        IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_Trans_PRI_Map_R,&temp,0x01);
        break;

    default:
        break;
    }
}

/**
 * @brief 将匹配范围逻辑端口x的报文丢弃，不再转发，优先级高于优先级转发功能
 * 
 * @param IP175LLF 
 * @param Range 0x01 范围逻辑端口0
 *              0x02 范围逻辑端口1
 *              0x03 范围逻辑端口0、1
 * @param Range_En 1 = 使能丢弃
 *                  0 = 失能丢弃
 */
void IP175LLF_SetQOS_RangeDrop(IP175LLF_Def *IP175LLF,uint8_t Range,bool Range_En)
{
    uint16_t temp;
    if(Range > 0x03 | Range == 0x00)
        return;

    IP175LLF->hw_rw(false,IP175LLF_Prio_Class,IP175_PRIDEF_DROP_R,&temp,0x01);

    temp |= ~IP175_USERDEF_RANGE0_DROP;
    temp &= Range_En ? (Range & IP175_USERDEF_RANGE0_DROP) : 0x00;

    IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_PRIDEF_DROP_R,&temp,0x01);
}

/**
 * @brief 
 * 
 * @param IP175LLF 
 * @param LogicPort 0x01 逻辑端口1
 *                  0x02 逻辑端口2
 *                  0x04 逻辑端口3
 *                  0x08 逻辑端口4
 *              注意：传入参数可以 逻辑或("|")
 * @param LogicPort_En 1 = 逻辑端口丢弃使能
 *                      0 = 失能
 */
void IP175LLF_SetQOS_LogicPortDrop(IP175LLF_Def *IP175LLF,uint8_t LogicPort,bool LogicPort_En)
{
    uint16_t temp;
    if(LogicPort > 0x0f | LogicPort == 0x00)
        return ;

    IP175LLF->hw_rw(false,IP175LLF_Prio_Class,IP175_PRIDEF_DROP_R,&temp,0x01);

    temp &= ~IP175_PREDEF_PORT_DROP;
    temp |= LogicPort_En ? ((LogicPort << 0x02) & IP175_PREDEF_PORT_DROP): 0x00;

    IP175LLF->hw_rw(true,IP175LLF_Prio_Class,IP175_PRIDEF_DROP_R,&temp,0x01);

}


