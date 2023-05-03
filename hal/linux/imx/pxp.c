/*
 * =====================================================================================
 *
 *       Filename:  pxp.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/23/2023 09:17:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *        Company:  Israel
 *
 * =====================================================================================
 */



#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <linux/mxcfb.h>

#include "pxp_lib.h"


#define DBG_DEBUG		3
#define DBG_INFO		2
#define DBG_WARNING		1
#define DBG_ERR			0

static int debug_level = DBG_INFO;
#define dbg(flag, fmt, args...)	{ if(flag <= debug_level)  printf("%s:%ul "fmt, __FILE__, __LINE__,##args); }


#define WIDTH	480
#define HEIGHT	640

struct pxp_mem_desc mem;
struct pxp_mem_desc mem_o;
pxp_chan_handle_t pxp_chan;


struct pxp_mem_desc mem1;
struct pxp_mem_desc mem1_o;
pxp_chan_handle_t pxp_chan1;





int pxp_yuv2rgb(void *src,void  *dst)
{
	int ret;
	static int state = 0;
	static struct pxp_config_data *pxp_conf = NULL;
	static struct pxp_proc_data *proc_data = NULL;

	if (state==0){
		ret = pxp_init();
		if (ret < 0) {
			dbg(DBG_ERR, "pxp init err\n");
			return -1;
		}

		ret = pxp_request_channel(&pxp_chan);
		if (ret < 0) {
			dbg(DBG_ERR, "pxp request channel err\n");
			//goto err0;
		}
		//dbg(DBG_INFO, "requested chan handle %d\n", pxp_chan.handle);

		/* Prepare the channel parameters */
		memset(&mem, 0, sizeof(struct pxp_mem_desc));
		memset(&mem_o, 0, sizeof(struct pxp_mem_desc));
		mem.size = WIDTH * HEIGHT * 2;
		mem_o.size = WIDTH * HEIGHT *  2;

		ret = pxp_get_mem(&mem);
		if (ret < 0) {
			dbg(DBG_DEBUG, "get mem err\n");
		}


		ret = pxp_get_mem(&mem_o);
		if (ret < 0) {
			dbg(DBG_ERR, "get mem_o err\n");
		}

		/* Configure the channel */
		pxp_conf = malloc(sizeof (*pxp_conf));
		memset(pxp_conf, 0, sizeof(*pxp_conf));
		proc_data = &pxp_conf->proc_data;



		/* Initialize non-channel-specific PxP parameters */
		proc_data->srect.left = 0;
		proc_data->srect.top = 0;
		proc_data->drect.left = 0;
		proc_data->drect.top = 0;
		proc_data->srect.width = WIDTH;
		proc_data->srect.height = HEIGHT;
		proc_data->drect.width =  WIDTH;
		proc_data->drect.height = HEIGHT;
		proc_data->scaling = 0;
		proc_data->hflip = 0; 
		proc_data->vflip = 0;
		proc_data->rotate = 0; 
		proc_data->bgcolor = 0;

		proc_data->overlay_state = 0;
		proc_data->lut_transform =PXP_LUT_NONE;//PXP_LUT_INVERT; // cmdl->pixel_inversion ?PXP_LUT_INVERT : PXP_LUT_NONE;

		/*
		 * Initialize S0 parameters
		 */
		pxp_conf->s0_param.pixel_fmt = PXP_PIX_FMT_UYVY; ;
		pxp_conf->s0_param.width = WIDTH;
		pxp_conf->s0_param.height = HEIGHT;
		pxp_conf->s0_param.color_key = -1;
		pxp_conf->s0_param.color_key_enable = false;
		pxp_conf->s0_param.paddr = mem.phys_addr;

		//dbg(DBG_DEBUG, "pxp_test s0 paddr %08x\n", pxp_conf->s0_param.paddr);
		/*
		 * Initialize OL parameters
		 * No overlay will be used for PxP operation
		 */
		for (int i=0; i < 8; i++) {
			pxp_conf->ol_param[i].combine_enable = false;
			pxp_conf->ol_param[i].width = 0;
			pxp_conf->ol_param[i].height = 0;
			pxp_conf->ol_param[i].pixel_fmt = PXP_PIX_FMT_RGB565;
			pxp_conf->ol_param[i].color_key_enable = false;
			pxp_conf->ol_param[i].color_key = -1;
			pxp_conf->ol_param[i].global_alpha_enable = false;
			pxp_conf->ol_param[i].global_alpha = 0;
			pxp_conf->ol_param[i].local_alpha_enable = false;
		}

		/*
		 * Initialize Output channel parameters
		 * Output is Y-only greyscale
		 */
		pxp_conf->out_param.width = WIDTH;
		pxp_conf->out_param.height = HEIGHT;
		pxp_conf->out_param.pixel_fmt = PXP_PIX_FMT_RGB565;
		if (proc_data->rotate % 180)
			pxp_conf->out_param.stride = HEIGHT;
		else
			pxp_conf->out_param.stride = WIDTH;

		pxp_conf->out_param.paddr = mem_o.phys_addr;
		state = 1;
	}else{
		ret = pxp_config_channel(&pxp_chan, pxp_conf);
		if (ret < 0) {
			dbg(DBG_ERR, "pxp config channel err\n");
		}

		memcpy ((void*)mem.virt_uaddr, src, WIDTH * HEIGHT * 2);

		ret = pxp_start_channel(&pxp_chan);
		if (ret < 0) {
			dbg(DBG_ERR, "pxp start channel err\n");
		}

		ret = pxp_wait_for_completion(&pxp_chan, 1);
		if (ret < 0) {
			dbg(DBG_ERR, "pxp wait for completion err\n");
		}

		memcpy (dst, (void*)mem_o.virt_uaddr, WIDTH * HEIGHT *2);
	}
	return 0;
}



