#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>
using namespace std;

class CTimeStamp
{
public:
	CTimeStamp(int               year,
		int               month,
		int               day,
		int               hour,
		int               minute,
		double            sec) {
		this->year = year; this->month = month; this->day = day; this->hour = hour; this->minute = minute; this->sec = sec;

	}
	//CTimeStamp() {}
	int            Compare(const CTimeStamp & x) const {
		if (year != x.year) {
			if (year > x.year)
				return 1;
			else
				return -1;
		}
		if (month != x.month) {
			if (month > x.month)
				return 1;
			else
				return -1;
		}
		if (day != x.day) {
			if (day > x.day)
				return 1;
			else
				return -1;
		}
		if (hour != x.hour) {
			if (hour > x.hour)
				return 1;
			else
				return -1;
		}
		if (minute != x.minute) {
			if (minute > x.minute)
				return 1;
			else
				return -1;
		}
		if (sec > x.sec)
			return 1;
		if(sec==x.sec)
			return 0;
		else 
		return -1;
        return 1;
	}
	/*int  getyear()const{return year;}
	int  getmonth()const{return month;}
	int  getday()const{return day;}
	int  gethod()const{return hour;}
	int  getmin()const{return minute;}
	double  getsec()const{return sec;}*/


	friend ostream & operator <<                           (ostream          & os,
		const CTimeStamp & x) {
		//cout<<"xui\n";

		os << x.year << "-" << setw(2) << setfill('0') << x.month << "-" << setw(2) << setfill('0') << x.day << " " << setw(2) << setfill('0') << x.hour << ":" << setw(2) << setfill('0') << x.minute << ":";
		os.precision(5);
		os << showpoint << setw(5) << setfill('0') << x.sec << " ";
		return os;
	}

private:
	int year, month, day, hour, minute;
	double sec;
};

class CMail
{
public:
CMail ( const CTimeStamp & timeStamp, const string & from, const string & to,const string & subject )
:timeStamp(timeStamp),from(from), to(to), subject(subject) {}
CMail(const CTimeStamp & timeStamp) :timeStamp(timeStamp){}
int CompareByTime ( const CTimeStamp & x ) const{
		return timeStamp.Compare(x);
}
int CompareByTime ( const CMail & x ) const{
		return timeStamp.Compare(x.timeStamp);
}
const string & From ( void ) const{return this->from;}
const string & To ( void ) const{return this->to;}
const string & Subject ( void ) const{return this->subject;}
const CTimeStamp & TimeStamp ( void ) const{return this->timeStamp;}
friend ostream & operator <<( ostream & os, const CMail & x ){
			os << x.timeStamp << x.from << " -> " << x.to << ", subject: " << x.subject;
		return os;
}
private:
CTimeStamp timeStamp;
string from;
string to;
string subject;
};

// your code will be compiled in a separate namespace
namespace MysteriousNamespace {
#endif /* __PROGTEST__ */
	//----------------------------------------------------------------------------------------
	class CMailLog
	{
	public:
		int            ParseLog(istream          & in) {
			int i = 0, rok, den, hodina, min, month=0;
			double sec;
			string mesic, nez, kod, last;
			char pop;
			while (in >> mesic) {
				if (mesic == "Jan")
					month = 1;
				else if (mesic == "Feb")
					month = 2;
				else if (mesic == "Mar")
					month = 3;
				else if (mesic == "Apr")
					month = 4;
				else if (mesic == "May")
					month = 5;
				else if (mesic == "Jun")
					month = 6;
				else if (mesic == "Jul")
					month = 7;
				else if (mesic == "Aug")
					month = 8;
				else if (mesic == "Sep")
					month = 9;
				else if (mesic == "Oct")
					month = 10;
				else if (mesic == "Nov")
					month = 11;
				else if (mesic == "Dec")
					month = 12;
				in >> den;
				in >> rok;
				in >> hodina;
				in >> pop;
				in >> min;
				in >> pop;
				in >> sec;
				in >> nez;
				in >> kod;
				getline(in, last);
				if (last[1] == 't') {
					if (last[2] == 'o'&&last[3] == '=') {
						last = last.substr(4, last.length());
						i++;
						auto it = lower_bound(multiv.begin(), multiv.end(), kod, [](klass1 range2, string kod) {return (range2.kodirovka < kod); });
						if (it == multiv.end())
							goto pppp;

						if ((it->kodirovka) != kod)
							goto pppp;

						CTimeStamp tt(rok, month, den, hodina, min, sec);
						CMail ggg(tt, it->from, last, it->sub);
						auto it1 = lower_bound(v.begin(), v.end(), ggg, [](const CMail &x, const CMail &y) {
							int p=((x).CompareByTime(y));
							if(p==0||p<0) 
							return 1;
							else
							return 0;
							
						});
						v.insert(it1, ggg);
					}
				pppp:
					sec = 0;
				}
				if (last[1] == 'f'&&last[2] == 'r'&&last[3] == 'o'&&last[4] == 'm'&&last[5] == '=') {
					last = last.substr(6, last.length());
					klass1 rtr;
					rtr.from = last;
					rtr.kodirovka = kod;
					auto it = lower_bound(multiv.begin(), multiv.end(), kod, [](klass1 range2, string kod) {return (range2.kodirovka < kod); });
					int flag = 0;
					if (it != multiv.end()) {
						if (it->kodirovka == kod)
							flag = 1;
					}
					if (flag == 1 && it->from == "")
						flag = 2;
					if (flag == 2)
						it->from = last;
					if (flag == 0)
						multiv.insert(it, rtr);
				}
				if (last[1] == 's'&&last[2] == 'u'&&last[3] == 'b'&&last[4] == 'j'&&last[5] == 'e'&&last[6] == 'c'&&last[7] == 't'&&last[8] == '=') {
					last = last.substr(9, last.length());
					klass1 rtr;
					rtr.sub = last;
					rtr.kodirovka = kod;
					auto it = lower_bound(multiv.begin(), multiv.end(), kod, [](const klass1 &range2,const string &kod) {return (range2.kodirovka < kod); });
					int flag = 0;
					if (it != multiv.end()) {
						if (it->kodirovka == kod)
							flag = 1;
					}
					if (flag == 1 && it->sub == "")
						flag = 2;
					if (flag == 2)
						it->sub = last;
					if (flag == 0)
						multiv.insert(it, rtr);
				}
			}
			return i;
		}

