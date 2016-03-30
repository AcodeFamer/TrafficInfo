/* -----------------------------------------------------------------------
 * Paramics Programmer API   (paramics-support@quadstone.com)
 * Quadstone Ltd.             Tel: +44 131 220 4491
 * 16 Chester Street          Fax: +44 131 220 4492
 * Edinburgh, EH3 7RA, UK     WWW: http://www.paramics-online.com
 * ----------------------------------------------------------------------- */ 
#ifndef _API_USER_H_
#define _API_USER_H_


#if defined ( WIN32 ) && defined ( WARNING_OFF )
#pragma warning( disable : WARNING_OFF )
#endif

#ifdef WIN32
#ifdef __cplusplus
#define PLUGIN_EXPORT_OR(r, f, p) extern "C" __declspec(dllexport) r f p;
#define PLUGIN_EXPORT_OL(r, f, p, c) extern "C" __declspec(dllexport) r f p;
#else
#define PLUGIN_EXPORT_OR(r, f, p)  __declspec(dllexport) r f p;
#define PLUGIN_EXPORT_OL(r, f, p, c)  __declspec(dllexport) r f p;
#endif
#else
#ifdef __cplusplus
#define PLUGIN_EXPORT_OR(r, f, p) extern "C" r f p;
#define PLUGIN_EXPORT_OL(r, f, p, c) extern "C" r f p;
#else
#define PLUGIN_EXPORT_OR(r, f, p) r f p;
#define PLUGIN_EXPORT_OL(r, f, p, c) r f p;
#endif
#endif
#include "api_exports.h"
#undef PLUGIN_EXPORT_OR
#undef PLUGIN_EXPORT_OL

#ifdef WIN32
#ifdef __cplusplus
#define PLUGIN_IMPORT(r, f, p) extern "C" __declspec(dllimport) r f p;
#else
#define PLUGIN_IMPORT(r, f, p)  __declspec(dllimport) r f p;
#endif
#else
#ifdef __cplusplus
#define PLUGIN_IMPORT(r, f, p) extern "C" r f p;
#else
#define PLUGIN_IMPORT(r, f, p) r f p;
#endif
#endif
#include "api_imports.h"
#undef PLUGIN_IMPORT

#include "api_old_imports.h"

#endif
