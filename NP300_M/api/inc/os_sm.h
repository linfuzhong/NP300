/******************************************************************************/
/** \file os_types.h
 **
 ** os type common define.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2020-11-07  1.0  LFZ First version.
 **
 ******************************************************************************/

#ifndef __OS_SM_H__
#define __OS_SM_H__

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "os_types.h"
#include "os_mgq.h"

/* 消息队列函数执行结构体 */
typedef void (*os_msg_func)(app_message_t *pt_msg);
typedef struct
{
  uint8        e_msg;
  os_msg_func  p_proc_msg;
}os_msg_array_t;

bool os_msg_sm_array_init(uint8 u8msgtype_start, uint8 u8msgtype_end, uint8 u8msg_array_size, const os_msg_array_t *pt_msg_array);
bool os_msg_sm_proc(uint8 u8msgtype_start, uint8 u8msgtype_end, const os_msg_array_t *pt_msg_array, app_message_t *pt_msg);

#ifdef __cplusplus  // close out "C" linkage in case of c++ compiling
}
#endif

#endif /* __OS_TYPES_H__ */

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/



