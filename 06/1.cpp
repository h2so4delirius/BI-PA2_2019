#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>
using namespace std;
#endif /* __PROGTEST__ */
//the flag is used to determine the method of writing
int flag=1;
int flag_1=1;
int flag_2=1;
int flag_3=1;
class component {//parent for output functions
public:
	   virtual  void output(ostream &oss) const = 0 ;
};

class CCPU :public component
{
public:
	CCPU(int jadra, int mhz) {//designer
		this->jadra = jadra;
		this->mhz = mhz;
	}
  CCPU()=default;
    void output(ostream & oss)const{//output
    if(flag_3==false){
        if(flag==true)
        oss<<"  ";
        else
        oss<<"| ";
    }
    if(flag_1)
    oss<<"\\";
    else
    oss<<"+";
    oss<<"-CPU, "<<jadra<<" cores @ "<<mhz<<"MHz"<<endl;
  }
private:
	int jadra;
	int mhz;
};
class CMemory :public component
{
public:
	CMemory(int mib) {//designer
		this->mib = mib;
	}
  CMemory()=default;
  void output(ostream & oss)const{//output
      if(flag_3==false){
          if(flag==true)
          oss<<"  ";
          else
          oss<<"| ";
      }
    if(flag_1)
    oss<<"\\";
    else
    oss<<"+";
    oss<<"-Memory, "<<mib<<" MiB"<<endl;
  }
private:
	int mib;
};
class CDisk :public component 
{

public:
	CDisk(bool typ, int GIB) {//designer
		this->typ = typ;
		this->GIB = GIB;
	}
  CDisk()=default;
    void output(ostream &oss)const{//output
    flag_2=false;
		if(flag_3==false){
			if(flag==true)
			oss<<"  ";
			else
			oss<<"| ";
		}
    if(flag_1)
    oss<<"\\";
    else
    oss<<"+";
    if(typ==true)
    oss<<"-SSD, ";
    else 
    oss<<"-HDD, ";
    oss<<GIB<<" GiB"<<endl;
    int i=0;
    for (auto it = p.begin();it<p.end();it++){
          if((it+1)==p.end()){
            flag_2=true;
					}
            if(flag_3==false){
              if(flag==true)
              oss<<"  ";
              else
              oss<<"| ";
						}
              if(flag_1==true)
              oss<<"  ";
              else
              oss<<"| ";
            
          if(flag_2)
          oss<<"\\";
          else
          oss<<"+";
      		oss<<"-["<<i<<"]: "<<it->pamet<<" GiB, "<<it->nazev<<endl;
          i++;
    }
  }
	CDisk & AddPartition(int pamet, string nazev) {//add folder
		cod rtr;
		rtr.nazev = nazev;
		rtr.pamet = pamet;
		p.push_back(rtr);
		return *this;
	}
	static const bool SSD = true;//use to determine the type of disk
  static const bool MAGNETIC=false;
private:
	struct cod
	{
		string nazev;
		int pamet;
	};
	bool typ;
	int GIB;
	vector<cod>p;
};
class CComputer
{
public:
	CComputer(string ccomputer) {//designer
		this->ccomputer = ccomputer;
	}

  CComputer()=default;

	CComputer& AddAddress(const string &cip) {//Add аddress
		ip.push_back(cip);
		return *this;
	}

	CComputer& AddComponent(const CMemory &rtr)//1 overload
	{		
componenty.push_back(make_shared<CMemory>(rtr));
		return *this;
	}

	CComputer& AddComponent(const CDisk &rtr)//2 overload
	{
		componenty.push_back(make_shared<CDisk>(rtr));
		return *this;
	}

	CComputer& AddComponent(const CCPU &rtr)//3 overload
	{
componenty.push_back(make_shared<CCPU>(rtr));
		return *this;
	}

  string getcomp(){//return the name of the computer
    return ccomputer;
  }

