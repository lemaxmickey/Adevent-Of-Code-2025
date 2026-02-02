module Main where
import System.IO
import Data.Char (isDigit, isSpace)
import Data.List (groupBy)

-- The idea is reading from the file into a 2-D grid
-- Problem statement: we have 4 rows of numbers and 1 row of operators (+, *)
-- The last row contains operators that are applied column-wise to the numbers above
-- For each column, apply the operator from the last row between consecutive numbers

-- Parse a row of space-separated numbers/operators into a list
parseRow :: String -> [String]
parseRow = filter (not . null) . groupBy (\a b -> not (isSpace a) && not (isSpace b))
         . filter (\c -> not (isSpace c) || c == ' ')

-- Parse the numbers from a row (keeping position info)
parseNumbers :: String -> [(Int, Integer)]
parseNumbers row = 
    let tokens = zip [0..] (words row)
    in [(pos, read num) | (pos, num) <- tokens, all isDigit num || (head num == '-' && all isDigit (tail num))]

-- Parse operators from the last row
parseOperators :: String -> [(Int, Char)]
parseOperators row = 
    let tokens = zip [0..] (words row)
    in [(pos, head op) | (pos, op) <- tokens, op == "+" || op == "*"]

-- Apply an operator to a list of numbers
applyOp :: Char -> [Integer] -> Integer
applyOp '+' nums = sum nums
applyOp '*' nums = product nums
applyOp _ nums = sum nums  -- default to sum

-- Get the value at a specific column position from parsed numbers
getNumberAtPos :: [(Int, Integer)] -> Int -> Maybe Integer
getNumberAtPos parsed pos = lookup pos parsed

-- Process all columns and compute the result
processColumns :: [[(Int, Integer)]] -> [(Int, Char)] -> Integer
processColumns numberRows operators = 
    sum [result | (pos, op) <- operators,
                  let nums = [n | row <- numberRows, Just n <- [getNumberAtPos row pos]],
                  not (null nums),
                  let result = applyOp op nums]

main :: IO()
main = do 
    file <- readFile "celephod.txt"
    let lns = lines file
        -- First 4 rows are numbers, last row is operators
        numberLines = take 4 lns
        operatorLine = lns !! 4
        -- Parse each number row
        parsedNumbers = map parseNumbers numberLines
        -- Parse operators
        parsedOperators = parseOperators operatorLine
        -- Process and compute result
        result = processColumns parsedNumbers parsedOperators
    putStrLn $ "Day 6 Part A Result: " ++ show result



    
    
        




    