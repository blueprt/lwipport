/**
 * @file ksz8863.c
 * @author chentao
 * @brief 
 * @version 0.1
 * @date 2022-09-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ksz8863.h"

#include <string.h>
#include <stdbool.h>

/**
 * @brief ksz8863初始化
 * @param struct ksz8863 ksz8863结构
 * 
 * @param uint8_t (*hw_rsert)(void)
 * 硬件重置
 * 返回值 0 = success 1 = fault
 * 
 * @param uint8_t (*mii_rmii_init_handle)(void)
 * rmii或者mii接口初始化，可以设置为NULL，当在外部已经进行初始化时
 * 返回值 0 = success 1 = fault
 * 
 * @param uint8_t (*hw_init_handle)(void)
 * 硬件读写接口初始化，可能的有smi、spi和iic接口三种，可以设置为NULL，当在外部已经进行初始化时
 * 返回值 0 = success 1 = fault
 * 
 * @param uint8_t (*hw_w)(uint8_t Memaddr,char *data,uint8_t datalen)
 *  spi\iic\smi写函数，需要用户实现的底层读写函数,相关时序参阅ksz8863.h
 *  参数 Memaddr:读写的地址，取值0-198u
 *  参数 *data:写的数据地址
 *  参数 datalen:数据长度
 *  返回值 0 = success 1 = fault
 * 
 *  * @param uint8_t (*hw_r)(uint8_t Memaddr,char *data,uint8_t datalen)
 *  spi\iic\smi读函数，需要用户实现的底层读写函数,相关时序参阅ksz8863.h
 *  参数 Memaddr:读写的地址，取值0-198u
 *  参数 *data:读的数据地址
 *  参数 datalen:数据长度
 *  返回值 0 = success 1 = fault
 * 
 */

uint8_t ksz8863(ksz8863_def *ksz8863,\
                uint8_t (*hw_rsert)(void),
                uint8_t (*mii_rmii_init_handle)(void),\
                uint8_t (*hw_init_handle)(void),\
                uint8_t (*hw_w)(uint8_t Memaddr,char *data,uint8_t datalen),\
                uint8_t (*hw_r)(uint8_t Memaddr,char *data,uint8_t datalen))
{
    if(mii_rmii_init_handle != NULL)
    {
        if(mii_rmii_init_handle())
            return 1;
    }
    if(hw_init_handle != NULL)
    {
        if(hw_init_handle())
            return 1;
    }
    
    ksz8863->hw_reset = hw_rsert;

    if(ksz8863->hw_reset)
    {
        if(ksz8863->hw_reset())
            return 1;
    }

    ksz8863->software_reset = ksz8863_software_reset;
    ksz8863->pcs_reset = ksz8863_pcs_reset;
    ksz8863->turn_on_off_AN = ksz8863_turn_on_off_AN;
    ksz8863->Restart_AN = ksz8863_Restart_AN;
    ksz8863->set_port_def_speed_duplex = ksz8863_set_port_def_speed_duplex;
    ksz8863->get_port_speed_duplex = ksz8863_get_port_speed_duplex;
    ksz8863->set_port3_macaddr = ksz8863_set_port3_macaddr;
    ksz8863->Interrupt_En = ksz8863_Interrupt_En;
    ksz8863->get_Interrupt_status = ksz8863_get_Interrupt_status;
    ksz8863->clear_Interrupt_status = ksz8863_clear_Interrupt_status;
    ksz8863->get_link_status = ksz8863_get_link_status;
    ksz8863->port3_set_MII_Mode = ksz8863_port3_set_MII_Mode;
    ksz8863->port3_RMII_clk_invert = ksz8863_port3_RMII_clk_invert;
    ksz8863->turn_on_off_TXQ_Split = ksz8863_turn_on_off_TXQ_Split;
    ksz8863->turn_on_off_802_1p_prio = ksz8863_turn_on_off_802_1p_prio;
    
    ksz8863->hw_w = hw_w;
    ksz8863->hw_r = hw_r;
    
    if(ksz8863->software_reset(ksz8863))
            return 1;
    if(ksz8863->hw_r)
    {
        if(ksz8863->hw_r(Chip_ID_Addr,(char *)&(ksz8863->ksz8863_MemData),End_Addr))
            return 1;
    }
    return 0;
}