		list<CMail>    ListMail(const CTimeStamp & from,
			                    const CTimeStamp & to) const {
			list<CMail>vp;
			CMail ggg(from, "", "", "");

			auto it = lower_bound(v.begin(), v.end(), ggg, [](const CMail &x, const CMail &y) {
							int p=((x).CompareByTime(y));
							if(p==0||p<0) 
							return 1;
							else
							return 0;
			});
			if (it != v.end()){
				
                //cout<<it->Subject()<<it->From()<<it->To();
			//cout<<it->hodina<<endl;
			//cout<<i; 
             
			for (; it < v.end(); it++) {

				if (it->CompareByTime(to)>0)
					break;

				//CTimeStamp tt(it->rok,it->month,it->day,it->hodina,it->minuta,it->sex);
				//CMail ggg(tt,it->fromm,it->too,it->subb);
				//i++;
				 //cout<<i<<endl;
				 vp.push_back(*it);
			}
                                }

			return vp;

		}

		set<string>    ActiveUsers(const CTimeStamp & from,
	                               const CTimeStamp & to) const {
			set<string>vp;
			CMail ggg(from, "", "", "");

			auto it = lower_bound(v.begin(), v.end(), ggg, [](const CMail &x, const CMail &y) {
							int p=((x).CompareByTime(y));
							if(p==0||p<0) 
							return 1;
							else
							return 0;
			});
			if (it != v.end()){
				
                //cout<<it->Subject()<<it->From()<<it->To();
			//cout<<it->hodina<<endl;
			//cout<<i; 
             
			for (; it < v.end(); it++) {
				if (it->CompareByTime(to)>0)
					break;
                string f=it->From();
                string t=it->To();
				vp.insert(f);
				vp.insert(t);
			}
            }
		
			return vp;

		}
	private:

		struct klass1
		{
			string from = "";
			string sub = "";
			string kodirovka = "";
		};
		
