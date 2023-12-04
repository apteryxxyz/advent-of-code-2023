local numbers = {
    ['one'] = 1,
    ['two'] = 2,
    ['three'] = 3,
    ['four'] = 4,
    ['five'] = 5,
    ['six'] = 6,
    ['seven'] = 7,
    ['eight'] = 8,
    ['nine'] = 9,
};

-- Replace words in a string with numbers
local function replaceWordsWithNumbers(input)
    -- Make a copy of the input, so we don't modify the original
    local result = input;

    local i = 0;
    local j = 0;

    while i < #input do
        i = i + 1;
        j = j + 1;

        local lastThree = string.sub(input, i - 2, i);
        local lastFour = string.sub(input, i - 3, i);
        local lastFive = string.sub(input, i - 4, i);

        local number = nil;
        if numbers[lastThree] then
            number = numbers[lastThree]
        elseif numbers[lastFour] then
            number = numbers[lastFour]
        elseif numbers[lastFive] then
            number = numbers[lastFive]
        end

        if number then
            -- Add the number after the word, e.g. seven7           
            result = string.sub(result, 1, j) .. number .. string.sub(result, j + 1);
            j = j + 1;
        end
    end

    return result;
end

-- Grab the first number it finds in a string
local function getFirstNumberInString(input)
    for i = 1, #input do
        local character = string.sub(input, i, i);
        local asNumber = tonumber(character, 10);

        if asNumber then
            return asNumber;
        end
    end

    return 0;
end

-- Sum of the first and last number in each line of a file
local function getSumOfEachLineInFile(filename)
    local result = 0;

    for line in io.lines(filename) do
        local newLine = replaceWordsWithNumbers(line);
        local first = getFirstNumberInString(newLine);
        local last = getFirstNumberInString(string.reverse(newLine));
        result = result + tonumber(first .. last);
    end

    return result;
end

-- Main
print(getSumOfEachLineInFile('input.txt')); -- Answer
