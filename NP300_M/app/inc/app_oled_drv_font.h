#ifndef _APP_DRV_OLED_FONT_H
#define _APP_DRV_OLED_FONT_H

/************************************5*10的点阵************************************/
const unsigned char asc_1005[] = 
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*" ",0*/
	0x00,0x00,0x7C,0x00,0x00,0x00,0x00,0x01,0x00,0x00,/*"!",1*/
	0x00,0x04,0x02,0x04,0x02,0x00,0x00,0x00,0x00,0x00,/*""",2*/
	0x50,0xF8,0x50,0xF8,0x50,0x00,0x00,0x00,0x00,0x00,/*"#",3*/
	0x00,0x9C,0xFE,0xCC,0x00,0x00,0x01,0x03,0x01,0x00,/*"$",4*/
	0x3C,0xA4,0xFC,0x24,0xE0,0x00,0x00,0x01,0x01,0x01,/*"%",5*/
	0xC0,0x3C,0xDC,0x60,0x20,0x00,0x01,0x01,0x01,0x01,/*"&",6*/
	0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"'",7*/
	0x00,0x00,0xF8,0x06,0x00,0x00,0x00,0x00,0x03,0x00,/*"(",8*/
	0x00,0x86,0x78,0x00,0x00,0x00,0x01,0x00,0x00,0x00,/*")",9*/
	0x50,0x30,0xF8,0x20,0x50,0x00,0x00,0x00,0x00,0x00,/*"*",10*/
	0x20,0x20,0xF8,0x20,0x20,0x00,0x00,0x00,0x00,0x00,/*"+",11*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,/*",",12*/
	0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0x00,0x00,/*"-",13*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,/*".",14*/
	0x00,0x80,0x70,0x0C,0x02,0x02,0x01,0x00,0x00,0x00,/*"/",15*/
	0xF8,0x04,0x04,0xF8,0x00,0x00,0x01,0x01,0x00,0x00,/*"0",16*/
	0x00,0x08,0xFC,0x00,0x00,0x00,0x01,0x01,0x01,0x00,/*"1",17*/
	0x00,0x8C,0x64,0x1C,0x00,0x00,0x01,0x01,0x01,0x00,/*"2",18*/
	0x00,0x8C,0x24,0xDC,0x00,0x00,0x01,0x01,0x01,0x00,/*"3",19*/
	0x60,0x50,0x48,0xFC,0x40,0x00,0x00,0x01,0x01,0x01,/*"4",20*/
	0x00,0x9C,0x14,0xF4,0x00,0x00,0x01,0x01,0x00,0x00,/*"5",21*/
	0xF8,0x14,0x14,0xE4,0x00,0x00,0x01,0x01,0x00,0x00,/*"6",22*/
	0x00,0x04,0xE4,0x1C,0x00,0x00,0x00,0x01,0x00,0x00,/*"7",23*/
	0xD8,0x24,0x24,0xD8,0x00,0x00,0x01,0x01,0x00,0x00,/*"8",24*/
	0x78,0x44,0xC4,0xF8,0x00,0x01,0x01,0x01,0x00,0x00,/*"9",25*/
	0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x01,0x00,0x00,/*":",26*/
	0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x03,0x00,0x00,/*";",27*/
	0x00,0x20,0x50,0x88,0x04,0x00,0x00,0x00,0x00,0x01,/*"<",28*/
	0x50,0x50,0x50,0x50,0x50,0x00,0x00,0x00,0x00,0x00,/*"=",29*/
	0x04,0x88,0x50,0x20,0x00,0x01,0x00,0x00,0x00,0x00,/*">",30*/
	0x00,0x18,0x04,0x64,0x18,0x00,0x00,0x01,0x00,0x00,/*"?",31*/
	0xF8,0xFC,0x9C,0xFC,0x78,0x00,0x01,0x01,0x01,0x00,/*"@",32*/
	0x80,0x78,0x4C,0xF0,0x00,0x01,0x00,0x00,0x01,0x01,/*"A",33*/
	0x04,0xFC,0x24,0xDC,0x00,0x01,0x01,0x01,0x01,0x00,/*"B",34*/
	0xF8,0x0C,0x04,0x8C,0x00,0x00,0x01,0x01,0x00,0x00,/*"C",35*/
	0x04,0xFC,0x04,0x04,0xF8,0x01,0x01,0x01,0x01,0x00,/*"D",36*/
	0x04,0xFC,0x24,0x74,0x0C,0x01,0x01,0x01,0x01,0x01,/*"E",37*/
	0x04,0xFC,0x74,0x04,0x00,0x01,0x01,0x01,0x00,0x00,/*"F",38*/
	0xF8,0x0C,0x44,0xCC,0x40,0x00,0x01,0x01,0x01,0x00,/*"G",39*/
	0x04,0xFC,0x24,0xFC,0x04,0x01,0x01,0x01,0x01,0x01,/*"H",40*/
	0x00,0x04,0xFC,0x04,0x00,0x00,0x01,0x01,0x01,0x00,/*"I",41*/
	0x00,0x04,0xFC,0x04,0x00,0x02,0x02,0x03,0x00,0x00,/*"J",42*/
	0x04,0xFC,0x14,0xEC,0x04,0x01,0x01,0x01,0x01,0x01,/*"K",43*/
	0x04,0xFC,0x04,0x00,0x00,0x01,0x01,0x01,0x01,0x01,/*"L",44*/
	0x04,0xFC,0x80,0xFC,0x04,0x00,0x01,0x01,0x01,0x01,/*"M",45*/
	0x04,0xFC,0x34,0xFC,0x04,0x01,0x01,0x01,0x01,0x00,/*"N",46*/
	0xF8,0x04,0x04,0xF8,0x00,0x00,0x01,0x01,0x00,0x00,/*"O",47*/
	0x04,0xFC,0x24,0x24,0x18,0x01,0x01,0x01,0x00,0x00,/*"P",48*/
	0xF8,0x84,0x04,0xF8,0x00,0x00,0x01,0x01,0x02,0x00,/*"Q",49*/
	0x04,0xFC,0x24,0xFC,0x00,0x01,0x01,0x01,0x00,0x01,/*"R",50*/
	0x98,0x24,0x24,0xCC,0x00,0x01,0x01,0x01,0x00,0x00,/*"S",51*/
	0x0C,0x04,0xFC,0x04,0x04,0x00,0x01,0x01,0x01,0x00,/*"T",52*/
	0xFC,0x04,0x04,0xFC,0x04,0x01,0x01,0x01,0x00,0x00,/*"U",53*/
	0x04,0x7C,0x80,0x7C,0x04,0x00,0x00,0x01,0x00,0x00,/*"V",54*/
	0x1C,0xE0,0x3C,0xE0,0x1C,0x00,0x01,0x00,0x01,0x00,/*"W",55*/
	0x04,0xDC,0x20,0xDC,0x04,0x01,0x01,0x00,0x01,0x01,/*"X",56*/
	0x04,0x1C,0xE0,0x1C,0x04,0x00,0x01,0x01,0x01,0x00,/*"Y",57*/
	0x8C,0x64,0x14,0x8C,0x00,0x01,0x01,0x01,0x01,0x00,/*"Z",58*/
	0x00,0x00,0xFE,0x02,0x00,0x00,0x00,0x03,0x02,0x00,/*"[",59*/
	0x00,0x04,0x38,0xC0,0x00,0x00,0x00,0x00,0x01,0x02,/*"\",60*/
	0x00,0x02,0xFE,0x00,0x00,0x00,0x02,0x03,0x00,0x00,/*"]",61*/
	0x00,0x02,0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,/*"^",62*/
	0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x02,/*"_",63*/
	0x00,0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"`",64*/
	0xA0,0x50,0x50,0xF0,0x00,0x01,0x01,0x01,0x01,0x01,/*"a",65*/
	0x04,0xFC,0x10,0xF0,0x00,0x00,0x01,0x01,0x01,0x00,/*"b",66*/
	0x00,0xE0,0x10,0x30,0x00,0x00,0x00,0x01,0x01,0x00,/*"c",67*/
	0xE0,0x10,0x14,0xFC,0x00,0x00,0x01,0x01,0x01,0x01,/*"d",68*/
	0xE0,0x50,0x50,0x60,0x00,0x00,0x01,0x01,0x01,0x00,/*"e",69*/
	0x00,0x10,0xFC,0x14,0x04,0x00,0x01,0x01,0x01,0x00,/*"f",70*/
	0x00,0xF0,0xB0,0x30,0x10,0x00,0x03,0x02,0x03,0x00,/*"g",71*/
	0x04,0xFC,0x10,0xF0,0x00,0x01,0x01,0x01,0x01,0x01,/*"h",72*/
	0x00,0x10,0xF4,0x00,0x00,0x00,0x01,0x01,0x01,0x00,/*"i",73*/
	0x00,0x10,0xF4,0x00,0x00,0x02,0x02,0x03,0x00,0x00,/*"j",74*/
	0x04,0xFC,0x40,0xB0,0x00,0x01,0x01,0x01,0x01,0x00,/*"k",75*/
	0x00,0x04,0xFC,0x00,0x00,0x00,0x01,0x01,0x01,0x00,/*"l",76*/
	0xF0,0x10,0xF0,0x10,0xF0,0x01,0x00,0x01,0x00,0x01,/*"m",77*/
	0x10,0xF0,0x10,0xF0,0x00,0x01,0x01,0x01,0x01,0x01,/*"n",78*/
	0xE0,0x10,0x10,0xE0,0x00,0x00,0x01,0x01,0x00,0x00,/*"o",79*/
	0x10,0xF0,0x10,0xF0,0x00,0x02,0x03,0x03,0x01,0x00,/*"p",80*/
	0xE0,0x10,0x10,0xF0,0x00,0x00,0x01,0x03,0x03,0x02,/*"q",81*/
	0x10,0xF0,0x10,0x10,0x00,0x01,0x01,0x01,0x00,0x00,/*"r",82*/
	0x00,0x30,0x50,0x90,0x00,0x00,0x01,0x01,0x01,0x00,/*"s",83*/
	0x00,0x10,0xFC,0x10,0x00,0x00,0x00,0x01,0x01,0x00,/*"t",84*/
	0x10,0xF0,0x10,0xF0,0x00,0x00,0x01,0x01,0x01,0x01,/*"u",85*/
	0x10,0x70,0x80,0x70,0x10,0x00,0x00,0x01,0x00,0x00,/*"v",86*/
	0x30,0xC0,0xF0,0xC0,0x30,0x00,0x01,0x00,0x01,0x00,/*"w",87*/
	0x10,0xB0,0xF0,0x10,0x00,0x01,0x00,0x01,0x01,0x00,/*"x",88*/
	0x10,0x70,0x80,0x70,0x10,0x02,0x02,0x01,0x00,0x00,/*"y",89*/
	0x00,0x90,0x50,0x30,0x00,0x00,0x01,0x01,0x01,0x00,/*"z",90*/
	0x00,0x00,0x20,0xFE,0x02,0x00,0x00,0x00,0x03,0x02,/*"{",91*/
	0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x03,0x00,0x00,/*"|",92*/
	0x02,0xFE,0x20,0x00,0x00,0x02,0x03,0x00,0x00,0x00,/*"}",93*/
	0x04,0x02,0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x00,/*"~",94*/
};

