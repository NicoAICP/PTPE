#include "menu.h"
#include "hw.h"
#include "shared.h"
#include <stdio.h>
#include "ST7735_TFT.h"
#include "f_util.h"
#include "ff.h"
#include "hw_config.h"
#include "rtc.h"
#include "bsp/board.h"
#include "tusb.h"


char *names;
char test[100];
int fd_in_array(FIL *fd, FIL *array[], int len)
{
  for (int i = 0; i < len; i++)
  {
    if (array[i] == fd)
      return 1;
  }
  return 0;
}
int get_fd_in_array(FIL *fd, FIL *array[], int len)
{
  for (int i = 0; i < len; i++)
  {
    if (array[i] == fd)
      return i;
  }
  return 0;
}

int add_fd_to_array(FIL *fd, FIL *array[], int len)
{
  for (int i = 0; i < len; i++)
  {
    if (array[i] == 0)
    {
      array[i] = fd;
      return 1;
    }
  }
  return 0;
}

int remove_fd_from_array(FIL *fd, FIL *array[], int len)
{
  for (int i = 0; i < len; i++)
  {
    if (array[i] == fd)
    {
      array[i] = 0;
      if (i + 1 >= len) // last element
        return 1;
      if (array[i + 1] != 0)
      {
        int j;
        for (j = i + 1; j < len; j++)
        {
          array[j - 1] = array[j];
          if (array[j] == 0)
            break;
        }
        j--;
        if (j == len)
          array[j] = 0;
      }
      return 1;
    }
  }
  return 0;
}

char create_sense_bitmask(FIL *array[], int len)
{
  char ret = 0;
  for (int i = 0; i < len; i++)
  {
    if (array[i] == 0)
      break;
    ret |= 1 << i*2;
  }
  return ret;
}

int SkylanderEndsWith(char *str, char *suffix)
{
  int str_len = strlen(str);
  int suffix_len = strlen(suffix);

  return (str_len >= suffix_len) &&
         (0 == strcmp(str + (str_len - suffix_len), suffix));
}

void GetSkylanderCount(){
    FRESULT res;
    DIR dir;
    FILINFO fno;
    bool skylander = false;
    SkylanderCount = 0;

    f_opendir(&dir, "/Skylanders"); // Open Skylanders folder
    do
    {
    skylander = false;
    f_readdir(&dir, &fno);

    if (fno.fname[0] != 0)
    {

      if (SkylanderEndsWith(fno.fname, "bin") == 1 || SkylanderEndsWith(fno.fname, "sky") == 1 || SkylanderEndsWith(fno.fname, "dmp") == 1 || SkylanderEndsWith(fno.fname, "dump") == 1)
      {
        SkylanderCount++;
        sprintf(test, "/Skylanders/%s", fno.fname);
      }
      else
      {
        printf("File is not a Skylander: %s\n", fno.fname);
      }
    }

    } 
    while (fno.fname[0] != 0);
    f_closedir(&dir);
    sleep_ms(3000);
}

void handleSkylander(int selection){
    if(selection != 2)
    {
        
        drawMenu(0);
        if(selection == 0){

            if(SkylanderCount > 0)
            {
                FIL *newfile = calloc(1, sizeof(FIL));
                FRESULT fr = f_open(newfile, test, FA_OPEN_EXISTING | FA_READ | FA_WRITE);
                char *nbuffer;
                nbuffer = calloc(SKYLANDER_MSG_SIZE, 1);
                nbuffer[0] = 0x53;
                nbuffer[6] = 0x01;
                if (fr != FR_OK && fr != FR_EXIST)
                {
                    //Skylander not found or loaded
                }
                else
                {   
                    if (fd_in_array(newfile, loaded_skylanders, MAX_SKYLANDER_COUNT) == 0)
                    {
                        loaded_skylanders[0] = newfile;
                        nbuffer = calloc(SKYLANDER_MSG_SIZE, 1);
                        nbuffer[0] = 0x53;
                        nbuffer[1] = create_sense_bitmask(loaded_skylanders, MAX_SKYLANDER_COUNT);
                        nbuffer[5] = sense_counter++;
                        nbuffer[6] = 0x01;
                        tud_hid_report(0, nbuffer, SKYLANDER_MSG_SIZE);
                    //free(nbuffer);
                    }
                    else
                    {
                    //Skylander not found or loaded
                    }
                }
            }
        }else{
            drawText(5, 37, "Nothing to see here", ST7735_WHITE, ST7735_BLACK, 1);
        }
        SkylanderMenu(currSel, 0);
    }
    else
    {
        reboot();
    }
    
}

void SkylanderMenu(int cursor, int select){
            if(first_init == 0) {
                drawText(5, 37, "Loading...", ST7735_WHITE, ST7735_BLACK, 1);
                GetSkylanderCount();
                first_init = 1;
                
                drawMenu(0);
        }
    if(select == 1 ){
        handleSkylander(cursor);
    }
    else
    {
        switch(cursor){
            case 0:
                drawText(5, 37, "-  Add Skylander        <", ST7735_WHITE, ST7735_BLACK, 1);
                drawText(5, 49, "-  Remove Skylander      ", ST7735_WHITE, ST7735_BLACK, 1);
                drawText(5, 61, "-  Exit Emulation        ", ST7735_WHITE, ST7735_BLACK, 1);
                break;
            case 1:
                drawText(5, 37, "-  Add Skylander         ", ST7735_WHITE, ST7735_BLACK, 1);
                drawText(5, 49, "-  Remove Skylander     <", ST7735_WHITE, ST7735_BLACK, 1);
                drawText(5, 61, "-  Exit Emulation        ", ST7735_WHITE, ST7735_BLACK, 1);
            
                break;
            case 2:
                drawText(5, 37, "-  Add Skylander         ", ST7735_WHITE, ST7735_BLACK, 1);
                drawText(5, 49, "-  Remove Skylander      ", ST7735_WHITE, ST7735_BLACK, 1);
                drawText(5, 61, "-  Exit Emulation       <", ST7735_WHITE, ST7735_BLACK, 1);
                break;
        }
    }
}
