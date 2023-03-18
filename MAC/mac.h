#ifndef __MAC_H
#define __MAC_H

#include <stdint.h>
#include <stdbool.h>
#include "mac_opt.h"

typedef struct
{
    union
    {
        volatile uint32_t MACCR;            /*<MAC配置寄存器是MAC的工作模式寄存器。它建立了接收和发送工作模式*/
        struct 
        {
            volatile uint32_t reserved1 :2;     
            volatile uint32_t re        :1;     /*<Receiver enable*/
            volatile uint32_t te        :1;     /*<Transmitter enable*/
            volatile uint32_t dc        :1;     /*<Deferral check*/
            volatile uint32_t bl        :2;     /*<Back-off limit*/
            volatile uint32_t apcs      :1;     /*<Automatic pad/CRC stripping*/
            volatile uint32_t reserved2 :1;
            volatile uint32_t rd        :1;     /*<Retry disable,禁止重试*/
            volatile uint32_t ipco      :1;     /*<IPv4checksumoffload,IPv4校验和减荷*/
            volatile uint32_t dm        :1;     /*<Duplexmode*/
            volatile uint32_t lm        :1;     /*<Loopbackmode*/
            volatile uint32_t rod       :1;     /*<Receive own disable,关闭自接收*/
            volatile uint32_t fes       :1;     /*<Fast Ethernet speed,此位用于选择MII,RMII接口速度,1:100Mbit/s*/
            volatile uint32_t reserved3 :1;
            volatile uint32_t csd       :1;     /*禁止载波侦听*/
            volatile uint32_t ifg       :1;     /*<帧间间隙*/
            volatile uint32_t reserved4 :2;     
            volatile uint32_t jd        :1;     /*<Jabber disable*/
            volatile uint32_t wd        :1;     /*<Watchdog disable*/
            volatile uint32_t reserved5 :1; 
            volatile uint32_t cstf      :1;     /*<类型帧的CRC去除*/
            volatile uint32_t reserved6 :6;     
        }MACCR_bit;
        
    };

    union 
    {
        volatile uint32_t MACFFR;               /*<MAC帧过滤寄存器包含用于接收帧的过滤控件。该寄存器的某些控件转到MAC的地址检查模
                                                块，以执行第一级地址过滤。第二级过滤基于其它控件（例如传送不良帧和传送控制帧）对
                                                传入帧过滤*/
        struct 
        {
            volatile uint32_t pm        :1;     /*<Promiscuous mode,混合模式,当该位置1时，不论其目标或源地址为何，地址过滤器都传送所有传入的帧,PM=1 时，
                                                始终将接收状态字SA/DA过滤失败状态位清零*/
            volatile uint32_t hu        :1;     /*<Hash unicast,1：MAC根据散列表对单播帧执行目标地址过滤
                                                0：MAC对单播帧执行完美目标地址过滤，即将DA字段与DA寄存器中编程的值进行比较*/
            volatile uint32_t hm        :1;     /*<Hash multicast,1：MAC根据散列表对接收到的多播帧执行目标地址过滤
                                                0：MAC对多播帧执行完美目标地址过滤，即将DA字段与DA寄存器中编程的值进行比较*/
            volatile uint32_t daif      :1;     /*<Destination address inverse filtering,目标地址反向过滤*/
            volatile uint32_t pam       :1;     /*<Pass all multicast,传送所有多播帧*/
            volatile uint32_t bfd       :1;     /*<Broadcast frames disable,禁止广播帧*/
            volatile uint32_t pcf       :2;     /*<Pass control frames,传送控制帧
                                                00:MAC阻止所有控制帧到达应用程序
                                                01:MAC将除了暂停控制帧以外的所有控制帧转发到应用程序
                                                10:即使所有控制帧通过地址过滤失败,MAC仍将它们转发给应用程序
                                                11:MAC转发通过地址过滤的控制帧*/
            volatile uint32_t saif      :1;     /*<Source address inverse filtering,源地址反向过滤*/
            volatile uint32_t saf       :1;     /*<Source address filter,源地址过滤*/
            volatile uint32_t hpf       :1;     /*<Hash or perfect filter,散列或完美过滤器
                                                1：如果HM或HU位置1，则地址过滤器传送与完美过滤或散列过滤匹配的帧*/
            volatile uint32_t reserved1 :20;
            volatile uint32_t ra        :1;     /*<Receive all*/
        }MACFFRbit;
        
    };
    
    volatile uint32_t MACHTHR;                  /*<64位散列表用于组地址过滤。对于散列过滤，传入帧中目标地址的内容通过CRC逻辑传
                                                送，CRC寄存器中的高6位用于对散列表内容进行索引*/
    volatile uint32_t MACHTLR;                                          

    union
    {
        volatile uint32_t MACMIIAR;         /*<MII地址寄存器通过管理接口控制外部PHY的寄存器*/
        struct
        {
            volatile uint32_t mb        :1;     /*<MII busy,向ETH_MACMIIAR和ETH_MACMIIDR写入前，此位应读取逻辑0*/
            volatile uint32_t mw        :1;     /*<MII write,
                                                1：是在告知PHY，将要启动一个使用MII数据寄存器的写操作
                                                0：则表示会启动一个读操作，将数据放入MII数据寄存器*/
            volatile uint32_t cr        :3;     /*<Clockrange,CR时钟范围选项可确定HCLK频率并用于决定MDC时钟频率*/
            volatile uint32_t reserved1 :1;
            volatile uint32_t mr        :5;     /*<MIIregister,这些位在所选PHY器件中选择需要的MII寄存器*/
            volatile uint32_t pa        :5;     /*<PHYaddress,该字段指示正在访问32个可能的PHY器件中的哪一个*/
            volatile uint32_t reserved2 :16;
        }MACMIIARbit;
        
    };
    
    volatile uint32_t MACMIIDR;

    union
    {
        volatile uint32_t MACFCR;           /*<流控制寄存器通过MAC来管理控制（暂停命令）帧的生成和接收*/
        struct
        {
            volatile uint32_t fcb       :1;     /*<Flow control busy/back pressure activate,流控制忙/背压激活*/
            volatile uint32_t tfce      :1;     /*<Transmitflowcontrolenable,发送流控使能，
                                                在全双工模式下，1：MAC将使能流控制操作来发送暂停帧
                                                0：将禁用MAC中的流控制操作，MAC不会传送任何暂停帧
                                                在半双工模式下，1：MAC将使能背压操作
                                                0：将禁止背压功能*/
            volatile uint32_t rfce      :1;     /*<Receive flow control enable,接收流控使能,
                                                1：MAC对接收到的暂停帧进行解码，并禁止其在指定时间（暂停时间）发送*/
            volatile uint32_t upfd      :1;     /*<Unicast pause frame detect,单播暂停帧检测*/
            volatile uint32_t plt       :2;     /*<Pause low threshold,此字段配置暂停定时器的阈值，达到该值时，会自动重新传输暂停帧*/
            volatile uint32_t reserved1 :1;     
            volatile uint32_t zqpd      :1;     /*<Zero-quanta pause disable,
                                                1：当来自FIFO层的流控制信号去断言后，此位会禁止自动生成零时间片暂停控制帧*/
            volatile uint32_t reserved2 :8;     
            volatile uint32_t pt        :16;    /*<Pause time,此字段保留发送控制帧中暂停时间字段要使用的*/
        }MACFCRbit;
    };
    
    union
    {
        volatile uint32_t MACVLANTR;        /*<VLAN标记寄存器包含用于标识VLAN帧的IEEE802.1QVLAN标记*/
        struct
        {
            volatile uint32_t vlanti    :16;    /*<此字段包含用于标识VLAN帧的802.1QVLAN标记，并与正在接收的VLAN帧的第十五和
                                                第十六字节进行比较
                                                位[15:13]是用户优先级
                                                位[12]是标准格式指示符(CFI)
                                                位[11:0]是VLAN标记的VLAN标识(VID)字段,
                                                VLANTC位置1时，仅使用VID（位[11:0]）进行比较
                                                如果VLANTI（VLANTI[11:0]，如果VLANTC位置1）全部为零，则MAC不会检查用
                                                VLAN标记比较的第十五和第十六字节，而是将类型字段值为0x8100的所有帧均声明为
                                                VLAN*/
            volatile uint32_t vlantc    :1;     /*<12位VLAN标记比较,
                                                1：使用12位VLAN标识符而不是完整的16位VLAN 标记进行比较和过滤，VLAN标记的位[11:0]与收到的VLAN标记帧的相应字段进行比较
                                                0：收到的VLAN帧的第十五和第十六字节的全部16位都要进行比较*/
            volatile uint32_t reserved1 :15;
        }MACVLANTRbit;
    };
    
    volatile uint32_t reserved1[2];

    volatile uint32_t MACRWUFFR;

    union
    {
        volatile uint32_t MACPMTCSR;        /*<配置唤醒事件请求并监视唤醒事件*/
        struct
        {
            volatile uint32_t pd        :1;     /*<1：MAC接收器在收到预期的magicpacket或远程唤醒帧之前会丢弃所有接收到的帧。然后该位会自动清除并关闭掉电模式
                                                在收到预期的magicpacket或远程唤醒帧之前，软件也会清除该位
                                                该位被清除后，MAC将接收到的帧转发给应用程序
                                                只能当MagicPacket使能位，全局单播位或远程唤醒帧使能位被置高时，才能将该位置1*/
            volatile uint32_t mpe       :1;     /*<1：表示在收到magicpacket时会生成电源管理事件*/
            volatile uint32_t wfe       :1;     /*<1：表示在收到远程唤醒帧时会生成电源管理事件*/
            volatile uint32_t reserved1 :2;
            volatile uint32_t mpr       :1;     /*<1：该位表示的是，因为接收到Magicpacket而生成了电源管理事件。读该寄存器可以将该位清零*/
            volatile uint32_t wfr       :1;     /*<1：该位表示的是因为收到远程唤醒帧而生成了电源管理事件。读该寄存器可以将该位清零*/
            volatile uint32_t reserved2 :2;
            volatile uint32_t gu        :1;     /*<1：所有通过MAC地址过滤的单播包均被使能为远程唤醒帧*/
            volatile uint32_t reserved3 :21;
            volatile uint32_t wffrpr    :1;     /*<1：会将远程唤醒帧过滤寄存器指针复位为0b000。它会在1个时钟周期后自动清零*/
        }MACPMTCSRbit;
    };
    
    volatile uint32_t reserved2;

    union
    {
        volatile uint32_t MACDBGR;
        struct
        {
            volatile uint32_t mmrpea    :1;     /*<MAC接收器处于非空闲状态*/
            volatile uint32_t msfrwcs   :2;     /*<msfrwcs[1]：Rx异步FIFO在HCLK时钟域进行读操作（MAC取出数据）
                                                msfrwcs[0]：Rx异步FIFO在MACRX_CLK时钟域进行写操作（MAC存入数据）*/
            volatile uint32_t reserved1 :1;
            volatile uint32_t rfwra     :1;     /*<RxFIFO写控制器有效*/
            volatile uint32_t rfrcs     :2;     /*<RxFIFO读控制器状态
                                                00：IDLE状态
                                                01：读取帧数据
                                                10：读取帧状态（或时间戳）
                                                11：刷新帧数据和状态*/
            volatile uint32_t reserved2 :1;
            volatile uint32_t rffl      :2;     /*<RxFIFO填充级别
                                                00：RxFIFO为空
                                                01：RxFIFO填充级别低于流控制取消激活阈值
                                                10：RxFIFO填充级别高于流控制激活阈值
                                                11：RxFIFO已满*/
            volatile uint32_t reserved3 :6;
            volatile uint32_t mmtea     :1;     /*<MACMII发送引擎有效*/
            volatile uint32_t mtfcs     :2;     /*<MAC发送帧控制器状态
                                                00：空闲
                                                01：等待前一个帧的状态或IFG/回退阶段结束
                                                10：生成并发送暂停控制帧（在全双工模式下）
                                                11：从 FIFO 读取待发送的帧*/
            volatile uint32_t mtp       :1;     /*<MAC发送器处于暂停*/
            volatile uint32_t tfrs      :2;     /*<TxFIFO读状态*/
            volatile uint32_t tfwa      :1;     /*<TxFIFO写有效*/
            volatile uint32_t reserved4 :1;
            volatile uint32_t tfne      :1;     /*<TxFIFO非空*/
            volatile uint32_t tff       :1;     /*<TxFIFO已满*/
            volatile uint32_t reserved5 :5;
        }MACDBGRbit;
    };
    
    union
    {
        volatile uint32_t MACSR;                /*<在MAC中标识可生成中断的事件*/
        struct
        {
            volatile uint32_t reserved1 :3;
            volatile uint32_t pmts      :1;     /*<0:未接收到唤醒帧或Magic Packet帧，1：在低功耗模式下，接收到唤醒帧或Magic Packet*/
            volatile uint32_t mmcs      :1;     /*<只要6:5中的任何一个位被设置为高电平，此位即会被设置为高电平。仅当这两个位均为
                                                低电平时，此位才被清零*/
            volatile uint32_t mmcrs     :1;     /*<ETH_MMCRIR寄存器中生成中断，此位就为高电平
                                                当此中断寄存器(ETH_MMCRIR)中的所有位都清零时，此位清零*/
            volatile uint32_t mmcts     :1;     /*<ETH_MMCTIRRegister寄存器中生成中断，此位就为高电平*/
            volatile uint32_t reserved2 :2;
            volatile uint32_t tsts      :1;     /*<当系统时间值等于或大于目标时间高位与低位寄存器中指定的值时，此位置1.*/
            volatile uint32_t reserved3 :22;
        }MACSRbit;
    };
    
    union
    {
        volatile uint32_t MACIMR;               /*<屏蔽因ETH_MACSR寄存器中的相应事件导致的中断信号*/
        struct
        {
            volatile uint32_t reserved1 :3;     
            volatile uint32_t pmtim     :1;     /*<时间戳触发中断屏蔽*/
            volatile uint32_t reserved2 :5; 
            volatile uint32_t tstim     :1;     /*<1：禁止因ETH_MACSR中的PMT状态位置1而触发中断信号*/
            volatile uint32_t reserved3 :22;
        }MACIMRbit;
    };
    
    union
    {
        volatile uint32_t MACA0HR;          /*<MAC地址0高位寄存器可保存站的第一个6字节MAC地址的高16位*/
        struct
        {
            volatile uint32_t maca0h    :16;    /*<此字段包含6字节MAC地址0的高16位(47:32)，MAC使用此字段过滤所接收的帧以及将
                                                MAC地址插入到发送流控制（暂停）帧中*/
            volatile uint32_t reserved1 :15;
            volatile uint32_t mo        :1;     /*<始终为1*/
        }MACA0HRbit;
        
    };
    volatile uint32_t MACA0LR;                  /*<此字段包含6字节MAC地址0的低32位，MAC使用此字段过滤所接收的帧以及将MAC
                                                地址插入到发送流控制（暂停）帧中*/
    
    union
    {
        volatile uint32_t MACA1HR;          /*<MAC地址1高位寄存器可保存站的第二个6字节MAC地址的高16位*/
        struct
        {
            volatile uint32_t maca1h    :16;    /*<此字段包含6字节MAC地址1的高16位(47:32)，MAC使用此字段过滤所接收的帧以及将
                                                MAC地址插入到发送流控制（暂停）帧中*/
            volatile uint32_t reserved1 :8;     
            volatile uint32_t mbc       :6;     /*<这些位是用于比较每个MAC地址1字节的屏蔽控制位。当将它们设为高电平时，MAC内核
                                                不会将所接收到的DA/SA的相应字节与MAC地址1寄存器的内容进行比较。每个位都用于
                                                控制字节的屏蔽，如下所示：
                                                -位29：ETH_MACA1HR[15:8]
                                                -位28：ETH_MACA1HR[7:0]
                                                -位27：ETH_MACA1LR[31:24]
                                                ...
                                                -位24：ETH_MACA1LR[7:0]*/
            volatile uint32_t sa        :1;     /*<1:将使用MAC地址1[47:0]与所接收帧的SA字段进行比较*/
            volatile uint32_t ae        :1;     /*<1：地址过滤器使用MAC地址1实现完美过滤。此位清零时，地址过滤器会忽略用于过滤的地址*/
        }MACA1HRbit;
        
    };
    volatile uint32_t MACA1LR;                  /*<此字段包含6字节MAC地址1的低32位，MAC使用此字段过滤所接收的帧以及将MAC
                                                地址插入到发送流控制（暂停）帧中*/

    union
    {
        volatile uint32_t MACA2HR;              /*<MAC地址2高位寄存器可保存站的第二个6字节MAC地址的高16位*/
        struct
        {
            volatile uint32_t maca2h    :16;    /*<此字段包含6字节MAC地址2的高16位(47:32)，MAC使用此字段过滤所接收的帧以及将
                                                MAC地址插入到发送流控制（暂停）帧中*/
            volatile uint32_t reserved1 :8; 
            volatile uint32_t mbc       :6;     /*<这些位是用于比较每个MAC地址1字节的屏蔽控制位。当将它们设为高电平时，MAC内核
                                                不会将所接收到的DA/SA的相应字节与MAC地址2寄存器的内容进行比较。每个位都用于
                                                控制字节的屏蔽，如下所示：
                                                -位29：ETH_MACA2HR[15:8]
                                                -位28：ETH_MACA2HR[7:0]
                                                -位27：ETH_MACA2LR[31:24]
                                                ...
                                                -位24：ETH_MACA2LR[7:0]*/
            volatile uint32_t sa        :1;     /*<1:将使用MAC地址2[47:0]与所接收帧的SA字段进行比较*/
            volatile uint32_t ae        :1;     /*<1：地址过滤器使用MAC地址2实现完美过滤。此位清零时，地址过滤器会忽略用于过滤的地址*/
                                                
        }MACA2HRbit;
        
    };
    volatile uint32_t MACA2LR;                  /*<此字段包含6字节MAC地址2的低32位，MAC使用此字段过滤所接收的帧以及将MAC
                                                地址插入到发送流控制（暂停）帧中*/

    union
    {
        volatile uint32_t MACA3HR;              /*<MAC地址3高位寄存器可保存站的第二个6字节MAC地址的高16位*/
        struct
        {
            volatile uint32_t maca3h    :16;    /*<此字段包含6字节MAC地址3的高16位(47:32)，MAC使用此字段过滤所接收的帧以及将
                                                MAC地址插入到发送流控制（暂停）帧中*/
            volatile uint32_t reserved1 :8; 
            volatile uint32_t mbc       :6;     /*<这些位是用于比较每个MAC地址1字节的屏蔽控制位。当将它们设为高电平时，MAC内核
                                                不会将所接收到的DA/SA的相应字节与MAC地址3寄存器的内容进行比较。每个位都用于
                                                控制字节的屏蔽，如下所示：
                                                -位29：ETH_MACA3HR[15:8]
                                                -位28：ETH_MACA3HR[7:0]
                                                -位27：ETH_MACA3LR[31:24]
                                                ...
                                                -位24：ETH_MACA3LR[7:0]*/
            volatile uint32_t sa        :1;     /*<1:将使用MAC地址3[47:0]与所接收帧的SA字段进行比较*/
            volatile uint32_t ae        :1;     /*<1：地址过滤器使用MAC地址3实现完美过滤。此位清零时，地址过滤器会忽略用于过滤的地址*/
                                                
        }MACA3HRbit;
        
    };
    volatile uint32_t MACA3LR;                  
                                                
}ETHMAC_TypeDef;

