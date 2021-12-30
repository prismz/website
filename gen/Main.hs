module Main where
import System.Directory ( listDirectory )
import Data.Char ( ord )
import System.Environment ( getArgs )
import Control.Exception
import Data.Time
import Control.Concurrent

import Markdown
import Config

-- File basename, without extension.
basename :: String -> String 
basename path = removeEnding $ func $ splitWithStr "/" path where
    func l
         | null l = []
         | last l == "" = func $ init l
         | otherwise = last l

    removeEnding str
                   | last str == '.' = init str
                   | otherwise = removeEnding $ init str

-- Insert [str] into a string [template] where [keyword] is on it's own line.
insertIntoTemplate :: String -> String -> String -> String
insertIntoTemplate template keyword str = unlines $ map replaceLine $ lines template where
    replaceLine l
                | l == stripWhiteSpace keyword = str
                | otherwise = l

-- Get contents of HTML tag.
tagContents :: String -> String
tagContents str
              | null str = "?"
              | null s = "?"
              | null e = "?"
              | otherwise = take (head e - 1) $ drop (head s + 1) str where
                    s = [x | x <- [0..length str - 1], str !! x == '>']
                    e = [x | x <- [0..length (drop (h s) str) - 1], drop (h s) str !! x == '<']

                    h [] = 0
                    h l = head l

-- Get 
getTitle :: String -> String
getTitle article = s "<h0>No title.</h0>" $ map stripWhiteSpace $ lines article where
    s g l
        | null l = g
        | (length (head l) >= 3) && (take 2 (head l) == "<h") && (head l !! 2 `elem` "1234567890") && 
            (ord (head l !! 2) >= ord (g !! 2)) 
                = s (stripWhiteSpace $ head l) (tail l)
        | otherwise = s g (tail l)

genLinks :: [String] -> [String] -> String -> [String]
genLinks articlePaths articleContents template = zipWith (curry tupleToLink) 
        (map (tagContents . getTitle . insertIntoTemplate template "%CONTENTS%") articleContents) articlePaths

convertArticle :: String -> String -> IO()
convertArticle htmlBoilerPlate path = do
    contents <- readFile path
    let convertedContents = markdownToHTML contents
    let newpath = dest ++ basename path ++ ".html"
    let title = tagContents $ getTitle convertedContents
    let completedNoTitle = insertIntoTemplate htmlBoilerPlate "%CONTENTS%" convertedContents
    let completed = insertIntoTemplate completedNoTitle "%TITLE%" title
    writeFile newpath completed
    putStrLn $ path ++ " > " ++ newpath

srcToDest :: String -> String
srcToDest str = dest ++ basename str ++ ".html"

-- href comes second
tupleToLink :: (String, String) -> String 
tupleToLink t = "<a href=\"" ++ snd t ++ "\">" ++ fst t ++ "</a>"

stringArrayToHTMLList :: [String] -> String
stringArrayToHTMLList arr = addCloseOpenC "class=\"article_list\"" "ul" $ "\n" ++ listContents where
    listContents = unlines $ map (addCloseOpen "li") arr

convertIntoHref :: String -> String
convertIntoHref link = articleHrefRoot ++ basename link ++ ".html"

mainLoopAction :: IO()
mainLoopAction = do
    boilerplateContents <- readFile htmlBoilerPlatePath 
    indexTemplateContents <- readFile indexTemplatePath

    articleBasePaths <- listDirectory src
    let articlePaths = map (src ++ ) articleBasePaths
    let articleFixedPaths = map convertIntoHref articlePaths

    mapM_ (convertArticle boilerplateContents) articlePaths

    convertedContents <- mapM (readFile . srcToDest) articlePaths
    let articleList = stringArrayToHTMLList $ genLinks articleFixedPaths convertedContents boilerplateContents
    let indexContents = insertIntoTemplate indexTemplateContents "%ARTICLELIST%" articleList
    writeFile indexPath indexContents

main = do
    args <- getArgs
    cond args where
        cond a
             | null a = mainLoopAction
             | head a == "debug" = loopMain
             | otherwise = putStrLn "Invalid arguments."

        loopMain = do
            -- Naive measurement: https://chrisdone.com/posts/measuring-duration-in-haskell/
            start <- getCurrentTime

            mainLoopAction
            end <- getCurrentTime
            print (diffUTCTime end start)

            putStrLn "---"

            threadDelay 3000000

            loopMain
