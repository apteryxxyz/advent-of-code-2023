#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// Get the character at the given position
char at(std::vector<std::string> rows, int x, int y) {
	if (y < 1 || y > rows.size()) return '.';
	if (x < 1 || x > rows[y - 1].length()) return '.';
	return rows[y - 1][x - 1];
}

// Check if the given character is a number
bool is_number(char c) { return c >= '0' && c <= '9'; }

// Check if the given character is a gear aka asterisk
bool is_gear(char c) { return c == '*'; }

// Found a number at x and y, get the full number by looking both ways
int get_full_number(std::vector<std::string> rows, std::string as, int x, int y)
{
    // Ensure we are start building the number from the start
    char previous = at(rows, x - 1, y);
    if (as == "" && is_number(previous)) return get_full_number(rows, as, x - 1, y);
    // Only passes if we are at the start of the number

    // Start grabing the number by looking ahead
    if (as == "") as = at(rows, x, y);
    char next = at(rows, x + 1, y);
    if (is_number(next)) return get_full_number(rows, as + next, x + 1, y);

    return std::stoi(as);
}

// Get the product of the two numbers surrounding the gear at x and y
int get_surrounding_numbers_product(std::vector<std::string> rows, int x, int y) {
	std::set<int> numbers;
	
	for (int dx = -1; dx <= 1; dx++)
		for (int dy = -1; dy <= 1; dy++) {
			if (dx == 0 && dy == 0) continue;
			
            char c = at(rows, x + dx, y + dy);
            if (is_number(c)) {
				int number = get_full_number(rows, "", x + dx, y + dy);
				if (number != -1) numbers.insert(number);
            }
		}

    // A gear must have at least two numbers surrounding it
    if (numbers.size() < 2) return 0;

    int product = 1;
    for (int num : numbers) product *= num;
    return product > 1 ? product : 0;
}

int main(int argc, char* argv[])
{
    std::ifstream file("input.txt");
    std::vector<std::string> rows;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line))
            rows.push_back(line);
    }

    int sum = 0;
    for (int y = 1; y < rows.size() + 1; y++) {
        for (int x = 1; x < rows[y - 1].length() + 1; x++) {
            char c = at(rows, x, y);

            if (is_gear(c)) {
                sum += get_surrounding_numbers_product(rows, x, y);
            }
        }
    }

    std::cout << sum << std::endl; // Answer
	
    return 0;
}
