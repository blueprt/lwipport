/**
 * @file IP175LLF_reg.h
 * @author 陈涛
 * @brief IP175LLF寄存器地址
 * @version 0.1
 * @date 2023-02-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __IP175LLF_REG_H
#define __IP175LLF_REG_H

typedef enum
{
    IP175LLF_Port0 = 0,
    IP175LLF_Port1,
    IP175LLF_Port2,
    IP175LLF_Port3,
    IP175LLF_Port5 = 5,
    IP175LLF_Sw_CR1 = 20,
    IP175LLF_Sw_CR2,
    IP175LLF_VLAN_CR,
    IP175LLF_VLAN_Table1,
    IP175LLF_VLAN_Table2,
    IP175LLF_Prio_Class,
    IP175LLF_MF,
}IPLLF_PHYID;







/**
 * @brief phy 控制寄存器，端口0~3分别有自己的控制寄存器，端口5也有但不同，且端口有的均为只读。
 * 以下定义中，带PHY0_3前缀的为端口0~3独有
 * 
 */
#define IP175_PHY_CR      0x00
#define IP175_P03_Reset                     0x8000          //相应端口重启
#define IP175_P03_Loop                      0x4000          //相应端口开启回环模式
#define IP175_Speed_Sel                     0x2000          //端口速率选择，端口5 RO且由硬件引脚设置
#define IP175_Nway_En                       0x1000          //自动协商是否启用，端口5 RO且为1
#define IP175_P03_Power_D                   0x0800          //相应端口进入掉电模式
#define IP175_P03_Re_Nway                   0x0200          //重新开始自动协商
#define IP175_Duplex_Sel                    0x0100          //是否全双工，端口5 RO且由硬件引脚设置
#define IP175_P03_Collision_Test            0x0080          //碰撞测试

/**
 * @brief phy 状态寄存器，全部只读，端口0~3分别有自己的控制寄存器，端口5也有但不同。
 * 以下定义中，带PHY0_3前缀的为端口0~3独有
 * IP175LLF支持100Base-X和10Base-T介质全双工能力
 */
#define IP175_PHY_SR            0x01
#define IP175__100Base_X_Full_Duplex        0x4000          //100Base-X 全双工能力
#define IP175__100Base_X_Half_Duplex        0x2000          //100Base-X 半双工能力
#define IP175__10Base_T_Full_Duplex         0x1000          //10Base-T 全双工能力
#define IP175__10Base_T_Half_Duplex         0x0800          //10Base-T 半双工能力
#define IP175_P03_MF                        0x0040          //MF 前导码抑制
#define IP175_Nway_Complete                 0x0020          //自动协商完成
#define IP175_P03_Remote_Fault              0x0010          //远程故障，当读为逻辑 1 时，表示 IP175LLF 检测到远程故障条件。该位设置直到远程故障条件消失并且在读取寄存器内容之前。该位在 IP175LLF复位后清零。
#define IP175_Nway_Ability                  0x0008          //自动协商能力，当读为逻辑 1 时，表明 IP175LLF 具有执行自动协商的能力。
#define IP175_Link_Status                   0x0004          //链接状态
#define IP175_P03_Jabber_Detect             0x0002          //干扰检测，当为100Mbps时，== 0 
#define IP175_Ex_Reg_Cap                    0x0001          //扩展寄存器功能

/**
 * @brief PHY 标识符 1寄存器，公共，支持PHY0~3,RO
 * 显示IP175LLF OUI ID的第3~18位，从第1开始计算，无第0
 * IP175LLF OUI ID = 0x0090C3 二进制是
 *      0000 0000 1001 0000 1100 0011
 *      lsb                         msb
 * 故第3位到第18位是 
 *         0 0000 1001 0000 11           = 0x243,即该寄存器的值是将OUI右移6位后&0xff
 * 
 */
#define IP175_PHY_ID1           0x02
#define IP175_OUI_ID                    0x0090C3

/**
 * @brief PHY 标识符 2寄存器,公共，支持PHY0~3,RO
 * 
 */
#define IP175_PHY_ID2               0x03
#define IP175_PHY_Identifier            0xFC00      //OUI&0x003f
#define IP175_Manu_Model_Num            0x03F0      //ip175llf = 0x18
#define IP175_Revision_Num              0x000F      //ip175llf = 0x00

/**
 * @brief 自动协商通告寄存器
 * 
 */
#define IP175_Nway_AR               0x04
#define IP175_P03_ReFa                  0x2000  //远程故障,同SR寄存器bit4
#define IP175_Pause                     0x0400  //是否具有暂停功能
#define IP175__100Base_TX_Fu_Dup        0x0100  //自动协商时是否支持100Base_Tx_Full，RW
#define IP175__100Base_TX_AN            0x0080
#define IP175__10Base_T_Fu_Dup          0x0040
#define IP175__10Base_TX_AN             0x0020
#define IP175_P03_Selector_Field        0x001f  

/**
 * @brief 自动协商连接者能力寄存器
 * 指示自动协商时，连接对方端口的能力
 */
#define IP175_Nway_LPAR         0x05
#define IP175_P03_L_Next_Page           0x8000  //对方端口是否具有下一页
#define IP175_P03_L_Ack                 0x4000  //对方端口是否已收到能力字
#define IP175_P03_Re_Fa_LPAR            0x2000  //对方端口是否报告远端错误
#define IP175_Pause_LPAR                0x0400  //对方端口是否具有pause能力
#define IP175_P03_L_100Base_T4          0x0200  //对方是否支持00Base_T4
#define IP175_L_100Base_TX_Full_Dup     0x0100  //对方是否支持100Base_TX_Full_Duplex
#define IP175_L_100Base_TX              0x0080  //对方是否支持100Base_TX
#define IP175_L_10Base_TX_Full_Dup      0x0040  //对方是否支持10Base_TX_Full_Duplex
#define IP175_L_10Base_TX               0x0020  //对方是否支持10Base_TX   
#define IP175_P03_L_Selector_Field      0x001F  //对方选择器字段

/**
 * @brief 自动协商扩展寄存器,RO
 *          端口5无此寄存器
 */
#define IP175_Nway_ExR          0x06
#define IP175_P03_Parallel_Det          0x0010
#define IP175_P03_L_isNextPage          0x0008
#define IP175_P03_Recv_New_Page         0x0020
#define IP175_P03_L_Nway_isEn           0x0001  //自动协商启用时，指示对方是否启用自动协商

/**
 * @brief 特殊控制寄存器
 *          端口5无此寄存器
 */
#define IP175_PHY_SCR             0x10
#define IP175_P03_AutoPowerSavingMode       0x0008

/**
 * @brief 特殊状态控制寄存器
 *      端口5无此寄存器
 */
#define IP175_PHY_SSR             0x12
#define IP175_Speed_Mode                0x0800
#define IP175_Duplex_Mode               0x0400

/**
 * @brief MDI_MDIX控制寄存器
 * 
 */
#define IP175_MDI_MDIX_CR         0x16
#define IP175_P3_Auto_MDI_MDIX_En       0x0080
#define IP175_P2_Auto_MDI_MDIX_En       0x0040
#define IP175_P1_Auto_MDI_MDIX_En       0x0020
#define IP175_P0_Auto_MDI_MDIX_En       0x0010
#define IP175_P3_Auto_MDI_MDIX_Sel      0x0008
#define IP175_P2_Auto_MDI_MDIX_Sel      0x0004
#define IP175_P1_Auto_MDI_MDIX_Sel      0x0002
#define IP175_P0_Auto_MDI_MDIX_Sel      0x0001

/*---------------------------------------------------------------PHY地址0x14(20)---------------------------------------------------------------------*/
/**
 * @brief 芯片ID寄存器
 * RO,IP175LLF芯片读出来 == 0x175D
 */
#define IP175_Chip_ID               0x00

/**
 * @brief 软件复位寄存器，软件写入175D时，芯片复位
 * 
 */
#define IP175_Soft_Reset_R      0x02

/**
 * @brief 表锁定寄存器
 * 
 */
#define IP175_Table_Lock_R      0x03
#define IP175_Multi_Field_Table_Lock    0x0002  //多字段表锁定
#define IP175_Address_Table_Lock        0x0001  //地址表锁定

