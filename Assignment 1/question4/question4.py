def solve_cryptarithmetic(puzzle, mapping, used_digits):
    if len(mapping) == len(puzzle):  # Όταν η αντιστοίχιση είναι πλήρης
        # Έλεγχος αν η αντιστοίχιση οδηγεί σε έγκυρη λύση
        if sum(mapping[c] for c in puzzle[:-1]) == mapping[puzzle[-1]]:
            return mapping  # Επιστρέφει την αντιστοίχιση
        else:
            return None  # Αν δεν είναι έγκυρη, επιστρέφει None
    else:
        next_char = next(filter(lambda x: x not in mapping, puzzle))  # Επιλογή του επόμενου χαρακτήρα που πρέπει να αντιστοιχηθεί
        for digit in range(10):  # Δοκιμή κάθε ψηφίου από 0 έως 9
            if digit not in used_digits:  # Έλεγχος αν το ψηφίο έχει ήδη χρησιμοποιηθεί
                mapping[next_char] = digit  # Αντιστοίχιση του επόμενου χαρακτήρα με το ψηφίο
                used_digits.add(digit)  # Προσθήκη του ψηφίου στα ψηφία που έχουν χρησιμοποιηθεί
                solution = solve_cryptarithmetic(puzzle, mapping, used_digits)  # Αναδρομική κλήση για τον επόμενο χαρακτήρα
                if solution is not None:  # Αν βρέθηκε λύση
                    return solution
                else:  # Αν δεν βρέθηκε λύση, επαναφορά των αλλαγών
                    del mapping[next_char]
                    used_digits.remove(digit)
        return None  # Αν δεν βρέθηκε λύση με κανένα ψηφίο, επιστρέφει None


def solve_puzzle(puzzle):
    mapping = {}  # Αρχικοποίηση αντιστοίχισης
    used_digits = set()  # Αρχικοποίηση συνόλου χρησιμοποιημένων ψηφίων
    chars = set(puzzle)  # Οι μοναδικοί χαρακτήρες στο παζλ
    chars.remove('+')  # Αφαίρεση του χαρακτήρα '+'
    chars.remove('=')  # Αφαίρεση του χαρακτήρα '='
    chars = list(chars)  # Μετατροπή του συνόλου σε λίστα για να διατηρήσουμε τη σειρά
    return solve_cryptarithmetic(puzzle, mapping, used_digits)


# Κύριο πρόγραμμα για δοκιμή
if __name__ == "__main__":
    puzzle = "BASE + BALL = GAMES"
    solution = solve_puzzle(puzzle)
    if solution:
        print("Solution found:")
        for char, digit in solution.items():
            print(f"{char}: {digit}")
    else:
        print("No solution found")
