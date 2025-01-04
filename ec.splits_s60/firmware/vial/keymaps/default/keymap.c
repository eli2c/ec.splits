#include QMK_KEYBOARD_H
#include <unistd.h>


#define _MA 0
#define _FN 1
int timer = 0;
char wpm_text[5];
int x = 31;
int currwpm = 0;
int vert_count = 0; 

//=============  USER CONFIG PARAMS  ===============
float max_wpm = 110.0f; //WPM value at the top of the graph window
int graph_refresh_interval = 80; //in milliseconds
int graph_area_fill_interval = 3; //determines how dense the horizontal lines under the graph line are; lower = more dense
int vert_interval = 3; //determines frequency of vertical lines under the graph line
bool vert_line = true; //determines whether to draw vertical lines
int graph_line_thickness = 3; //determines thickness of graph line in pixels
//=============  END USER PARAMS  ===============

enum custom_keycodes {
  KC_CUST = SAFE_RANGE,
};




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
    [0] = LAYOUT_ortho_6x4(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),


};
 #if defined(ENCODER_MAP_ENABLE) 
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
     [0] = { ENCODER_CCW_CW(KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN)  }
    
};
 #endif
   

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

void oled_task_user(void) {
	
	//get current WPM value
	currwpm = get_current_wpm();
	
	//check if it's been long enough before refreshing graph
	if(timer_elapsed(timer) > graph_refresh_interval){
	
		// main calculation to plot graph line
		x = 32 - ((currwpm / max_wpm) * 32);
		
		//first draw actual value line
		for(int i = 0; i <= graph_line_thickness - 1; i++){
			oled_write_pixel(1, x + i, true);
		}
		
		
		//then fill in area below the value line
		if(vert_line){
			if(vert_count == vert_interval){
				vert_count = 0;
				while(x <= 32){
					oled_write_pixel(1, x, true);
					x++;
				}
			} else {
				for(int i = 32; i > x; i--){
					if(i % graph_area_fill_interval == 0){
						oled_write_pixel(1, i, true);
					}
				}
				vert_count++;
			}
		} else {
			for(int i = 32; i > x; i--){
				if(i % graph_area_fill_interval == 0){
					oled_write_pixel(1, i, true);
				}
			}
		}
		
		//then move the entire graph one pixel to the right
		oled_pan(false); 
		
		//refresh the timer for the next iteration
		timer = timer_read();
		
	}
	
	//format current WPM value into a printable string
	sprintf(wpm_text,"%i", currwpm);
	
	//formatting for triple digit WPM vs double digits, then print WPM readout
	if(currwpm >= 100){
		oled_set_cursor(14, 3);
		oled_write("WPM: ", false);
		oled_set_cursor(18, 3);
		oled_write(wpm_text, false);
	} else if (currwpm >= 10){
		oled_set_cursor(15, 3);
		oled_write("WPM: ", false);
		oled_set_cursor(19, 3);
		oled_write(wpm_text, false);
	} else if (currwpm > 0) {
		oled_set_cursor(16, 3);
		oled_write("WPM: ", false);
		oled_set_cursor(20, 3);
		oled_write(wpm_text, false);		
	}
	
}

#endif


