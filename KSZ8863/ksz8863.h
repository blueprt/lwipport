/**
 * @file ksz8863.h
 * @author chentao
 * @brief 
 * @version 0.1
 * @date 2022-08-23
 * 
 * -# ksz8863支持标准和非标准MII接口：
 * 标准SMI接口可以访问标准MIIM寄存器[0:5]和两个用户MIIM寄存器[29,31]，最大速率5MHz，时序如下：
 *          前导      起始帧     读写OP码       PHY地址[4:0]      寄存器地址[4:0]      TA              数据[15:0]            空闲
 * 读        32位1        01          10              AAAAA               RRRRR           Z0              DDDDDDDD_DDDDDDDD       z
 * 写        32位1        01          01              AAAAA               RRRRR           10              DDDDDDDD_DDDDDDDD       z
 * 非标准SMI接口可以访问所有配置寄存器，包括全局、端口和高级控制寄存器0-198(0x00-0xc6)，以及间接访问标准MII寄存器[0:5]和自定义MII寄存器[29:31],时序如下：
 *          前导      起始帧     读写OP码       PHY地址[4:0]      寄存器地址[4:0]      TA              数据[15:0]            空闲
 * 读        32位1        01          00              1xAAA               RRRRR           Z0              DDDDDDDD_DDDDDDDD       z
 * 写        32位1        01          00              0xAAA               RRRRR           Z0              DDDDDDDD_DDDDDDDD       z
 * 使用非标准接口读写0-196号寄存器时，PHY地址[2:0]和寄存器地址[4:0]连接形成8bit地址，即[PHY地址[2:0]:寄存器地址[4:0]]=要访问的寄存器地址[7:0]
 * TA位是'Z0'，处理器MDIO引脚从输出模式改为输入高阻态，0是设备响应
 * 当写入寄存器时，TA位被置为[10].
 * 所有寄存器是8bit数据宽度
 * 对于读操作，数据[15:8]读回'0'，对于写操作，KSZ芯片会忽略数据[15:8]，所以'0''1'均可
 * 
 * -# I2C客户端：
 * 当将ksz8863配置为I2C从设备（P2LED[1:0] = 01）时，
 * CPU可以通过I2C总线访问所有198个寄存器，同时对静态MAC表、VLAN表、动态MAC表和MIB计数器进行间接访问。使用寄存器121到131.
 * 读写时序同EEPROM。读/写控制通过两个固定的8位设备地址来寻址。10111111B = 读，10111110B = 写
 * 字节序：1、start      2、读/写控制字    ACK     3、读写地址      ACK     4、读写数据 ...      ACK     n、stop
 * 
 * -# SPI客户端：
 * 当将ksz8863配置为I2C从设备（P2LED[1:0] = 10）时，
 * CPU可以通过I2C总线访问所有198个寄存器，同时对静态MAC表、VLAN表、动态MAC表和MIB计数器进行间接访问。使用寄存器121到131.
 * 读写使用标准SPI命令。0x03 = 读，0x02 = 写。支持多读多写，即在一次读、写后继续拉低片选，给出时钟，KSZ8863内部寄存器地址会自动加1。
 * SPI速度最高可达25Mhz
 * 
 * SPI->clk = 常高，上升沿有效
 * 字节序：1、读/写控制字(0x03 = 读，0x02 = 写)      2、读写地址      3、读写数据  ...
 * 
 * 
 * 
 * -# 环回支持：
 *  远端环回：远端环回是在KSZ8863MLL/FLL/RLL的两个PHY端口之间进行的。用于诊断目的的环回每次被限制在几个包内，不能支持大流量。
 * 环回路径从“发起”PHY端口的接收输入(RXP/RXM)开始，绕到“发起”PHY端口的PMD/PMA，并结束于“发起”PHY端口的发送输出(TXP/TXM)。
 * 寄存器29和寄存器45的[0]位分别用于对端口1和端口2启用远端环回。或者，MII管理寄存器0，位[14]可以用来启用远端环回。
 *  近端(远端)环回在KSZ8863MLL/FLL/RLL的PHY端口1或PHY端口2进行。环回路径从PHY端口的接收输入(RXPx/RXMx)开始，缠绕在同一个PHY端口的PMD/PMA，
 * 结束于PHY端口的发送输出(TXPx/TXMx)。寄存器26和寄存器42的[1]位分别用于对端口1和端口2启用近端环回。或者，MII管理寄存器31，位[1]可以用来启用近端环回。
 * 
 * 
 * 
 * -# 全双工流量控制：
 * KSZ8863MLL/FLL/RLL在收发端均支持IEEE 802.3x标准流量控制帧。
 * 
 * 在接收端，如果KSZ8863MLL/FLL/RLL接收到一个暂停控制帧，KSZ8863MLL/FLL/RLL不会发送下一个正常帧，直到暂停控制帧中指定的定时器过期。
 * 如果在当前定时器过期前接收到另一个暂停帧，则在第二个暂停帧中用新的值更新定时器。在此期间(虽然是流量控制)，只传输KSZ8863MLL/FLL/RLL的流量控制报文。
 * 
 * 在传输端，KSZ8863MLL/FLL/RLL具有智能和有效的方法来确定何时调用流控制。流控制基于系统资源的可用性，包括可用的缓冲区、可用的传输队列和可用的接收队列。
 * KSZ8863MLL/FLL/RLL将对刚刚收到数据包的端口进行流控制，如果目的端口资源繁忙。KSZ8863MLL/FLL/RLL发布流量控制帧(XOFF)，包含IEEE 802.3x标准定义的最大暂停时间。
 * 一旦资源被释放，KSZ8863MLL/FLL/RLL发送另一个流量控制帧(XON)，零暂停时间关闭流量控制(打开到端口的传输)。提供了一种迟滞特性，以防止流动控制机构不断被激活和关闭。
 * KSZ8863MLL/FLL/RLL流控制所有端口，如果接收队列已满。
 * 
 * 
 * 
 * -# 半双工Backpreure：
 * 提供了半双工Backpreure选项(不在IEEE 802.3标准中)。激活和去激活条件与全双工流量控制相同。如果需要Backpreure，KSZ8863MLL/FLL/RLL发送前导来延迟其他站点的传输(载波感知延迟)。
 * 
 * 为了避免jabber和excessive deference(按照IEEE 802.3标准的定义)，在一段时间后，KSZ8863MLL/ FLL/RLL中断载波侦听，然后迅速再次提高载波侦听。这种短暂的静默时间(没有载波感知)阻止其他站点发送包，
 * 从而使其他站点处于载波感知延迟状态。如果端口在Backpreure情况下有报文要发送，则载波感应反压中断，转而发送这些报文。如果没有额外的数据包要发送，载波感知型反压将再次被激活，直到交换机资源被释放。
 * 如果发生冲突，则跳过二进制指数回退算法，立即生成载波感知，从而减少再次发生冲突的机会，并保持载波感知，从而防止报文接收。
 * 
 * 为了保证在10BASE-T或100BASE-TX半双工模式下不丢包，用户必须开启以下功能:
 * 侵略性回退(寄存器3 (Ox03)，位[0])
 * 无过多碰撞掉落(寄存器4 (Ox04)，位[3])
 * 注意:这些位没有设置为默认值，因为它不是IEEE标准。
 * 
 * 
 * 
 * -# IEEE 802.1Q VLAN支持：
 * KSZ8863MLL/FLL/RLL支持IEEE 802.1Q规范中4096个可能的vlan中的16个活动vlan。KSZ8863MLL/FLL/RLL提供了一个16项的VLAN表，它将12位的VLAN ID (VID)转换为4位的Filter ID (FID)，
 * 用于地址查找。如果收到不带标签或带null-VID标签的报文，则使用入接口默认VID进行查找。VLAN模式下，查找过程从查找VLAN Table开始，判断VID是否有效。
 * 如果VID不合法，则丢弃该报文，不学习其地址。如果VID有效，则检索FID以进行进一步查找。FID和Destination Address (FID+DA)用于确定目的端口。使用FID和源地址(FID+SA)进行地址学习。
 * 
 * KSZ8863MLL/FLL/RLL还支持VLAN高级特性，如“入口VLAN过滤”和“丢弃非PVID报文”。这些特性可以在每个端口的基础上设置，并分别在寄存器18、34和50中为端口1、2和3定义。
 * 
 * -# qos优先级支持：
 * KSZ8863MLL/FLL/RLL为VolP和视频会议等应用提供服务质量(QoS)。每个端口提供4个优先级队列，每个端口传输队列可以分为4个优先级队列:队列3是最高优先级队列，队列O是最低优先级队列。
 * 寄存器16、寄存器32、寄存器48的位[0]分别用于使能端口1、端口2、端口3的分离传输队列。如果端口的发送队列没有拆分，高优先级和低优先级的报文在发送队列中的优先级相等。还有一个附加选项，
 * 可以始终首先交付高优先级数据包，或者对四个优先级队列使用加权公平排队。这个全局选项在寄存器5的位[3]中设置和解释。
 * 
 * -# 出口优先级：
 * 基于端口的优先级，每个入口端口被单独分类为高优先级接收端口。高优先级接收端口接收到的所有报文都被标记为高优先级，如果相应的发送队列被拆分，则发送到高优先级发送队列。
 * 使用寄存器16、32和48的位[4:3]分别使能端口1、端口2和端口3的基于端口的优先级。
 * 
 * -# 802.1 p-based优先级：
 * 对于基于802.1p的优先级，KSZ8863MLL/FLL/RLL检查入(入)包，以确定它们是否被标记。如果标记了，将检索VLAN标记中的3位优先级字段，
 * 并与寄存器12和13指定的“优先级映射”值进行比较。“优先级映射”值是可编程的。
 * 
 * 端口1、端口2、端口3的寄存器16、32、48的位[5]使能基于802.1p的优先级。KSZ8863MLL/FLL/RLL提供了在每个单独的出口端口插入或删除优先级标记帧的头的选项。
 * 该头部由2字节的VPID (VLAN Protocol ID)和2字节的TCI (Tag Control Information field)组成，也被称为IEEE 802.1Q VLAN Tag。
 * 标签插入通过端口寄存器控制0的位[2]和寄存器194使能，分别用于选择端口1、端口2和端口3的出端口可以插入哪个源端口(入端口)PVID。在出端口，不带标签的报文被贴上入端口的默认标签。
 * 默认标记分别为端口1、2和3的寄存器集[19,20]、[35,36]和[51,52]编程;源端口VID必须按寄存器194的位[5:0]插入到选定的出口端口。
 * KSZ8863MLL/FLL/RLL不会对已经标记的数据包添加标记。端口1、2和3的寄存器16、32和48的位[1]启用Tag Removal。在出口端口，带标签的报文的802.1Q VLAN tag将被删除。
 * 
 * KSZ8863MLL/FLL/RLL不修改未标记的报文。对于标签插入和标签移除，都要重新计算CRC。
 * 
 * 802.1p优先级字段重映射是一个QoS特性，允许KSZ8863MLL/FLL/RLL在任何入口端口设置“用户优先级上限”。
 * 如果入接口报文的优先级字段高于入接口端口的默认标签的优先级字段，则该报文的优先级字段将替换为默认标签的优先级字段。
 * 
 * 
 * -# DIFFSERV-BASED优先级：
 * 基于差分服务的优先级使用ToS寄存器(寄存器96到111)在高级控制寄存器部分。Tos优先级控制寄存器实现了一个完全解码的、64位差异化服务码点(DSCP)寄存器，
 * 从IP报头中的6位Tos字段确定数据包的优先级。当ToS字段最有效的6位被完全解码后，64个可能的结果将与DSCP寄存器中相应的位进行比较以确定优先级。
 * 
 * 
 * 
 * -# 尾标记模式：
 * 只有端口3接口才能看到并使用Tail Tag，该端口3应该连接到处理器。对于生成树协议IGMP snooping和其他应用来说，获取入端口信息是一种有效的方法。
 * 一个字节尾标记中的第1位和第0位用于表示端口3中的源端口或目的端口。位3和位2用于设置端口3的入口帧的优先级。其他位没有被使用。通过设置寄存器3位6来启用尾标记功能。
 * 
 * -# IGMP的支持：
 * KSZ8863MLL/FLL/RLL为支持IGMP (Internet Group Management Protocol)协议在第二层提供了两个组件:
 * IGMP SNOOPING
 * KSZ8863MLL/FLL/RLL对IGMP报文进行trap处理，只将IGMP报文转发给处理器(端口3)。IGMP报文被标识为IP报文(Ethernet IP报文或IEEE 802.3 SNAP IP报文)，IP版本号为Ox4，协议版本号为Ox2。
 * 将igmp发送回订阅端口
 * 主机一旦对收到的IGMP报文做出响应，就需要知道IGMP的原始入口端口，并只将IGMP报文发送回该端口。否则该IGMP报文会广播到所有端口，降低性能。启用尾标记模式后，
 * 主机将知道从尾标记位[0]接收到的IGMP报文端口，并通过设置尾标记位[1,0]将响应IGMP报文发送回该订阅端口。通过设置寄存器3位6来启用“尾标记模式”。当IGMP报文从订阅端口发出时，该报文的尾标签会自动移除。
 * 
 * 
 * 
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __KSZ_8863_H
#define __KSZ_8863_H

#include "ksz8863_reg.h"
#include <stdbool.h>

/**
 * @brief ksz8863硬件读写接口功能码
 * 
 */
