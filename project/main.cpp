#include "stm32h7xx_hal.h"
#include "sys.h"
#include <stdio.h>
#include <stdlib.h>
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "rtthread.h"
#include "board.h"
#include "lcd_spi_169.h"

class testxx
{
  public:
    testxx()
    {
      printf("%s\r\n",__FUNCTION__);
    }
	~testxx()
	{
		
	}
  private:

};

uint8_t mpudata[128] __attribute__((section(".dtcmram")));
uint8_t mpudata1[128] __attribute__((section(".ramd2")));
uint8_t mpudata2[128] __attribute__((section(".ramd3")));
void Delay(__IO uint32_t nCount);
void Delay(__IO uint32_t nCount)
{
    while(nCount--){}
}
static struct rt_thread led1_thread;

static rt_uint8_t rt_led1_thread_stack [1024] ALIGN(RT_ALIGN_SIZE);

void led1_thread_entry(void* p)
{
    while(1)
    {
      HAL_Delay(1000);
      printf("this thread tid is %s\n",rt_thread_self()->name);
    }
}

void led1_thread2_entry(void* p)
{

  while(1)
  {
    HAL_Delay(1000);
    printf("led2 off\r\n");
    led_off();
    
    //rt_thread_delay(500);
    HAL_Delay(1000);
    printf("led2 on\r\n");
    led_on();
    
  }
}
void mtimerout(void* x)
{
  static int m;
  if(m == 0)
  {
    //LED1_OFF();
    ++m;
  }
  else if(m == 1)
  {
    m = 0;
    //LED1_ON();
  }
  
}
/*************************************************************************************************
*	函 数 名:	LCD_Test_Clear
*
*	函数功能:	清屏测试
*************************************************************************************************/
void LCD_Test_Clear(void)
{
	uint8_t	i = 0;			// 计数变量
	
	LCD_SetDirection(Direction_V);		
	LCD_SetTextFont(&CH_Font24);			// 设置2424中文字体,ASCII字体对应为2412
	LCD_SetColor(LCD_BLACK);				// 设置画笔颜色

	for(i=0;i<8;i++)
	{
		switch (i)		// 切换背景色
		{
			case 0: LCD_SetBackColor(LIGHT_RED); 		break;	
			case 1: LCD_SetBackColor(LIGHT_GREEN); 	break;				
			case 2: LCD_SetBackColor(LIGHT_BLUE); 		break;
			case 3: LCD_SetBackColor(LIGHT_YELLOW); 	break;
			case 4: LCD_SetBackColor(LIGHT_CYAN);		break;
			case 5: LCD_SetBackColor(LIGHT_GREY); 		break;
			case 6: LCD_SetBackColor(LIGHT_MAGENTA); 	break;
			case 7: LCD_SetBackColor(LCD_WHITE); 		break;			
			default:	break;			
		}
		LCD_Clear();		// 清屏
		LCD_DisplayText(13, 70,"STM32H7 刷屏测试");
		LCD_DisplayText(13,106,"屏幕分辨率:240*280");
		LCD_DisplayText(13,142,"控制器:ST7789");	
		HAL_Delay(1000);	// 延时
	}
}


