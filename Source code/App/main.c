
#include "main.h"

struct menu {
	char *items;
	int price;
};
struct menu menu_card[5] = {"",0,
							"BURGER", 99, 
							"FRIES", 49,
							"ICESCREAM", 29,
							"COKE", 59 };
			
struct ImgDim {
	char dx;
	char dy;
};
struct ImgDim Dimen[5] = { 0,0,
							74, 63, 
							52, 64,
							44, 68,
							54, 64 };

uint8_t items_select[] = {0,0,0,0,0};
uint8_t taste[] = {0,0,0,0,0};
uint8_t MenuCnt = 0;
uint8_t TotalAmount = 0;

volatile struct  {
		volatile uint8_t Meas:1;
}Flags;
	
int main(void)
{
	init();

	while (TRUE) {
		
		if (Flags.Meas) {
			Flags.Meas = 0;
			
			switch(find_row()) {
				case 1:	DispMenu();	break;
				case 2: MenuSel();	break;
				case 3:	if(items_select[1] == 1 || items_select[2]  == 1 || items_select[3] == 1 || items_select[4]  == 1 ) 
							Pay();
						else {
							GLCD_GoTo(70,7);
							GLCD_WriteString("NO ITEM's");
							beep(1,250);
							dlyms(DISP_DLY);
							GLCD_GoTo(70,7);
							GLCD_WriteString("         ");
						} 
						break;
				default: break;
			} 
		
		}
	}
	return 0;
}

static void init(void)
{
	buzinit();
	beep(2,150);
	ledinit();
	
	uartinit();
	tmr2init();
	adcinit();
	
	GLCD_Initalize();
	GLCD_ClearScreen();
	
	GLCD_Bitmap (coffe_cup_bmp,4,2,69,48);
	
	GLCD_GoTo(5,0);
	GLCD_WriteString("FOOD Ordering System");
	GLCD_Line(5,10,125,10);
	GLCD_GoTo(80,6);
	GLCD_WriteString("Menu");
	
	sei();
	
	/* check for Menu Click */
	while (1) {
			if (Flags.Meas) {
				Flags.Meas = 0;
				if (find_row() == 5)
				break;
			}
	}
	DispMenu();
}

static void DispMenu(void) 
{
	 uint8_t  *foods[] = {0,burger, fries, ice_cream, coke};
	char str[10];
	
	if (++MenuCnt == 5)
		MenuCnt = 1;
	
	GLCD_ClearScreen();
	GLCD_Bitmap (foods[MenuCnt], 0,0,Dimen[MenuCnt].dx,Dimen[MenuCnt].dy); 
	GLCD_GoTo(70,0);
	GLCD_WriteString(menu_card[MenuCnt].items);
	GLCD_GoTo(90,1);
	itoa(menu_card[MenuCnt].price,str);
	GLCD_WriteString(str);
	
	GLCD_GoTo(80,2);
	GLCD_WriteString("Next");
	GLCD_GoTo(80,3);
	GLCD_WriteString("Order");
	GLCD_GoTo(80,4);
	GLCD_WriteString("Finish");
	beep(1,250);
	dlyms(1000);
	
 }
static void MenuSel(void) 
{
	uint8_t tast = FALSE;
	
	if (MenuCnt == 1 || MenuCnt == 2) {
		
		GLCD_GoTo(85,5);
		GLCD_WriteString("normal");
		GLCD_GoTo(85,6);
		GLCD_WriteString("spicy");
		beep(1,150);
		
		do {
			switch(find_row()) {
				case 4:	taste[MenuCnt] = 0; tast = TRUE; break;
				case 5: taste[MenuCnt] = 1; tast = TRUE; break;
				default: break;
			}
		} while (!tast);
		
	} 
	
	items_select[MenuCnt] = 1;
	TotalAmount += menu_card[MenuCnt].price;
	
	OrderPlaced();
	DispMenu();
}
static void tmr2init(void)
{
	TCNT2   = 75;
	TIMSK   |= _BV(TOIE2);			//ENABLE OVERFLOW INTERRUPT
	TCCR2  |=  _BV(CS22) | _BV(CS21) | _BV(CS20); /* PRESCALAR BY 256 */
}

/* overflows at every 25msec */
ISR(TIMER2_OVF_vect)
{
	static uint8_t i,j;
	TCNT2 = 75;

	if (++i >= 200) i = 0;
	switch(i) {
		case 0: case 5: ledon(); break;
		case 1: case 6: ledoff(); break;
	} 
	if (++j >= 20) {
		j = 0;
		Flags.Meas = 1;
	}
}

static void OrderPlaced(void) 
{
	GLCD_ClearScreen();
	GLCD_GoTo(5,2);
	GLCD_WriteString("YOUR ORDER IS PLACE.");
	GLCD_GoTo(5,3);
	GLCD_WriteString("IT WILL BE SERVED IN");
	beep(1,150);
		
	putchar(MenuCnt);
	putchar(taste[MenuCnt]);
	
	while(getchar() != 's');
	GLCD_GoTo(35,4);
	GLCD_WriteString("15 Minutes...");
	beep(1,150);
	
	dlyms(1000);
}
static void Pay(void) 
{
	char str[10];
	
	GLCD_ClearScreen();
	GLCD_GoTo(15,2);
	GLCD_WriteString("PLEASE PAY RS:");
	GLCD_GoTo(100,2);
	itoa(TotalAmount,str);
	
	putchar(5);
	putchar(0);
	
	GLCD_WriteString(str);
	GLCD_GoTo(20,3);
	GLCD_WriteString("AT THE COUNTER 3.");
	GLCD_GoTo(40,5);
	GLCD_WriteString("THANK YOU.");
	GLCD_GoTo(12,6);
	GLCD_WriteString("PLEASE VISIT AGAIN.");
	beep(1,150);
	for(;;);
	
}
