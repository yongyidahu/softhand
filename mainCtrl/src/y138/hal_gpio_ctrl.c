#include "hal_gpio_ctrl.h"


static void hal_clk_init(void);
LEDCtrl_typedef ledCtrl;


/************************
 *       gpio控制方法
 ***********************/

void hal_clk_init(void){
    /****************************
     *    io 口时钟
     ****************************/
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_AF);
}

/*********************
 *   I2C作为输入输出
 ********************/
void blight_gpio_init(void){
 
}

void led_gpio_init(void){
   memset(&ledCtrl,0,sizeof(LEDCtrl_typedef));
   gpio_init(cfgLED_GPIO_PORT,GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,cfgLED_GPIO_PIN);
   gpio_bit_set(cfgLED_GPIO_PORT,cfgLED_GPIO_PIN); 
}


void led_on_off(void){
   ledCtrl.togTime++;
   if(ledCtrl.togTime>=cfgLED_TOG_TIME){
     ledCtrl.togTime=0;
      if(ledCtrl.state==LED_ON){
         ledCtrl.state=LED_OFF;
         gpio_bit_set(cfgLED_GPIO_PORT,cfgLED_GPIO_PIN); 
     }else{
         ledCtrl.state=LED_ON;
         gpio_bit_reset(cfgLED_GPIO_PORT,cfgLED_GPIO_PIN); 
     }
   }
}

void led_off(void){
  gpio_bit_set(cfgLED_GPIO_PORT,cfgLED_GPIO_PIN); 
}

void led_on(void){
  gpio_bit_reset(cfgLED_GPIO_PORT,cfgLED_GPIO_PIN); 
}


/*********************
 *    舵机电源初始化 
 ********************/
void servo_power_init(void){



}

void servo_pwm_init(){

    
}

/***************************
 *          串口GPI初始化O
 **************************/
void uart_gpio_init(){

  
}

/**************************
 *    can 总线初始化
 **************************/
void can_gpio_init(){

}



/*******************
 *   GPIO 初始化
 ******************/
void hal_gpio_init(void){
    hal_clk_init();
    blight_gpio_init();
    led_gpio_init();
    servo_power_init();
    servo_pwm_init();
    uart_gpio_init();
}

















