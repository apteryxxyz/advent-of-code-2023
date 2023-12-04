with open('input.txt', 'r') as file:
    rows = file.read().split('\n')

# Parse the line into winning numbers and your numbers
def parse_line(line):
    contents = line.split(': ')[1].split(' | ')
    winning_numbers = [num for num in contents[0].split(' ') if num]
    your_numbers = [num for num in contents[1].split(' ') if num]
    return winning_numbers, your_numbers

# Count how many winning numbers match your numbers
def get_match_count(winning_numbers, your_numbers):
    count = 0
    for y in your_numbers:
        for w in winning_numbers:
            if y == w:
                count += 1
                break
    return count

# Calculate the score based on the number of matches
def get_score(count):
    if count == 0:
        return 0

    score = 1
    for _ in range(count):
        score *= 2
    
    score = score / 2 if score > 1 else 1
    return score

# Main
sum = 0
for row in rows:
    winning_numbers, your_numbers = parse_line(row)
    count = get_match_count(winning_numbers, your_numbers)
    score = get_score(count)
    sum += score
print(sum) # Answer
