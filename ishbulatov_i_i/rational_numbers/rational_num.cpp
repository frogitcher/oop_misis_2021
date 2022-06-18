#include <iostream>
#include "rational.h"
#include <cmath>
#include <stdexcept>
#include <algorithm>
int gcd(int a, int b){
    a=std::abs(a);
    b=std::abs(b);
    if (a==0){
        return b;
    }else{
    return gcd(b%a,a);
    }
}
void rational::normalize(){
    if (GetDen()<0 && GetNum()>=0){
        den=-den;
        num=-num;
    }
    int g=gcd(abs(GetNum()),abs(GetDen()));
    num=num/g;
    den=den/g;
}
rational::rational(int _num){
    num=_num;
    den=1;
}
rational::rational(int _num,int _den){
    num=_num;
    den=_den;
    if (den==0){
        throw std::invalid_argument("Denominator can not be 0");
    }
    rational::normalize();
}
rational::rational(const rational& other){
    num=other.GetNum();
    den=other.GetDen();
    rational::normalize();
}
rational& rational::operator=(const rational& rhs)
{
	num = rhs.GetNum();
	den = rhs.GetDen();
	return *this;
}
rational rational:: operator +(const rational& rhs) const{
    return rational(*this)+=rhs;
}
rational rational:: operator -(const rational& rhs) const{
    return rational(*this)-=rhs;
}
rational rational:: operator /(const rational& rhs) const {
    return rational(*this)/=rhs;

}
rational rational::operator*(const rational& rhs) const{
    return rational(*this)*=rhs;
}
rational& rational:: operator+=(const rational& rhs){
    int c=(abs(GetDen()*rhs.GetDen())/gcd(GetDen(),rhs.GetDen()));
    num=GetNum()*(c/GetDen())+rhs.GetNum()*(c/rhs.GetDen());
    den=c;
    rational::normalize();
    return *this;
}
rational& rational:: operator-=(const rational& rhs){
    int c=(abs(GetDen()*rhs.GetDen())/gcd(GetDen(),rhs.GetDen()));
    num=GetNum()*(c/GetDen())-rhs.GetNum()*(c/rhs.GetDen());
    den=c;
    rational::normalize();
    return *this;
}
rational& rational:: operator *=(const rational& rhs){
    num*=rhs.GetNum();
    den*=rhs.GetDen();
    normalize();
    return *this;
}
rational& rational::operator /=(const rational& rhs){
    if (rhs==rational(0)){
        throw std::domain_error("Division by 0!!!");
    }
    num*=rhs.GetNum();
    den*=rhs.GetDen();
    normalize();
    return *this;
}
bool rational::operator<(const rational& rhs) const{
    return!(*this>=rhs);
}
bool rational::operator>(const rational& rhs) const{
    return !(*this<=rhs);
}
bool rational::operator<=(const rational& rhs) const{
    return!(*this>rhs);
}
bool rational::operator>=(const rational& rhs) const{
    return !(*this<rhs);
}
bool rational::operator==(const rational& rhs) const{
    return ((GetNum()*rhs.GetDen())==(rhs.GetNum() * GetDen()));
}
bool rational::operator!=(const rational& rhs) const{
    return !(*this==rhs);
}
rational rational::operator -() const{
    rational a(*this);
    a.num*=-1;
    return a;
}
rational& rational::operator++(){
    return *this += 1;
}
rational rational::operator ++(int a){
    rational r(*this);
    *this+=rational(1,1);
    return r;
}
rational rational::operator --(int a){
    rational r(*this);
    *this -=rational(1,1);
    return r;
}
rational& rational::operator --(){
    rational(*this-=rational(1,1));
}
int main(){

}
