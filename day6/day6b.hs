module Main where

import Data.Char (isDigit)

-- Read character at position, space if out of bounds
charAt :: String -> Int -> Char
charAt s i = if i < length s then s !! i else ' '

-- Apply operator
applyOp :: Char -> [Integer] -> Integer
applyOp '+' nums = sum nums
applyOp '*' nums = product nums
applyOp _ nums = sum nums

-- Find block ranges: [(startCol, endCol, operator)]
findBlockRanges :: String -> [(Int, Int, Char)]
findBlockRanges opLine = 
    let opPositions = [(i, c) | (i, c) <- zip [0..] opLine, c `elem` "+*"]
        width = length opLine
        ranges = zipWith makeRange opPositions (map fst (tail opPositions) ++ [width])
    in ranges
  where
    makeRange (start, op) nextStart = (start, nextStart - 1, op)

-- For ONE character column, read bottom-to-top and form a number
-- The first digit read (bottom) is the ones place!
readColumnNumber :: [String] -> Int -> Maybe Integer
readColumnNumber rows col =
    let chars = [charAt row col | row <- reverse rows]  -- bottom to top
        digits = filter isDigit chars
    in if null digits 
       then Nothing 
       else Just (digitsToNumber digits)

-- Convert digits read bottom-up to a number (first digit = ones place)
digitsToNumber :: [Char] -> Integer
digitsToNumber digits = 
    sum [fromIntegral (fromEnum d - fromEnum '0') * (10 ^ i) 
        | (i, d) <- zip [0..] digits]

-- For a block, get all column numbers
extractNumbers :: [String] -> Int -> Int -> [Integer]
extractNumbers rows startCol endCol =
    [n | col <- [startCol..endCol], Just n <- [readColumnNumber rows col]]

-- Process all blocks and sum results
solve :: [String] -> String -> Integer
solve numberLines opLine =
    let blocks = findBlockRanges opLine
        results = [applyOp op (extractNumbers numberLines start end) 
                  | (start, end, op) <- blocks]
    in sum results

main :: IO ()
main = do
    file <- readFile "celephod.txt"
    let lns = lines file
        numberLines = take 4 lns
        operatorLine = lns !! 4
        result = solve numberLines operatorLine
    putStrLn $ "Day 6 Part B Result: " ++ show result