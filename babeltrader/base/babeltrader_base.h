/******************************************************************************
 *  @file         babeltrader_base.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-07-01
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader base headers
 *****************************************************************************/

#ifndef BABELTRADER_BASE_H_
#define BABELTRADER_BASE_H_

// common
#include "babeltrader/include/common_macro.h"
#include "babeltrader/include/common_msg_type.h"
#include "babeltrader/include/common_net_message.h"
#include "babeltrader/include/common_event_message.h"
#include "babeltrader/include/common_msg_struct.h"

// defines
#include "babeltrader/base/defines/macro.h"
#include "babeltrader/base/defines/enum.h"
#include "babeltrader/base/defines/struct.h"

// version
#include "babeltrader/base/version/version.h"

// log
#include "babeltrader/base/log/log.h"

// json
#include "babeltrader/base/json/json_utils.h"

// memory
#include "babeltrader/base/memory/event_msg_pool.h"

// codec
#include "babeltrader/base/codec/codec.h"
#include "babeltrader/base/codec/codec_callback.h"
#include "babeltrader/base/codec/codec_chain.h"
#include "babeltrader/base/codec/tcp_bytes_buf_codec.h"

// service
#include "babeltrader/base/service/endian_conv.h"
#include "babeltrader/base/service/socket_handle.h"
#include "babeltrader/base/service/tcp_socket_handle.h"
#include "babeltrader/base/service/event_loop.h"
#include "babeltrader/base/service/server_event_loop.h"
#include "babeltrader/base/service/session_manager.h"
#include "babeltrader/base/service/message_dispatcher.hpp"

#endif /* ifndef BABELTRADER_BASE_H_ */
