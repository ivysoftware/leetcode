/*
 * permutation.h
 *
 *  Created on: 2014年11月5日
 *      Author: ivycui
 */

#include <vector>
#include <math.h>
#include <iostream>
using namespace std;
#define MAX_PI 12
#define MAX_PJ 13
#define PATH_INIT -2

//根据二维路径返回排列组合后的所有路径
//列可以不连续，中间有一列是无效的，仍然可以输出,且不输出后半部无效列
/*
 * output paths:8
0 2 -2 4 7
0 2 -2 4 5
0 2 -2 3 7
0 2 -2 3 5
0 1 -2 4 7
0 1 -2 4 5
0 1 -2 3 7
0 1 -2 3 5
 */
int GetPathVec_3(int (&paths)[MAX_PI][MAX_PJ], vector< vector< int > > &out_paths)
{
	int i, j;
	int number = 1;
	int col_len = 0;
	int col_num = 0;
	vector<int> col_num_arr;
	vector<int> back_n; //后面所有列的可能性数目
	int cur_max_pj = 0;//合法的最长列范围
	for(i = MAX_PJ - 1; i >= 0; i --)
	{
		if(paths[0][i] != PATH_INIT)
		{
			cur_max_pj = i + 1; //合法的最长列范围
			break;
		}
	}
    for (i=0; i<cur_max_pj; i++)
    {
    	col_len = 0;
    	//计算当前列长度
        for (; col_len<MAX_PI && paths[col_len][i] != PATH_INIT; col_len++)
        {
        	;
        }
        if(col_len > 0)
        {
        	number *= col_len;
        	col_num ++; //有效列长度
        }
        //统计每列元素个数
        col_num_arr.push_back(col_len);
    }
    out_paths.resize(number);
    //从0开始
    i = 0;
    int index = 0;
    int p = 1;
    //预存第j列后n-j-1列所有情况数目
    back_n.resize(cur_max_pj);
    for(j = cur_max_pj - 1; j >= 0; j --)
    {
    	back_n[j] = p;
    	if(col_num_arr[j] > 1)
    		p = p * col_num_arr[j];
    }
    //通过while的形式防止大量数组的拷贝赋值，操作
    while(i < number)
    {
    	vector<int> path;
    	path.resize(cur_max_pj);
    	p = cur_max_pj - 1;
    	//计算每一列下标
    	for(j = cur_max_pj - 1; j >= 0; j --)
    	{
    		//跳过没有值的列
    		if(col_num_arr[j] == 0)
    		{
    			path[p--] = PATH_INIT;
    			continue;
    		}
			//devide all possibility num
			index = i / back_n[j];
			//cal bin num in current column
			index = index % col_num_arr[j];
    		//加入每一列的值
    		path[p--] = paths[index][j];
    	}
    	out_paths[i] = path;
    	i++;
    }
	return 0;
}

/*根据二维路径返回排列组合后的所有路径
 * 条件：保持行列连续性，只在连续的区域内有效
 */
