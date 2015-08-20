

#ifndef __QQGAME_LOGGER_DIR_ANDROID_H__
#define __QQGAME_LOGGER_DIR_ANDROID_H__

#include "QGDirAdapter_Unix.h"

namespace QGLoggerSystem
{
	class QGDirAdapter : public QGDirAdapter_Unix
	{
		QG_DISABLE_COPY(QGDirAdapter);

	public:
		QGDirAdapter();
		virtual ~QGDirAdapter();
		static void SetExternalStroageRedy(bool bReady);
		static void SetAppPath(QString appPath);
		static void SetExternalStoragePath(QString sdPath);
	protected:

		virtual QString GetCachePath() const;

		virtual QString GetAppPath() const;

		virtual long GetCreationTime() const;
		virtual long GetLastAccessTime() const;
		virtual long GetLastWriteTime() const;

	private:
		static QString m_strSDPath;
		static QString m_strCachePath;
		static bool m_bSDReady;
	};
}


#endif	/*__QQGAME_LOGGER_DIR_WIN32_H__*/
