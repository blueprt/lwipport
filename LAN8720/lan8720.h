#ifndef __LAN8720_H
#define __LAN8720_H

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    BCR = 0,
    BSR,
    ID1,
    ID2,
    ANAR,
    ANLPAR,
    MCSR = 17,
    SMR,
    SECNR = 26,
    CSIR,
    ISR = 29,
    IMR,
    SCSR
}LAN8720_RegDef;

typedef struct lan8720_Memdata
{
    union
    {
        uint16_t BCR;
        struct
        {
            uint16_t reserved1          :8;
            uint16_t Duplex_Mod_def     :1;
            uint16_t Restart_AN         :1;
            uint16_t Isolate            :1;
            uint16_t power_Down         :1;
            uint16_t AN_En              :1;
            uint16_t Speed_def          :1;
            uint16_t Loopback           :1;
            uint16_t Soft_Reset         :1;
        }BCR_bit;
    };
    
    union
    {
        uint16_t BSR;
        struct
        {
            uint16_t Extend_Cap         :1;
            uint16_t Jabber_Detect      :1;
            uint16_t Link_Status        :1;
            uint16_t AN_Ability         :1;
            uint16_t Remote_Fault       :1;
            uint16_t AN_Done            :1;
            uint16_t reserved1          :5;
            uint16_t _10BT_Half_Duplex  :1;
            uint16_t _10BT_Full_Duplex  :1;
            uint16_t _100BT_Half_Duplex :1;
            uint16_t _100BT_Full_Duplex :1;
            uint16_t _100BT             :1;
        }BSR_bit;
    };
    
    uint16_t Id1;

    union
    {
        uint16_t id2;
        struct 
        {
            uint16_t revision_num       :4;
            uint16_t Model_num          :6;
            uint16_t id_19th_24th       :6;
        }id2_bit;
    };
    
    union
    {
        uint16_t AN_Adv_R;
        struct
        {
            uint16_t Field_sele         :5;
            uint16_t _10BT              :1;
            uint16_t _10BT_Full_Duplex  :1;
            uint16_t _100BT             :1;
            uint16_t _100BT_Full_Duplex :1;
            uint16_t reserved3          :1;
            uint16_t pause_operation    :2;
            uint16_t reserved2          :1;
            uint16_t Remote_Fault       :1;
            uint16_t reserved1          :2;
        }AN_Adv_R_bit;
    };
    
    union
    {
        uint16_t AN_Link_Partner_Ablity;
        struct
        {
            uint16_t Field_sele         :5;
            uint16_t _10BT              :1;
            uint16_t _10BT_Full_Duplex  :1;
            uint16_t _100BT             :1;
            uint16_t _100BT_Full_Duplex :1;
            uint16_t _100BT_T4          :1;
            uint16_t pause_operation    :1;
            uint16_t reserved1          :2;
            uint16_t Remote_Fault       :1;
            uint16_t Ack                :1;
            uint16_t Next_Page          :1;
        }AN_Link_Partner_Ablity_bit;
    };
    
    union
    {
        uint16_t AN_Ex_R;
        struct
        {
            uint16_t Link_Partner_AN    :1;
            uint16_t Page_Received      :1;
            uint16_t Next_Page_Able     :1;
            uint16_t Link_Partner_NP    :1;
            uint16_t parallel_det_Fault :1;
            uint16_t reserved1          :11;
        }AN_Ex_R_bit;
    };
    
    union
    {
        uint16_t Mode_CSR;
        struct
        {
            uint16_t reserved5          :1;
            uint16_t ENERGYON           :1;
            uint16_t reserved4          :4;
            uint16_t ALT_Interrupt_En   :1;
            uint16_t reserved3          :2;
            uint16_t FAR_loopback       :1;
            uint16_t reserved2          :2;
            uint16_t EDPWR_Down         :1;
            uint16_t reserved1          :2;
        }Mode_CSR_bit;
    };

    union
    {
        uint16_t SMode_R;
        struct
        {
            uint16_t PHY_Addr           :5;
            uint16_t Mode               :3;
            uint16_t reserved2          :6;
            uint16_t write_only_1       :1;
            uint16_t reserved1          :1;
        }SMode_R_bit;
    };
    
    uint16_t Sym_Err_CNT;

    union
    {
        uint16_t SCS_IR;
        struct
        {
            uint16_t reserved3          :4;
            uint16_t XPOL               :1;
            uint16_t reserved2          :8;
            uint16_t CH_Sele            :1;
            uint16_t reserved1          :1;
            uint16_t Auto_MDIX_Ctl      :1;
        }SCS_IR_bit;
    };
    
    union
    {
        uint16_t Interrupt_SRC_Flag;
        struct
        {
            uint16_t reserved2          :1;
            uint16_t AN_Page_Received   :1;
            uint16_t Par_Det_Fault      :1;
            uint16_t AN_LP_Ack          :1;
            uint16_t Link_Down          :1;
            uint16_t Remote_Fault_Dete  :1;
            uint16_t AN_Done            :1;
            uint16_t ENERGYON_Flag      :1;
            uint16_t reserved1          :8;
        }Interrupt_SRC_Flag_bit;
    };
    
    union
    {
        uint16_t Interrupt_SRC_En;
        struct
        {
            uint16_t reserved2          :1;
            uint16_t AN_Page_Received_En    :1;
            uint16_t Par_Det_Fault_En   :1;
            uint16_t AN_LP_Ack_En       :1;
            uint16_t Link_Down_En       :1;
            uint16_t Remote_Fault_Dete_En   :1;
            uint16_t AN_Done_En         :1;
            uint16_t ENERGYON_Flag_En   :1;
            uint16_t reserved1          :8;
            
        }Interrupt_SRC_En_bit;
    };

    union
    {
        uint16_t SCSR;
        struct
        {
            uint16_t reserved3          :2;
            uint16_t Speed_Duplex       :3;     /*!<001 = 10BASE-T half-duplex
                                                101 = 10BASE-T full-duplex
                                                010 = 100BASE-TX half-duplex
                                                110 = 100BASE-TX full-duplex*/
            uint16_t reserved2          :7;
            uint16_t AN_Done            :1;
            uint16_t reserved1          :3;
            

        }SCSR_bit;
    };
}lan8720_Memdata_def;

