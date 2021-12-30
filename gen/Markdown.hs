-- A simple markdown implementation in Haskell, not intended to comply with the standard.
-- I wrote this to practice Haskell. I know the code is very bad and unreadable.

-- PRIMITIVE VERSION - NO INLINE MARKDOWN ELEMENTS (links, bold).

module Markdown where

g :: Int -> Int
g i
    | i == 0 = 0
    | i >= 1 = 1
    | otherwise = 0

stripWhiteSpace :: String -> String
stripWhiteSpace = stripLW . stripTW where
    isWhiteSpace c = c `elem` ['\n', '\t']

    stripTW "" = ""
    stripTW str = if isWhiteSpace $ last str then stripTW $ init str else str

    stripLW "" = ""
    stripLW str = if isWhiteSpace $ head str then stripLW $ tail str else str

-- Add opener and closer of an HTML tag
addCloseOpen :: String -> String -> String
addCloseOpen tag str = "<" ++ tag ++ ">" ++ str ++ "</" ++ tag ++ ">"

-- Add opener and closer with custom attributes
addCloseOpenC :: String -> String -> String -> String
addCloseOpenC attrs tag str = "<" ++ tag ++ " " ++ attrs ++ ">" ++ str ++ "</" ++ tag ++ ">"

-- Add opener and closer of an HTML tag, but the opener at the first item of a tuple, and the closer at the second item.
addCloseOpenT :: String -> String -> (Int, Int) -> String
addCloseOpenT tag str i = p1 ++ mid ++ p2 where
    p1 = take (fst i) str ++ "<" ++ tag ++ ">"
    mid = tail $ take (snd i - fst i) $ drop (fst i) str
    p2 = "</" ++ tag ++ ">" ++ drop (length mid + length p1 - 1) str

-- Taken from StackOverflow, I have no clue how it works
splitWithStr :: Eq a => [a] -> [a] -> [[a]]
splitWithStr x y = func x y [[]]
    where
        func x [] z = reverse $ map reverse z
        func x (y:ys) (z:zs) = if take (length x) (y:ys) == x then
            func x (drop (length x) (y:ys)) ([]:(z:zs))
        else
            func x ys ((y:z):zs)

getBlocks :: String -> [String]
getBlocks = splitWithStr "\n\n"

-- Numbered list check
blockIsNList :: [String] -> Bool
blockIsNList = any ((== True) . isListLine) where
    isListLine str = take 3 str == "0. "

-- Format numbered list
fmtNList :: [String] -> String
fmtNList block = addCloseOpen "ol" $ "\n" ++ fmtInternals block where
    fmtInternals = concatMap ((++ "\n") . addCloseOpen "li" . stripWhiteSpace . drop 3)

-- Ordered list check
blockIsOList :: [String] -> Bool
blockIsOList = any ((== True) . isListLine) where
    isListLine str = head str `elem` "*-"

-- Format ordered list
fmtOList :: [String] -> String
fmtOList block = addCloseOpen "ul" $ "\n" ++ fmtInternals block where
    fmtInternals = concatMap ((++ "\n") . addCloseOpen "li" . stripWhiteSpace . drop 2)

-- Header check
blockIsHeader :: [String] -> Bool
blockIsHeader block = head (head block) == '#'

-- Format header
fmtHeader :: [String] -> String
fmtHeader block = addCloseOpen tag $ stripWhiteSpace $ drop (hType + 1) $ head block where
    tag = "h" ++ show hType
    hType = getHeaderType (head block) 0
    getHeaderType line t = if head line == '#' then getHeaderType (tail line) t + 1 else t

-- Quote check
blockIsQuote :: [String] -> Bool
blockIsQuote = any ((== True) . isQuoteLine) where
    isQuoteLine str = take 2 str == "> "

-- Format quote
fmtQuote :: [String] -> String
fmtQuote block = addCloseOpen "blockquote" ("\n" ++ contents ++ "\n") where
    contents = stripWhiteSpace $ concatMap ((++ "\n") . drop 2) block

-- Code check
blockIsCode :: [String] -> Bool
blockIsCode = any ((== True) . isCodeLine) where
    isCodeLine line = take 4 line == "    "

-- Format code
fmtCode :: [String] -> String
fmtCode block = addCloseOpen "pre" ("\n" ++ contents) where
    contents = concatMap ((++ "\n") . drop 4 . stripWhiteSpace) block

-- Format paragraph
fmtPg :: [String] -> String
fmtPg block = addCloseOpen "p" ("\n" ++ unlines block) ++ "\n"

-- Add d to each item of t.
tAdd :: Int -> (Int, Int) -> (Int, Int)
tAdd d t = (fst t + d, snd t + d)

-- Groups a list into a list of pairs. The list must have an even number of items.
-- e.g. listToPairs [1, 2, 3, 4] -> [(1, 2), (3, 4)]
listToPairs :: [Int] -> [(Int, Int)]
listToPairs [] = []
listToPairs l = (head l, l !! 1) : listToPairs (drop 2 l)

delIndices :: String -> [Int] -> String
delIndices str [] = str
delIndices str indices = delIndices r (map (subtract 1) (tail indices)) where
    r = strRem (head indices)
    strRem i = take i str ++ drop (i + 1) str

cleanEscapes :: String -> String
cleanEscapes str = delIndices str toRemove where
    toRemove = [x - g x | x <- [0..length str - 1], str !! x `elem` escs && str !! (x - g x) == '\\']
    escs = "*!#$%^&()[]\\"

fixIllegals :: String -> String 
fixIllegals = replace where
    replace ('<':xs) = "&lt;" ++ replace xs
    replace ('>':xs) = "&gt;" ++ replace xs
    replace (x:xs) = x : replace xs
    replace [] = []

fmt :: [String] -> String
fmt b  -- b is block
        | blockIsCode   b      = fmtPg $ lines $ fmtCode b
        | blockIsNList  b      = fmtPg $ lines $ fmtNList b
        | blockIsOList  b      = fmtPg $ lines $ fmtOList b
        | blockIsQuote  b      = fmtPg $ lines $ fmtQuote b
        | blockIsHeader b      = fmtHeader b
        | otherwise            = fmtPg b

markdownToHTML :: String -> String
markdownToHTML str = stripWhiteSpace $ 
    cleanEscapes $ concatMap ((++ "\n") . fmt . lines) (getBlocks str)