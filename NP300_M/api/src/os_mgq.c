/******************************************************************************/
/** \file os_mgq.c
 **
 ** os type common define.
 ** @link SampleGroup Some description @endlink
 **
 **  - 2020-11-07  1.0  LFZ First version.
 **
 ******************************************************************************/
#include "os_mgq.h"
#include "bsp_log.h"

#define OS_MGQ_LOG(re, fmt, args...)			NP300_LOG(re, "MGQ:"fmt, ##args)

/* ÿ����Ϣ����󳤶� */
#define APP_MGQ_SIZE					 (sizeof(app_message_t))

/* ��̬��Ϣ���е��ڴ�� */
static uint8 os_msg_pool[OS_MSG_POOL_SIZE_MAX];

/**
 ******************************************************************************
 ** @brief  ������̬��Ϣ����
 ** @param  mq:��Ϣ���е�ַ
 ** @param	name:��Ϣ����
 ** @param  e_mgs:��ʼ������Ϣ�����ڴ��ö��
 ** @return true/false
 ******************************************************************************/
bool os_mq_init(rt_mq_t mq, const char *name, app_message_pool_e e_mgs)
{
	rt_size_t pool_size;
	rt_err_t evt;
	switch (e_mgs){
		case e_mgs_pool_sample:
			pool_size = SAMPLE_MSG_POOL_SIZE;
			break;
		case e_mgs_pool_display:
			pool_size = DISPLAY_MSG_POOL_SIZE;
			break;
		case e_mgs_pool_end:
			return false;
		
		default:
			return false;
	}
  evt = rt_mq_init(mq, name, &os_msg_pool[e_mgs], APP_MGQ_SIZE, pool_size, RT_IPC_FLAG_FIFO);
	
	if (evt != RT_EOK){
		  OS_MGQ_LOG(e_log_error, "init error");
	    return false;
	} else {
	    return true;
	}
}

/**
 ******************************************************************************
 ** @brief  ������̬��Ϣ����
 ** @param	name  ����Ϣ����
 ** @param  max_msgs:��Ϣ����
 ** @return rt_mq_t:��̬��Ϣ�ĵ�ַ
 ******************************************************************************/
rt_mq_t os_mq_create(const char *name, rt_size_t  max_msgs)
{
	return ( rt_mq_create(name, APP_MGQ_SIZE, max_msgs, RT_IPC_FLAG_FIFO) );
}

/**
 ******************************************************************************
 ** @brief  Ϊ���ʹ����ݵ���Ϣ���붯̬�ڴ�
 ** @param	pt_msg  ����׼��Ϣ����ָ��
 ** @param  u8msg_type:��Ϣ����
 ** @return true/false
 ******************************************************************************/
bool os_mq_get_mem(app_mgq_pt pt_msg, uint8 u8msg_type, const uint16 u16size)
{
	void *pmem = NULL;
	pt_msg->u8mg_type 		= u8msg_type;
	pt_msg->u16mg_datalen = u16size;
	pt_msg->pt_mgdata 		= NULL;
	if (u16size > 0) {
			pmem = RT_KERNEL_MALLOC(u16size);
			if (u16size != NULL){
					memset(pmem, 0, u16size);
					pt_msg->pt_mgdata = pmem;					
			} else {
				  OS_MGQ_LOG(e_log_error, "get mem error");
					return false;
			}
	}
	return true;
}

/**
 ******************************************************************************
 ** @brief  �ͷŷ��ʹ����ݵ���Ϣʱ����Ķ�̬�ڴ�
 ** @param	pt_msg  ����׼��Ϣ����ָ��
 ** @return none
 ******************************************************************************/
void os_mq_free_mem(app_mgq_pt pt_msg)
{
	/*�ͷ����ݿռ�*/
	if (pt_msg->pt_mgdata != NULL){
			RT_KERNEL_FREE(pt_msg->pt_mgdata);
			pt_msg->pt_mgdata = NULL;
	}
}

/**
 ******************************************************************************
 ** @brief  ���ʹ����ݵ���Ϣ
 ** @param  mq			: ��Ϣ����ָ��
 ** @param	pt_msg  ����׼��Ϣ����ָ��
 ** @param  gent_en : true-���ͽ�����Ϣ/false-����������Ϣ
 ** @return true/false
 ******************************************************************************/
bool os_mq_send_with_data(rt_mq_t mq, app_mgq_pt pt_msg, bool gent_en)
{
	rt_err_t evt;
	if ((pt_msg == NULL) || (mq == NULL)){
		  OS_MGQ_LOG(e_log_error, "send param error");
			return false;
	}
	if (gent_en){	
		  evt = rt_mq_urgent(mq, pt_msg, APP_MGQ_SIZE);
	} else {
			evt = rt_mq_send(mq, pt_msg, APP_MGQ_SIZE);
	}	
	if (evt != RT_EOK){
			os_mq_free_mem(pt_msg);
		  OS_MGQ_LOG(e_log_error, "send error");
	    return false;
	} else {
	    return true;
	}
}

/**
 ******************************************************************************
 ** @brief  ���������ݵ���Ϣ
 ** @param  mq			: ��Ϣ����ָ��
 ** @param	mgq_type����׼��Ϣ���ݵ�����
 ** @param  gent_en : true-���ͽ�����Ϣ/false-����������Ϣ
 ** @return true/false
 ******************************************************************************/
bool os_mq_send_no_data(rt_mq_t mq, uint8 mgq_type, bool gent_en)
{
	rt_err_t evt;
	app_message_t  mgq_t = {0};
	if (mq == NULL){
		  OS_MGQ_LOG(e_log_error, "send param error");
		  return -RT_ENOMEM;
	}	
	mgq_t.u8mg_type 		 = mgq_type;
	mgq_t.u16mg_datalen  = 0;
	mgq_t.pt_mgdata 		 = NULL;
	
	if (gent_en){	
			evt = rt_mq_urgent(mq, &mgq_t, APP_MGQ_SIZE);
	} else {
			evt = rt_mq_send(mq, &mgq_t, APP_MGQ_SIZE);
	}	
	if (evt != RT_EOK){
		  OS_MGQ_LOG(e_log_error, "send error");
	    return false;
	} else {
	    return true;
	}
}

/**
 ******************************************************************************
 ** @brief  ������Ϣ
 ** @param  mq : ��Ϣ����ָ��
 ** @param	pt_msg : ���յ���Ϣ��ŵ�ַ
 ** @param  timeout : ָ���ĳ�ʱʱ��
 ** @return true/false
 ******************************************************************************/
bool os_mq_recv(rt_mq_t mq, app_mgq_pt pt_msg, rt_int32_t timeout)
{
	rt_err_t evt;
	evt = rt_mq_recv(mq, pt_msg, APP_MGQ_SIZE, timeout);
	return ( evt != RT_EOK ? false : true);
}



/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
