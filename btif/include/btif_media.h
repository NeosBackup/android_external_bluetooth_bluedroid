/******************************************************************************
 *
 *  Copyright (C) 2009-2012 Broadcom Corporation
 *
 *  This program is the proprietary software of Broadcom Corporation and/or its
 *  licensors, and may only be used, duplicated, modified or distributed
 *  pursuant to the terms and conditions of a separate, written license
 *  agreement executed between you and Broadcom (an "Authorized License").
 *  Except as set forth in an Authorized License, Broadcom grants no license
 *  (express or implied), right to use, or waiver of any kind with respect to
 *  the Software, and Broadcom expressly reserves all rights in and to the
 *  Software and all intellectual property rights therein.
 *  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS
 *  SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY BROADCOM AND DISCONTINUE
 *  ALL USE OF THE SOFTWARE.
 *
 *  Except as expressly set forth in the Authorized License,
 *
 *  1.     This program, including its structure, sequence and organization,
 *         constitutes the valuable trade secrets of Broadcom, and you shall
 *         use all reasonable efforts to protect the confidentiality thereof,
 *         and to use this information only in connection with your use of
 *         Broadcom integrated circuit products.
 *
 *  2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED
 *         "AS IS" AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES,
 *         REPRESENTATIONS OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY,
 *         OR OTHERWISE, WITH RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY
 *         DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY,
 *         NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES,
 *         ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 *         CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING
 *         OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
 *
 *  3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM
 *         OR ITS LICENSORS BE LIABLE FOR
 *         (i)   CONSEQUENTIAL, INCIDENTAL, SPECIAL, INDIRECT, OR EXEMPLARY
 *               DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY RELATING TO
 *               YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM
 *               HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES; OR
 *         (ii)  ANY AMOUNT IN EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE
 *               SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE
 *               LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF
 *               ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.
 *
 *****************************************************************************/

/****************************************************************************
 **
 **  Name:          btif_media.h
 **
 **  Description:   This is the audio module for the BTIF system.  It contains
 **                 task implementations of A2DP
 **
 ******************************************************************************/

#ifndef BTIF_MEDIA_H
#define BTIF_MEDIA_H

#include "bta_api.h"
#include "bd.h"
#include "gki.h"
#include "btif_av_api.h"

/* Generic part */
#define BTIF_SUCCESS                         0

/*
* AV (Audio Video source) Errors
 */
#define BTIF_ERROR_SRV_AV_NOT_ENABLED        700     /* AV is not enabled */
#define BTIF_ERROR_SRV_AV_FEEDING_NOT_SUPPORTED 701  /* Requested Feeding not supported */
#define BTIF_ERROR_SRV_AV_BUSY               702     /* Another operation ongoing */
#define BTIF_ERROR_SRV_AV_NOT_OPENED         703     /* No AV link opened */
#define BTIF_ERROR_SRV_AV_NOT_STARTED        704     /* AV is not started */
#define BTIF_ERROR_SRV_AV_CP_NOT_SUPPORTED   705     /* Content protection is not supported by all headsets */

/*****************************************************************************
 **  Constants
 *****************************************************************************/


/* transcoding definition for TxTranscoding and RxTranscoding */
#define BTIF_MEDIA_TRSCD_OFF             0
#define BTIF_MEDIA_TRSCD_PCM_2_SBC       1  /* Tx */


/*****************************************************************************
 **  Data types
 *****************************************************************************/

typedef int tBTIF_STATUS;

/* tBTIF_MEDIA_INIT_AUDIO msg structure */
typedef struct
{
        BT_HDR hdr;
        UINT16 SamplingFreq; /* 16k, 32k, 44.1k or 48k*/
        UINT8 ChannelMode; /* mono, dual, stereo or joint stereo*/
        UINT8 NumOfSubBands; /* 4 or 8 */
        UINT8 NumOfBlocks; /* 4, 8, 12 or 16*/
        UINT8 AllocationMethod; /* loudness or SNR*/
        UINT16 MtuSize; /* peer mtu size */
} tBTIF_MEDIA_INIT_AUDIO;

#if (BTA_AV_INCLUDED == TRUE)
/* tBTIF_MEDIA_UPDATE_AUDIO msg structure */
typedef struct
{
        BT_HDR hdr;
        UINT16 MinMtuSize; /* Minimum peer mtu size */
        UINT8 MaxBitPool; /* Maximum peer bitpool */
        UINT8 MinBitPool; /* Minimum peer bitpool */
} tBTIF_MEDIA_UPDATE_AUDIO;

