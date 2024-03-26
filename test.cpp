#include <iostream>
#include <string> 
using namespace std;
int main(){
    string A;
    getline(cin, A);
    for(int i = 0; i < A.size(); ++i){
        if(A[i] >='A' && A[i] <= 'Z'){
            A[i] +=32;
        }else if(A[i] >= 'a' && A[i] <= 'z'){
            A[i] -= 32;
        }
    }
    cout << A;
    return 0;
}