/**
 * @brief 使用软件重启ksz8863，软件复位会将所有寄存器复位到开机复位或热复位的初始值(保留表带值)
 * 
 * @param ksz8863 
 * @return uint8_t 1 = fault 0 = success
 */
uint8_t ksz8863_software_reset(struct ksz8863 *ksz8863)
{
    uint16_t temtime = 0;
    ksz8863->ksz8863_MemData.Reset_bit.Soft_Reset = 1;

    if(ksz8863->hw_w(Reset_Addr,(char *)&(ksz8863->ksz8863_MemData.Reset),1))
        return 1;
    
    do{
        ksz8863->hw_r(Reset_Addr,(char *)&(ksz8863->ksz8863_MemData.Reset),1);
        temtime ++ ;
    }while((ksz8863->ksz8863_MemData.Reset_bit.Soft_Reset) && (temtime < 0x0FFF));

    if(temtime >= 0x0FFF)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief 使用软件以PCS方式重启ksz8863，PCS复位将重置PHY PCS层的状态机和时钟域。
 * 
 * @param ksz8863 
 * @return uint8_t 1 = fault 0 = success
 */
uint8_t ksz8863_pcs_reset(struct ksz8863 *ksz8863)
{
    uint16_t temtime = 0;
    ksz8863->ksz8863_MemData.Reset_bit.PCS_Reset = 1;

    if(ksz8863->hw_w(Reset_Addr,(char *)&(ksz8863->ksz8863_MemData.Reset),1))
        return 1;
    
    do{
        ksz8863->hw_r(Reset_Addr,(char *)&(ksz8863->ksz8863_MemData.Reset),1);
        temtime ++ ;
    }while((ksz8863->ksz8863_MemData.Reset_bit.PCS_Reset) && (temtime < 0x0FFF));

    if(temtime >= 0x0FFF)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief 打开关闭端口n自动协商功能
 * 
 * @param ksz8863 
 * @param portn 端口号，支持 0 = 端口1和 1 = 端口2
 * @param status 1 = 打开自动协商 0 = 关闭自动协商
 * @return uint8_t 1 = fault 0 = success
 */
uint8_t ksz8863_turn_on_off_AN(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool status)
{
    uint16_t temtime = 0 ;
    char data = 0;
    switch (portn)
    {
    case ksz8863_port1:
        if( status == ksz8863->ksz8863_MemData.Port1_ctl12_bit.AN_En)
            return 0;
    
        ksz8863->ksz8863_MemData.Port1_ctl12_bit.AN_En = status;
        data = ksz8863->ksz8863_MemData.Port1_ctl12;
        ksz8863->ksz8863_MemData.Port1_ctl12_bit.AN_En = !ksz8863->ksz8863_MemData.Port1_ctl12_bit.AN_En;
        do{

            if(ksz8863->hw_w(Port1_CR12_Addr,(char *)&(data),1))
                return 1;
            ksz8863->hw_r(Port1_CR12_Addr,(char *)&(ksz8863->ksz8863_MemData.Port1_ctl12),1);
            temtime ++ ;
        }while((status != ksz8863->ksz8863_MemData.Port1_ctl12_bit.AN_En) && (temtime < 0x0FFF));

        if(temtime >= 0x0FFF)
        {
            return 1;
        }
        break;
    case ksz8863_port2:
        if( status == ksz8863->ksz8863_MemData.Port2_ctl12_bit.AN_En)
            return 0;
    
        ksz8863->ksz8863_MemData.Port2_ctl12_bit.AN_En = status;
        data = ksz8863->ksz8863_MemData.Port2_ctl12;
        ksz8863->ksz8863_MemData.Port2_ctl12_bit.AN_En = !ksz8863->ksz8863_MemData.Port2_ctl12_bit.AN_En;
        do{

            if(ksz8863->hw_w(Port2_CR12_Addr,(char *)&(data),1))
                return 1;
            ksz8863->hw_r(Port2_CR12_Addr,(char *)&(ksz8863->ksz8863_MemData.Port2_ctl12),1);
            temtime ++ ;
        }while((status != ksz8863->ksz8863_MemData.Port2_ctl12_bit.AN_En) && (temtime < 0x0FFF));

        if(temtime >= 0x0FFF)
        {
            return 1;
        }
    case  ksz8863_port3:
    default:
        return 1;
        break;
    }
    return 0;
}

/**
 * @brief 重启端口n自动协商,并返回协商后速度和工作模式
 * @note 端口3不支持自动协商功能，使用 @see ksz8863_set_port_def_speed_duplex
 * @param ksz8863 
 * @param portn 端口号，支持 0 = 端口1和 1 = 端口2
 * @param speed 连接速度
 * @param duplex 工作模式
 * @return uint8_t 1 = fault 0 = success
 */
uint8_t ksz8863_Restart_AN(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool *speed,bool *duplex)
{
    uint16_t temtime = 0;
    switch (portn)
    {
    case ksz8863_port1:
        if(ksz8863->ksz8863_MemData.Port1_ctl12_bit.AN_En)
        {
            ksz8863->ksz8863_MemData.Port1_ctl13_bit.Restart_AN = 1;
            if(ksz8863->hw_w(Port1_CR13_Addr,(char *)&(ksz8863->ksz8863_MemData.Port1_ctl13),1))
                return 1;
            do{
                if(ksz8863->hw_r(Port1_SR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port1_Status),2))
                    return 1;
                temtime ++ ;
            }while((ksz8863->ksz8863_MemData.Port1_Status_bit.AN_Done == 0) && (temtime < 0x0FFF));

            if(temtime >= 0x0FFF)
            {
                return 1;
            }

            *speed = ksz8863->ksz8863_MemData.Port1_Status_bit.Operation_Speed;
            *duplex = ksz8863->ksz8863_MemData.Port1_Status_bit.Operation_Duplex;

            return 0;
        }
        else
            return 1;
        break;

    case ksz8863_port2:
        if(ksz8863->ksz8863_MemData.Port2_ctl12_bit.AN_En)
        {
            ksz8863->ksz8863_MemData.Port2_ctl13_bit.Restart_AN = 1;
            if(ksz8863->hw_w(Port2_CR13_Addr,(char *)&(ksz8863->ksz8863_MemData.Port2_ctl13),1))
                return 1;
            do{
                if(ksz8863->hw_r(Port2_SR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port2_Status),2))
                    return 1;
                temtime ++ ;
            }while((ksz8863->ksz8863_MemData.Port2_Status_bit.AN_Done == 0) && (temtime < 0x0FFF));

            if(temtime >= 0x0FFF)
            {
                return 1;
            }

            *speed = ksz8863->ksz8863_MemData.Port2_Status_bit.Operation_Speed;
            *duplex = ksz8863->ksz8863_MemData.Port2_Status_bit.Operation_Duplex;

            return 0;
        }
        else
            return 1;
        break;

    case  ksz8863_port3:
    default:
        return 1;
        break;
    }
}

