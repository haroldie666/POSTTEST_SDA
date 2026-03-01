#include <iostream>
using namespace std;

int main() {
    int fibo[8] = {1, 1, 2, 3, 5, 8, 13, 21}; // Merupakan contoh dari kondisi best case, karenan array sudah terurut secara ascending
    int A = 8;
    int min = fibo[0];
    int index = 0;

    for(int i = 1; i < A; i++) {
        if(fibo[i] < min) {
            min = fibo[i];
            index = i;
        }
    }

    cout << "Nilai minimum adalah  : " << min << endl;
    cout << "Indeks nilai minimum adalah : " << index << endl;

    return 0;
}

/*
--------------------------------------------------------
| Pseudocode              |  Cost   |  Tmin  |  Tmax   |
|-------------------------|----------------------------|
| procedure FindMin       |   C1    |   1    |    1    |
|-------------------------|----------------------------|
| min ← A[0]              |   C2    |   1    |    1    |
|-------------------------|----------------------------|
| for i ← 1 to n - 1 do   |   C3    |   n    |    n    |
|-------------------------|----------------------------|
| if A[i] < min then      |   C4    |  n-1   |   n-1   |
|-------------------------|----------------------------|
| min ← A[i]              |   C5    |   0    |   n-1   |
|-------------------------|----------------------------|
| end if                  |   C6    |  n-1   |   n-1   |
|-------------------------|----------------------------|
| end for                 |   C7    |   n    |    n    |
|-------------------------|----------------------------|
| return min              |   C8    |   1    |    1    |
|-------------------------|----------------------------|
| end procedure           |   C9    |   1    |    1    |
|-------------------------|----------------------------|
| Total waktu (Tn)                  |  O(n)  |   O(n)  |
|------------------------------------------------------|

Tmin (best case) 
C1 + C2 + C3n + C4(n-1) + 0 + C6(n-1) + C7n + C8+ C9
C4(n-1) = C4n-C4
C6(n-1) = C6n-C6
Tn = C1 + C2 + C3n + C4n-C4 + 0 + C6n-C6 + C7n + C8+ C9
   = (C3+C4+C6+C7)n + (C1+C2+C8+C9−C4−C6)
   = (1+1+1+1)n + (1+1+1+1-1-1)
   = 4n + 2
   = O(n) => karena membentuk fungsi linear, maka Big O-nya adalah O(n)

Tmax (worst case)
C1 + C2 + C3n + C4(n-1) + C5(n-1) + C6(n-1) + C7n + C8+ C9
C4(n-1) = C4n-C4
C5(n-1) = C5n-C5
C6(n-1) = C6n-C6
Tn = C1 + C2 + C3n + C4n-C4 + C5n-C5 + C6n-C6 + C7n + C8+ C9
   = (C3+C4+C5+C6+C7)n + (C1+C2+C8+C9−C4−C5−C6)
   = (1+1+1+1+1)n + (1+1+1+1-1-1-1)
   = 5n + 1
   = O(n) => karena membentuk fungsi linear, maka Big O-nya adalah O(n)

*/