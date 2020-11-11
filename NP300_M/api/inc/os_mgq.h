/******************************************************************************/
/** \file os_types.h
 **
 ** os type common define.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2020-11-07  1.0  LFZ First version.
 **
 ******************************************************************************/

#ifndef __OS_MGQ_H__
#define __OS_MGQ_H__

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include <rtthread.h>
#include "os_types.h"

/*总的消息队列内存池大小*/
#define OS_MSG_POOL_SIZE_MAX							(1024)

/*采集任务内存池的起始地址和大小*/
#define SAMPLE_MSG_POOL_START							(0)
#define SAMPLE_MSG_POOL_SIZE							(128)

/*显示任务内存池的其实地址和大小*/
#define DISPLAY_MSG_POOL_START						(SAMPLE_MSG_POOL_START + SAMPLE_MSG_POOL_SIZE)
#define DISPLAY_MSG_POOL_SIZE							(128)

/*标注消息的数据结构体*/
typedef struct
{
	uint8  		u8mg_type;					//消息的类型
	uint16		u16mg_datalen;			//带数据的消息的长度
	uint8 *		pt_mgdata;				  //带数据的消息的数据
}app_message_t;

typedef app_message_t* app_mgq_pt;

typedef enum
{
	e_mgs_pool_sample  = SAMPLE_MSG_POOL_START,
	e_mgs_pool_display = DISPLAY_MSG_POOL_START,
	
	e_mgs_pool_end     = OS_MSG_POOL_SIZE_MAX
}app_message_pool_e;
	
bool os_mq_init(rt_mq_t mq, const char *name, app_message_pool_e e_mgs);
rt_mq_t os_mq_create(const char *name, rt_size_t  max_msgs);

bool os_mq_get_mem(app_mgq_pt pt_msg, uint8 u8msg_type, const uint16 u16size);
void os_mq_free_mem(app_mgq_pt pt_msg);

bool os_mq_send_with_data(rt_mq_t mq, app_mgq_pt pt_msg, bool gent_en);
bool os_mq_send_no_data(rt_mq_t mq, uint8 mgq_type, bool gent_en);

bool os_mq_recv(rt_mq_t mq, app_mgq_pt pt_msg, rt_int32_t timeout);

#ifdef __cplusplus  // close out "C" linkage in case of c++ compiling
}
#endif

#endif /* __OS_TYPES_H__ */

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/



