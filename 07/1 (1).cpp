#ifndef __PROGTEST__
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <list>
#include <algorithm>

#if defined ( __cplusplus ) && __cplusplus > 199711L /* C++ 11 */
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
#endif /* C++ 11 */

using namespace std;
#endif /* __PROGTEST__ */
class CTrain;
class NoRouteException 
{ 
};
class CTrain;
    template <typename _T, typename _E>
    struct cesta;

    template <typename _T, typename _E>

    class CRoute
    {
    public:
      CRoute()=default; 
    CRoute& Add (const _T &r1 , const _T &r2 ,const _E &r3) {
      cesta kl;//(r1,r2,r3);
      kl.from=r1;
      kl.to=r2;
      kl.rtr.push_back(r3);    
      auto it=lower_bound(puti.begin(),puti.end(),kl,[](cesta range1,cesta range2) {
       if(range2.from != range1.from) {return (range2.from > range1.from );}
       else{return (range2.to > range1.to);}
        });

      if(it!=puti.end()){
        if(it->from==r1&&it->to==r2)
          it->rtr.push_back(r3);
        else
          puti.insert(it,kl);
      }
      else
        puti.insert(it,kl);
/////////////////////////////////////////////////////////////
        _T d=kl.from;
        kl.from=kl.to;
        kl.to=d;
        it=lower_bound(puti.begin(),puti.end(),kl,[](cesta range1,cesta range2) {
       if(range2.from != range1.from) {return (range2.from > range1.from );}
       else{return (range2.to > range1.to);}
        });

      if(it!=puti.end()){
        if(it->from==r2&&it->to==r1)
          it->rtr.push_back(r3);
        else
          puti.insert(it,kl);
      }
      else{puti.insert(it,kl);}
      int po=0;
      for(auto it=puti.begin();it<puti.end();it++){
        it->pocet=po;
        po++;
      }
      return *this;
    }
    list<_T> Find(const _T &from,const _T &to)const{
      list<_T> list_by_f;
      int mesto=0;
      //int pidr[lox*lox];
      vector<data>pidr;
      if(from==to){
        list_by_f.push_back(to);return list_by_f;
      }
      auto it=lower_bound(puti.begin(),puti.end(),from,[](cesta range1,_T range2)
       {return (range2 > range1.from );});
       for(auto it1=it;it1<puti.end();it1++){
          if(it1->from!=from){break;}
          data rtr;
          rtr.m_back=-1;
          rtr.m_poz=it1->pocet;
          pidr.push_back(rtr);
       }
              if(pidr.empty()){
         throw NoRouteException ();
       }
       while(1){
            auto it=lower_bound(puti.begin(),puti.end(),puti[pidr[mesto].m_poz].to,[](cesta range1,_T range2)
            {return (range2 > range1.from );}); 
            for(auto it1=it;it1<puti.end();it1++){
              if(puti[pidr[mesto].m_poz].to!=it1->from){break;}
                data rtr;
                rtr.m_back=mesto;
                rtr.m_poz=it1->pocet;
                pidr.push_back(rtr);
                if(it1->from==to){
                  list_by_f.insert(list_by_f.begin(),it1->from);
                  int kde=pidr[pidr.size()-1].m_back;
                  for(;;){
                    list_by_f.insert(list_by_f.begin(),puti[pidr[kde].m_poz].from);
                    kde=pidr[kde].m_back;
                    if(kde==-1){return list_by_f;}
                  }
                }
            }
          mesto++;
       }
      return list_by_f;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename Compare>
list<_T> Find(const _T &from,const _T &to,const Compare &fun)const {
      bool proverka=false;

      list<_T> list_by_f;
      int mesto=0;
      vector<data>pidr;
      if(from==to){
        list_by_f.push_back(to);return list_by_f;
      }
      auto it=lower_bound(puti.begin(),puti.end(),from,[](cesta range1,_T range2)
       {return (range2 > range1.from );});
       for(auto it1=it;it1<puti.end();it1++){
          if(it1->from!=from){break;}
          for(auto it2=it1->rtr.begin();it2<it1->rtr.end();it2++){
            if(fun(*it2))
              proverka=true;
          }
          if(proverka){
          data rtr;
          rtr.m_back=-1;
          rtr.m_poz=it1->pocet;
          pidr.push_back(rtr);
          }
          proverka=false;
       }
              if(pidr.empty()){
         throw NoRouteException ();
       }
       while(1){
            auto it=lower_bound(puti.begin(),puti.end(),puti[pidr[mesto].m_poz].to,[](cesta range1,_T range2)
            {return (range2 > range1.from );}); 
            for(auto it1=it;it1<puti.end();it1++){
              if(puti[pidr[mesto].m_poz].to!=it1->from){break;}
          for(auto it2=it1->rtr.begin();it2<it1->rtr.end();it2++){
            if(fun(*it2))
              proverka=true;
          }
          if(proverka){
                data rtr;
                rtr.m_back=mesto;
                rtr.m_poz=it1->pocet;
                pidr.push_back(rtr);
                if(it1->from==to){
                  list_by_f.insert(list_by_f.begin(),it1->from);
                  int kde=pidr[pidr.size()-1].m_back;
                  for(;;){
                    list_by_f.insert(list_by_f.begin(),puti[pidr[kde].m_poz].from);
                    kde=pidr[kde].m_back;
                    if(kde==-1){return list_by_f;}
                  }
                }
          }
          proverka=false;
            }
          mesto++;
       }
      return list_by_f;
    }
    ~CRoute(){}
    // destructor
    // Add

    // Find (with optional filter)
    private:

    class cesta
    {
      public:
      cesta(){
        rtr.clear();
      }
      cesta(const _T & f, const _T &t, const _E &tr):
        from(f), to(t)  {
          rtr.push_back(tr);
        };
      _T from;
      _T to;
      vector<_E> rtr;
      int pocet=-1;
      
    };
    struct data
    {
      int m_poz=0;
      int m_back=0;
    };
    int poradok=0;
    vector<cesta>puti;
    bool flag=false;
    };



#ifndef __PROGTEST__
//=================================================================================================
class CTrain
{
  public:
                             CTrain                        ( const string    & company, 
                                                             int               speed )
                             : m_Company ( company ), 
                               m_Speed ( speed ) 
    { 
    }
    //---------------------------------------------------------------------------------------------
    string                   m_Company;
    int                      m_Speed; 
};
//=================================================================================================
class TrainFilterCompany
{
  public:
                             TrainFilterCompany            ( const set<string> & companies ) 
                             : m_Companies ( companies ) 
    { 
    }
    //---------------------------------------------------------------------------------------------
    bool                     operator ()                   ( const CTrain & train ) const
    { 
      return m_Companies . find ( train . m_Company ) != m_Companies . end (); 
    }
    //---------------------------------------------------------------------------------------------
  private:  
    set <string>             m_Companies;    
};
//=================================================================================================
class TrainFilterSpeed
{
  public:
                             TrainFilterSpeed              ( int               min, 
                                                             int               max )
                             : m_Min ( min ), 
                               m_Max ( max ) 
    { 
    }
    //---------------------------------------------------------------------------------------------
    bool                     operator ()                   ( const CTrain    & train ) const
    { 
      return train . m_Speed >= m_Min && train . m_Speed <= m_Max; 
    }
    //---------------------------------------------------------------------------------------------
  private:  
    int                      m_Min;
    int                      m_Max; 
};
//=================================================================================================
bool               NurSchnellzug                           ( const CTrain    & zug )
{
  return ( zug . m_Company == "OBB" || zug . m_Company == "DB" ) && zug . m_Speed > 100;
}
//=================================================================================================
static string      toText                                  ( const list<string> & l )
{
  ostringstream oss;
  
  auto it = l . cbegin();
  oss << *it;
  for ( ++it; it != l . cend (); ++it )
    oss << " > " << *it;
  return oss . str ();
}
//=================================================================================================
int main ( void )
{
  CRoute<string,CTrain> lines;
  
  lines . Add ( "Berlin", "Prague", CTrain ( "DB", 120 ) )
        . Add ( "Berlin", "Prague", CTrain ( "CD",  80 ) )
        . Add ( "Berlin", "Dresden", CTrain ( "DB", 160 ) )
        . Add ( "Dresden", "Munchen", CTrain ( "DB", 160 ) )
        . Add ( "Munchen", "Prague", CTrain ( "CD",  90 ) )
        . Add ( "Munchen", "Linz", CTrain ( "DB", 200 ) )
        . Add ( "Munchen", "Linz", CTrain ( "OBB", 90 ) )
        . Add ( "Linz", "Prague", CTrain ( "CD", 50 ) )
        . Add ( "Prague", "Wien", CTrain ( "CD", 100 ) )
        . Add ( "Linz", "Wien", CTrain ( "OBB", 160 ) )
        . Add ( "Paris", "Marseille", CTrain ( "SNCF", 300 ))
        . Add ( "Paris", "Dresden",  CTrain ( "SNCF", 250 ) );
  //lines.show();
  list<string> r1 = lines . Find ( "Berlin", "Linz" );
  assert ( toText ( r1 ) == "Berlin > Prague > Linz" );
  
  list<string> r2 = lines . Find ( "Linz", "Berlin" );
  assert ( toText ( r2 ) == "Linz > Prague > Berlin" );

  list<string> r3 = lines . Find ( "Wien", "Berlin" );
  assert ( toText ( r3 ) == "Wien > Prague > Berlin" );

  list<string> r4 = lines . Find ( "Wien", "Berlin", NurSchnellzug );
  assert ( toText ( r4 ) == "Wien > Linz > Munchen > Dresden > Berlin" );

  list<string> r5 = lines . Find ( "Wien", "Munchen", TrainFilterCompany ( set<string> { "CD", "DB" } ) );
  assert ( toText ( r5 ) == "Wien > Prague > Munchen" );

  list<string> r6 = lines . Find ( "Wien", "Munchen", TrainFilterSpeed ( 120, 200 ) );
  assert ( toText ( r6 ) == "Wien > Linz > Munchen" );

  list<string> r7 = lines . Find ( "Wien", "Munchen", [] ( const CTrain & x ) { return x . m_Company == "CD"; } );
   assert ( toText ( r7 ) == "Wien > Prague > Munchen" );

  list<string> r8 = lines . Find ( "Munchen", "Munchen" );
  assert ( toText ( r8 ) == "Munchen" );
  
  list<string> r9 = lines . Find ( "Marseille", "Prague" );
  assert ( toText ( r9 ) == "Marseille > Paris > Dresden > Berlin > Prague" 
           || toText ( r9 ) == "Marseille > Paris > Dresden > Munchen > Prague" );
  
  try 
  { 
    list<string> r10 = lines . Find ( "Marseille", "Prague", NurSchnellzug ); 
    assert ( "Marseille > Prague connection does not exist!!" == NULL );
  }
  catch ( const NoRouteException & e ) 
  { 
  }
  
  list<string> r11 = lines . Find ( "Salzburg", "Salzburg" );
  assert ( toText ( r11 ) == "Salzburg" );

  list<string> r12 = lines . Find ( "Salzburg", "Salzburg", [] ( const CTrain & x ) { return x . m_Company == "SNCF"; }  );
  assert ( toText ( r12 ) == "Salzburg" );

  try 
  { 
    list<string> r13 = lines . Find ( "London", "Oxford" ); 
    assert ( "London > Oxford connection does not exist!!" == NULL );
  }
  catch ( const NoRouteException & e ) 
  { 
  }
  return 0;
}
#endif  /* __PROGTEST__ */