/**
 * @brief MII 强制模式
 * 
 */
#define IP175_MII_Force_Mode_R  0x04
#define IP175_MAC5_FORCE_100            0x8000  //mac5强制100M
#define IP175_MAC5_FORCE_FULL           0x2000  //mac5强制全双工

/**
 * @brief 拥塞控制寄存器
 * 
 */
#define IP175_Congestion_CR     0x05
#define IP175_Cont_Pause                0x0100  //连续发暂停包
#define IP175_Mod_Carrier_Algorithm     0x0080  //改进的基于载体的碰撞算法
#define IP175_Input_Filter              0x0040  //输入过滤器
#define IP175_Drop16                    0x0020  //连续 16 次碰撞后丢弃输入数据包。
#define IP175_MODBCK                    0x0010  //改进的退避冲突算法
#define IP175_BP_KIND                   0x0008  //背压类，0： 基于运营商，1： 基于碰撞
#define IP175_BK_EN                     0x0004  //背压使能
#define IP175_X_EN                      0x0002  //IEEE 802.3x流控使能（5个端口共享寄存器）
#define IP175_MAC_X_En                  0x0001  //MII0-2的流控使能

/**
 * @brief 端口状态寄存器
 * 
 */
#define IP175_Port_State            0x06
#define IP175_P5_Forward_En             0x2000  //开启端口n转发
#define IP175_P4_Forward_En             0x1000
#define IP175_P3_Forward_En             0x0800
#define IP175_P2_Forward_En             0x0400
#define IP175_P1_Forward_En             0x0200
#define IP175_P0_Forward_En             0x0100  //开启端口n学习
#define IP175_P5_Learning_En            0x0020  
#define IP175_P4_Learning_En            0x0010  
#define IP175_P3_Learning_En            0x0008  
#define IP175_P2_Learning_En            0x0004  
#define IP175_P1_Learning_En            0x0002  
#define IP175_P0_Learning_En            0x0001  

/**
 * @brief 错误帧过滤控制寄存器
 * 
 */
#define IP175_Lllegal_Frm_FR    0x07
#define IP175_Long_Frm                  0x0018  //最大帧长度 00 == 1536Bytes(def) 01 == 1552Bytes 10 = 1792Bytes 11 == reserved
#define IP175_MC_SMC                    0x0004  //使用组播源 MAC 地址过滤帧
#define IP175_NULL_MAC                  0x0002  //过滤具有空源或目标 MAC 地址的帧
#define IP175_CRC_ERROR                 0x0001  //过滤 CRC错误帧

/**
 * @brief 特殊包标识寄存器1
 * 保留地址 01-80-c2-00-00-00到01-80-c2-00-00-1f
 */
#define IP175_Spe_Pack_Identi1  0x08
#define IP175_TRAP_RSVD_ADDR1           0xC000  //01-80-c2-00-00-11到01-80-c2-00-00-1f   :的包处理方式。00 == 转发（def）  01 == 转发到CPU 10 == 丢弃 11 == 保留（未使用）
#define IP175_TRAP_ABM                  0x3000  //IEEE 802.1D 定义的所有网桥多播地址保留 MAC 地址为01:80:C2:00:00:10:的包处理方式,同上
#define IP175_TRAP_RSVD_ADDR0           0x0C00  //01:80:C2:00:00:04 至 01:80:C2:00:00:0D，01:80:C2:00:00:0F:的包处理方式，同上
#define IP175_TRAP_LLDP                 0x0300  //链路层发现协议，保留的 MAC 地址为 01:80:C2:00:00:0E，使用以太网类型值 0x88CC 编码的 LLDP 数据单元(LLDPDU)的包处理方式，同上
#define IP175_TRAP_802P1X               0x00C0  //IEEE 802.1X 基于端口的网络访问控制保留 MAC地址为 01:80:C2:00:00:03，同上
#define IP175_TRAP_SP                   0x0030  //IEEE 802 标准协议 – 慢速协议保留 MAC 地址为 01:80:C2:00:00:02，同上
#define IP175_TRAP_PAUSE                0x0004  //陷阱暂停点对点暂停功能保留的 MAC 地址为 01:80:C2:00:00:01，1 == 转发，0 = 丢弃
#define IP175_TRAP_BPDU                 0x0003  //标准生成树协议保留的 MAC 地址为 01:80:C2:00:00:00，00 == 转发（def）  01 == 转发到CPU 10 == 丢弃 11 == 保留（未使用）

/**
 * @brief 特殊包标识寄存器2
 * 保留地址 01-80-C2-00-00-20 to 01-80-C2-00-00-FF
 * 
 */
#define IP175_Spe_Pack_Identi2  0x09
#define IP175_TRAP_RSVD_ADDR3           0x00C0  //保留地址范围 3:01:80:C2:00:00:30 至 01:80:C2:00:00:FF
#define IP175_TRAP_RSVD_ADDR2           0x0030  //保留地址范围 2:01:80:C2:00:00:22 至 01:80:C2:00:00:2F
#define IP175_TRAP_GVRP                 0x000C  //GVRP地址： 01-80-C2-00-00-21
#define IP175_TRAP_GMRP                 0x003c  //GMRP地址： 01-80-C2-00-00-20

/**
 * @brief 杂项特殊数据包识别寄存器1
 * 
 */
#define IP175_MISC_SPack_Identi1    0x0A
#define IP175_TRAP_ICMP                 0xC000  //ICMPv4: TYPE=0x0800 and Protocol=1,ICMPv6: TYPE=0x86DD and Protocol=58
#define IP175_TRAP_MLD_CTRL             0x3000  //MLD 控制包 DMAC=33-33-XXXX-XX-XX EtherType=0x86DD    Version=6   Next Header=58
#define IP175_TRAP_MLD                  0x0C00  //多播侦听器发现 DMAC=33-33-XX-XX-XX-XX    EtherType=0x86DD    Version=6
#define IP175_TRAP_IPM_DATA             0x0300  //IP组播数据包 DMAC=01-00-5E-XX-XX-XX    EtherType=0x0800    Version=4   DIP=224.0.1.0~239.225.225.225   协议不是 IGMP
#define IP175_TRAP_IPM_CTRL             0x00C0  //IP 组播控制包 DMAC=01-00-5E-XX-XX-XX   EtherType=0x0800    Version=4   DIP=224.0.0.x   协议不是 IGMP
#define IP175_TRAP_IGMP                 0x0030  //Internet 组管理协议 DMAC=01-00-5EXX-XX-XX  EtherType=0x0800    Version=4   Protocol = 2(IGMP)
#define IP175_TRAP_RARP                 0x000C  //反向地址解析协议目标 MAC 地址为 FF: FF: FF: FF: FF: FF     并且 Ether-Type字段为 0x8035
#define IP175_TRAP_ARP                  0x0003  //地址解析协议目标 MAC 地址为 FF: FF: FF: FF: FF: FF   并且 Ether-Type字段为 0x0806

/**
 * @brief 杂项特殊数据包识别寄存器2
 * 
 */
#define IP175_MISC_SPack_Identi2    0x0B
#define IP175_TRAP_BOOTP                0x000C  //自举(DHCP)协议端口号=16'd67 或 16'd68
#define IP175_TRAP_PPPoE                0x0003  //以太网点对点协议  以太类型=0x8863 或 0x8864

/**
 * @brief 网络安全寄存器
 * 
 */
#define IP175_Network_Security  0x0C
#define IP175_ILL_SMAC_2CPU             0x4000  //非法SMAC转发
#define IP175_P5_ILL_SMAC_PORT          0x2000  //非法源MAC地址保护
#define IP175_P4_ILL_SMAC_PORT          0x1000
#define IP175_P3_ILL_SMAC_PORT          0x0800
#define IP175_P2_ILL_SMAC_PORT          0x0400
#define IP175_P1_ILL_SMAC_PORT          0x0200
#define IP175_P0_ILL_SMAC_PORT          0x0100
#define IP175_P5_CHK_PORT               0x0020  //根据地址表中的 SMAC 和入口端口号的组合检查帧
#define IP175_P4_CHK_PORT               0x0010
#define IP175_P3_CHK_PORT               0x0008
#define IP175_P2_CHK_PORT               0x0004
#define IP175_P1_CHK_PORT               0x0002
#define IP175_P0_CHK_PORT               0x0001