    friend ostream& operator <<( ostream & oss,CComputer const &rtr){//output
      flag_1=false;
      if(flag==true){
    if(flag_3==false)
        oss<<"\\-Host: "<<rtr.ccomputer<<endl;
      else
        oss<<"Host: "<<rtr.ccomputer<<endl;
      for(auto it=rtr.ip.begin();it<rtr.ip.end();it++)
        if(flag_3==false)
        oss<<"  +-"<<*it<<endl;
        else 
        oss<<"+-"<<*it<<endl;
      }
      else{
      if(flag_3==false) 
        oss<<"+-Host: "<<rtr.ccomputer<<endl;
      else 
          oss<<"Host: "<<rtr.ccomputer<<endl;    
      for(auto it=rtr.ip.begin();it<rtr.ip.end();it++)
        if(flag_3==false)
        oss<<"| +-"<<*it<<endl;      
        else
        oss<<"+-"<<*it<<endl;   
      }
    for(auto it=rtr.componenty.begin();it<rtr.componenty.end();it++){
      if(it+1==rtr.componenty.end()){
         flag_1=true;
      }
      (*it)->output(oss);
    }
  return oss;
  }

private:
	string ccomputer;
	vector<shared_ptr<component>>componenty;
	vector<string>ip;
};

class CNetwork {
public:
	CNetwork(string network) {//designer
		this->network = network;
	}
  CComputer*FindComputer(string comp){//searches for a computer by name and returns a link to it
    for(auto &k : ccomputer){
      if(k.getcomp()==comp)
      return &k;
  	}
		return nullptr;
	}
	CNetwork&AddComputer(const CComputer &comp) {//adds the computer to the list
		auto n = make_shared<CComputer>();
    *n=comp;
    ccomputer.push_back(comp);
		return *this;
	}
friend ostream & operator <<( ostream & oss,CNetwork const &rtr)//output
{
  flag=false;
	oss<<"Network: "<<rtr.network<<endl;
    for(auto it=rtr.ccomputer.begin();it<rtr.ccomputer.end();it++){
      if(it+1==rtr.ccomputer.end())
         flag=true;
      flag_3=false;
      oss<<*it;
    }  
    flag_3=true;
	return oss;
}
CNetwork(CNetwork &other) {//copy  class
	this->network=other.network;
	ccomputer.clear();
	for(auto k : other.ccomputer){
		ccomputer.push_back(k);
	}
}

private:
	string network;
	vector<CComputer>ccomputer;
};


#ifndef __PROGTEST__
template<typename _T>
string toString ( const _T & x )
{
  ostringstream oss;
  oss << x;
  return oss . str ();
}

