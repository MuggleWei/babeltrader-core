/******************************************************************************
 *  @file         message_dispatcher.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-17
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader message dispatcher
 *****************************************************************************/

#ifndef BABELTRADER_MESSAGE_DISPATCHER_H_
#define BABELTRADER_MESSAGE_DISPATCHER_H_

#include "babeltrader/base/defines/macro.h"
#include "babeltrader/base/log/log.h"
#include <functional>

NS_BABELTRADER_BEGIN

class MessageDispatcher
{
	class MsgCallback
	{
	public:
		virtual ~MsgCallback() {}
		virtual void OnMessage(void*) {}
	};

	template<typename T>
	class TMsgCallback : public MsgCallback
	{
		typedef std::function<void(T*)> callbackFunc;

	public:
		TMsgCallback(const callbackFunc &callback)
			: MsgCallback()
			, callback_(callback)
		{}

		virtual void OnMessage(void *msg) override
		{
			callback_((T*)msg);
		}

	public:
		callbackFunc callback_;
	};

public:
	MessageDispatcher(uint32_t max_msg_type)
		: msg_type_limit_(max_msg_type + 1)
	{
		if (max_msg_type == 0)
		{
			const char *err_msg = 
				"failed init message dispatcher with 0 max message type";
			LOG_ERROR(err_msg);
			throw std::logic_error(err_msg);
		}

		callbacks_ = (MsgCallback**)malloc(sizeof(MsgCallback*) * msg_type_limit_);
		if (callbacks_ == nullptr)
		{
			const char *err_msg = "failed allocate message callback array";
			LOG_ERROR(err_msg);
			throw std::runtime_error(err_msg);
		}

		for (uint32_t i = 0; i < msg_type_limit_; i++)
		{
			callbacks_[i] = nullptr;
		}
	}

	virtual ~MessageDispatcher()
	{
		if (callbacks_)
		{
			for (uint32_t i = 0; i < msg_type_limit_; i++)
			{
				if (callbacks_[i])
				{
					delete callbacks_[i];
				}
			}
			free(callbacks_);
			callbacks_ = nullptr;
		}
	}

	template<typename T>
	bool Register(uint32_t msg_type, const std::function<void(T*)>& callback)
	{
		if (msg_type >= msg_type_limit_)
		{
			LOG_ERROR("message type beyond the max message type number: msg_type=%llu",
				(unsigned long long)msg_type);
			return false;
		}

		if (callbacks_[msg_type])
		{
			LOG_ERROR("repeated register callback: msg_type=%llu",
				(unsigned long long)msg_type);
			return false;
		}

		TMsgCallback<T> *tcallback = new TMsgCallback<T>(callback);
		callbacks_[msg_type] = tcallback;

		return true;
	}

	bool OnMessage(uint32_t msg_type, void *msg)
	{
		if (msg_type >= msg_type_limit_)
		{
			LOG_ERROR("message type beyond the max message type number: msg_type=%llu",
				(unsigned long long)msg_type);
			return false;
		}

		if (callbacks_[msg_type] == nullptr)
		{
			LOG_WARNING("can not find message type callback: msg_type=%llu",
				(unsigned long long)msg_type);
			return false;
		}

		callbacks_[msg_type]->OnMessage(msg);

		return true;
	}

private:
	uint32_t msg_type_limit_;
	MsgCallback **callbacks_;
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_EVENT_DISPATCHER_H_ */