int GetPathVec_2(int (&paths)[MAX_PI][MAX_PJ], vector< vector< int > > &out_paths)
{
	int i, j;
	int number = 1;
	int col_len = 0;
	int col_num = 0;
	vector<int> col_num_arr;
    for (i=0; i<MAX_PJ && paths[0][i] != PATH_INIT; i++)
    {
    	col_len = 0;
    	//计算当前列长度
        for (; col_len<MAX_PI && paths[col_len][i] != PATH_INIT; col_len++)
        {
        	;
        }
        number *= col_len;
        //统计每列元素个数
        col_num_arr.push_back(col_len);
        //cout << "col_len:" << col_len << endl;
    }
    col_num = i;
    out_paths.resize(number);
    //从0开始
    i = 0;
    int index = 0;
    int p = 1;
    while(i < number)
    {
    	vector<int> path;
    	path.resize(col_num);
    	//计算每一列下标
    	for(j = col_num - 1; j >= 0; j --)
    	{
    		if(j == col_num -1)
    		{
    			index = i % col_num_arr[j];
    			p = col_num_arr[j];
    		}
    		else
    		{
    			//devide all possibility num
    			index = i / p;
    			//cal bin num in current column
    			index = index % col_num_arr[j];
    			p = p * col_num_arr[j];
    		}
    		//加入每一列的值
    		path[j] = paths[index][j];
    	}
    	out_paths[i] = path;
    	i++;
    }
	return 0;
}
//根据二维路径返回排列组合后的所有路径
int GetPathVec_1(int (&paths)[MAX_PI][MAX_PJ], vector< vector< int > > &out_paths)
{
    int max_row = -1; //行
    int max_col = -1; //列
    int i, j;
    for (i=0; i<MAX_PI; i++)
    {
        for (j=0; j<MAX_PJ; j++)
        {
            if (paths[i][j] != PATH_INIT)
            {
                if (i >= max_col)
                    max_col = i+1;

                if (j >= max_row)
                    max_row = j+1;
            }
        }
    }
    if (max_col == -1 || max_row == -1)
        return -1;

    int number = pow((float)max_col, max_row) - 1;
    while (number >= 0)
    {
        vector<int> ppath;
        int tmp = number;
		for (j=0; j<max_row; j++)
		{
			if (tmp%max_col >= 0)
			{
			    int ti = tmp%max_col;
			    if (paths[ti][j] != PATH_INIT)
			    {
                    ppath.push_back(paths[ti][j]);
			    }
			    else
			    	break;
			    tmp = tmp/max_col;
			}
		}
		if (ppath.size() >= max_row)
		    out_paths.push_back(ppath);
		number--;
    }

#ifdef _PATTERN_DEBUG_
    printf("output paths:\n");
    for (int i = 0; i < out_paths.size(); i++)
    {
        for (int j = 0; j < out_paths[i].size(); j++)
            printf("%d ", out_paths[i][j]);
        printf("\n");
    }
    printf("\n");
#endif
    return 0;
}

int test_permutation()
{
	//test permutation
	int grid[MAX_PI][MAX_PJ];
	for(int i = 0; i < MAX_PI; i ++)
	{
		for(int j = 0; j < MAX_PJ; j ++)
		{
			grid[i][j] = PATH_INIT;
		}
	}
	grid[0][0] = 0;
	grid[0][1] = 2;
	grid[0][2] = -2;
	grid[0][3] = 4;
	grid[0][4] = 7;

	grid[1][0] = -2;
	grid[1][1] = 1;
	grid[1][2] = -2;
	grid[1][3] = 3;
	grid[1][4] = 5;
	/*
	grid[0][4] = 0;
	grid[0][5] = 0;

	grid[1][1] = 1;
	grid[2][1] = 2;
	grid[3][1] = 3;

	grid[1][2] = 1;
	grid[2][2] = 2;

	grid[1][3] = 1;
	*/
	//for(int t = 0 ; t < 100; t++)
	//{
		vector<vector<int> > out_paths;
		struct timeval start,end;
		unsigned long use_time;
		gettimeofday(&start, NULL);
		GetPathVec_2(grid, out_paths);
		gettimeofday(&end, NULL);
		use_time = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);
		cout << "getPath_2 use time:" << use_time << endl;
		printf("output paths:%d\n", out_paths.size());

		for (int i = 0; i < (int)out_paths.size(); i++)
		{
			for (int j = 0; j < (int)out_paths[i].size(); j++)
				printf("%d ", out_paths[i][j]);
			if(out_paths[i].size() > 0)
				printf("\n");
		}
		printf("\n");

		out_paths.clear();
		gettimeofday(&start, NULL);
		GetPathVec_1(grid, out_paths);
		gettimeofday(&end, NULL);
		use_time = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);

		cout << "getPath_1 use time:" << use_time << endl;
		printf("output paths:%d\n", out_paths.size());

		for (int i = 0; i < (int)out_paths.size(); i++)
		{
			for (int j = 0; j < (int)out_paths[i].size(); j++)
				printf("%d ", out_paths[i][j]);
			if(out_paths[i].size() > 0)
				printf("\n");
		}
		printf("\n");

	//}
	return 0;
}

int main()
{
  return 0;
}
