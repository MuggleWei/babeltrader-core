#include "trade_api.h"
#include "babeltrader/base/version/version.h"

NS_BABELTRADER_BEGIN

///////////////// trade spi /////////////////

TradeSpi::TradeSpi()
{}

TradeSpi::~TradeSpi()
{}

void TradeSpi::OnConnected()
{}

void TradeSpi::OnDisconnected()
{}

///////////////// trade api /////////////////

TradeApi::TradeApi()
{}

TradeApi::~TradeApi()
{}

const char* TradeApi::GetVersion()
{
	return "";
}

void TradeApi::RegisterSpi(babeltrader::TradeSpi *)
{}

void TradeApi::RegisterServiceAddr(const char *)
{}

void TradeApi::Run()
{}

void TradeApi::Stop()
{}

const char* TradeApi::GetTradingDay()
{
	return "";
}

NS_BABELTRADER_END
