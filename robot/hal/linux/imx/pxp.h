/*
 * =====================================================================================
 *
 *       Filename:  pxp.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/25/2023 08:25:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *        Company:  Israel
 *
 * =====================================================================================
 */
#ifdef PXP_H
int pxp_yuv2rgb( void *src,void  *dst);
int pxp_yuv2gray(void *src,void  *dst);

void pxp_release();
#endif
