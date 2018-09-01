/*
���������51��Ƭ��ʵ�ֵĺ���ң�أ�ʹ����������ʱ����
Timer1���ڿ��Ƹߵ͵�ƽ��ʱ�䳤�ȣ�Timer0�������38KHz�ز�
������Ϊ����ͨ�Ż���Ҫһ����ʱ�����͸��ÿ�ѭ��������ʱ����
���������Ҫʹ�ô��ڣ���������Բ���һ����ȷ�ĺ���ң�ز��� 
*/ 
#include<reg52.h>
#include<intrins.h>
#define MAIN_Fosc 11059200	//��ʱ��Ƶ��
sbit IR_LED	= P2^4;			//������ⷢ������
unsigned char IR_CodeBuf[68]; //�洢��������:IR_CodeBuf[1]~	IR_CodeBuf[67]
//ģʽ0~ģʽ4
void change_mode(unsigned char x)
{
	switch(x)
	{
	case 0:IR_CodeBuf[1]=0;IR_CodeBuf[2]=0;IR_CodeBuf[3]=0;break;//�Զ�
	case 1:IR_CodeBuf[1]=1;IR_CodeBuf[2]=0;IR_CodeBuf[3]=0;break;//����
	case 2:IR_CodeBuf[1]=0;IR_CodeBuf[2]=1;IR_CodeBuf[3]=0;break;//��ʪ
	case 3:IR_CodeBuf[1]=1;IR_CodeBuf[2]=1;IR_CodeBuf[3]=0;break;//�ͷ�
	case 4:IR_CodeBuf[1]=0;IR_CodeBuf[2]=0;IR_CodeBuf[3]=1;break;//����
	default: IR_CodeBuf[1]=0;IR_CodeBuf[2]=0;IR_CodeBuf[3]=0;//Ĭ�ϣ��Զ�
	}
}
// 1��������0���ػ�
void On_Off(bit x)
{
	IR_CodeBuf[4]=x;
}
//����
void change_speed(unsigned char x)
{
	switch(x)
	{
		case 0:IR_CodeBuf[5]=0;IR_CodeBuf[6]=0;break;//�Զ�
		case 1:IR_CodeBuf[5]=1;IR_CodeBuf[6]=0;break;//һ��
		case 2:IR_CodeBuf[5]=0;IR_CodeBuf[6]=1;break;//����
		case 3:IR_CodeBuf[5]=1;IR_CodeBuf[6]=1;break;//����
		default: IR_CodeBuf[5]=0;IR_CodeBuf[6]=0;//Ĭ�ϣ��Զ�
	}
}
//ɨ��
void swing_flap(bit x)
{
	IR_CodeBuf[7]=x;
}
//˯�ߣ�ÿ��һ��ʱ�䣬�Զ������¶�
void sleep(bit x)
{
 	IR_CodeBuf[8]=x;
}

//���£�16~30��
//��(t-16)ת����2���ƣ�IR_CodeBuf[9]ΪLSB��IR_CodeBuf[12]ΪMSB
void temperature(unsigned char t)
{
	IR_CodeBuf[9]=(t-16)&1;
	IR_CodeBuf[10]=((t-16)>>1)&1;
	IR_CodeBuf[11]=((t-16)>>2)&1;
	IR_CodeBuf[12]=((t-16)>>3)&1;
}

//��ʱ
//�ݲ�������ʹ�ö�ʱ��Ĭ��ȫ0
void timing(unsigned char t)
{
	IR_CodeBuf[13]=(t>>0)&1;
	IR_CodeBuf[14]=(t>>1)&1;
	IR_CodeBuf[15]=(t>>2)&1;
	IR_CodeBuf[16]=(t>>3)&1;

	IR_CodeBuf[17]=(t>>4)&1;
	IR_CodeBuf[18]=(t>>5)&1;
	IR_CodeBuf[19]=(t>>6)&1;
	IR_CodeBuf[20]=(t>>7)&1;
}
//��ʪ
void moistening(bit x)
{
	IR_CodeBuf[21]=x;
}
//�ƹ�		   
void light(bit x)
{
	IR_CodeBuf[22]=x;
}
//������
void anion(bit x)
{
	IR_CodeBuf[23]=x;
}
//�ڵ�
void dimout(bit x)
{
	IR_CodeBuf[24]=x;
}
//����
void aeration(bit x)
{
	IR_CodeBuf[25]=x;
}

