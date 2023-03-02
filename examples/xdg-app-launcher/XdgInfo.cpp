#include "XdgInfo.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <QStringList>
#include <QProcessEnvironment>
#include <QFileInfo>

XdgInfo XdgInfo::xdginfo;

XdgInfo &XdgInfo::getInstance() {
  return xdginfo;
}

XdgInfo::XdgInfo()
{
  QProcessEnvironment env { QProcessEnvironment::systemEnvironment() };
  if (m_xdg_data_dirs.size() == 0)
    {
      QString dir;
      if((dir = env.value("XDG_DATA_HOME")).size() > 0)
	{
	  m_xdg_data_dirs.push_back(dir);
	}
      else
	{
	  if((dir = env.value("HOME")).size() > 0)
	    {
	      m_xdg_data_dirs.push_back(dir + "/.local/share");
	    }
	  else
	    {
              // get the home directory of this user
	      struct passwd *info = ::getpwuid(::getuid());
	      if (info)
		{
		  m_xdg_data_dirs.push_back(QString(info->pw_dir) + "/.local/share");
		}
	    }
	}
      if((dir = env.value("XDG_DATA_DIRS")).size() > 0)
	{
          m_xdg_data_dirs << dir.split(':');
	}
      // Common paths
      m_xdg_data_dirs.push_back("/usr/share");
      
      // If all else fails, check the current directory
      m_xdg_data_dirs.push_back(".");
    }
}

QString XdgInfo::find(QString const &file,
                      QString const &subdir,
                      QString const &extension)
{
  QString full_path;
  QFileInfo fi { file };
  if (fi.exists() && fi.isFile() && fi.isReadable())
    {
      // argument `file` may point to the full path:
      full_path = fi.canonicalFilePath();
    }
  else
    {
      QString fil(file);
      QString sub(subdir.size() ? QString("/") + subdir + "/" : "/");
      QString ext(extension.size() ? ((extension[0] == QChar('.')) ? QString("") : QString(".")) + extension : "");

      // Strip the extension, if it exists
      if (fil.endsWith(ext))
        fil.truncate(fil.indexOf(ext));
      
      // now search in the XDG directories:
      for(auto dir : m_xdg_data_dirs)
        {
          QString path(dir + sub + fil + ext);
          QFileInfo fi { path };
          if (fi.exists())
            {
              if (fi.isFile() && fi.isReadable())
                {
                  // Found the file:
                  full_path = fi.canonicalFilePath();
                  break;
                }
            }
        }
    }
  return full_path;
}

