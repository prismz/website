Handling Time in Haskell
Jan 19, 2022

Haskell's method of handling time may be a bit confusing
for those first reading about it. I know I spent some time
trying to figure it out.

As a C programmer, you may be used to `strftime` and
its related structs and functions.

It seems like all the articles on the internet don't actually
explain how to use something similar to `strftime` in Haskell.

Getting the time is rather easy, but the functions have different
names than we may be used to. For example:

    import Data.Time

    getTime :: IO String
    getTime = do
        -- getZonedTime for current timezone, as
        -- getCurrentTime may be inaccurate
        now <- getZonedTime
        return $ formatTime defaultTimeLocale "%I:%M:%S" now

    main = do
        time <- getTime
        putStrLn time

The format used is the same as `strftime`, so you can simply read
the [manual page](https://linux.die.net/man/3/strftime) to learn 
how to format time the way you'd like.
