#ifndef KVASERCAN_GLOBAL_H
#define KVASERCAN_GLOBAL_H

#include <QtCore/qglobal.h>
#include<canlib.h>

#if defined(KVASERCAN_LIBRARY)
#  define KVASERCANSHARED_EXPORT Q_DECL_EXPORT
#else
#  define KVASERCANSHARED_EXPORT Q_DECL_IMPORT
#endif

#define KCAN_CAN_HANDLE_INIT             (-1)
#define KCAN_SELECTED_CHANEL_INIT             (-1)  // selected chanel init
#define KCAN_OPEN_CHANEL_FLAG_INIT              (-1)
#define KCAN_NUMBER_OF_CHANELS_INIT              (-1)


typedef struct {
  unsigned char data[8];
  unsigned int dlc;
  unsigned int flags;
  unsigned long time;
  long id;
} CanMessage;

typedef struct {
  CanHandle i_canHandle;
  int i_selectedChannel;
  int i_openChanelFlags;
  int i_busControlMode;
  int i_bitrateCode;
  unsigned int ui_tseg1;
  unsigned int ui_tseg2;
  unsigned int ui_sjw;
  unsigned int ui_noSamp;
  unsigned int ui_syncmode;
  char ca_selectedInterfaceName[64];
} KvaserCanConfig;
/**
 * \param[out] ui_tseg1     Time segment 1, that is, the number of quanta from (but not
 *                       including) the Sync Segment to the sampling point.
 * \param[out] ui_tseg2     Time segment 2, that is, the number of quanta from the sampling
 *                       point to the end of the bit.
 * \param[out] ui_sjw       The Synchronization Jump Width; can be 1,2,3, or 4.
 * \param[out] ui_noSamp    The number of sampling points; can be 1 or 3.
 * \param[out] ui_syncmode  Unsupported, always read as zero.
 * */

#endif // KVASERCAN_GLOBAL_H
