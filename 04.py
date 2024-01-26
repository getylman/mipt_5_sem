def get_files(src):
    masks = ['hlm', 'brhl']
    res = []
    with open(src, 'r') as lines:
        for line in lines:
            for word in line.split():
                if word.endswith('.'):
                    word = word[:-1]
                if ('.' not in word) or (word.startswith('.')) or (not word.islower()):
                    continue
                if word.rsplit('.', 1)[1] == masks[0] or word.rsplit('.', 1)[1] == masks[1]:
                    res.append(word)
    return res


def make_magic(src, dst):
    files = get_files(src)
    with open(dst, 'w') as ostream:
        for file_name in files:
            ostream.write(file_name + '\n')


make_magic('input.txt', 'output.txt')
