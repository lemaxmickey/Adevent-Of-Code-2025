module Main where
import System.IO
import qualified Data.Vector.Unboxed as U
import Data.Array

-- The idea is readin from the file into a 2-D A(r,c)= (4, len(line))
-- Problem statement is that we have three lines or rather a grid = (4 , len(line))
-- Then the last grid !! 3 (o-indexed) so the idea is iterate the grid in that
-- we map the value of the last row index to the above cells .

readGrid :: String -> Array(Int, Int) Char
readGrid contents = 
    let lns = lines contents
        rows = length lns
        cols = if null lns then 0 else length (head lns)
    in array((0, 0), (rows -1, cols -1))
            [ ((r,c) ,(lns !! r) !! c) | r <- [0..rows -1],c <- [0..cols-1]]


main :: IO()
main = do 
    file <- readFile "celephod.txt"
    let grid = readGrid file 
    print grid



    
    
        




    