/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

/**
 * lcd/extui/dgus/dgus_extui.cpp
 */

#include "../../../inc/MarlinConfigPre.h"

#if HAS_DGUS_LCD_CLASSIC

#include "../ui_api.h"
#include "DGUSDisplay.h"
#include "DGUSDisplayDef.h"
#include "DGUSScreenHandler.h"

namespace ExtUI {


  void onStartup() {
    dgusdisplay.InitDisplay();
    ScreenHandler.UpdateScreenVPData();
  }

  void onIdle() { ScreenHandler.loop();}
    // void onIdle() { }

  void onPrinterKilled(FSTR_P const error, FSTR_P const) {
    ScreenHandler.sendinfoscreen(GET_TEXT_F(MSG_HALTED), error, FPSTR(NUL_STR), GET_TEXT_F(MSG_PLEASE_RESET), true, true, true, true);
    // ScreenHandler.GotoScreen(DGUSLCD_SCREEN_KILL);
    while (!ScreenHandler.loop());  // Wait while anything is left to be sent
  }

  void onMediaInserted() { TERN_(SDSUPPORT, ScreenHandler.SDCardInserted()); }
  void onMediaError()    { TERN_(SDSUPPORT, ScreenHandler.SDCardError()); }
  void onMediaRemoved()  { TERN_(SDSUPPORT, ScreenHandler.SDCardRemoved()); }

  void onPlayTone(const uint16_t frequency, const uint16_t duration) {}
  void onPrintTimerStarted() {}
  void onPrintTimerPaused() {}
  void onPrintTimerStopped() {}
  void onFilamentRunout(const extruder_t extruder) {}

  void onUserConfirmRequired(const char * const msg) {
    if (msg) {
      ScreenHandler.sendinfoscreen(F("Please confirm."), nullptr, msg, nullptr, true, true, false, true);
      ScreenHandler.SetupConfirmAction(setUserConfirmed);
      // ScreenHandler.GotoScreen(DGUSLCD_SCREEN_POPUP);
    }
    // else if (ScreenHandler.getCurrentScreen() == DGUSLCD_SCREEN_POPUP) {
    //   ScreenHandler.SetupConfirmAction(nullptr);
    //   ScreenHandler.PopToOldScreen();
    // }
  }

  void onStatusChanged(const char * const msg) { ScreenHandler.setstatusmessage(msg); }

