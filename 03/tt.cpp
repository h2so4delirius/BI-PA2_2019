#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>

using namespace std;

class InvalidRangeException {
};

#endif /* __PROGTEST__ */

// uncomment if your code implements initializer lists
// #define EXTENDED_SYNTAX

class CRange {

public:

    CRange(long long xvalue, long long yvalue) {
        if(xvalue>yvalue){
            throw InvalidRangeException();
        }
        x = xvalue;
        y = yvalue;
    }


    long long getx() const {
        return x;
    }

    long long gety() const {
        return y;
    }

    void setx(const long long &xvalue) {
        x = xvalue;
    }

    void sety(const long long &yvalue) {
        y = yvalue;
    }

    //void print(){
    //cout<<CRange.x;
    //}
private:
    long long x;
    long long y;
};

class CRangeList {

public:

    // constructor
    // Includes long long / range
    CRangeList &operator+=(const CRange &range1) {
        int flag = 0, flag2 = 0;
        CRange rtr(range1.getx(), range1.gety());
        auto it1 = lower_bound(cis.begin(), cis.end(), range1,
                               [](CRange range2, CRange range3) { return (range2.getx() < range3.getx()); });
        auto it2 = it1;
        //auto it2=upper_bound(cis.begin(),cis.end(),range1,[] (CRange range2,CRange range3){return (range2.gety()<range3.gety());});
        if (it1 != cis.begin()) {
            if ((it1 - 1)->gety() >= range1.gety() && (it1 - 1)->gety() >= range1.getx()) {
                goto rp; //goto
            }
            if ((it1 - 1)->gety() + 1 >= range1.getx()) {
                rtr.setx((it1 - 1)->getx());
                flag = 1;
            }
        }
        for (auto it = it1; it < cis.end(); it++) {
            //cout <<rtr.gety() <<" " <<it->getx() <<endl;
            
            if (rtr.gety() + 1 >= it->getx()||(rtr.gety()==9223372036854775807&&rtr.gety() >= it->getx())) {
            
                if (rtr.gety() <= it->gety())
                    rtr.sety(it->gety());
                
                flag2 = 1;
                it2 = it;
                
            }
             else
                break;
        }
        if (flag == 0 && flag2 == 0) {
            cis.insert(it1, rtr);
        } else if (flag == 0 && flag2 == 1) {
            cis.erase(it1, (it2 + 1));
            it1 = lower_bound(cis.begin(), cis.end(), range1,
                              [](CRange range2, CRange range3) { return (range2.getx() < range3.getx()); });
            cis.insert(it1, rtr);
        } else if (flag == 1 && flag2 == 0) {
            cis.erase((it1 - 1));
            it1 = lower_bound(cis.begin(), cis.end(), range1,
                              [](CRange range2, CRange range3) { return (range2.getx() < range3.getx()); });
            cis.insert(it1, rtr);
        } else if (flag == 1 && flag2 == 1) {
            cis.erase((it1 - 1), (it2 + 1));
            it1 = lower_bound(cis.begin(), cis.end(), range1,
                              [](CRange range2, CRange range3) { return (range2.getx() < range3.getx()); });
            cis.insert(it1, rtr);
        }


        rp:
        flag = 3;
return *this;
    }
    CRangeList& operator -=(const CRange &range1)
    {
        int flag=0;
        CRange rtr(range1.getx(),range1.gety());
        auto it1=lower_bound(cis.begin(),cis.end(),range1,[] (CRange range2,CRange range3){return (range2.getx()<range3.getx());});
        auto it2=it1;

        if(it1!=cis.begin()){
            if((it1-1)->getx()<rtr.getx()&&(it1-1)->gety()>rtr.gety()){
                long long d=rtr.getx();
                d--;
                long long p=rtr.gety();
                rtr.sety((it1-1)->gety());
                (it1-1)->sety(d);
                d=p;
                d++;
                rtr.setx(d);
                cis.insert(it1,rtr);
                goto zaebalo;
            }
            if((it1-1)->gety()>=rtr.getx()){
//cout«"g\n";
                if((it1-1)->getx()<rtr.getx()&&(it1-1)->gety()<=rtr.gety()){
                    long long  d=rtr.getx();
                    d--;
                    (it1-1)->sety(d);
                }
            }
        }
        for(auto it=it1;it<cis.end();it++){
            
            if(it->getx()<=rtr.gety()){
                //cout<<it1->getx()<<" "<<rtr.gety()<<"fsg\n";
                if(it1->gety()>rtr.gety()){
                    long long d=rtr.gety();
                    d++;
                    it1->setx(d);
                    break;
                }
                
                it2=it;
                flag=1;
            }
            else
                break;
        }
        if(flag==1){
            //cout<<it1->getx()<<" "<<it1->gety()<<endl;
            //if(it2==cis.begin())
            //cis.erase(cis.begin());
            cis.erase(it1,(it2+1));
        }
        zaebalo:
        flag=3;
return *this;
    }
    //-=//
    CRangeList& operator-=(const CRangeList &ref) {
        for(CRange k : ref.cis)
            *this-=k;
     return *this;
    }
    //+=//
    CRangeList& operator+=(const CRangeList &ref) {
        for(CRange k : ref.cis)
            *this+=k;
     return *this;
    }
    //=//
    CRangeList& operator =(const CRangeList &range1) {
        this->cis.clear();
        for(CRange rtr:range1.cis){
            this->cis.push_back(rtr);
        }
        return *this;
    }
    CRangeList &operator=(const CRange &ref) {
        cis.clear();
        cis.push_back(ref);
        return *this;
    }

