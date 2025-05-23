/*
 * Copyright (c) 2024, COVESA
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *    * Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of COVESA nor the names of its contributors may be
 *      used to endorse or promote products derived from this software without
 *      specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file This files contains functions for de-/serialization of IEEE1722's ACF
 * Most PDU formats. For details see IEEE Std. 1722-2016, chapter 9.4.6.
 */

#pragma once

#include "avtp/Defines.h"
#include "avtp/acf/AcfCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Length of ACF Most header. */
#define AVTP_MOST_HEADER_LEN (4 * AVTP_QUADLET_SIZE)

/** ACF Most PDU. */
typedef struct {
    uint8_t header[AVTP_MOST_HEADER_LEN];
    uint8_t payload[0];
} Avtp_Most_t;

/** Fields of ACF Most PDU. */
typedef enum  {
    /* ACF common header fields */
    AVTP_MOST_FIELD_ACF_MSG_TYPE = 0,
    AVTP_MOST_FIELD_ACF_MSG_LENGTH,
    /* ACF Most header fields */
    AVTP_MOST_FIELD_PAD,
    AVTP_MOST_FIELD_MTV,
    AVTP_MOST_FIELD_MOST_NET_ID,
    AVTP_MOST_FIELD_RESERVED,
    AVTP_MOST_FIELD_MESSAGE_TIMESTAMP,
    AVTP_MOST_FIELD_DEVICE_ID,
    AVTP_MOST_FIELD_FBLOCK_ID,
    AVTP_MOST_FIELD_INST_ID,
    AVTP_MOST_FIELD_FUNC_ID,
    AVTP_MOST_FIELD_OP_TYPE,
    AVTP_MOST_FIELD_RESERVED_2,
    /* Count number of fields for bound checks */
    AVTP_MOST_FIELD_MAX
} Avtp_MostFields_t;

/**
 * Initializes an ACF Most PDU.
 *
 * @param pdu Pointer to the first bit of a 1722 ACF Most PDU.
 */
void Avtp_Most_Init(Avtp_Most_t* pdu);

/**
 * Returns the value of an ACF Most PDU field.
 *
 * @param pdu Pointer to the first bit of an 1722 ACF Most PDU.
 * @param field Data field to be read
 * @returns Value of the PDU field.
 */
uint64_t Avtp_Most_GetField(const Avtp_Most_t* const pdu, Avtp_MostFields_t field);

uint8_t Avtp_Most_GetAcfMsgType(const Avtp_Most_t* const pdu);
uint16_t Avtp_Most_GetAcfMsgLength(const Avtp_Most_t* const pdu);
uint8_t Avtp_Most_GetPad(const Avtp_Most_t* const pdu);
uint8_t Avtp_Most_GetMtv(const Avtp_Most_t* const pdu);
uint8_t Avtp_Most_GetMostNetId(const Avtp_Most_t* const pdu);
uint64_t Avtp_Most_GetMessageTimestamp(const Avtp_Most_t* const pdu);
uint16_t Avtp_Most_GetDeviceId(const Avtp_Most_t* const pdu);
uint8_t Avtp_Most_GetFblockId(const Avtp_Most_t* const pdu);
uint8_t Avtp_Most_GetInstId(const Avtp_Most_t* const pdu);
uint16_t Avtp_Most_GetFuncId(const Avtp_Most_t* const pdu);
uint8_t Avtp_Most_GetOpType(const Avtp_Most_t* const pdu);

/**
 * Sets the value of an ACF Most PDU field.
 *
 * @param pdu Pointer to the first bit of an 1722 ACF Most PDU.
 * @param field Specifies the position of the data field to be read
 * @param value Pointer to location to store the value.
 */
void Avtp_Most_SetField(Avtp_Most_t* pdu, Avtp_MostFields_t field, uint64_t value);

void Avtp_Most_SetAcfMsgType(Avtp_Most_t* pdu, uint8_t value);
void Avtp_Most_SetAcfMsgLength(Avtp_Most_t* pdu, uint16_t value);
void Avtp_Most_SetPad(Avtp_Most_t* pdu, uint8_t value);
void Avtp_Most_EnableMtv(Avtp_Most_t* pdu);
void Avtp_Most_DisableMtv(Avtp_Most_t* pdu);
void Avtp_Most_SetMostNetId(Avtp_Most_t* pdu, uint8_t value);
void Avtp_Most_SetMessageTimestamp(Avtp_Most_t* pdu, uint64_t value);
void Avtp_Most_SetDeviceId(Avtp_Most_t* pdu, uint16_t value);
void Avtp_Most_SetFblockId(Avtp_Most_t* pdu, uint8_t value);
void Avtp_Most_SetInstId(Avtp_Most_t* pdu, uint8_t value);
void Avtp_Most_SetFuncId(Avtp_Most_t* pdu, uint16_t value);
void Avtp_Most_SetOpType(Avtp_Most_t* pdu, uint8_t value);

/**
 * Checks if the ACF Most frame is valid by checking:
 *     1) if the length field of AVTP/ACF messages contains a value larger than the actual size of the buffer that contains the AVTP message.
 *     2) if other format specific invariants are not upheld
 * @param pdu Pointer to the first bit of an 1722 ACF Most PDU.
 * @param bufferSize Size of the buffer containing the ACF Most frame.
 * @return true if the ACF Most frame is valid, false otherwise.
 */
uint8_t Avtp_Most_IsValid(const Avtp_Most_t* const pdu, size_t bufferSize);


#ifdef __cplusplus
}
#endif