typedef struct
{
    union
    {
        volatile uint32_t MMCCR;
        struct
        {
            volatile uint32_t cr        :1;     /*<计数器复位，该位置位后，会在1个时钟周期后由硬件自动清零*/
            volatile uint32_t csr       :1;     /*<计数器停止回转，0：计数器在计数到最大值后，会重新置0开始计数*/
            volatile uint32_t ror       :1;     /*<0：读MSC计数器后，计数器不复位*/
            volatile uint32_t mcf       :1;     /*<1：冻结MSC计数器，保持它们的当前值，ROR位可在计数器冻结状态时工作*/
            volatile uint32_t mcp       :1;     /*<1：将MSC计数器预设为一个预设值，预设值取决于mcfhp*/
            volatile uint32_t mcfhp     :1;     /*<0:预设MMC计数器的值为近似半值(0x7FFFFFF0),1：预设MSC计数器的值为近似全值(0xFFFF FFF0)*/
            volatile uint32_t reserved1 :26;
        }MMCCRbit;
        
    };
    
    union
    {
        volatile    uint32_t MMCRIR;        /*<以太网MMC接收中断寄存器*/
        struct
        {
            volatile uint32_t reserved1 :5;
            volatile uint32_t rfces     :1;     /*<当存在CRC错误的接收帧计数器达到其最大值的一半时，该位置1*/
            volatile uint32_t rfaes     :1;     /*<当存在对齐错误的接收帧计数器达到其最大值的一半时，该位置1*/
            volatile uint32_t reserved2 :10;
            volatile uint32_t rgufs     :1;     /*<当接收到的良好单播帧计数器达到其最大值的一半时，该位置1*/
            volatile uint32_t reserved3 :14;
        }MMCRIRbit;
        
    };
    
    union
    {
        volatile uint32_t MMCTIR;           /*<以太网MMC发送中断寄存器*/
        struct
        {
            volatile uint32_t reserved1 :14;
            volatile uint32_t tgfscs    :1;     /*<单个冲突后发送的良好帧计数器达到其最大值的一半时，该位置1*/
            volatile uint32_t tgfmscs   :1;     /*<多个冲突后发送的良好帧计数器达到其最大值的一半时，该位置1*/
            volatile uint32_t reserved2 :5; 
            volatile uint32_t tgfs      :1;     /*<当发送的良好帧计数器达到其最大值的一半时，该位置1*/
            volatile uint32_t reserved3 :10;
        }MMCTIRbit;
    };
    
    union
    {
        volatile uint32_t MMCRIMR;          /*<以太网MMC接收中断屏蔽寄存器*/
        struct
        {
            volatile uint32_t reserved1 :5;     
            volatile uint32_t rfcem     :1;     /*<1：当存在CRC错误的接收帧计数器达到其最大值的一半时，会屏蔽中断*/
            volatile uint32_t rfaem     :1;     /*<1：当存在对齐错误的接收帧计数器达到其最大值的一半时，会屏蔽中断*/
            volatile uint32_t reserved2 :10;
            volatile uint32_t rgufm     :1;     /*<1：当接收到的良好单播帧计数器达到其最大值的一半时，会屏蔽中断*/
            volatile uint32_t reserved3 :14;        
        }MMCRIMRbit;
        
    };
    
    union
    {
        volatile uint32_t MMCTIMR;          /*<以太网MMC发送中断屏蔽寄存器*/
        struct
        {
            volatile uint32_t reserved1 :14;
            volatile uint32_t tgfscm    :1;     /*<1：当单个冲突后发送的良好帧计数器达到其最大值的一半时，会屏蔽中断*/
            volatile uint32_t tgfmscm   :1;     /*<1：当多个冲突后发送的良好帧计数器达到其最大值的一半时，会屏蔽中断*/
            volatile uint32_t reserved2 :5;
            volatile uint32_t tgfm      :1;     /*<1：当发送的良好帧计数器达到其最大值的一半时，会屏蔽中断*/
            volatile uint32_t reserved3 :10;
        }MMCTIMRbit;
    };

    volatile uint32_t reserved1[14];

    volatile uint32_t MMCTGFSCCR;               /*<以太网MMC在单个冲突后发送的良好帧计数器寄存器*/
    volatile uint32_t MMCTGFMSCCR;              /*<以太网MMC在多个冲突后发送的良好帧计数器寄存器*/
    volatile uint32_t reserved2[5];

    volatile uint32_t MMCTGFCR;                 /*<以太网MMC发送的良好帧计数器寄存器*/
    volatile uint32_t reserved3[10];

    volatile uint32_t MMCRFCECR;                /*<带有CRC错误计数器寄存器的以太网MMC接收帧*/
    volatile uint32_t MMCRFAECR;                /*<带有对齐错误计数器寄存器的以太网MMC接收帧*/

    volatile uint32_t reserved4[10];
    volatile uint32_t MMCRGUFCR;                /*<MMC接收的良好单播帧计数器寄存器*/

}ETHMMC_TypeDef;

