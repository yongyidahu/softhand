#include "hal_i2c_ctrl.h"

I2CTypedef i2c[cfgI2C_LIGHT_NUM];    //I2C灯控制
static void hal_i2c_definit(int idx);
static void i2c_gpio_init(int idx);
static uint8_t i2c_get_sda(int idx);
/*******************
 *    i2c初始化 
 ******************/
void hal_i2c_init(int idx){
      hal_i2c_definit(I2C_BLIGHT_LEFT);
      hal_i2c_definit(I2C_BLIGHT_RIGHT);
      hal_i2c_definit(I2C_BLIGHT_FRONT);
}

void hal_i2c_definit(int idx){
    switch(idx){
         case I2C_BLIGHT_LEFT:{
            i2c[I2C_BLIGHT_LEFT].idx=I2C_BLIGHT_LEFT;
            i2c[I2C_BLIGHT_LEFT].gpio.sclPort=cfgLBLIGHT_SCL_PORT;
            i2c[I2C_BLIGHT_LEFT].gpio.sclPin=cfgLBLIGHT_SCL_PIN;
            i2c[I2C_BLIGHT_LEFT].gpio.sdaPort=cfgLBLIGHT_SDA_PORT;
            i2c[I2C_BLIGHT_LEFT].gpio.sdaPin=cfgLBLIGHT_SDA_PIN;
            i2c[I2C_BLIGHT_LEFT].gpio.rstPort=cfgLBLIGHT_RST_PORT;
            i2c[I2C_BLIGHT_LEFT].gpio.rstPin=cfgLBLIGHT_RST_PIN; 
         }break;
         
         case I2C_BLIGHT_RIGHT:{
            i2c[I2C_BLIGHT_RIGHT].idx=I2C_BLIGHT_RIGHT;
            i2c[I2C_BLIGHT_RIGHT].gpio.sclPort=cfgRBLIGHT_SCL_PORT;
            i2c[I2C_BLIGHT_RIGHT].gpio.sclPin=cfgRBLIGHT_SCL_PIN;
            i2c[I2C_BLIGHT_RIGHT].gpio.sdaPort=cfgRBLIGHT_SDA_PORT;
            i2c[I2C_BLIGHT_RIGHT].gpio.sdaPin=cfgRBLIGHT_SDA_PIN;
            i2c[I2C_BLIGHT_RIGHT].gpio.rstPort=cfgRBLIGHT_RST_PORT;
            i2c[I2C_BLIGHT_RIGHT].gpio.rstPin=cfgRBLIGHT_RST_PIN; 
         }break;
         
         case I2C_BLIGHT_FRONT:{
            i2c[I2C_BLIGHT_FRONT].idx=I2C_BLIGHT_FRONT;
            i2c[I2C_BLIGHT_FRONT].gpio.sclPort=cfgFBLIGHT_SCL_PORT;
            i2c[I2C_BLIGHT_FRONT].gpio.sclPin=cfgFBLIGHT_SCL_PIN;
            i2c[I2C_BLIGHT_FRONT].gpio.sdaPort=cfgFBLIGHT_SDA_PORT;
            i2c[I2C_BLIGHT_FRONT].gpio.sdaPin=cfgFBLIGHT_SDA_PIN;
            i2c[I2C_BLIGHT_FRONT].gpio.rstPort=cfgFBLIGHT_RST_PORT;
            i2c[I2C_BLIGHT_FRONT].gpio.rstPin=cfgFBLIGHT_RST_PIN; 
         }break;
         default:{
         
         }break;
     }
    i2c_gpio_init(idx);
}


void i2c_gpio_init(int idx){
      //都设置成输出模式
    gpio_init(i2c[idx].gpio.sclPort,GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,i2c[idx].gpio.sclPin);
    gpio_init(i2c[idx].gpio.sdaPort,GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,i2c[idx].gpio.sdaPin);
    gpio_init(i2c[idx].gpio.rstPort,GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,i2c[idx].gpio.rstPin);
    gpio_bit_set(i2c[idx].gpio.sclPort,i2c[idx].gpio.sclPin);
    gpio_bit_set(i2c[idx].gpio.sdaPort,i2c[idx].gpio.sdaPin);
    gpio_bit_set(i2c[idx].gpio.rstPort,i2c[idx].gpio.rstPin);
}

