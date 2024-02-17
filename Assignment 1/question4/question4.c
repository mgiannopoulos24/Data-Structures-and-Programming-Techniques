#include <stdio.h>

int is_valid_solution(int *values) {
    // Έλεγχος ότι κάθε ψηφίο είναι διαφορετικό
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (values[i] == values[j]) {
                return 0; // Μη έγκυρη λύση
            }
        }
    }

    // Έλεγχος εάν η πρόσθεση είναι έγκυρη
    int base = values['A' - 'A'];
    int ball = values['B' - 'A'];
    int games = values['G' - 'A'];
    int total1 = base * 1000 + ball * 100 + ball * 10 + base;
    int total2 = games * 10000 + ball * 1000 + ball * 100 + base * 10 + games;
    
    return total1 + total1 == total2;
}

void solve_cryptarithm(int *values, int index) {
    if (index == 10) { // Έχουμε βρει μια πιθανή λύση
        if (is_valid_solution(values)) {
            printf("A = %d, B = %d, E = %d, G = %d, L = %d, M = %d, S = %d\n",
                   values['A' - 'A'], values['B' - 'A'], values['E' - 'A'],
                   values['G' - 'A'], values['L' - 'A'], values['M' - 'A'],
                   values['S' - 'A']);
        }
        return;
    }

    for (int i = 0; i < 10; i++) {
        values[index] = i;
        solve_cryptarithm(values, index + 1);
    }
}

int main() {
    int values[10];
    solve_cryptarithm(values, 0);
    return 0;
}
