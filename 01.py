f = open('input.txt', 'r')
f1 = open('output.txt', 'w')
ans = ''

for line in f:
    if line == '\n':
        continue
    if '\n' in line:
        line.removesuffix('\n')
    arr = line.split(' ')
    for i in range(len(arr)):
        if (arr[i][len(arr[i]) - 1] == '.'):
            # print(arr[i])
            arr[i] = arr[i][:len(arr[i]) - 1]
            # print(arr[i])
        if arr[i].count('.') == 1 and len(arr[i]) >= 5 and arr[i][0] != '.' and ((arr[i].find('.hlm') == len(arr[i]) - 4) or (arr[i].find('.brhl') == len(arr[i]) - 5)):
            flag = True
            for j in arr[i]:
                if j == '.':
                    continue
                if ((ord(j) < ord('0') or ord(j) > ord('9')) and (ord(j) < ord('a') or ord(j) > ord('z'))):
                    flag = False
                    break
            if flag:
                ans += arr[i] + '\n'
f1.write(ans)
f.close()
f1.close()


'''
test
12:21:10 12/01/2022 127.0.0.1 error abc.hlm is broken.
12:21:10 12/01/2022 127.0.0.1 error abc.hlm.cpp is broken.
12:21:10 12/01/2022 127.0.0.1 error abc.brhl is broken.
12:21:10 12/01/2022 127.0.0.1 error abc.hlm aaa.hlm is broken.


'''

'''router = [0, 0, 0, 0]
col = [0, 0]

router[0] = int(input())
router[1] = int(input())
router[2] = int(input())
router[3] = int(input())

col[0] = int(input())
col[1] = int(input())

if ()

area = [0, 0, 2 * col[0], 2 * col[1]]

new_router = []
'''
'''
# o
line = input()
while True:
    if line == "":
        break
    arr = line.split(' ')
    for i in arr:
        if i.count('.') == 1 and len(i) >= 5 and i[0] != '.' and ((i.find('.hlm') == len(i) - 4) or (i.find('.brhl') == len(i) - 5)):
            flag = True
            for j in i:
                if j == '.':
                    continue
                if ((ord(j) < ord('0') or ord(j) > ord('9')) and (ord(j) < ord('a') or ord(j) > ord('z'))):
                    flag = False
                    break
            if flag:
                print(i)
    line = input()
'''

'''
a = int(input())
b = int(input())

cur = ""
cur_k = 0
i = input()
while i != "0":
    if len(cur) + len(i) + 1 <= a and cur_k + 1 <= b:
        cur += (' ' if cur != '' else '') + i
        cur_k += 1
    else:
        print(cur)
        cur = i
        cur_k = 1
    i = input()

print(cur)
'''