int pxp_yuv2gray(void *src,void  *dst)
{
	int ret;
	static int state = 0;
	static struct pxp_config_data *pxp_conf = NULL;
	static struct pxp_proc_data *proc_data = NULL;
	switch (state) 
	{
		case 0:
			{
				ret = pxp_init();
				if (ret < 0) {
					dbg(DBG_ERR, "pxp init err\n");
					return -1;
				}

				ret = pxp_request_channel(&pxp_chan1);
				if (ret < 0) {
					dbg(DBG_ERR, "pxp request channel err\n");
					//goto err0;
				}
				//dbg(DBG_INFO, "requested chan handle %d\n", pxp_chan.handle);

				/* Prepare the channel parameters */
				memset(&mem1, 0, sizeof(struct pxp_mem_desc));
				memset(&mem1_o, 0, sizeof(struct pxp_mem_desc));
				mem1.size = WIDTH * HEIGHT * 2;
				mem1_o.size = WIDTH * HEIGHT * 1;

				ret = pxp_get_mem(&mem1);
				if (ret < 0) {
					dbg(DBG_DEBUG, "get mem err\n");
				}


				ret = pxp_get_mem(&mem1_o);
				if (ret < 0) {
					dbg(DBG_ERR, "get mem_o err\n");
				}

				/* Configure the channel */
				pxp_conf = malloc(sizeof (*pxp_conf));
				memset(pxp_conf, 0, sizeof(*pxp_conf));
				proc_data = &pxp_conf->proc_data;



				/* Initialize non-channel-specific PxP parameters */
				proc_data->srect.left = 0;
				proc_data->srect.top = 0;
				proc_data->drect.left = 0;
				proc_data->drect.top = 0;
				proc_data->srect.width = WIDTH;
				proc_data->srect.height = HEIGHT;
				proc_data->drect.width =  WIDTH;
				proc_data->drect.height = HEIGHT;
				proc_data->scaling = 0;
				proc_data->hflip = 0; 
				proc_data->vflip = 0;
				proc_data->rotate = 0; 
				proc_data->bgcolor = 0;

				proc_data->overlay_state = 0;
				proc_data->lut_transform =PXP_LUT_NONE;//PXP_LUT_INVERT; // cmdl->pixel_inversion ?PXP_LUT_INVERT : PXP_LUT_NONE;

				/*
				 * Initialize S0 parameters
				 */
				pxp_conf->s0_param.pixel_fmt = PXP_PIX_FMT_UYVY; ;
				pxp_conf->s0_param.width = WIDTH;
				pxp_conf->s0_param.height = HEIGHT;
				pxp_conf->s0_param.color_key = -1;
				pxp_conf->s0_param.color_key_enable = false;
				pxp_conf->s0_param.paddr = mem1.phys_addr;

				//dbg(DBG_DEBUG, "pxp_test s0 paddr %08x\n", pxp_conf->s0_param.paddr);
				/*
				 * Initialize OL parameters
				 * No overlay will be used for PxP operation
				 */
				for (int i=0; i < 8; i++) {
					pxp_conf->ol_param[i].combine_enable = false;
					pxp_conf->ol_param[i].width = 0;
					pxp_conf->ol_param[i].height = 0;
					pxp_conf->ol_param[i].pixel_fmt = PXP_PIX_FMT_GREY;
					pxp_conf->ol_param[i].color_key_enable = false;
					pxp_conf->ol_param[i].color_key = -1;
					pxp_conf->ol_param[i].global_alpha_enable = false;
					pxp_conf->ol_param[i].global_alpha = 0;
					pxp_conf->ol_param[i].local_alpha_enable = false;
				}

				/*
				 * Initialize Output channel parameters
				 * Output is Y-only greyscale
				 */
				pxp_conf->out_param.width = WIDTH;
				pxp_conf->out_param.height = HEIGHT;
				pxp_conf->out_param.pixel_fmt = PXP_PIX_FMT_GREY;
				if (proc_data->rotate % 180)
					pxp_conf->out_param.stride = HEIGHT;
				else
					pxp_conf->out_param.stride = WIDTH;

				pxp_conf->out_param.paddr = mem1_o.phys_addr;
				state = 1;
			}
		case 1:
			{
				ret = pxp_config_channel(&pxp_chan1, pxp_conf);
				if (ret < 0) {
					dbg(DBG_ERR, "pxp config channel err\n");
				}

				memcpy ((void*)mem1.virt_uaddr, src, WIDTH * HEIGHT * 2);

				ret = pxp_start_channel(&pxp_chan1);
				if (ret < 0) {
					dbg(DBG_ERR, "pxp start channel err\n");
				}

				ret = pxp_wait_for_completion(&pxp_chan1, 1);
				if (ret < 0) {
					dbg(DBG_ERR, "pxp wait for completion err\n");
				}

				memcpy (dst, (void*)mem1_o.virt_uaddr, WIDTH * HEIGHT *1);
			}
	}
	return 0;
}



void pxp_release()
{
	pxp_put_mem(&mem_o);
	pxp_put_mem(&mem);
	pxp_release_channel(&pxp_chan);

	pxp_put_mem(&mem1_o);
	pxp_put_mem(&mem1);
	pxp_release_channel(&pxp_chan1);


}