typedef struct
{
    union
    {
        volatile uint32_t PTPTSCS;          /*<以太网PTP时间戳控制寄存器*/
        struct
        {
            volatile uint32_t tse       :1;     /*<时间戳使能*/
            volatile uint32_t tsfcu     :1;     /*<时间戳精密更新或粗略更新*/
            volatile uint32_t tssti     :1;     /*<时间戳系统时间初始化*/
            volatile uint32_t tsstu     :1;     /*<时间戳系统时间更新*/
            volatile uint32_t tsite     :1;     /*<时间戳中断触发使能*/
            volatile uint32_t ttsaru    :1;     /*<时间戳加数寄存器更新*/
            volatile uint32_t reserved1 :2;
            volatile uint32_t tssarfe   :1;     /*<所有接收帧的时间戳快照使能*/
            volatile uint32_t tsssr     :1;     /*<时间戳亚秒翻转：数字或二进制翻转控制*/
            volatile uint32_t tsptppsv2e:1;     /*<1：将使用版本2格式对PTP数据包进行监听
                                                0：将使用版本1格式式对PTP数据包进行监听*/
            volatile uint32_t tssptpoefe:1;     /*<1:将拍摄在以太网帧中也含有PTP消息(PTPoverEthernet)的帧的时间戳快
                                                    照。默认情况下，将拍摄UDP-IPEthernetPTP数据包的快照*/
            volatile uint32_t tssipv6fe :1;     /*<1:将拍摄IPv6帧的时间戳快照*/
            volatile uint32_t tssipv4fe :1;     /*<1:将拍摄IPv4帧的时间戳快照*/
            volatile uint32_t tsseme    :1;     /*<1:仅拍摄事件消息的时间戳快照（SYNC、Delay_Re、Pdelay_Req、Pdelay_Resp）
                                                0：将拍摄除Announce、Management、Signaling以外其它所有消息的快照*/
            volatile uint32_t tssmrme   :1;     /*<1:仅拍摄主节点相关消息的快照
                                                    0：仅拍摄从节点相关消息的快照。这仅适用于普通时钟和边界时钟节点*/
            volatile uint32_t tscnt     :2;     /*<时间戳时钟节点类型，00：普通时钟，01：边界时钟，10：端对端透明时钟,11：点对点透明时钟*/
            volatile uint32_t tspffmae  :1;     /*<1:当PTP直接通过以太网发送时，此位将使用MAC地址(除MAC地址0)来过滤PTP帧*/
            volatile uint32_t reserved2 :13;
        }PTPSCSbit;
    };

    volatile uint32_t PTPSSIR;                  /*<系统时间亚秒增量,此寄存器中编程的值在每次更新时都会被增加到系统时间亚秒值的内容
                                                例如，要得到20ns的精度，该值为20/0.467=~43（或0x2A）*/
    volatile uint32_t PTPTSHR;                  /*<字段中的值表示由内核维持的以秒为单位的系统时间当前值*/
    
    union
    {
        volatile uint32_t PTPTSLR;
        struct
        {
            volatile uint32_t stss      :31;    /*<该字段中的值包含亚秒时间表示，精度为0.46ns*/
            volatile uint32_t stpns     :1;     /*<该位指示正负时间,通常为零*/
        }PTPTSLRbit;
    };
    
    volatile uint32_t PTPTSHUR;                 /*<该字段中的值指示要初始化或增加到系统时间中的时间，单位为秒*/
    union
    {
        volatile uint32_t PTPTSLUR;
        struct
        {
            volatile uint32_t tsuss     :31;    /*<该字段中的值指示要初始化或增加到系统时间中的亚秒时间*/
            volatile uint32_t tsupns    :1;     /*<该位指示正负时间值，1：该位指示时间表示为负值，0：该位指示时间表示为正
                                                值。当TSSTI=1（系统时间初始化）时，该位应为零值
                                                如果当TSSTU=1时该位也=1，则时间戳更新寄存器中的值要从系统时间中减去。否则，它要增加到系统时间中*/
        }PTPTSLURbit;
    };
    
    volatile uint32_t PTPTSAR;                  /*<该寄存器由软件用来重新线性调节时钟频率，使其与主时钟频率匹配。仅当系统时间配置为
                                                微调更新模式ETH_PTPTSCR中的TSFCU位）时使用该寄存器*/

    volatile uint32_t PTPTTHR;                  /*<该寄存器包含要与用于中断事件生成的系统时间进行比较的32位时间。目标时间高位寄
                                                存器与目标时间低位寄存器一起，用于在系统时间超过这些寄存器中编程的值时规划中断事件
                                                （ETH_PTPTSCR中的TSARU位）*/
    volatile uint32_t PTPTTLR;                  /*<该寄存器包含要与用于中断事件生成的系统时间进行比较的32位时间*/

    volatile uint32_t reserved1;

    union
    {
        volatile uint32_t PTPTSSR;
        struct
        {
            volatile uint32_t tsso      :1;     /*<1：该位指示系统时间值大于或等于在目标时间高位和低位寄存器中指定的值*/
            volatile uint32_t tsttr     :1;     /*<1：该位指示时间戳的秒值已上溢，超过0xFFFFFFFF*/
            volatile uint32_t reserved1 :30;
        }PTPTSSRbit;
    };
    
    volatile uint32_t PTPPPSCR;         /*<PPS 频率选择,PPS输出频率设置为2^(PPSFREQ)Hz,*/
}ETHPTP_TypeDef;