		vector<klass1>multiv;
		vector<CMail>v;
	};
	//----------------------------------------------------------------------------------------
#ifndef __PROGTEST__
} // namespace
string             printMail(const list<CMail> & all)
{
	ostringstream oss;
	for (const auto & mail : all)
		oss << mail << endl;
	return oss.str();
}
string             printUsers(const set<string> & all)
{
	ostringstream oss;
	bool first = true;
	for (const auto & name : all)
	{
		if (!first)
			oss << ", ";
		else
			first = false;
		oss << name;
	}
	return oss.str();
}
int                main(void)
{
	MysteriousNamespace::CMailLog m;
	list<CMail> mailList;
	set<string> users;
	istringstream iss;

	iss.clear();
	iss.str(
		"Mar 29 2019 12:35:32.233 relay.fit.cvut.cz ADFger72343D: from=user1@fit.cvut.cz\n"
		"Mar 29 2019 12:37:16.234 relay.fit.cvut.cz JlMSRW4232Df: from=person3@fit.cvut.cz\n"
		"Mar 29 2019 12:55:13.023 relay.fit.cvut.cz JlMSRW4232Df: subject=New progtest homework!\n"
		"Mar 29 2019 13:38:45.043 relay.fit.cvut.cz Kbced342sdgA: from=office13@fit.cvut.cz\n"
		"Mar 29 2019 13:36:13.023 relay.fit.cvut.cz JlMSRW4232Df: to=user76@fit.cvut.cz\n"
		"Mar 29 2019 13:55:31.456 relay.fit.cvut.cz KhdfEjkl247D: from=PR-department@fit.cvut.cz\n"
		"Mar 29 2019 14:18:12.654 relay.fit.cvut.cz Kbced342sdgA: to=boss13@fit.cvut.cz\n"
		"Mar 29 2019 14:48:32.563 relay.fit.cvut.cz KhdfEjkl247D: subject=Business partner\n"
		"Mar 29 2019 14:58:32.000 relay.fit.cvut.cz KhdfEjkl247D: to=HR-department@fit.cvut.cz\n"
		"Mar 29 2019 14:25:23.233 relay.fit.cvut.cz ADFger72343D: mail undeliverable\n"
		"Mar 29 2019 15:02:34.231 relay.fit.cvut.cz KhdfEjkl247D: to=CIO@fit.cvut.cz\n"
		"Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=CEO@fit.cvut.cz\n"
		"Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=dean@fit.cvut.cz\n"
		"Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=vice-dean@fit.cvut.cz\n"
		"Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=archive@fit.cvut.cz\n");
	//cout<<iss.str();
	assert(m.ParseLog(iss) == 8);
	//m.show();
	mailList = m.ListMail(CTimeStamp(2019, 3, 28, 0, 0, 0),
		CTimeStamp(2019, 3, 29, 23, 59, 59));

	assert(printMail(mailList) ==
		"2019-03-29 13:36:13.023 person3@fit.cvut.cz -> user76@fit.cvut.cz, subject: New progtest homework!\n"
		"2019-03-29 14:18:12.654 office13@fit.cvut.cz -> boss13@fit.cvut.cz, subject: \n"
		"2019-03-29 14:58:32.000 PR-department@fit.cvut.cz -> HR-department@fit.cvut.cz, subject: Business partner\n"
		"2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> CEO@fit.cvut.cz, subject: Business partner\n"
		"2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> dean@fit.cvut.cz, subject: Business partner\n"
		"2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> vice-dean@fit.cvut.cz, subject: Business partner\n"
		"2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> archive@fit.cvut.cz, subject: Business partner\n"
		"2019-03-29 15:02:34.231 PR-department@fit.cvut.cz -> CIO@fit.cvut.cz, subject: Business partner\n");

	mailList = m.ListMail(CTimeStamp(2019, 3, 28, 0, 0, 0),
		CTimeStamp(2019, 3, 29, 14, 58, 32));
	//cout<<(printMail(mailList));
	assert(printMail(mailList) ==
		"2019-03-29 13:36:13.023 person3@fit.cvut.cz -> user76@fit.cvut.cz, subject: New progtest homework!\n"
		"2019-03-29 14:18:12.654 office13@fit.cvut.cz -> boss13@fit.cvut.cz, subject: \n"
		"2019-03-29 14:58:32.000 PR-department@fit.cvut.cz -> HR-department@fit.cvut.cz, subject: Business partner\n");
	mailList = m.ListMail(CTimeStamp(2019, 3, 30, 0, 0, 0),
		CTimeStamp(2019, 3, 30, 23, 59, 59));
	assert(printMail(mailList) == "");
	users = m.ActiveUsers(CTimeStamp(2019, 3, 28, 0, 0, 0),
		CTimeStamp(2019, 3, 29, 23, 59, 59));
	assert(printUsers(users) == "CEO@fit.cvut.cz, CIO@fit.cvut.cz, HR-department@fit.cvut.cz, PR-department@fit.cvut.cz, archive@fit.cvut.cz, boss13@fit.cvut.cz, dean@fit.cvut.cz, office13@fit.cvut.cz, person3@fit.cvut.cz, user76@fit.cvut.cz, vice-dean@fit.cvut.cz");
	users = m.ActiveUsers(CTimeStamp(2019, 3, 28, 0, 0, 0),
		CTimeStamp(2019, 3, 29, 13, 59, 59));
       // cout<<printUsers(users);
	assert(printUsers(users) == "person3@fit.cvut.cz, user76@fit.cvut.cz");
    //Scout<<"1";*/
	return 0;
}
#endif /* __PROGTEST__ */