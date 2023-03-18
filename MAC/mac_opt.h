#ifndef __MAC_OPT_H
#define __MAC_OPT_H

#include "mac.h"

#define ETHMAC      ((ETHMAC_TypeDef *)0x40028000)
#define ETHMMC      ((ETHMMC_TypeDef *)0x40028100)
#define ETHPTP      ((ETHPTP_TypeDef *)0x40028700)
#define ETHDMA      ((ETHDMA_TypeDef *)0x40029000)

#define AT32F437    1

#define PHY_TIMEOUT   (0x0000ffff)

/** @defgroup ETH_Buffers_setting ETH Buffers setting
  * @{
  */
#define ETH_MAX_PACKET_SIZE     ((uint32_t)1524U)   /*!< ETH_HEADER + ETH_EXTRA + ETH_VLAN_TAG + ETH_MAX_ETH_PAYLOAD + ETH_CRC */
#define ETH_HEADER          ((uint32_t)14U)     /*!< 6 byte Dest addr, 6 byte Src addr, 2 byte length/type */
#define ETH_CRC           ((uint32_t)4U)      /*!< Ethernet CRC */
#define ETH_EXTRA         ((uint32_t)2U)      /*!< Extra bytes in some cases */
#define ETH_VLAN_TAG        ((uint32_t)4U)      /*!< optional 802.1q VLAN Tag */
#define ETH_MIN_ETH_PAYLOAD     ((uint32_t)46U)     /*!< Minimum Ethernet payload size */
#define ETH_MAX_ETH_PAYLOAD     ((uint32_t)1500U)   /*!< Maximum Ethernet payload size */
#define ETH_JUMBO_FRAME_PAYLOAD   ((uint32_t)9000U)   /*!< Jumbo frame payload size */

#ifndef CHECKSUM_BY_HARDWARE
#define CHECKSUM_BY_HARDWARE      1
#endif /*CHECKSUM_BY_HARDWARE*/

#define ETH_RXINTERRUPT_MODE      1

#endif

