#include <Complex.hpp>

template<typename f>
Complex<f>::Complex(): real(f(0)), imag(f(0)){}

template<typename f>
Complex<f>::Complex(f r, f i): real(r), imag(i){}

template<typename f>
Complex<f>::~Complex(){}

template<typename f>
f& Complex<f>::operator[](int index){
    if(index)
        return imag;
    else
        return real;
}

template<typename f>
Complex<f> Complex<f>::operator+(Complex<f>& c){
    return Complex<f>(real + c[0], imag + c[1]);
}

template<typename f>
Complex<f> Complex<f>::operator-(Complex<f>& c){
    return Complex<f>(real - c[0], imag - c[1]);
}

template<typename f>
Complex<f> Complex<f>::operator*(Complex<f>& c){
    return Complex<f>(real*c[0] - imag*c[1], real*c[1] + imag*c[0]);
}

template<typename f>
Complex<f> Complex<f>::operator/(Complex<f>& c){
    Complex<f> temp( (*this)*(!c) );
    f c_abs2 = pow(c.abs(),2);
    return Complex<f>(temp[0]/c_abs2,temp[1]/c_abs2);
}

template<typename f>
f Complex<f>::abs(){
    return sqrt(real*real+imag*imag);
}

template<typename f>
Complex<f> Complex<f>::operator-(){
    return Complex<f>(-real,-imag);
}

template<typename f>
Complex<f> Complex<f>::operator!(){
    return Complex<f>(real,-imag);
}

template<typename f>
bool Complex<f>::operator==(Complex<f>& c){
    return real==c[0] && imag==c[1];
}

template<typename f>
bool Complex<f>::operator!=(Complex<f>& c){
    return real!=c[0] || imag!=c[1];
}
