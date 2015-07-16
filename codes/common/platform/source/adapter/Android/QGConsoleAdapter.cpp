

#include "QGConsoleAdapter.h"

namespace QGLoggerSystem
{
	QGConsoleAdapter::QGConsoleAdapter(){

	}

	void QGConsoleAdapter::Print(const char *pText){
		LOGD("QGameLogSDK","%s\n",pText);
	}
}