/**
 * @brief 学习控制寄存器
 * 
 */
#define IP175_Learning_CR       0x0D
#define IP175_Filter_MDMAC              0x0300  //过滤未知多播 DMAC,多播 DMAC 不包括广播 DMAC
#define IP175_Filter_UDMAC              0x00C0  //过滤未知的单播 DMAC
#define IP175_Learn_Dis_Pause           0x0020  //因 PAUSE 帧而无法学习
#define IP175_AT_STR                    0x0008  //地址表结构,0： 单播帧的 2K 地址表（默认）,1： 单播帧1K地址表，组播帧1K地址表
#define IP175_IGMP_Over_VLAN            0x0002  //VLAN上空的IGMP
#define IP175_Learn_Constrain           0x0001  //学习约束,0： 不使用 VLAN 信息（FID）创建哈希键 1：使用 VLAN 信息（FID）创建哈希键

/**
 * @brief 老化时间参数寄存器1
 * 
 */
#define IP175_Aging_Time_Par1_R 0x0E
#define IP175_AGE_Time_Unit             0x0060  //老化时间单位    00 == 1min  01 == 1s    10 = 10ms   11 = 快速模式。这种模式将使整个表老化1~2毫秒。对于某些特殊应用（例如 RSTP）需要尽快清理表。独立于 AGE_Time_Val
#define IP175_AGE_Time_Val              0x001F  //老化时间      00 == 无老化   老化时间 = AGE_Time_Unit * AGE_Time_Val

/**
 * @brief 老化时间参数寄存器2
 * 
 */
#define IP175_Aging_Time_Par2_R 0x0F
#define IP175_PID_En                    0x0100  //如果设置，则老化模块老化端口 ID 匹配的条目PID_Val
#define IP175_PID_Val                   0x00E0  //000：保留        001:端口0 010:端口1 011:端口2 100:端口3 101:端口4 110:端口5 other:保留
#define IP175_FID_En                    0x0010  //如果设置，则老化模块老化 FID 匹配的条目FID_VAL
#define IP175_FID_al                    0x000F

/**
 * @brief 广播风暴保护寄存器1
 * 
 */
#define IP175_BroCas_Sto_Pro1_R 0x10
#define IP175_P5_BF_STM_EN              0x2000  //广播风暴使能.如果排队的广播数达到超过阈值则丢弃传入数据包。该阈值在寄存器20.17~20.19（同PHY地址）中定义 
#define IP175_P4_BF_STM_EN              0x1000
#define IP175_P3_BF_STM_EN              0x0800
#define IP175_P2_BF_STM_EN              0x0400
#define IP175_P1_BF_STM_EN              0x0200
#define IP175_P0_BF_STM_EN              0x0100

#define IP175_P5_BF_FFFF_ONLY           0x0020  //1:广播风暴保护不包含组播报文。IP175LLF仅在达到广播阈值(默认值)时丢弃DA等于0xFFFFFFFF的数据包。0:广播风暴保护，包括组播报文。当达到广播阈值时，IP175LLF丢弃DA等于0xFFFFFFFFF或多播地址的报文。
#define IP175_P4_BF_FFFF_ONLY           0x0010
#define IP175_P3_BF_FFFF_ONLY           0x0008
#define IP175_P2_BF_FFFF_ONLY           0x0004
#define IP175_P1_BF_FFFF_ONLY           0x0002
#define IP175_P0_BF_FFFF_ONLY           0x0001

/**
 * @brief 广播风暴保护寄存器2
 * 
 */
#define IP175_BroCas_Sto_Pro2_R 0x11
#define IP175_BF_STM_THR_1              0xFF00  //端口 1 的广播风暴阈值设置,当连接为100Mbps时，阈值范围为1 ~ 255包/10ms;当连接为10Mbps时，阈值范围为1 ~ 255包/100ms
#define IP175_BF_STM_THR_0              0x00FF

/**
 * @brief 广播风暴保护寄存器3
 * 
 */
#define IP175_BroCas_Sto_Pro3_R 0x12
#define IP175_BF_STM_THR_3              0xFF00  //端口 3 的广播风暴阈值设置,当连接为100Mbps时，阈值范围为1 ~ 255包/10ms;当连接为10Mbps时，阈值范围为1 ~ 255包/100ms
#define IP175_BF_STM_THR_2              0x00FF

/**
 * @brief 广播风暴保护寄存器4
 * 
 */
#define IP175_BroCas_Sto_Pro4_R 0x13
#define IP175_BF_STM_THR_5              0xFF00  //端口 5 的广播风暴阈值设置,当连接为100Mbps时，阈值范围为1 ~ 255包/10ms;当连接为10Mbps时，阈值范围为1 ~ 255包/100ms
#define IP175_BF_STM_THR_4              0x00FF

/**
 * @brief 端口镜像寄存器1
 * 
 */
#define IP175_Port_Mirror1_R    0x14
#define IP175_PORT_MIRROR_EN            0x8000  //端口镜像使能
#define IP175_PORT_MIRROR_MODE          0x6000  //端口进行模式    00:镜像RX的一个端口（默认）    
                                                //01:镜像TX的一个端口（默认）  
                                                //10:镜像源-目标对（TX 和 RX 的端口必须不同）   
                                                //11:镜像TX 和 RX 的一个端口（TX 和 RX 的端口必须相同）
#define IP175_P5_SEL_RX_PORT_MIRROR     0x0020  //选择要镜像的源（接收）端口,P5
#define IP175_P4_SEL_RX_PORT_MIRROR     0x0010  //选择要镜像的源（接收）端口,P4
#define IP175_P3_SEL_RX_PORT_MIRROR     0x0008  //选择要镜像的源（接收）端口,P3
#define IP175_P2_SEL_RX_PORT_MIRROR     0x0004  //选择要镜像的源（接收）端口,P2
#define IP175_P1_SEL_RX_PORT_MIRROR     0x0002  //选择要镜像的源（接收）端口,P1
#define IP175_P0_SEL_RX_PORT_MIRROR     0x0001  //选择要镜像的源（接收）端口,P0

/**
 * @brief 端口镜像寄存器2
 * 
 */
#define IP175_Port_Mirror2_R    0x15
#define IP175_SEL_MIRROR_PORT           0x7000  //选择一个镜像端口来监控任何其他端口,000:端口0 001:端口1 010:端口2 011:端口3 100:端口4 101:端口5
#define IP175_SEL_TX_PORT_MIRROR        0x003F  //选择要镜像的目标（传输）端口
                                                //6’b00_0000：保留（默认）
                                                //6’b00_0001: 端口 0
                                                //6’b00_0010：端口 1
                                                //6’b00_0100：端口 2
                                                //6’b00_1000：端口 3
                                                //6’b01_0000：端口 4
                                                //6’b10_0000：端口 5 (MII0)

/**
 * @brief 源块保护
 * 
 */
#define IP175_Src_Bck_Prt_R     0x16
#define IP175_SBP_En                    0x0040  //源块保护使能
#define IP175_P5_SBP_Status             0x0020  //源块保护状态
#define IP175_P4_SBP_Status             0x0010  
#define IP175_P3_SBP_Status             0x0008  
#define IP175_P2_SBP_Status             0x0004  
#define IP175_P1_SBP_Status             0x0002  
#define IP175_P0_SBP_Status             0x0001  

/**
 * @brief LED模式选择
 * 
 */
#define IP175_LED_CR            0x18
#define IP175_LED_Sel                   0x0003  //LED 输出模式选择。 00 == mode0 ...


/*---------------------------------------------------------------PHY地址0x15(21)---------------------------------------------------------------------*/

/**
 * @brief 外部 MII 状态报告寄存器
 *  RO
 */
#define IP175_Ex_MII_SRR        0x00
#define IP175_MII0_Full                 0x0080  //1 = 全双工，0 = 半双工
#define IP175_MII0_Speed_10             0x0040  //1 = 10M，0 = 100M
#define IP175_MII0_Flow                 0x0020  //流控，1 = 使能，0 = 失能

/**
 * @brief MII接外部PHY时，PHY反馈状态
 * 
 */
