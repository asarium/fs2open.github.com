
#ifndef CHROMIUMSTATELOGIC_H
#define CHROMIUMSTATELOGIC_H
#pragma once

#include <ctime>

#include "globalincs/pstypes.h"
#include "statelogic/statelogic.h"
#include "chromium/ClientImpl.h"
#include "chromium/Browser.h"

namespace chromium
{
	class ChromiumStateLogic : public statelogic::StateLogic
	{
	private:
		CefString mInitialUrl;

		boost::shared_ptr<Browser> mBrowser;

		std::clock_t mLastUpdate;

	public:
		ChromiumStateLogic(const SCP_string& url);

		virtual void enterState(GameState oldState) override;

		virtual void doFrame() override;

		virtual void leaveState(GameState newState) override;
	};
}

#endif // CHROMIUMSTATELOGIC_H
