/*

calibration menu:

enter by pressing left encoder button during start up; follow the instructions


*/

#define CALIB_MENU_ITEMS 12

char *calib_menu_strings[CALIB_MENU_ITEMS] = {

   "--> calibrate:", 
   "trim center value:", 
   "trim to 1 volts", 
   "trim to 2 volts", 
   "trim to 3 volts", 
   "trim to 4 volts",
   "trim to 6 volts",
   "trim to 7 volts",
   "trim to 8 volts",
   "trim to 9 volts",
   "trim to 10 volts",
   "done?"
};

enum STEPS {
  
  HELLO,
  CENTRE,
  VOLT_1,
  VOLT_2,
  VOLT_3,
  VOLT_4,
  VOLT_6,
  VOLT_7,
  VOLT_8,
  VOLT_9,
  VOLT_10,
  CHECK
};  


uint8_t _steps = 0;
uint16_t DAC_output;
int32_t encoder_data;

/*        loop calibration menu until we're done       */

void calibrate_main() {
  
        UImode = CALIBRATE;
        MENU_REDRAW = 1;
        _steps = 0;
            
        u8g.setFont(u8g_font_6x12);
        u8g.setColorIndex(1);
        u8g.setFontRefHeightText();
        u8g.setFontPosTop();
       
        while(UImode == CALIBRATE) {
         
             UI();
             delay(20);
             MENU_REDRAW = 1;
             
             /* advance in menu or exit */
             
             if (_steps >= CHECK) { 
                      
                       if (millis() - LAST_BUT > DEBOUNCE && !digitalRead(butR)) {
                         
                            UImode = SCREENSAVER;
                            LAST_BUT = millis();
                       }
             } 
             else if (millis() - LAST_BUT > DEBOUNCE && !digitalRead(butR)) { 
                       
                             _steps++;   
                             if (_steps > CENTRE && _steps < VOLT_6) encoder[RIGHT].setPos(octaves[_steps-1]);
                             else if (_steps > VOLT_4) encoder[RIGHT].setPos(octaves[_steps]);
                             LAST_BUT = millis(); 
             }
             
             encoder_data = encoder[RIGHT].pos();
             if (encoder_data >= MAX_VALUE) encoder[RIGHT].setPos(MAX_VALUE);
        } 
        encoder[RIGHT].setPos(0);
        UImode = SCREENSAVER;  
}


void calibrate() {
  
    u8g.drawStr(10, 10, calib_menu_strings[_steps]); 
    
    switch (_steps) {
      
      case HELLO: { 
        
          u8g.drawStr(10, 30, "use encoder (R)");
          u8g.drawStr(10, 50, "switch: left pos.");
          set8565_CHA(octaves[5]); // ch A >> 
          set8565_CHB(octaves[5]); // ch B >>
          set8565_CHC(octaves[5]); // ch C >>
          set8565_CHD(octaves[5]); // ch D >>
          break;
      }
      
      case CENTRE: {
        
          u8g.drawStr(10, 30, "- > 5.000V");  
          u8g.drawStr(10, 50, "use trimpots!");  
          break;   
      }  
      
      case VOLT_1: {
          u8g.drawStr(10, 30, "- > 1.000V /");
          u8g.setPrintPos(87, 30);
          u8g.print(encoder_data);
          u8g.drawStr(10, 50, "use encoder!");  
          break;   
      } 
      
      case VOLT_2: {
          u8g.drawStr(10, 30, "- > 2.000V /");
          u8g.setPrintPos(87, 30);
          u8g.print(encoder_data);
          u8g.drawStr(10, 50, "use encoder!");  
          break;   
      } 
      
      case VOLT_3: {
          u8g.drawStr(10, 30, "- > 3.000V /");
          u8g.setPrintPos(87, 30);
          u8g.print(encoder_data);
          u8g.drawStr(10, 50, "use encoder!");  
        break;   
      } 
      
      case VOLT_4: {
          u8g.drawStr(10, 30, "- > 4.000V /");
          u8g.setPrintPos(87, 30);
          u8g.print(encoder_data);
          u8g.drawStr(10, 50, "use encoder!");  
        break;   
      }
      
      case VOLT_6: {
          u8g.drawStr(10, 30, "- > 6.000V /");
          u8g.setPrintPos(87, 30);
          u8g.print(encoder_data);
          u8g.drawStr(10, 50, "use encoder!");  
        break;   
      } 
      
      case VOLT_7: {
          u8g.drawStr(10, 30, "- > 7.000V /");
          u8g.setPrintPos(87, 30);
          u8g.print(encoder_data);
          u8g.drawStr(10, 50, "use encoder!");  
        break;   
      } 
      
      case VOLT_8: {
          u8g.drawStr(10, 30, "- > 8.000V /");
          u8g.setPrintPos(87, 30);
          u8g.print(encoder_data);
          u8g.drawStr(10, 50, "use encoder!");  
        break;   
      } 
      
      case VOLT_9: {
          u8g.drawStr(10, 30, "- > 9.000V /");
          u8g.setPrintPos(87, 30);
          u8g.print(encoder_data);
          u8g.drawStr(10, 50, "use encoder!");  
        break;   
      } 
      
      case VOLT_10: {
          u8g.drawStr(10, 30, "- > 10.00V /");
          u8g.setPrintPos(87, 30);
          u8g.print(encoder_data);
          u8g.drawStr(10, 50, "use encoder!");  
        break;   
      } 
      
      case CHECK: {
        
        u8g.drawStr(10, 30, "push to exit");  
        break;   
      } 
      
      default: break;
      
    } 
} 



