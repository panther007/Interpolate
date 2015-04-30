#ifndef _INTERPOLATE_HPP
#define _INTERPOLATE_HPP

#define DEBUG_STM(fmt) \
        std::cout<<__FILE__<<":"<<__FUNCTION__<<":"<<__LINE__<<": "<<fmt<<std::endl
#define ERROR_STM(fmt) \
        std::cerr<<__FILE__<<":"<<__FUNCTION__<<":"<<__LINE__<<": "<<fmt<<std::endl


#include <iostream>
#include <cstdarg>
#include <string>
#include <stdexcept>
#include <sstream>
#include <assert.h>
#include <typeinfo>
#include <ios>
#include <iomanip>

namespace cs540 {

struct WrongNumberOfArgs: public std::runtime_error
{
    WrongNumberOfArgs(std::string const& message)
    : std::runtime_error(message + " Was thrown")
    {}
};
void throwException(){
    throw  WrongNumberOfArgs("Wrong Number Of Args");
}

void Interpolate_inside(std::stringstream& ss, std::string ln){
    std::string str2 ("%");
    std::size_t found=-1;
    std::string res("");
    do{
        found = ln.find(str2, found+1);
        if(found==std::string::npos){
            break;
        }
        if(found == 0){
            throwException();
        }
        if(ln.at(found-1)!='\\'){
            throwException();
        }
    }while(true);
    res += ln;
    std::string str3 ("\\%");
    std::size_t found2 = -1;
    do{
        found2 = res.find(str3, found2+1);
        
        if(found2==std::string::npos){
            break;
        }
        res.replace(found2, 2, std::string("%"));
        found2 --;
    }while(true);
	ss << res;
}
class ffr;
template<typename First>
bool isManipulators(First& arg){
	if(typeid(First) == typeid(std::ios_base& (*)(std::ios_base&)))
		return 1;
	std::stringstream tmpstr;
	tmpstr << arg;
	if(tmpstr.str().empty()){
		return 1;
	}
	return 0;
}
template<typename First>
bool isffr(First&){
	if(typeid(First) == typeid(ffr)){
		return 1;
	}
	return 0;
}
template<typename First, typename ... Strings>
void Interpolate_inside(std::stringstream& ss, const std::string ln, First& arg, Strings&... rest){
	if(isffr(arg)){
		ss << arg;
		Interpolate_inside(ss, ln, rest...);
		return;
	}
    std::string str2 ("%");
    std::size_t found=-1;
    std::string res("");
    do{
        found = ln.find(str2, found+1);
        if(found==std::string::npos){
		if(isManipulators(arg)){
			ss << ln;
			ss << arg;
			Interpolate_inside(ss, ln, rest...);
			return;	
		}
		else {
           		throwException();
		}
        }
        if(found == 0){
            break;
        }
        if(ln.at(found-1)!='\\'){
            break;
        }
    }while(true);
    res += ln.substr(0, found);
    std::string str3 ("\\%");
    std::size_t found2 = -1;
    do{
        found2 = res.find(str3, found2+1);
        
        if(found2==std::string::npos){
            break;
        }
        res.replace(found2, 2, std::string("%"));
        found2 --;
    }while(true);
	ss << res;
	if(isManipulators(arg)){
		ss << arg;
		std::string restStr = ln.substr(found);
		Interpolate_inside(ss, restStr, rest...);
	}
	
	else{
		ss << arg;
		std::string restStr = ln.substr(found+1);
    		res += ss.str();   
    		Interpolate_inside(ss, restStr, rest...);
	}
}

std::stringstream* sst;
template<typename ... Strings>
std::string Interpolate(const std::string ln, Strings&&... rest){ 
	std::stringstream st;
	sst = &st;
	st.str(std::string());	
	Interpolate_inside(st, ln, rest...);
	std::string res = st.str();
	st.str(std::string());
    	return res;
}

class ffr{
public:
	std::ostream& (*func) (std::ostream&);
	ffr(std::ostream& (*f) (std::ostream&)){
		this->func = &(*f);
	}
	friend std::ostream& operator<< (std::ostream& stream, const ffr& ftmp) {
		(*ftmp.func)(stream);
		return stream;
  }
	
};

}
#endif //#ifndef _INTERPOLATE_HPP