typedef enum
{
    lan8720_Write = 0,
    lan8720_Read
}lan8720_wrcode;

typedef struct lan8720
{
    uint16_t PHY_Addr;
    lan8720_Memdata_def Lan8720_Memdata;

    uint8_t (*hw_reset)(void);
    uint8_t (*hw_w)(uint8_t phy_addr,uint8_t reg_addr,uint16_t data);
    uint8_t (*hw_r)(uint8_t phy_addr,uint8_t reg_addr,uint16_t *data);
    
    
    uint8_t (*Restart_AN)(struct lan8720 *lan8720,bool *speed,bool *duplex);
    uint8_t (*soft_reset)(struct lan8720 *lan8720);
    uint8_t (*get_link_status)(struct lan8720 *lan8720,bool *status);
}lan8720_def;

void lan8720(struct lan8720 *lan8720,\
            uint16_t PHY_Addr,\
            uint8_t (*hw_reset)(void),\
            uint8_t (*hw_w)(uint8_t phy_addr,uint8_t reg_addr,uint16_t data),\
            uint8_t (*hw_r)(uint8_t phy_addr,uint8_t reg_addr,uint16_t *data));

uint8_t lan8720_soft_reset(struct lan8720 *lan8720);
uint8_t lan8720_Restart_AN(struct lan8720 *lan8720,bool *speed,bool *duplex);
uint8_t lan8720_get_link_status(struct lan8720 *lan8720,bool *status);
#endif // !__LAN8720_H


