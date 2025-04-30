#define LOGO_WIDTH    32
#define LOGO_HEIGHT   16

static const char PROGMEM dvd_logo[] = {
    0x00, 0x00, 0x00, 0xE0,
    0xEC, 0xEC, 0x0C, 0x0C,
    0x8C, 0xDC, 0xFC, 0xFC,
    0x3C, 0x7C, 0xF8, 0xE0,
    0xC0, 0xE0, 0x70, 0x38,
    0x1C, 0xEC, 0xEC, 0x6C,
    0x0C, 0x0C, 0x8C, 0xF8,
    0xF8, 0x70, 0x00, 0x00,
    0x00, 0x00, 0x30, 0x33,
    0x33, 0x73, 0x73, 0x71,
    0x79, 0x79, 0x78, 0x78,
    0x58, 0x58, 0x59, 0x5F,
    0x5B, 0x79, 0x78, 0x78,
    0x79, 0x7B, 0x73, 0x73,
    0x73, 0x31, 0x31, 0x31,
    0x00, 0x00, 0x00, 0x00,
};

static int8_t dvd_x = 0;
static int8_t dvd_y = 0;
static int8_t dvd_v_x = 1;
static int8_t dvd_v_y = 1;

static void set_pixel(char *buffer, int x, int y) {
    if (x < 0 || x >= OLED_DISPLAY_WIDTH || y < 0 || y >= OLED_DISPLAY_HEIGHT) {
        return;
    }
    int page = y / 8;
    int index = page * OLED_DISPLAY_WIDTH + x;
    buffer[index] |= (1 << (y % 8));
}

bool render_dvd(void) {
    static char oled_buffer[OLED_DISPLAY_WIDTH * OLED_DISPLAY_HEIGHT / 8];
    static uint16_t last_time = 0;
    uint16_t current_time = timer_read();

    if (timer_elapsed(last_time) > 50) {
        last_time = current_time;
        dvd_x += dvd_v_x;
        dvd_y += dvd_v_y;

        // Bbounce horizontally
        if (dvd_x < 0) {
            dvd_x = 0;
            dvd_v_x = -dvd_v_x;
        } else if (dvd_x > (OLED_DISPLAY_WIDTH - LOGO_WIDTH)) {
            dvd_x = OLED_DISPLAY_WIDTH - LOGO_WIDTH;
            dvd_v_x = -dvd_v_x;
        }
        // bounce vertically
        if (dvd_y < 0) {
            dvd_y = 0;
            dvd_v_y = -dvd_v_y;
        } else if (dvd_y > (OLED_DISPLAY_HEIGHT - LOGO_HEIGHT)) {
            dvd_y = OLED_DISPLAY_HEIGHT - LOGO_HEIGHT;
            dvd_v_y = -dvd_v_y;
        }
    }

    memset(oled_buffer, 0, sizeof(oled_buffer));
    for (int y = 0; y < LOGO_HEIGHT; y++) {
        int page = y / 8;
        uint8_t row_bit = 1 << (y % 8);
        for (int x = 0; x < LOGO_WIDTH; x++) {
            uint8_t pixel_byte = pgm_read_byte(&dvd_logo[page * LOGO_WIDTH + x]);
            if (pixel_byte & row_bit) {
                set_pixel(oled_buffer, dvd_x + x, dvd_y + y);
            }
        }
    }

    oled_write_raw_P((const char *)oled_buffer, sizeof(oled_buffer));
    return false;
}
