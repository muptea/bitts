//Drivers for display

#include <util/delay.h>
#include <Arduino.h>
#include "game_hw.h"
#include "game_sound.h"

volatile uint8_t v_rnd=0;//Random number
volatile uint8_t v_LevelSpeed=2;//Game speed 0...5
volatile uint16_t v_GamePoints=0;//Game points


//=======================================================
//SPI
//-------------------------------------------------------
void spi_MasterInit(void)
{
	sbi(PORTB,2); sbi(DDRB,2);//SS pin
	sbi(DDRB,3);//MOSI
	sbi(DDRB,5);//SCK
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void spi_Write(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF))){};
}
//=======================================================
//ADC
//-------------------------------------------------------
void adc_Init(void)
{
	ADMUX |= (1<<REFS0);// Select Vref=AVcc
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);  //set prescaller to 128 and enable ADC 
}

uint16_t adc_Read(uint8_t adc_input)
{
	ADMUX=adc_input|0x40;
	delay_us(10);
	ADCSRA|=(1<<ADSC);//Start conversion
	while ((ADCSRA & (1<<ADIF))==0);//Wait
	ADCSRA|=0x10;
	return ADC;
}
//=======================================================
//Hardware Timer
//-------------------------------------------------------

//Globals
//volatile uint8_t ht0_load=0;
//volatile uint16_t millis()=0;
uint16_t ht0_blink_v=0;
uint16_t blink_time=300/ht0_time;
uint8_t blink=0;

void ht0_Delay(uint16_t t)
{
	uint16_t tmp;
	tmp=millis();
	while ((millis()-tmp)<t) {};
}

uint8_t ht0_BlinkWork(void)
{
	if ((millis()-ht0_blink_v)>(blink_time))
	{
		ht0_blink_v=millis();
		blink=byte_inv(blink);
		return 1;
	};
	return 0;
}
/*
void ht0_Init(void)
{
	TCCR0B=0x05;
	OCR0A=0x00; OCR0B=0x00;
	ht0_load=0x63;//16MHz 10ms
	TCNT0=ht0_load;
	TIMSK0|=0x01;
	sei();
}

ISR(_VECTOR(16))
{
	millis()++;
	TCNT0=ht0_load;
}*/
//=======================================================
//Buttons (Keys)
//-------------------------------------------------------
//Globals
uint8_t	pkeys_Value_Change;
uint8_t pkeys_Unused=0b11000000;
uint8_t	pkeys_Value=0xFF;
uint8_t	pkeys_Value_Old=0xFF;
uint32_t pkeys_timer_cnt;
uint32_t pkeys_timer_switch;
uint32_t pkeys_timer_read;

void pkeys_Init(void)
{
	cbi(pkeys_k0_ddr,pkeys_k0_bit); sbi(pkeys_k0_port,pkeys_k0_bit);
	cbi(pkeys_k1_ddr,pkeys_k1_bit); sbi(pkeys_k1_port,pkeys_k1_bit);
	cbi(pkeys_k2_ddr,pkeys_k2_bit); sbi(pkeys_k2_port,pkeys_k2_bit);
	cbi(pkeys_k3_ddr,pkeys_k3_bit); sbi(pkeys_k3_port,pkeys_k3_bit);
	cbi(pkeys_k4_ddr,pkeys_k4_bit); sbi(pkeys_k4_port,pkeys_k4_bit);
	cbi(pkeys_k5_ddr,pkeys_k5_bit); sbi(pkeys_k5_port,pkeys_k5_bit);
	cbi(pkeys_k6_ddr, pkeys_k6_bit); sbi(pkeys_k6_port, pkeys_k6_bit);
	pkeys_timer_cnt=millis();
	pkeys_timer_switch=millis();
	pkeys_timer_read=millis();
	pReadKeys();
}

uint8_t pReadKeys(void)
{
    if ((millis() - pkeys_timer_read) > pkeys_TimeRead)
    {
        pkeys_timer_read = millis();
        pkeys_Value_Old = pkeys_Value;
        pkeys_Value = 0;

        if (!inbit(pkeys_k0_pin, pkeys_k0_bit)) { pkeys_Value |= 0x01; } // Бит 0 - UP
        if (!inbit(pkeys_k1_pin, pkeys_k1_bit)) { pkeys_Value |= 0x02; } // Бит 1 - LEFT
        if (!inbit(pkeys_k2_pin, pkeys_k2_bit)) { pkeys_Value |= 0x04; } // Бит 2 - DOWN
        if (!inbit(pkeys_k3_pin, pkeys_k3_bit)) { pkeys_Value |= 0x08; } // Бит 3 - RIGHT
        if (!inbit(pkeys_k4_pin, pkeys_k4_bit)) { pkeys_Value |= 0x10; } // Бит 4 - ACTION 
        if (!inbit(pkeys_k5_pin, pkeys_k5_bit)) { pkeys_Value |= 0x20; } // Бит 5 - PAUSE 
        if (!inbit(pkeys_k6_pin, pkeys_k6_bit)) { pkeys_Value |= 0x40; } // Бит 6 - EXIT 

        pkeys_Value_Change = (pkeys_Value != pkeys_Value_Old);
        if (pkeys_Value_Change)
        {
            pkeys_timer_cnt = millis();
        }
        return 1;
    }
    return 0;
}

