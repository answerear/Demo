

#ifndef __VISION_DIR_WIN32_H__
#define __VISION_DIR_WIN32_H__


#include "IDirAdapter.h"
#include <windows.h>


namespace VPlatform
{
	class VDirAdapter : public IDirAdapter
	{
		V_DISABLE_COPY(VDirAdapter);

	public:
		VDirAdapter();
		virtual ~VDirAdapter();

	protected:
		virtual bool findFile(const VString &strPath);
		virtual bool findNextFile();
		virtual void close();

		virtual VString getRoot() const;
		virtual VString getFileName() const;
		virtual VString getFilePath() const;
		virtual VString getFileTitle() const;

		virtual uint32_t getLength() const;

		virtual bool isDots() const;
		virtual bool isDirectory() const;

		virtual long_t getCreationTime() const;
		virtual long_t getLastAccessTime() const;
		virtual long_t getLastWriteTime() const;

		virtual bool makeDir(const VString &strDir);
		virtual bool removeDir(const VString &strDir);

		virtual bool remove(const VString &strFileName);
		virtual bool exists(const VString &strPath) const;

		virtual VString getCachePath() const;
		virtual VString getAppPath() const;
		virtual char getNativeSeparator() const;

		bool extractRoot(const VString &strFilePath, VString &strRoot);
		bool extractFileName(const VString &strFilePath, VString &strName, VString &strTitle) const;

	protected:
		HANDLE			m_hFindFile;
		WIN32_FIND_DATA	m_FindFileData;

		mutable	bool		m_bExtractName;

		mutable VString		m_strRoot;
		mutable VString		m_strPath;
		mutable VString		m_strName;
		mutable VString		m_strTitle;
	};
}


#endif	/*__VISION_DIR_WIN32_H__*/