/************************************6*12的点阵************************************/
const unsigned char asc_1206[] =
{
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*" ",0*/
  0x00,0x00,0x7C,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,/*"!",1*/
  0x00,0x04,0x03,0x04,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*""",2*/
  0x90,0xFC,0x90,0xFC,0x90,0x00,0x00,0x03,0x00,0x03,0x00,0x00,/*"#",3*/
  0x18,0x24,0xFE,0x44,0x88,0x00,0x01,0x02,0x07,0x02,0x01,0x00,/*"$",4*/
  0x38,0x44,0xF8,0xD0,0x2C,0xC0,0x00,0x03,0x00,0x01,0x02,0x01,/*"%",5*/
  0xC0,0x38,0xE4,0x18,0xE0,0x20,0x01,0x02,0x02,0x01,0x02,0x01,/*"&",6*/
  0x04,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"'",7*/
  0x00,0x00,0xF8,0x06,0x01,0x00,0x00,0x00,0x00,0x03,0x04,0x00,/*"(",8*/
  0x00,0x01,0x06,0xF8,0x00,0x00,0x00,0x04,0x03,0x00,0x00,0x00,/*")",9*/
  0x90,0x60,0xF8,0x60,0x90,0x00,0x00,0x00,0x01,0x00,0x00,0x00,/*"*",10*/
  0x00,0x20,0x20,0xF8,0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x00,/*"+",11*/
  0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x03,0x00,0x00,0x00,0x00,/*",",12*/
  0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x00,/*"-",13*/
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,/*".",14*/
  0x00,0x00,0xC0,0x30,0x0C,0x02,0x04,0x03,0x00,0x00,0x00,0x00,/*"/",15*/
  0xF8,0x04,0x04,0x04,0xF8,0x00,0x01,0x02,0x02,0x02,0x01,0x00,/*"0",16*/
  0x00,0x08,0xFC,0x00,0x00,0x00,0x00,0x02,0x03,0x02,0x00,0x00,/*"1",17*/
  0x18,0x84,0x44,0x24,0x18,0x00,0x03,0x02,0x02,0x02,0x02,0x00,/*"2",18*/
  0x08,0x04,0x24,0x24,0xD8,0x00,0x01,0x02,0x02,0x02,0x01,0x00,/*"3",19*/
  0xC0,0xA0,0x98,0xFC,0x80,0x00,0x00,0x00,0x02,0x03,0x02,0x00,/*"4",20*/
  0x7C,0x24,0x24,0x24,0xC4,0x00,0x01,0x02,0x02,0x02,0x01,0x00,/*"5",21*/
  0xF0,0x48,0x24,0x24,0xC8,0x00,0x01,0x02,0x02,0x02,0x01,0x00,/*"6",22*/
  0x00,0x04,0xC4,0x34,0x0C,0x00,0x00,0x00,0x03,0x00,0x00,0x00,/*"7",23*/
  0xD8,0x24,0x24,0x24,0xD8,0x00,0x01,0x02,0x02,0x02,0x01,0x00,/*"8",24*/
  0x38,0x44,0x44,0x24,0xF8,0x00,0x01,0x02,0x02,0x01,0x00,0x00,/*"9",25*/
  0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,/*":",26*/
  0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,/*";",27*/
  0x00,0x60,0x90,0x08,0x04,0x00,0x00,0x00,0x00,0x01,0x02,0x00,/*"<",28*/
  0x50,0x50,0x50,0x50,0x50,0x50,0x00,0x00,0x00,0x00,0x00,0x00,/*"=",29*/
  0x00,0x04,0x08,0x90,0x60,0x00,0x00,0x02,0x01,0x00,0x00,0x00,/*">",30*/
  0x18,0x04,0xC4,0x24,0x18,0x00,0x00,0x00,0x02,0x00,0x00,0x00,/*"?",31*/
  0xF0,0x08,0xE4,0xF4,0x84,0x78,0x00,0x01,0x02,0x02,0x02,0x01,/*"@",32*/
  0x00,0xE0,0x9C,0xF0,0x80,0x00,0x02,0x03,0x00,0x00,0x03,0x02,/*"A",33*/
  0x04,0xFC,0x24,0x24,0xD8,0x00,0x02,0x03,0x02,0x02,0x01,0x00,/*"B",34*/
  0xF8,0x04,0x04,0x04,0x0C,0x00,0x01,0x02,0x02,0x02,0x01,0x00,/*"C",35*/
  0x04,0xFC,0x04,0x04,0xF8,0x00,0x02,0x03,0x02,0x02,0x01,0x00,/*"D",36*/
  0x04,0xFC,0x24,0x74,0x0C,0x00,0x02,0x03,0x02,0x02,0x03,0x00,/*"E",37*/
  0x04,0xFC,0x24,0x74,0x0C,0x00,0x02,0x03,0x02,0x00,0x00,0x00,/*"F",38*/
  0xF0,0x08,0x04,0x44,0xCC,0x40,0x00,0x01,0x02,0x02,0x01,0x00,/*"G",39*/
  0x04,0xFC,0x20,0x20,0xFC,0x04,0x02,0x03,0x00,0x00,0x03,0x02,/*"H",40*/
  0x04,0x04,0xFC,0x04,0x04,0x00,0x02,0x02,0x03,0x02,0x02,0x00,/*"I",41*/
  0x00,0x04,0x04,0xFC,0x04,0x04,0x0C,0x08,0x08,0x07,0x00,0x00,/*"J",42*/
  0x04,0xFC,0x24,0x50,0x8C,0x04,0x02,0x03,0x02,0x00,0x03,0x02,/*"K",43*/
  0x04,0xFC,0x04,0x00,0x00,0x00,0x02,0x03,0x02,0x02,0x02,0x03,/*"L",44*/
  0xFC,0x3C,0xC0,0x3C,0xFC,0x04,0x03,0x00,0x03,0x00,0x03,0x02,/*"M",45*/
  0x04,0xFC,0x30,0xC4,0xFC,0x04,0x02,0x03,0x02,0x00,0x03,0x00,/*"N",46*/
  0xF8,0x04,0x04,0x04,0xF8,0x00,0x01,0x02,0x02,0x02,0x01,0x00,/*"O",47*/
  0x04,0xFC,0x24,0x24,0x18,0x00,0x02,0x03,0x02,0x00,0x00,0x00,/*"P",48*/
  0xF8,0x84,0x84,0x04,0xF8,0x00,0x01,0x02,0x02,0x07,0x05,0x00,/*"Q",49*/
  0x04,0xFC,0x24,0x64,0x98,0x00,0x02,0x03,0x02,0x00,0x03,0x02,/*"R",50*/
  0x18,0x24,0x24,0x44,0x8C,0x00,0x03,0x02,0x02,0x02,0x01,0x00,/*"S",51*/
  0x0C,0x04,0xFC,0x04,0x0C,0x00,0x00,0x02,0x03,0x02,0x00,0x00,/*"T",52*/
  0x04,0xFC,0x00,0x00,0xFC,0x04,0x00,0x01,0x02,0x02,0x01,0x00,/*"U",53*/
  0x04,0x7C,0x80,0xE0,0x1C,0x04,0x00,0x00,0x03,0x00,0x00,0x00,/*"V",54*/
  0x3C,0xC0,0x7C,0xC0,0x3C,0x00,0x00,0x03,0x00,0x03,0x00,0x00,/*"W",55*/
  0x04,0x9C,0x60,0x9C,0x04,0x00,0x02,0x03,0x00,0x03,0x02,0x00,/*"X",56*/
  0x04,0x3C,0xC0,0x3C,0x04,0x00,0x00,0x02,0x03,0x02,0x00,0x00,/*"Y",57*/
  0x0C,0x84,0x64,0x1C,0x04,0x00,0x02,0x03,0x02,0x02,0x03,0x00,/*"Z",58*/
  0x00,0x00,0xFF,0x01,0x01,0x00,0x00,0x00,0x07,0x04,0x04,0x00,/*"[",59*/
  0x00,0x06,0x38,0xC0,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x00,/*"\",60*/
  0x00,0x01,0x01,0xFF,0x00,0x00,0x00,0x04,0x04,0x07,0x00,0x00,/*"]",61*/
  0x00,0x02,0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"^",62*/
  0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,/*"_",63*/
  0x00,0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"`",64*/
  0x00,0x40,0xA0,0xA0,0xC0,0x00,0x00,0x01,0x02,0x02,0x03,0x02,/*"a",65*/
  0x02,0xFE,0x20,0x20,0xC0,0x00,0x00,0x03,0x02,0x02,0x01,0x00,/*"b",66*/
  0x00,0xC0,0x20,0x20,0x60,0x00,0x00,0x01,0x02,0x02,0x01,0x00,/*"c",67*/
  0x00,0xC0,0x20,0x22,0xFE,0x00,0x00,0x01,0x02,0x02,0x03,0x02,/*"d",68*/
  0x00,0xC0,0xA0,0xA0,0xC0,0x00,0x00,0x01,0x02,0x02,0x02,0x00,/*"e",69*/
  0x00,0x20,0xFC,0x22,0x22,0x04,0x00,0x02,0x03,0x02,0x02,0x00,/*"f",70*/
  0x00,0x40,0xA0,0xA0,0x60,0x20,0x00,0x05,0x0A,0x0A,0x0A,0x04,/*"g",71*/
  0x02,0xFE,0x20,0x20,0xC0,0x00,0x02,0x03,0x02,0x00,0x03,0x02,/*"h",72*/
  0x00,0x20,0xE6,0x00,0x00,0x00,0x00,0x02,0x03,0x02,0x00,0x00,/*"i",73*/
  0x00,0x00,0x20,0xE6,0x00,0x00,0x08,0x08,0x08,0x07,0x00,0x00,/*"j",74*/
  0x02,0xFE,0x80,0x60,0x20,0x00,0x02,0x03,0x00,0x01,0x02,0x00,/*"k",75*/
  0x02,0x02,0xFE,0x00,0x00,0x00,0x02,0x02,0x03,0x02,0x02,0x00,/*"l",76*/
  0xE0,0x20,0xE0,0x20,0xC0,0x00,0x03,0x00,0x03,0x00,0x03,0x00,/*"m",77*/
  0x20,0xE0,0x20,0x20,0xC0,0x00,0x02,0x03,0x02,0x00,0x03,0x02,/*"n",78*/
  0x00,0xC0,0x20,0x20,0xC0,0x00,0x00,0x01,0x02,0x02,0x01,0x00,/*"o",79*/
  0x20,0xE0,0x20,0x20,0xC0,0x00,0x08,0x0F,0x0A,0x02,0x01,0x00,/*"p",80*/
  0x00,0xC0,0x20,0x20,0xE0,0x00,0x00,0x01,0x02,0x0A,0x0F,0x08,/*"q",81*/
  0x20,0xE0,0x40,0x20,0x20,0x00,0x02,0x03,0x02,0x00,0x00,0x00,/*"r",82*/
  0x00,0x60,0xA0,0xA0,0x20,0x00,0x00,0x02,0x02,0x02,0x03,0x00,/*"s",83*/
  0x00,0x20,0xF8,0x20,0x20,0x00,0x00,0x00,0x03,0x02,0x02,0x00,/*"t",84*/
  0x20,0xE0,0x00,0x20,0xE0,0x00,0x00,0x01,0x02,0x02,0x03,0x02,/*"u",85*/
  0x20,0xE0,0x00,0xE0,0x20,0x00,0x00,0x00,0x03,0x00,0x00,0x00,/*"v",86*/
  0x60,0x80,0xE0,0x80,0x60,0x00,0x00,0x03,0x00,0x03,0x00,0x00,/*"w",87*/
  0x20,0x60,0x80,0x60,0x20,0x00,0x02,0x03,0x00,0x03,0x02,0x00,/*"x",88*/
  0x20,0xE0,0x00,0x00,0xE0,0x20,0x08,0x08,0x05,0x03,0x00,0x00,/*"y",89*/
  0x00,0x20,0xA0,0x60,0x20,0x00,0x00,0x02,0x03,0x02,0x02,0x00,/*"z",90*/
  0x00,0x00,0x20,0xFF,0x01,0x00,0x00,0x00,0x00,0x07,0x04,0x00,/*"{",91*/
  0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x0F,0x00,0x00,/*"|",92*/
  0x00,0x01,0xDF,0x20,0x00,0x00,0x00,0x04,0x07,0x00,0x00,0x00,/*"}",93*/
  0x02,0x01,0x01,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"~",94*/

};
/****************************************8*16的点阵************************************/
const unsigned char asc_1608[]=	  
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*" ",0*/
  0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x00,0x00,0x00,0x00,/*"!",1*/
  0x00,0x10,0x0C,0x02,0x10,0x0C,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*""",2*/
  0x00,0x40,0xC0,0x78,0x40,0xC0,0x78,0x00,0x00,0x04,0x3F,0x04,0x04,0x3F,0x04,0x00,/*"#",3*/
  0x00,0x70,0x88,0x88,0xFC,0x08,0x30,0x00,0x00,0x18,0x20,0x20,0xFF,0x21,0x1E,0x00,/*"$",4*/
  0xF0,0x08,0xF0,0x80,0x60,0x18,0x00,0x00,0x00,0x31,0x0C,0x03,0x1E,0x21,0x1E,0x00,/*"%",5*/
  0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,0x1E,0x21,0x23,0x2C,0x19,0x27,0x21,0x10,/*"&",6*/
  0x00,0x12,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"'",7*/
  0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,/*"(",8*/
  0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,/*")",9*/
  0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,/*"*",10*/
  0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x0F,0x01,0x01,0x01,/*"+",11*/
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x70,0x00,0x00,0x00,0x00,0x00,/*",",12*/
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00,/*"-",13*/
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,/*".",14*/
  0x00,0x00,0x00,0x00,0xC0,0x38,0x04,0x00,0x00,0x60,0x18,0x07,0x00,0x00,0x00,0x00,/*"/",15*/
  0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,/*"0",16*/
  0x00,0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,/*"1",17*/
  0x00,0x70,0x08,0x08,0x08,0x08,0xF0,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,/*"2",18*/
  0x00,0x30,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x18,0x20,0x21,0x21,0x22,0x1C,0x00,/*"3",19*/
  0x00,0x00,0x80,0x40,0x30,0xF8,0x00,0x00,0x00,0x06,0x05,0x24,0x24,0x3F,0x24,0x24,/*"4",20*/
  0x00,0xF8,0x88,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x20,0x20,0x20,0x11,0x0E,0x00,/*"5",21*/
  0x00,0xE0,0x10,0x88,0x88,0x90,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x20,0x1F,0x00,/*"6",22*/
  0x00,0x18,0x08,0x08,0x88,0x68,0x18,0x00,0x00,0x00,0x00,0x3E,0x01,0x00,0x00,0x00,/*"7",23*/
  0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,/*"8",24*/
  0x00,0xF0,0x08,0x08,0x08,0x10,0xE0,0x00,0x00,0x01,0x12,0x22,0x22,0x11,0x0F,0x00,/*"9",25*/
  0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,/*":",26*/
  0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,/*";",27*/
  0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,/*"<",28*/
  0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x00,/*"=",29*/
  0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,/*">",30*/
  0x00,0x70,0x48,0x08,0x08,0x88,0x70,0x00,0x00,0x00,0x00,0x30,0x37,0x00,0x00,0x00,/*"?",31*/
  0xC0,0x30,0xC8,0x28,0xE8,0x10,0xE0,0x00,0x07,0x18,0x27,0x28,0x2F,0x28,0x17,0x00,/*"@",32*/
  0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20,/*"A",33*/
  0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00,/*"B",34*/
  0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,/*"C",35*/
  0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00,/*"D",36*/
  0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00,/*"E",37*/
  0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,/*"F",38*/
  0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00,/*"G",39*/
  0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20,/*"H",40*/
  0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,/*"I",41*/
  0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00,/*"J",42*/
  0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00,/*"K",43*/
  0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00,/*"L",44*/
  0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,0x20,0x3F,0x01,0x3E,0x01,0x3F,0x20,0x00,/*"M",45*/
  0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00,/*"N",46*/
  0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00,/*"O",47*/
  0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00,/*"P",48*/
  0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x28,0x28,0x30,0x50,0x4F,0x00,/*"Q",49*/
  0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20,/*"R",50*/
  0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00,/*"S",51*/
  0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,/*"T",52*/
  0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,/*"U",53*/
  0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00,/*"V",54*/
  0x08,0xF8,0x00,0xF8,0x00,0xF8,0x08,0x00,0x00,0x03,0x3E,0x01,0x3E,0x03,0x00,0x00,/*"W",55*/
  0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20,/*"X",56*/
  0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,/*"Y",57*/
  0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00,/*"Z",58*/
  0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,/*"[",59*/
  0x00,0x04,0x38,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00,/*"\",60*/
  0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,/*"]",61*/
  0x00,0x00,0x04,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"^",62*/
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,/*"_",63*/
  0x00,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"`",64*/
  0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x19,0x24,0x24,0x12,0x3F,0x20,0x00,/*"a",65*/
  0x10,0xF0,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00,/*"b",66*/
  0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00,/*"c",67*/
  0x00,0x00,0x80,0x80,0x80,0x90,0xF0,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,/*"d",68*/
  0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x24,0x24,0x24,0x24,0x17,0x00,/*"e",69*/
  0x00,0x80,0x80,0xE0,0x90,0x90,0x20,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,/*"f",70*/
  0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00,/*"g",71*/
  0x10,0xF0,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,/*"h",72*/
  0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,/*"i",73*/
  0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,/*"j",74*/
  0x10,0xF0,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x06,0x29,0x30,0x20,0x00,/*"k",75*/
  0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,/*"l",76*/
  0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,/*"m",77*/
  0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,/*"n",78*/
  0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,/*"o",79*/
  0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0x91,0x20,0x20,0x11,0x0E,0x00,/*"p",80*/
  0x00,0x00,0x00,0x80,0x80,0x00,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0x91,0xFF,0x80,/*"q",81*/
  0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00,/*"r",82*/
  0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00,/*"s",83*/
  0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x10,0x00,/*"t",84*/
  0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,/*"u",85*/
  0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x03,0x0C,0x30,0x0C,0x03,0x00,0x00,/*"v",86*/
  0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x01,0x0E,0x30,0x0C,0x07,0x38,0x06,0x01,/*"w",87*/
  0x00,0x80,0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x20,0x31,0x0E,0x2E,0x31,0x20,0x00,/*"x",88*/
  0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x81,0x86,0x78,0x18,0x06,0x01,0x00,/*"y",89*/
  0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00,/*"z",90*/
  0x00,0x00,0x00,0x00,0x00,0xFC,0x02,0x02,0x00,0x00,0x00,0x00,0x01,0x3E,0x40,0x40,/*"{",91*/
  0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,/*"|",92*/
  0x02,0x02,0xFC,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x3E,0x01,0x00,0x00,0x00,0x00,/*"}",93*/
  0x00,0x02,0x01,0x02,0x02,0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"~",94*/
};