#define IP175_MII_MAC_Mode_R    0x01
#define IP175_MAC_XCTRLEN               0x8000  //在MII0上外接PHY的连接者流控能力
#define IP175_MAC_Force                 0x4000  //1：MII0的速度和双工被强制，因为IP175LLF发现外部PHY不支持SMI   0：MII0 通过 SMI 轮询外部 PHY 来决定其速度和双工。
#define IP175_MII_Link                  0x2000  //1：链接正常
#define IP175_Cap_ExPHYOnMII            0x1F00  //R/W,外部PHY能力：bit12：流控  bit11:100M全双工   bit10:100M半双工   bit9:10M全双工 bit8:10M半双工
#define IP175_Speed_ExPHYOnMII          0x0080  //外部PHY速度，1= 10M，0 = 100M
#define IP175_Duplex_ExPHYOnMII         0x0040  //外部PHY双工，1 = 全双工，0 = 半双工
#define IP175_LinkStatus_ExPHYOnMII     0x0020  //外部PHY链接状态，    1 = 链接打开，0 = 链接关闭
#define IP175_MII_MAC_PHY_ADDR          0x001F  //R/W,部PDY地址

/**
 * @brief MII 控制寄存器1
 * 
 */
#define IP175_MII_1CR       0x03
#define IP175_SMI_POLLING               0x4000  //RO,SMI轮询 1 = MII MAC模式    ，0 = MII PHY模式
#define IP175_MII_MAC_Mode_En           0x0800  //1 = MII作为MAC工作    ，0 = MII作为PHY工作
#define IP175_MII_RMII_En               0x0400  //1 = RMII使能 ， 0 = RMII失能
#define IP175_MII_MAC_REPEATER          0x0040  //1 = 外部PHY的TXEN不循环回CRS,0 = 外部PHY的TXEN循环回CRS
#define IP175_MII_PHY_COL_DELAY         0x0010  //1 = 碰撞延时24个时钟,0 = 不延时

/**
 * @brief MII 控制寄存器2
 * 
 */
#define IP175_MII_2CR       0x04
#define IP175_MII0_CHK_CRC              0x0001  //1 = 检查mii0端口每个入帧的CRC字段

/**
 * @brief IGMP 控制寄存器
 * 
 */
#define IP175_IGMP_CR       0x05
#define IP175_Fast_Leave                0x0400
#define IP175_MG_Include_RP             0x0200  //组播组包含路由器端口
#define IP175_FLOOD_UNIGMP              0x0100  //淹没未知 IGMP,未知IGMP不是以下原因之一：一般查询，组特定查询，IGMP报告，离开
#define IP175_FLOOD_IPM_CTRL            0x0080  //发送IP组播控制报文,IP 多播控制数据包： DMAC=01-00-5e-xx-xx-xx， DIP= 224.0.0.x 和非 IGMP
#define IP175_UNIPM_MODE                0x0060  //未知IP多播包处理模式，IP 组播数据包： DMAC=01-00-5e-xx-xx-xx 和 DIP=outside 224.0.0.x
                                        //00 == 丢弃  01 == 转发到CPU 10 ==flood packet  11 == 转发到路由器端口
#define IP175_DISCARD_LEAVE             0x0010  //丢弃IGMP离开报文
#define IP175_FLOOD_RPT                 0x0008  //发送到其他端口的Flood 报告消息
#define IP175_LRP_NULL_SIP              0x0004  //即使源IP地址为0.0.0.0，也要学习路由器端口
#define IP175_LEARN_RP                  0x0002  //学习路由器端口
#define IP175_HW_IGMP_EN                0x0001  //硬件IGMO使能

/**
 * @brief 路由器端口超时寄存器
 * 
 */
#define IP175_Route_Port_T  0x06
#define IP175_ROUTER_TIMEOUT_VLE        0xFF00  //超时时间 = ROUTER_TIMEOUT_UNIT *ROUTER_TIMEOUT_VLE
#define IP175_ROUTER_TIMEOUT_UNIT       0x00C0  //00 = 1s   01 = 2s 10 = 4s 11 = 8s
#define IP175_DEFAULT_ROUTER_PORT       0x003F  //默认路由器端口   bit5:端口5    bit4：端口4    ...

/**
 * @brief IGMP组超时时间
 * 
 */
#define IP175_IGMP_Group_TR 0x07
#define IP175_IGMP_TIMEOUT_VLE          0xFF00  //超时时间 = IGMP_TIMEOUT_VLE *IGMP_TIMEOUT_UNIT
#define IP175_IGMP_TIMEOUT_UNIT         0x0003  //00 = 1s   01 = 2s 10 = 4s 11 = 8s

/**
 * @brief 速率控制寄存器1
 * 
 */
#define IP175_Rate_1CR      0x08
#define IP175_BW_TI                     0x007F  //速率控制时间间隔,仅供出口端口和输出队列使用 单位： 毫秒

/**
 * @brief 速率控制寄存器2
 *  
 */
#define IP175_Rate_2CR      0x09    
#define IP175_BW_MBS                    0xFFFF  //速率控制最大突发大小以字节表示。

/**
 * @brief 速率控制寄存器3
 * 
 */
#define IP175_Rata_3CR      0x0A
#define IP175_BW_CREDIT_SIZE            0xFFFF  //在每个时间间隔内累积桶的信用大小。以字节表示。

/**
 * @brief 速率设置访问控制寄存器
 * 
 */
#define IP175_Rata_SA_CR        0x0C
#define IP175_BW_PORT                   0x0007  //设置带宽速率的端口号。
#define IP175_BW_IOE                    0x0008  //带宽速率设置在入口或出口端口 0： 入口端口（默认）    1： 出口端口
#define IP175_BW_QUEUE                  0x0030  //分配用于设置速率控制值的出口输出队列号   00：出口端口（默认） 01：队列1  10：队列2  11：队列3
#define IP175_BW_RW                     0x0100  //速率控制数据读写信号 0：读速率控制数据（默认） 1：写速率控制数据
#define IP175_BW_RW_START               0x0200  //当向该寄存器写入逻辑“1”时，表示开始读/写端口的速率控制数据。

/**
 * @brief 地址表访问寄存器
 * 
 */
#define IP175_Command_R         0x0E
#define IP175_START_DONE                0x8000  //设置为 1 时启动读或写命令。读或写命令完成后自清
#define IP175_DATA_VALID                0x2000  //数据有效,IP175LLF 会将此位设置为 1 以指示数据可用
#define IP175_COMMAND                   0x1800  //命令[1:0] 01：单写 10：单读
#define IP175_Table_Index               0x07FF  //索引选择地址表条目之一。

/*****************************此部分待整理**************************************/
/**
 * @brief 数据缓存寄存器
 * 单播、多播、IP单播   部分寄存器不同MAC地址
 */
#define IP175_MAC_ADDR_15_0     0x0F
#define IP175_MAC_ADDR_31_16    0x10
#define IP175_MAC_ADDR_47_32    0x11
#define IP175_MAC_ADDR_MASK             0xFFFF

#define IP175_Data_Buffer       0x12
#define IP175_FILTER_INFO               0xC000
#define IP175_PRI_INFO                  0x3C00
#define IP175_FID                       0x03C0  
#define IP175_Port_IDOfUniCast          0x0038  //如果PORT_ID设置为全0，帧的DMAC匹配此表项将被丢弃。
#define IP175_AGEOfUniCast              0x0007  //如果该字段全为零，则该条目过时或无效。
#define IP175_Port_MAPOfMultiCast       0x003F  //如果PORT_MAP设置为全零，帧的DMAC匹配此条目将被丢弃。

#define IP175_Data_Status       0x13
#define IP175_StaticOfUniCast           0x0002  //条目是静态的，不能覆盖或老化
#define IP175_ValidOfMultiCast          0x0002  //条目有效
#define IP175_IGMPOfMultiCast           0x0001  //保持为0

/******************************待整理区结束****************************************/

/**
 * @brief CPU中断控制寄存器
 * 
 */
#define IP175_CPU_INIT_CR       0x14
#define IP175_Interrupt_High            0x8000  //中断信号活动时电平状态，1 = 高活动   0 = 低活动
#define IP175_Loop_Detec_En             0x0008

