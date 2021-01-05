
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
#include "watchdog.h"
#include "sgm706.h"

#ifdef PKG_USING_SGM706

#define DBG_TAG "sgm706"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_err_t sgm706_feed(rt_watchdog_t *wdt)
{
	rt_base_t pin = 0;
	
	pin = (rt_base_t)wdt->parent.user_data;
	if (PIN_LOW == rt_pin_read(pin))
	{
		rt_pin_write(pin, PIN_HIGH);
	}
	else
	{
		rt_pin_write(pin, PIN_LOW);
	}
	return RT_EOK;
}

static rt_err_t sgm706_init(rt_watchdog_t *wdt)
{
  	rt_base_t pin = 0;
	
	pin = (rt_base_t)wdt->parent.user_data;
	rt_pin_mode(pin, PIN_MODE_OUTPUT);
	rt_pin_write(pin, PIN_LOW);	/* 初始化引脚后即启动sgm706看门狗，且不可停止 */
	return RT_EOK;
}

static rt_err_t sgm706_control(rt_watchdog_t *wdt, int cmd, void *args)
{
  	rt_uint8_t  *p = RT_NULL;
	
    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
       	p = (rt_uint8_t*)args;
		*p = 16;	/* sgm706为 1.6s溢出时间 */
        break;
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        sgm706_feed(wdt);
        break;
    default:
        return RT_ERROR;
    }
    return RT_EOK;
}

static struct rt_watchdog_ops sgm706_ops =
    {
        sgm706_init,
        sgm706_control
    };

static rt_watchdog_t sgm706_iwg =
    {
        .ops = &sgm706_ops
    };

int rt_hw_sgm706_init(const char*name, rt_base_t pin)
{
  	return rt_hw_watchdog_register(&sgm706_iwg, name, RT_DEVICE_FLAG_DEACTIVATE, (void*)pin);
}

#endif