/****************************************************汉字*********************************************************/
const unsigned char hz_1206[] = 
{
  0x00,0xDF,0x95,0x95,0x95,0xF5,0x95,0x95,0x95,0x9F,0x00,0x00,
	0x09,0x08,0x0A,0x0A,0x0A,0x0F,0x0A,0x0A,0x0A,0x08,0x08,0x00,/*"星",0*/
  
  0x04,0xFF,0x54,0x54,0xFF,0x04,0x00,0xFE,0x92,0x92,0xFE,0x00,
	0x09,0x05,0x01,0x01,0x05,0x09,0x08,0x07,0x00,0x08,0x0F,0x00,/*"期",1*/
  
  0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"一",2*/
  
  0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,/*"二",3*/
  
  0x00,0x02,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x02,0x00,0x00,
	0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,/*"三",4*/
  
  0x00,0xFE,0x02,0x82,0x7E,0x02,0x02,0x7E,0x82,0x82,0xFE,0x00,
	0x00,0x0F,0x05,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x0F,0x00,/*"四",5*/
  
  0x02,0x22,0x22,0xE2,0x3E,0x22,0x22,0x22,0xE2,0x02,0x00,0x00,
  0x08,0x08,0x0E,0x09,0x08,0x08,0x08,0x08,0x0F,0x08,0x08,0x00,/*"五",6*/
  
  0x10,0x10,0x10,0xD0,0x11,0x16,0x10,0x50,0x90,0x10,0x10,0x00,
  0x08,0x04,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0C,0x00,/*"六",7*/
  
  0x00,0xFE,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0xFE,0x00,0x00,
  0x00,0x0F,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x0F,0x00,0x00,/*"日",8*/
  
  0x02,0x05,0x02,0xF8,0x04,0x02,0x02,0x02,0x04,0x0E,0x80,0x00,
  0x00,0x00,0x00,0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00,/*"℃",9*/
	
	0x00,0x00,0xFE,0x92,0x92,0x92,0x92,0x92,0x92,0xFE,0x00,0x00,
	0x08,0x06,0x01,0x00,0x00,0x00,0x00,0x08,0x08,0x0F,0x00,0x00,/*"月",10*/
};

