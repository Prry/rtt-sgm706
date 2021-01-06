
/*
 * Copyright (c) 2020 panrui <https://github.com/Prry/rtt-sgm706>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-05     panrui      the first version
 */

#include <rtthread.h> 
#include <rtdevice.h>
#include "sgm706.h"

#define WDT_DEVICE_NAME    "wdt"    /* ���Ź��豸���� */
#define WDT_PIN				35      /* ι������ */

static rt_device_t wdg_dev;         /* ���Ź��豸��� */

static void idle_hook(void)
{
    /* �ڿ����̵߳Ļص�������ι�� */
    rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);
}

static int wdt_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    char device_name[RT_NAME_MAX];

    /* �ж������в����Ƿ�������豸���� */
    if (argc == 2)
    {
        rt_strncpy(device_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(device_name, WDT_DEVICE_NAME, RT_NAME_MAX);
    }
    /* �����豸���Ʋ��ҿ��Ź��豸����ȡ�豸��� */
    wdg_dev = rt_device_find(device_name);
    if (!wdg_dev)
    {
        rt_kprintf("find %s failed!\n", device_name);
        return RT_ERROR;
    }

	/* ��ʼ�����������Ź� */
	ret = rt_device_init(wdg_dev);
    if (ret != RT_EOK)
    {
        rt_kprintf("%s init failed!\n", device_name);
        return RT_ERROR;
    }
	
    /* ���ÿ����̻߳ص����� */
    rt_thread_idle_sethook(idle_hook);
	
	rt_kprintf("start watchdog device\n");
	
    return ret;
}
/* ������ msh �����б��� */
MSH_CMD_EXPORT(wdt_sample, wdt sample);

static int rt_hw_sgm706_port(void)
{
    rt_hw_sgm706_init(WDT_DEVICE_NAME, WDT_PIN);

    return RT_EOK;
}
/* ע�ῴ�Ź��豸 */
INIT_COMPONENT_EXPORT(rt_hw_sgm706_port);