/**
 * @brief 回环端口指示寄存器
 * 
 */
#define IP175_Loop_Indicator_R  0x15
#define IP175_Loop_Indicator            0x00F0
#define IP175_Have_Loop                 0x0008
#define IP175_Port4_Loop                0x0004

/**
 * @brief 杂项控制寄存器1
 * 
 */
#define IP175_MISC_CR1          0x16
#define IP175_REDUCE_IPG                0x4000  //此功能随机降低 IPG 从 0~20 PPM
#define IP175_TWOPARTD                  0x2000  //如果 CRS 信号在 IPG 期间的三分之二断言。
#define IP175_HP_DIS_FLOW_EN            0x1000  //禁用流控制的高优先级数据包,当端口收到高优先级报文时，流量控制功能将关闭2sec。
#define IP175_DRIVE                     0x0C00  //驱动能力选择    00: 4 mA    01: 8 mA    10: 12 mA   11: 16 mA
#define IP175_LINK_Q_EN                 0x0008  //链接质量检测使能
#define IP175_TB31_EN                   0x0004  //Turbo MII0 31.25MHZ输出使能
#define IP175_STAG_TX_EN                0x0002  //TX特殊标记使能
#define IP175_STAG_RX_EN                0x0001  //RX特殊标记使能

/**
 * @brief 杂项控制寄存器2
 * 
 */
#define IP175_MISC_CR2          0x18
#define IP175_FLOOD_FRM                 0x00FC
#define IP175_FAST_Mode                 0x0002
#define IP175_ALL_PASS                  0x0001

/**
 * @brief CRC计数寄存器
 * 
 */
#define IP175_CRC_Count_CR      0x19
#define IP175_CRC_Counter               0x00FF  //CRC计数器，用于累计所有端口的CRC数。任何端口接收到CRC错误的帧都会将该计数器增加1。

/*------------------------------------------------PHY地址0x16(22)-------------------------------------------------------------------------*/

/**
 * @brief VLAN分类寄存器
 * 
 */
#define IP175_VLANClass_R           0x00
#define IP175_VLAN_Table_CLR                0x8000  //1 = 清除VLAN表
#define IP175_UNVID_MODE                    0x3000  //未知VID处理方式 00 = 丢弃 01 = 转发至CPU 10  = flood packet  11 = 未使用
#define IP175_P5_VLAN_CLS                   0x0800  //每个端口对应的VLAN分类,仅在基于标记的VLAN上活动. 
                                                    //0 = 如果tag报文，使用VID查找VLAN表,如果untag报文，使用PVID查找VLAN表
                                                    //1 = 永远使用PVID查找VLAN表
#define IP175_P4_VLAN_CLS                   0x0400
#define IP175_P3_VLAN_CLS                   0x0200
#define IP175_P2_VLAN_CLS                   0x0100
#define IP175_P1_VLAN_CLS                   0x0080
#define IP175_P0_VLAN_CLS                   0x0040

#define IP175_P5_VlLAN_MODE                 0x0020  //与每个端口关联的 VLAN 模式设置    0 = 基于端口的VLAN(def), 1 = 基于tag的VLAN
#define IP175_P4_VlLAN_MODE                 0x0010
#define IP175_P3_VlLAN_MODE                 0x0008
#define IP175_P2_VlLAN_MODE                 0x0004
#define IP175_P1_VlLAN_MODE                 0x0002
#define IP175_P0_VlLAN_MODE                 0x0001

/**
 * @brief VLAN入口规则寄存器
 * 
 */
#define IP175_VLAN_Ingress_Rule_R   0x01
#define IP175_VLAN_DROP_CFI                 0x0800  //如果 CFI 字段不为零，则丢弃传入帧
#define IP175_RSVD_VID                      0x0700  //预留VID bit0 = 空 VID。如果设置，具有空 VID 的帧（优先级标记帧）将视为未标记帧。
                                                    //bit1 = 将默认 VID 替换为 PVID
                                                    //bit2 = 如果 VID 为值 FFF 则丢弃帧
#define IP175_ACCEPTABLE_FRM_TYPE           0x00C0  //可接受的帧类型,  00 = 允许所有帧（默认）  01 = 允许带有VLAN 标记的帧  10 = 允许未标记的帧    11 = 未使用
#define IP175_P5_VLAN_INGRESS_FILTER        0x0020  //与每个端口关联的 VLAN 入口过滤器.如果设置了端口的入接口过滤器，则帧将在VLAN分类不包括该端口的端口上丢弃。
#define IP175_P4_VLAN_INGRESS_FILTER        0x0010
#define IP175_P3_VLAN_INGRESS_FILTER        0x0008
#define IP175_P2_VLAN_INGRESS_FILTER        0x0004
#define IP175_P1_VLAN_INGRESS_FILTER        0x0002
#define IP175_P0_VLAN_INGRESS_FILTER        0x0001

/**
 * @brief VLAN出口规则寄存器
 * 
 */
#define IP175_VLAN_Egress_Rule_R    0x02
#define IP175_P5_IGMP_IGNORE_MEMBER         0x0800  //IGMP 忽略成员集,忽略DMAC在01-00-5e-xx-xx-xx帧的成员集
#define IP175_P4_IGMP_IGNORE_MEMBER         0x0400
#define IP175_P3_IGMP_IGNORE_MEMBER         0x0200
#define IP175_P2_IGMP_IGNORE_MEMBER         0x0100
#define IP175_P1_IGMP_IGNORE_MEMBER         0x0080
#define IP175_P0_IGMP_IGNORE_MEMBER         0x0040

#define IP175_P5_KEEP_TAG                   0x0020  //保留VLAN标签头， 1 = VLAN tag头与帧保持一致。如果帧在一个出口端口标签帧上传输，该帧可能包含两个标签报头
#define IP175_P4_KEEP_TAG                   0x0010
#define IP175_P3_KEEP_TAG                   0x0008
#define IP175_P2_KEEP_TAG                   0x0004
#define IP175_P1_KEEP_TAG                   0x0002
#define IP175_P0_KEEP_TAG                   0x0001

/**
 * @brief 默认VLAN信息寄存器
 * 
 */
#define TPID_VALUE_R            0x03        //802.1Q 标签协议类型
#define IP175_P0_VLAN_INFO_R    0x04        //端口0默认VLAN信息值
#define IP175_P1_VLAN_INFO_R    0x05
#define IP175_P2_VLAN_INFO_R    0x06
#define IP175_P3_VLAN_INFO_R    0x07
#define IP175_P4_VLAN_INFO_R    0x08
#define IP175_P5_VLAN_INFO_R    0x09

/**
 * @brief VLAN控制寄存器
 * 
 */
#define IP175_VLAN_VALID_R          0x0A    //VALN 过滤器有效。
#define IP175_QU_NUM_EN_R           0x0B    //分配新队列号启用
#define IP175_STP_IDX_EN_R          0x0C    //生成树协议索引启用
#define IP175_REW_VLAN_PRI_EN_R     0x0D    //重写 VLAN 优先级字段启用

/**
 * @brief VLAN标识符寄存器
 * 本组寄存器共用掩码
 */
#define IP175_FID_Mask                      0xF000
#define IP175_VID_Mask                      0x0FFF
#define IP175_VLAN_Identifier0_R    0x0E
#define IP175_VLAN_Identifier1_R    0x0F
#define IP175_VLAN_Identifier2_R    0x10

#define IP175_VLAN_Identifier3_R    0x11
#define IP175_VLAN_Identifier4_R    0x12
#define IP175_VLAN_Identifier5_R    0x13
#define IP175_VLAN_Identifier6_R    0x14
#define IP175_VLAN_Identifier7_R    0x15
#define IP175_VLAN_Identifier8_R    0x16
#define IP175_VLAN_Identifier9_R    0x17
#define IP175_VLAN_IdentifierA_R    0x18
#define IP175_VLAN_IdentifierB_R    0x19
#define IP175_VLAN_IdentifierC_R    0x1A
#define IP175_VLAN_IdentifierD_R    0x1B
#define IP175_VLAN_IdentifierE_R    0x1C
#define IP175_VLAN_IdentifierF_R    0x1D