const unsigned char hz_1608[] = 
{	 
  0x00,0x00,0x00,0xBE,0x2A,0x2A,0x2A,0xEA,0x2A,0x2A,0x2A,0x3E,0x00,0x00,0x00,0x00,
  0x00,0x44,0x42,0x49,0x49,0x49,0x49,0x7F,0x49,0x49,0x49,0x49,0x41,0x40,0x00,0x00,/*"星",0*/
  
  0x00,0x04,0xFF,0x24,0x24,0x24,0xFF,0x04,0x00,0xFE,0x22,0x22,0x22,0xFE,0x00,0x00,
  0x88,0x48,0x2F,0x09,0x09,0x19,0xAF,0x48,0x30,0x0F,0x02,0x42,0x82,0x7F,0x00,0x00,/*"期",1*/
  
  0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"一",2*/
    
  0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00,
  0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,/*"二",3*/
    
  0x00,0x04,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x04,0x00,0x00,
  0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,/*"三",4*/
    
  0x00,0xFC,0x04,0x04,0x04,0xFC,0x04,0x04,0x04,0xFC,0x04,0x04,0x04,0xFC,0x00,0x00,
  0x00,0x7F,0x28,0x24,0x23,0x20,0x20,0x20,0x20,0x21,0x22,0x22,0x22,0x7F,0x00,0x00,/*"四",5*/
    
  0x00,0x02,0x42,0x42,0x42,0xC2,0x7E,0x42,0x42,0x42,0x42,0xC2,0x02,0x02,0x00,0x00,
  0x40,0x40,0x40,0x40,0x78,0x47,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x00,/*"五",6*/
    
  0x20,0x20,0x20,0x20,0x20,0x20,0x21,0x22,0x2C,0x20,0x20,0x20,0x20,0x20,0x20,0x00,
  0x00,0x40,0x20,0x10,0x0C,0x03,0x00,0x00,0x00,0x01,0x02,0x04,0x18,0x60,0x00,0x00,/*"六",7*/
    
  0x00,0x00,0x00,0xFE,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0xFE,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0xFF,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0xFF,0x00,0x00,0x00,0x00,/*"日",8*/
	
};


