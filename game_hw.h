#ifndef _GAME_HW_
#define _GAME_HW_

#ifndef  sbi
# define  sbi(port, bit)   ((port) |= (1 << (bit)))
#endif

#ifndef cbi
# define  cbi(port, bit)   ((port) &= ~(1 << (bit)))
#endif

#ifndef inbit
#define   inbit(port, bit)   ((port)&(1 << (bit)))
#endif

#ifndef	wdr
#define 	wdr()   asm("wdr")
#endif

#ifndef	nop
#define 	nop()   asm("nop")
#endif

#ifndef	wdr
#define 	sei()   asm("sei")
#endif

#ifndef	nop
#define 	cli()   asm("cli")
#endif

#ifndef delay_ms
#define   delay_ms(t)   (_delay_ms(t))
#endif

#ifndef delay_us
#define   delay_us(t)   (_delay_us(t))
#endif

#define ht0_time 1

#define ht0_cnt ((uint16_t)millis())

#ifdef __cplusplus
extern "C" {
#endif

//===================================
extern volatile uint8_t v_rnd;//Random number
extern volatile uint8_t v_LevelSpeed;//Game speed 0...5
extern volatile uint16_t v_GamePoints;//Game points
//===================================


//extern volatile uint8_t ht0_load;
//extern volatile uint16_t ht0_cnt;

extern uint16_t ht0_blink_v;
extern uint16_t blink_time;
extern uint8_t blink;

//void ht0_Init(void);
void ht0_Delay(uint16_t t);
uint8_t ht0_BlinkWork(void);
//===================================
//SPI
void spi_MasterInit(void);
void spi_Write(uint8_t data);
//===================================
//ADC
void adc_Init(void);
uint16_t adc_Read(uint8_t adc_input);
//===================================
//Buttons (Keys)
//Key 0
#define pkeys_k0_bit	1
#define pkeys_k0_pin	PINB
#define pkeys_k0_ddr	DDRB
#define pkeys_k0_port	PORTB

//Key 1
#define pkeys_k1_bit	0
#define pkeys_k1_pin	PINB
#define pkeys_k1_ddr	DDRB
#define pkeys_k1_port	PORTB

//Key 2
#define pkeys_k2_bit	7
#define pkeys_k2_pin	PIND
#define pkeys_k2_ddr	DDRD
#define pkeys_k2_port	PORTD

//Key 3
#define pkeys_k3_bit	6
#define pkeys_k3_pin	PIND
#define pkeys_k3_ddr	DDRD
#define pkeys_k3_port	PORTD

//Key 4
#define pkeys_k4_bit	5
#define pkeys_k4_pin	PIND
#define pkeys_k4_ddr	DDRD
#define pkeys_k4_port	PORTD

//Key 5
#define pkeys_k5_bit	4
#define pkeys_k5_pin	PIND
#define pkeys_k5_ddr	DDRD
#define pkeys_k5_port	PORTD

// Key 6
#define pkeys_k6_bit	3 
#define pkeys_k6_pin	PIND
#define pkeys_k6_ddr	DDRD
#define pkeys_k6_port	PORTD

#define pkeys_TimeRead			30 /ht0_time	//ms, Between read
#define pkeys_LongPressTime		200 /ht0_time   //ms, Long press
#define pkeys_LongTimeSwitch	30 /ht0_time	//ms, repeat time

extern uint8_t pkeys_Unused;
extern uint8_t pkeys_Value;

void pkeys_Init(void);
uint8_t pReadKeys(void);
uint8_t pKeyPressed(uint8_t NumBit);
uint8_t pLongKeyPressed(uint8_t NumBit);
uint8_t pKeySwitch(uint8_t NumBit);
//===================================
//MAX7219
#define max7219d_CS_port	PORTC
#define max7219d_CS_ddr		DDRC
#define max7219d_CS_bit		0

void max7219_Init(void);
void max7219_LoadBytes16(uint8_t *data);
void RNDpADC(uint8_t n);
inline uint8_t byte_inv(uint8_t b);
void ArrayFill_U8(uint8_t v, uint16_t n, uint8_t *arr);

//===================================
#ifdef __cplusplus
};
#endif

#endif //#define _GAME_HW_