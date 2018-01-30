#include "hal_breath_light.h"

void hal_blight_init(void){


}


uint8_t blight_reg_write(int idx,uint8_t reg,uint8_t val){
    uint8_t ack=0;
    i2c_start(idx);
    i2c_write_data(idx,reg);
    ack=i2c_wait_ack(idx);
    if(!ack){
       //没有获取到数据响应
        i2c_stop(idx);
        return 0;
    }
    i2c_write_data(idx,val);
      if(!ack){
       //没有获取到数据响应
        i2c_stop(idx);
        return 0;
    }
    i2c_stop(idx);
    return 1;
}

void blight_hw_reset(int idx){
     i2c_hw_reset(idx);
}

void bright_sf_reset(int idx){

}
