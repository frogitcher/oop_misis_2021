#include <iostream>
#include <vector>

using namespace std;

//template<size_t N>
struct vect{
private:
//public:
    size_t N;
    double a[20];
public:
    vect(size_t n){
        N = n;
        for(int i=0;i<n;i++)
            a[i] = 0;
    };
    vect(size_t n, vector<double> b){
        N = n;
        for(int i=0;i<n;i++)
            a[i] = b[i];
    };
    size_t Size(){
        return N;
    }
    double operator [](int i){
        return a[i];
    }
    vect operator =(vect b){
        if(this->N == b.Size()){
            for(int i=0;i<N;i++)
                a[i] = b[i];
        }
    }
    double operator =(double d){
        return d;
    }
    bool operator ==(vect b){
        if(N != b.Size())return false;
        for(int i=0;i<N;i++)if(a[i] != b[i])return false;
        return true;
    }
    ~vect() = default;
};

int main()
{
    vect a(10);
    vect b(10);
    vector<double> d;
    int i;
    for(i=0;i<10;i++)
        d.push_back(i/(2.0));
    vect c(10,d);
    for(i=0;i<10;i++)cout << c[i] << " ";
    a = c;
    cout << "\n";
    for(i=0;i<10;i++)cout << a[i] << " ";
    cout << ((a==c)?'t':'f');
}