/*************************************************************************************************
*	函 数 名:	LCD_Test_Text
*
*	函数功能:	文本显示测试
*
*	说    明:	显示文本，包括各种字体大小的中文和ASCII字符 
*************************************************************************************************/
void LCD_Test_Text(void)
{
	LCD_SetBackColor(LCD_BLACK); 			//	设置背景色
	LCD_Clear(); 								// 清屏
	
	LCD_SetColor(LCD_WHITE);
	LCD_SetAsciiFont(&ASCII_Font32); LCD_DisplayString(0, 20,"!#$'()*+,-.0123"); 						    		
	LCD_SetAsciiFont(&ASCII_Font24); LCD_DisplayString(0, 52,"!#$'()*+,-.012345678"); 				   
	LCD_SetAsciiFont(&ASCII_Font20); LCD_DisplayString(0, 76,"!#$'()*+,-.0123456789:;<");      	
	LCD_SetAsciiFont(&ASCII_Font16); LCD_DisplayString(0, 96,"!#$'()*+,-.0123456789:;<=>?@AB"); 	
	LCD_SetAsciiFont(&ASCII_Font12); LCD_DisplayString(0,112,"!#$'()*+,-.0123456789:;<=>?@ABCDEFGHIJKL"); 	
																																		
	LCD_SetColor(LCD_CYAN);                                                                             
	LCD_SetAsciiFont(&ASCII_Font12); LCD_DisplayString(0,124,"!#&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKL"); 	
	LCD_SetAsciiFont(&ASCII_Font16); LCD_DisplayString(0,136,"!#&'()*+,-.0123456789:;<=>?@AB"); 	
	LCD_SetAsciiFont(&ASCII_Font20); LCD_DisplayString(0,152,"!#&'()*+,-.0123456789:;<");		  	
	LCD_SetAsciiFont(&ASCII_Font24); LCD_DisplayString(0,172,"!#&'()*+,-.012345678"); 				  	
	LCD_SetAsciiFont(&ASCII_Font32); LCD_DisplayString(0,196,"!#&'()*+,-.0123"); 							  		

	LCD_SetTextFont(&CH_Font24);			// 设置2424中文字体,ASCII字体对应为2412
	LCD_SetColor(LCD_YELLOW);				// 设置画笔，黄色
	LCD_DisplayText(0, 236,"ASCII字符集");

	HAL_Delay(2000);	// 延时等待
	LCD_Clear(); 								// 清屏

	LCD_SetTextFont(&CH_Font12);			// 设置1212中文字体,ASCII字体对应为1206
	LCD_SetColor(0X8AC6D1);					// 设置画笔
	LCD_DisplayText(14, 30,"1212:反客科技");	
	
	LCD_SetTextFont(&CH_Font16);			// 设置1616中文字体,ASCII字体对应为1608
	LCD_SetColor(0XC5E1A5);					// 设置画笔
	LCD_DisplayText(14, 50,"1616:反客科技");		
	
	LCD_SetTextFont(&CH_Font20);			// 设置2020中文字体,ASCII字体对应为2010
	LCD_SetColor(0XFFB549);					// 设置画笔
	LCD_DisplayText(14, 80,"2020:反客科技");		

	LCD_SetTextFont(&CH_Font24);			// 设置2424中文字体,ASCII字体对应为2412
	LCD_SetColor(0XFF585D);					// 设置画笔
	LCD_DisplayText(14,110,"2424:反客科技");		

	LCD_SetTextFont(&CH_Font32);			// 设置3232中文字体,ASCII字体对应为3216
	LCD_SetColor(0xFFB6B9);					// 设置画笔
	LCD_DisplayText(14,150,"3232:反客科技");		

	LCD_SetTextFont(&CH_Font24);			// 设置2424中文字体,ASCII字体对应为2412
	LCD_SetColor(LCD_WHITE);
 	LCD_DisplayText(14,200,"中文显示");	  

	HAL_Delay(2000);	// 延时等待
}
/************************************************************************************************
*	函 数 名:	LCD_Test_Variable
*
*	函数功能:	变量显示，包括整数和小数
*************************************************************************************************/
void LCD_Test_Variable (void)
{
	uint16_t i;					// 计数变量
	int32_t	a = 0;			// 定义整数变量，用于测试
	int32_t	b = 0;			// 定义整数变量，用于测试
	int32_t	c = 0;			// 定义整数变量，用于测试

	double p = 3.1415926;	// 定义浮点数变量，用于测试
	double f = -1234.1234;	// 定义浮点数变量，用于测试
	
	LCD_SetBackColor(LCD_BLACK); 			//	设置背景色
	LCD_Clear(); 								// 清屏
	
   LCD_SetTextFont(&CH_Font24);     
	LCD_SetColor(LIGHT_CYAN);					// 设置画笔，蓝绿色		
	LCD_DisplayText(0,30,"正数:");				
	LCD_DisplayText(0,60,"负数:");					
				
	LCD_SetColor(LIGHT_YELLOW);				// 设置画笔，亮黄色		
	LCD_DisplayText(0,100,"填充空格:");	
	LCD_DisplayText(0,130,"填充0:");	
	
	LCD_SetColor(LIGHT_RED);					// 设置画笔	，亮红色		
	LCD_DisplayText(0,170,"正小数:");	
	LCD_DisplayText(0,200,"负小数:");		
	
	for(i=0;i<100;i++)
   {
		LCD_SetColor(LIGHT_CYAN);								// 设置画笔	，蓝绿色	
		LCD_ShowNumMode(Fill_Space);							// 多余位填充空格
		LCD_DisplayNumber( 80,30, b+i*10, 4) ;				// 显示变量			
		LCD_DisplayNumber( 80,60, c-i*10, 4) ;				// 显示变量			
		
		LCD_SetColor(LIGHT_YELLOW);								// 设置画笔，亮黄色	

		LCD_ShowNumMode(Fill_Space);								// 多余位填充 空格
		LCD_DisplayNumber( 130,100, a+i*150, 8) ;				// 显示变量		

		LCD_ShowNumMode(Fill_Zero);								// 多余位填充0      
		LCD_DisplayNumber( 130,130, b+i*150, 8) ;				// 显示变量			
		
		LCD_SetColor(LIGHT_RED);									// 设置画笔，亮红色			
		LCD_ShowNumMode(Fill_Space);								// 多余位填充空格		
		LCD_DisplayDecimals( 100,170, p+i*0.1,  6,3);		// 显示小数	
		LCD_DisplayDecimals( 100,200, f+i*0.01, 11,4);		// 显示小数		
		
		HAL_Delay(15);				
   }
	HAL_Delay(2500);		
}
/*************************************************************************************************
*	函 数 名:	LCD_Test_Color
*
*	函数功能:	颜色测
*************************************************************************************************/
void LCD_Test_Color(void)
{
	uint16_t i;					// 计数变量
	uint16_t y;
// 颜色测试>>>>>	
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色
	
	LCD_SetTextFont(&CH_Font20);			// 设置字体
	LCD_SetColor(LCD_WHITE);				// 设置画笔颜色
	LCD_DisplayText(0,20,"RGB三基色:");

	//使用画线函数绘制三基色色条
	for(i=0;i<240;i++)
	{
		LCD_SetColor( LCD_RED-(i<<16) );
      LCD_DrawLine_V(0+i,  40,10);
	}
	for(i=0;i<240;i++)
	{
		LCD_SetColor( LCD_GREEN-(i<<8) );
      LCD_DrawLine_V(0+i,  55,10);
	}
	for(i=0;i<240;i++)
	{
		LCD_SetColor( LCD_BLUE-i );
      LCD_DrawLine_V(0+i,  70,10);
	}	

   y = 90;
   LCD_SetColor(LIGHT_CYAN);    LCD_FillRect(150,y+5     ,90,10);  LCD_DisplayString(0,y     ,"LIGHT_CYAN");	   
	LCD_SetColor(LIGHT_MAGENTA); LCD_FillRect(150,y+20*1+5,90,10);  LCD_DisplayString(0,y+20*1,"LIGHT_MAGENTA");	
	LCD_SetColor(LIGHT_YELLOW);  LCD_FillRect(150,y+20*2+5,90,10);  LCD_DisplayString(0,y+20*2,"LIGHT_YELLOW");	
	LCD_SetColor(LIGHT_GREY);    LCD_FillRect(150,y+20*3+5,90,10);  LCD_DisplayString(0,y+20*3,"LIGHT_GREY");  	

   LCD_SetColor(DARK_CYAN);     LCD_FillRect(150,y+20*4+5,90,10);  LCD_DisplayString(0,y+20*4,"DARK_CYAN");		
	LCD_SetColor(DARK_MAGENTA);  LCD_FillRect(150,y+20*5+5,90,10);  LCD_DisplayString(0,y+20*5,"DARK_MAGENTA");	
	LCD_SetColor(DARK_YELLOW);   LCD_FillRect(150,y+20*6+5,90,10);  LCD_DisplayString(0,y+20*6,"DARK_YELLOW");	
	LCD_SetColor(DARK_GREY);     LCD_FillRect(150,y+20*7+5,90,10);	 LCD_DisplayString(0,y+20*7,"DARK_GREY");	

	HAL_Delay(2000);
}

