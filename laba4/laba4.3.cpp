#include <iostream>
#include <vector>
#include <map>

using namespace std;

unsigned int xorshift(unsigned int& state) {
    unsigned int x = state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state = x;
    return x;
}

int main() {
    unsigned int X = 123456789;
    unsigned int N = 5;  
    
    cout << "X = " << X << " Вывод: ";
    
    vector<unsigned int> seq;
    map<unsigned int, int> firstIndex;
    
    unsigned int state = X;
    
    for (unsigned int i = 0; i < N; i++) {
        unsigned int num = xorshift(state);
        seq.push_back(num);
        
        if (firstIndex.find(num) != firstIndex.end()) {
            for (const auto& val : seq) {
                cout << val << " ";
            }
            cout << firstIndex[num] << endl;
            return 0;
        }
        
        firstIndex[num] = i;
    }
    
    // Если повторения не было за N чисел
    for (const auto& val : seq) {
        cout << val << " ";
    }
    cout << endl;
    
    return 0;
}