/**
 * @brief 设置ksz8863端口默认连接速度和工作模式，上电默认值为100BT full_Duplex 。
 * @note 端口3连接到CPU，不支持自动协商功能，使用该函数手动设置连接速度和工作模式。注意和CPU MAC速度和工作模式对应
 * 
 * @param ksz8863 
 * @param portn 0 = 端口1 ， 1 = 端口2 ， 2 = 端口3
 * @param speed 0 = 10BT , 1 = 100BT
 * @param duplex 0 = half_duplex , 1 = full_duplex
 * @return uint8_t 1 = fault 0 = success
 */
uint8_t ksz8863_set_port_def_speed_duplex(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool speed,bool duplex)
{
    switch (portn)
    {
    case ksz8863_port1:
        if((ksz8863->ksz8863_MemData.Port1_ctl12_bit.Force_Speed == speed) && (ksz8863->ksz8863_MemData.Port1_ctl12_bit.Force_Duplex == duplex))
            return 0;
        if(ksz8863->hw_r(Port1_CR12_Addr,(char *)&(ksz8863->ksz8863_MemData.Port1_ctl12),1))
            return 1;

        ksz8863->ksz8863_MemData.Port1_ctl12_bit.Force_Speed = speed;
        ksz8863->ksz8863_MemData.Port1_ctl12_bit.Force_Duplex = duplex;

        if(ksz8863->hw_w(Port1_CR12_Addr,(char *)&(ksz8863->ksz8863_MemData.Port1_ctl12),1))
            return 1;
        break;

    case ksz8863_port2:
        if((ksz8863->ksz8863_MemData.Port2_ctl12_bit.Force_Speed == speed) && (ksz8863->ksz8863_MemData.Port2_ctl12_bit.Force_Duplex == duplex))
            return 0;
        if(ksz8863->hw_r(Port2_CR12_Addr,(char *)&(ksz8863->ksz8863_MemData.Port2_ctl12),1))
            return 1;

        ksz8863->ksz8863_MemData.Port2_ctl12_bit.Force_Speed = speed;
        ksz8863->ksz8863_MemData.Port2_ctl12_bit.Force_Duplex = duplex;

        if(ksz8863->hw_w(Port2_CR12_Addr,(char *)&(ksz8863->ksz8863_MemData.Port2_ctl12),1))
            return 1;
        break;

    case ksz8863_port3:
        if(ksz8863->ksz8863_MemData.Global_ctl4_bit.MII_10BT == speed)
            ksz8863->ksz8863_MemData.Global_ctl4_bit.MII_10BT = !(ksz8863->ksz8863_MemData.Global_ctl4_bit.MII_10BT);
        if(ksz8863->ksz8863_MemData.Global_ctl4_bit.MII_Half_Dup_Mode == duplex)
            ksz8863->ksz8863_MemData.Global_ctl4_bit.MII_Half_Dup_Mode = !(ksz8863->ksz8863_MemData.Global_ctl4_bit.MII_Half_Dup_Mode);
        if(ksz8863->hw_w(Global_CR4_Addr,(char *)&(ksz8863->ksz8863_MemData.Global_ctl4),1))
            return 1;
        break;

    default:
        return 1;
        break;
    }
    return 0;
}