/*************************************************************************************************
*	函 数 名:	LCD_Test_Grahic
*
*	函数功能:	2D图形绘制
*************************************************************************************************/
void LCD_Test_Grahic(void)
{
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色	

	LCD_SetColor(LCD_WHITE);	
	LCD_DrawRect(0,0,240,280); 			//绘制矩形

	LCD_SetColor(LCD_RED);    LCD_FillCircle(140,70,30);		//填充圆形
	LCD_SetColor(LCD_GREEN);  LCD_FillCircle(170,70,30); 	
	LCD_SetColor(LCD_BLUE);   LCD_FillCircle(200,70,30);  	
	
	LCD_SetColor(LCD_YELLOW);
	LCD_DrawLine(26,46,113, 84);				//画直线
	LCD_DrawLine(35,42,106,101);				//画直线
	LCD_DrawLine(45,40, 93,120);				//画直线
	LCD_DrawLine(52,36, 69,128);				//画直线
	LCD_DrawLine(62,36, 44,128);				//画直线
	
	LCD_SetColor(LIGHT_CYAN);
	LCD_DrawCircle(120,190,30);			//绘制圆形
	LCD_DrawCircle(120,190,20);   

	LCD_SetColor(LIGHT_RED);	
	LCD_DrawEllipse(120,190,90,40); 	//绘制椭圆 
	LCD_DrawEllipse(120,190,70,40); 	//绘制椭圆    
	LCD_SetColor(LIGHT_MAGENTA);	
	LCD_DrawEllipse(120,190,100,50); 	//绘制椭圆
	LCD_DrawEllipse(120,190,110,60);  

	HAL_Delay(2000);		
}
/*************************************************************************************************
*	函 数 名:	LCD_Test_Image
*
*	函数功能:	图片显示测试
*************************************************************************************************/
void LCD_Test_Image(void)
{
	LCD_SetBackColor(LCD_BLACK); 			//	设置背景色
	LCD_Clear(); 								// 清屏
	
	LCD_SetColor( 0xffF6E58D);
	LCD_DrawImage( 19, 41, 83, 83, Image_Android_83x83) ;	   // 显示图片

	LCD_SetColor( 0xffDFF9FB);
	LCD_DrawImage( 141, 41, 83, 83, Image_Message_83x83) ;	// 显示图片
	
	LCD_SetColor( 0xff9DD3A8);
	LCD_DrawImage( 19, 160, 83, 83, Image_Toys_83x83) ;		// 显示图片
	
	LCD_SetColor( 0xffFF8753);
	LCD_DrawImage( 141, 160, 83, 83, Image_Video_83x83) ;		// 显示图片

	HAL_Delay(2000);	
}
/*************************************************************************************************
*	函 数 名:	LCD_Test_Direction
*
*	函数功能:	更换显示方向
*************************************************************************************************/
void  LCD_Test_Direction(void)
{
	for(int i=0;i<4;i++)
	{  
      LCD_SetBackColor(LCD_BLACK); 			//	设置背景色
      LCD_Clear(); 								// 清屏
      LCD_SetTextFont(&CH_Font24);  
	   LCD_SetColor( 0xffDFF9FB);         
		switch (i)		// 切换背景色
		{
			case 0:  
            LCD_SetDirection(Direction_V);		   
            LCD_DisplayText(20,40,"Direction_V"); 
         break;	

			case 1:  
            LCD_SetDirection(Direction_H); 	
            LCD_DisplayText(20,40,"Direction_H"); 
         break;	

			case 2:  
            LCD_SetDirection(Direction_V_Flip); 
            LCD_DisplayText(20,40,"Direction_V_Flip"); 
         break;
			case 3: 
            LCD_SetDirection(Direction_H_Flip); 	
            LCD_DisplayText(20,40,"Direction_H_Flip"); 
         break;
	
			default:	break;			
		}
      LCD_SetColor( 0xffF6E58D);
      LCD_DrawImage( 19,100, 83, 83, Image_Android_83x83) ;	   // 显示图片
      LCD_SetTextFont(&CH_Font32);
      LCD_SetColor( 0xff9DD3A8);  
      LCD_DisplayText(130,110,"反客");
      LCD_DisplayText(130,150,"科技");
 
      HAL_Delay(1000);	// 延时
	}
}


