/*
 * The Clear BSD License
 * Copyright (c) 2014-2016, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 * that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Generated by erpcgen 1.5.0 on Mon Nov 13 15:29:32 2017.
 *
 * AUTOGENERATED - DO NOT EDIT
 */


#include "client_manager.h"
#include "erpc_port.h"
extern "C"
{
#include "erpc_matrix_multiply.h"
}

#if 10500 != ERPC_VERSION_NUMBER
#error "The generated shim code version is different to the rest of eRPC code."
#endif


#if !defined(ERPC_GENERATED_CRC) || ERPC_GENERATED_CRC != 47304
#error "Macro 'ERPC_GENERATED_CRC' should be defined with value 47304."
#endif


using namespace erpc;
using namespace std;

extern ClientManager *g_client;
// for mdk/keil do not forgett add "--muldefweak" for linker
extern const uint32_t erpc_generated_crc;
#pragma weak erpc_generated_crc
extern const uint32_t erpc_generated_crc = 47304;


// Constant variable definitions
#pragma weak matrix_size
extern const int32_t matrix_size = 5;


// MatrixMultiplyService interface erpcMatrixMultiply function client shim.
void erpcMatrixMultiply(Matrix matrix1, Matrix matrix2, Matrix result_matrix)
{
    erpc_status_t err = kErpcStatus_Success;

    // Get a new request.
    RequestContext request = g_client->createRequest(false);

    // Encode the request.
    Codec * codec = request.getCodec();
    if (codec == NULL)
    {
        err = kErpcStatus_MemoryError;
    }

    if (!err)
    {
        err = codec->startWriteMessage(kInvocationMessage, kMatrixMultiplyService_service_id, kMatrixMultiplyService_erpcMatrixMultiply_id, request.getSequence());
    }
    if (!err)
    {
        for (uint32_t arrayCount1 = 0; arrayCount1 < 5; ++arrayCount1)
        {
            for (uint32_t arrayCount2 = 0; arrayCount2 < 5; ++arrayCount2)
            {
                if (!err)
                {
                    err = codec->write(matrix1[arrayCount1][arrayCount2]);
                }
                else
                {
                    break;
                }
            }
        }
    }

    if (!err)
    {
        for (uint32_t arrayCount1 = 0; arrayCount1 < 5; ++arrayCount1)
        {
            for (uint32_t arrayCount2 = 0; arrayCount2 < 5; ++arrayCount2)
            {
                if (!err)
                {
                    err = codec->write(matrix2[arrayCount1][arrayCount2]);
                }
                else
                {
                    break;
                }
            }
        }
    }

    if (!err)
    {
        err = codec->endWriteMessage();
    }

    // Send message to server
    if (!err)
    {
        err = g_client->performRequest(request);
    }

    if (!err)
    {
        for (uint32_t arrayCount1 = 0; arrayCount1 < 5; ++arrayCount1)
        {
            for (uint32_t arrayCount2 = 0; arrayCount2 < 5; ++arrayCount2)
            {
                if (!err)
                {
                    err = codec->read(&result_matrix[arrayCount1][arrayCount2]);
                }
                else
                {
                    break;
                }
            }
        }
    }

    if (!err)
    {
        err = codec->endReadMessage();
    }

    // Dispose of the request.
    g_client->releaseRequest(request);

    if (err)
    {
        client_error_handler_t errorHandler = g_client->getErrorHandler();
        if (errorHandler != NULL)
        {
            (*errorHandler)(err);
        }
        
    }

    return;
}
