

#define B_E         0x40 /*enable signal*/
#define B_SELECT    4
#define B_RW        2
#define B_RS        1

void ascii_ctrl_bit_set(char x);;
void ascii_ctrl_bit_clear(char x);;
char  ascii_read_controller();;
char  ascii_read_status();;
char ascii_read_data();
void ascii_write_controller(char command);
void ascii_write_cmd(char command);
void ascii_write_data(char command);
void ascii_command(char command);
void ascii_write_char(char command);void ascii_init();
void ascii_gotoxy(int x, int y);
void ascii_init();
void ascii_clear_screen();
void ascii_write_text_at(char num, int x, int y);