typedef enum wrcode
{
    ksz8863_Wirte = 0,
    ksz8863_Read
}wrcode_def;

/**
 * @brief ksz8863端口中断源
 * 
 */
typedef enum ksz8863_Interrupt
{
    ksz8863_P1_P2_Link_Changes = 0,
    ksz8863_P3_Link_Changes,
    ksz8863_P2_Link_Changes,
    ksz8863_P1_Link_Changes
}ksz8863_Interrupt_def;

typedef enum ksz8863_portn
{
    ksz8863_port1 = 0,
    ksz8863_port2,
    ksz8863_port3
}ksz8863_portn_def;

/**
 * @brief ksz8863结构
 * 
 */
typedef struct ksz8863
{
    ksz8863_MemData_def ksz8863_MemData;

    uint8_t (*hw_reset)(void);
    uint8_t (*hw_w)(uint8_t Memaddr,char *data,uint8_t datalen);
    uint8_t (*hw_r)(uint8_t Memaddr,char *data,uint8_t datalen);

    uint8_t (*software_reset)(struct ksz8863 *ksz8863);
    uint8_t (*pcs_reset)(struct ksz8863 *ksz8863);
    uint8_t (*turn_on_off_AN)(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool status);
    uint8_t (*Restart_AN)(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool *speed,bool *duplex);
    uint8_t (*set_port_def_speed_duplex)(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool speed,bool duplex);
    uint8_t (*get_port_speed_duplex)(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool *speed,bool *duplex);
    uint8_t (*set_port3_macaddr)(struct ksz8863 *ksz8863,uint8_t *macaddr);
    uint8_t (*Interrupt_En)(struct ksz8863 *ksz8863,ksz8863_Interrupt_def Interrupt_SRC,bool status);
    uint8_t (*get_Interrupt_status)(struct ksz8863 *ksz8863,ksz8863_Interrupt_def Interrupt_SRC,bool *status);
    uint8_t (*clear_Interrupt_status)(struct ksz8863 *ksz8863,ksz8863_Interrupt_def Interrupt_SRC);
    uint8_t (*get_link_status)(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool *status);
    uint8_t (*port3_set_MII_Mode)(struct ksz8863 *ksz8863,bool status);
    uint8_t (*port3_RMII_clk_invert)(struct ksz8863 *ksz8863,bool status);
    uint8_t (*turn_on_off_TXQ_Split)(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool status);
    uint8_t (*turn_on_off_802_1p_prio)(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool status);
}ksz8863_def;