int main(void)
{
	CNetwork n("FIT network");
	n.AddComputer(
		CComputer("progtest.fit.cvut.cz") .
		AddAddress("147.32.232.142") .
		AddComponent(CCPU(8, 2400)) .
		AddComponent(CCPU(8, 1200)) .
		AddComponent(CDisk(CDisk::MAGNETIC, 1500) .
			AddPartition(50, "/") .
			AddPartition(5, "/boot").
			AddPartition(1000, "/var")) .
		AddComponent(CDisk(CDisk::SSD, 60) .
			AddPartition(60, "/data")) .
		AddComponent(CMemory(2000)).
		AddComponent(CMemory(2000))) .
		AddComputer(
			CComputer("edux.fit.cvut.cz") .
			AddAddress("147.32.232.158") .
			AddComponent(CCPU(4, 1600)) .
			AddComponent(CMemory(4000)).
			AddComponent(CDisk(CDisk::MAGNETIC, 2000) .
				AddPartition(100, "/")   .
				AddPartition(1900, "/data"))) .
		AddComputer(
			CComputer("imap.fit.cvut.cz") .
			AddAddress("147.32.232.238") .
			AddComponent(CCPU(4, 2500)) .
			AddAddress("2001:718:2:2901::238") .
			AddComponent(CMemory(8000)));
	assert(toString(n) ==
		"Network: FIT network\n"
		"+-Host: progtest.fit.cvut.cz\n"
		"| +-147.32.232.142\n"
		"| +-CPU, 8 cores @ 2400MHz\n"
		"| +-CPU, 8 cores @ 1200MHz\n"
		"| +-HDD, 1500 GiB\n"
		"| | +-[0]: 50 GiB, /\n"
		"| | +-[1]: 5 GiB, /boot\n"
		"| | \\-[2]: 1000 GiB, /var\n"
		"| +-SSD, 60 GiB\n"
		"| | \\-[0]: 60 GiB, /data\n"
		"| +-Memory, 2000 MiB\n"
		"| \\-Memory, 2000 MiB\n"
		"+-Host: edux.fit.cvut.cz\n"
		"| +-147.32.232.158\n"
		"| +-CPU, 4 cores @ 1600MHz\n"
		"| +-Memory, 4000 MiB\n"
		"| \\-HDD, 2000 GiB\n"
		"|   +-[0]: 100 GiB, /\n"
		"|   \\-[1]: 1900 GiB, /data\n"
		"\\-Host: imap.fit.cvut.cz\n"
		"  +-147.32.232.238\n"
		"  +-2001:718:2:2901::238\n"
		"  +-CPU, 4 cores @ 2500MHz\n"
		"  \\-Memory, 8000 MiB\n");
	//cout<<"2\n";
	CNetwork x=n;
  //cout<<"2\n";
	auto c = x.FindComputer("imap.fit.cvut.cz");
  //cout<<toString(*c);
	assert(toString(*c) ==
		"Host: imap.fit.cvut.cz\n"
		"+-147.32.232.238\n"
		"+-2001:718:2:2901::238\n"
		"+-CPU, 4 cores @ 2500MHz\n"
		"\\-Memory, 8000 MiB\n");
	c->AddComponent(CDisk(CDisk::MAGNETIC, 1000) .
		AddPartition(100, "system") .
		AddPartition(200, "WWW") .
		AddPartition(700, "mail"));
	assert(toString(x) ==
		"Network: FIT network\n"
		"+-Host: progtest.fit.cvut.cz\n"
		"| +-147.32.232.142\n"
		"| +-CPU, 8 cores @ 2400MHz\n"
		"| +-CPU, 8 cores @ 1200MHz\n"
		"| +-HDD, 1500 GiB\n"
		"| | +-[0]: 50 GiB, /\n"
		"| | +-[1]: 5 GiB, /boot\n"
		"| | \\-[2]: 1000 GiB, /var\n"
		"| +-SSD, 60 GiB\n"
		"| | \\-[0]: 60 GiB, /data\n"
		"| +-Memory, 2000 MiB\n"
		"| \\-Memory, 2000 MiB\n"
		"+-Host: edux.fit.cvut.cz\n"
		"| +-147.32.232.158\n"
		"| +-CPU, 4 cores @ 1600MHz\n"
		"| +-Memory, 4000 MiB\n"
		"| \\-HDD, 2000 GiB\n"
		"|   +-[0]: 100 GiB, /\n"
		"|   \\-[1]: 1900 GiB, /data\n"
		"\\-Host: imap.fit.cvut.cz\n"
		"  +-147.32.232.238\n"
		"  +-2001:718:2:2901::238\n"
		"  +-CPU, 4 cores @ 2500MHz\n"
		"  +-Memory, 8000 MiB\n"
		"  \\-HDD, 1000 GiB\n"
		"    +-[0]: 100 GiB, system\n"
		"    +-[1]: 200 GiB, WWW\n"
		"    \\-[2]: 700 GiB, mail\n");
    //cout<<toString(n);
	assert(toString(n) ==
		"Network: FIT network\n"
		"+-Host: progtest.fit.cvut.cz\n"
		"| +-147.32.232.142\n"
		"| +-CPU, 8 cores @ 2400MHz\n"
		"| +-CPU, 8 cores @ 1200MHz\n"
		"| +-HDD, 1500 GiB\n"
		"| | +-[0]: 50 GiB, /\n"
		"| | +-[1]: 5 GiB, /boot\n"
		"| | \\-[2]: 1000 GiB, /var\n"
		"| +-SSD, 60 GiB\n"
		"| | \\-[0]: 60 GiB, /data\n"
		"| +-Memory, 2000 MiB\n"
		"| \\-Memory, 2000 MiB\n"
		"+-Host: edux.fit.cvut.cz\n"
		"| +-147.32.232.158\n"
		"| +-CPU, 4 cores @ 1600MHz\n"
		"| +-Memory, 4000 MiB\n"
		"| \\-HDD, 2000 GiB\n"
		"|   +-[0]: 100 GiB, /\n"
		"|   \\-[1]: 1900 GiB, /data\n"
		"\\-Host: imap.fit.cvut.cz\n"
		"  +-147.32.232.238\n"
		"  +-2001:718:2:2901::238\n"
		"  +-CPU, 4 cores @ 2500MHz\n"
		"  \\-Memory, 8000 MiB\n"); 
		//cout<<toString(n);
		return 0;
}
#endif /* __PROGTEST__ */