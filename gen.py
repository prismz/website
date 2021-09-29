import os
import time

HTML_HEADER = """<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>&_FTITLE</title>
    <link rel="stylesheet" href="/u/style.css">
</head>
"""

HTML_BOILER_MAINHEAD = """<!DOCTYPE html>
<html lang="en">
&_FCONTENTS
</html>"""

HTML_BOILER_BODY = """<body>
&_FBODY
</body>"""

def read_file(name):
    try:
        x = open(name, 'r')
        c = x.read()
        x.close()
        return c
    except:
        return None

def parse_article(filepath):
    c = read_file(filepath)
    if c is None:
        return None

    metadata = {}
    metadata['raw_body'] = c
    for line in c.splitlines():
        if line.strip().startswith('<h'):
            title = line.split('>', 1)[-1].split('</h')[0]
            metadata['title'] = title

        if line.strip().startswith('<!--META'):
            data = [i.strip()[:-3].strip() for i in line.strip().split('<!--META')]
            meta, data = data[-1].strip().split(' ', 1)
            metadata[meta.lower()] = data

    return metadata

def format_article(metadata, header, footer):
    if metadata == {}:
        print('no metadata passed to format_article')
        return

    raw = metadata['raw_body']
    title = metadata['title']
    ftitle = f'{title} - hasan zahra\'s website'
    rhh = HTML_HEADER.replace('&_FTITLE', ftitle)
    bb = HTML_BOILER_BODY.replace('&_FBODY', f'{header}\n{raw}\n{footer}')
    full = HTML_BOILER_MAINHEAD.replace('&_FCONTENTS', f'{rhh}{bb}')

    return full

if __name__ == '__main__':
    srcdir = 'c'
    dstdir = 'd'
    while 1:
        st = time.time()
        header = read_file('u/header.html')
        footer = read_file('u/footer.html')
        for a in os.listdir('c'):
            c = format_article(parse_article(f'c/{a}'), header, footer)
            f = open(f'{dstdir}/{a}', 'w+')
            f.write(c)
            f.close()

        et = time.time() - st
        print(f'completed in {round(et, 5)}')
        time.sleep(2)