/* tBTIF_MEDIA_INIT_AUDIO_FEEDING msg structure */
typedef struct
{
        BT_HDR hdr;
        tBTIF_AV_FEEDING_MODE feeding_mode;
        tBTIF_AV_MEDIA_FEEDINGS feeding;
} tBTIF_MEDIA_INIT_AUDIO_FEEDING;
#endif


/*****************************************************************************
 **  Local data
 *****************************************************************************/

/*****************************************************************************
 **  public functions
 *****************************************************************************/

/*******************************************************************************
 **
 ** Function         btif_av_task
 **
 ** Description
 **
 ** Returns          void
 **
 *******************************************************************************/
extern int btif_media_task(void *p);


/*******************************************************************************
 **
 ** Function         btif_media_task_enc_init_req
 **
 ** Description      Request to initialize the media task encoder
 **
 ** Returns          TRUE is success
 **
 *******************************************************************************/
extern BOOLEAN btif_media_task_enc_init_req(tBTIF_MEDIA_INIT_AUDIO * p_msg);

/*******************************************************************************
 **
 ** Function         btif_media_task_enc_update_req
 **
 ** Description      Request to update the media task encoder
 **
 ** Returns          TRUE is success
 **
 *******************************************************************************/
#if (BTA_AV_INCLUDED == TRUE)
extern BOOLEAN btif_media_task_enc_update_req(tBTIF_MEDIA_UPDATE_AUDIO * p_msg);
#endif
/*******************************************************************************
 **
 ** Function         btif_media_task_start_aa_req
 **
 ** Description      Request to start audio encoding task
 **
 ** Returns          TRUE is success
 **
 *******************************************************************************/
extern BOOLEAN btif_media_task_start_aa_req(void);

/*******************************************************************************
 **
 ** Function         btif_media_task_stop_aa_req
 **
 ** Description      Request to stop audio encoding task
 **
 ** Returns          TRUE is success
 **
 *******************************************************************************/
extern BOOLEAN btif_media_task_stop_aa_req(void);


/*******************************************************************************
 **
 ** Function         btif_media_task_aa_tx_flush_req
 **
 ** Description      Request to flush audio encoding pipe
 **
 ** Returns          TRUE is success
 **
 *******************************************************************************/
extern BOOLEAN btif_media_task_aa_tx_flush_req(void);

/*******************************************************************************
 **
 ** Function         btif_media_aa_readbuf
 **
 ** Description      Read an audio GKI buffer from the BTIF media TX queue
 **
 ** Returns          pointer on a GKI aa buffer ready to send
 **
 *******************************************************************************/
extern BT_HDR *btif_media_aa_readbuf(void);

/*******************************************************************************
 **
 ** Function         btif_media_aa_writebuf
 **
 ** Description      Enqueue a Advance Audio media GKI buffer to be processed by btif media task.
 **
 ** Returns          TRUE is success
 **
 *******************************************************************************/
extern void btif_media_aa_writebuf(BT_HDR *pBuf, UINT32 timestamp, UINT16 seq_num);

/*******************************************************************************
 **
 ** Function         btif_media_av_writebuf
 **
 ** Description      Enqueue a video media GKI buffer to be processed by btif media task.
 **
 ** Returns          TRUE is success
 **
 *******************************************************************************/
extern BOOLEAN btif_media_av_writebuf(UINT8 *p_media, UINT32 media_len,
                                     UINT32 timestamp, UINT16 seq_num);

#if (BTA_AV_INCLUDED == TRUE)

/*******************************************************************************
 **
 ** Function         btif_media_task_audio_feeding_init_req
 **
 ** Description      Request to initialize audio feeding
 **
 ** Returns          TRUE is success
 **
 *******************************************************************************/

extern BOOLEAN btif_media_task_audio_feeding_init_req(tBTIF_MEDIA_INIT_AUDIO_FEEDING *p_msg);
#endif


/*******************************************************************************
 **
 ** Function         dump_codec_info
 **
 ** Description      Decode and display codec_info (for debug)
 **
 ** Returns          void
 **
 *******************************************************************************/
extern void dump_codec_info(unsigned char *p_codec);

#endif
