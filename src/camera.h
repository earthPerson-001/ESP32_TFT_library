#pragma once

#include "esp_err.h"
#include "esp_camera.h"

#ifdef __cplusplus
extern "C"
{
#endif


// AI-Thinker PIN Map
#define CAM_PIN_PWDN 32  // power down is not used
#define CAM_PIN_RESET -1 // software reset will be performed
#define CAM_PIN_XCLK 0
#define CAM_PIN_SIOD 26
#define CAM_PIN_SIOC 27

#define CAM_PIN_D7 35
#define CAM_PIN_D6 34
#define CAM_PIN_D5 39
#define CAM_PIN_D4 36
#define CAM_PIN_D3 21
#define CAM_PIN_D2 19
#define CAM_PIN_D1 18
#define CAM_PIN_D0 5
#define CAM_PIN_VSYNC 25
#define CAM_PIN_HREF 23
#define CAM_PIN_PCLK 22

#define RFID_PHOTO_QUEUE_SIZE 10

#define JPEG_QUALITY 15

    esp_err_t camera_init();

    esp_err_t get_image(camera_fb_t **fb_ret);

    esp_err_t return_image(camera_fb_t *fb);


#ifdef __cplusplus
}
#endif