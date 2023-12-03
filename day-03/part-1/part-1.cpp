#include <fstream>
#include <iostream>
#include <set>
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

// Check if the given character is a symbol
bool is_symbol(char c) { return !is_number(c) && c != '.'; }

// Make a key from the given x and y
std::string make_key(int x, int y)
{
    return std::to_string(x) + "," + std::to_string(y);
}

// Found a number at x and y, get the full number by looking ahead
int get_full_number(std::vector<std::string> rows, std::string as, int x, int y)
{
    char c = at(rows, x + 1, y);
    if (!is_number(c)) return std::stoi(as);
    return get_full_number(rows, as + c, x + 1, y);
}

// Check if there is a symbol at the given position
bool is_symbol_at(std::set<std::string> symbols, std::vector<std::string> rows, int x, int y)
{
    std::string key = make_key(x, y);
    if (symbols.find(key) != symbols.end()) return true;
    
    bool is = is_symbol(at(rows, x, y));
    if (is) symbols.insert(key);
    return is;
}

// Check if there is a symbol adjacent to the given position
bool has_adjacent_symbol(std::set<std::string> symbols, std::vector<std::string> rows, int x, int y)
{
    for (int dx = -1; dx <= 1; dx++)
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            if (is_symbol_at(symbols, rows, x + dx, y + dy)) return true;
        }
    return false;
}

int main(int argc, char* argv[])
{
    std::ifstream file("input.txt");
    std::vector<std::string> rows;
    std::set<std::string> symbols;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line))
            rows.push_back(line);
    }

    int sum = 0;
    for (int y = 1; y < rows.size() + 1; y++) {
        for (int x = 1; x < rows[y - 1].length() + 1; x++) {
            char c = at(rows, x, y);

            if (is_symbol(c)) {
                symbols.insert(make_key(x, y));
            }
            else if (is_number(c)) {
                int full_number = get_full_number(rows, {c}, x, y);

                int number_length = std::to_string(full_number).length();
                for (int i = 0; i < number_length; i++) {
                    if (has_adjacent_symbol(symbols, rows, x + i, y)) {
                        sum += full_number;
                        break;
                    }
                }

                // skip ahead to the end of the number
                x += number_length - 1;
            }
        }
    }

    std::cout << sum << std::endl;

    return 0;
}