/**
 * @brief 获取端口n连接速度和工作模式
 * 
 * @param ksz8863 
 * @param portn 端口号 0 = 端口1 ，1 = 端口2 ， 3 = 端口3
 * @param speed 获取到的连接速度
 * @param duplex 获取到的工作模式
 * @return uint8_t 1 = fault 0 = success
 */
uint8_t ksz8863_get_port_speed_duplex(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool *speed,bool *duplex)
{
    switch (portn)
    {
    case ksz8863_port1:
        if(ksz8863->hw_r(Port1_SR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port1_Status),2))
            return 1;
        *speed = ksz8863->ksz8863_MemData.Port1_Status_bit.Operation_Speed;
        *duplex = ksz8863->ksz8863_MemData.Port1_Status_bit.Operation_Duplex;
        break;
    case ksz8863_port2:
        if(ksz8863->hw_r(Port2_SR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port2_Status),2))
            return 1;
        *speed = ksz8863->ksz8863_MemData.Port2_Status_bit.Operation_Speed;
        *duplex = ksz8863->ksz8863_MemData.Port2_Status_bit.Operation_Duplex;
        break;
    case ksz8863_port3:
        if(ksz8863->hw_r(Port3_SR1_Addr,(char *)&(ksz8863->ksz8863_MemData.Port3_Status),1))
            return 1;
        *speed = ksz8863->ksz8863_MemData.Port3_Status_bit.Operation_Speed;
        *duplex = ksz8863->ksz8863_MemData.Port3_Status_bit.Operation_Duplex;
        break;
    default:
        return 1;
        break;
    }
    return 0;
}

/**
 * @brief 设置交换机引擎的MAC地址。这个48位地址被用作MAC的全双工流控制(暂停)帧的源地址。
 * 
 * @param ksz8863 
 * @param macaddr 
 * @return uint8_t 0 = success 1 = fault
 */
uint8_t ksz8863_set_port3_macaddr(struct ksz8863 *ksz8863,uint8_t *macaddr)
{
    for(char i = 0; i < 5; i++)
    {
        ksz8863->ksz8863_MemData.maca[i] = macaddr[i];
    }

    if(ksz8863->hw_w(MACAddr_Addr,(char *)&(ksz8863->ksz8863_MemData.maca),5))
        return 1;

    if(ksz8863->hw_r(MACAddr_Addr,(char *)&(ksz8863->ksz8863_MemData.maca),5))
        return 1;

    return 0;
}

