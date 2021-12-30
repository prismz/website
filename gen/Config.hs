module Config where

-- All paths must end with a forward slash.

dest :: String
dest = "../articles/html/"

src :: String
src = "../articles/md/"

articleHrefRoot :: String
articleHrefRoot = "/articles/html/"

indexTemplatePath :: String
indexTemplatePath = "../indextemplate.html"

indexPath :: String
indexPath = "../index.html"

htmlBoilerPlatePath :: String
htmlBoilerPlatePath = "../boilerplate.html"