//һ�ι̶�����������Ϊǰ35λ�Ľ���
void end1()
{
	IR_CodeBuf[26]=0;
	IR_CodeBuf[27]=0;
	IR_CodeBuf[28]=0;
	IR_CodeBuf[29]=1;
	IR_CodeBuf[30]=0;
	IR_CodeBuf[31]=1;
	IR_CodeBuf[32]=0;

	IR_CodeBuf[33]=0;
	IR_CodeBuf[34]=1;
	IR_CodeBuf[35]=0;
}


//����ɨ��
void up_down_swing(bit x)
{
	IR_CodeBuf[36]=x;
}
//�̶���������
void swing_connect1()
{
	IR_CodeBuf[37]=0;
	IR_CodeBuf[38]=0;
	IR_CodeBuf[39]=0;
}
//����ɨ��
void left_right_swing(bit x)
{
	IR_CodeBuf[40]=x;
}
//�̶�������
void swing_connect2()
{
	IR_CodeBuf[41]=0;
	IR_CodeBuf[42]=0;
	IR_CodeBuf[43]=0;
}
//�¶���ʾ
void display_temp(unsigned char x)
{
	switch(x)
	{
		case 0:IR_CodeBuf[44]=0;IR_CodeBuf[45]=0;break;
		case 1:IR_CodeBuf[44]=1;IR_CodeBuf[45]=0;break;
		case 2:IR_CodeBuf[44]=0;IR_CodeBuf[45]=1;break;
		case 3:IR_CodeBuf[44]=1;IR_CodeBuf[45]=1;break;
		default:	IR_CodeBuf[44]=0;IR_CodeBuf[45]=1;
	}
}
//�̶�������
void connect2()
{
	int i=0;
	for(i=46;i<=61;i++)
		IR_CodeBuf[i]=0;
	IR_CodeBuf[49]=1;
	IR_CodeBuf[63]=0;
}
//����
void energy_conservation(bit x)
{
	IR_CodeBuf[62]=x;
}
//У����
void checkout()
{
	unsigned char check;
	check=IR_CodeBuf[1] + IR_CodeBuf[2]*2 + IR_CodeBuf[3]*4+IR_CodeBuf[4]*8;
	check+=IR_CodeBuf[9] + IR_CodeBuf[10]*2 + IR_CodeBuf[11]*4 + IR_CodeBuf[12]*8;	
	check+=IR_CodeBuf[25];
	check+=IR_CodeBuf[40];
	check+=IR_CodeBuf[62];
	check+=12;
	check&=0x0f;

	IR_CodeBuf[64]=check&1;
	IR_CodeBuf[65]=(check>>1)&1;
	IR_CodeBuf[66]=(check>>2)&1;
	IR_CodeBuf[67]=(check>>3)&1;
}
void IR_Data_Init()
{
	change_mode(1);//Ĭ��ģʽ������
	
	On_Off(1);//Ĭ�Ͽ��أ���
	
	change_speed(0);//Ĭ�Ϸ��٣��Զ�
	swing_flap(1);//Ĭ��ɨ��
	sleep(0);//Ĭ��˯�ߣ���
	
	temperature(23);//Ĭ���¶ȣ�23��


	timing(0);//Ĭ�϶�ʱ������ʱ
	moistening(0);//��ʪ����
	light(1);//�ƹ⣺��
	anion(0);//�����ӣ���
	dimout(0);//�ڵ磺��
	aeration(0);//��������
	end1();//��һ�����ݵĽ�����
	up_down_swing(1);//����ɨ�磺��
	swing_connect1();
	left_right_swing(1);//����ɨ�磺��
	swing_connect2();
	display_temp(2);//�¶���ʾ����֪����ô���£���������û��
	connect2();
	energy_conservation(0);//���ܣ���
	checkout();//ÿ���޸�����֮��Ҫ����һ��У����
}
//���ĺ�������ʱ�����Ŀ��أ����������ģʽ���Լ��¶ȣ����ౣ��IR_Data_Init()������Ĭ��ֵ����
//On_Off������1���أ�0
//mode�����䣨1�������ȣ�0��
//t��	26~30
void IR_Data_Change(bit Turn_On_off, bit mode, unsigned char t)
{
	On_Off(Turn_On_off);
	if(mode)	change_mode(1);
	else		change_mode(4);
	temperature(t);
	checkout();
}
void Delay_ms(unsigned int ms)
{
     unsigned int i;
	 do{
	      i = MAIN_Fosc / 96000;
		  while(--i)	;   //96T per loop
     }while(--ms);
}
//ʹ�ö�ʱ���ж������к��ⷢ���ʱ�����
void IR_TX_Init()
{
	TMOD = 0x12;// 0001(timer1) 0010(timer0) 
	TH0	= 0xf4;
	TL0	= 0xf4;//38KHz 
	EA	= 1;// Enable All Interrupt
	ET1	= 1;// Enable Timer1
	ET0	= 1;// Enable Timer0	
	IR_LED = 1;	// stop emit
}
//��ʱ��1���Ʒ����ʱ�䳤�ȣ���ʱ��0ͨ�����Ϸ�ת��ƽ����������38KHz�ز�
void Timer1_Delay(unsigned char th1,unsigned char tl1,bit mod)
{
	TH1 = th1;
	TL1 = tl1;
	TR1 = 1;//timer1 run
	TR0 = mod;//timer0 run
	while(!TF1);//wait timer1 flag
	TF1 = 0;
	TR0 = 0;//timer0 stop run
	TR1 = 0;//timer1 stop run
	IR_LED = 1;// stop emit
}

