/*
  Additional tools for Minizip
  Code: Xavier Roche '2004
  License: Same as ZLIB (www.gzip.org)
*/

#ifndef _zip_tools_H
#define _zip_tools_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ZLIB_H
#include "zlib.h"
#endif

#include "unzip.h"

/* Repair a ZIP file_manager (missing central directory)
   file_manager: file_manager to recover
   fileOut: output file_manager after recovery
   fileOutTmp: temporary file_manager name used for recovery
*/
extern int ZEXPORT unzRepair(const char* file,
                             const char* fileOut,
                             const char* fileOutTmp,
                             uLong* nRecovered,
                             uLong* bytesRecovered);


#ifdef __cplusplus
}
#endif


#endif
