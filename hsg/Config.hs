module Config where

import Util
-- To combine paths, use function `pathJoin`.

-- General Info
siteName :: String
siteName = "Hasan Zahra's Website"

-- Final paths 
postsPath :: String
postsPath = "../posts.html"

indexPath :: String
indexPath = "../index.html"

-- Template paths
templateDir :: String
templateDir = "../templates"

postsTemplatePath :: String
postsTemplatePath = pathJoin templateDir "posts.html" 

indexTemplatePath :: String
indexTemplatePath = pathJoin templateDir "index.html"

articleTemplatePath :: String
articleTemplatePath = pathJoin templateDir  "article.html"

footerPath :: String
footerPath = pathJoin templateDir "footer.html"

-- Other paths
articleDir :: String
articleDir = "../articles"

stylePath :: String
stylePath = "/style.css"

-- Conversion options

converterCommand :: String
converterCommand = "lowdown %SRC% > %DEST%"
