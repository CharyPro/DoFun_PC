#ifndef DLCV_GLOBAL_H
#define DLCV_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLCV_PLUGIN_LIBRARY)
#  define DLCV_PLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DLCV_PLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DLCV_GLOBAL_H
