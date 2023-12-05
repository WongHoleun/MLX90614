/**
****************************************************************************************
* @Description:系统检测状态机程序
* @Author: Haolin Wang
* @Date: 2023-06-03 17:31:33
* @LastEditTime: 2023-06-03 17:33:12
* @Note:用于分时段启动不同传感器通信
****************************************************************************************
*/

#include "stdio.h"
#include "math.h"
#include "stdbool.h"
#include "MLX90614.h"
#include "State_Machine.h"

SYSTEM_STATE StateMachine_system; // 状态机

/* 全局变量 */
float Average_Tr = 0;
extern bool Flag;	// 声明外部变量

/**
****************************************************************************************
* @Funticon name: 状态机程序段
* @Berif: 具有5种状态的状态机，同时在中断期间一直收集样本。
* @Note: C 语言中标签(例如case)的下一条语句不能是定义变量的表达式，需要通过大括号将语句变成复合语句
* @return {*}
****************************************************************************************
*/
bool Detection_Task(void)
{
    uint8_t i = 0, n = 10;

    /* 状态机循环 */
	switch (StateMachine_system)
	{

		case STATE_MLX90614: // 与 MLX90614 进行通信
		{
			float sum_Tr = 0, Tr = 0;

			/* 动作 */
			Tr = Mlx90614_measure_temperature(); // Tr皮肤绝对辐射温度
			for (i = 0; i < n; i++)
			{
				Tr = Mlx90614_measure_temperature(); // Tr皮肤绝对辐射温度
				sum_Tr += Tr;
				HAL_Delay(1000);
			}
			Average_Tr = sum_Tr / (float)n; // 求平均值

			/* 串口通信 */
			printf("Absolute radiation temperature=%.2f\r\n", Average_Tr); // Absolute radiation temperature(ART)

			break;
		}   // case STATE_MLX90614

		default:
		{
			;
			break;
		}	// 默认情况处理

	} // switch

    return Flag;
} // bool DETECTION_Task(void)

void SYSTEM_STATE_Init(void)
{
    StateMachine_system = STATE_MLX90614; // 状态机初始状态
}
