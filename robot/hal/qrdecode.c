/*
 * =====================================================================================
 *
 *       Filename:  t1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/31/2023 01:58:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *        Company:  Israel
 *
 * =====================================================================================
 */
#include "qrdecode.h"
//#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "quirc/lib/quirc.h"


//gcc t1.c -o t1  libquirc.a -lm
//convert img2.png -depth 8 gray:img2.raw
//convert key.jpeg -resize 480x640!  -depth 8 gray:key.raw
int qrdecode(char *buf) {
	struct quirc *qr;
	uint8_t *image;
	int w, h;
	int err;
	struct quirc_code code;
	struct quirc_data data;
	FILE *ptr;

	qr = quirc_new();
	if (!qr) {
		perror("Failed to allocate memory");
		abort();
	}
	//if (quirc_resize(qr, 473, 1024) < 0) {
	if (quirc_resize(qr, 640, 480) < 0) {
	//if (quirc_resize(qr, 2048, 1152) < 0) {

		perror("Failed to allocate video memory");
		abort();
	}

	image = quirc_begin(qr, &w, &h);
	memcpy (image, buf, h*w);

//	 ptr = fopen("/home/yair/binata/ir_med/quirc/key.raw","rb");  // r for read, b for binary
	
	//ptr = fopen("/home/yair/binata/ir_med/quirc/img2.raw","rb");  // r for read, b for binary
		
	//ptr = fopen("/home/yair/binata/ir_med/quirc/img1.raw","rb");  // r for read, b for binary

//	 fread(image,2359296,1,ptr); // read 10 bytes to our buffer
	/* fill image*/
	quirc_end(qr);
	int num_codes;
	int i;

	/* We've previously fed an image to the decoder via
	 * quirc_begin/quirc_end.
	 */

	num_codes = quirc_count(qr);
	for (i = 0; i < num_codes; i++) {
		struct quirc_code code;
		struct quirc_data data;
		quirc_decode_error_t err;

		quirc_extract(qr, i, &code);

		/* Decoding stage */
		err = quirc_decode(&code, &data);
		if (err) {
			//printf("DECODE FAILED: %s\n", quirc_strerror(err));
		}
		else
			printf("Data: %s\n", data.payload);
	}



	err = quirc_decode(&code, &data);
	if (err == QUIRC_ERROR_DATA_ECC) {
		quirc_flip(&code);
		err = quirc_decode(&code, &data);
	}

	if (err) {
		//printf("DECODE FAILED: %s\n", quirc_strerror(err));
		}
	else
		printf("Data: %s\n", data.payload);
	quirc_destroy(qr);
	return 0;
}