typedef struct
{
    union
    {
        volatile uint32_t DMABMR;           /*以太网DMA总线模式寄存器*/
        struct
        {
            volatile uint32_t sr        :1;     /*<软件复位，当该位为1时，MACDMA控制器会复位所有MAC子系统的内部寄存器和逻辑。在所有内
                                                核时钟域完成复位操作后，该位自动清零。重新编程任何内核寄存器之前，在该位中读取0*/
            volatile uint32_t da        :1;     /*<DMA仲裁0：循环调度，Rx:Tx优先级比在位[15:14]中给出，1：Rx优先于Tx*/
            volatile uint32_t dsl       :5;     /*<该位指定两个未链接描述符之间跳过的字数。地址从当前描述符结束处开始跳到下一个描述
                                                符起始处。当DSL值等于零时，在环形模式下DMA会将描述符表视为连续的*/
#if STM32
            volatile uint32_t edfe      :1;     /*<增强描述符格式使能*/
#else
            volatile uint32_t reserved2 :1;
#endif /*STM32*/
            volatile uint32_t pbl       :6;     /*<基本同rpd位，*/
            volatile uint32_t pm        :2;     /*<RxDMA请求优先于TxDMA请求，优先级比如下：
                                                00:1:1
                                                01:2:1
                                                10:3:1
                                                11:4:1
                                                这仅在DA位清零时有效*/
            volatile uint32_t fb        :1;     /*<固定突发,该位控制AHB主接口是否执行固定突发传输
                                                1：AHB在正常突发传输开始期间仅使用SINGLE、INCR4、INCR8、INCR16
                                                0：AHB使用SINGLE、INCR突发传输操作*/
            volatile uint32_t rdp       :6;     /*<这些位指示要在一个RxDMA事务中传输的最大节拍数。这是在单个块读/写操作中使用的最
                                                大值，RxDMA每次在主机总线上开始突发传输时，始终尝试按RDP中指定的方式进行突发
                                                允许使用1,2,4,8,16,32对RDP进行编程。任何其它值都会产生未定义的行为，
                                                仅在USP设置为高电平时这些位才有效且适用*/
            volatile uint32_t usp       :1;     /*<1：配置RxDMA，将位[22:17]中配置的值用于PBL，而位[13:8]中的PBL值仅适用于TxDMA操作
                                                    0：位[13:8]中的PBL值同时适用于两个DMA引擎*/
            volatile uint32_t fpm       :1;     /*<1：该位会将编程的PBL值（位[22:17]和位[13:8]）乘以四倍
                                                因此，DMA根据PBL值以最高4、8、16、32、128个节拍传输数*/
            volatile uint32_t aab       :1;     /*<地址对齐的节拍，当该位设置为高电平并且FB位等于1时，AHB接口会生成与起始地址LS 位对齐的所有突
                                                发。如果FB位等于0，则第一个突发（访问数据缓冲器的起始地址）不对齐，但后续的突发与地址对齐*/
            volatile uint32_t mb        :1;     /*<混合突发,该位置为高电平且FB位置为低电平时，AHB主接口将以INCR（未定义突发）启动所有长
                                                度大于16的突发传输。该位清零时，对于长度等于或小于16的突发，将恢复为固定突发传输（INCRx和SINGLE）*/
            volatile uint32_t reserved1 :5;
        }DMABMRbit;
    };
    
    volatile uint32_t DMATPDR;                  /*<向这些位写入任何值时，DMA都会读取ETH_DMACHTDR寄存器指向的当前描述符
                                                如该描述符不可用（由主机所有），则发送会返回到挂起状态，并将ETH_DMASR寄存器位2
                                                进行置位。如果该描述符可用，则发送会继续进行*/
    volatile uint32_t DMARPDR;                  /*<向这些位写入任何值时，DMA都会读取ETH_DMACHRDR寄存器指向的当前描述符
                                                如该描述符不可用（由主机所有），则接收会返回到挂起状态，且不会将ETH_DMASR寄存
                                                器位7进行置位。如果该描述符可用，接收DMA将返回到活动状态*/
    volatile uint32_t DMARDLAR;                 /*<此字段包含接收描述符列表中的首个描述符的基址，DMA会在内部将LSB位[1/2/3:0]（对
                                                应于32/64/128位的总线宽度）忽略，并将其值均视为零。因此，这些LSB位为只读*/
    volatile uint32_t DMATDLAR;                 /*<此字段包含发送描述符列表中的首个描述符的基址，DMA会在内部将LSB位[1/2/3:0]（对
                                                应于32/64/128位的总线宽度）忽略，并将其值均视为零。因此，这些LSB位为只读*/
    union
    {
        volatile uint32_t DMASR;
        struct
        {
            volatile uint32_t ts        :1;     /*<发送状态*/
            volatile uint32_t tpss      :1;     /*<发送过程停止状态*/
            volatile uint32_t tbus      :1;     /*<发送缓冲区不可用状态*/
            volatile uint32_t tjts      :1;     /*<发送jabber超时状态*/
            volatile uint32_t ros       :1;     /*<接收上溢状态*/
            volatile uint32_t tus       :1;     /*<发送下溢状态*/
            volatile uint32_t rs        :1;     /*<接收状态*/
            volatile uint32_t rbus      :1;     /*<接收缓冲区不可用状态*/
            volatile uint32_t rpss      :1;     /*<接收过程停止状态*/
            volatile uint32_t pwts      :1;     /*<接收看门狗超时状态*/
            volatile uint32_t est       :1;     /*<提前发送状态*/
            volatile uint32_t reserved1 :2;
            volatile uint32_t fbes      :1;     /*<致命总线错误状态*/
            volatile uint32_t ers       :1;     /*<提前接收状态*/
            volatile uint32_t ais       :1;     /*<异常中断汇总*/
            volatile uint32_t nis       :1;     /*<正常中断汇总*/
            volatile uint32_t rps       :3;     /*<这些位指示接收DMAFSM的状态*/
            volatile uint32_t tps       :3;     /*<这些位指示发送DMAFSM的状态*/
            volatile uint32_t ebs       :3;     /*<这些位指示导致总线错误（AHB接口上的错误响应）的错误类型。仅在致命总线错误
                                                （ETH_DMASR寄存位[13]）置1时有效。此字段不会产生中断
                                                位23 1   TxDMA传输数据时出错(Error during data transfer by TxDMA)
                                                        0   RxDMA传输数据时出错(Error during data transfer by RxDMA)
                                                位24 1   读取传输时出错(Error during read transfer)
                                                        0   写入传输时出错(Erro rduring write transfer)
                                                位25 1   访问描述符时出错(Error during descriptor access)
                                                        0   访问数据缓冲区时出错(Error during data buffer access)*/
            volatile uint32_t reserved2 :1;
            volatile uint32_t mmcs      :1;     /*<此位反映MAC内核的MMC中发生的事件。软件必须读取MAC内核中对应的寄存器，以获
                                                取产生中断的具体原因，然后将中断源清零，才能将此位置0。当此位处于高电平时，使能
                                                后会产生中断*/
            volatile uint32_t pmts      :1;     /*<此位指示MAC内核的PMT中发生的事件。软件必须读取MAC内核中对应的寄存器，以获
                                                取产生中断的具体原因，然后将其源清零，才能将此位复位为0。当此位处于高电平时，使
                                                能后会产生中断*/
            volatile uint32_t tsts      :1;     /*<此位指示MAC内核的时间戳发生器块中发生的中断事件。软件必须读取MAC内核的状态寄
                                                存器，将其源（位9）清零，才能将此位复位为0。当此位处于高电平时，使能后会产生中断*/
            volatile uint32_t reserved3 :2;
        }DMASRbit;
    };
    
    union
    {
        volatile uint32_t DMAOMR;           /*<作为DMA初始化过程的一部分，应将ETH_DMAOMR寄存器作为最后的CSR进行写操作*/
        struct
        {
            volatile uint32_t reserved1 :1;
            volatile uint32_t sr        :1;     /*<启动/停止接收*/
            volatile uint32_t osf       :1;     /*<处理第二个帧，该位置1时会命令DMA处理第二个发送数据帧，即使尚未获得首个帧的状态*/
            volatile uint32_t rtc       :2;     /*<接收阈值控制*/
            volatile uint32_t resvered2 :1;
            volatile uint32_t fugf      :1;     /*<转发过小的好帧，1：RxFIFO会转发包含pad字节和CRC的过小帧（无错误但长度小于64字节的帧
                                                0：RxFIFO会丢弃所有不超过64字节的帧，除非因接收阈值下限更低（例如RTC=01）而导致此类帧已传输*/
            volatile uint32_t fef       :1;     /*<转发错误，1：除短错误帧之外的所有帧都会转发到DMA
                                                0：RxFIFO会丢弃带有错误状态（CRC错误、冲突错误、巨帧、看门狗超时、上
                                                溢）的帧。不过，如果某个帧的起始字节（写）指针已传输到读控制器端（阈值模式下），
                                                则不会丢弃该帧。如果ARI总线上未传输（输出）帧的起始字节，则RxFIFO会丢弃此错误*/
            volatile uint32_t reserved3 :5;
            volatile uint32_t st        :1;     /*<启动/停止发送*/
            volatile uint32_t ttc       :3;     /*<发送阈值控制，这三个位用于控制发送FIFO的阈值级别。当发送FIFO中的帧大小大于阈值时启动发送。此
                                                外，还会发送长度小于阈值的全帧。这些位只有在TSF位（位21）清零后才能使用
                                                000:64
                                                001:128
                                                010:192
                                                011:256
                                                100:40
                                                101:32
                                                110:24
                                                111:16*/
            volatile uint32_t reserved4 :3;
            volatile uint32_t ftf       :1;     /*<刷新发送FIFO*/
            volatile uint32_t tsf       :1;     /*<发送存储并转发,该位只有在已停止传输时才能更新
                                                1：如果发送FIFO中有一个完整帧，则发送会启动。会忽略由ETH_DMAOMR寄存器位[16:14]指定的TTC值
                                                0：ETH_DMAOMR寄存器位[16:14]指定的TTC值才会有效*/
            volatile uint32_t reserved5 :2;
            volatile uint32_t dfrf      :1;     /*<禁止刷新接收FIFO，1：RxDMA不会因为接收描述符/缓冲区不可用而刷新任何帧（通常情况下，
                                                此位清零时它会这样做*/
            volatile uint32_t rsf       :1;     /*<接收存储并转发，1：RxFIFO写入完整帧后，可从中读取一个帧，同时忽略RTC位
                                                0：RxFIFO在直通模式下工作，具体取决于RTC位指定的阈值*/
            volatile uint32_t dtcefd    :1;     /*<禁止丢弃TCP/IP校验和错误帧*/
            volatile uint32_t reserved6 :5;
        }DMAOMRbit;
    };
    
    union
    {
        volatile uint32_t DMAIER;
        struct
        {
            volatile uint32_t tie       :1;     /*<发送中断使能*/
            volatile uint32_t tpsie     :1;     /*<发送过程停止中断使能*/
            volatile uint32_t tbuie     :1;     /*<发送缓冲区不可用中断使能*/
            volatile uint32_t tjtie     :1;     /*<发送jabber超时中断使能*/
            volatile uint32_t roie      :1;     /*<上溢中断使能*/
            volatile uint32_t tuie      :1;     /*<下溢中断使能*/
            volatile uint32_t rie       :1;     /*<接收中断使能*/
            volatile uint32_t rbuie     :1;     /*<接收缓冲区不可用中断使能*/
            volatile uint32_t rpsie     :1;     /*<接收过程停止中断使能*/
            volatile uint32_t rwtie     :1;     /*<接收看门狗超时中断使能*/
            volatile uint32_t etie      :1;     /*<提前发送中断使能*/
            volatile uint32_t reserved1 :2;
            volatile uint32_t fbeie     :1;     /*<致命总线错误中断使能*/
            volatile uint32_t erie      :1;     /*<提前接收中断使能,当该位通过正常中断汇总使能位（ETH_DMAIER寄存位[16]）置1时，可使能提前接收中断
                                                该位清零时，会禁止提前接收中断*/
            volatile uint32_t aise      :1;     /*<异常中断汇总使能，1：会使能一个异常中断，0：会禁止一个异常中断。该位可使能以下位：
                                                -ETH_DMASR[1]：发送过程停止
                                                -ETH_DMASR[3]：发送jabber超时
                                                -ETH_DMASR[4]：接收上溢
                                                -ETH_DMASR[5]：发送下溢
                                                -ETH_DMASR[7]：接收缓冲区不可用
                                                -ETH_DMASR[8]：接收过程停止
                                                -ETH_DMASR[9]：接收看门狗超时
                                                -ETH_DMASR[10]：提前发送中断
                                                -ETH_DMASR[13]：致命总线错误*/
            volatile uint32_t nise      :1;     /*<正常中断汇总使能，1：会使能一个正常中断，0：会禁止一个正常中断。该位可使能以下位：
                                                -ETH_DMASR[0]：发送中断
                                                -ETH_DMASR[2]：发送缓冲区不可用
                                                -ETH_DMASR[6]：接收断
                                                -ETH_DMASR[14]：提前接收中断*/
            volatile uint32_t reserved2 :15;
        }DMAIERbit;
    };
    
    union
    {
        volatile uint32_t DMAMFBOCR;        
        struct
        {
            volatile uint32_t mfc       :16;    /*<控制器因主机接收缓冲区不可用而丢失的帧数*/
            volatile uint32_t omfc      :1;     /*<丢失帧计数器的上溢位*/
            volatile uint32_t mfa       :11;    /*<应用程序所丢失的帧*/
            volatile uint32_t ofoc      :1;     /*<FIFO上溢计数器的上溢*/
            volatile uint32_t reserved1 :3;
        }DMAFBOCRbit;
    };
    
    volatile uint32_t DMARSWTR;                 /*<接收状态(RS)看门狗定时器计数*/
    
    volatile uint32_t reserved1[8];
    
    volatile uint32_t DMACHTDR;                 /*<当前主机发送描述符寄存器会指向DMA所读取的当前发送描述符的起始地址*/
    volatile uint32_t DMACHRDR;                 /*<当前主机接收描述符寄存器会指向DMA所读取的当前接收描述符的起始地址*/
    volatile uint32_t DMACHTBAR;                /*<当前主机发送缓冲区地址寄存器会指向DMA所读取的当前发送缓冲区地址*/
    volatile uint32_t DMACHRBAR;                /*<当前主机接收缓冲区地址寄存器会指向DMA所读取的当前接收缓冲区地址*/
}ETHDMA_TypeDef;

