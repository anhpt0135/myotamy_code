#ifndef _dbg_h_
#define _dbg_h_

#include <stdio.h>
#include <string.h>
#include <errno.h>

// log_info("This is function a");
// log_info("The result is %d and the response is %s", result, res);
#define log_info(M, ...) fprintf(fp, "[INFO]: (%s, %d)" M "\n",__FILE__, __LINE__, ##__VA_ARGS__)
#define log_err(M, ...) fprintf(fp, "[ERROR]: (%s, %d)" M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#endif