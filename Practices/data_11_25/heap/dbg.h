#ifndef _dbg_h_
#define _dbg_h_

#include <stdio.h>

#define log_info(M, ...) fprintf(stdout, "[INFO]:(%s: %s: %d)"M"\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define log_err(M, ...) fprintf(stdout, "[ERROR]:(%s: %s: %d)"M"\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)


#endif