/**
  * @brief  DMA描述符结构
  */
typedef struct  {
    union
    {
        uint32_t status;
        struct
        {
            uint32_t db         :1;     /*<1:MAC 在发送前因为监测到载波信号而推迟帧发送。该位只在半双工模式下有效*/
            uint32_t uf         :1;     /*<数据下溢错误*/
            uint32_t ed         :1;     /*<顺延过多,在以太网MAC配置寄存器(EMAC_MACCTRL)的DC位为1时，因为顺延超过24288 位时而结束发送*/
            uint32_t cc         :4;     /*<冲突计数，这4位值记录了帧发送出去前出现的冲突次数。在 EC位(TDES0[8])为1时，该位
                                            无效。这位仅在半双工模式下有效*/
            uint32_t vf         :1;     /*<VLAN帧，该位表明发送的帧是VLAN类型帧*/
            uint32_t ec         :1;     /*<冲突过多, 1:MAC 在尝试发送当前帧的过程中因为连续发生16词冲突而
                                        中止发送。如果以太网 MAC 配置寄存器(EMAC_MACCTRL),RD(不进行重发)
                                        为1，那么在发生第一次冲突后，该位就置为1，并中止发送*/
            uint32_t lc         :1;     /*<迟到冲突,1:帧因为在发送过程中在冲突检测窗口检测到冲突(MII 模式下，包
                                        括前导符64个字节时间)而中止发送。在下溢错误位置1的情况下该位无效*/
            uint32_t nc         :1;     /*<无载波，1:帧发送的过程中从 PHY 发过来的载波侦听信号没有置起*/
            uint32_t loc        :1;     /*<载波丢失,帧发送的过程中发生了载波丢失(MII_CRS 信号在发送过程中
                                        存在一个或多个以上发送时钟周期的无效状态)。该位只有在半双工模式下且发送
                                        帧没有冲突时有效*/
            uint32_t ipe        :1;     /*<IP 数据错误*/
            uint32_t ff         :1;     /*<帧清除，该位表明由于CPU发出帧清空命令，DMA或者MTL把帧FIFO 中清空*/
            uint32_t jt         :1;     /*<Jabber timeout,只在以太网MAC配置寄存
                                        (EMAC_MACCR)JD 位不为1时才会在发生Jabber timeout时被置1*/
            uint32_t es         :1;     /*<错误汇总*/
            uint32_t ihe        :1;     /*<IP 报头错误*/
            uint32_t ttss       :1;     /*<发送时间戳状态*/
            uint32_t reserved1  :2;
            uint32_t tch        :1;     /*<第二地址链表,TDES1中TBS2代表的是下一个描述符的地址，而不是第二个缓存
                                        的地址。TDES0[21]的功能优先于本位(TDES0[20])。该位只在FS位(TDES0[28])为1时才有效*/
            uint32_t ter        :1;     /*<环形发送结构*/
            uint32_t cic        :2;     /*<校验和插入控制
                                        00:不使能插入校验和功能
                                        01:仅使能IP报头的校验和计算和插入；
                                        10:使能IP报头和数据域的校验和计算和插入，但是不计算伪报头的校验和
                                        11:使能IP报头和数据域的校验和计算和插入，同时也计算伪报头的校验和*/
            uint32_t reserved2  :1;
            uint32_t ttse       :1;     /*<发送时间戳使能,只在TSE位(EMAC_PTPTSCTRL[0])且FS位(TDES0[28])为1时有效*/
            uint32_t dp         :1;     /*<0:MAC 对帧长不超过64字节的帧自动填充字节，而且无论DC位(TDES0[27])为何
                                        值MAC都会在帧结尾插入CRC数值。该位只在FS位(TDES0[28])为1时有效*/
            uint32_t dc         :1;     /*<不计算CRC,1:MAC不再在发送帧结束时插入CRC帧*/
            uint32_t fs         :1;     /*<1:表示当前描述符指向的缓存存放着帧的第一个分包*/
            uint32_t ls         :1;     /*<1:当前描述符指向的缓存存放着帧的最后一个分包，1:TDES1中TBS1或者TBS2的值不能为0*/
            uint32_t ic         :1;     /*<完成时中断，该位仅在LS位为1时有效*/
            uint32_t own        :1;     /*<占有位*/
        }TxDESCstatus;
        struct
        {
            uint32_t pce        :1;     /*<数据校验和错误*/
            uint32_t ce         :1;     /*<CRC 错误*/
            uint32_t dre        :1;     /*<Dribble 位错误，1:接收到的帧长度不是字节的整数倍，MII模式有效*/
            uint32_t re         :1;     /*<接收错误*/
            uint32_t rwt        :1;     /*<接收看门狗超时*/
            uint32_t ft         :1;     /*<帧类型，1:以太网帧((LT域大于等于1536);0:IEEE802.3Q*/
            uint32_t lc         :1;     /*<迟到冲突,1:在半双工模式下接收帧的时候发生了迟到冲突*/
            uint32_t iphce      :1;     /*<IPv 报头校验和错误*/
            uint32_t ls         :1;     /*<最后一个描述符*/
            uint32_t fs         :1;     /*<第一个描述符*/
            uint32_t vlan       :1;     /*<VLAN标签*/
            uint32_t oe         :1;     /*<溢出错误*/
            uint32_t le         :1;     /*<长度错误,该位只有在RDES0[5]位为1才有效*/
            uint32_t saf        :1;     /*<源地址过滤器未通过*/
            uint32_t de         :1;     /*<描述符错误，该位表示由于描述符的缓存装不下当前接收帧，DMA 又不占有下一个
                                            描述符，导致当前帧被切断。该位只有在LS位(RDES0[8])位1时才有效*/
            uint32_t es         :1;     /*<错误汇总*/
            uint32_t fl         :14;    /*<帧长*/
            uint32_t afm        :1;     /*<目的地址过滤器未通过*/
            uint32_t own        :1;     /*<占有位*/
        }RxDESCstatus;
    };

    union
    {
        uint32_t controlsize;           /*!< control and buffer1, buffer2 lengths */
        struct
        {
            uint32_t tbs1       :13;    /*<发送缓存1小,如果它的值是0，那么DMA跳过这个缓存，根据TDES0[20]位配置使用缓存2或者下一个缓存*/
            uint32_t reserved1  :3;
            uint32_t tbs2       :13;    /*<发送缓存2大小,如果TDES0[20]位为1时，这些位表示第二个描述符的地址*/
            uint32_t reserved2  :3; 
        }TxDESCConrtolSize;
        struct
        {
            uint32_t rbs1       :13;    /*<接收缓存1大小*/
            uint32_t reserved1  :1;
            uint32_t rch        :1;     /*<第二地址链表*/
            uint32_t rer        :1;     /*<接收描述符环形结构结构*/
            uint32_t rbs2       :13;    /*<接收缓存2大小*/
            uint32_t reserved2  :2;
            uint32_t dic        :1;     /*<关闭接收完成中断*/
        }RxDESCConrtolSize;
    };
    uint32_t buf1addr;              /*!< buffer1 address pointer */
    uint32_t buf2nextdescaddr;      /*!< buffer2 or next descriptor address pointer */

#if STM32
    uint32_t reserved1;
    uint32_t reserved2;
    uint32_t ttsl;
    uint32_t ttsh;
#endif /*STM32*/

} ETH_DMADESC_TypeDef;