    // operator ==
   bool operator==(const CRangeList &ref)const {
        auto it = ref.cis.begin();
        auto it1 = this->cis.begin();
        while(it != ref.cis.end()){
            if((it1 == this->cis.end() && it != ref.cis.end()) || (it == ref.cis.end() && it1 != this->cis.end()))
                return false;
            if(it->gety() != it1-> gety() || it->getx() != it1->getx())
                return false;
            ++it;
            ++it1;
        }
        return true;
    }
    // operator !=
    bool operator!=(const CRangeList &ref)const {
        auto it = ref.cis.begin();
        auto it1 = this->cis.begin();
        while(it != ref.cis.end()){
            if((it1 == this->cis.end() && it != ref.cis.end()) || (it == ref.cis.end() && it1 != this->cis.end()))
                return true;
            if(it->gety() != it1-> gety() || it->getx() != it1->getx())
                return true;
            ++it;
            ++it1;
        }
        return false;

    }
    bool Includes(const long long &ref)const {

            if(cis.size()==0)
            return false;

        CRange tmp(ref, ref);
        auto it = lower_bound(cis.begin(), cis.end(), tmp,
                    [](CRange range2, CRange range3) { return (range2.getx() < range3.getx()); });
        //if(it==cis.end())
        //return false;
        if(it!=cis.begin()){
            //cout<<"11\n";
                    if ( (it-1)->getx() <= ref && (it-1)->gety() >= ref)
            return true;
        }
        if ( it->getx() <= ref && it->gety() >= ref){
            if(cis.end()==it)
             return false;
            return true;
        }
        return false;
    }
    bool Includes(const CRange &ref)const{
            if(cis.size()==0)
            return false;
        auto it = lower_bound(cis.begin(), cis.end(), ref,
                              [](CRange range2, CRange range3) { return (range2.getx() < range3.getx()); });
       if(it!=cis.begin()){
         if ((it-1)->getx() <= ref.getx() && (it-1)->gety() >= ref.gety())
            return true;          
       }
       
        if (it->getx() <= ref.getx() && it->gety() >= ref.gety()){
                     if(cis.end()==it)
             return false;
            return true;
        }
        return false;
    }
    friend ostream &operator<<(ostream &oss, const CRangeList &x);
    friend CRangeList operator+(CRangeList r1, const CRangeList &r2);
    friend CRangeList operator-(CRangeList r1, const CRangeList &r2);
private:
    vector<CRange> cis;
};


//friends//
CRangeList operator+(CRangeList r1, const CRangeList &r2) {  //friend
    for(CRange k : r2.cis){
        r1+=k;
    }
    return r1;
}

CRangeList operator-(CRangeList r1, const CRangeList &r2){
    for(CRange k : r2.cis){
        r1-=k;
    }
    return r1;
}
/////////////////////


//-// after -=
CRangeList operator-(const CRange &r1, const CRange &r2){
    CRangeList tmp;
    tmp=r1;
    tmp-=r2;
    return tmp;
}

CRangeList operator-(CRangeList r1, const CRange &r2){
    r1-=r2;
    return r1;
}

//+// after +=
CRangeList operator+(const CRange &r1, const CRange &r2) {
    CRangeList tmp;
    tmp=r1;
    tmp+=r2;
    return tmp;
}


CRangeList operator+(CRangeList r1, const CRange &r2){
    r1+=r2;
    return r1;
}




ostream &operator<<(ostream &oss, const CRangeList &x) {
    oss << "{";
    for (auto it = x.cis.begin(); it < x.cis.end(); it++) {
        if (it->getx() == it->gety())

            oss << it->getx();
        else
            oss << "<" << it->getx() << ".." << it->gety() << ">";
        if (it + 1 != x.cis.end())
            oss << ",";
    }
    oss << "}";
    return oss;
}


