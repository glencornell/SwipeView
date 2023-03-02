#pragma once

#include <QString>
#include <QStringList>

class XdgInfo
{
public:
  static XdgInfo &getInstance();
  
  // find the full path to the given desktop entry:
  QString find(QString const &file,       // full path to file or just filename (with or without extension)
               QString const &subdir,     // "", "application", "directory", or "icon"
               QString const &extension); // optional
private:
  XdgInfo();
  ~XdgInfo() = default;
  XdgInfo(XdgInfo const &other) = delete;

  static XdgInfo xdginfo;
  
  QStringList m_xdg_data_dirs;
};
