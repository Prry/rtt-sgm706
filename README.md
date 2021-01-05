# SGM706独立看门狗驱动软件包



## 1 简介

sgm706软件包是基于RT-Thread watchdog框架实现的一个驱动包。基于该软件包，RT-Thread应用程序可以使用标准IO设备接口访问sgm706看门狗。



### 1.1 目录结构

| 名称       | 说明                  |
| ---------- | --------------------- |
| docs       | 文档目录              |
| examples   | 例子目录              |
| inc        | 头文件目录            |
| src        | 源代码目录            |
| LICENSE    | 许可证文件            |
| SConscript | RT-Thread默认构建脚本 |



### 1.2 许可证

sgm706软件包遵循 Apache license v2.0 许可，详见 `LICENSE` 文件。

<br>

## 2 芯片介绍

sgm706是圣邦微（SGMICRO）电子新推出的多功能微处理器监控电路芯片，除了看门狗功能外，还具有上电自动复位、手动复位及低电压报警（复位）等功能，使用起来非常方便可靠，可替代MAX706。sgm706可广泛应用于微处理器和微控制器系统、嵌入式控制器系统、电池供电系统、智能仪器仪表、通信系统等等。



<br>

## 3 支持情况

| 包含设备     | 温度计 |
| ------------ | ------ |
| **通信接口** |        |
| GPIO         | √      |
| **功能**     |        |
| 喂狗         | √      |
| 获取喂狗时间 | √      |
| **控制模式** |        |
| 不支持暂停   | √      |
| 支持暂停     |        |

<br>

## 4 使用说明

### 4.1 依赖

- RT-Thread 3.0.0+
- watchdog框架组件
- pin驱动



### 4.2 获取软件包

使用 sgm706 package 需要在 RT-Thread 的包管理器中选择它，具体路径如下。然后让 RT-Thread 的包管理器自动更新，或者使用 `pkgs --update` 命令更新包到 BSP 中。如需使用示例程序，则使能<code>Enable sgm706 sample</code>。

```
RT-Thread online packages --->
    peripheral libraries and drivers --->
        sensors drivers --->
            [*] SGM706 Independent watchdog..
            		[*] Enable sgm706 sample
                    Version (latest)  --->
```

>  **Version**：软件包版本选择，默认选择最新版本。 



### 4.3 初始化

sgm706 软件包初始化函数如下所示：

```
int rt_hw_sgm706_init(const char*name, rt_base_t pin)；
```

该函数需要由用户调用，函数主要完成的功能有:

- name，设备名称

- pin，通信gpio引脚序号

  

**参考示例：**

```
#include "sgm706.h"

static int rt_hw_sgm706_port(void)
{
    rt_hw_sgm706_init("wdt", 35); /* PB0 */

    return RT_EOK;
}
/* 注册看门狗设备 */
INIT_COMPONENT_EXPORT(rt_hw_sgm706_port);
```



### 4.4 启动看门狗

sgm706 软件包基于watchdog框架，watchdog框架继承于RT-Thread标准设备框架，可以使用RT-Thread标准设备接口"open/read/control"来访问sgm706。



**参考伪代码:**

```
wdg_dev = rt_device_find("wdt");/* 查找看门狗设备 */
rt_device_init(wdg_dev); /* 初始化并启动看门狗 */
rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);/* 喂狗 */
```

<br>

>通常设置空闲线程钩子函数，在空闲线程中进行喂狗，参考“sgm706_sample.c”例程。

<br>

### 4.5 msh/finsh测试

#### 查看设备注册

```
msh >list_device
device           type         ref count
-------- -------------------- ----------
wdt      Miscellaneous Device 0            
pin      Miscellaneous Device 0       
uart4    Character Device     2       
uart2    Character Device     0   
```



#### 通过msh启动看门狗

```
msh >wdt_sample
start watchdog device
```

<br>

## 5 注意事项

暂无

<br>

## 6 联系方式

- 维护：[Acuity](https://github.com/Prry)
- 主页：<https://github.com/Prry/rtt-sgm706>    