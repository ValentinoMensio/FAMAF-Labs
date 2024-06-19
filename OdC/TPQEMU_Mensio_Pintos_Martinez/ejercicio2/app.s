.equ SCREEN_WIDTH,     	640
.equ SCREEN_HEIGH,     	480
.equ BITS_PER_PIXEL,  	32


.globl main

main:
	// X0 contiene la direccion base del framebuffer
 	mov x20, x0	// Save framebuffer base address to x20    
	//---------------- CODE HERE ------------------------------------

	mov x4, #1
	mov x5, xzr
	mov x6, xzr

//
InfLoop:
	add x8, xzr, xzr
	add x8, x8, #0xFFF    
	lsl x8, x8, #7     //Creo un numero grande (0xFFF^~15)  	

longDelayloop:
	cbz x8, longDelayEnd	// si x8 es igual a 0 termino delay
	ldur x9, [sp, #0]
	stur x9, [sp, #0]
	sub x8, x8, #1
	b longDelayloop

longDelayEnd:

	//FONDO
	mov x0,x20
	movz x10, 0x18, lsl 16    
	movk x10, 0x0038, lsl 00

	mov x2, SCREEN_HEIGH     	// Y Size
loop1:
	mov x1, SCREEN_WIDTH     	// X Size
loop0:
	stur w10,[x0]   	// Set color of pixel N
	add x0,x0,4   		// Next pixel
	sub x1,x1,1   		// decrement X counter
	cbnz x1,loop0   	// If not end row jump
	sub x2,x2,1   		// Decrement Y counter
	cbnz x2,loop1   	// if not last row, jump

	add x5,x5,#10


	//EDIFICIOS
	movz x10, 0x00, lsl 16
	mov x8, #100	
	mov x9, #160
	mov x17, #0
	add x17,x17,x5
	mov x18, #320
	bl big_hline
    
	//PARTE DE ADENTRO
	movz x10, 0x20, lsl 16
	movk x10, 0x2020, lsl 0
	mov x8, #80
	mov x9, #150
	mov x17, #10
	add x17,x17,x5
	mov x18, #330
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #20
	mov x9, #20
	mov x17, #20
	add x17,x17,x5
	mov x18, #340
	bl big_hline
    
	movz x10, 0x00
	mov x8, #20
	mov x9, #20
	mov x17, #60
	add x17,x17,x5
	mov x18, #340
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #20
	mov x9, #20
	mov x17, #20
	add x17,x17,x5
	mov x18, #380
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #20
	mov x9, #20
	mov x17, #60
	add x17,x17,x5
	mov x18, #380
	bl big_hline
    
	movz x10, 0x00
	mov x8, #20
	mov x9, #20
	mov x17, #20
	add x17,x17,x5
	mov x18, #420
	bl big_hline
    
	movz x10, 0x00
	mov x8, #20
	mov x9, #20
	mov x17, #60
	add x17,x17,x5
	mov x18, #420
	bl big_hline
    
	//EDIFICIO2
	bl big_hline
	movz x10, 0x00
	mov x8, #100
	mov x9, #80
	mov x17, #100
	add x17,x17,x5
	mov x18, #400
	bl big_hline
    
	//PARTE DE ADENTRO 2
	movz x10, 0x20, lsl 16    
	movk x10, 0x2020, lsl 0	 
	mov x8, #90
	mov x9, #70
	mov x17, #105
	add x17,x17,x5
	mov x18, #410
	bl big_hline
    
	movz x10, 0x00
	mov x8, #20
	mov x9, #20
	mov x17, #115
	add x17,x17,x5
	mov x18, #420
	bl big_hline
    
	movz x10, 0x00
	mov x8, #20
	mov x9, #20
	mov x17, #165
	add x17,x17,x5
	mov x18, #420
	bl big_hline
    
	//EDIFICIO 3
	movz x10, 0x00
	mov x8, #75
	mov x9, #280 
	mov x17, #200
	add x17,x17,x5
	mov x18, #200
	bl big_hline
    
	//PARTE DE ADENTRO 3
	movz x10, 0x20, lsl 16
	movk x10, 0x2020, lsl 0
	mov x8, #55
	mov x9, #270
	mov x17, #210
	add x17,x17,x5
	mov x18, #210
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #15
	mov x9, #15
	mov x17, #240
	add x17,x17,x5
	mov x18, #220
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #15
	mov x9, #15
	mov x17, #220
	add x17,x17,x5
	mov x18, #220
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #15
	mov x9, #15
	mov x17, #240
	add x17,x17,x5
	mov x18, #260
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #15
	mov x9, #15
	mov x17, #220
	add x17,x17,x5
	mov x18, #260
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #15
	mov x9, #15
	mov x17, #240
	add x17,x17,x5
	mov x18, #300
	bl big_hline
    
	movz x10, 0x00
	mov x8, #15
	mov x9, #15
	mov x17, #220
	add x17,x17,x5
	mov x18, #300
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #15
	mov x9, #15
	mov x17, #240
	add x17,x17,x5
	mov x18, #340
	bl big_hline
    
	movz x10, 0x00
	mov x8, #15
	mov x9, #15
	mov x17, #220
	add x17,x17,x5
	mov x18, #340
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #15
	mov x9, #15
	mov x17, #240
	add x17,x17,x5
	mov x18, #380
	bl big_hline
    
	movz x10, 0x00
	mov x8, #15
	mov x9, #15
	mov x17, #220
	add x17,x17,x5
	mov x18, #380
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #15
	mov x9, #15
	mov x17, #240
	add x17,x17,x5
	mov x18, #420
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #15
	mov x9, #15
	mov x17, #220
	add x17,x17,x5
	mov x18, #420
	bl big_hline
    
	//EDIFICIO 4
	movz x10, 0x00
	mov x8, #90
	mov x9, #130
	mov x17, #275
	add x17,x17,x5
	mov x18, #350
	bl big_hline
    
	//PARTE DE ADENTRO 4
	movz x10, 0x20, lsl 16
	movk x10, 0x2020, lsl 0
	mov x8, #75
	mov x9, #120
	mov x17, #280
	add x17,x17,x5
	mov x18, #360
	bl big_hline
    
	movz x10, 0x00
	mov x8, #20
	mov x9, #20
	mov x17, #290
	add x17,x17,x5
	mov x18, #370
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #20
	mov x9, #20
	mov x17, #325
	add x17,x17,x5
	mov x18, #370
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #20
	mov x9, #20
	mov x17, #290
	add x17,x17,x5
	mov x18, #410
	bl big_hline
    
	movz x10, 0x00
	mov x8, #20
	mov x9, #20
	mov x17, #325
	add x17,x17,x5
	mov x18, #410
	bl big_hline
    
	movz x10, 0x00
	mov x8, #20
	mov x9, #20
	mov x17, #290
	add x17,x17,x5
	mov x18, #450
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #20
	mov x9, #20
	mov x17, #325
	add x17,x17,x5
	mov x18, #450
	bl big_hline
    
	//EDIFICIO 5
	movz x10, 0x00
	mov x8, #100
	mov x9, #115
	mov x17, #365
	add x17,x17,x5
	mov x18, #400
	bl big_hline
    
	//PARTE DE ADENTRO 5
	movz x10, 0x20, lsl 16
	movk x10, 0x2020, lsl 0
	mov x8, #80
	mov x9, #105
	mov x17, #375
	add x17,x17,x5
	mov x18, #410
	bl big_hline
    
	movz x10, 0x00
	mov x8, #20
	mov x9, #20
	mov x17, #385
	add x17,x17,x5
	mov x18, #420
	bl big_hline
    
	movz x10, 0x00
	mov x8, #20
	mov x9, #20
	mov x17, #425
	add x17,x17,x5
	mov x18, #420
	bl big_hline
    
	movz x10, 0x00
	mov x8, #20
	mov x9, #20
	mov x17, #385
	add x17,x17,x5
	mov x18, #450
	bl big_hline
    
	movz x10, 0x00
	mov x8, #20
	mov x9, #20
	mov x17, #425
	add x17,x17,x5
	mov x18, #450
	bl big_hline
    
	//EDIFICIO 6
	movz x10, 0x00
	mov x8, #75
	mov x9, #280
	mov x17, #465
	add x17,x17,x5
	mov x18, #200
	bl big_hline
    
	//PARTE DE ADENTRO 6
	movz x10, 0x20, lsl 16
	movk x10, 0x2020, lsl 0
	mov x8, #55
	mov x9, #270
	mov x17, #475
	add x17,x17,x5
	mov x18, #210
	bl big_hline
    
	movz x10, 0x00
	mov x8, #15
	mov x9, #15
	mov x17, #485
	add x17,x17,x5
	mov x18, #225
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #15
	mov x9, #15
	mov x17, #505
	add x17,x17,x5
	mov x18, #225
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #15
	mov x9, #15
	mov x17, #485
	add x17,x17,x5
	mov x18, #265
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #15
	mov x9, #15
	mov x17, #505
	add x17,x17,x5
	mov x18, #265
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #15
	mov x9, #15
	mov x17, #485
	add x17,x17,x5
	mov x18, #305
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #15
	mov x9, #15
	mov x17, #505
	add x17,x17,x5
	mov x18, #305
	bl big_hline
    
	movz x10, 0x00
	mov x8, #15
	mov x9, #15
	mov x17, #485
	add x17,x17,x5
	mov x18, #345
	bl big_hline
    
	movz x10, 0x00
	mov x8, #15
	mov x9, #15
	mov x17, #505
	add x17,x17,x5
	mov x18, #345
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #15
	mov x9, #15
	mov x17, #485
	add x17,x17,x5
	mov x18, #385
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #15
	mov x9, #15
	mov x17, #505
	add x17,x17,x5
	mov x18, #385
	bl big_hline
    
	movz x10, 0x00
	mov x8, #15
	mov x9, #15
	mov x17, #485
	add x17,x17,x5
	mov x18, #425
	bl big_hline
    
	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #15
	mov x9, #15
	mov x17, #505
	add x17,x17,x5
	mov x18, #425
	bl big_hline
    
	//EDIFICIO 7
	movz x10, 0x00
	mov x8, #100
	mov x9, #120
	mov x17, #540
	add x17,x17,x5
	mov x18, #360
	bl big_hline

	//PARTE DE ADENTRO 7
	movz x10, 0x20, lsl 16
	movk x10, 0x2020, lsl 0
	mov x8, #80	
	mov x9, #110
	mov x17, #550
	add x17,x17,x5
	mov x18, #370
	bl big_hline

	movz x10, 0x00
	mov x8, #20
	mov x9, #20
	mov x17, #560
	add x17,x17,x5
	mov x18, #385
	bl big_hline

	movz x10, 0xCC, lsl 16
	movk x10, 0xCC00, lsl 0
	mov x8, #20
	mov x9, #20
	mov x17, #600
	add x17,x17,x5
	mov x18, #385
	bl big_hline

	movz x10, 0x00
	mov x8, #20
	mov x9, #20
	mov x17, #560
	add x17,x17,x5
	mov x18, #425
	bl big_hline

	movz x10, 0x00
	mov x8, #20
	mov x9, #20
	mov x17, #600
	add x17,x17,x5
	mov x18, #425
	bl big_hline

	//LUNA
	movz x10, 0x002F, lsl 16	//cambio color
	movk x10, 0x1A3C, lsl 00	//cambio color
	mov x11, #80	//radio
	mov x15, #90	//X
	add x15,x15,x6
	mov x16, #100	//Y
	mov x9, #2
	mov x8, #2
	bl circulo

	movz x10, 0x00FF, lsl 16	//cambio color
	movk x10, 0xFF66, lsl 00	//cambio color
	mov x11, #50	//radio
	mov x15, #90	//X
	add x15,x15,x6
	mov x16, #100	//Y
	mov x9, #2
	mov x8, #2
	bl circulo

	subs x4, x4, #1
	cbz x4, frame1
	b frame2


frame1:

	//Arcoiris
    //Rojo

    movz x10, 0x00FF, lsl 16
	mov x8, #30    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #0		//X
	mov x18, #145 	//Y
	bl big_hline

	movz x10, 0x00FF, lsl 16    
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #89	//X
	mov x18, #145 	//Y
	bl big_hline

    movz x10, 0x00FF, lsl 16    
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #149  	//X
	mov x18, #158	//Y
	bl big_hline

    movz x10, 0x00FF, lsl 16   
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #29	//X
	mov x18, #158	//Y
	bl big_hline

    //Naranja

	movz x10, 0x00FF, lsl 16
    movk x10, 0x8000, lsl 00   
    mov x8, #30    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #0		//X
	mov x18, #165	//Y
	bl big_hline

	movz x10, 0x00FF, lsl 16
    movk x10, 0x8000, lsl 00  
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #89	//X
	mov x18, #165	//Y
	bl big_hline

    movz x10, 0x00FF, lsl 16
    movk x10, 0x8000, lsl 00    
	mov x8, #60    	//Xsize
	mov x9, #20   	//Ysize
	mov x17, #149  	//X
	mov x18, #178	//Y
	bl big_hline

    movz x10, 0x00FF, lsl 16
    movk x10, 0x8000, lsl 00   
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #29	//X
	mov x18, #178	//Y
	bl big_hline

    //Amarillo

    movz x10, 0x00FF, lsl 16
    movk x10, 0xFF00, lsl 00   
    mov x8, #30    	//Xsize
	mov x9, #25    	//Ysize
	mov x17, #0		//X
	mov x18, #185	//Y
	bl big_hline

    movz x10, 0x00FF, lsl 16
    movk x10, 0xFF00, lsl 00
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #89	//X
	mov x18, #185	//Y
	bl big_hline

    movz x10, 0x00FF, lsl 16
    movk x10, 0xFF00, lsl 00   
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #149  	//X
	mov x18, #198	//Y
	bl big_hline

    movz x10, 0x00FF, lsl 16
    movk x10, 0xFF00, lsl 00  
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #29	//X
	mov x18, #198	//Y
	bl big_hline

    //Verde

    movz x10, 0x0000, lsl 16
    movk x10, 0xFF00, lsl 00	 
    mov x8, #30    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #0		//X
	mov x18, #205	//Y
	bl big_hline

    movz x10, 0x0000, lsl 16
    movk x10, 0xFF00, lsl 00    
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #89	//X
	mov x18, #205	//Y
	bl big_hline

    movz x10, 0x0000, lsl 16
    movk x10, 0xFF00, lsl 00   
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #149  	//X
	mov x18, #218	//Y
	bl big_hline

    movz x10, 0x0000, lsl 16
    movk x10, 0xFF00, lsl 00  
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #29	//X
	mov x18, #218	//Y
	bl big_hline

    //Celeste

    movz x10, 0x0037, lsl 16
    movk x10, 0x60F8, lsl 00    
    mov x8, #30    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #0		//X
	mov x18, #225	//Y
	bl big_hline

    movz x10, 0x0037, lsl 16
    movk x10, 0x60F8, lsl 00  
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #89	//X
	mov x18, #225	//Y
	bl big_hline

    movz x10, 0x0037, lsl 16
    movk x10, 0x60F8, lsl 00   
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #149  	//X
	mov x18, #238	//Y
	bl big_hline

    movz x10, 0x0037, lsl 16
    movk x10, 0x60F8, lsl 00   
	mov x8, #60    	//Xsize
	mov x9, #25    	//Ysize
	mov x17, #29	//X
	mov x18, #238	//Y
	bl big_hline

    //Violeta

    movz x10, 0x006C, lsl 16
    movk x10, 0x0AFF, lsl 00    
    mov x8, #30    	//Xsize
	mov x9, #20   	//Ysize
	mov x17, #0		//X
	mov x18, #245	//Y
	bl big_hline

    movz x10, 0x006C, lsl 16
    movk x10, 0x0AFF, lsl 00
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #89	//X
	mov x18, #245	//Y
	bl big_hline

    movz x10, 0x006C, lsl 16
    movk x10, 0x0AFF, lsl 00  
    mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #149  	//X
	mov x18, #258	//Y
	bl big_hline

    movz x10, 0x006C, lsl 16
    movk x10, 0x0AFF, lsl 00  
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #29	//X
	mov x18, #258	//Y
	bl big_hline

	add x6,x6,#1
	//PATAS IZQ
	movz x10, 0x009B, lsl 16	//cambio color
	movk x10, 0x9B9D, lsl 00	//cambio color
	mov x11,#20    	//radio
	mov x15, #250	//X
	mov x16, #320	//Y
	mov x9, #2
	mov x8, #2
	bl circulo

	movz x10, 0x009B, lsl 16	//cambio color
	movk x10, 0x9B9D, lsl 00	//cambio color
	mov x11,#20    	//radio
	mov x15, #220	//X
	mov x16, #290	//Y
	mov x9, #2
	mov x8, #8
	bl circulo

	//PATAS DER
	movz x10, 0x009B, lsl 16	//cambio color
	movk x10, 0x9B9D, lsl 00	//cambio color
	mov x11,#20    	//radio
	mov x15, #380	//X
	mov x16, #320	//Y
	mov x9, #2
	mov x8, #2
	bl circulo

	movz x10, 0x009B, lsl 16	//cambio color
	movk x10, 0x9B9D, lsl 00	//cambio color
	mov x11,#20    	//radio
	mov x15, #450	//X
	mov x16, #320	//Y
	mov x9, #2
	mov x8, #2
	bl circulo

	//CUERPO
	movz x10, 0x00F6, lsl 16	//cambio color
	movk x10, 0xC09D, lsl 00	//cambio color
	mov x11,#90    	//radio
	mov x15, #345	//X
	mov x16, #220	//Y
	mov x9, #5
	mov x8, #50
	bl circulo

	//CUERPO MEDIO
	movz x10, 0x00FA, lsl 16	//cambio color
	movk x10, 0x96F6, lsl 00	//cambio color
	mov x11,#70	//radio
	mov x15, #345	//X
	mov x16, #220	//Y
	mov x9, #5
	mov x8, #50
	bl circulo

	//CABEZA
	movz x10, 0x009B, lsl 16	//cambio color
	movk x10, 0x9B9D, lsl 00	//cambio color
	mov x11,#70	//radio
	mov x15, #450	//X
	mov x16, #240	//Y
	mov x9, #2
	mov x8, #40
	bl circulo

	//OREJAS
	movz x10, 0x009B, lsl 16	//cambio color
	movk x10, 0x9B9D, lsl 00	//cambio color
	mov x11, #0    	//Triangulo para arriba #0, abajo #1
	mov x8, #80    	//Xsize
	mov x17, #420	//X
	mov x18, #189	//Y
	bl Triangle
    
	movz x10, 0x009B, lsl 16	//cambio color
	movk x10, 0x9B9D, lsl 00	//cambio color
	mov x11, #0    	//Triangulo para arriba #0, abajo #1
	mov x8, #80 	//Base
	mov x17, #361	//X
	mov x18, #189	//Y
	bl Triangle

	//BOCA
	movz x10, 0x0, lsl 00	//cambio color
	mov x11,#20    	//radio
	mov x15, #454	//X
	mov x16, #265	//Y
	mov x9, #2
	bl semi_circulo

	movz x10, 0x0, lsl 00	//cambio color 
	mov x11,#20    	//radio
	mov x15, #415	//X
	mov x16, #265	//Y
	mov x9, #2
	bl semi_circulo

	//NARIZ
	movz x10, 0x0, lsl 16	//cambio color
	mov x11, #1    	//Triangulo para arriba #0, abajo #1
	mov x8, #26 	//Base
	mov x17, #422	//X
	mov x18, #258	//Y
	bl Triangle

	//UWU
	movz x10, 0x00F8, lsl 16	//cambio color
	movk x10, 0x9A9A, lsl 00	//cambio color
	mov x11,#15 	//radio
	mov x15, #375	//X
	mov x16, #255	//Y
	mov x9, #1
	mov x8, #8
	bl circulo

	movz x10, 0x00F8, lsl 16	//cambio color
	movk x10, 0x9A9A, lsl 00	//cambio color
	mov x11,#15    	//radio
	mov x15, #497	//X
	mov x16, #255	//Y
	mov x9, #1
	mov x8, #8
	bl circulo

	//OJOS
	movz x10, 0x0, 	lsl 00	//cambio color
	mov x11,#15    	//radio
	mov x15, #470	//X
	mov x16, #230	//Y
	mov x9, #2
	mov x8, #2
	bl circulo

	movz x10, 0x00FB, lsl 16	//cambio color
	movk x10, 0xFBFB, lsl 00	//cambio color
	mov x11,#5    	//radio
	mov x15, #465	//X
	mov x16, #225	//Y
	mov x9, #2
	mov x8, #2
	bl circulo

	movz x10, 0x0, 	lsl 00	//cambio color
	mov x11,#15    	//radio
	mov x15, #395	//X
	mov x16, #230	//Y
	mov x9, #2
	mov x8, #2
	bl circulo

	movz x10, 0x00FB, lsl 16	//cambio color
	movk x10, 0xFBFB, lsl 00	//cambio color
	mov x11,#5    	//radio
	mov x15, #390	//X
	mov x16, #225	//Y
	mov x9, #2
	mov x8, #2
	bl circulo

	mov x4, #2
	b endpixel

frame2:
	//Arcoiris
    //Rojo

    movz x10, 0x00FF, lsl 16
	mov x8, #30    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #0		//X
	mov x18, #158 	//Y
	bl big_hline

	movz x10, 0x00FF, lsl 16    
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #89	//X
	mov x18, #158 	//Y
	bl big_hline

    movz x10, 0x00FF, lsl 16    
	mov x8, #65    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #149  	//X
	mov x18, #145	//Y
	bl big_hline

    movz x10, 0x00FF, lsl 16   
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #29	//X
	mov x18, #145	//Y
	bl big_hline

    //Naranja

	movz x10, 0x00FF, lsl 16
    movk x10, 0x8000, lsl 00   
    mov x8, #30    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #0		//X
	mov x18, #178	//Y
	bl big_hline

	movz x10, 0x00FF, lsl 16
    movk x10, 0x8000, lsl 00  
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #89	//X
	mov x18, #178	//Y
	bl big_hline

    movz x10, 0x00FF, lsl 16
    movk x10, 0x8000, lsl 00    
	mov x8, #60    	//Xsize
	mov x9, #20   	//Ysize
	mov x17, #149  	//X
	mov x18, #165	//Y
	bl big_hline

    movz x10, 0x00FF, lsl 16
    movk x10, 0x8000, lsl 00   
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #29	//X
	mov x18, #165	//Y
	bl big_hline

    //Amarillo

    movz x10, 0x00FF, lsl 16
    movk x10, 0xFF00, lsl 00   
    mov x8, #30    	//Xsize
	mov x9, #25    	//Ysize
	mov x17, #0	//X
	mov x18, #198	//Y
	bl big_hline

    movz x10, 0x00FF, lsl 16
    movk x10, 0xFF00, lsl 00
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #89	//X
	mov x18, #198	//Y
	bl big_hline

    movz x10, 0x00FF, lsl 16
    movk x10, 0xFF00, lsl 00   
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #149  	//X
	mov x18, #185	//Y
	bl big_hline

    movz x10, 0x00FF, lsl 16
    movk x10, 0xFF00, lsl 00  
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #29	//X
	mov x18, #185	//Y
	bl big_hline

    //Verde

    movz x10, 0x0000, lsl 16
    movk x10, 0xFF00, lsl 00	 
    mov x8, #30    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #0		//X
	mov x18, #218	//Y
	bl big_hline

    movz x10, 0x0000, lsl 16
    movk x10, 0xFF00, lsl 00    
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #89	//X
	mov x18, #218	//Y
	bl big_hline

    movz x10, 0x0000, lsl 16
    movk x10, 0xFF00, lsl 00   
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #149  	//X
	mov x18, #205	//Y
	bl big_hline

    movz x10, 0x0000, lsl 16
    movk x10, 0xFF00, lsl 00  
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #29	//X
	mov x18, #205	//Y
	bl big_hline

    //Celeste

    movz x10, 0x0037, lsl 16
    movk x10, 0x60F8, lsl 00    
    mov x8, #30    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #0		//X
	mov x18, #238	//Y
	bl big_hline

    movz x10, 0x0037, lsl 16
    movk x10, 0x60F8, lsl 00  
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #89	//X
	mov x18, #238	//Y
	bl big_hline

    movz x10, 0x0037, lsl 16
    movk x10, 0x60F8, lsl 00   
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #149  	//X
	mov x18, #225	//Y
	bl big_hline

    movz x10, 0x0037, lsl 16
    movk x10, 0x60F8, lsl 00   
	mov x8, #60    	//Xsize
	mov x9, #25    	//Ysize
	mov x17, #29	//X
	mov x18, #225	//Y
	bl big_hline

    //Violeta

    movz x10, 0x006C, lsl 16
    movk x10, 0x0AFF, lsl 00    
    mov x8, #30    	//Xsize
	mov x9, #20   	//Ysize
	mov x17, #0		//X
	mov x18, #258	//Y
	bl big_hline

    movz x10, 0x006C, lsl 16
    movk x10, 0x0AFF, lsl 00
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #89	//X
	mov x18, #258	//Y
	bl big_hline

    movz x10, 0x006C, lsl 16
    movk x10, 0x0AFF, lsl 00  
    mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #149  	//X
	mov x18, #245	//Y
	bl big_hline

    movz x10, 0x006C, lsl 16
    movk x10, 0x0AFF, lsl 00  
	mov x8, #60    	//Xsize
	mov x9, #20    	//Ysize
	mov x17, #29	//X
	mov x18, #245	//Y
	bl big_hline

	//PATAS IZQ
	movz x10, 0x009B, lsl 16	//cambio color
	movk x10, 0x9B9D, lsl 00	//cambio color
	mov x11,#20    	//radio
	mov x15, #260	//X
	mov x16, #310	//Y
	mov x9, #2
	mov x8, #2
	bl circulo

	movz x10, 0x009B, lsl 16	//cambio color
	movk x10, 0x9B9D, lsl 00	//cambio color
	mov x11,#20    	//radio
	mov x15, #230	//X
	mov x16, #275	//Y
	mov x9, #2
	mov x8, #8
	bl circulo

	//PATAS DER
	movz x10, 0x009B, lsl 16	//cambio color
	movk x10, 0x9B9D, lsl 00	//cambio color
	mov x11,#20    	//radio
	mov x15, #390	//X
	mov x16, #300	//Y
	mov x9, #2
	mov x8, #2
	bl circulo

	movz x10, 0x009B, lsl 16	//cambio color
	movk x10, 0x9B9D, lsl 00	//cambio color
	mov x11,#20    	//radio
	mov x15, #440	//X
	mov x16, #300	//Y
	mov x9, #2
	mov x8, #2
	bl circulo

	//CUERPO
	movz x10, 0x00F6, lsl 16	//cambio color
	movk x10, 0xC09D, lsl 00	//cambio color
	mov x11,#90    	//radio
	mov x15, #345	//X
	mov x16, #210	//Y
	mov x9, #5
	mov x8, #50
	bl circulo

	//CUERPO MEDIO
	movz x10, 0x00FA, lsl 16	//cambio color
	movk x10, 0x96F6, lsl 00	//cambio color
	mov x11,#70	//radio
	mov x15, #345	//X
	mov x16, #210	//Y
	mov x9, #5
	mov x8, #50
	bl circulo

	//CABEZA
	movz x10, 0x009B, lsl 16	//cambio color
	movk x10, 0x9B9D, lsl 00	//cambio color
	mov x11,#70	//radio
	mov x15, #450	//X
	mov x16, #220	//Y
	mov x9, #2
	mov x8, #40
	bl circulo

	//OREJAS
	movz x10, 0x009B, lsl 16	//cambio color
	movk x10, 0x9B9D, lsl 00	//cambio color
	mov x11, #0    	//Triangulo para arriba #0, abajo #1
	mov x8, #80    	//Xsize
	mov x17, #420	//X
	mov x18, #169	//Y
	bl Triangle
    
	movz x10, 0x009B, lsl 16	//cambio color
	movk x10, 0x9B9D, lsl 00	//cambio color
	mov x11, #0    	//Triangulo para arriba #0, abajo #1
	mov x8, #80 	//Base
	mov x17, #361	//X
	mov x18, #169	//Y
	bl Triangle

	//BOCA
	movz x10, 0x0, lsl 00	//cambio color
	mov x11,#20    	//radio
	mov x15, #454	//X
	mov x16, #245	//Y
	mov x9, #2
	bl semi_circulo

	movz x10, 0x0, lsl 00	//cambio color
	mov x11,#20    	//radio
	mov x15, #415	//X
	mov x16, #245	//Y
	mov x9, #2
	bl semi_circulo

	//NARIZ
	movz x10, 0x0, lsl 16	//cambio color
	mov x11, #1    	//Triangulo para arriba #0, abajo #1
	mov x8, #26 	//Base
	mov x17, #422	//X
	mov x18, #238	//Y
	bl Triangle

	//UWU
	movz x10, 0x00F8, lsl 16	//cambio color
	movk x10, 0x9A9A, lsl 00	//cambio color
	mov x11,#15 	//radio
	mov x15, #375	//X
	mov x16, #235	//Y
	mov x9, #1
	mov x8, #8
	bl circulo

	movz x10, 0x00F8, lsl 16	//cambio color
	movk x10, 0x9A9A, lsl 00	//cambio color
	mov x11,#15    	//radio
	mov x15, #497	//X
	mov x16, #235	//Y
	mov x9, #1
	mov x8, #8
	bl circulo

	//OJOS
	movz x10, 0x0, 	lsl 00	//cambio color
	mov x11,#15    	//radio
	mov x15, #470	//X
	mov x16, #210	//Y
	mov x9, #2
	mov x8, #2
	bl circulo
	movz x10, 0x00FB, lsl 16	//cambio color
	movk x10, 0xFBFB, lsl 00	//cambio color
	mov x11,#5    	//radio
	mov x15, #465	//X
	mov x16, #205	//Y
	mov x9, #2
	mov x8, #2
	bl circulo

	movz x10, 0x0, 	lsl 00	//cambio color
	mov x11,#15    	//radio
	mov x15, #395	//X
	mov x16, #210	//Y
	mov x9, #2
	mov x8, #2
	bl circulo
	movz x10, 0x00FB, lsl 16	//cambio color
	movk x10, 0xFBFB, lsl 00	//cambio color
	mov x11,#5    	//radio
	mov x15, #390	//X
	mov x16, #205	//Y
	mov x9, #2
	mov x8, #2
	bl circulo

	mov x4, #1
	b endpixel

//Bloque------------------------------------------------------
big_hline:
	mov x29, x30

	bl calc_p

	mov x2, x9            	// Y Size
linh1:
	mov x0, x3         	// cargo en x0 un pixel para abajo
	mov x1, x8       	// X Size
linh0:
	stur w10,[x0]       	// Set color of pixel N
	add x0,x0,4           	// Next pixel
	sub x1,x1,1           	// decrement X counter
	cbnz x1,linh0       	// If not end row jump
	sub x2,x2,1           	// Decrement Y counter

	add x3,x3,0xa00    	// Salto a la linea de abajo 1 pixeles mas a la izquierda

	cbnz x2,linh1       	// if not last row, jump

	br x29

//Triangulo----------------------------------------------------
Triangle:
	mov x29, x30

	lsr x9, x8, #1
	bl calc_p

	mov x2, x9        	// X/2*Y -> Y=x/2
tri1:
	mov x0, x3         	// cargo en x0 un pixel para abajo
	mov x1, x8       	// X Size
tri0:
	stur w10,[x0]       	// Set color of pixel N
	add x0,x0,4           	// Next pixel
	subs x1,x1,1           	// decrement X counter
	b.gt tri0       	// If not end row jump

	sub x8,x8,2        	// reduzco X 1 pixel de tamaño

	cmp x11, xzr
	b.eq true_t    	//d<0
	b else_t
true_t:
	sub x3,x3,0x9FC    	// Salto a la linea de abajo 2 pixeles mas a la izquierda
	b continue_t
else_t:    
	add x3,x3,0xa04    	// Salto a la linea de arriba 2 pixeles mas a la izquierda
continue_t:

	subs x2,x2,1       	// Decrement Y counter
	b.gt tri1           	// if not last row, jump
    
	br x29

//Semi_Circulo (Bresenham)----------------------------------------------------
semi_circulo:
	mov x29, x30	//guardo pos de return
	//Tx(x12), ty(x13), d(x14)
	mov x12, xzr    	//tx=0
	mov x13, x11    	//ty=r
	lsl x14, x11 ,#1	//2*r
	sub x14, xzr, x14	// -2*r
	add x14, x14, #3	// -2*r + 3
	semi_cir0:
    	add x18, x16, x13	//y+ty

    	add x17, x15, x12 	//x+tx
    	bl calc_p            	//x+tx, y+ty
    	stur w10,[x0]       	// Set color of pixel N

    	sub x17, x15, x12 	//x-tx
    	bl calc_p            	//x-tx, y+ty
    	stur w10,[x0]       	// Set color of pixel N

    	add x18, x16, x12 	//y+tx

    	add x17, x15, x13	//x+ty
    	bl calc_p            	//x+ty, y+tx
    	stur w10,[x0]       	// Set color of pixel N

    	sub x17, x15, x13	//x-ty
    	bl calc_p            	//x-ty, y+tx
    	stur w10,[x0]       	// Set color of pixel N


    	cmp x14, xzr
    	b.lt semi_true    	//d<0
    	b semi_else

	semi_true:
    	mov x17, x14
    	lsl x14, x12, #2	// d
    	add x14, x14, #6
    	add x14, x14, x17
    	b semi_continue
	semi_else:
    	mov x17, x14
    	sub x14, x12 , x13	// d = tx - ty
    	lsl x14, x14, x9	// d = 4*(tx-ty)
    	add x14, x14, #10	// d = 4*(tx-ty) + 10
    	add x14, x14, x17

    	sub x13, x13, #1	// ty= ty-1

	semi_continue:

    	add x12, x12, #1

    	cmp x12, x13
    	b.le semi_cir0
   	 
    	br x29

//Circulo (Bresenham)----------------------------------------------------
circulo:
	mov x29, x30	//guardo pos de return

	//Tx(x12), ty(x13), d(x14)
	mov x12, xzr    	//tx=0
	mov x13, x11    	//ty=r
	lsl x14, x11 ,#1	//2*r
	sub x14, xzr, x14	// -2*r
	add x14, x14, #3	// -2*r + 3


	cir0:
   	 
    	add x17, x15, x12 	//x+tx
    	add x18, x16, x13	//y+ty
    	bl calc_p            	//x+tx, y+ty
   	 
    	mov x22, x17    	//Guardo pos x+tx

    	sub x18, x16, x13	//y-ty
    	bl calc_p        	//x+tx, y-ty
    	movk x7, 0x0, lsl 00


    	sub x17, x15, x12 	//x-tx
    	sub x17, x17, x8
    	bl calc_p            	//x-tx, y-ty
    	movk x7, 0x0, lsl 00

    	sub x22, x22, x17	// x+tx - x-tx
    	add x22, x22, #1	//sumo 1

    	bl hline 			//Dibujo una linea de izquierda a derecha del circulo
   	 
    	add x18, x16, x13	//y+ty
    	bl calc_p            	//x-tx, y+ty
    	movk x7, 0x0, lsl 00

    	bl hline 			//Dibujo una linea de izquierda a derecha del circulo

    	add x17, x15, x13	//x+ty
    	add x18, x16, x12 	//y+tx
    	bl calc_p            	//x+ty, y+tx

    	mov x22, x17    	//Guardo pos x+ty -----------
   	 
    	sub x18, x16, x12 	//y-tx
    	bl calc_p            	//x+tx, y-ty
                       	 
    	sub x17, x15, x13	//x-ty
    	sub x17, x17, x8
    	bl calc_p            	//x-ty, y-tx

    	sub x22, x22, x17	//x+ty - x-ty
    	add x22, x22, #1	//sumo 1

    	bl hline        	//Dibujo una linea de izquierda a derecha del circulo
   	 
    	add x18, x16, x12 	//y+tx
    	bl calc_p            	//x+ty, y+tx

    	bl hline        	//Dibujo una linea de izquierda a derecha del circulo


    	cmp x14, xzr
    	b.lt true    	//d<0
    	b else

	true:
    	mov x17, x14
    	lsl x14, x12, #2	// d = 4 * tx
    	add x14, x14, #6	// d = 4 * tx + 6
    	add x14, x14, x17	// d += 4 * tx + 6
    	b continue
	else:
    	mov x17, x14
    	sub x14, x12 , x13	// d = tx - ty
    	lsl x14, x14, x9	// d = 4*(tx-ty)
    	add x14, x14, #10	// d = 4*(tx-ty) + 10
    	add x14, x14, x17	// d += 4*(tx-ty) + 10

    	sub x13, x13, #1	// ty= ty-1

	continue:

    	add x12, x12, #1

    	cmp x12, x13
    	b.le cir0
   	 
    	br x29

calc_p:					// calcular posicon de inicio
	mov x19, #640		// guardo en x19 = 640
	mul x0, x18, x19	// (y*640)
	add x0, x0, x17		// x + (y*640)
	lsl x0, x0, #2		// 4 * [x + (y*640)]

	add x0, x20, x0 	// Direccion de inicio + 4 * [x + (y*640)] 
	mov x3, x0 			//guardo el resultado en x3 auxiliar

	ret

hline:
	mov x2, #1        	// Y Size
l1:
	mov x1, x22       	// X Size
l0:
	stur w10,[x0]       	// Set color of pixel N
	add x0,x0,4           	// Next pixel
	sub x1,x1,1           	// decrement X counter
	cbnz x1,l0           	// If not end row jump

	sub x2,x2,1       		// Decrement Y counter

	cbnz x2,l1           	// if not last row, ju

	ret
endpixel:
	// Infinite Loop
	b InfLoop
