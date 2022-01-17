module Util where

import Data.Char

stripW :: String -> String
stripW = stripL . stripT where
    stripL str
             | str == [] = []
             | isSpace $ head str = stripL $ tail str
             | otherwise = str

    stripT str
             | str == [] = []
             | isSpace $ last str = stripT $ init str
             | otherwise = str

-- Get first occurrence of Char c
getFirstOccOfChar :: String -> Char -> Int
getFirstOccOfChar "" _ = -1
getFirstOccOfChar str c = func str c 0 where
    func str c i
               | head str == c = i
               | otherwise = func (tail str) c (i + 1)

replaceStr :: String -> String -> String -> String
replaceStr str tr w
    | v == -1 = str
    | otherwise = replaceStr ((fst t) ++ w ++ (drop (length tr) $ snd t)) tr w where
        t = splitAt v str
        v = func str tr 0
        l = length str
        func str tr i
                    | i >= l = -1 
                    | take (length tr) str == tr = i
                    | otherwise = func (tail str) tr (i + 1)

-- Replaces multiple strings. e.g.
-- replaceStrT "abc||def$$ghi" [("||", "!!"), ("$$", "%%")]
--    -> "abc!!def%%ghi"
replaceStrT :: String -> [(String, String)] -> String
replaceStrT str [] = str
replaceStrT str csps = replaceStrT (replaceStr str f s) (tail csps) where
    f = fst $ head csps
    s = snd $ head csps

endsWith :: String -> String -> Bool
endsWith w str = take (length w) (reverse str) == (reverse w) 

pathJoin :: String -> String -> String
pathJoin p1 p2 = p1 ++ d ++ p2 where
    d = if last p1 == '/' || head p2 == '/' then "" else "/"

splitBy :: String -> String -> [String]
splitBy delim str = func str delim [[]] where
    func "" _ l = l
    func str d l
               | take (length d) str == d = func (drop (length d) str) d (l ++ [""])
               | otherwise = func (tail str) d (init l ++ [(last l ++ [head str])])

encloseInHtml :: String -> String -> String
encloseInHtml tag str = "<" ++ tag ++ ">" ++ str ++ "</" ++ tag ++ ">"
