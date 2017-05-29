#include </home/pi/SeniorProject/wiringPi/wiringPi/wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <softPwm.h>
#include <time.h>
#include <png.h>
#define	ALSB 0
#define	B 1
#define	C 2
#define	DMSB 3
#define	DATA 4
#define	EN1 6
#define	EN2 5

unsigned int width;
unsigned int height;
png_bytep *row_pointers;

static void read_png_file(char *filename) {
    FILE *fp = fopen(filename, "rb");
    png_byte bit_depth;
    png_byte color_type;
    unsigned int y;

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) abort();
    png_infop info = png_create_info_struct(png);
    if (!info) abort();
    if (setjmp(png_jmpbuf(png))) abort();
    png_init_io(png, fp);
    png_read_info(png, info);
    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);
    color_type = png_get_color_type(png, info);
    bit_depth = png_get_bit_depth(png, info);
    /* Read any color_type into 8bit depth, RGBA format. */
    /* See http://www.libpng.org/pub/png/libpng-manual.txt */
    if (bit_depth == 16)
        png_set_strip_16(png);
    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);
    /* PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth. */
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);
    if (png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);
    /* These color_type don't have an alpha channel then fill it with 0xff. */
    if (color_type == PNG_COLOR_TYPE_RGB ||
            color_type == PNG_COLOR_TYPE_GRAY ||
            color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
    if (color_type == PNG_COLOR_TYPE_GRAY ||
            color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);
    png_read_update_info(png, info);
    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
    }
    png_read_image(png, row_pointers);
    fclose(fp);
}

static void write_png_file(char *filename) {
    unsigned int y;
    FILE *fp = fopen(filename, "wb");
    if (!fp) abort();
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) abort();
    png_infop info = png_create_info_struct(png);
    if (!info) abort();
    if (setjmp(png_jmpbuf(png))) abort();
    png_init_io(png, fp);
    
    png_set_IHDR(
        png,
        info,
        width,
        height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );
    
    png_write_info(png, info);
    /* To remove the alpha channel for PNG_COLOR_TYPE_RGB format, */
    /* Use png_set_filler(). */
    /*png_set_filler(png, 0, PNG_FILLER_AFTER);*/
    png_write_image(png, row_pointers);
    png_write_end(png, NULL);
    
    for (y = 0; y < height; y++) 
    {
        free(row_pointers[y]);
    }
    
    free(row_pointers);
    fclose(fp);
}


void PinPwmInit(int pinNum)
{
	srand(time(NULL));   // should only be called once
	  softPwmCreate(DATA, 0, 30);
}

// The angle goes from 0 to 180
void SetPwmAngle(int pinNum, int angle)
{
	
	
    softPwmWrite(DATA, angle);
}

void WriteNum(int pinNum, int pwmVal)
{
	digitalWrite(EN1, pinNum <= 15 ? HIGH : LOW);
	printf("EN1: %d \n", pinNum <= 15 ? HIGH : LOW);
	
	digitalWrite(EN2, pinNum > 15 ? HIGH : LOW);
	printf("EN2: %d \n", pinNum > 15 ? HIGH : LOW);
	
	digitalWrite (DMSB, (0x8 & pinNum) == 8 ? HIGH : LOW);
	printf("%d ", (0x8 & pinNum) == 8 ? HIGH : LOW);
	digitalWrite (C, (0x4 & pinNum) == 4 ? HIGH : LOW);	// On
	printf("%d ", (0x4 & pinNum) == 4 ? HIGH : LOW);
	digitalWrite (B, (0x2 & pinNum) == 2 ? HIGH : LOW);	// On
	printf("%d ", (0x2 & pinNum) == 2 ? HIGH : LOW);
	digitalWrite (ALSB, (0x1 & pinNum) == 1 ? HIGH : LOW);
	printf("%d \n", (0x1 & pinNum) == 1 ? HIGH : LOW);
	SetPwmAngle(DATA, pwmVal);
}

int main (void)
{
	printf ("Raspberry Pi blink\n") ;
	int drawArr[32] = {28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 19, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0};
	wiringPiSetup () ;
	pinMode (ALSB, OUTPUT) ;
	pinMode (B, OUTPUT) ;
	pinMode (C, OUTPUT) ;
	pinMode (DMSB, OUTPUT) ;
	pinMode (DATA, OUTPUT) ;
	pinMode (EN1, OUTPUT) ;
	pinMode (EN2, OUTPUT) ;
	PinPwmInit(DATA);

	int i = 0;
	
	for (i = 0; i < 32; i++)
	{
		WriteNum(i, 5);
		delay (1000);
	}
	
	for (i = 0; i < 32; i++)
	{
		WriteNum(i, drawArr[i]);
		delay (1000);
	}
	













  
 

  
  if (0)
  {
	read_png_file(0);
	write_png_file(0);  
  }
  
  //for (i = 5; i <= 30; i + 5)
  //{
   // SetPwmAngle(DATA, i);
   // delay (1000);		// mS
  //}
  return 0;
}
