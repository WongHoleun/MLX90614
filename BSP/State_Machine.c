/**
****************************************************************************************
* @Description:ϵͳ���״̬������
* @Author: Haolin Wang
* @Date: 2023-06-03 17:31:33
* @LastEditTime: 2023-06-03 17:33:12
* @Note:���ڷ�ʱ��������ͬ������ͨ��
****************************************************************************************
*/

#include "stdio.h"
#include "math.h"
#include "stdbool.h"
#include "MLX90614.h"
#include "State_Machine.h"

SYSTEM_STATE StateMachine_system; // ״̬��

/* ȫ�ֱ��� */
float Average_Tr = 0;
extern bool Flag;	// �����ⲿ����

/**
****************************************************************************************
* @Funticon name: ״̬�������
* @Berif: ����5��״̬��״̬����ͬʱ���ж��ڼ�һֱ�ռ�������
* @Note: C �����б�ǩ(����case)����һ����䲻���Ƕ�������ı��ʽ����Ҫͨ�������Ž�����ɸ������
* @return {*}
****************************************************************************************
*/
bool Detection_Task(void)
{
    uint8_t i = 0, n = 10;

    /* ״̬��ѭ�� */
	switch (StateMachine_system)
	{

		case STATE_MLX90614: // �� MLX90614 ����ͨ��
		{
			float sum_Tr = 0, Tr = 0;

			/* ���� */
			Tr = Mlx90614_measure_temperature(); // TrƤ�����Է����¶�
			for (i = 0; i < n; i++)
			{
				Tr = Mlx90614_measure_temperature(); // TrƤ�����Է����¶�
				sum_Tr += Tr;
				HAL_Delay(1000);
			}
			Average_Tr = sum_Tr / (float)n; // ��ƽ��ֵ

			/* ����ͨ�� */
			printf("Absolute radiation temperature=%.2f\r\n", Average_Tr); // Absolute radiation temperature(ART)

			break;
		}   // case STATE_MLX90614

		default:
		{
			;
			break;
		}	// Ĭ���������

	} // switch

    return Flag;
} // bool DETECTION_Task(void)

void SYSTEM_STATE_Init(void)
{
    StateMachine_system = STATE_MLX90614; // ״̬����ʼ״̬
}