/**
 * @brief 中断使能
 * 
 * @param ksz8863 
 * @param Interrupt_SRC 中断源，    ksz8863_P1_P2_Link_Changes = 0,<p>
 *                                  ksz8863_P3_Link_Changes,<p>
 *                                  ksz8863_P2_Link_Changes,<p>
 *                                  ksz8863_P1_Link_Changes<p>
 * @param status    1 = enable  0 = disable
 * @return uint8_t 0 = success  1 = fault
 */
uint8_t ksz8863_Interrupt_En(struct ksz8863 *ksz8863,ksz8863_Interrupt_def Interrupt_SRC,bool status)
{
    switch (Interrupt_SRC)
    {
    case ksz8863_P1_P2_Link_Changes:
        if (ksz8863->ksz8863_MemData.Interrupt_En_bit.P1_P2_Link_Change_En == status)
            return 0;
        else
            ksz8863->ksz8863_MemData.Interrupt_En_bit.P1_P2_Link_Change_En = status;
        break;
    case ksz8863_P3_Link_Changes:
        if (ksz8863->ksz8863_MemData.Interrupt_En_bit.P3_Link_Change_En == status)
            return 0;
        else
            ksz8863->ksz8863_MemData.Interrupt_En_bit.P3_Link_Change_En = status;
        break;
    case ksz8863_P2_Link_Changes:
        if (ksz8863->ksz8863_MemData.Interrupt_En_bit.P2_Link_Change_En == status)
            return 0;
        else
            ksz8863->ksz8863_MemData.Interrupt_En_bit.P2_Link_Change_En = status;
        break;
    case ksz8863_P1_Link_Changes:
        if (ksz8863->ksz8863_MemData.Interrupt_En_bit.P1_MII_link_Change_En == status)
            return 0;
        else
            ksz8863->ksz8863_MemData.Interrupt_En_bit.P1_MII_link_Change_En = status;
        break;
    default:
        return 1;
        break;
    }

    if(ksz8863->hw_w((char)Interrupt_SRC_Addr,(char *)&(ksz8863->ksz8863_MemData.Interrupt_En),1))
        return 1;
    if(ksz8863->hw_r((char)Interrupt_SRC_Addr,(char *)&(ksz8863->ksz8863_MemData.Interrupt_En),1))
        return 1;
    
    return 0;
}

/**
 * @brief 获取ksz8863对应中断源的中断状态
 * 
 * @param ksz8863 
 * @param Interrupt_SRC 中断源         ksz8863_P1_P2_Link_Changes = 0,<p>
 *                                  ksz8863_P3_Link_Changes,<p>
 *                                  ksz8863_P2_Link_Changes,<p>
 *                                  ksz8863_P1_Link_Changes<p>
 * @param status 返回的中断状态    1 = 触发  0 = 未触发
 * @return uint8_t 0 = success  1 = fault
 */
uint8_t ksz8863_get_Interrupt_status(struct ksz8863 *ksz8863,ksz8863_Interrupt_def Interrupt_SRC,bool *status)
{
    if(ksz8863->hw_r((char)Interrupt_SR_Addr,(char *)&(ksz8863->ksz8863_MemData.Interrupt_SC),1))
        return 1;
    switch (Interrupt_SRC)
    {
    case ksz8863_P1_P2_Link_Changes:
        *status = (bool)ksz8863->ksz8863_MemData.Interrupt_SC_bit.P1_P2_Link_Change;
        break;
    case ksz8863_P3_Link_Changes:
        *status = (bool)ksz8863->ksz8863_MemData.Interrupt_SC_bit.P3_Link_Change;
        break;
    case ksz8863_P2_Link_Changes:
        *status = (bool)ksz8863->ksz8863_MemData.Interrupt_SC_bit.P2_Link_Change;
        break;
    case ksz8863_P1_Link_Changes:
        *status = (bool)ksz8863->ksz8863_MemData.Interrupt_SC_bit.P1_MII_link_Change;
        break;
    default:
        return 1;
        break;
    }
    return 0;
}

/**
 * @brief 清除ksz8863对应中断源的中断状态
 * 
 * @param ksz8863 
 * @param Interrupt_SRC 中断源         ksz8863_P1_P2_Link_Changes = 0,<p>
 *                                  ksz8863_P3_Link_Changes,<p>
 *                                  ksz8863_P2_Link_Changes,<p>
 *                                  ksz8863_P1_Link_Changes<p>
 * @return uint8_t uint8_t 0 = success  1 = fault
 */
