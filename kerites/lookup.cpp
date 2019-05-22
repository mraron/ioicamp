#include <bits/stdc++.h>
#include "lookup.h"
#define _MaxN            100003

using namespace std;

struct PointType {
  long x, y;
};

static int _Inint = true;
static long _N;
static PointType _P[_MaxN ];
static PointType _A, _B;

static void WriteOut(long x, long y, string Ms){
  cout<<x<<" "<<y<<endl;
  cout<<Ms<<endl;
  exit(0);
}

static void ReadIn(){
  long x, y, i;
  cin>>_A.x>>_A.y>>_B.x>>_B.y;
  cin>>_N;

  _P[_N+1] = _A;
  _P[_N+2] = _B;

  for (i = 1; i <= _N; i++) {
    cin>>_P[i].x;
    cin>>_P[i].y;
  }  /*for i*/

  _Inint = false;
}  /*Readin*/

int Drift(long x, long y, long z){
  /*Returns: +1 if x->y->z turns left,
             0 if x,y and z are collinear,
            -1 if x->y->z turns right*/
  long crosspr;
  if (_Inint)
    ReadIn();
  if (x < 1 || y < 1 || z < 1 || x > _N + 2 || y > _N + 2 || z > _N + 2) {
    WriteOut(-1L, -1L, "ERROR: Illegal argument of Drift");
  }
  crosspr = (_P[y].x - _P[x].x) * (_P[z].y - _P[x].y) -
	    (_P[z].x - _P[x].x) * (_P[y].y - _P[x].y);
  if (crosspr < 0)
    return -1;
  else if (crosspr > 0)
    return 1;
  else
    return 0;
}  /*Drift*/

long GetN(){
  if (_Inint) {
    ReadIn();
    _Inint = false;
  }
  return _N;
}

void Answer(long left, long right){
  if (_Inint) {
    WriteOut(-1, -1, "ERROR: You must call GetN first");
  }
  WriteOut(left, right, "Normal termination");
}
