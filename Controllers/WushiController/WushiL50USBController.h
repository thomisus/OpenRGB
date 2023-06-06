/*-------------------------------------*\
|  WushiL50USBController.h              |
|                                       |
|  interface for Wushi L50 Devices      |
\*-------------------------------------*/

#pragma once

#include "RGBController.h"

#include <string>
#include <hidapi/hidapi.h>

#ifndef HID_MAX_STR
#define HID_MAX_STR                 255
#endif

#define WUSHI_L50_HID_PACKET_SIZE   33
#define WUSHI_L50_NUM_LEDS          4

enum WUSHI_L50_EFFECT
{
    WUSHI_L50_EFFECT_STATIC         = 1,    /* Static mode              */
    WUSHI_L50_EFFECT_BREATH         = 3,    /* Breathing mode           */
    WUSHI_L50_EFFECT_WAVE           = 4,    /* Wave mode                */
    WUSHI_L50_EFFECT_SMOOTH         = 6,    /* Smooth mode              */
    WUSHI_L50_EFFECT_RACE           = 8,    /* Race mode                */
    WUSHI_L50_EFFECT_STACK          = 10,   /* Stack mode               */
};

enum WUSHI_L50_BRIGHTNESS
{
    WUSHI_L50_BRIGHTNESS_LOW        = 1,    /* Low brightness           */
    WUSHI_L50_BRIGHTNESS_HIGH       = 2,    /* High brightness          */
};

enum WUSHI_L50_SPEED
{
    WUSHI_L50_SPEED_SLOWEST         = 1,    /* Slowest speed            */
    WUSHI_L50_SPEED_SLOW            = 2,    /* Slow speed               */
    WUSHI_L50_SPEED_FAST            = 3,    /* Fast speed               */
    WUSHI_L50_SPEED_FASTEST         = 4,    /* Fastest speed            */
};

enum WUSHI_L50_Direction
{
    WUSHI_L50_Direction_LEFT        = 1,    /* Left direction           */
    WUSHI_L50_Direction_RIGHT       = 2,    /* Right direction          */
};

class WushiL50State
{
public:
    uint8_t header[2]               = {0xCC, 0x16};
    uint8_t effect                  = WUSHI_L50_EFFECT_STATIC;
    uint8_t speed                   = WUSHI_L50_SPEED_SLOWEST;
    uint8_t brightness              = WUSHI_L50_BRIGHTNESS_LOW;
    uint8_t zone0_rgb[3]            = {0xFF, 0xFF, 0xFF};
    uint8_t zone1_rgb[3]            = {0xFF, 0xFF, 0xFF};
    uint8_t zone2_rgb[3]            = {0xFF, 0xFF, 0xFF};
    uint8_t zone3_rgb[3]            = {0xFF, 0xFF, 0xFF};
    uint8_t padding                 = 0;
    uint8_t wave_ltr                = 0;
    uint8_t wave_rtl                = 0;
    uint8_t unused[13]              = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    void Reset()
    {
        header[0]                   = 0xCC;
        header[1]                   = 0x16;
        effect                      = WUSHI_L50_EFFECT_STATIC;
        speed                       = WUSHI_L50_SPEED_SLOWEST;
        brightness                  = WUSHI_L50_BRIGHTNESS_LOW;
        padding                     = 0;
        wave_ltr                    = 0;
        wave_rtl                    = 0;

        for(int i = 0; i < 13; ++i)
        {
            unused[i]               = 0;
        }
    }

    void SetColors(std::vector<RGBColor> group_colors)
    {
        zone0_rgb[0]                = RGBGetRValue(group_colors[0]);
        zone0_rgb[1]                = RGBGetGValue(group_colors[0]);
        zone0_rgb[2]                = RGBGetBValue(group_colors[0]);
        zone1_rgb[0]                = RGBGetRValue(group_colors[1]);
        zone1_rgb[1]                = RGBGetGValue(group_colors[1]);
        zone1_rgb[2]                = RGBGetBValue(group_colors[1]);
        zone2_rgb[0]                = RGBGetRValue(group_colors[2]);
        zone2_rgb[1]                = RGBGetGValue(group_colors[2]);
        zone2_rgb[2]                = RGBGetBValue(group_colors[2]);
        zone3_rgb[0]                = RGBGetRValue(group_colors[3]);
        zone3_rgb[1]                = RGBGetGValue(group_colors[3]);
        zone3_rgb[2]                = RGBGetBValue(group_colors[3]);

        wave_rtl                    = 0;
    }
};

class WushiL50USBController
{
public:
    WushiL50USBController(hid_device* dev_handle, const char* path);
    ~WushiL50USBController();

    void        setMode(WushiL50State * in_mode);

    std::string getName();
    std::string getLocation();
    std::string GetSerialString();

private:
    std::string     name;
    hid_device *    dev;
    std::string     location;
    std::string     serial_number;
};