uint8_t pKeyPressed(uint8_t NumBit)
{
    if ((pkeys_Value & NumBit) != 0)
    {
        return 1;
    }
    return 0;
}

uint8_t pLongKeyPressed(uint8_t NumBit)
{
	uint8_t tmp;
	NumBit = 255 - NumBit;
	
	if ((pkeys_Value_Old==NumBit)&(pkeys_Value==NumBit)&((millis()-pkeys_timer_cnt)>pkeys_LongPressTime))
	{
		tmp=1;
	} else
	{
		tmp=0;
	};

	if (tmp)
	{
		if ((millis()-pkeys_timer_switch)>pkeys_LongTimeSwitch)
		{
			tmp=2;
			pkeys_timer_switch=millis();
		} else
		{
			tmp=1;
		};
	};
	return tmp;
}

uint8_t pKeySwitch(uint8_t NumBit)
{
	if (pkeys_Value_Change && (pkeys_Value & NumBit) && !(pkeys_Value_Old & NumBit))
	{
		return 2;
	};
return 0;
}
//=======================================================
//MAX7219 x2
//-------------------------------------------------------
void max7219_Load(void)
{
	sbi(max7219d_CS_port,max7219d_CS_bit); cbi(max7219d_CS_port,max7219d_CS_bit);
}

void max7219_write(uint8_t adr,uint8_t data)
{
	spi_Write(adr); spi_Write(data);
}

void max7219_On(void)
{
	max7219_write(0x0C,0x01);
}

void max7219_Off(void)
{
	max7219_write(0x0C,0x00);
}

void max7219_SetDecode(uint8_t n)
{
	max7219_write(0x09,n);
}

void max7219_SetIntensity(uint8_t n)
{
	max7219_write(0x0A,n);
}

void max7219_Init(void)
{
	cbi(max7219d_CS_port,max7219d_CS_bit);
	sbi(max7219d_CS_ddr,max7219d_CS_bit);
	max7219_SetDecode(0); max7219_SetDecode(0); max7219_Load();
	max7219_write(0x0B,0x07); max7219_write(0x0B,0x07); max7219_Load();
	max7219_SetIntensity(0x0A); max7219_SetIntensity(0x0A); max7219_Load();
	max7219_On(); max7219_On(); max7219_Load();
}

//Load 16 bytes
void max7219_LoadBytes16(uint8_t *data)
{
	spi_Write(0x01); spi_Write(data[1]); spi_Write(0x01); spi_Write(data[0]);
	sbi(max7219d_CS_port,max7219d_CS_bit); wdr(); cbi(max7219d_CS_port,max7219d_CS_bit);

	spi_Write(0x02); spi_Write(data[3]); spi_Write(0x02); spi_Write(data[2]);
	sbi(max7219d_CS_port,max7219d_CS_bit); wdr(); cbi(max7219d_CS_port,max7219d_CS_bit);

	spi_Write(0x03); spi_Write(data[5]); spi_Write(0x03); spi_Write(data[4]);
	sbi(max7219d_CS_port,max7219d_CS_bit); wdr(); cbi(max7219d_CS_port,max7219d_CS_bit);

	spi_Write(0x04); spi_Write(data[7]); spi_Write(0x04); spi_Write(data[6]);
	sbi(max7219d_CS_port,max7219d_CS_bit); wdr(); cbi(max7219d_CS_port,max7219d_CS_bit);

	spi_Write(0x05); spi_Write(data[9]); spi_Write(0x05); spi_Write(data[8]);
	sbi(max7219d_CS_port,max7219d_CS_bit); wdr(); cbi(max7219d_CS_port,max7219d_CS_bit);

	spi_Write(0x06); spi_Write(data[11]); spi_Write(0x06); spi_Write(data[10]);
	sbi(max7219d_CS_port,max7219d_CS_bit); wdr(); cbi(max7219d_CS_port,max7219d_CS_bit);

	spi_Write(0x07); spi_Write(data[13]); spi_Write(0x07); spi_Write(data[12]);
	sbi(max7219d_CS_port,max7219d_CS_bit); wdr(); cbi(max7219d_CS_port,max7219d_CS_bit);

	spi_Write(0x08); spi_Write(data[15]); spi_Write(0x08); spi_Write(data[14]);
	sbi(max7219d_CS_port,max7219d_CS_bit); wdr(); cbi(max7219d_CS_port,max7219d_CS_bit);
}
//=======================================================
//Random
void RNDpADC(uint8_t n)
{
	if (n==0) n++;
	while (n--)
	{
		v_rnd+=adc_Read(8);//Temperature sensor
	};
}
//=======================================================
//Special functions
inline uint8_t byte_inv(uint8_t b)
{
	return 255-b;
}

void ArrayFill_U8(uint8_t v, uint16_t n, uint8_t *arr)
{
	while (n--)
	{
		arr[n]=v;
	};
}
//=======================================================