/** @defgroup ETH_Inter_Frame_Gap ETH Inter Frame Gap
  * @{
  */
typedef enum
{
    ETH_INTERFRAMEGAP_96BIT = 0,
    ETH_INTERFRAMEGAP_88BIT,
    ETH_INTERFRAMEGAP_80BIT,
    ETH_INTERFRAMEGAP_72BIT,
    ETH_INTERFRAMEGAP_64BIT,
    ETH_INTERFRAMEGAP_56BIT,
    ETH_INTERFRAMEGAP_48BIT,
    ETH_INTERFRAMEGAP_40BIT
}ETH_INTERFRAMEGAP_TypeDef;

/** @defgroup ETH_Back_Off_Limit ETH Back Off Limit
  * @{
  */
typedef enum
{
    ETH_BACKOFFLIMIT_10 = 0,
    ETH_BACKOFFLIMIT_8,
    ETH_BACKOFFLIMIT_4,
    ETH_BACKOFFLIMIT_1
}ETH_BACKOFFLIMIT_TypeDef;

/** @defgroup PassControlFrames ETH Pass Control Frames
 *  @{
 */
typedef enum 
{
    PreventAll = 0,
    PreventPausePassOther,
    PassAll,
    PreventAddressFault
}PassControlFrames_TypeDef;

