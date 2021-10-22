/******************************************************************************
 *  @file         common_msg_struct.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-10-20
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader common message struct
 *****************************************************************************/

#ifndef BABELTRADER_COMMON_MSG_STRUCT_H_
#define BABELTRADER_COMMON_MSG_STRUCT_H_

#include "babeltrader/include/common_macro.h"

; // for avoid pragma warning tip in vim
#pragma pack(push, 1)

NS_BABELTRADER_BEGIN

/**
 * @brief empty message
 */
struct MsgEmpty
{};

NS_BABELTRADER_END

#pragma pack(pop)

#endif /* ifndef BABELTRADER_BASE_MSG_STRUCT_H_ */