/*--------------------------------------------------------PHY地址0x17----------------------------------------------------------------------*/
/**
 * @brief VLAN成员寄存器
 * 本组寄存器共用掩码
 */
#define IP175_VLAN_MemberH_Mask             0x3F00
#define IP175_VLAN_MemBerL_Mask             0x003F
#define IP175_VLAN_Member1_0_R  0x00
#define IP175_VLAN_Member3_2_R  0x01
#define IP175_VLAN_Member5_4_R  0x02
#define IP175_VLAN_Member7_6_R  0x03
#define IP175_VLAN_Member9_8_R  0x04
#define IP175_VLAN_MemberB_A_R  0x05
#define IP175_VLAN_MemberD_C_R  0x06
#define IP175_VLAN_MemberF_E_R  0x07

/**
 * @brief 添加标签控制寄存器
 * 本组寄存器共用掩码
 */
#define IP175_P5_ADD_VLAN_TagH_Mask         0x0020
#define IP175_P4_ADD_VLAN_TagH_Mask         0x0010
#define IP175_P3_ADD_VLAN_TagH_Mask         0x0008
#define IP175_P2_ADD_VLAN_TagH_Mask         0x0004
#define IP175_P1_ADD_VLAN_TagH_Mask         0x0002
#define IP175_P0_ADD_VLAN_TagH_Mask         0x0001

#define IP175_P5_ADD_VLAN_TagL_Mask         0x2000
#define IP175_P4_ADD_VLAN_TagL_Mask         0x1000
#define IP175_P3_ADD_VLAN_TagL_Mask         0x0800
#define IP175_P2_ADD_VLAN_TagL_Mask         0x0400
#define IP175_P1_ADD_VLAN_TagL_Mask         0x0200
#define IP175_P0_ADD_VLAN_TagL_Mask         0x0100

#define IP175_ADD_TAG1_0_R  0x08
#define IP175_ADD_TAG3_2_R  0x09
#define IP175_ADD_TAG5_4_R  0x0A
#define IP175_ADD_TAG7_6_R  0x0B
#define IP175_ADD_TAG9_8_R  0x0C
#define IP175_ADD_TAGB_A_R  0x0D
#define IP175_ADD_TAGD_C_R  0x0E
#define IP175_ADD_TAGF_E_R  0x0F

/**
 * @brief 移除标签控制寄存器
 * 本组寄存器共用掩码
 */
#define IP175_P5_RE_VLAN_TagH_Mask          0x0020
#define IP175_P4_RE_VLAN_TagH_Mask          0x0010
#define IP175_P3_RE_VLAN_TagH_Mask          0x0008
#define IP175_P2_RE_VLAN_TagH_Mask          0x0004
#define IP175_P1_RE_VLAN_TagH_Mask          0x0002
#define IP175_P0_RE_VLAN_TagH_Mask          0x0001

#define IP175_P5_RE_VLAN_TagL_Mask          0x2000
#define IP175_P4_RE_VLAN_TagL_Mask          0x1000
#define IP175_P3_RE_VLAN_TagL_Mask          0x0800
#define IP175_P2_RE_VLAN_TagL_Mask          0x0400
#define IP175_P1_RE_VLAN_TagL_Mask          0x0200
#define IP175_P0_RE_VLAN_TagL_Mask          0x0100

#define IP175_RE_TAG1_0_R       0x10
#define IP175_RE_TAG3_2_R       0x11
#define IP175_RE_TAG5_4_R       0x12
#define IP175_RE_TAG7_6_R       0x13
#define IP175_RE_TAG9_8_R       0x14
#define IP175_RE_TAGB_A_R       0x15
#define IP175_RE_TAGD_C_R       0x16
#define IP175_RE_TAGF_E_R       0x17

/**
 * @brief VLAN杂项控制寄存器
 * 本组寄存器共用掩码
 */
#define IP175_STP_IDX_H                     0x0300  //生成树索引，该寄存器仅在启用 STP_IDX_EN[0] 时有效，PHY = 17 , Reg = 0x0C
#define IP175_QU_NUM_H                      0x0C00  //优先队列号，该寄存器仅在启用 QU_NUM_EN[0] 时有效，PHY = 17 , Reg = 0x0B
#define IP175_LEARN_DIS_H                   0x1000  //学习失能
#define IP175_REW_VLAN_PRI_H                0xE000  //重写 VLAN 优先级值，该寄存器仅在启用 REW_VLAN_PRI_EN[0] 时有效,PHY = 17 , Reg = 0x0D

#define IP175_STP_IDX_L                     0x0003
#define IP175_QU_NUM_L                      0x000C
#define IP175_LEARN_DIS_L                   0x0010
#define IP175_REW_VLAN_PRI_L                0x00E0

#define IP175_VLAN_MISC1_0_R    0x18
#define IP175_VLAN_MISC3_2_R    0x19
#define IP175_VLAN_MISC5_4_R    0x1A
#define IP175_VLAN_MISC7_6_R    0x1B
#define IP175_VLAN_MISC9_8_R    0x1C
#define IP175_VLAN_MISCB_A_R    0x1D
#define IP175_VLAN_MISCD_C_R    0x1E
#define IP175_VLAN_MISCF_E_R    0x1F

/*---------------------------------------------------------PHY地址0x18------------------------------------------------------------------*/
/**
 * @brief 生成树表
 * 
 */
#define IP175_P5_STP_FORWARD_EN             0x2000  //生成树报文STP_IDX关联的P5端口的转发能力
#define IP175_P4_STP_FORWARD_EN             0x1000
#define IP175_P3_STP_FORWARD_EN             0x0800
#define IP175_P2_STP_FORWARD_EN             0x0400
#define IP175_P1_STP_FORWARD_EN             0x0200
#define IP175_P0_STP_FORWARD_EN             0x0100

#define IP175_P5_STP_LEARNING_EN            0x0020  //生成树报文与STP_IDX关联的P5端口的学习能力
#define IP175_P4_STP_LEARNING_EN            0x0010
#define IP175_P3_STP_LEARNING_EN            0x0008
#define IP175_P2_STP_LEARNING_EN            0x0004
#define IP175_P1_STP_LEARNING_EN            0x0002
#define IP175_P0_STP_LEARNING_EN            0x0001

#define IP175_Spanning_Tree_0_R 0x00
#define IP175_Spanning_Tree_1_R 0x01
#define IP175_Spanning_Tree_2_R 0x02
#define IP175_Spanning_Tree_3_R 0x03

/*------------------------------------------------------------PHY地址0x19---------------------------------------------------------------------------*/
/**
 * @brief QOS基础控制寄存器
 * 
 */
#define IP175_QOS_BCR       0x00    
#define IP175_LP_OVER_DSCP                  0x8000  //逻辑端口优先级高于DSCP优先级
#define IP175_TOS_OVER_VLAN_PRI             0x4000  //IP帧优先级高于VLAN帧优先级。即IP帧的优先级高于带VLAN标签的帧。
#define IP175_P5_COS_EN                     0x2000  //为P5端口启用COS
#define IP175_P4_COS_EN                     0x1000
#define IP175_P3_COS_EN                     0x0800
#define IP175_P2_COS_EN                     0x0400
#define IP175_P1_COS_EN                     0x0200
#define IP175_P0_COS_EN                     0x0100
#define IP175_USER_DEF_PRI                  0x0080  //用户自定义优先级
#define IP175_P5_PORT_PRI_EN                0x0020  //为P5端口启用基于端口的优先级功能
#define IP175_P4_PORT_PRI_EN                0x0010  
#define IP175_P3_PORT_PRI_EN                0x0008
#define IP175_P2_PORT_PRI_EN                0x0004
#define IP175_P1_PORT_PRI_EN                0x0002
#define IP175_P0_PORT_PRI_EN                0x0001

/**
 * @brief 端口优先级映射寄存器
 * 
 */
#define IP175_Port_PRI_Map_R    0x01
#define IP175_P5_PRI                        0x0C00  //00 = 将数据包分配到队列0;  01 = 将数据包分配到队列1;    10 = 将数据包分配到队列2;    11 = 将数据包分配到队列3(def)
#define IP175_P4_PRI                        0x0300
#define IP175_P3_PRI                        0x00C0
#define IP175_P2_PRI                        0x0030
#define IP175_P1_PRI                        0x000C
#define IP175_P0_PRI                        0x0003

