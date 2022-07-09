Never pay to download media again
Jan 19, 2022

When you find something you'd like to download, websites will either 
ask you to pay, make an account, or both. Some sites do not give
you the option to download at all.

Enter [youtube-dl](https://youtube-dl.org/) and its forked
version [yt-dlp](https://github.com/yt-dlp/yt-dlp).

Despite the name, both programs can download from many different
websites. The complete list of supported sites can be found [here](https://gist.github.com/sky-y/1fac37a3c9db71e6af78).

These programs are available in the repos for most distributions, 
and you can easily download them on other platforms.

# What's the difference?

`yt-dlp` is slightly less popular than youtube-dl,
so you may have a harder time finding it in your repos.

If you can get it, use `yt-dlp`, otherwise, use `youtube-dl`.

`yt-dlp` is "A youtube-dl fork with additional features and fixes".

I've noticed that bugs tend to be fixed faster in `yt-dlp`.

Despite these differences, either one works for downloading media.

# How to use it

The best place to read about all the options is the
manual page ([youtube-dl](https://www.mankier.com/1/youtube-dl),
[yt-dlp](https://www.mankier.com/1/yt-dlp)). Some basic examples are
listed below. You may need to replace `youtube-dl` with `yt-dlp` depending on which
one you're using.

To extract audio, use the following command:

    youtube-dl -x --audio-format mp3 [url]

To download video, just run the command with the url as the argument. For example:

    youtube-dl [url]