/** @defgroup ETH_Pause_Low_Threshold ETH Pause Low Threshold
  * @{
  */
typedef enum
{
    ETH_PAUSELOWTHRESHOLD_MINUS4 = 0,           /*!< Pause time minus 4 slot times */
    ETH_PAUSELOWTHRESHOLD_MINUS28,              /*!< Pause time minus 28 slot times */
    ETH_PAUSELOWTHRESHOLD_MINUS144,             /*!< Pause time minus 144 slot times */
    ETH_PAUSELOWTHRESHOLD_MINUS256              /*!< Pause time minus 256 slot times */
}ETH_PAUSELOWTHRESHOLD;

/** @defgroup DMAPBL
 *  @{
 */
typedef enum
{
    DMAPBL_1 = 1,
    DMAPBL_2 = 2,
    DMAPBL_4 = 4,
    DMAPBL_8 = 8,
    DMAPBL_16 = 16,
    DMAPBL_32 = 32
}DMAPBL_typeDef;

/** @defgroup DMA Rx/Tx Priority Ratio
 *  @{
 */
typedef enum
{
    RxDMAreq_1_TxDMAreq_1 = 0,
    RxDMAreq_2_TxDMAreq_1,
    RxDMAreq_3_TxDMAreq_1,
    RxDMAreq_4_TxDMAreq_1
}Rx_Tx_PriorityRatioType;


