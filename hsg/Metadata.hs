module Metadata where

import Config
import Util
import System.FilePath.Posix(takeBaseName)

type Metadata = [(String, String)]

-- It would probably better to use Data.Map instead of a tuple here
parseMetadata :: String -> Metadata
parseMetadata contents = map (uncurry (\a b -> (stripW a, stripW $ tail b)) . f)
        $ lines contents
          where
            f line = splitAt (getFirstOccOfChar line '=') line

-- Get value from Metadata, returning `ifFail` if the item can not be found.
getMetadataValue :: String -> Metadata -> String -> String
getMetadataValue value metadata ifFail
                                     | null l = ifFail
                                     | otherwise = snd $ head l where
                                        l = filter (\x -> fst x == value) metadata

parseSiteMap :: String -> [Metadata]
parseSiteMap sitemap = map parseMetadata $ splitBy "\n\n" sitemap

articleToPostsEntry :: Metadata -> String
articleToPostsEntry article = "<tr>\n" ++ "<td><a href=\"" ++ path ++ "\">" ++ title ++ "</a></td>\n<td>" ++ date ++ "</td></tr>\n" where
    title = getMetadataValue "title" article "No Title."
    date = getMetadataValue "date" article ""
    path = pathJoin articleDir $ ((takeBaseName $ getMetadataValue "path" article "?") ++ ".html")

sitemapToPosts :: [Metadata] -> String
sitemapToPosts sitemap = concat $ map articleToPostsEntry sitemap where
    f s = s