uint8_t ksz8863_clear_Interrupt_status(struct ksz8863 *ksz8863,ksz8863_Interrupt_def Interrupt_SRC)
{
    if(ksz8863->hw_r((char)Interrupt_SR_Addr,(char *)&(ksz8863->ksz8863_MemData.Interrupt_SC),1))
        return 1;
    switch (Interrupt_SRC)
    {
    case ksz8863_P1_P2_Link_Changes:
        if(ksz8863->ksz8863_MemData.Interrupt_SC_bit.P1_P2_Link_Change)
        {
            ksz8863->ksz8863_MemData.Interrupt_SC = 0;
            ksz8863->ksz8863_MemData.Interrupt_SC_bit.P1_P2_Link_Change = 1;
            if(ksz8863->hw_w((char)Interrupt_SR_Addr,(char *)&(ksz8863->ksz8863_MemData.Interrupt_SC),1))
                return 1;
        }
        break;
    case ksz8863_P3_Link_Changes:
        if(ksz8863->ksz8863_MemData.Interrupt_SC_bit.P3_Link_Change)
        {
            ksz8863->ksz8863_MemData.Interrupt_SC = 0;
            ksz8863->ksz8863_MemData.Interrupt_SC_bit.P3_Link_Change = 1;
            if(ksz8863->hw_w((char)Interrupt_SR_Addr,(char *)&(ksz8863->ksz8863_MemData.Interrupt_SC),1))
                return 1;
        }
        break;
    case ksz8863_P2_Link_Changes:
        if(ksz8863->ksz8863_MemData.Interrupt_SC_bit.P2_Link_Change)
        {
            ksz8863->ksz8863_MemData.Interrupt_SC = 0;
            ksz8863->ksz8863_MemData.Interrupt_SC_bit.P2_Link_Change = 1;
            if(ksz8863->hw_w((char)Interrupt_SR_Addr,(char *)&(ksz8863->ksz8863_MemData.Interrupt_SC),1))
                return 1;
        }
        break;
    case ksz8863_P1_Link_Changes:
        if(ksz8863->ksz8863_MemData.Interrupt_SC_bit.P1_MII_link_Change)
        {
            ksz8863->ksz8863_MemData.Interrupt_SC = 0;
            ksz8863->ksz8863_MemData.Interrupt_SC_bit.P1_MII_link_Change = 1;
            if(ksz8863->hw_w((char)Interrupt_SR_Addr,(char *)&(ksz8863->ksz8863_MemData.Interrupt_SC),1))
                return 1;
        }
        break;
    default:
        return 1;
        break;
    }

    if(ksz8863->hw_r((char)Interrupt_SR_Addr,(char *)&(ksz8863->ksz8863_MemData.Interrupt_SC),1))
        return 1;

    return 0;
}

/**
 * @brief 获取连接状态，不支持端口3，端口3连接状态一直为good
 * 
 * @param ksz8863 
 * @param portn 0 = 端口1 ，1 = 端口2 ，2 = 未使用
 * @param status 0 = not good   1 = good
 * @return uint8_t 0 = success  1 = fault
 */
uint8_t ksz8863_get_link_status(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool *status)
{
    switch (portn)
    {
    case ksz8863_port1:
        if(ksz8863->hw_r(Port1_SR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port1_Status),2))
            return 1;
        *status = ksz8863->ksz8863_MemData.Port1_Status_bit.Link_Good;
        break;
    
    case ksz8863_port2:
        if(ksz8863->hw_r(Port2_SR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port2_Status),2))
            return 1;
        *status = ksz8863->ksz8863_MemData.Port2_Status_bit.Link_Good;
        break;
    case ksz8863_port3:
    default:
        return 1;
        break;
    }

    return 0;
}

/**
 * @brief 设置端口3MII接口工作模式，上电默认为PHY模式
 * @note
 *  根据手册，端口1控制其寄存器5 位[7] == 1，不等于1时，该函数会设置为1。
 * @param ksz8863 
 * @param status 
 * @return uint8_t 0 = success  1 = fault
 */