uint8_t ksz8863(ksz8863_def *ksz8863,\
                uint8_t (*hw_rsert)(void),
                uint8_t (*mii_rmii_init_handle)(void),\
                uint8_t (*hw_init_handle)(void),\
                uint8_t (*hw_w)(uint8_t Memaddr,char *data,uint8_t datalen),\
                uint8_t (*hw_r)(uint8_t Memaddr,char *data,uint8_t datalen));

uint8_t ksz8863_software_reset(struct ksz8863 *ksz8863);
uint8_t ksz8863_pcs_reset(struct ksz8863 *ksz8863);
uint8_t ksz8863_turn_on_off_AN(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool status);
uint8_t ksz8863_Restart_AN(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool *speed,bool *duplex);
uint8_t ksz8863_set_port_def_speed_duplex(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool speed,bool duplex);
uint8_t ksz8863_get_port_speed_duplex(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool *speed,bool *duplex);
uint8_t ksz8863_set_port3_macaddr(struct ksz8863 *ksz8863,uint8_t *macaddr);
uint8_t ksz8863_Interrupt_En(struct ksz8863 *ksz8863,ksz8863_Interrupt_def Interrupt_SRC,bool status);
uint8_t ksz8863_get_Interrupt_status(struct ksz8863 *ksz8863,ksz8863_Interrupt_def Interrupt_SRC,bool *status);
uint8_t ksz8863_clear_Interrupt_status(struct ksz8863 *ksz8863,ksz8863_Interrupt_def Interrupt_SRC);
uint8_t ksz8863_get_link_status(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool *status);
uint8_t ksz8863_port3_set_MII_Mode(struct ksz8863 *ksz8863,bool status);
uint8_t ksz8863_port3_RMII_clk_invert(struct ksz8863 *ksz8863,bool status);
uint8_t ksz8863_turn_on_off_TXQ_Split(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool status);
uint8_t ksz8863_turn_on_off_802_1p_prio(struct ksz8863 *ksz8863,ksz8863_portn_def portn,bool status);
#endif /*__KSZ_8863_H*/

s