module Main where

import Util
import Config
import Metadata
import Converter

import System.Directory
import Data.List

main = do
    sitemapRaw <- readFile "../articles/sitemap"
    let sitemap = parseSiteMap $ stripW sitemapRaw

    mapM_ convertArticle sitemap

    let posts = sitemapToPosts sitemap
    formatPostsPage posts

    formatIndexPage