  void onHomingStart() 
  {
      if(lcd_info.Screen_now==Screen_control)
      {
          if(lcd_info.language == (language_t)1)
          {
               ScreenHandler.GotoScreen(DGUSLCD_SCREEN_GOHOME);
          }
          else if(lcd_info.language == (language_t)2)
          {
            ScreenHandler.GotoScreen(DGUSLCD_Screens(64));
          }
          else if(lcd_info.language == (language_t)3)
          {
            ScreenHandler.GotoScreen(DGUSLCD_Screens(101));
          }
          else if(lcd_info.language == (language_t)4)
          {
            ScreenHandler.GotoScreen(DGUSLCD_Screens(138));
          }
          else if(lcd_info.language == (language_t)5)
          {
            ScreenHandler.GotoScreen(DGUSLCD_Screens(175));
          }
          else if(lcd_info.language == (language_t)6)
          {
            ScreenHandler.GotoScreen(DGUSLCD_Screens(213));
          }
      }
      if(lcd_info.Screen_now == Screen_abort)
      {
          if(lcd_info.language == (language_t)1)
          {
             ScreenHandler.GotoScreen(DGUSLCD_Screens(30));
          }
          else if(lcd_info.language == (language_t)2)
          {
            ScreenHandler.GotoScreen(DGUSLCD_Screens(66));
          }
          else if(lcd_info.language == (language_t)3)
          {
            ScreenHandler.GotoScreen(DGUSLCD_Screens(103));
          }
          else if(lcd_info.language == (language_t)4)
          {
            ScreenHandler.GotoScreen(DGUSLCD_Screens(140));
          }
          else if(lcd_info.language == (language_t)5)
          {
            ScreenHandler.GotoScreen(DGUSLCD_Screens(177));
          }
          else if(lcd_info.language == (language_t)6)
          {
            ScreenHandler.GotoScreen(DGUSLCD_Screens(215));
          }
      }
      
  }
void onHomingComplete() 
{
     if(lcd_info.Screen_now==Screen_control)
     {
       if(lcd_info.language == (language_t)1)
       {
        ScreenHandler.GotoScreen(DGUSLCD_SCREEN_CONTROL);
       }
      else if(lcd_info.language ==(language_t)2)
      {
         ScreenHandler.GotoScreen(DGUSLCD_Screens(42));
      }
        else if(lcd_info.language ==(language_t)3)
      {
         ScreenHandler.GotoScreen(DGUSLCD_Screens(77));
      }
        else if(lcd_info.language ==(language_t)4)
      {
         ScreenHandler.GotoScreen(DGUSLCD_Screens(117));
      }
        else if(lcd_info.language ==(language_t)5)
      {
         ScreenHandler.GotoScreen(DGUSLCD_Screens(152));
      }
        else if(lcd_info.language ==(language_t)6)
      {
         ScreenHandler.GotoScreen(DGUSLCD_Screens(192));
      }
        lcd_info.Screen_now =Screen_null;
     }
     if(lcd_info.Screen_now == Screen_abort)
     {
        if(lcd_info.language == (language_t)1)
        {
           ScreenHandler.GotoScreen(DGUSLCD_SCREEN_SDFILELIST);
        }
        else if(lcd_info.language == (language_t)2)
        {
          ScreenHandler.GotoScreen(DGUSLCD_SCREEN_EN_SDFILELIST);
        }
        else if(lcd_info.language ==(language_t)3)
        {
          ScreenHandler.GotoScreen(DGUSLCD_Screens(76));
        }
          else if(lcd_info.language ==(language_t)4)
        {
          ScreenHandler.GotoScreen(DGUSLCD_Screens(116));
        }
          else if(lcd_info.language ==(language_t)5)
        {
          ScreenHandler.GotoScreen(DGUSLCD_Screens(151));
        }
          else if(lcd_info.language ==(language_t)6)
        {
          ScreenHandler.GotoScreen(DGUSLCD_Screens(191));
        }
          lcd_info.Screen_now =Screen_null;
     }
    // ScreenHandler.PopToOldScreen();
}
  void onPrintFinished() 
  {
     if(lcd_info.language == (language_t)1)
        ScreenHandler.GotoScreen(DGUSLCD_SCREEN_SDFILELIST);
        else if(lcd_info.language == (language_t)2)
        ScreenHandler.GotoScreen(DGUSLCD_SCREEN_EN_SDFILELIST);
        else if(lcd_info.language == (language_t)3)
        ScreenHandler.GotoScreen(DGUSLCD_SCREEN_ES_SDFILELIST);
        else if(lcd_info.language == (language_t)4)
        ScreenHandler.GotoScreen(DGUSLCD_SCREEN_FR_SDFILELIST);
        else if(lcd_info.language == (language_t)5)
        ScreenHandler.GotoScreen(DGUSLCD_SCREEN_DE_SDFILELIST);
        else if(lcd_info.language == (language_t)6)
        ScreenHandler.GotoScreen(DGUSLCD_SCREEN_PY_SDFILELIST);
  }

  void onFactoryReset() {}

  void onStoreSettings(char *buff) {
    // Called when saving to EEPROM (i.e. M500). If the ExtUI needs
    // permanent data to be stored, it can write up to eeprom_data_size bytes
    // into buff.

    // Example:
    //  static_assert(sizeof(myDataStruct) <= eeprom_data_size);
    //  memcpy(buff, &myDataStruct, sizeof(myDataStruct));
  }

