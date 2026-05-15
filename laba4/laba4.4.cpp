#include <iostream>
#include <vector>
using namespace std;

int main() {
    int cands, types;
    
    cout << "количество участников: ";
    cin >> cands;
    cout << "количество уникальных голосов: ";
    cin >> types;
    
    vector<int> scores(cands, 0);
    vector<vector<int>> pairs(cands, vector<int>(cands, 0));
    
    for (int t = 0; t < types; t++) {
        int cnt;
        string voteStr;
        
        cout << "количество голосов и столбец значений: ";
        cin >> cnt >> voteStr;
        
        vector<char> ranks(cands);
        for (int j = 0; j < cands; j++) {
            ranks[cands - 1 - j] = voteStr[j];
        }
        
        // Борда
        for (int j = 0; j < cands; j++) {
            int idx = ranks[j] - 'A';
            scores[idx] += j * cnt;
        }
        
        // Кондорсе
        for (int a = 0; a < cands; a++) {
            for (int b = a + 1; b < cands; b++) {
                int hi = ranks[a] - 'A';
                int lo = ranks[b] - 'A';
                pairs[lo][hi] += cnt;
            }
        }
    }
    
    // Максимум Борда
    int best = 0;
    for (int s : scores) {
        if (s > best) best = s;
    }
    
    cout << "\nПо Борду: ";
    for (int i = 0; i < cands; i++) {
        if (scores[i] == best) {
            cout << char('A' + i) << " (" << best << " очков)";
        }
    }
    cout << endl;
    
    cout << "По Кондорсе: ";
    bool found = false;
    for (int i = 0; i < cands; i++) {
        bool ok = true;
        for (int j = 0; j < cands; j++) {
            if (i != j && pairs[i][j] <= pairs[j][i]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << char('A' + i) << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "не определён" << endl;
    }
    
    return 0;
}
