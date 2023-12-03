# Parses a game line into a directory of cube colours
def parse_line(line)
  header, contents = line.split(':')
  game = { "id" => header.split[1].to_i, "red" => 0, "green" => 0, "blue" => 0 }

  contents.split(';').each do |round|
    round.split(',').each do |item|
      count, colour = item.split

      # Only replace the colour if it is greator than the existing
      if count.to_i > game[colour]
        game[colour] = count.to_i
      end
    end
  end

  game
end

def is_possible(game, red = 12, green = 13, blue = 14)
  game['red'] <= red and game['green'] <= green and game['blue'] <= blue
end

# Main
sum = 0
File.readlines('input.txt', chomp: true).each do |line|
  game = parse_line(line)
  if is_possible(game)
    sum += game['id']
  end
end
puts sum # print the answer