/**
 * @brief VLAN优先级映射寄存器
 * 
 */
#define IP175_VLAN_PRI_Map_R    0x02
#define IP175_VLAN_PRI7                     0xC000  //00 = 将数据包分配到队列0;  01 = 将数据包分配到队列1;    10 = 将数据包分配到队列2;    11 = 将数据包分配到队列3(def)
#define IP175_VLAN_PRI6                     0x3000
#define IP175_VLAN_PRI5                     0x0C00
#define IP175_VLAN_PRI4                     0x0300
#define IP175_VLAN_PRI3                     0x00C0
#define IP175_VLAN_PRI2                     0x0030
#define IP175_VLAN_PRI1                     0x000C
#define IP175_VLAN_PRI0                     0x0003

/**
 * @brief TOS/DSCP优先级映射寄存器
 * DSCP优先级0-63，寄存器设置时，每个寄存器可以设置8个，那么设置第m个( 63 >= m >= 0)DSCP优先级映射应该为
 * 寄存器地址 = 0x03 + m >> 3;
 * 寄存器中的位 = m & 0x07;
 * 掩码 = DSCP_PRIx_8n( x = 寄存器中的位)
 */
#define IP175_TOS_PRI_Map_1R    0x03
#define IP175_TOS_PRI_Map_2R    0x04
#define IP175_TOS_PRI_Map_3R    0x05
#define IP175_TOS_PRI_Map_4R    0x06
#define IP175_TOS_PRI_Map_5R    0x07
#define IP175_TOS_PRI_Map_6R    0x08
#define IP175_TOS_PRI_Map_7R    0x09
#define IP175_TOS_PRI_Map_8R    0x0A

#define IP175_DSCP_PRI7_8n                  0xC000  //00 = 将数据包分配到队列0;  01 = 将数据包分配到队列1;    10 = 将数据包分配到队列2;    11 = 将数据包分配到队列3(def)
#define IP175_DSCP_PRI6_8n                  0x3000
#define IP175_DSCP_PRI5_8n                  0x0C00
#define IP175_DSCP_PRI4_8n                  0x0300
#define IP175_DSCP_PRI3_8n                  0x00C0
#define IP175_DSCP_PRI2_8n                  0x0030
#define IP175_DSCP_PRI1_8n                  0x000C
#define IP175_DSCP_PRI0_8n                  0x0003

/**
 * @brief TCP/UDP 端口优先级映射
 * 
 */
#define IP175_TCP_UDP_PRI_Map_1R    0x0B
#define IP175_LP_TYPE                       0x00C0  //  00 = 逻辑端口优先级禁用; 01 = 源逻辑端口优先级启用;    10 = 目标逻辑端口优先级启用;   11 = 源或目标逻辑端口优先级使能
#define IP175_USERDEF_RANGE_EN              0x0030  //  bit1 = 用户定义范围 1 寄存器启用;  bit0 = 用户定义范围 0 寄存器启用
#define IP175_PREDEF_PORT_EN                0x000F  //  bit3 = 逻辑端口3 启用，端口 6000
                                                    //  bit2 = 逻辑端口2 启用，端口 3389
                                                    //  bit1 = 逻辑端口1 启用，端口 443
                                                    //  bit0 = 逻辑端口0 启用，端口 22

#define IP175_PREDEF_PORT_0_R       0x0C
#define IP175_PREDEF_PORT_1_R       0x0D
#define IP175_PREDEF_PORT_2_R       0x0E
#define IP175_PREDEF_PORT_3_R       0x0F
#define IP175_USERDEF_RANGE0_LOW_R  0x10        //用户自定义逻辑端口范围0下限
#define IP175_USERDEF_RANGE0_HIGH_R 0x11        //用户自定义逻辑端口范围0上限
#define IP175_USERDEF_RANGE1_LOW_R  0x12
#define IP175_USERDEF_RANGE1_HIGH_R 0x13

/**
 * @brief 传输优先级队列映射寄存器
 * 
 */
#define IP175_Trans_PRI_Map_R       0x14
#define IP175_USERDEF_RANGE_1Q              0x0C00  //用户自定义逻辑端口范围1传输优先级队列映射
#define IP175_USERDEF_RANGE_0Q              0x0300
#define IP175_PREDEF_PORT_3Q                0x00C0  //预定义端口3传输优先级队列映射。
#define IP175_PREDEF_PORT_2Q                0x0030
#define IP175_PREDEF_PORT_1Q                0x000C
#define IP175_PREDEF_PORT_0Q                0x0003

/**
 * @brief 
 * 
 */
#define IP175_PRIDEF_DROP_R         0x15
#define IP175_PREDEF_PORT_DROP              0x003C  //将匹配REDEF_PORT_0_R[15:0]中定义的TCP/UDP端口号的入站报文丢弃到PREDEF_PORT_3_R[15:0]。优先于帧分类优先级
                                                    //[0] drop packet number匹配PREDEF_PORT_0[15:0]
                                                    //[1] drop packet number匹配PREDEF_PORT_1[15:0]
                                                    //[2] drop packet number匹配PREDEF_PORT_2[15:0]
                                                    //[3] drop packet number匹配PREDEF_PORT_3[15:0]
#define IP175_USERDEF_RANGE0_DROP           0x0003  //用户自定义逻辑端口丢弃报文。丢弃匹配端口范围寄存器中定义的TCP/UDP端口号的数据包。优先于帧分类优先级
                                                    //[0] userdef_range0_low ~ userdef_range0_high
                                                    //[1] userdef_range1_low ~ userdef_range1_high

/**
 * @brief 队列调度配置寄存器
 * 
 */
#define IP175_Queue_Sch_Config_R    0x16
#define IP175_QOS_OVER_FC                   0x2000
#define IP175_P5_SCH_TYPE                   0x0C00  //端口5队列
                                                    //          Q3  Q2  Q1  Q0
                                                    //2’b00:    WRR WRR WRR WRR
                                                    //2’b01:    WFQ WFQ WFQ WFQ(BE)
                                                    //2’b10:    SP  WFQ WFQ BE
                                                    //2’b11:    SP  SP  SP  SP
                                                    //WRR: 加权轮询调度
                                                    //WFQ: 加权公平队列
                                                    //BE: 尽力
                                                    //SP: 严格优先级
#define IP175_P4_SCH_TYPE                   0x0300
#define IP175_P3_SCH_TYPE                   0x00C0
#define IP175_P2_SCH_TYPE                   0x0030
#define IP175_P1_SCH_TYPE                   0x000C
#define IP175_P0_SCH_TYPE                   0x0003

/**
 * @brief 队列调度算法控制寄存器
 * 
 */
#define IP175_Queue_Sch_CR      0x17
#define IP175_Q3_WEIGHT                     0xF000  //输出队列3加权轮询调度控制寄存器  4'b0001 = 1 packet  ;   4'b0010 = 2packets  ... 4'b1111 = 15packets
#define IP175_Q2_WEIGHT                     0x0F00
#define IP175_Q1_WEIGHT                     0x00F0
#define IP175_Q0_WEIGHT                     0x000F

/*--------------------------------------------------------------------PHY地址0x1A(26)------------------------------------------*/
/**
 * @brief QoS 多字段分类表控制寄存器
 * 
 */
#define IP175_QOS_MF_CR     0x00
#define IP175_MF_QOS_EN                     0x8000  //开启多字段QoS访问控制功能。当启用此位时，交换机引擎将使用多字段寄存器对传入的帧进行分类。
#define IP175_MF_REG_CLR                    0x0400  //自清零位，清除多字段分类寄存器和多字段表QOS速率控制寄存器的内容。这是出于编程方便的考虑。当设置为0时，除IP掩码寄存器- MF_IP_SA_MASK[3:0]和MF_IP_DA_MASK[3:0]外，所有的多字段寄存器都清除为0。
#define IP175_MF_CNT_RESET                  0x0200  //自清零位，多字段计数器复位。当重置时，它将引用MF_RESET_EN寄存器的设置。
#define IP175_MF_ENTRY_RESET                0x0100  //自清零位，多字段条目重置。当重置时，它将引用MF_RESET_EN寄存器的设置
#define IP175_MF_RESET_EN                   0x00FF  //对每个条目或计数器启用多字段重置。

