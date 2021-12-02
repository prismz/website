import os
import time
import sys
import string
import codecs

# all characters besides lowercase characters
NLOWER = [i for i in string.printable if i not in string.ascii_lowercase]

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
        x = open(name, 'r', encoding='utf8')
        c = x.read()
        x.close()
        return c
    except Exception as e:
        print(f'read: error {e}')
        return None

def parse_article(filepath):
    c = read_file(filepath)
    if c is None:
        return None

    metadata = {}
    have_content = False
    metadata['raw_body'] = ''
    metadata['sections'] = []
    metadata['content_list'] = '<br><ul class="section-list">\n    <li class="secl-header"><h4>content</h4></li>\n'
    metadata['content_added'] = 0
    for line in c.splitlines():
        # h4 is reserved for sections
        if line.strip().startswith('<h4>'):
            title = line.split('>', 1)[-1].split('</h')[0]
            r_id = title.lower()
            for c in NLOWER:
                r_id = r_id.strip(c)

            # create href id and add it to the content list
            r_id = r_id.replace(' ', '_').strip()
            n = f'<h4 id="{r_id}">{title}</h4>'
            metadata['raw_body'] += n + '\n'

            # append to numbered list of sections
            metadata['content_list'] += f'    <li class="secl-item">{metadata["content_added"] + 1}. <a href="#{r_id}">{title}</a></li>\n'
            metadata['content_added'] += 1
            have_content = True
            continue

        if line.strip().startswith('<h'):
            title = line.split('>', 1)[-1].split('</h')[0]
            metadata['title'] = title
            continue

        # parse comments with metadata
        if line.strip().startswith('<!--META'):
            data = [i.strip()[:-3].strip() for i in line.strip().split('<!--META')]
            meta, data = data[-1].strip().split(' ', 1)
            metadata[meta.lower()] = data

        metadata['raw_body'] += line + '\n'

    metadata['content_list'] += '</ul><br>\n\n'
    if have_content:
        metadata['raw_body'] = f'<h3>{metadata["title"]}</h3>\n' + metadata['content_list'] +  metadata['raw_body']
    else:
        metadata['raw_body'] = f'<h3>{metadata["title"]}</h3>\n' + metadata['raw_body']

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

global order
order = []
def main(debug=False):
    srcdir = 'c'
    dstdir = 'd'

    # removing old articles
    for i in os.listdir(dstdir):
        os.remove(f'{dstdir}/{i}')

    try:
        st = time.time()
        header = read_file('u/header.html')
        footer = read_file('u/footer.html')
        index_template = read_file('indextemplate.html')
        index_text = ''
        sections = {}
        for a in os.listdir(srcdir):
            parsed = parse_article(f'{srcdir}/{a}')
            c = format_article(parsed, header, footer)
            f = open(f'{dstdir}/{a}', 'w+', encoding='utf8')
            f.write(c)
            f.close()

            category = parsed['category']
            title = parsed['title']
            date = parsed['date']
            ctnt = f'<li title="{date}"><a href="{dstdir}/{a}">{title}</a></li>\n'
            try:
                sections[category] += ctnt
            except:
                sections[category] = ctnt

        for i in sections.keys():
            sections[i] = f'<h3>{i.replace("_", " ")}</h3>\n<ul>\n' + sections[i] + '\n</ul>'

        added = []
        global order
        if order == []:
            print('sections will be placed in the following order:')
            for index, i in enumerate(sections.keys()):
                print(f'{index + 1}. {i}')
                order.append(index)

            x = input('is this okay? [Y/numbers followed by spaces] ')
            if x.strip() == '' or x.lower().strip() == 'y':
                pass
            else:
                order = []
                order += [int(i) - 1 for i in x.strip().split(' ')]
                print(f'custom order: {order}')

        while len(added) != len(order):
            for i in order:
                for si, s in enumerate(sections.keys()):
                    if i == si:
                        added.append(si)
                        index_text += sections[s]
        
        index_text = index_template.replace('_ARTICLELIST_', index_text)
        f = open('index.html', 'w+', encoding='utf8')
        f.write(index_text)
        f.close()

        et = time.time() - st
        print(f'completed in {round(et, 5)}')
    except Exception as e:
        print(f'err in main(): {e}')

if __name__ == '__main__':
    if len(sys.argv) >= 2 and sys.argv[1] == 'debug':
        while 1:
            try:
                main(debug=True)
                time.sleep(2)
            except Exception as e:
                print(f'err in __name == \'__main__\': {e}')
    else:
        print('pass arg "debug" to constantly regenerate - (for debugging only)')
        main()
