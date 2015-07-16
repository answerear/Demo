

#ifndef __QQGAME_DIR_ADAPTER_UNIX_H__
#define __QQGAME_DIR_ADAPTER_UNIX_H__


#include "IDirAdapter.h"
#include <dirent.h>


namespace VPlatform
{
    class VDirAdapter_Unix : public IDirAdapter
    {        
    public:
        VDirAdapter_Unix();
        virtual ~VDirAdapter_Unix();
        
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
        
		virtual bool makeDir(const VString &strDir);
        
		virtual bool removeDir(const VString &strDir);
        
		virtual bool remove(const VString &strFileName);
        
        virtual bool exists(const VString &strPath) const;
        
        virtual char getNativeSeparator() const;
        
    protected:
        bool extractRoot(const VString &strPath, VString &strRoot);
        bool extractExt(const VString &strName, VString &strExt);
        bool extractFileName(const VString &strPath, VString &strName, VString &strTitle) const;
        
    protected:
        DIR     *m_pDir;
        dirent  *m_pDirent;
        
        mutable bool    m_bExtractName;
        
        VString m_strExt;
        VString m_strRoot;
        mutable VString m_strName;
        mutable VString m_strTitle;
    };
}


#endif	/*__QQGAME_DIR_ADAPTER_UNIX_H__*/