  void onLoadSettings(const char *buff) {
    // Called while loading settings from EEPROM. If the ExtUI
    // needs to retrieve data, it should copy up to eeprom_data_size bytes
    // from buff

    // Example:
    //  static_assert(sizeof(myDataStruct) <= eeprom_data_size);
    //  memcpy(&myDataStruct, buff, sizeof(myDataStruct));
  }

  void onPostprocessSettings() {
    // Called after loading or resetting stored settings
  }

  void onConfigurationStoreWritten(bool success) {
    // Called after the entire EEPROM has been written,
    // whether successful or not.
  }

  void onConfigurationStoreRead(bool success) {
    // Called after the entire EEPROM has been read,
    // whether successful or not.
  }

  #if HAS_MESH
    void onMeshLevelingStart() 
    {
       lcd_info.level_pos = 0;
       lcd_info.level_start = 1;
    }

    void onMeshUpdate(const int8_t xpos, const int8_t ypos, const_float_t zval) {
     
      // Called when any mesh points are updated
    
        lcd_info.level_pos=lcd_info.level_pos+1;
       dgusdisplay.WriteVariable(0x5700,(uint16_t)lcd_info.level_pos);
       if(lcd_info.level_pos>=25)
      { 
        if(lcd_info.language ==(language_t)1)
        dgusdisplay.WriteVariable(0x3300,(uint16_t)1);
        else if(lcd_info.language == (language_t)2)
        dgusdisplay.WriteVariable(0x3302,(uint16_t)1);
        else if(lcd_info.language == (language_t)3)
        dgusdisplay.WriteVariable(0x3304,(uint16_t)1);
        else if(lcd_info.language == (language_t)4)
        dgusdisplay.WriteVariable(0x3306,(uint16_t)1);
        else if(lcd_info.language == (language_t)5)
        dgusdisplay.WriteVariable(0x3308,(uint16_t)1);
          else if(lcd_info.language == (language_t)6)
        dgusdisplay.WriteVariable(0x330A,(uint16_t)1);
        lcd_info.level_pos = 0;
        lcd_info.level_start=0;
      }
    }

    void onMeshUpdate(const int8_t xpos, const int8_t ypos, const probe_state_t state) {
      // Called to indicate a special condition
    }
  #endif

  #if ENABLED(POWER_LOSS_RECOVERY)
    void onPowerLossResume() {
      // Called on resume from power-loss
      // IF_DISABLED(DGUS_LCD_UI_MKS, ScreenHandler.GotoScreen(DGUSLCD_SCREEN_POWER_LOSS));
      if(lcd_info.language == (language_t)1)
      {
        ScreenHandler.GotoScreen(DGUSLCD_SCREEN_POWER_LOSS);
      }
      else if(lcd_info.language == (language_t)2)
      {
        ScreenHandler.GotoScreen(DGUSLCD_SCREEN_EN_POWER_LOSS);
      }
    }
  #endif

  #if HAS_PID_HEATING
    void onPidTuning(const result_t rst) {
      // Called for temperature PID tuning result
      switch (rst) {
        case PID_STARTED:
          ScreenHandler.setstatusmessagePGM(GET_TEXT(MSG_PID_AUTOTUNE));
          break;
        case PID_BAD_EXTRUDER_NUM:
          ScreenHandler.setstatusmessagePGM(GET_TEXT(MSG_PID_BAD_EXTRUDER_NUM));
          break;
        case PID_TEMP_TOO_HIGH:
          ScreenHandler.setstatusmessagePGM(GET_TEXT(MSG_PID_TEMP_TOO_HIGH));
          break;
        case PID_TUNING_TIMEOUT:
          ScreenHandler.setstatusmessagePGM(GET_TEXT(MSG_PID_TIMEOUT));
          break;
        case PID_DONE:
          ScreenHandler.setstatusmessagePGM(GET_TEXT(MSG_PID_AUTOTUNE_DONE));
          break;
      }
      ScreenHandler.GotoScreen(DGUSLCD_SCREEN_MAIN);
    }
  #endif

  void onSteppersDisabled() {}
  void onSteppersEnabled()  {}
}

#endif // HAS_DGUS_LCD_CLASSIC
