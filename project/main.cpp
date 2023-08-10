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
#include <iostream>
using namespace std;

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
      HAL_Delay(300);
      //printf("this thread tid is %s\r\n",rt_thread_self()->name);
    }
}

void led1_thread2_entry(void* p)
{

  while(1)
  {
    //rt_thread_delay(5000000);
	HAL_Delay(100);
    //printf("led2 off\r\n");
    led_off();
    
    //rt_thread_delay(500);
    //rt_thread_delay(5000000);
	HAL_Delay(100);
    //printf("led2 on\r\n");
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
int main(void)
{

  void* p =  rt_malloc(1024);
  int* p1 = new int;
  void* p2 = malloc(10);
  printf("p = %p\n",p);
  printf("p1 = %p\n",p1);
  printf("p2 = %p\n",p2);
  int a;
  cout << &a << endl;
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
	HAL_Delay(100);
	rt_thread_delay(100);
	//printf("what fuck ???\r\n");
  }
}