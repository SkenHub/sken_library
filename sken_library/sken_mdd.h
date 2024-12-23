/*
 * sken_mdd.h
 *
 *  Created on: 2021/02/01
 *      Author: TakumaNakao
 */

#ifndef SKEN_MDD_H_
#define SKEN_MDD_H_

#include "sken_library/include.h"

enum CommunicationMode {
	UART_MODE = 0,
	CAN_MODE
};

enum MddCommandId {
	MOTOR_RPS_COMMAND_MODE = 0,
	MOTOR_PWM_COMMAND_MODE,
	MECANUM_MODE,
	OMNI3_MODE,
	OMNI4_MODE,
	M1_PID_GAIN_CONFIG,
	M2_PID_GAIN_CONFIG,
	M3_PID_GAIN_CONFIG,
	M4_PID_GAIN_CONFIG,
	ROBOT_DIAMETER_CONFIG,
	PID_RESET_COMMAND,
	MOTOR_COMMAND_MODE_SELECT,
	ENCODER_RESOLUTION_CONFIG
};

enum MddStdid{
	None,
	MDD_0 = 0x300,
	MDD_1 = 0x301,
	MDD_2 = 0x302,
	MDD_3 = 0x303,
	MDD_4 = 0x304,
	MDD_5 = 0x305,
	MDD_6 = 0x306,
	MDD_7 = 0x307,
	MDD_8 = 0x308,
	MDD_9 = 0x309,
	MDD_A = 0x30A,
	MDD_B = 0x30B,
	MDD_C = 0x30C,
	MDD_D = 0x30D,
	MDD_E = 0x30E,
	MDD_F = 0x30F,
};

struct SendData{
	uint8_t send_data[3][8];
};

class SkenMdd {
	CommunicationMode mode_;
	Uart serial;
	uint8_t receive_data;
	uint8_t seq;
	CanData rx_can_data_;
	uint8_t send_data_[3][8];
	CanSelect can_select_;
	MddStdid stdid_;
	uint8_t send_num_ = 0;
	void UartSendData(uint8_t id,const float (&command_data)[4]);
	void CanSendData(uint8_t id,const float (&command_data)[4],int send_num = 0);
	bool Uart_tcp(uint8_t id,const float (&command_data)[4],unsigned int resend_time,unsigned int max_wait_time);
	bool Can_tcp(uint8_t id,const float (&command_data)[4],unsigned int resend_time,unsigned int max_wait_time);
	void setFloatData(const float (&command_data)[4],uint8_t (&send_data)[21]);
	uint8_t CalcChecksum(const uint8_t (&send_data)[21]);
public:
	void init(Pin tx_pin,Pin rx_pin,UartNumber uart_num);
	void init(MddStdid stdid,Pin can_tx,Pin can_rx,CanSelect can_select);
	bool tcp(uint8_t id,const float (&command_data)[4],unsigned int resend_time,unsigned int max_wait_time);
	void udp(uint8_t id,const float (&command_data)[4]);
	SendData GetSendData();
};

#endif /* SKEN_MDD_H_ */
