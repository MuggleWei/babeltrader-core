/******************************************************************************
 *  @file         json_utils.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-07-07
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader json utils
 *****************************************************************************/

#ifndef BABELTRADER_JSON_UTILS_H_
#define BABELTRADER_JSON_UTILS_H_

#include "babeltrader/base/defines/macro.h"
#include "babeltrader/base/log/log.h"

NS_BABELTRADER_BEGIN

#define BABELTRADER_JSON_HAS_OBJ(node, field) (node.HasMember(field) && node[field].IsObject())
#define BABELTRADER_JSON_HAS_STR(node, field) (node.HasMember(field) && node[field].IsString())
#define BABELTRADER_JSON_HAS_INT(node, field) (node.HasMember(field) && node[field].IsInt())
#define BABELTRADER_JSON_HAS_UINT(node, field) (node.HasMember(field) && node[field].IsUint())
#define BABELTRADER_JSON_HAS_BOOL(node, field) (node.HasMember(field) && node[field].IsBool())

#define BABELTRADER_JSON_GET_STR_THROW(val, node, field) \
if (BABELTRADER_JSON_HAS_STR(node, field)) \
{ \
	val = node[field].GetString(); \
} \
else \
{ \
	LOG_ERROR("can't find field '" field "' with string type"); \
	throw std::logic_error("can't find field '" field "' with string type"); \
}

#define BABELTRADER_JSON_GET_STR(val, node, field, default_val) \
if (BABELTRADER_JSON_HAS_STR(node, field)) \
{ \
	val = node[field].GetString(); \
} \
else \
{ \
	val = default_val; \
}

#define BABELTRADER_JSON_GET_INT_THROW(val, node, field) \
if (BABELTRADER_JSON_HAS_INT(node, field)) \
{ \
	val = node[field].GetInt(); \
} \
else \
{ \
	LOG_ERROR("can't find field '" field "' with int type"); \
	throw std::logic_error("can't find field '" field "' with int type"); \
}

#define BABELTRADER_JSON_GET_INT(val, node, field, default_val) \
if (BABELTRADER_JSON_HAS_INT(node, field)) \
{ \
	val = node[field].GetInt(); \
} \
else \
{ \
	val = default_val; \
}

#define BABELTRADER_JSON_GET_UINT_THROW(val, node, field) \
if (BABELTRADER_JSON_HAS_UINT(node, field)) \
{ \
	val = node[field].GetUint(); \
} \
else \
{ \
	LOG_ERROR("can't find field '" field "' with uint type"); \
	throw std::logic_error("can't find field '" field "' with uint type"); \
}

#define BABELTRADER_JSON_GET_UINT(val, node, field, default_val) \
if (BABELTRADER_JSON_HAS_UINT(node, field)) \
{ \
	val = node[field].GetUint(); \
} \
else \
{ \
	val = default_val; \
}

#define BABELTRADER_JSON_GET_BOOL_THROW(val, node, field) \
if (BABELTRADER_JSON_HAS_BOOL(node, field)) \
{ \
	val = node[field].GetBool(); \
} \
else \
{ \
	LOG_ERROR("can't find field '" field "' with boolean type"); \
	throw std::logic_error("can't find field '" field "' with boolean type"); \
}

#define BABELTRADER_JSON_GET_BOOL(val, node, field, default_val) \
if (BABELTRADER_JSON_HAS_BOOL(node, field)) \
{ \
	val = node[field].GetBool(); \
} \
else \
{ \
	val = default_val; \
}

#define BABELTRADER_JSON_SET_STR(w, k, v) \
w.Key(k); w.String(v);

#define BABELTRADER_JSON_SET_INT(w, k, v) \
w.Key(k); w.Int(v);

#define BABELTRADER_JSON_SET_BOOL(w, k, v) \
w.Key(k); w.Bool(v);

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_JSON_UTILS_H_ */