/****************************************************图片*********************************************************/
const unsigned char BMP_four[] =
{
	0x3C,0xE7,0x81,0xBD,0xBD,0x81,0xBD,0xBD,0x81,0xBD,0xBD,0x81,0xBD,0xBD,0x81,0xFF, /*80~ 100 4格满电*/
};

const unsigned char BMP_three[] =
{
	0x3C,0xE7,0x81,0x81,0x81,0x81,0xBD,0xBD,0x81,0xBD,0xBD,0x81,0xBD,0xBD,0x81,0xFF, /*60~ 80 3格电*/
};

const unsigned char BMP_two[] =
{
	0x3C,0xE7,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0xBD,0xBD,0x81,0xBD,0xBD,0x81,0xFF, /*40~ 60 2格电*/
};

const unsigned char BMP_one[] =
{
	0x3C,0xE7,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0xBD,0xBD,0x81,0xFF, /*20~ 40 1格电*/
};

const unsigned char BMP_zero[] =
{
	0x3C,0xE7,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0xFF, /*0~20 0格电*/
};

const unsigned char BMP_none[] =
{
	0x3C,0xE7,0x81,0x00,0x81,0x00,0x81,0x00,0x81,0x00,0x81,0x00,0x81,0x00,0x81,0xFF, /*无电池*/
};

#endif


