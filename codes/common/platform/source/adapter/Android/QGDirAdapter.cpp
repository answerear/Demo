#include "QGDirAdapter.h"
namespace QGLoggerSystem
{

bool QGDirAdapter::m_bSDReady;
QString QGDirAdapter::m_strCachePath;
QString QGDirAdapter::m_strSDPath;

QGDirAdapter::QGDirAdapter(){

}

QGDirAdapter::~QGDirAdapter(){

}


QString QGDirAdapter::GetAppPath() const{
	return m_strCachePath;
}

QString QGDirAdapter::GetCachePath() const{
	if(m_bSDReady){
		return m_strSDPath;
	}
	return m_strCachePath;
}

long_t QGDirAdapter::GetCreationTime() const{
	return 0;
}

long_t QGDirAdapter::GetLastAccessTime() const{
    return 0;
}

long_t QGDirAdapter::GetLastWriteTime() const{
	return 0;
}

void QGDirAdapter::SetExternalStroageRedy(bool bReady){
	m_bSDReady=bReady;
}

void QGDirAdapter::SetExternalStoragePath(QString sdPath){
	m_strCachePath=sdPath;
}

void QGDirAdapter::SetAppPath(QString appPath){
	m_strCachePath=appPath;
}
}

