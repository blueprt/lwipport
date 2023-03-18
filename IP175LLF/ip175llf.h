#ifndef __IP175LLF_H
#define __IP175LLF_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "IP175LLF_reg.h"

typedef struct IP175LLF
{
    uint32_t IP175LLF_OUI_ID;
    uint8_t IP175LLF_ID;
    uint8_t IP175LLF_Revision;
    uint8_t IP175LLF_Manu;
    uint16_t IP175LLF_ChipID;
    
    bool (*hw_rw)(bool rdInstruct,uint8_t PHY_addr,uint8_t reg_addr,uint16_t *rdData,uint32_t rdLen);
    void (*hw_init)(void);
    void (*hw_reset)(void);
}IP175LLF_Def;

#define IP175LLF_Debug(format,...) printf("File: "__FILE__", Line: %05d: "format"/n", __LINE__, ##__VA_ARGS__)
#define IP175LLF_Error(format,...) printf("File: "__FILE__", Line: %05d: "format"/n", __LINE__, ##__VA_ARGS__)

bool IP175LLF_Init( IP175LLF_Def *IP175LLF, 
                    bool (*hw_rw)(bool rdInstruct,uint8_t PHY_addr,uint8_t reg_addr,uint16_t *rdData,uint32_t rdLen),
                    void (*hw_init)(void),
                    void (*hw_reset)(void));

void IP175LLF_SoftwareReset(IP175LLF_Def *IP175LLF);
void IP175LLF_PortReset(IP175LLF_Def *IP175LLF,IPLLF_PHYID PHY_Portx);
void IP175LLF_PortPowerDown(IP175LLF_Def *IP175LLF,IPLLF_PHYID PHY_Portx,bool Enable);

bool IP175LLF_ReadPHYSpeedDuplexStatus(IP175LLF_Def *IP175LLF,IPLLF_PHYID PHY_Portx,bool *Speed,bool *Duplex);
bool IP175LLF_SetPHYSpeedDuplex(IP175LLF_Def *IP175LLF,IPLLF_PHYID PHY_Portx,bool Speed,bool Duplex);
bool IP175LLF_GetLinkStatus(IP175LLF_Def *IP175LLF,IPLLF_PHYID PHY_Portx);
void IP175LLF_NwayEn(IP175LLF_Def *IP175LLF,IPLLF_PHYID PHY_Portx,bool status);
bool IP175LLF_NwayReset(IP175LLF_Def *IP175LLF,IPLLF_PHYID PHY_Portx);

void IP175LLF_SetPort5Par(IP175LLF_Def *IP175LLF,bool WorkMode,bool InterfaceMode);
void IP175LLF_SetLEDMode(IP175LLF_Def *IP175LLF,uint8_t mode);

void IP175LLF_SetQOS_TxSpecialTag(IP175LLF_Def *IP175LLF,bool Enalbe);
void IP175LLF_SetQOS_LP_Over_DSCP(IP175LLF_Def *IP175LLF,bool Enalbe);
void IP175LLF_SetQOS_TOS_Over_VLAN_Prio(IP175LLF_Def *IP175LLF,bool Enalbe);
void IP175LLF_SetQOS_COSEn(IP175LLF_Def *IP175LLF,uint8_t portn,bool Enalbe);
void IP175LLF_SetQOS_QueueScheduling(IP175LLF_Def *IP175LLF,uint8_t portn,uint8_t mode);
void IP175_SetQOS_QueueSchWFR(IP175LLF_Def *IP175LLF,uint8_t Queue,uint8_t Weight);
void IP175LLF_SetQOS_VLANPrioMap(IP175LLF_Def *IP175LLF,uint8_t VLANPrio,uint8_t Queue);
void IP175LLF_SetQOS_PortPrioMap(IP175LLF_Def *IP175LLF,uint8_t PortPrio,uint8_t Queue);
void IP175LLF_SetQOS_DSCPMap(IP175LLF_Def *IP175LLF,uint8_t DSCPPrio,uint8_t Queue);
void IP175LLF_SetQOS_LPPrioMode(IP175LLF_Def *IP175LLF,uint8_t Mode);
void IP175LLF_SetQOS_RangeLP_En(IP175LLF_Def *IP175LLF,uint8_t Range,bool Range_En);
void IP175LLF_SetQOS_LP_En(IP175LLF_Def *IP175LLF,uint8_t LogicPort,bool LogicPort_En);
void IP175LLF_SetQOS_RangeLogicPort(IP175LLF_Def *IP175LLF,uint8_t Range,uint16_t RangeLogicPortLow,uint16_t RangeLogicPortHigh);
void IP175LLF_SetQOS_LogicPort(IP175LLF_Def *IP175LLF,uint8_t LogicPort,uint16_t LogicPortValue);
void IP175LLF_SetQOS_RangeLPPrioMap(IP175LLF_Def *IP175LLF,uint8_t Range,uint8_t Queue);
void IP175LLF_SetQOS_LogicPortPrioMap(IP175LLF_Def *IP175LLF,uint8_t LogicPort,uint8_t Queue);
void IP175LLF_SetQOS_RangeDrop(IP175LLF_Def *IP175LLF,uint8_t Range,bool Range_En);
void IP175LLF_SetQOS_LogicPortDrop(IP175LLF_Def *IP175LLF,uint8_t LogicPort,bool LogicPort_En);

#endif /*__IP175LLF_H*/