uint8_t ksz8863_port3_set_MII_Mode(struct ksz8863 *ksz8863,bool status)
{
    if(ksz8863->ksz8863_MemData.Port1_ctl5_bit.Port3_MII_Mode != 1)
    {
        ksz8863->ksz8863_MemData.Port1_ctl5_bit.Port3_MII_Mode = 1;
        if(ksz8863->hw_w(Port1_CR5_Addr,(char *)&(ksz8863->ksz8863_MemData.Port1_ctl5),1))
            return 1;
        if(ksz8863->hw_r(Port1_CR5_Addr,(char *)&(ksz8863->ksz8863_MemData.Port1_ctl5),1))
            return 1;
    }
    if(ksz8863->ksz8863_MemData.Port3_ctl5_bit.Port3_MII_Mode == status)
        return 0;
    ksz8863->ksz8863_MemData.Port3_ctl5_bit.Port3_MII_Mode = status;
    if(ksz8863->hw_w(Port3_CR5_Addr,(char *)&(ksz8863->ksz8863_MemData.Port3_ctl5),1))
        return 1;
    if(ksz8863->hw_r(Port3_CR5_Addr,(char *)&(ksz8863->ksz8863_MemData.Port3_ctl5),1))
        return 1;
    return 0;
}

/**
 * @brief 设置端口3 RMII接口基准时钟是否翻转
 * 
 * @param ksz8863 
 * @param status 0 = 不翻转 1 = 翻转
 * @return uint8_t  0 = success 1 = fault
 */
uint8_t ksz8863_port3_RMII_clk_invert(struct ksz8863 *ksz8863,bool status)
{
    if(ksz8863->ksz8863_MemData.Port3_Q0_IDRL_bit.RMII_Refclk_Invert == status)
        return 0;
    ksz8863->ksz8863_MemData.Port3_Q0_IDRL_bit.RMII_Refclk_Invert = status;

    if(ksz8863->hw_w(Port3_Q0_IDRL_Addr,(char *)&(ksz8863->ksz8863_MemData.Port3_Q0_IDRL),1))
        return 1;
    if(ksz8863->hw_r(Port3_Q0_IDRL_Addr,(char *)&(ksz8863->ksz8863_MemData.Port3_Q0_IDRL),1))
        return 1;
    return 0;
}

/**
 * @brief 打开或者关闭端口n 4×分离队列
 * 
 * @param ksz8863 
 * @param portn 端口号 0 = 端口1 ，1 = 端口2 ，2 = 端口3
 * @param status 0 = 不打开4×分离队列 1= 打开4×分离队列
 * @return uint8_t  0 = success 1 = fault
 */
