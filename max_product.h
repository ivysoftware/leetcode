/*
 * max_product.h
 *
 *  Created on: 2014年11月5日
 *      Author: ivycui
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sys/time.h>
using namespace std;


/* 考虑边界和各种情况
 * 整数包括正、负、0三种情况
 * 1. 全正数
 * 2. 全负数，奇数个，偶数个
 * 3. 长度为1
 * 4. 中间某个数字为0
 * 5. 普通情况，正负0都有
*/

int MaxProduct(int A[], int n)
{
	int* a = A;
	int result = a[0];
	int allp = 1;
	int count = 0;
	int pre = 0;
	int post = 0;
	////前面n-1的乘积（无符号）
	//如果数组中有0出现，则分而治之
	int* b = new int[n];
	for(int i = 0 ; i < n ;i ++)
	{
		if(a[i] == 0)
		{//如果数组中有0出现，则分而治之

			if(i > 0)
				pre = MaxProduct(a, i);
			if(i < n - 1)
				post = MaxProduct(a+i+1, n-i-1);
			return pre > post ? pre : post;
		}
		else if(a[i] < 0)
		{
			count ++;
			allp *= -a[i]; //负数变正数
		}else
		{
			allp *= a[i];
		}
		b[i] = allp;//[0,i]的乘积（无符号）
	}
	//保证没有0
	if((count & 1) == 0)
	{//偶数个负号，选择全部数字相乘
		return allp;
	}
	else
	{//奇数个负号，结果为第一个或最后一个负数前后两部分乘积较大的一方
		pre = post = a[0];
		result = a[0];
		for(int i = 0 ; i < n - 1; i++)
		{//第一个负数,不能是第n-1个位置，第n-1个位置前面乘积无意义
			if(a[i] < 0)
			{
				post= allp/b[i];
				break;
			}
		}
		//反方向，++记得是--
		for(int i = n - 1; i >= 1; i--)
		{//第二个负数,不能是第0个位置，第0个位置前面乘积无意义
			if(a[i] < 0)
			{
				pre = b[i - 1];
				break;
			}
		}
		result = pre > post ? pre : post;
	}
	delete b;
	return result;
}
