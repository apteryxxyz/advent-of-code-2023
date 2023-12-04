# Parses a game line into a directory of cube colours
def parse_line(line)
  header, contents = line.split(':')
  game = { "red" => 0, "green" => 0, "blue" => 0 }

  contents.split(';').each do |round|
    round.split(',').each do |item|
      count, colour = item.split

      # Only replace the colour if it is greater than the existing
      if count.to_i > game[colour]
        game[colour] = count.to_i
      end
    end
  end

  game['id'] = header.split[1].to_i
  game['product'] = game['red'] * game['green'] * game['blue']

  game
end

# Main
sum = 0
File.readlines('input.txt', chomp: true).each do |line|
  game = parse_line(line)
  # Part 2 just consisted of getting the product of all the cudes and summing, easy
  sum += game['product']
end
puts sum # Answer
