#ifndef __HMSD_EXPORT_DEFS_H__
#define __HMSD_EXPORT_DEFS_H__

#ifdef HMSD_EXPORTS
#define HMSD_API __declspec(dllexport)
#else
#define HMSD_API __declspec(dllimport)
#endif

#define EXTERN_C_START extern "C" {
#define EXTERN_C_END }


#endif //__HMSD_EXPORT_DEFS_H__