//���ͺ�������
//���η��ͣ���ʼ��+35λ������+������+32λ������
void Transmit_TR_CODE()
{
	unsigned char i;

	//��ʼ��
	Timer1_Delay(0xdf, 0x9a, 1);//emit 9ms
	Timer1_Delay(0xef, 0xcd, 0);//delay 4.5ms
	//35λ������
	for(i = 1; i < 36; i++)
	{		
		Timer1_Delay(0xfd, 0xfc, 1);//emit 0.56ms
		if (IR_CodeBuf[i])
			Timer1_Delay(0xf9, 0xef, 0);//delay 1.685ms
		else
			Timer1_Delay(0xfd, 0xfc, 0);//delay 0.56ms	
	}
	//������
	Timer1_Delay(0xfd, 0xd7, 1);//emit 600us
	Timer1_Delay(0xb7, 0xff, 0);//delay 20000us
	//32λ������
	for(i = 36; i < 68; i++)
	{		
		Timer1_Delay(0xfd, 0xfc, 1);//emit 0.56ms
		if (IR_CodeBuf[i])
			Timer1_Delay(0xf9, 0xef, 0);//delay 1.685ms
		else
			Timer1_Delay(0xfd, 0xfc, 0);//delay 0.56ms		
	}
	Timer1_Delay(0xfd, 0xd7, 1);//emit 600us

}
//��ʱ��0��������͵ĺ�������38KHz�ز�
void Timer0() interrupt 1 //1 mean timer0
{
	IR_LED = ~IR_LED;
}
//��ʱ��1ֻ�õ��˶�ʱ��־λTF1�������жϺ����������κβ���
void Timer1() interrupt 3
{
	
}
void main()
{
	 unsigned char temp=0xfe;	 
	 IR_TX_Init();//IR���͡����ճ�ʼ��
	 IR_Data_Init();//IR���ݳ�ʼ��
	 while(1)
	 {
		IR_Data_Change(1,1,23);//�������䣬25���϶�		
		Transmit_TR_CODE();		

		temp = _cror_(temp,1);
		P1 = temp;
		
		Delay_ms(2000);
	 }
	 	
}
