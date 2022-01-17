module Converter where

import Metadata
import Config
import Util

import System.Directory
import System.FilePath.Posix(takeBaseName)
import System.Process

convertArticle :: Metadata -> IO()
convertArticle metadata = do
    let articlePath = pathJoin articleDir (getMetadataValue "path" metadata "?")

    articleMarkdown <- readFile articlePath 
    articleTemplate <- readFile articleTemplatePath 
    
    let workFile = pathJoin articleDir "work"
    let dest = pathJoin articleDir ((takeBaseName articlePath) ++ ".html")
    let command = replaceStrT converterCommand [
                                                 ("%SRC%", articlePath)
                                               , ("%DEST%", workFile)]

    callCommand command
    
    let title = getMetadataValue "title" metadata "No Title"
    let date = getMetadataValue "date" metadata ""
    contents <- readFile workFile 
    let footer = "" 
    let header = ""
    
    let dict = [
               ("%TITLE%", title)
               , ("%DATE%", date)
               , ("%SITENAME%", siteName)
               , ("%STYLEPATH%", stylePath)
               , ("%HEADER%", header)
               , ("%FOOTER%", footer)
               , ("%CONTENTS%", contents)]

    let formatted = replaceStrT articleTemplate dict
    writeFile dest formatted
    removeFile workFile

    putStrLn $ "[" ++ title ++ "] - " ++ articlePath ++ " > " ++ dest

formatPostsPage :: String -> IO()
formatPostsPage posts = do
   postsTemplate <- readFile postsTemplatePath 
   let formatted = replaceStrT postsTemplate [
                                               ("%ARTICLELIST%", posts)
                                             , ("%SITENAME%", siteName)
                                             , ("%STYLEPATH%", stylePath)]
   writeFile postsPath formatted

formatIndexPage :: IO()
formatIndexPage = do
    indexTemplate <- readFile indexTemplatePath
    let formatted = replaceStrT indexTemplate [
                                                ("%SITENAME%", siteName)
                                              , ("%STYLEPATH%", stylePath)]

    writeFile indexPath formatted
