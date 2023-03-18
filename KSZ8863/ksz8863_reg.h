/**
 * @file ksz8863_reg.h
 * @author chentao
 * @brief ksz8863寄存器列表及地址
 * @version 0.1
 * @date 2022-09-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __KSZ8863_REG_H
#define __KSZ8863_REG_H

#include <stdint.h>

typedef struct ksz8863_Reg
{
    uint16_t PHY1_BCR;
    uint16_t PHY1_BSR;
    uint16_t PHY1_ID1;
    uint16_t PHY1_ID2;
    uint16_t PHY1_ANAR;
    uint16_t PHY1_ANLR;
    uint16_t PHY1_SCS;

    uint16_t PHY2_BCR;
    uint16_t PHY2_BSR;
    uint16_t PHY2_PI1;
    uint16_t PHY2_PI2;
    uint16_t PHY2_ANAR;
    uint16_t PHY2_ANLR;
    uint16_t LMDCS;
    uint16_t PHY2_SCS;
}ksz8863_Reg_def;

#ifndef U16_BIT
#define U16_BIT(x)                          ((uint32_t)((uint32_t)0x01U<<(x)))
#endif  /*U16_BIT*/

#define KSZ8863_BCR_LOOPBACK                U16_BIT(14)
#define KSZ8863_BCR_Force_100               U16_BIT(13)
#define KSZ8863_BCR_AN_Enable               U16_BIT(12)
#define KSZ8863_BCR_PowerDown               U16_BIT(11)

#define KSZ8863_BCR_Restart_AN              U16_BIT(9)
#define KSZ8863_BCR_Force_Full_Dup          U16_BIT(8)
#define KSZ8863_BCR_Hp_MDIX                 U16_BIT(5)
#define KSZ8863_BCR_Force_MDI               U16_BIT(4)
#define KSZ8863_BCR_Disable_MDIX            U16_BIT(3)
#define KSZ8863_BCR_Disable_FarEnd_Fault    U16_BIT(2)
#define KSZ8863_BCR_Disable_TX              U16_BIT(1)
#define KSZ8863_BCR_Disable_LED             U16_BIT(0)

#define KSZ8863_BSR_T4_Capable              U16_BIT(15)
#define KSZ8863_BSR_100_Full_Capable        U16_BIT(14)
#define KSZ8863_BSR_100_Half_Capable        U16_BIT(13)
#define KSZ8863_BSR_10_Full_Capable         U16_BIT(12)
#define KSZ8863_BSR_10_Half_Capable         U16_BIT(11)
#define KSZ8863_BSR_MF_Preamble_Supp        U16_BIT(6)
#define KSZ8863_BSR_AN_Complete             U16_BIT(5)
#define KSZ8863_BSR_Far_End_Fault           U16_BIT(4)
#define KSZ8863_BSR_AN_Capable              U16_BIT(3)
#define KSZ8863_BSR_LinkStatus              U16_BIT(2)
#define KSZ8863_BSR_Jabber_Test             U16_BIT(1)
#define KSZ8863_BSR_Extended_Capable        U16_BIT(0)

#define KSZ8863_ANAR_Pause                  U16_BIT(10)
#define KSZ8863_ANAR_Adv_100_Full           U16_BIT(9)
#define KSZ8863_ANAR_Adv_100_Half           U16_BIT(8)
#define KSZ8863_ANAR_Adv_10_Full            U16_BIT(7)
#define KSZ8863_ANAR_Adv_10_Half            U16_BIT(6)

#define KSZ8863_ANAL_Pause                  U16_BIT(10)
#define KSZ8863_ANAL_Adv_100_Full           U16_BIT(9)
#define KSZ8863_ANAL_Adv_100_Half           U16_BIT(8)
#define KSZ8863_ANAL_Adv_10_Full            U16_BIT(7)
#define KSZ8863_ANAL_Adv_10_Half            U16_BIT(6)

#define KSZ8863_LMDCS_Vct_Enadle            U16_BIT(15)
#define KSZ8863_LMDCS_Vct_Result            U16_BIT(14)|U16_BIT(13)
#define KSZ8863_LMDCS_Vct_10M_Short         U16_BIT(12)
#define KSZ8863_LMDCS_Vct_Fault_Count       0x00ff

#define KSZ8863_SCR_Polrvs              U16_BIT(5)
#define KSZ8863_SCR_MDI_X_Status        U16_BIT(4)
#define KSZ8863_SCR_Force_Ink           U16_BIT(3)
#define KSZ8863_SCR_Pwesave             U16_BIT(2)
#define KSZ8863_SCR_Remote_LoopBack     U16_BIT(1)

typedef enum KSZ8863_Memory_Map
{
    Chip_ID_Addr = 0x00,

    Global_CR0_Addr = 0x02,
    Global_CR1_Addr,
    Global_CR2_Addr,
    Global_CR3_Addr,
    Global_CR4_Addr,

    Global_CR6_Addr = 0x08,
    Global_CR7_Addr,
    Global_CR8_Addr,
    Global_CR9_Addr,
    Global_CR10_Addr,

    Global_CR12_Addr = 0x0E,
    Global_CR13_Addr,

    Port1_CR0_Addr = 0x10,
    Port1_CR1_Addr,
    Port1_CR2_Addr,
    Port1_CR3_Addr,
    Port1_CR4_Addr,
    Port1_CR5_Addr,
    Port1_Q0_IDRL_Addr,         //!<Port1 Q0 Ingress Data Rate Limit
    Port1_Q1_IDRL_Addr,
    Port1_Q2_IDRL_Addr,
    Port1_Q3_IDRL_Addr,
    Port1_SCS_Addr,             //!<端口1特殊控制/状态寄存器
    Port1_LMDR_Addr,                //!<端口1线路检测结果寄存器
    Port1_CR12_Addr,
    Port1_CR13_Addr,
    Port1_SR0_Addr,
    Port1_SR1_Addr,
    
    Port2_CR0_Addr = 0x20,
    Port2_CR1_Addr,
    Port2_CR2_Addr,
    Port2_CR3_Addr,
    Port2_CR4_Addr,
    Port2_CR5_Addr,
    Port2_Q0_IDRL_Addr,         //!<Port2 Q0入口速率限制
    Port2_Q1_IDRL_Addr,
    Port2_Q2_IDRL_Addr,
    Port2_Q3_IDRL_Addr,
    Port2_SCS_Addr,             //!<端口2特殊控制/状态寄存器
    Port2_LMDR_Addr,                //!<端口2线路检测结果寄存器
    Port2_CR12_Addr,
    Port2_CR13_Addr,
    Port2_SR0_Addr,
    Port2_SR1_Addr,

    Port3_CR0_Addr = 0x30,
    Port3_CR1_Addr,
    Port3_CR2_Addr,
    Port3_CR3_Addr,
    Port3_CR4_Addr,
    Port3_CR5_Addr,
    Port3_Q0_IDRL_Addr,         //!<port3 Q0入口速率限制
    Port3_Q1_IDRL_Addr,
    Port3_Q2_IDRL_Addr,
    Port3_Q3_IDRL_Addr,
                            //!<0x3A-0x3E   Reserved
    Port3_SR1_Addr = 0x3f,
                            //!<0x40-0x5f   Reserved
    Reset_Addr = 0x43,

    TOS_PCR0_Addr = 0x60,   /*!<Pv4/IPv6 TOS优先级控制寄存器实现了一个完全解码的128位差分服务码点(DSCP)寄存器集，
                            用于从IP报头中的服务类型(TOS)字段确定优先级。TOS字段最有效的6位被完全解码为64种可能，
                            结果的奇异码与DSCP寄存器中相应的位进行比较，以确定优先级。*/
    TOS_PCR1_Addr,
    TOS_PCR2_Addr,
    TOS_PCR3_Addr,
    TOS_PCR4_Addr,
    TOS_PCR5_Addr,
    TOS_PCR6_Addr,
    TOS_PCR7_Addr,
    TOS_PCR8_Addr,
    TOS_PCR9_Addr,
    TOS_PCR10_Addr,
    TOS_PCR11_Addr,
    TOS_PCR12_Addr,
    TOS_PCR13_Addr,
    TOS_PCR14_Addr,
    TOS_PCR15_Addr,

    MACAddr_Addr = 0x70,    //!<寄存器112到117包含交换机引擎的MAC地址。这个48位地址被用作MAC的全双工流控制(暂停)帧的源地址。

    /**
     * @brief 寄存器118 ~ 120为用户自定义寄存器(udr)。这些是通用的读/写寄存器，
     * 可用于在KSZ8863和外部处理器之间传递用户定义的控制和状态信息
     * 
     */
    User_DR1_Addr = 0x76,
    User_DR2_Addr,
    User_DR3_Addr,

    /**
     * @brief 寄存器121 ~ 131提供对静态MAC地址表、VLAN表、动态MAC地址表和MIB计数器的读写权限
     * 
     */
    Indirect_AccessCR0_Addr = 0x79,
    Indirect_AccessCR1_Addr,
    Indirect_DR8_Addr,
    Indirect_DR7_Addr,
    Indirect_DR6_Addr,
    Indirect_DR5_Addr,
    Indirect_DR4_Addr,
    Indirect_DR3_Addr,
    Indirect_DR2_Addr,
    Indirect_DR1_Addr,
    Indirect_DR0_Addr,

    SA1_MACA1_Addr = 0x8E,  //!<Station Address 1 MACA1,站点地址用于自MAC地址滤波，详见端口寄存器控制5 位[6,5],高字节在147，低字节在142
    SA2_MACA2_Addr = 0x94,  //!<Station Address 1 MACA1,站点地址用于自MAC地址滤波，详见端口寄存器控制5 位[6,5],高字节在153，低字节在148

    Port1_Q0_EDRL_Addr = 0x9A,  //!<Port1 Q0 Egress Data Rate Limit
    Port1_Q1_EDRL_Addr,
    Port1_Q2_EDRL_Addr,
    Port1_Q3_EDRL_Addr,

    Port2_Q0_EDRL_Addr, //!<Port2 Q0 Egress Data Rate Limit
    Port2_Q1_EDRL_Addr,
    Port2_Q2_EDRL_Addr,
    Port2_Q3_EDRL_Addr,

    Port3_Q0_EDRL_Addr, //!<Port3 Q0 Egress Data Rate Limit
    Port3_Q1_EDRL_Addr,
    Port3_Q2_EDRL_Addr,
    Port3_Q3_EDRL_Addr,

    Mode_SR_Addr = 0xA6,

    Q3_HPP_SR_Addr = 0xA7,  //!<High Priority Packet Buffer Reserved for Q3
    Q2_HPP_SR_Addr,
    Q1_HPP_SR_Addr,
    Q0_HPP_SR_Addr,

    PM_FCSM1_SR_Addr = 0xAB,    //!< PM Usage Flow Control Select Mode 1
    PM_FCSM2_SR_Addr,
    PM_FCSM3_SR_Addr,
    PM_FCSM4_SR_Addr,

    Port1_TXQ_S_Q3_Addr = 0xAF,     //!<TXQ Split for Q3 in Port 1
    Port1_TXQ_S_Q2_Addr,
    Port1_TXQ_S_Q1_Addr,
    Port1_TXQ_S_Q0_Addr,

    Port2_TXQ_S_Q3_Addr,                //!<TXQ Split for Q3 in Port 1
    Port2_TXQ_S_Q2_Addr,
    Port2_TXQ_S_Q1_Addr,
    Port2_TXQ_S_Q0_Addr,

    Port3_TXQ_S_Q3_Addr,                //!<TXQ Split for Q3 in Port 1
    Port3_TXQ_S_Q2_Addr,
    Port3_TXQ_S_Q1_Addr,
    Port3_TXQ_S_Q0_Addr,

    Interrupt_SRC_Addr = 0xBB,          //!<Link Change Interrupt Enable Register
    Interrupt_SR_Addr,                  //!<Link Change Interrupt status Register
    
    FPOILE_CSR_Addr = 0xBD,             //!< Force Pause Off Iteration Limit Enable

    Fiber_Signal_T_Addr = 0xC0,         //!<Fiber Signal Threshold
    SRC_PVID_Addr = 0xC2,               //!<Insert SRC PVID
    PowerMan_LED_SR_Addr = 0xC3,        //!<Power Management and LED Mode
    SleepMode_Addr = 0xC4,
    FI_VID_F_HM_Addr = 0xC6,            //!<Forward Invalid VID Frame and Host Mode
    End_Addr
}KSZ8863_Memory_Map_Typedef;