/** @defgroup EMAC_smi_clock_border_definition
  * @brief emac smi clock border
  * @{
  */
#define MAC_HCLK_BORDER_20MHZ           (20000000)   /*!< hclk boarder of 20 mhz */
#define MAC_HCLK_BORDER_35MHZ           (35000000)   /*!< hclk boarder of 35 mhz */
#define MAC_HCLK_BORDER_60MHZ           (60000000)   /*!< hclk boarder of 60 mhz */
#define MAC_HCLK_BORDER_100MHZ          (100000000)  /*!< hclk boarder of 100 mhz */
#define MAC_HCLK_BORDER_150MHZ          (150000000)  /*!< hclk boarder of 150 mhz */
#define MAC_HCLK_BORDER_250MHZ          (250000000)  /*!< hclk boarder of 250 mhz */
#define MAC_HCLK_BORDER_288MHZ          (288000000)  /*!< hclk boarder of 288 mhz */

/**
  * @brief  mdc clock type
  */
typedef enum
{
  MAC_SMI_CLK_60_TO_100             = 0x00, /*!< mdc is hclk/42 */
  MAC_SMI_CLK_100_TO_150            = 0x01, /*!< mdc is hclk/62 */
  MAC_SMI_CLK_20_TO_35              = 0x02, /*!< mdc is hclk/16 */
  MAC_SMI_CLK_35_TO_60              = 0x03, /*!< mdc is hclk/26 */
  MAC_SMI_CLK_150_TO_250            = 0x04, /*!< mdc is hclk/102 */
  MAC_SMI_CLK_250_TO_288            = 0x05  /*!< mdc is hclk/102 */
} MAC_SMI_CLK_TypeDef;

/**
  * @brief  dma tx rx type
  */
typedef enum
{
  ETH_DMA_TRANSMIT                      = 0x00, /*!< transmit dma */
  ETH_DMA_RECEIVE                       = 0x01  /*!< receive dma */
} ETH_DMA_tx_rx_TypeDef;

/** @defgroup ETH_DMA_Tx_descriptor_Checksum_Insertion_Control ETH DMA Tx descriptor Checksum Insertion Control
  * @{
  */
typedef enum
{
    ETH_DMATXDESC_CHECKSUMBYPASS = 0,
    ETH_DMATXDESC_CHECKSUMIPV4HEADER,
    ETH_DMATXDESC_CHECKSUMTCPUDPICMPSEGMENT,
    ETH_DMATXDESC_CHECKSUMTCPUDPICMPFULL
}ETH_DMATXDESC_CHECKSUM_TypeDef;

typedef enum
{
    disable = 0,
    enable
}config_stateTypeDef;

typedef enum
{
    error = 0,
    success
}ETH_error_status;

typedef struct{
    uint32_t length;
    uint8_t *buffer;
    uint32_t SegCount;
    ETH_DMADESC_TypeDef *FSdescriptor;
    ETH_DMADESC_TypeDef *LSdescriptor;
}FrameTypeDef;

void ETH_MAC_Speed_Duplex(bool speed, bool duplex);
void ETH_Start(void);
void ETH_Stop(void);
uint8_t SMI_PHY_Register_Write(uint8_t PHY_address,uint8_t reg,uint16_t data);
uint8_t SMI_PHY_Register_Read(uint8_t PHY_address,uint8_t reg,uint16_t *data);
bool SMI_PHY_Register_RW(bool rdInstruct,uint8_t PHY_address,uint8_t reg,uint16_t *rdData,uint32_t rdDataLen);
FrameTypeDef ETH_GetReceivedFrame_IT(void);
ETH_error_status ETH_TransmitFrame(uint16_t FrameLength);
void ETH_DMA_DescriptorsListInit(ETH_DMA_tx_rx_TypeDef ETH_DMA_tx_rx,ETH_DMADESC_TypeDef *ETH_DMA_Descriptors ,uint8_t *buff, uint32_t buffer_count);
ETH_error_status ETH_Init(uint8_t *MACAddr,bool speed,bool duplex,uint32_t SysCoreClock,void (*ETH_MspInit)(void));

void ETH_Delayms(uint32_t ms);
#endif /*__MAC_H*/

