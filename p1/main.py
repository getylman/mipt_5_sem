import user_interface

a = user_interface.LabyrinthUser()


def set_args():
    print('First argument can be only 1 or 2.')
    print('1 - and 3 more arguments width, height and style (\'mst\' or \'dfs\')')
    print('2 - and 1 more argument file name from were you want take labbyrinth')
    arg1 = int(input('Input first argument: '))
    arg2 = []
    if arg1 == 1:
        arg2 = [0, 0, '']
        arg2[0] = int(input('Input width of labyrinth: '))
        arg2[1] = int(input('Input height of labyrinth: '))
        arg2[2] = (
            input('Input style (only \'mst\' or \'dfs\') of labyrinth: '))
    elif arg1 == 2:
        arg2 = input(
            'Input name of file from were you want import labyrinth: ')
    else:
        print('I told you choose 1 or 2')
        exit()
    a.create_labyrinth(arg1, arg2)


print('Hello, user. You have ability to create a labyrinth.')

arg1 = 0
arg2 = []
set_args()

while True:
    print('What you want?')
    print('1 - print labyrinth')
    print('2 - save labyrinth')
    print('3 - generate labyrinth')
    print('4 - set start and finish points')
    print('5 - print labyrinth with solution')
    print('6 - finish program')
    arg3 = int(input('Input argument: '))
    if arg3 == 1:
        a.print_labyrinth()
    elif arg3 == 2:
        arg4 = input('Input name file to save: ')
        a.save_labyrinth(arg4)
    elif arg3 == 3:
        set_args()
    elif arg3 == 4:
        arg4s = []
        print('Input 4 integers in one line')
        arg4 = map(int, input().split())
    elif arg3 == 5:
        a.solve_the_labyrinth()
    elif arg3 == 6:
        print('Program finished!')
        break
    else:
        print('I told you choose 1, 2, 3, 4, 5 or 6!')
        exit()
