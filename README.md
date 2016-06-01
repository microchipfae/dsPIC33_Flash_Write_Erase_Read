# Flash Er/Wr/Rd example for dsPIC33 Family

----------
#### <i class="icon-file"></i> Summary - Simple example of how to:
1. Erase a small portion of Flash
2. Write data to Flash
3. Read data from Flash
4. Using `#include <libpic30.h>`

Coded for:
> MICROSTICK dsPIC33FJ64MC802
> PIM dsPIC33FJ256GP710A

Tools:
> MPLAB X  v3.30
> XC16 v1.26

----------
**Known issues:**
<i class="icon-cog"></i> MPLABX **Read Device Memory** for Microstick is grayed out; will not see accurate Program memory contents.
<i class="icon-cog"></i>  This works OK for the Explorer 16 + PIM using ICD3 however.

Source:
>main.c
>traps.c
>config_regs.c

Configurations:
>MICROSTICK
>PIM_dsPIC33FJ256GP710A

Links:

[Microchip Main Site](http://www.microchip.com) for all Microchip products.
**GITHUB Syntax**  [github formatting](https://help.github.com/articles/basic-writing-and-formatting-syntax/) 
**Support StackEdit** [Online Markdown Editor](https://stackedit.io/editor) 
**Another** [Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Here-Cheatsheet) 

---------

dsPIC33_Flash_Write_Erase_Read

Created for Joel F., May 2016:

```flow
st=>start: Start
e=>end
op=>operation: Olive Running
cond=>condition: Yes or No?
st->op->cond
cond(yes)->e
cond(no)->op
```

---
	Copyright (c) 2016 released Microchip Technology Inc.  All rights reserved.
	
	Microchip licenses to you the right to use, modify, copy and distribute
	Software only when embedded on a Microchip microcontroller or digital signal
	controller that is integrated into your product or third party product
	(pursuant to the sublicense terms in the accompanying license agreement).
	
	You should refer to the license agreement accompanying this Software for
	additional information regarding your rights and obligations.
	
	SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
	EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
	MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
	IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
	CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
	OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
	INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
	CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
	SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
	(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