/**
 * @brief 多字段分类寄存器
 * 
 */
#define IP175_QOS_MF_Class_R    0x01
#define IP175_MF_CTRL                       0xC000  //多字段输入控制寄存器
                                                    //[1]:过滤/转发—0:转发；—1:过滤器
                                                    //[0]:流量调节(QoS速率控制)
#define IP175_MF_IP_RANGE                   0x1000  //开启IP地址范围监控功能。
                                                    //启用后，源和目的IP地址寄存器将用作IP地址范围监控器寄存器。
                                                    //MF_IM_SA将是一个IP地址监控器的起始编号
                                                    //MF_IM_DA将是一个IP地址监控器停止编号
                                                    //{MF_IM_DIP, MF_IM_SIP}        监控类型
                                                    //      0       0               保留
                                                    //      0       1               源地址
                                                    //      1       0               目的地址
                                                    //      1       1               source或dest. addr
#define IP175_MF_IN_SA_EN                   0x0800  //启用IP/MAC源地址字段。
#define IP175_MF_IM_SIP                     0x0400  //IP/MAC源地址字段作为IP地址。
#define IP175_MF_IP_SA_MASK                 0x03C0  //IP源地址子网掩码。IP地址可以分为四组，每组8位，以十进制格式表示(称为点分十进制)。这个寄存器用作掩码来提取IP地址
#define IP175_MF_IM_DA_EN                   0x0020  //IP/MAC目的地址字段使能
#define IP175_MF_IM_DIP                     0x0010  //IP/MAC目的地址字段作为IP地址
#define IP175_MF_IP_DA_MASK                 0x000F  //IP目的地址子网掩码。

#define IP175_MF_IM_SA15_0  0x02    //IP/MAC源地址。当使用IP地址时，只引用LSB中的32位，忽略其余部分。
#define IP175_MF_IM_SA31_16 0x03    
#define IP175_MF_IM_SA47_32 0x04    

#define IP175_MF_IM_DA15_0  0x05    //IP/MAC目的地址。当使用IP地址时，只引用LSB中的32位，忽略其余部分
#define IP175_MF_IM_DA31_16 0x06
#define IP175_MF_IM_DA47_32 0x07

#define IP175_MF_ET_VALUE   0x08    //EtherType(以太网类型)值

/**
 * @brief 
 * 
 */
#define IP175_MF_ET_IP_CR   0x09
#define IP175_MF_ET_EN                      0x8000  //EtherType字段启用
#define IP175_MF_FW_CTRL                    0x3000  //当Multi_Field条目命中时，转发或复制数据包到指定端口   2 'b00:禁用   2'b01:转发到CPU    2'b10:拷贝到镜像端口   2 'b11:保留   
                                                    //只有当对应的MF_CTRL[1]位为disable(Forwarding enable)时才有效。
#define IP175_MF_PRI_CTRL                   0x0E00  //当Multi_Field条目命中时，将数据包转发到特定队列
                                                    //3 'b000:禁用
                                                    //3'b100:转发到队列0
                                                    //3’b101:转发到队列1
                                                    //3'b110:转发到队列2
                                                    //3 ' b111:转发到队列3
                                                    //其他:保留
#define IP175_MF_PTL_EN                     0x0100  //IP协议号字段使能
#define IP175_MF_PTL_NUM                    0x00FF  //IP协议号字段

/**
 * @brief TCP/UDP端口范围监控控制寄存器
 * 
 */
#define IP175_MF_LG_CR      0x0A
#define IP175_MF_LG_RANGE                   0x0010  //开启TCP/UDP端口范围监控功能。
                                                    //启用后，源和目标端口寄存器将用作端口范围监控器寄存器。
                                                    //MF_LG_SP_NUM将是端口监视器的起始编号
                                                    //MF_LG_DP_NUM将是端口监视器停止号
                                                    //{MF_LG_DP_TYPE, MF_LG_SP_TYPE}    监控类型
                                                    //      0           0               保留
                                                    //      0           1               TCP
                                                    //      1           0               UDP
                                                    //      1           1               TCP或UDP
                                                    //{MF_LG_DP_EN, MF_LG_SP_EN}        监控类型
                                                    //      0           0               保留
                                                    //      0           1               源端口
                                                    //      1           0               目的端口
                                                    //      1           1                source或dest. port
#define IP175_MF_LG_SP_EN                   0x0008  //启用TCP/UDP源端口字段
#define IP175_MF_LG_SP_TYPE                 0x0004  //MF_LG_SP_NUM字段是TCP或UDP端口。0: TCP端口 1: UDP端口
#define IP175_MF_LG_DP_EN                   0x0002  //TCP/UDP目的端口字段启用。
#define IP175_MF_LG_DP_TYPE                 0x0001  //MF_LG_DP_NUM字段为TCP或UDP端口。0: TCP端口 1: UDP端口

#define IP175_MF_LG_SP_NUM_R    0x0B    //TCP/UDP要监控的源端口号
#define IP175_MF_LG_DP_NUM_R    0x0C    //TCP/UDP要监控的目的端口号。

/**
 * @brief 物理源端口控制寄存器
 * 
 */
#define IP175_MF_SP_CR      0x0D
#define IP175_MF_SP_EN                      0x8000  //物理源端口字段启用
#define IP175_P4_MF_SP_NUM                  0x4000  //物理源端口号
#define IP175_P3_MF_SP_NUM                  0x2000
#define IP175_P2_MF_SP_NUM                  0x1000
#define IP175_P1_MF_SP_NUM                  0x0800
#define IP175_P0_MF_SP_NUM                  0x0400  

/**
 * @brief 行为聚合功能控制寄存器
 * 
 */
#define IP175_MF_BA_CR      0x0E
#define IP175_MF_BA_EN                      0x0080  //行为聚合功能启用
#define IP175_MF_BA_TYPE                    0x0040  //行为聚合函数类型  0表示DSCP (ipv4 TOS或ipv6 DSCP)。   1: VLAN优先级
#define IP175_MF_BA_VALUE                   0x003F  //行为聚合值,    对于DSCP，使用整个6位，但上面的3位用于VLAN优先级参考。

/**
 * @brief 多字段表QoS速率控制寄存器
 * 
 */
#define IP175_MF_MBS_R          0x10    //最大突发尺寸,以字节表示。只有当对应的MF_CTRL[0]位使能时才有效。
#define IP175_MF_CREDIT_SIZE_R  0x11    //在每个时间间隔内累积桶的信用大小。以字节表示。只有当MF_CTRL[0]位为enable时才有效。

/**
 * @brief 多字段访问控制寄存器
 * 
 */
#define IP175_MF_Access1_CR     0x13
#define IP175_MF_VALID                      0x00FF  //对每个条目有效的多字段功能

#define IP175_MF_Access2_CR     0x14
#define IP175_MF_CNT_READ                   0x0040  //当写入逻辑“1”到该寄存器时，指示开始读取一个条目的多字段计数器内容。
#define IP175_MF_OVERFLOW_THR               0x0020  //MF计数器溢出阈值指数   1: 32 'hffff_0000   0: 32 'hff00_0000
#define IP175_MF_RW_START                   0x0010  //自清零位，开始读写表项的多字段
#define IP175_MF_RW                         0x0008  //多字段数据读写信号 0 == 读 ； 1 == 写
#define IP175_MF_ENTRY                      0x0007  //多字段输入号。8 .入口采用MF QoS功能

#define IP175_MF_CNT_LSB_R      0x15
#define IP175_MF_CNT_MSB_R      0x16

/**
 * @brief 多字段状态寄存器
 * 
 */
#define IP175_MF_OVERFLOW_R     0x17

/*----------------------------------------------PHY地址0x1B----------------------------------------------------------*/
/**
 * @brief 自动阻塞/恢复环路端口
 * 
 */
#define IP175_At_Block_Loop_R   0x09
#define IP175_Auto_blocking_loop_port           0xC000

#define IP175_At_Rec_Loop_R     0x0B
#define IP175_Auto_recover_loop_port            0xC000

#endif /*__IP175LLF_REG_H*/

