/**
 * @file lan8720.c
 * @author chentao
 * @brief 
 * @version 0.1
 * @date 2022-09-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "lan8720.h"
#include <string.h>

/**
 * @brief 
 * 
 * @param lan8720 lan8720结构
 * @param PHY_Addr lan8720芯片地址
 * @param hw_reset 硬件复位
 * @param hw_w SMI写接口,其返回值 （0 = success 1 = fault）
 * @param hw_r SMI读接口,其返回值 （0 = success 1 = fault）
 * 
 */
void lan8720(struct lan8720 *lan8720,\
            uint16_t PHY_Addr,\
            uint8_t (*hw_reset)(void),\
            uint8_t (*hw_w)(uint8_t phy_addr,uint8_t reg_addr,uint16_t data),\
            uint8_t (*hw_r)(uint8_t phy_addr,uint8_t reg_addr,uint16_t *data))
{
    lan8720->PHY_Addr = PHY_Addr;

    if(hw_reset != NULL)
    {
        lan8720->hw_reset = hw_reset;
        lan8720->hw_reset();
    }

    lan8720->hw_w = hw_w;
    lan8720->hw_r = hw_r;

    lan8720->soft_reset = lan8720_soft_reset;
    lan8720->Restart_AN = lan8720_Restart_AN;
    lan8720->get_link_status = lan8720_get_link_status;
}

/**
 * @brief lan8720 软件重启
 * 
 * @param lan8720 
 * @return uint8_t 0 = success   1 = fault
 */
uint8_t lan8720_soft_reset(struct lan8720 *lan8720)
{
    if(lan8720->hw_r(lan8720->PHY_Addr,BCR,&(lan8720->Lan8720_Memdata.BCR)))
        return 1;

    lan8720->Lan8720_Memdata.BCR_bit.Soft_Reset = 1;

    if(lan8720->hw_w(lan8720->PHY_Addr,BCR,lan8720->Lan8720_Memdata.BCR))
        return 1;

    return 0;
}

/**
 * @brief 重启lan8720自动协商，并获取协商结果，当自动协商功能未使能时，此函数会打开使能
 * 
 * @param lan8720 
 * @param speed 协商正常时，连接速率
 * @param duplex 协商正常时，工作模式
 * @return uint8_t 0 = success   1 = fault
 */
uint8_t lan8720_Restart_AN(struct lan8720 *lan8720,bool *speed,bool *duplex)
{
    uint16_t temtime = 0;
    if(lan8720->hw_r(lan8720->PHY_Addr,BCR,&(lan8720->Lan8720_Memdata.BCR)))
        return 1;
    
    lan8720->Lan8720_Memdata.BCR_bit.AN_En = 1;
    lan8720->Lan8720_Memdata.BCR_bit.Restart_AN = 1;

    if(lan8720->hw_w(lan8720->PHY_Addr,BCR,lan8720->Lan8720_Memdata.BCR))
        return 1;
    
    do
    {
        temtime ++ ;
        if(lan8720->hw_r(lan8720->PHY_Addr,BSR,&(lan8720->Lan8720_Memdata.BSR)))
            return 1;
    } while (((lan8720->Lan8720_Memdata.BSR_bit.AN_Done == 0) || (lan8720->Lan8720_Memdata.BSR_bit.Link_Status == 0)) && (temtime < 0xffff));
    
    if(temtime >= 0xffff)
        return 1;
    if(lan8720->hw_r(lan8720->PHY_Addr,SCSR,&(lan8720->Lan8720_Memdata.SCSR)))
        return 1;
    
    switch (lan8720->Lan8720_Memdata.SCSR_bit.Speed_Duplex)
    {
    case 1:
        *speed = 0;
        *duplex = 0;
        break;
    case 2:
        *speed = 1;
        *duplex = 0;
        break;
    case 5:
        *speed = 0;
        *duplex = 1;
        break;
    case 6:
        *speed = 1;
        *duplex = 1;
        break;
    default:
        break;
    }

    return 0;
}

/**
 * @brief 获取连接状态
 * 
 * @param lan8720 
 * @param status 连接状态 1 = 连接      0 = 未连接
 * @return uint8_t 0 = success  1 = fault
 */
uint8_t lan8720_get_link_status(struct lan8720 *lan8720,bool *status)
{
    if(lan8720->hw_r(lan8720->PHY_Addr,BSR,&(lan8720->Lan8720_Memdata.BSR)))
        return 1;
    
    *status = lan8720->Lan8720_Memdata.BSR_bit.Link_Status;

    return 0;
}