#pragma pack (1)

typedef struct ksz8863_MemData
{
/**
 * @brief Chip ID Register 相应参数掩码,寄存器地址0x00
 * 
 */
    union
    {
        uint16_t Chip_ID;
        struct
        {
            char Family_ID              :8;
            char StartSwitch            :1;
            char Revision_ID            :3;
            char Chip_ID                :4;
        }Chip_ID_bit;
    };
    
/**
 * @brief 全局控制寄存器0，寄存器地址0x02
 * 
 */
    union
    {
        char Global_ctl0;
        struct
        {
            char reserved2                  :3;
            char Pass_Flow_CP               :1;     //!<交换机将通过802.1x流控报文
            char FS_MAC_Tab                 :1;     //!<使能生成树应用刷新静态MAC表功能
            char FD_MAC_Tab                 :1;     //!<使能生成树应用刷新动态MAC表功能
            char reserved1                  :1;
            char New_Back_Off_Enable        :1;     //!<为UNH设计的新的后退算法
        }Global_ctl0_bit;
    };
    
/**
 * @brief 全局控制寄存器1，寄存器地址0x03
 * 
 */
    union
    {
        char Global_ctl1;
        struct
        {
            char Agg_Back_Off_EN            :1;     //!<在半双工模式下启用更激进的后退算法，以提高性能。这不是IEEE的标准。
            char Fast_Age_En                :1;     //!<使能快速age
            char Aging_En                   :1;     //!<使能芯片的age功能
            char Frame_Len_Check            :1;     //!<将检查IEEE包中的帧长度字段。如果实际长度不匹配，数据包将被丢弃(长度/类型字段 < 1500)
            char IEEE_Rx_Dir_FC_En          :1;     //!<将使能接收方向流量控制功能。
            char IEEE_Tx_Dir_FC_En          :1;     //!<将使能传输方向流量控制功能。
            char port3_TTM_Enable           :1;     //!<启用端口3 Tail Tag模式
            char Pass_All_Frames            :1;     //!<切换所有数据包，包括坏数据包。仅用于调试目的。仅在嗅探模式下工作。
        }Global_ctl1_bit;
    };
    
/**
 * @brief 全局控制寄存器2，寄存器地址0x04
 * 
 */
    union
    {
        char Global_ctl2;
        struct
        {
            char reserved1                  :1;
            char Leg_Max_Packet_Size        :1;     //!<0 =将接受包大小不超过1536字节(包括)。
                                                    //!<1 =带标签的报文为1522字节，不带标签的报文为1518字节。任何大于指定值的数据包都将被丢弃。
            char Huge_Pack_Sup              :1;     //!<将接受1916字节(包括)以内的数据包大小。 该位设置将覆盖该寄存器第1位的设置。
            char No_Ex_colDrop              :1;     //!<当16个或更多的碰撞发生时，交换机不丢弃数据包
            char FC_BPF_Mod                 :1;     //!<选择公平模式。在该模式下，如果流控端口和非流控端口与同一个目的端口进行会话，可能会导致非流控端口的报文被丢弃。这是为了防止流量控制端口被长时间的流量控制。
            char Back_Pressure_Mod          :1;     //!<选择基于载波感知的背压
            char Mul_Storm_Pro_Dis          :1;     //!<广播风暴防护不包括组播报文。只有DA = FF-FF-FF-FF-FF-FF报文会被调整。
            char Un_VLAN_Mis_DisC           :1;     //!<所有报文不能跨越VLAN边界
        }Global_ctl2_bit;
    };
    
/**
 * @brief 全局控制寄存器3，寄存器地址0x05
 * 
 */
    union
    {
        char Global_ctl3;
        struct
        {
            char Sniff_Mode_Sel             :1;     //!<1 =将做RX和TX嗅探(源端口和目的端口需要匹配)
                                                    //!<0 =将做RX或TX嗅(源端口或目的端口需要匹配)。这是用于实现RX仅嗅探的模式
            char reserved2                  :2;
            char Weighted_FQ_En             :1;     //!<0=由寄存器175-186(0xAF-0xBA) bit[7]= 0设置的优先级方法用于端口1、端口2和端口3。
                                                    //!<1 =启用加权公平排队。当四个队列都有报文等待发送时，带宽分配为q3:q2:q1:q0 = 8:4:2:1。
                                                    //!<如果有任何队列为空，最高的非空队列将多获得一个权值。例如，如果q2为空，则q3:q2:q1:q0变为(8+1):0:2:1。
            char reserved1                  :2;
            char IGMP_Snoop_En              :1;     //!<IGMP snooping功能已开启。所有IGMP报文将被转发到交换机MII端口。
            char VLAN_Enable                :1;     //!<802.1Q VLAN模式开启。操作前需要先建立VLAN表
        }Global_ctl3_bit;
    };
    
/**
 * @brief 全局控制寄存器4、5，寄存器地址0x06、0x07,两个寄存器应该联合使用
 * 
 */
    union
    {
        uint16_t Global_ctl4;
        struct 
        {
            uint16_t BroadStorm_Protec_H        :3; 
            char Null_VID_Replace               :1;     //!<将NULL VID替换为端口VID
            char MII_10BT                       :1;     //!<交换机接口为10mbps模式
            char MII_FC_En                      :1;     //!<在交换机MII接口上使能全双工流量控制功能。
            char MII_Half_Dup_Mode              :1;     //!<使能MII接口半双工模式
            char reserved1                      :1;
            uint16_t BroadStorm_Protec_L        :8; //!<在预设的时间段内，在一个输入端口上允许多少个“64字节块”的数据包数据。100BT的周期是67 ms, 10BT的周期是500 ms。默认为1%。
                                                        //!<注:100BT速率:148,800帧/秒*67毫秒/间隔*1% = 99帧/间隔(约)= 0x63
            
            
        }Global_ctl4_bit;
    };

/**
 * @brief 全局控制寄存器6、7、8,寄存器地址0x08、0x09、0x0A
 * @note 3个寄存器地址保留
 */
    char Global_ctl6;
    char Global_ctl7;
    char Global_ctl8;

/**
 * @brief 全局控制寄存器9，寄存器地址0x0b
 * @note 保留位值应该为0x40
 */
    union
    {
        char Global_ctl9;
        struct
        {
            char reserved1                      :6;
            char  CPU_CLK_Sel                   :2; //!<00 = 31.25 MHz支持低于6 MHz的SPI速度
                                                    //!<01 = 62.5 MHz支持6 ~ 12.5 MHz之间的SPI速度
                                                    //!<defalut Value:10 = 125 MHz支持SPI速度12.5 MHz以上
                                                    //!<较低的时钟速度将节省更多的功耗，如果SPI不要求高速度，最好设置为31.25 MHz。
        }Global_ctl9_bit;
    };
    
/**
 * @brief 全局控制寄存器10、11，寄存器地址0x0c、0x0d
 * 
 */
    union
    {
        uint16_t Global_ctl10;
        struct
        {
            char Tag_0x0                        :2;     //!<IEEE 802.1p 的映射。当IEEE 802.1p标签的值为0x0时，该字段的值作为帧的优先级。
            char Tag_0x1                        :2;     //!<IEEE 802.1p 的映射。当IEEE 802.1p标签的值为0x1时，该字段的值作为帧的优先级。
            char Tag_0x2                        :2;     //!<IEEE 802.1p 的映射。当IEEE 802.1p标签的值为0x2时，该字段的值作为帧的优先级。
            char Tag_0x3                        :2;     //!<IEEE 802.1p 的映射。当IEEE 802.1p标签的值为0x3时，该字段的值作为帧的优先级。
            char Tag_0x4                        :2;     //!<IEEE 802.1p 的映射。当IEEE 802.1p标签的值为0x4时，该字段的值作为帧的优先级。
            char Tag_0x5                        :2;     //!<IEEE 802.1p 的映射。当IEEE 802.1p标签的值为0x5时，该字段的值作为帧的优先级。
            char Tag_0x6                        :2;     //!<IEEE 802.1p 的映射。当IEEE 802.1p标签的值为0x6时，该字段的值作为帧的优先级。
            char Tag_0x7                        :2;     //!<IEEE 802.1p 的映射。当IEEE 802.1p标签的值为0x7时，该字段的值作为帧的优先级。
        }Global_ctl10_bit;
    };

/**
 * @brief 全局控制寄存器12，寄存器地址0x0e
 * 
 */
    union
    {
        char Global_ctl12;
        struct
        {
            char Un_Packet_Def_Port             :3;     //!<指定发送目的MAC地址未知的数据包的端口。该特性由该寄存器的位[7]启用。
                                                        //!<第2位表示端口3。
                                                        //!<第1位表示端口2。
                                                        //!<第0位表示端口1。
                                                        //!< '1'包含一个端口，'0'排除一个端口.
            char reserved1                      :3;
            char Drive_Strength                 :1;     //!<16mA
            char Un_Packet_Def_Port_En          :1;     //!<将目的MAC地址未知的数据包发送到该寄存器的指定端口(位[2:0])
        }Global_ctl12_bit;
    };
    
/**
 * @brief 全局控制寄存器13，地址0x0f
 * 
 */
    char PHY_Addr;                                      //!<端口1 PHY地址，注意：端口2 PHY地址 = 端口1 PHY地址 + 1

/**
 * @brief 端口1控制寄存器0,端口1寄存器地址：0x10
 *
 */
    union
    {
        char Port1_ctl0;
        struct
        {
            char TXQ_Split_En                   :1;     //!<1 =将TXQ拆分为4队列配置。它不能在寄存器18、34、50位7的split 2队列同时启用。0 =无分割，视为1队列配置
            char Tag_Removal                    :1;     //!<1 =当端口输出报文时，交换机在接收到带有802.1p/q标记的报文时，将删除802.1p/q标记。交换机不会修改接收到的没有标签的数据包。0 =禁用标签移除
            char Tag_Insertion                  :1;     //!<当报文输出到端口时，交换机会对接收到的没有802.1p/q标记的报文添加802.1p/q标记。交换机不会对已经标记的数据包添加标记。插入的标签是入口端口的“端口VID”。
                                                        //!<0 =禁用标签插入
                                                        //!<注意:对于可用的标签插入，必须先设置寄存器194位[5:0]
            char Port_based_prio_Class          :2;     //!<00 =如果“Diffserv”或“802.1p”分类未启用或分类失败，端口上的入站报文将被分类为优先级0队列。
                                                        //!<01 =如果“Diffserv”或“802.1p”分类未启用或分类失败，端口上的入接口报文将被分类为优先级1队列。
                                                        //!<10 =如果“Diffserv”或“802.1p”分类未启用或分类失败，端口上的入接口报文将被分类为优先级2队列。
                                                        //!<11 =如果“Diffserv”或“802.1p”分类未启用或分类失败，端口上的入站报文将被分类为优先级3队列。
                                                        //!<“DiffServ”、“802.1p”和端口优先级可以同时使能。802.1p和DSCP的OR结果将覆盖端口优先级。
            char _802_1p_prio_Class_En          :1;     //!<开启端口入接口报文的802.1p优先级分类功能
            char Diff_Prio_Class_En             :1;     //!<在端口上启用IPv4报文的DiffServ优先级分类
            char Broad_Storm_Prot_En            :1;     //!<在端口上为入接口数据包启用广播风暴保护,default Value:0,不启用
        }Port1_ctl0_bit;
    };
    
/**
 * @brief 端口1控制寄存器1,端口1寄存器地址：0x11
 * 
 */
    union
    {
        char Port1_ctl1;
        struct
        {
            char port_VLAN_membership           :3;     //!<定义端口的出口VLAN成员关系。端口只能在成员内部通信。位2表示端口3，位1表示端口2，位0表示端口1。'1'包含一个端口。'0'不包含端口
            char User_Prio_ceil                 :1;     //!<1 =如果报文的“用户优先级字段”大于端口默认标记寄存器的“用户优先级字段”，则将报文的“用户优先级字段”替换为端口默认标记寄存器的“用户优先级字段”。
                                                        //!<0 =不比较和替换数据包的“用户优先级字段”
            char Double_tag                     :1;     //!<1 =所有报文都将被打入端口的port default tag，不管原始报文是否打了tag
            char Trans_Sniff                    :1;     //!<1 =在该端口上传输的所有数据包都将被标记为“监听数据包”，并转发到指定的“嗅探器端口”
            char Receive_Sniff                  :1;     //!<1 =端口上收到的所有数据包都将被标记为“监控数据包”，并转发到指定的“嗅探端口”
            char Sniffer_port                   :1;     //!<1 =端口被指定为嗅探器端口，将传输被监控的数据包。
        }Port1_ctl1_bit;
    };
    
/**
 * @brief 端口1控制寄存器2,端口1寄存器地址：0x12
 * 
 */
    union
    {
        char Port1_ctl2;
        struct
        {
            char Learning_Disable               :1;     //!<1 = 失能交换机地址学习
            char Rx_En                          :1;     //!<1 = 使能接收
            char Tx_En                          :1;     //!<1 = 使能发送
            char Back_Pressure_En               :1;     //!<1 = 使能半双工Back Pressure
            char Force_FC                       :1;     //!<1 =将始终使能端口的全双工流量控制，无论自动协商结果如何。0 =根据自动协商结果启用全双工流量控制。
            char Discard_non_PVID               :1;     //!<1 =交换机丢弃与入端口默认VID不匹配的报文
            char Ingress_VLAN_Filter            :1;     //!<1 =交换机将丢弃VLAN表位中VID端口成员不包括入端口的报文。
            char _2Queue_Sp_of_Tx_En            :1;     //!<它不能在寄存器16、32和48位0拆分4queue的同时启用。
        }Port1_ctl2_bit;
    };
    
/**
 * @brief 端口1控制寄存器3、4,端口1寄存器地址：0x13、0x14
 * 
 */
    union
    {
        uint16_t Port1_ctl3;                            //!<vid标签
        struct
        {
            uint16_t Def_Tag_H                  :4;
            uint16_t CFI_bit                    :1;
            uint16_t User_prio_bits             :3;
            uint16_t Def_Tag_L                  :8;
        }Port1_ctl3_bit;
    };
    
/**
 * @brief 端口1控制寄存器5,端口1寄存器地址：0x15
 * 
 */
    union
    {
        char Port1_ctl5;
        struct
        {
            char Count_Pre                      :1;     //!<1 =每个帧的前导字节(每帧8)包含在输入和输出速率限制计算中。
            char Count_IFG                      :1;     //!<1 =每个帧的最小帧间间隙(IFG)字节(每帧12)包含在输入和输出速率限制计算中。
            char Limit_Mode                     :2;     //!<进入限制模式
                                                        //!<这些位决定什么类型的帧是有限的，并计算入帧率限制。
                                                        //!<00 =限制和计数所有帧
                                                        //!<01 = limit and count广播，组播和泛洪的单播帧
                                                        //!<10 =限制和计数广播和组播帧
                                                        //!<仅限广播帧数
            char Drop_Ingress_Tag               :1;
            char Self_Addr_MACA2_Filter_En      :1;     //!<使能端口2MACA1地址自过滤
            char Self_Addr_MACA1_Filter_En      :1;     //!<使能端口1MACA1地址自过滤
            char Port3_MII_Mode                 :1;     //!< = 1
        }Port1_ctl5_bit;
        
    };
    
/**
 * @brief 端口1 Q0入口数据速率限制,端口1寄存器地址：0x16
 * 
 */
    union
    {
        char Port1_Q0_IDRL;
        struct
        {
            char Q0_IDRL                        :7;     //!<优先级为0帧的入站数据速率限制该优先级队列的入站流量根据“入站数据速率选择表”进行整形。
            char reserved                       :1;
        }Port1_Q0_IDRL_bit;
    };
    
/**
 * @brief 端口1 Q1入口数据速率限制,端口1寄存器地址：0x17
 * 
 */
    union
    {
        char Port1_Q1_IDRL;
        struct
        {
            char Q1_IDRL                        :7;     //!<优先级为1帧的入站数据速率限制该优先级队列的入站流量根据“入站数据速率选择表”进行整形。
            char reserved                       :1;
        }Port1_Q1_IDRL_bit;
    };

/**
 * @brief 端口1 Q2入口数据速率限制,端口1寄存器地址：0x18
 * 
 */
    union
    {
        char Port1_Q2_IDRL;
        struct
        {
            char Q2_IDRL                        :7;     //!<优先级为2帧的入站数据速率限制该优先级队列的入站流量根据“入站数据速率选择表”进行整形。
            char reserved                       :1;
        }Port1_Q2_IDRL_bit;
    };

/**
 * @brief 端口1 Q3入口数据速率限制,端口1寄存器地址：0x19
 * 
 */
    union
    {
        char Port1_Q3_IDRL;
        struct
        {
            char Q3_IDRL                        :7;     //!<优先级为3帧的入站数据速率限制该优先级队列的入站流量根据“入站数据速率选择表”进行整形。
            char reserved                       :1;
        }Port1_Q3_IDRL_bit;
    };

/**
 * @brief 端口1 特殊控制/状态寄存器,端口1寄存器地址：0x1A、0x1B
 * 
 */
    union
    {
        uint16_t Port1_SCS;
        struct
        {
            uint16_t Vct_fault_Count_H          :1;
            uint16_t Remote_Loopback            :1;
            uint16_t reserved1                  :1;
            uint16_t Force_Ink                  :1;
            uint16_t Vct_En                     :1;
            uint16_t Vct_result                 :2;
            uint16_t Vct_10M_Short              :1;
            uint16_t Vct_fault_Count_L          :8;
        }Port1_SCS_bit;
    };
    
/**
 * @brief 端口1 控制寄存器12,端口1寄存器地址：0x1C
 * 
 */
    union
    {
        char Port1_ctl12;
        struct
        {
            char Adv_10BT_Half_Dup_Cap          :1;     //!<1 = 允许使用10BT 半双工，0 = 不使用
            char Adv_10BT_Full_Dup_Cap          :1;     //!<1 = 允许使用10BT 全双工，0 = 不使用
            char Adv_100BT_Half_Dup_Cap         :1;     //!<1 = 允许使用100BT 半双工，0 = 不使用
            char Adv_100BT_Full_Dup_Cap         :1;     //!<1 = 允许使用100BT 全双工， 0 = 不使用
            char Adv_FC_Cap                     :1;     //!<1 = 允许使用流控能力 ，0 = 抑制流控能力
            char Force_Duplex                   :1;     //!<失能自动协商或者自动协商失败时，1 = Full_Duplex 
            char Force_Speed                    :1;     //!<失能自动协商或者自动协商失败时，1 = 100BT 
            char AN_En                          :1;     //!<1 = 使能自动协商
        }Port1_ctl12_bit;
    };
    
/**
 * @brief 端口1 控制寄存器13,端口1寄存器地址：0x1D
 * 
 */
    union
    {
        char Port1_ctl13;
        struct
        {
            char LoopBack                       :1;     //!<回环
            char Force_MDI                      :1;     //!<关闭自动交叉时，1 = 直连模式，0 = 交叉模式
            char Dis_Auto_MDI                   :1;     //!<1 = 关闭自动交叉
            char Power_down                     :1;
            char Restart_AN                     :1;     //!<重启自动协商
            char Txdis                          :1;     //!<关闭端口发送
            char LED_Off                        :1;     //!<关闭端口所有LED
        }Port1_ctl13_bit;
    };
    
/**
 * @brief 端口1 状态寄存器，寄存器地址：0x1E、0x1F
 * @note 除hp_MDIX外全部RO
 */
    union
    {
        uint16_t Port1_Status;
        struct
        {
            uint16_t Par_10BT_Half_Dup_Cap      :1;     //!<1 = 连接方允许使用10BT 半双工，0 = 不使用
            uint16_t Par_10BT_Full_Dup_Cap      :1;     //!<1 = 连接方允许使用10BT 全双工，0 = 不使用
            uint16_t Par_100BT_Half_Dup_Cap     :1;     //!<1 = 连接方允许使用100BT 半双工，0 = 不使用
            uint16_t Par_100BT_Full_Dup_Cap     :1;     //!<1 = 连接方允许使用100BT 全双工， 0 = 不使用
            uint16_t Par_FC_Cap                 :1;     //!<1 = 连接方有流控能力
            uint16_t Link_Good                  :1;     //!<1 = 连接良好
            uint16_t AN_Done                    :1;     //!<1 = 自动协商完成
            uint16_t MDI_X_Status               :1;     //!<1 = 直连模式
            uint16_t Far_End_Fault              :1;     //!<1 = 检测到远端故障状态
            uint16_t Operation_Duplex           :1;     //!<1 = 连接模式全双工
            uint16_t Operation_Speed            :1;     //!<1 = 连接速度100Mbps
            uint16_t RX_FC_Active               :1;     //!<1 = 接收流控活动
            uint16_t Tx_FC_Active               :1;     //!<1 = 发送流控活动
            uint16_t Polrvs                     :1;     //!<1 = 极性逆转
            uint16_t reserved1                  :1;
            uint16_t Hp_MDIX                    :1;     //!<1 = hp ，0 = mircochip
        }Port1_Status_bit;
    };
    



/**
 * @brief 端口2控制寄存器0,端口2寄存器地址：0x20
 *          
 */
    union
    {
        char Port2_ctl0;
        struct
        {
            char TXQ_Split_En                   :1;     //!<1 =将TXQ拆分为4队列配置。它不能在寄存器18、34、50位7的split 2队列同时启用。0 =无分割，视为1队列配置
            char Tag_Removal                    :1;     //!<1 =当端口输出报文时，交换机在接收到带有802.1p/q标记的报文时，将删除802.1p/q标记。交换机不会修改接收到的没有标签的数据包。0 =禁用标签移除
            char Tag_Insertion                  :1;     //!<当报文输出到端口时，交换机会对接收到的没有802.1p/q标记的报文添加802.1p/q标记。交换机不会对已经标记的数据包添加标记。插入的标签是入口端口的“端口VID”。
                                                        //!<0 =禁用标签插入
                                                        //!<注意:对于可用的标签插入，必须先设置寄存器194位[5:0]
            char Port_based_prio_Class          :2;     //!<00 =如果“Diffserv”或“802.1p”分类未启用或分类失败，端口上的入站报文将被分类为优先级0队列。
                                                        //!<01 =如果“Diffserv”或“802.1p”分类未启用或分类失败，端口上的入接口报文将被分类为优先级1队列。
                                                        //!<10 =如果“Diffserv”或“802.1p”分类未启用或分类失败，端口上的入接口报文将被分类为优先级2队列。
                                                        //!<11 =如果“Diffserv”或“802.1p”分类未启用或分类失败，端口上的入站报文将被分类为优先级3队列。
                                                        //!<“DiffServ”、“802.1p”和端口优先级可以同时使能。802.1p和DSCP的OR结果将覆盖端口优先级。
            char _802_1p_prio_Class_En          :1;     //!<开启端口入接口报文的802.1p优先级分类功能
            char Diff_Prio_Class_En             :1;     //!<在端口上启用IPv4报文的DiffServ优先级分类
            char Broad_Storm_Prot_En            :1;     //!<在端口上为入接口数据包启用广播风暴保护,default Value:0,不启用
        }Port2_ctl0_bit;
    };
    
/**
 * @brief 端口2控制寄存器1,端口2寄存器地址：0x21
 * 
 */
    union
    {
        char Port2_ctl1;
        struct
        {
            char port_VLAN_membership           :3;     //!<定义端口的出口VLAN成员关系。端口只能在成员内部通信。位2表示端口3，位1表示端口2，位0表示端口2。'1'包含一个端口。'0'不包含端口
                                                        //!<0 =不比较和替换数据包的“用户优先级字段”
            char User_Prio_ceil                 :1;     //!<1 =如果报文的“用户优先级字段”大于端口默认标记寄存器的“用户优先级字段”，则将报文的“用户优先级字段”替换为端口默认标记寄存器的“用户优先级字段”。
            char Double_tag                     :1;     //!<1 =所有报文都将被打入端口的port default tag，不管原始报文是否打了tag
            char Trans_Sniff                    :1;     //!<1 =在该端口上传输的所有数据包都将被标记为“监听数据包”，并转发到指定的“嗅探器端口”
            char Receive_Sniff                  :1;     //!<1 =端口上收到的所有数据包都将被标记为“监控数据包”，并转发到指定的“嗅探端口”
            char Sniffer_port                   :1;     //!<1 =端口被指定为嗅探器端口，将传输被监控的数据包。
        }Port2_ctl1_bit;
    };
    
/**
 * @brief 端口2控制寄存器2,端口2寄存器地址：0x22
 * 
 */
    union
    {
        char Port2_ctl2;
        struct
        {
            char Learning_Disable               :1;     //!<1 = 失能交换机地址学习
            char Rx_En                          :1;     //!<1 = 使能接收
            char Tx_En                          :1;     //!<1 = 使能发送
            char Back_Pressure_En               :1;     //!<1 = 使能半双工Back Pressure
            char Force_FC                       :1;     //!<1 =将始终使能端口的全双工流量控制，无论自动协商结果如何。0 =根据自动协商结果启用全双工流量控制。
            char Discard_non_PVID               :1;     //!<1 =交换机丢弃与入端口默认VID不匹配的报文
            char Ingress_VLAN_Filter            :1;     //!<1 =交换机将丢弃VLAN表位中VID端口成员不包括入端口的报文。
            char _2Queue_Sp_of_Tx_En            :1;     //!<它不能在寄存器16、32和48位0拆分4queue的同时启用。
        }Port2_ctl2_bit;
    };
    
/**
 * @brief 端口2控制寄存器3、4,端口2寄存器地址：0x23、0x24
 * 
 */
    union
    {
        uint16_t Port2_ctl3;                            //!<vid标签
        struct
        {
            uint16_t Def_Tag_H                  :4;
            uint16_t CFI_bit                    :1;
            uint16_t User_prio_bits             :3;
            uint16_t Def_Tag_L                  :8;
        }Port2_ctl3_bit;
    };
    
/**
 * @brief 端口2控制寄存器5,端口2寄存器地址：0x25
 * 
 */
    union
    {
        char Port2_ctl5;
        struct
        {
            char Count_Pre                      :1;     //!<1 =每个帧的前导字节(每帧8)包含在输入和输出速率限制计算中。
            char Count_IFG                      :1;     //!<1 =每个帧的最小帧间间隙(IFG)字节(每帧12)包含在输入和输出速率限制计算中。
            char Limit_Mode                     :2;     //!<进入限制模式
                                                        //!<这些位决定什么类型的帧是有限的，并计算入帧率限制。
                                                        //!<00 =限制和计数所有帧
                                                        //!<01 = limit and count广播，组播和泛洪的单播帧
                                                        //!<10 =限制和计数广播和组播帧
                                                        //!<仅限广播帧数
            char Drop_Ingress_Tag               :1;
            char Self_Addr_MACA2_Filter_En      :1;     //!<使能端口2MACA1地址自过滤
            char Self_Addr_MACA1_Filter_En      :1;     //!<使能端口1MACA1地址自过滤
            char reserved1                      :1;
        }Port2_ctl5_bit;
        
    };
    
/**
 * @brief 端口2 Q0入口数据速率限制,端口2寄存器地址：0x26
 * 
 */
    union
    {
        char Port2_Q0_IDRL;
        struct
        {
            char Q0_IDRL                        :7;     //!<优先级为0帧的入站数据速率限制该优先级队列的入站流量根据“入站数据速率选择表”进行整形。
            char reserved                       :1;
        }Port2_Q0_IDRL_bit;
    };
    
/**
 * @brief 端口2 Q1入口数据速率限制,端口2寄存器地址：0x27
 * 
 */
    union
    {
        char Port2_Q1_IDRL;
        struct
        {
            char Q1_IDRL                        :7;     //!<优先级为1帧的入站数据速率限制该优先级队列的入站流量根据“入站数据速率选择表”进行整形。
            char reserved                       :1;
        }Port2_Q1_IDRL_bit;
    };

/**
 * @brief 端口2 Q2入口数据速率限制,端口2寄存器地址：0x28
 * 
 */
    union
    {
        char Port2_Q2_IDRL;
        struct
        {
            char Q2_IDRL                        :7;     //!<优先级为2帧的入站数据速率限制该优先级队列的入站流量根据“入站数据速率选择表”进行整形。
            char reserved                       :1;
        }Port2_Q2_IDRL_bit;
    };

/**
 * @brief 端口2 Q3入口数据速率限制,端口2寄存器地址：0x29
 * 
 */
    union
    {
        char Port2_Q3_IDRL;
        struct
        {
            char Q3_IDRL                        :7;     //!<优先级为3帧的入站数据速率限制该优先级队列的入站流量根据“入站数据速率选择表”进行整形。
            char reserved                       :1;
        }Port2_Q3_IDRL_bit;
    };

/**
 * @brief 端口2 特殊控制/状态寄存器,端口2寄存器地址：0x2A、0x2B
 * 
 */
    union
    {
        uint16_t Port2_SCS;
        struct
        {
            uint16_t Vct_fault_Count_H          :1;
            uint16_t Remote_Loopback            :1;
            uint16_t reserved1                  :1;
            uint16_t Force_Ink                  :1;
            uint16_t Vct_En                     :1;
            uint16_t Vct_result                 :2;
            uint16_t Vct_10M_Short              :1;
            uint16_t Vct_fault_Count_L          :8;
        }Port2_SCS_bit;
    };
    
/**
 * @brief 端口2 控制寄存器12,端口2寄存器地址：0x2C
 * 
 */
    union
    {
        char Port2_ctl12;
        struct
        {
            char Adv_10BT_Half_Dup_Cap          :1;     //!<1 = 允许使用10BT 半双工，0 = 不使用
            char Adv_10BT_Full_Dup_Cap          :1;     //!<1 = 允许使用10BT 全双工，0 = 不使用
            char Adv_100BT_Half_Dup_Cap         :1;     //!<1 = 允许使用100BT 半双工，0 = 不使用
            char Adv_100BT_Full_Dup_Cap         :1;     //!<1 = 允许使用100BT 全双工， 0 = 不使用
            char Adv_FC_Cap                     :1;     //!<1 = 允许使用流控能力 ，0 = 抑制流控能力
            char Force_Duplex                   :1;     //!<失能自动协商或者自动协商失败时，1 = Full_Duplex 
            char Force_Speed                    :1;     //!<失能自动协商或者自动协商失败时，1 = 100BT 
            char AN_En                          :1;     //!<1 = 使能自动协商
        }Port2_ctl12_bit;
    };
    
/**
 * @brief 端口2 控制寄存器13,端口2寄存器地址：0x2D
 * 
 */
    union
    {
        char Port2_ctl13;
        struct
        {
            char LoopBack                       :1;     //!<回环
            char Force_MDI                      :1;     //!<关闭自动交叉时，1 = 直连模式，0 = 交叉模式
            char Dis_Auto_MDI                   :1;     //!<1 = 关闭自动交叉
            char Power_down                     :1;
            char Restart_AN                     :1;     //!<重启自动协商
            char Txdis                          :1;     //!<关闭端口发送
            char LED_Off                        :1;     //!<关闭端口所有LED
        }Port2_ctl13_bit;
    };
    
/**
 * @brief 端口2 状态寄存器，寄存器地址：0x2E、0x2F
 * @note 除hp_MDIX外全部RO
 */
    union
    {
        uint16_t Port2_Status;
        struct
        {
            uint16_t Par_10BT_Half_Dup_Cap      :1;     //!<1 = 连接方允许使用10BT 半双工，0 = 不使用
            uint16_t Par_10BT_Full_Dup_Cap      :1;     //!<1 = 连接方允许使用10BT 全双工，0 = 不使用
            uint16_t Par_100BT_Half_Dup_Cap     :1;     //!<1 = 连接方允许使用100BT 半双工，0 = 不使用
            uint16_t Par_100BT_Full_Dup_Cap     :1;     //!<1 = 连接方允许使用100BT 全双工， 0 = 不使用
            uint16_t Par_FC_Cap                 :1;     //!<1 = 连接方有流控能力
            uint16_t Link_Good                  :1;     //!<1 = 连接良好
            uint16_t AN_Done                    :1;     //!<1 = 自动协商完成
            uint16_t MDI_X_Status               :1;     //!<1 = 直连模式
            uint16_t reserved2                  :1;
            uint16_t Operation_Duplex           :1;     //!<1 = 连接模式全双工
            uint16_t Operation_Speed            :1;     //!<1 = 连接速度100Mbps
            uint16_t RX_FC_Active               :1;     //!<1 = 接收流控活动
            uint16_t Tx_FC_Active               :1;     //!<1 = 发送流控活动
            uint16_t Polrvs                     :1;     //!<1 = 极性逆转
            uint16_t reserved1                  :1;
            uint16_t Hp_MDIX                    :1;     //!<1 = hp ，0 = mircochip
        }Port2_Status_bit;
    };


/**
 * @brief 端口3控制寄存器0,端口3寄存器地址：0x30
 *          
 */
    union
    {
        char Port3_ctl0;
        struct
        {
            char TXQ_Split_En                   :1;     //!<1 =将TXQ拆分为4队列配置。它不能在寄存器18、34、50位7的split 2队列同时启用。0 =无分割，视为1队列配置
            char Tag_Removal                    :1;     //!<1 =当端口输出报文时，交换机在接收到带有802.1p/q标记的报文时，将删除802.1p/q标记。交换机不会修改接收到的没有标签的数据包。0 =禁用标签移除
            char Tag_Insertion                  :1;     //!<当报文输出到端口时，交换机会对接收到的没有802.1p/q标记的报文添加802.1p/q标记。交换机不会对已经标记的数据包添加标记。插入的标签是入口端口的“端口VID”。
                                                        //!<0 =禁用标签插入
                                                        //!<注意:对于可用的标签插入，必须先设置寄存器194位[5:0]
            char Port_based_prio_Class          :2;     //!<00 =如果“Diffserv”或“802.1p”分类未启用或分类失败，端口上的入站报文将被分类为优先级0队列。
                                                        //!<01 =如果“Diffserv”或“802.1p”分类未启用或分类失败，端口上的入接口报文将被分类为优先级1队列。
                                                        //!<10 =如果“Diffserv”或“802.1p”分类未启用或分类失败，端口上的入接口报文将被分类为优先级2队列。
                                                        //!<11 =如果“Diffserv”或“802.1p”分类未启用或分类失败，端口上的入站报文将被分类为优先级3队列。
                                                        //!<“DiffServ”、“802.1p”和端口优先级可以同时使能。802.1p和DSCP的OR结果将覆盖端口优先级。
            char _802_1p_prio_Class_En          :1;     //!<开启端口入接口报文的802.1p优先级分类功能
            char Diff_Prio_Class_En             :1;     //!<在端口上启用IPv4报文的DiffServ优先级分类
            char Broad_Storm_Prot_En            :1;     //!<在端口上为入接口数据包启用广播风暴保护,default Value:0,不启用
            
        }Port3_ctl0_bit;
    };
    
/**
 * @brief 端口3控制寄存器1,端口3寄存器地址：0x31
 * 
 */
    union
    {
        char Port3_ctl1;
        struct
        {
            char port_VLAN_membership           :3;     //!<定义端口的出口VLAN成员关系。端口只能在成员内部通信。位2表示端口3，位1表示端口3，位0表示端口3。'1'包含一个端口。'0'不包含端口
            char User_Prio_ceil                 :1;     //!<1 =如果报文的“用户优先级字段”大于端口默认标记寄存器的“用户优先级字段”，则将报文的“用户优先级字段”替换为端口默认标记寄存器的“用户优先级字段”。
                                                        //!<0 =不比较和替换数据包的“用户优先级字段”
            char Double_tag                     :1;     //!<1 =所有报文都将被打入端口的port default tag，不管原始报文是否打了tag
            char Trans_Sniff                    :1;     //!<1 =在该端口上传输的所有数据包都将被标记为“监听数据包”，并转发到指定的“嗅探器端口”
            char Receive_Sniff                  :1;     //!<1 =端口上收到的所有数据包都将被标记为“监控数据包”，并转发到指定的“嗅探端口”
            char Sniffer_port                   :1;     //!<1 =端口被指定为嗅探器端口，将传输被监控的数据包。
        }Port3_ctl1_bit;
    };
    
/**
 * @brief 端口3控制寄存器2,端口3寄存器地址：0x32
 * 
 */
    union
    {
        char Port3_ctl2;
        struct
        {
            char Learning_Disable               :1;     //!<1 = 失能交换机地址学习
            char Rx_En                          :1;     //!<1 = 使能接收
            char Tx_En                          :1;     //!<1 = 使能发送
            char Back_Pressure_En               :1;     //!<1 = 使能半双工Back Pressure
            char Force_FC                       :1;     //!<1 =将始终使能端口的全双工流量控制，无论自动协商结果如何。0 =根据自动协商结果启用全双工流量控制。
            char Discard_non_PVID               :1;     //!<1 =交换机丢弃与入端口默认VID不匹配的报文
            char Ingress_VLAN_Filter            :1;     //!<1 =交换机将丢弃VLAN表位中VID端口成员不包括入端口的报文。
            char _2Queue_Sp_of_Tx_En            :1;     //!<它不能在寄存器16、32和48位0拆分4queue的同时启用。
        }Port3_ctl2_bit;
    };
    
/**
 * @brief 端口3控制寄存器3、4,端口3寄存器地址：0x33、0x34
 * 
 */
    union
    {
        uint16_t Port3_ctl3;                            //!<vid标签
        struct
        {
            uint16_t Def_Tag_H                  :4;
            uint16_t CFI_bit                    :1;
            uint16_t User_prio_bits             :3;
            uint16_t Def_Tag_L                  :8;
        }Port3_ctl3_bit;
    };
    
/**
 * @brief 端口3控制寄存器5,端口3寄存器地址：0x35
 * 
 */
    union
    {
        char Port3_ctl5;
        struct
        {
            char Count_Pre                      :1;     //!<1 =每个帧的前导字节(每帧8)包含在输入和输出速率限制计算中。
            char Count_IFG                      :1;     //!<1 =每个帧的最小帧间间隙(IFG)字节(每帧12)包含在输入和输出速率限制计算中。
            char Limit_Mode                     :2;     //!<进入限制模式
                                                        //!<这些位决定什么类型的帧是有限的，并计算入帧率限制。
                                                        //!<00 =限制和计数所有帧
                                                        //!<01 = limit and count广播，组播和泛洪的单播帧
                                                        //!<10 =限制和计数广播和组播帧
                                                        //!<仅限广播帧数
            
            char Drop_Ingress_Tag               :1;
            char reserved2                      :1;
            char reserved1                      :1;
            char Port3_MII_Mode                 :1;     //!< 1 = MAC模式，0 = PHY模式
            
        }Port3_ctl5_bit;
        
    };
    
/**
 * @brief 端口3 Q0入口数据速率限制,端口3寄存器地址：0x36
 * 
 */
    union
    {
        char Port3_Q0_IDRL;
        struct
        {
            char Q0_IDRL                        :7;     //!<优先级为0帧的入站数据速率限制该优先级队列的入站流量根据“入站数据速率选择表”进行整形。
            char RMII_Refclk_Invert             :1;     //!<1 = ref clk 极性翻转
        }Port3_Q0_IDRL_bit;
    };
    
/**
 * @brief 端口3 Q1入口数据速率限制,端口3寄存器地址：0x37
 * 
 */
    union
    {
        char Port3_Q1_IDRL;
        struct
        {
            char Q1_IDRL                        :7;     //!<优先级为1帧的入站数据速率限制该优先级队列的入站流量根据“入站数据速率选择表”进行整形。
            char reserved                       :1;
        }Port3_Q1_IDRL_bit;
    };

/**
 * @brief 端口3 Q2入口数据速率限制,端口3寄存器地址：0x38
 * 
 */
    union
    {
        char Port3_Q2_IDRL;
        struct
        {
            char Q2_IDRL                        :7;     //!<优先级为2帧的入站数据速率限制该优先级队列的入站流量根据“入站数据速率选择表”进行整形。
            char reserved                       :1;
        }Port3_Q2_IDRL_bit;
    };

/**
 * @brief 端口3 Q3入口数据速率限制,端口3寄存器地址：0x39
 * 
 */
    union
    {
        char Port3_Q3_IDRL;
        struct
        {
            char Q3_IDRL                        :7;     //!<优先级为3帧的入站数据速率限制该优先级队列的入站流量根据“入站数据速率选择表”进行整形。
            char reserved                       :1;
        }Port3_Q3_IDRL_bit;
    };

/**
 * @brief 保留，地址0x3A-0x3E
 * 
 */
    char reserved1[5];

/**
 * @brief 端口3 状态寄存器，寄存器地址：0x3F
 * @note 除hp_MDIX外全部RO
 */
    union
    {
        char Port3_Status;
        struct
        {
            char reserved2                      :1;
            char Operation_Duplex               :1;     //!<1 = 连接模式全双工
            char Operation_Speed                :1;     //!<1 = 连接速度100Mbps
            char RX_FC_Active                   :1;     //!<1 = 接收流控活动
            char Tx_FC_Active                   :1;     //!<1 = 发送流控活动
            char reserved1                      :3;
        }Port3_Status_bit;
    };

/**
 * @brief 保留，地址0x40-0x42
 * 
 */
    char reserved2[3];

/**
 * @brief Reset，地址0x43
 * 
 */
    union
    {
        char Reset;
        struct
        {
            char PCS_Reset                      :1;     //!<pcs复位是在做软件复位时用于完全复位,PCS重置将重置PHY的PCS层的状态机和时钟域
            char reserved1                      :3;
            char Soft_Reset                     :1;     //!<软件复位会将所有寄存器复位到开机复位或热复位的初始值(保留表带值)。
            char reserved2                      :3;
        }Reset_bit;
    };

/**
 * @brief 保留，地址0x44-0x5F
 * 
 */
    char reserved3[28];

/**
 * @brief TOS优先级控制寄存器，寄存器地址：0x60-0x6F
 * @note IPv4/IPv6 TOS优先级控制寄存器实现了一个完全解码的128位差分服务码点(DSCP)寄存器集，
 * 用于从IP报头中的服务类型(TOS)字段确定优先级。TOS字段最有效的6位被完全解码为64种可能，
 * 结果的奇异码与DSCP寄存器中相应的位进行比较，以确定优先级。
 * 
 * 
 */
    union
    {
        char TOS_prio_ctl[16];
        struct
        {
            char DSCP_0x00                      :2;
            char DSCP_0x01                      :2;
            char DSCP_0x02                      :2;
            char DSCP_0x03                      :2;
            char DSCP_0x04                      :2;
            char DSCP_0x05                      :2;
            char DSCP_0x06                      :2;
            char DSCP_0x07                      :2;
            char DSCP_0x08                      :2;
            char DSCP_0x09                      :2;
            char DSCP_0x0A                      :2;
            char DSCP_0x0B                      :2;
            char DSCP_0x0C                      :2;
            char DSCP_0x0D                      :2;
            char DSCP_0x0E                      :2;
            char DSCP_0x0F                      :2;
            char DSCP_0x10                      :2;
            char DSCP_0x11                      :2;
            char DSCP_0x12                      :2;
            char DSCP_0x13                      :2;
            char DSCP_0x14                      :2;
            char DSCP_0x15                      :2;
            char DSCP_0x16                      :2;
            char DSCP_0x17                      :2;
            char DSCP_0x18                      :2;
            char DSCP_0x19                      :2;
            char DSCP_0x1A                      :2;
            char DSCP_0x1B                      :2;
            char DSCP_0x1C                      :2;
            char DSCP_0x1D                      :2;
            char DSCP_0x1E                      :2;
            char DSCP_0x1F                      :2;
            char DSCP_0x20                      :2;
            char DSCP_0x21                      :2;
            char DSCP_0x22                      :2;
            char DSCP_0x23                      :2;
            char DSCP_0x24                      :2;
            char DSCP_0x25                      :2;
            char DSCP_0x26                      :2;
            char DSCP_0x27                      :2;
            char DSCP_0x28                      :2;
            char DSCP_0x29                      :2;
            char DSCP_0x2A                      :2;
            char DSCP_0x2B                      :2;
            char DSCP_0x2C                      :2;
            char DSCP_0x2D                      :2;
            char DSCP_0x2E                      :2;
            char DSCP_0x2F                      :2;
            char DSCP_0x30                      :2;
            char DSCP_0x31                      :2;
            char DSCP_0x32                      :2;
            char DSCP_0x33                      :2;
            char DSCP_0x34                      :2;
            char DSCP_0x35                      :2;
            char DSCP_0x36                      :2;
            char DSCP_0x37                      :2;
            char DSCP_0x38                      :2;
            char DSCP_0x39                      :2;
            char DSCP_0x3A                      :2;
            char DSCP_0x3B                      :2;
            char DSCP_0x3C                      :2;
            char DSCP_0x3D                      :2;
            char DSCP_0x3E                      :2;
            char DSCP_0x3F                      :2;
        }TOS_prio_ctl_bit;
    };
    
/**
 * @brief 交换机引擎的MAC地址,寄存器地址0x70-0x75
 * 
 */
    char maca[6];

/**
 * @brief 用户寄存器 ，寄存器地址0x76-0x78
 * @note 这些是通用的读/写寄存器，可用于在KSZ8863和外部处理器之间传递用户定义的控制和状态信息。
 */
    char udr[3];

/**
 * @brief 间接访问控制寄存器，寄存器地址0x79-0x7A
 * @note 寄存器0x79-0x8A提供对静态MAC地址表、VLAN表、动态MAC地址表和MIB计数器的读写权限。
 * 对寄存器0x8A的写操作会触发读/写命令。读或写访问是由寄存器0x79位4决定的。所以先写该寄存器高位，再读取低位
 */
    union
    {
        uint16_t Indirect_Access_ctl;
        struct
        {
            uint16_t Indirect_addr_H            :2; //!<要读取的地址
            uint16_t Table_Sel                  :2;     //!< 00 = 静态MAC地址表
                                                        //!< 01 = VLAN表
                                                        //!< 10 = 动态MAC地址表
                                                        //!< 11 = MIB计数器
            uint16_t RWcode                     :1;     //!<1 = read cycle. 0 = write cycle
            uint16_t reserved1                  :3;
            uint16_t Indirect_addr_L                :8; //!<要读取的地址
        }Indirect_Access_ctl_bit;
    };
    
/**
 * @brief 间接访问数据寄存器，寄存器地址0x7B-0x83
 * 
 */
    char Indirect_Data[9];

/**
 * @brief 保留，寄存器地址0x84-0x8D
 * 
 */
    char reserved4[10];

/**
 * @brief 站点地址寄存器,MACA1寄存器地址0x8E-0x93,MACA1寄存器地址0x94-0x99
 * @note 站点地址用于自MAC地址滤波，详见端口寄存器控制5位[6,5]。
 * @note 地址低位在前，高位在后，即MAC地址高位存储在Station_MACA1[4],MAC地址低位存储在Station_MACA1[0]
 */
    char Station_MACA1[6];
    char Station_MACA2[6];

/**
 * @brief 端口1 Q0出口速率限制，寄存器地址0x9A
 * 
 */
    union
    {
        char Port1_Q0_EDRL;
        struct
        {
            char Q0_EDRL                    :7;     //!<优先级0帧的出口数据速率限制该优先级队列的出口流量根据“数据速率限制选择表”进行整形。
            char reserved1                  :1;
        }Port1_Q0_EDRL_bit;
    };
    
/**
 * @brief 端口1 Q1出口速率限制，寄存器地址0x9B
 * 
 */
    union
    {
        char Port1_Q1_EDRL;
        struct
        {
            char Q1_EDRL                    :7;     //!<优先级1帧的出口数据速率限制该优先级队列的出口流量根据“数据速率限制选择表”进行整形。
            char reserved1                  :1;
        }Port1_Q1_EDRL_bit;
    };

/**
 * @brief 端口1 Q2出口速率限制，寄存器地址0x9C
 * 
 */
    union
    {
        char Port1_Q2_EDRL;
        struct
        {
            char Q2_EDRL                    :7;     //!<优先级2帧的出口数据速率限制该优先级队列的出口流量根据“数据速率限制选择表”进行整形。
            char reserved1                  :1;
        }Port1_Q2_EDRL_bit;
    };

/**
 * @brief 端口1 Q3出口速率限制，寄存器地址0x9D
 * 
 */
    union
    {
        char Port1_Q3_EDRL;
        struct
        {
            char Q3_EDRL                    :7;     //!<优先级1帧的出口数据速率限制该优先级队列的出口流量根据“数据速率限制选择表”进行整形。
            char reserved1                  :1;
        }Port1_Q3_EDRL_bit;
    };

/**
 * @brief 端口2 Q0出口速率限制，寄存器地址0x9E
 * 
 */
    union
    {
        char Port2_Q0_EDRL;
        struct
        {
            char Q0_EDRL                    :7;     //!<优先级0帧的出口数据速率限制该优先级队列的出口流量根据“数据速率限制选择表”进行整形。
            char reserved1                  :1;
        }Port2_Q0_EDRL_bit;
    };
    
/**
 * @brief 端口2 Q1出口速率限制，寄存器地址0x9F
 * 
 */
    union
    {
        char Port2_Q1_EDRL;
        struct
        {
            char Q1_EDRL                    :7;     //!<优先级1帧的出口数据速率限制该优先级队列的出口流量根据“数据速率限制选择表”进行整形。
            char reserved1                  :1;
        }Port2_Q1_EDRL_bit;
    };

/**
 * @brief 端口2 Q2出口速率限制，寄存器地址0xA0
 * 
 */
    union
    {
        char Port2_Q2_EDRL;
        struct
        {
            char Q2_EDRL                    :7;     //!<优先级2帧的出口数据速率限制该优先级队列的出口流量根据“数据速率限制选择表”进行整形。
            char reserved1                  :1;
        }Port2_Q2_EDRL_bit;
    };

/**
 * @brief 端口2 Q3出口速率限制，寄存器地址0xA1
 * 
 */
    union
    {
        char Port2_Q3_EDRL;
        struct
        {
            char Q3_EDRL                    :7;     //!<优先级3帧的出口数据速率限制该优先级队列的出口流量根据“数据速率限制选择表”进行整形。
            char reserved1                  :1;
        }Port2_Q3_EDRL_bit;
    };

/**
 * @brief 端口3 Q0出口速率限制，寄存器地址0xA2
 * 
 */
    union
    {
        char Port3_Q0_EDRL;
        struct
        {
            char Q0_EDRL                    :7;     //!<优先级0帧的出口数据速率限制该优先级队列的出口流量根据“数据速率限制选择表”进行整形。
            char reserved1                  :1;
        }Port3_Q0_EDRL_bit;
    };
    
/**
 * @brief 端口3 Q1出口速率限制，寄存器地址0xA3
 * 
 */
    union
    {
        char Port3_Q1_EDRL;
        struct
        {
            char Q1_EDRL                    :7;     //!<优先级1帧的出口数据速率限制该优先级队列的出口流量根据“数据速率限制选择表”进行整形。
            char reserved1                  :1;
        }Port3_Q1_EDRL_bit;
    };

/**
 * @brief 端口3 Q2出口速率限制，寄存器地址0xA4
 * 
 */
    union
    {
        char Port3_Q2_EDRL;
        struct
        {
            char Q2_EDRL                    :7;     //!<优先级2帧的出口数据速率限制该优先级队列的出口流量根据“数据速率限制选择表”进行整形。
            char reserved1                  :1;
        }Port3_Q2_EDRL_bit;
    };

/**
 * @brief 端口3 Q3出口速率限制，寄存器地址0xA5
 * 
 */
    union
    {
        char Port3_Q3_EDRL;
        struct
        {
            char Q3_EDRL                    :7;     //!<优先级3帧的出口数据速率限制该优先级队列的出口流量根据“数据速率限制选择表”进行整形。
            char reserved1                  :1;
        }Port3_Q3_EDRL_bit;
    };  

/**
 * @brief KSZ8863模式指示器,寄存器地址0xA6
 * @note RO
 */
    union
    {
        char Mode_Indicator;
        struct
        {
            char Port2_Media                :1;     //!<1 = port2 Copper,only = 1
            char Port1_Media                :1;     //!<1 = port1 Copper,0 = port1 fiber
            char Port3_Interface_Mod        :1;     //!<1 = MAC , 0 = PHY
            char reserved3                  :1;
            char Port3_Interface            :1;     //!< 1 = RMII ,0 = MII
            char reserved2                  :1;
            char _48p_pkg_of_2PHY           :1;     //!< only = 1
            char reserved1                  :1;
        }Mode_Indicator_bit;
    };
    
/**
 * @brief 高优先级报文缓存区，保留给Q3、Q2、Q1、Q0,寄存器地址0xA7-0xAA
 * @note only = 0x45352515,RO
 */
    char High_Prio_packet_Buffer_Reserved[4];

/**
 * @brief PM使用流程控制选择模式,保留，寄存器地址0xAB-0xAE
 * @note only = 0x18100805,RO
 */
    char PM_Usage_FC_Select_Mod_Reserved[4];

/**
 * @brief 端口1 Q3 TXQ队列优先级，寄存器地址0xAF
 * 
 */
    union
    {
        char port1_Q3_TXQ_Split;
        struct
        {
            char reserved1                  :7;
            char Prio_Select                :1;     //!<使用寄存器 176/177/178(0xB0/0xB1/0xB2) bit[7]=0和寄存器5 bit[3]=0使优先级更高
                                                    //!<4个队列的优先级比为8:4:2:1,2个队列的优先级比为2:1,寄存器 184/185/186(0xB0/0xB1/0xB2) bit[7]=1
        }port1_Q3_TXQ_Split_bit;
    };
    
/**
 * @brief 端口1 Q2 TXQ队列优先级，寄存器地址0xB0
 * 
 */
    union
    {
        char port1_Q2_TXQ_Split;
        struct
        {
            char reserved1                  :7;
            char Prio_Select                :1;     //!<使用寄存器 175/177/178(0xAF/0xB1/0xB2) bit[7]=0和寄存器5 bit[3]=0使优先级更高
                                                    //!<4个队列的优先级比为8:4:2:1,2个队列的优先级比为2:1,寄存器 175/177/178(0xAF/0xB1/0xB2) bit[7]=1
        }port1_Q2_TXQ_Split_bit;
    };

/**
 * @brief 端口1 Q1 TXQ队列优先级，寄存器地址0xB1
 * 
 */
    union
    {
        char port1_Q1_TXQ_Split;
        struct
        {
            char reserved1                  :7;
            char Prio_Select                :1;     //!<使用寄存器 175/176/178(0xAF/0xB0/0xB2) bit[7]=0和寄存器5 bit[3]=0使优先级更高
                                                    //!<4个队列的优先级比为8:4:2:1,2个队列的优先级比为2:1,寄存器 175/176/178(0xAF/0xB0/0xB2) bit[7]=1
        }port1_Q1_TXQ_Split_bit;
    };

/**
 * @brief 端口1 Q0 TXQ队列优先级，寄存器地址0xB2
 * 
 */
    union
    {
        char port1_Q0_TXQ_Split;
        struct
        {
            char reserved1                  :7;
            char Prio_Select                :1;     //!<使用寄存器 175/176/177(0xAF/0xB0/0xB1) bit[7]=0和寄存器5 bit[3]=0使优先级更高
                                                    //!<4个队列的优先级比为8:4:2:1,2个队列的优先级比为2:1,寄存器 175/176/177(0xAF/0xB0/0xB1) bit[7]=1
        }port1_Q0_TXQ_Split_bit;
    };

/**
 * @brief 端口2 Q3 TXQ队列优先级，寄存器地址0xB3
 * 
 */
    union
    {
        char port2_Q3_TXQ_Split;
        struct
        {
            char reserved1                  :7;
            char Prio_Select                :1;     //!<使用寄存器 180/181/182(0xB4/0xB5/0xB6) bit[7]=0和寄存器5 bit[3]=0使优先级更高
                                                    //!<4个队列的优先级比为8:4:2:1,2个队列的优先级比为2:1,寄存器 180/181/182(0xB5/0xB6/0xB6) bit[7]=1
        }port2_Q3_TXQ_Split_bit;
    };
    
/**
 * @brief 端口2 Q2 TXQ队列优先级，寄存器地址0xB4
 * 
 */
    union
    {
        char port2_Q2_TXQ_Split;
        struct
        {
            char reserved1                  :7;
            char Prio_Select                :1;     //!<使用寄存器 179/181/182(0xB3/0xB5/0xB6) bit[7]=0和寄存器5 bit[3]=0使优先级更高
                                                    //!<4个队列的优先级比为8:4:2:1,2个队列的优先级比为2:1,寄存器 179/181/182(0xB3/0xB5/0xB6) bit[7]=1
        }port2_Q2_TXQ_Split_bit;
    };

/**
 * @brief 端口2 Q1 TXQ队列优先级，寄存器地址0xB5
 * 
 */
    union
    {
        char port2_Q1_TXQ_Split;
        struct
        {
            char reserved1                  :7;
            char Prio_Select                :1;     //!<使用寄存器 179/180/182(0xB3/0xB4/0xB6) bit[7]=0和寄存器5 bit[3]=0使优先级更高
                                                    //!<4个队列的优先级比为8:4:2:1,2个队列的优先级比为2:1,寄存器 179/180/182(0xB3/0xB4/0xB6) bit[7]=1
        }port2_Q1_TXQ_Split_bit;
    };

/**
 * @brief 端口2 Q0 TXQ队列优先级，寄存器地址0xB6
 * 
 */
    union
    {
        char port2_Q0_TXQ_Split;
        struct
        {
            char reserved1                  :7;
            char Prio_Select                :1;     //!<使用寄存器 179/180/181(0xB3/0xB4/0xB5) bit[7]=0和寄存器5 bit[3]=0使优先级更高
                                                    //!<4个队列的优先级比为8:4:2:1,2个队列的优先级比为2:1,寄存器 179/180/181(0xB3/0xB4/0xB5) bit[7]=1
        }port2_Q0_TXQ_Split_bit;
    };

/**
 * @brief 端口3 Q3 TXQ队列优先级，寄存器地址0xB7
 * 
 */
    union
    {
        char port3_Q3_TXQ_Split;
        struct
        {
            char reserved1                  :7;
            char Prio_Select                :1;     //!<使用寄存器 184/185/186(0xB8/0xB9/0xBA) bit[7]=0和寄存器5 bit[3]=0使优先级更高
                                                    //!<4个队列的优先级比为8:4:2:1,2个队列的优先级比为2:1,寄存器 184/185/186(0xB8/0xB9/0xBA) bit[7]=1
        }port3_Q3_TXQ_Split_bit;
    };
    
/**
 * @brief 端口3 Q2 TXQ队列优先级，寄存器地址0xB8
 * 
 */
    union
    {
        char port3_Q2_TXQ_Split;
        struct
        {
            char reserved1                  :7;
            char Prio_Select                :1;     //!<使用寄存器 183/185/186(0xB7/0xB9/0xBA) bit[7]=0和寄存器5 bit[3]=0使优先级更高
                                                    //!<4个队列的优先级比为8:4:2:1,2个队列的优先级比为2:1,寄存器 183/185/186(0xB7/0xB9/0xBA) bit[7]=1
        }port3_Q2_TXQ_Split_bit;
    };

/**
 * @brief 端口3 Q1 TXQ队列优先级，寄存器地址0xB9
 * 
 */
    union
    {
        char port3_Q1_TXQ_Split;
        struct
        {
            char reserved1                  :7;
            char Prio_Select                :1;     //!<使用寄存器 183/184/186(0xB7/0xB8/0xBA) bit[7]=0和寄存器5 bit[3]=0使优先级更高
                                                    //!<4个队列的优先级比为8:4:2:1,2个队列的优先级比为2:1,寄存器 183/184/186(0xB7/0xB8/0xBA) bit[7]=1
        }port3_Q1_TXQ_Split_bit;
    };

/**
 * @brief 端口3 Q0 TXQ队列优先级，寄存器地址0xBA
 * 
 */
    union
    {
        char port3_Q0_TXQ_Split;
        struct
        {
            char reserved1                  :7;
            char Prio_Select                :1;     //!<使用寄存器 183/184/185(0xB7/0xB8/0xB9) bit[7]=0和寄存器5 bit[3]=0使优先级更高
                                                    //!<4个队列的优先级比为8:4:2:1,2个队列的优先级比为2:1,寄存器 183/184/185(0xB7/0xB8/0xB9) bit[7]=1
        }port3_Q0_TXQ_Split_bit;
    };

/**
 * @brief 中断使能寄存器，寄存器地址0xBB
 * @note 首先设置寄存器187，然后设置寄存器188 (W1C= Write ' 1 ' Clear)，等待在pin 35 INTRN上的中断，以改变链路。
 */
    union
    {
        char Interrupt_En;
        struct
        {
            char P1_MII_link_Change_En      :1;
            char P2_Link_Change_En          :1;
            char P3_Link_Change_En          :1;
            char reserved1                  :4;
            char P1_P2_Link_Change_En       :1;
        }Interrupt_En_bit;
    };
    
/**
 * @brief 中断控制寄存器，寄存器地址0xBC
 * @note 写1清除
 */
    union
    {
        char Interrupt_SC;
        struct
        {
            char P1_MII_link_Change     :1;
            char P2_Link_Change         :1;
            char P3_Link_Change         :1;
            char reserved1              :4;
            char P1_P2_Link_Change      :1;
        }Interrupt_SC_bit;
    };
    
/**
 * @brief 强制暂停关闭迭代限制,寄存器地址0xBD
 * 
 */
    char Force_Pause_off_En;                    //!<在请求流控制无效之前的160毫秒

/**
 * @brief 保留,寄存器地址0xBE-0xBF
 * 
 */
    char reserved5[2];

/**
 * @brief 光纤信号阈值,寄存器地址0xC0
 * 
 */
    union
    {
        char Fiber_Threshold;
        struct
        {
            char reserved1                  :6;
            char Port1_Fiber_Signal_Th      :1;     //!< 1 = 2.0V 0 = 1.2V
            char Port2_Fiber_Signal_Th      :1;     //!< 1 = 2.0V 0 = 1.2V
        }Fiber_Threshold_bit;
    };
    
/**
 * @brief 内部1.8V LDO控制，寄存器地址0xC1
 * 
 */
    union
    {
        char Internal_LDO_ctl;
        struct
        {
            char Reserved1                  :6;
            char Dis_Internal_LDO           :1;     //!<1 = 关闭内部1.8V LDO
            char reserved1                  :1;
        }Internal_LDO_ctl_bit;
    };

/**
 * @brief 插入源端口PVID，寄存器地址0xC2
 * 
 */
    union
    {
        char Insert_SRC_PVID;
        struct
        {
            char Insert_SRC_P3VID_at_P2     :1;
            char Insert_SRC_P3VID_at_P1     :1;
            char Insert_SRC_P2VID_at_P3     :1;
            char Insert_SRC_P2VID_at_P1     :1;
            char Insert_SRC_P1VID_at_P3     :1;
            char Insert_SRC_P1VID_at_P2     :1;
            char reserved1                  :2;
        }Insert_SRC_PVID_bit;
    };
    
/**
 * @brief 电源管理，寄存器地址0xC3
 * 
 */
    union
    {
        char Power_Man_LED_Mod;
        struct
        {
            char power_Man_Mod              :2;     //!<00 = normal 01 = 能量检测模式 10 = software power down 11 = 节能模式
            char PLL_OFF_En                 :1;     //!<1 = PLL power down
            char LED_Out_Mod                :1;     //!<1 = 模拟模块内部拉伸的能量信号将被抵消并输出到LED1，内部器件准备信号将被抵消并输出到LED0。0 = LED1/LED0引脚将指示常规LED输出。
            char LDE_Mod                    :2;     //!<00 = LED0: Link/ACT, LED1: Speed
                                                    //!<01 = LED0: Link, LED1: ACT
                                                    //!<10 = LED0: Link/ACT, LED1: Duplex
                                                    //!<11 = LED0: Link, LED1: Duplex
            char Switch_Power_Down          :1;
            char CPU_IF_Power_Down          :1;
        }Power_Man_LED_Mod_bit;
    };
    
/**
 * @brief 睡眠模式，寄存器地址0xC4
 * @note 该值用于控制ED模式开启时，设备连续检测到无能量事件进入低功耗状态的最短时间。
 * 单位是20毫秒。默认的go_sleep时间是1.6秒
 */
    char Sleep_Mod;

/**
 * @brief 保留，寄存器地址0xC5
 * 
 */
    char reserved6;

/**
 * @brief 转发无效的VID帧和主机模式,寄存器地址0xC6
 * 
 */
    union
    {
        char Forward_Invalid_VID;
        struct
        {
            char Host_IF_Mod            :2;     //!<00 = I2C Host mode 01 = I2C Client Mode 10 = SPI Client Mode 11 = SMI Mode
            char P1_RMII_Clk            :1;     //!<1 = Interbal 0 = External
            char P3_RMII_Clk            :1;     //!<1 = Interbal 0 = External
            char Forward_IVID           :3;
            char reserved1              :1;
        }Forward_Invalid_VID_bit;
    };
    
}ksz8863_MemData_def;

#pragma pack ()

#endif // !__KSZ8863_REG_H

