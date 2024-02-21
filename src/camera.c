#include "driver/sdmmc_types.h"
#include "lwip/netdb.h"
#include "ping/ping_sock.h"
#include "inttypes.h"

#include "esp_camera.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_spiffs.h"

#include "freertos/task.h"
#include "freertos/event_groups.h"

// local includes
#include "camera.h"
//---------------

static const char *TAG = "CAMERA";

static camera_config_t camera_config = {
    .pin_pwdn = CAM_PIN_PWDN,
    .pin_reset = CAM_PIN_RESET,
    .pin_xclk = CAM_PIN_XCLK,
    .pin_sccb_sda = CAM_PIN_SIOD,
    .pin_sccb_scl = CAM_PIN_SIOC,

    .pin_d7 = CAM_PIN_D7,
    .pin_d6 = CAM_PIN_D6,
    .pin_d5 = CAM_PIN_D5,
    .pin_d4 = CAM_PIN_D4,
    .pin_d3 = CAM_PIN_D3,
    .pin_d2 = CAM_PIN_D2,
    .pin_d1 = CAM_PIN_D1,
    .pin_d0 = CAM_PIN_D0,
    .pin_vsync = CAM_PIN_VSYNC,
    .pin_href = CAM_PIN_HREF,
    .pin_pclk = CAM_PIN_PCLK,

    .xclk_freq_hz = 16500000, // https://github.com/espressif/esp32-camera/issues/150
                              // EXPERIMENTAL: Set to 16MHz on ESP32-S2 or ESP32-S3 to enable EDMA mode
    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,

    .pixel_format = PIXFORMAT_JPEG, // YUV422,GRAYSCALE,RGB565,JPEG
    .frame_size = FRAMESIZE_HVGA,   // QQVGA-UXGA, For ESP32, do not use sizes above QVGA when not JPEG. The performance of the ESP32-S series has improved a lot, but JPEG mode always gives better frame rates.
    // use higher quality initially as described in : https://github.com/espressif/esp32-camera/issues/185#issue-716800775
    .jpeg_quality = JPEG_QUALITY, // 0-63, for OV series camera sensors, lower number means higher quality
    .fb_count = 2,      // When jpeg mode is used, if fb_count more than one, the driver will work in continuous mode.
    .fb_location = CAMERA_FB_IN_DRAM,
    .grab_mode = CAMERA_GRAB_LATEST, // CAMERA_GRAB_LATEST. Sets when buffers should be filled
    .sccb_i2c_port = 0};

esp_err_t camera_init()
{
    // initialize the camera
    esp_err_t err = esp_camera_init(&camera_config);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Camera Init Failed");
        return err;
    }

    return ESP_OK;
}

esp_err_t get_image(camera_fb_t **fb_ret)
{
    // now use lower quality as described in : https://github.com/espressif/esp32-camera/issues/185#issue-716800775
    // sensor_t *ss = esp_camera_sensor_get();
    // ss->set_quality(ss, JPEG_QUALITY);

    *fb_ret = esp_camera_fb_get();

    return (fb_ret == NULL) ? ESP_ERR_NOT_FOUND : ESP_OK;
}

esp_err_t return_image(camera_fb_t *fb)
{
    esp_camera_fb_return(fb);

    return ESP_OK; // just for consistency
}