int main(void)
{
   SPI_LCD_Init();     	 	// 液晶屏以及SPI初始化 


  rt_uint32_t total, maxused, used;
  struct rt_timer timer1;
  printf("sys clock is %lu\r\n",HAL_RCC_GetSysClockFreq());
  printf("HCLK clock is %lu\r\n",HAL_RCC_GetHCLKFreq());
  rt_timer_init(&timer1,"timer1",mtimerout,RT_NULL,50,RT_TIMER_FLAG_PERIODIC);
  rt_timer_start(&timer1);
  rt_thread_init(&led1_thread, "led1", led1_thread_entry, RT_NULL, &rt_led1_thread_stack[0], 1024, 3, 20);
  rt_thread_startup(&led1_thread);

  struct rt_thread* led2_thread = rt_thread_create("led2", led1_thread2_entry, RT_NULL, 1024, 3, 20);
  rt_thread_startup(led2_thread);
  while(RT_TRUE)
  {
   	LCD_Test_Clear(); 		// 清屏测试
		LCD_Test_Text();			// 文本测试
		LCD_Test_Variable ();	// 变量显示，包括整数和小数
		LCD_Test_Color();			// 颜色测试
		LCD_Test_Grahic();		// 2D图形绘制	
		LCD_Test_Image();			// 图片显示
		LCD_Test_Direction();	// 更换显示方向
  }
}