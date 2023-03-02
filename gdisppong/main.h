typedef volatile struct {
	int seconds;
	int ten_seconds;
	int minutes;
} TIME, *PTIME;
static TIME time;
void timer6_interrupt();
void print_scores();