void i2c_sda_out(int idx){ // SDA作为输出
     gpio_afio_deinit();
     gpio_init(i2c[idx].gpio.sdaPort,GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,i2c[idx].gpio.sdaPin);
}

void i2c_sda_in(int idx){   // SDA作为输入
     gpio_afio_deinit();
     gpio_init(i2c[idx].gpio.sdaPort,GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ,i2c[idx].gpio.sdaPin);
}

void i2c_scl_set(int idx){
     gpio_bit_set(i2c[idx].gpio.sclPort,i2c[idx].gpio.sclPin);
}


void i2c_scl_reset(int idx){
     gpio_bit_reset(i2c[idx].gpio.sclPort,i2c[idx].gpio.sclPin);
}

void i2c_sda_set(int idx){
     gpio_bit_set(i2c[idx].gpio.sdaPort,i2c[idx].gpio.sdaPin);
}

void i2c_sda_reset(int idx){
     gpio_bit_reset(i2c[idx].gpio.sdaPort,i2c[idx].gpio.sdaPin);
}

static uint8_t i2c_get_sda(idx){
    return gpio_output_bit_get(i2c[idx].gpio.sdaPort,i2c[idx].gpio.sdaPin);
}

void i2c_hw_reset(int idx){//硬件复位
    gpio_bit_reset(i2c[idx].gpio.rstPort,i2c[idx].gpio.rstPin);
    i2c_delay(100);
    gpio_bit_set(i2c[idx].gpio.rstPort,i2c[idx].gpio.rstPin);
    i2c_delay(10);
}

/***************************
 *    开始I2C通信
 ***************************/
void i2c_start(int idx){
     i2c_sda_set(idx);
     i2c_scl_set(idx);
     i2c_delay(2);
     i2c_sda_reset(idx);
     i2c_delay(2);
     i2c_scl_reset(idx);
     i2c_delay(2);
}

/***************************
 *    I2C 通信停止
 **************************/
void i2c_stop(int idx){
     i2c_scl_reset(idx);
     i2c_delay(2);
     i2c_scl_set(idx);
     i2c_delay(2);
     i2c_sda_set(idx);
}

/***************************
 *         写数据
 **************************/
uint8_t i2c_write_data(int idx,uint8_t val){
    uint8_t i=0;
    uint8_t data=val;
    i2c_sda_out(idx);
    i2c_delay(1);
    i2c_scl_reset(idx);
    for(i=0;i<8;i++){
      if(((data>>i)&0x01)==1){
         i2c_sda_set(idx);   // 设置输出高
      }else{ 
         i2c_sda_reset(idx); // 设置输出低电平
      }
      i2c_delay(1);
      i2c_scl_set(idx);
      i2c_delay(1);
      i2c_scl_reset(idx);
    }
    return 0;
}
/**************************
 *         读取数据
 *************************/
uint8_t i2c_read_data(int idx){
    uint8_t data=0,i=0;
    i2c_sda_in(idx);
    for(i=0;i<8;i++){
       data<<=1;
       i2c_delay(3);
       i2c_scl_set(idx); 
        if(i2c_get_sda(idx)==SET){
          data|=0x01;
        }else{
          data&=0xfe;   
        }
       i2c_delay(1);
       i2c_scl_reset(idx);
    }
    i2c_scl_set(idx); 
    i2c_delay(2);
    i2c_scl_reset(idx); 
    i2c_delay(2);
    return data;
}



/**********************
 *    等待ACK
 *********************/
uint8_t i2c_wait_ack(int idx){
    uint8_t ucErrTime=0;
    i2c_sda_in(idx);
    i2c_sda_set(idx);
    i2c_delay(1);
    i2c_scl_set(idx);
    while(i2c_get_sda(idx)){
      ucErrTime++;
      if(ucErrTime>=250){
         i2c_stop(idx);
         return 0;
      }
    }
    i2c_scl_reset(idx);
    i2c_delay(1);
    return 1;
}



/**********************
 *     延时函数
 *********************/
void i2c_delay(uint16_t us){
    uint16_t i=0;
    for(i=0;i<us*cfgSYS_FREQ;i++);
}