uint8_t ksz8863_turn_on_off_TXQ_Split(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool status)
{
    switch(portn)
    {
        case ksz8863_port1:
            if(status == true)
            {
                if(ksz8863->hw_r(Port1_CR2_Addr,(char *)&(ksz8863->ksz8863_MemData.Port1_ctl2),1))
                    return 1;
                if(ksz8863->ksz8863_MemData.Port1_ctl2_bit._2Queue_Sp_of_Tx_En)
                {
                    ksz8863->ksz8863_MemData.Port1_ctl2_bit._2Queue_Sp_of_Tx_En = 0;
                    if(ksz8863->hw_w(Port1_CR2_Addr,(char *)&(ksz8863->ksz8863_MemData.Port1_ctl2),1))
                        return 1;
                    if(ksz8863->hw_r(Port1_CR2_Addr,(char *)&(ksz8863->ksz8863_MemData.Port1_ctl2),1))
                        return 1;
                }
            }
            if(ksz8863->ksz8863_MemData.Port1_ctl0_bit.TXQ_Split_En == status)
                return 0;
            ksz8863->ksz8863_MemData.Port1_ctl0_bit.TXQ_Split_En = status;

            if(ksz8863->hw_w(Port1_CR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port1_ctl0),1))
                return 1;
            if(ksz8863->hw_r(Port1_CR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port1_ctl0),1))
                return 1;
            break;

        case ksz8863_port2:
            if(status == true)
            {
                if(ksz8863->hw_r(Port2_CR2_Addr,(char *)&(ksz8863->ksz8863_MemData.Port2_ctl2),1))
                    return 1;
                if(ksz8863->ksz8863_MemData.Port2_ctl2_bit._2Queue_Sp_of_Tx_En)
                {
                    ksz8863->ksz8863_MemData.Port2_ctl2_bit._2Queue_Sp_of_Tx_En = 0;
                    if(ksz8863->hw_w(Port2_CR2_Addr,(char *)&(ksz8863->ksz8863_MemData.Port2_ctl2),1))
                        return 1;
                    if(ksz8863->hw_r(Port2_CR2_Addr,(char *)&(ksz8863->ksz8863_MemData.Port2_ctl2),1))
                        return 1;
                }
            }
            if(ksz8863->ksz8863_MemData.Port2_ctl0_bit.TXQ_Split_En == status)
                return 0;
            ksz8863->ksz8863_MemData.Port2_ctl0_bit.TXQ_Split_En = status;

            if(ksz8863->hw_w(Port2_CR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port2_ctl0),1))
                return 1;
            if(ksz8863->hw_r(Port2_CR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port2_ctl0),1))
                return 1;
            break;
        
        case ksz8863_port3:
            if(status == true)
            {
                if(ksz8863->hw_r(Port3_CR2_Addr,(char *)&(ksz8863->ksz8863_MemData.Port3_ctl2),1))
                    return 1;
                if(ksz8863->ksz8863_MemData.Port3_ctl2_bit._2Queue_Sp_of_Tx_En)
                {
                    ksz8863->ksz8863_MemData.Port3_ctl2_bit._2Queue_Sp_of_Tx_En = 0;
                    if(ksz8863->hw_w(Port3_CR2_Addr,(char *)&(ksz8863->ksz8863_MemData.Port3_ctl2),1))
                        return 1;
                    if(ksz8863->hw_r(Port2_CR3_Addr,(char *)&(ksz8863->ksz8863_MemData.Port3_ctl2),1))
                        return 1;
                }
            }
            if(ksz8863->ksz8863_MemData.Port3_ctl0_bit.TXQ_Split_En == status)
                return 0;
            ksz8863->ksz8863_MemData.Port3_ctl0_bit.TXQ_Split_En = status;

            if(ksz8863->hw_w(Port3_CR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port3_ctl0),1))
                return 1;
            if(ksz8863->hw_r(Port3_CR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port3_ctl0),1))
                return 1;
            break;

        default:
            break;
    }
    return 0;
}

/**
 * @brief 打开关闭端口n 802.1p优先级功能
 * 
 * @param ksz8863 
 * @param portn 端口号 0 = 端口1 ，1 = 端口2 ，2 = 端口3
 * @param status 0 = 关闭802.1p优先级功能 1 = 打开802.1p优先级功能
 * @return uint8_t 0 = success  1 = fault
 */
uint8_t ksz8863_turn_on_off_802_1p_prio(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool status)
{
    switch (portn)
    {
    case ksz8863_port1:
        if(ksz8863->ksz8863_MemData.Port1_ctl0_bit._802_1p_prio_Class_En == status)
            return 0;
        ksz8863->ksz8863_MemData.Port1_ctl0_bit._802_1p_prio_Class_En = status;
        if(ksz8863->hw_w(Port1_CR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port1_ctl0),1))
            return 1;
        if(ksz8863->hw_r(Port1_CR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port1_ctl0),1))
            return 1;
        break;
    
    case ksz8863_port2:
        if(ksz8863->ksz8863_MemData.Port2_ctl0_bit._802_1p_prio_Class_En == status)
            return 0;
        ksz8863->ksz8863_MemData.Port2_ctl0_bit._802_1p_prio_Class_En = status;
        if(ksz8863->hw_w(Port2_CR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port2_ctl0),1))
            return 1;
        if(ksz8863->hw_r(Port2_CR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port2_ctl0),1))
            return 1;
        break;

    case ksz8863_port3:
        if(ksz8863->ksz8863_MemData.Port3_ctl0_bit._802_1p_prio_Class_En == status)
            return 0;
        ksz8863->ksz8863_MemData.Port3_ctl0_bit._802_1p_prio_Class_En = status;
        if(ksz8863->hw_w(Port3_CR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port3_ctl0),1))
            return 1;
        if(ksz8863->hw_r(Port3_CR0_Addr,(char *)&(ksz8863->ksz8863_MemData.Port3_ctl0),1))
            return 1;
        break;

    default:
        break;
    }
    return 0;
}


