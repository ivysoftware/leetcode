#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <sys/time.h>
#include <algorithm>
using namespace std;
//复杂度：O(n^2),空间复杂度O(n^2)
//更简化的做法：不保存截距，中间结果对于只计算最大值的情况，尽量用中间变量代替，抛弃无用的中间结果
//			 统计通过某点的直线中，最多有多少个点
/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
struct Point {
     int x;
     int y;
     Point() : x(0), y(0) {}
     Point(int a, int b) : x(a), y(b) {}
};

class Solution {
public:
	struct Line{
		float k;
		float b;
		int count;
	};
    bool PointSort(const Point& a, const Point &b)
    {
        if(a.x > b.x)
            return true;
        else if(a.x == b.x && a.y > b.y)
            return true;
        return false;
    }
    bool IsSame(Point& a, Point &b)
    {
    	if(a.x == b.x && a.y == b.y)
    		return true;
    	else
    		return false;
    }
    int maxPoints(vector<Point> &points) {
        //sort(points.begin(), points.end(), PointSort);
        //1. normal line non-y asix
        map<float, map<float, set<int> > > k2b2p;
        float k = 0, b = 0;
        int maxcount = 0;
        map<float, map<float, set<int> > >::iterator k_it;
        map<float, set<int> >::iterator b_it ;
        set<int>::iterator set_it;
        //2. y-axis
        map<int, int> y2c;
        set<float> ks;
        set<float>::iterator k_set_it;
        for(unsigned i = 0; i < points.size(); i ++)
        {
        	ks.clear();
            y2c[points[i].y] ++;
            for(unsigned j = i + 1; j < points.size(); j ++)
            {
            	if(points[i].x == points[j].x && points[i].y == points[j].y)
            		ks.insert(j);
            }
            for(unsigned j = i + 1; j < points.size(); j ++)
            {
                if(points[i].y == points[j].y)
                    continue;
                k = (float)(points[i].x - points[j].x)/(float)(points[i].y - points[j].y);
                b = points[i].y - points[i].x * k;
                k2b2p[k][b].insert(i);
                k2b2p[k][b].insert(j);
                k_set_it = ks.begin();
                for(; k_set_it != ks.end(); k_set_it ++)
                	k2b2p[k][b].insert(*(k_set_it));
            }

        }
        k_it = k2b2p.begin();
        for(; k_it!=k2b2p.end(); k_it++)
        {
        	b_it = k_it->second.begin();
        	for(; b_it != k_it->second.end(); b_it++){
				if(maxcount < (int)b_it->second.size()){
					maxcount = b_it->second.size();
					cout << "k=" <<  k_it->first << " ,b=" << b_it->second.size() << ", size=" << b_it->second.size() << endl;
					set_it = b_it->second.begin();
					for( ;set_it != b_it->second.end(); set_it++)
						cout << "point:" << *(set_it) << endl;
				}
        	}
        }
        map<int,int>::iterator it_y = y2c.begin();
        for(; it_y!=y2c.end(); it_y ++)
        {
            if(maxcount < it_y->second){
                maxcount = it_y->second;
                cout << "y2c:" << it_y->first << " " << it_y->second << endl;
            }
        }
        return maxcount;
    }
};

int main()
{
    /* max points */

    Point arr[] = {Point(0,-12),
                   Point(0,-5), Point(0,-8), Point(0,-9),
                   Point(-2,-1),Point(0,-11), Point(0,-9),Point(0,-12)};
    vector<Point> points(arr, arr+8);
    Solution s;
    cout << s.maxPoints(points)
}
