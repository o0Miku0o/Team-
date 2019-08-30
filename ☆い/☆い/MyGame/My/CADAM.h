#ifndef CADAM
#define CADAM
#include <math.h>
/*
�֐���  lnprm
�@�\    �����̕������̌v�Z
�`��    int lnprm( double *pt1, double *pt2,
double a, double b, double c )
���    �w�肳�ꂽ 2�_  (pt1[1],  pt1[2])  ��  (pt2[1],  pt2[2])  ��ʂ�
�����̕�����(ax  +  by  +  c  =  0)�̌W��(a,  b,  c)�����߂܂��B
�߂�l  lnprm�́A���������0�A���s�����-1��Ԃ��܂��B
*/
/*  
TO SET UP AN EQUATION OF LINE AND
CALCULATE THE COEFFICIENTS
( ax + by + c = 0 )
*/
int lnprm(double *pt1, double *pt2, double *a, double *b, double *c);
/*
�֐���  lncl
�@�\    �~�ƒ����̌�_�̌v�Z
�`��    int lncl(  double  *pt1,  double  *pt2,  double  *xyr,
double  *pnear,  double  *xy)
���    ���S���W�Ɣ��a  (xyr[0],  xyr[1],  xyr[2])  �Œ�`�����~�ƁA�w
�肳�ꂽ 2�_  (pt1[1],  pt1[2])  ��  (pt2[1],  pt2[2])  ��ʂ钼
���Ƃ̌�_  (xy[0],  xy[1]) ���v�Z���܂��B��_�� 2���݂���Ƃ�
�͎w�肵���_  (pnear[0],  pnear[1]) �ɋ߂����̌�_���I������܂��B
�߂�l  lncl�́A��������ƌ�_�̐��A��_�����݂��Ȃ���-1��Ԃ��܂��B
*/
/*
INTERSECTING POINTS OF LINE AND CIRCLE
*/
int lncl(double *pt1, double *pt2, double *xyr, double *pnear, double *xy);
/*
�֐���  lnln
�@�\    �񒼐��̌�_�̌v�Z
�`��    int lnln( double (*pxy1)[2], double (*pxy2)[2], int *xy )
���    ����  (pxy1[0][0], pxy1[0][1] - pxy1[1][0], pxy1[1][1])  ��  ����
(pxy1[0][0], pxy1[0][1] - pxy1[1][0], pxy1[1][1])  �̌�_  (xy[0],
xy[1])  ���v�Z���܂��B
�߂�l  lnln�́A���������0�A��_�����݂��Ȃ���-1��Ԃ��܂��B
*/
int lnln(double(*pxy1)[2], double(*pxy2)[2], double *xy);
#endif