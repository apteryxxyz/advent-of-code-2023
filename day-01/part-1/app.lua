
-- Grab the first number it finds in a string
local function getFirstNumberInString(input)
    for i = 1, #input do
        local character = input:sub(i, i);
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
        if line then
            local first = getFirstNumberInString(line);
            local last = getFirstNumberInString(line:reverse());

            result = result + tonumber(first .. last);
        end
    end
    return result;
end

-- Main
print(getSumOfEachLineInFile('input.txt')) -- Answer
