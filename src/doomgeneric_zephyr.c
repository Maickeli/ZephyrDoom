
#include "doomgeneric/doomkeys.h"

#include "doomgeneric/doomgeneric.h"

#include <stdio.h>

#include <zephyr/kernel.h>

#define KEYQUEUE_SIZE 16

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

static unsigned char convertToDoomKey(unsigned char key)
{
    /*switch (key)
    {
    case VK_RETURN:
        key = KEY_ENTER;
        break;
    case VK_ESCAPE:
        key = KEY_ESCAPE;
        break;
    case VK_LEFT:
        key = KEY_LEFTARROW;
        break;
    case VK_RIGHT:
        key = KEY_RIGHTARROW;
        break;
    case VK_UP:
        key = KEY_UPARROW;
        break;
    case VK_DOWN:
        key = KEY_DOWNARROW;
        break;
    case VK_CONTROL:
        key = KEY_FIRE;
        break;
    case VK_SPACE:
        key = KEY_USE;
        break;
    case VK_SHIFT:
        key = KEY_RSHIFT;
        break;
    default:
        key = tolower(key);
        break;
    }
*/
    return key;
}

static void addKeyToQueue(int pressed, unsigned char keyCode)
{
    unsigned char key = convertToDoomKey(keyCode);

    unsigned short keyData = (pressed << 8) | key;

    s_KeyQueue[s_KeyQueueWriteIndex] = keyData;
    s_KeyQueueWriteIndex++;
    s_KeyQueueWriteIndex %= KEYQUEUE_SIZE;
}


void DG_Init()
{


}

void DG_DrawFrame()
{


    //StretchDIBits(s_Hdc, 0, 0, DOOMGENERIC_RESX, DOOMGENERIC_RESY, 0, 0, DOOMGENERIC_RESX, DOOMGENERIC_RESY, DG_ScreenBuffer, &s_Bmi, 0, SRCCOPY);

}

void DG_SleepMs(uint32_t ms)
{
    k_sleep(K_MSEC(ms));
}

uint32_t DG_GetTicksMs()
{
    return k_uptime_get();
}

int DG_GetKey(int* pressed, unsigned char* doomKey)
{
    if (s_KeyQueueReadIndex == s_KeyQueueWriteIndex)
    {
        //key queue is empty

        return 0;
    }
    else
    {
        unsigned short keyData = s_KeyQueue[s_KeyQueueReadIndex];
        s_KeyQueueReadIndex++;
        s_KeyQueueReadIndex %= KEYQUEUE_SIZE;

        *pressed = keyData >> 8;
        *doomKey = keyData & 0xFF;

        return 1;
    }
}

void DG_SetWindowTitle(const char * title)
{

}

