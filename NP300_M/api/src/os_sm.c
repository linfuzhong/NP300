/******************************************************************************/
/** \file os_sm.c
 **
 ** os type common define.
 ** @link SampleGroup Some description @endlink
 **
 **  - 2020-11-07  1.0  LFZ First version.
 **
 ******************************************************************************/
#include "os_sm.h"
#include "bsp_log.h"

#define OS_SM_LOG(re, fmt, args...)			NP300_LOG(re, "MSG_SM:"fmt, ##args)

/* 执行消息队列的状态机初始化和检查 */
bool os_msg_sm_array_init(uint8 u8msgtype_start, uint8 u8msgtype_end, uint8 u8msg_array_size, const os_msg_array_t *pt_msg_array)
{
	uint8 u8idx;
	uint8 u8msg     = 0;
	uint8 u8msg_num = 0;
	/* 1. Verify inupt parameter */
	if (u8msgtype_end <= u8msgtype_start) {
		  OS_SM_LOG(e_log_error, "start end error");
		  return false;
	}

	if (NULL == pt_msg_array) {
		  OS_SM_LOG(e_log_error, "sm array null");
		  return false;
	}

	/* 2. Compare the Msg number with the table size. */
	u8msg_num = u8msgtype_end - u8msgtype_start + 1;
	if (u8msg_array_size != u8msg_num) {
		  OS_SM_LOG(e_log_error, "sm array size error");
		  return false;
	}

	/* 3. Check the position of msgID in the function table. */
	u8msg = u8msgtype_start;
	for (u8idx = 0; u8idx < u8msg_num; u8idx++, u8msg++) {
		   if (u8msg != pt_msg_array[u8idx].e_msg) {
			     return false;
		   }
	}
	return true;
}


/* 执行消息队列状态机函数 */
bool os_msg_sm_proc(uint8 u8msgtype_start, uint8 u8msgtype_end, const os_msg_array_t *pt_msg_array, app_message_t *pt_msg) 
{
	uint8 u8msg_type = pt_msg->u8mg_type;
	if ((u8msg_type < u8msgtype_end) && (u8msg_type > u8msgtype_start)) {
			os_msg_func pmsg_proc = NULL;
			pmsg_proc = pt_msg_array[u8msg_type - u8msgtype_start].p_proc_msg;
			if (NULL != pmsg_proc) {
				 (*pmsg_proc)(pt_msg);
		  } else {
				 OS_SM_LOG(e_log_waring, "func not find%d", u8msg_type);
		  }
		return true;
	} else {
		/* This message is not for me */
		return false;
	}
}



/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