#ifndef __PROGTEST__

string toString(const CRangeList &x) {
    ostringstream oss;
    oss << x;
    return oss.str();
}

int                main                                    ( void )
{
  CRangeList a, b;

  assert ( sizeof ( CRange ) <= 2 * sizeof ( long long ) );
  a = CRange ( 5, 10 );
  a += CRange ( 25, 100 );
  assert ( toString ( a ) == "{<5..10>,<25..100>}" );
  a += CRange ( -5, 0 );
  a += CRange ( 8, 50 );
  assert ( toString ( a ) == "{<-5..0>,<5..100>}" );
  a += CRange ( 101, 105 ) + CRange ( 120, 150 ) + CRange ( 160, 180 ) + CRange ( 190, 210 );
  assert ( toString ( a ) == "{<-5..0>,<5..105>,<120..150>,<160..180>,<190..210>}" );
  a += CRange ( 106, 119 ) + CRange ( 152, 158 );
  assert ( toString ( a ) == "{<-5..0>,<5..150>,<152..158>,<160..180>,<190..210>}" );
  a += CRange ( -3, 170 );
  a += CRange ( -30, 1000 );
  assert ( toString ( a ) == "{<-30..1000>}" );
  b = CRange ( -500, -300 ) + CRange ( 2000, 3000 ) + CRange ( 700, 1001 );
  a += b;
  assert ( toString ( a ) == "{<-500..-300>,<-30..1001>,<2000..3000>}" );
  a -= CRange ( -400, -400 );
  assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..1001>,<2000..3000>}" );
  a -= CRange ( 10, 20 ) + CRange ( 900, 2500 ) + CRange ( 30, 40 ) + CRange ( 10000, 20000 );
  assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
  try
  {
    a += CRange ( 15, 18 ) + CRange ( 10, 0 ) + CRange ( 35, 38 );
    assert ( "Exception not thrown" == NULL );
  }
  catch ( const InvalidRangeException & e )
  {
  }
  catch ( ... )
  {
    assert ( "Invalid exception thrown" == NULL );
  }
  assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
  b = a;
  assert ( a == b );
  assert ( !( a != b ) );
  b += CRange ( 2600, 2700 );
  assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
  assert ( a == b );
  assert ( !( a != b ) );
  b += CRange ( 15, 15 );
  assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,15,<21..29>,<41..899>,<2501..3000>}" );
  assert ( !( a == b ) );
  assert ( a != b );
  assert ( b . Includes ( 15 ) );
  assert ( b . Includes ( 2900 ) );
  assert ( b . Includes ( CRange ( 15, 15 ) ) );
  assert ( b . Includes ( CRange ( -350, -350 ) ) );
  assert ( b . Includes ( CRange ( 100, 200 ) ) );
  assert ( !b . Includes ( CRange ( 800, 900 ) ) );
  assert ( !b . Includes ( CRange ( -1000, -450 ) ) );
  assert ( !b . Includes ( CRange ( 0, 500 ) ) );
  a += CRange ( -10000, 10000 ) + CRange ( 10000000, 1000000000 );
  assert ( toString ( a ) == "{<-10000..10000>,<10000000..1000000000>}" );
  b += a;
  assert ( toString ( b ) == "{<-10000..10000>,<10000000..1000000000>}" );
  b -= a;
  assert ( toString ( b ) == "{}" );
  b += CRange ( 0, 100 ) + CRange ( 200, 300 ) - CRange ( 150, 250 ) + CRange ( 160, 180 ) - CRange ( 170, 170 );
  assert ( toString ( b ) == "{<0..100>,<160..169>,<171..180>,<251..300>}" );
  b -= CRange ( 10, 90 ) - CRange ( 20, 30 ) - CRange ( 40, 50 ) - CRange ( 60, 90 ) + CRange ( 70, 80 );
  assert ( toString ( b ) == "{<0..9>,<20..30>,<40..50>,<60..69>,<81..100>,<160..169>,<171..180>,<251..300>}" );
#ifdef EXTENDED_SYNTAX
  CRangeList x { { 5, 20 }, { 150, 200 }, { -9, 12 }, { 48, 93 } };
  assert ( toString ( x ) == "{<-9..20>,<48..93>,<150..200>}" );
  ostringstream oss;
  oss << setfill ( '=' ) << hex << left;
  for ( const auto & v : x + CRange ( -100, -100 ) )
    oss << v << endl;
  oss << setw ( 10 ) << 1024;
  assert ( oss . str () == "-100\n<-9..20>\n<48..93>\n<150..200>\n400=======" );
#endif /* EXTENDED_SYNTAX */
  return 0;
}
#endif /* __PROGTEST__ */