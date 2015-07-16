

#ifndef __QQGAME_LOGGER_TIMER_ANDROID_H__
#define __QQGAME_LOGGER_TIMER_ANDROID_H__


#include "ITimerAdapter.h"
#include "QGConsoleAdapter.h"
#include <map>


namespace QGLoggerSystem
{
	class QGTimerAdapter : public ITimerAdapter
	{
	public:
		QGTimerAdapter();
		virtual ~QGTimerAdapter();
		//供jni函数调用下载以后，直接通过这个函数触发超时事件
		static void  OnTimer(uint32_t uIDEvent);

		QG_DISABLE_COPY(QGTimerAdapter);
	protected:
		virtual uint32_t Start(uint32_t unInterval);
		virtual void Stop();
		virtual void SetObserver(ITimerObserver *pObserver);
		virtual uint32_t GetTimerID() const;

	private:
		

	private:
		typedef std::pair<uint32_t, QGTimerAdapter*>	QTimerPair;
		typedef std::map<uint32_t, QGTimerAdapter*>		QTimerMap;

		static QTimerMap	m_sTimerMap;

		ITimerObserver		*m_pObserver;
		uint32_t				m_unTimerID;
	};
}


#endif	/*__QQGAME_LOGGER_TIMER_ANDROID_H__*/

