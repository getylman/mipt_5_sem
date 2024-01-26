from random import choice
from random import randint


class LabyrinthMap:
    # class of unit in labyrinth
    class Cell:
        def __init__(self, x, y):
            self.x, self.y = x, y
            self.walls = {'top': True, 'right': True,
                          'bottom': True, 'left': True}

        # function to gate the status of current cell
        def get_walls_status(self):
            return self.walls

        # function to break a wall by direction
        def brake_wall(self, direction):
            self.walls[direction] = False

    def _remove_walls(self, cur_x, cur_y, neighbor_x, neighbor_y):
        dx = cur_x - neighbor_x
        dy = cur_y - neighbor_y
        if dx == 1:
            self._cells[cur_x + cur_y * self._width].brake_wall('left')
            self._cells[neighbor_x + neighbor_y *
                        self._width].brake_wall('right')
        if dx == -1:
            self._cells[cur_x + cur_y * self._width].brake_wall('right')
            self._cells[neighbor_x + neighbor_y *
                        self._width].brake_wall('left')
        if dy == 1:
            self._cells[cur_x + cur_y * self._width].brake_wall('top')
            self._cells[neighbor_x + neighbor_y *
                        self._width].brake_wall('bottom')
        if dy == -1:
            self._cells[cur_x + cur_y * self._width].brake_wall('bottom')
            self._cells[neighbor_x + neighbor_y *
                        self._width].brake_wall('top')

    def _dfs_gen(self):
        # list of visited for dfs
        visited = [False] * (self._width * self._height)
        # stack
        stack = []

        def get_direction(x_cur, y_cur):
            def check_cell(x_cur, y_cur):
                if x_cur >= 0 and x_cur < self._width and y_cur >= 0 and y_cur < self._height:
                    return True
                return False
            neighbors = []
            # top
            if check_cell(x_cur, y_cur - 1) and not visited[x_cur + (y_cur - 1) * self._width]:
                neighbors.append([x_cur, y_cur - 1].copy())
            # bottom
            if check_cell(x_cur, y_cur + 1) and not visited[x_cur + (y_cur + 1) * self._width]:
                neighbors.append([x_cur, y_cur + 1].copy())
            # left
            if check_cell(x_cur - 1, y_cur) and not visited[(x_cur - 1) + y_cur * self._width]:
                neighbors.append([x_cur - 1, y_cur].copy())
            # right
            if check_cell(x_cur + 1, y_cur) and not visited[(x_cur + 1) + y_cur * self._width]:
                neighbors.append([x_cur + 1, y_cur].copy())
            return choice(neighbors).copy() if neighbors else False
        cur_cell = [0, 0]
        stack.append(cur_cell.copy())
        while stack:
            next_cell = get_direction(cur_cell[0], cur_cell[1])
            if next_cell:
                visited[next_cell[0] + next_cell[1] * self._width] = True
                self._remove_walls(cur_cell[0], cur_cell[1],
                                   next_cell[0], next_cell[1])
                stack.append(next_cell)
                cur_cell = next_cell.copy()
            else:
                cur_cell = stack.pop().copy()

    def _mst_gen(self):
        # using Prim algorithm
        # list of visited
        visited = [False] * (self._width * self._height)
        start_id = choice(range(self._width * self._height))
        cur_cell = [self._cells[start_id].x, self._cells[start_id].y]
        visited[start_id] = True
        neighbors = []

        def get_neighbors(x_cur, y_cur):
            def check_cell(x_cur, y_cur):
                if x_cur >= 0 and x_cur < self._width and y_cur >= 0 and y_cur < self._height:
                    return True
                return False
            # top
            if check_cell(x_cur, y_cur - 1) and not visited[x_cur + (y_cur - 1) * self._width]:
                neighbors.append(
                    [[x_cur, y_cur - 1], [x_cur, y_cur]].copy())
            # bottom
            if check_cell(x_cur, y_cur + 1) and not visited[x_cur + (y_cur + 1) * self._width]:
                neighbors.append(
                    [[x_cur, y_cur + 1], [x_cur, y_cur]].copy())
            # left
            if check_cell(x_cur - 1, y_cur) and not visited[(x_cur - 1) + y_cur * self._width]:
                neighbors.append(
                    [[x_cur - 1, y_cur], [x_cur, y_cur]].copy())
            # right
            if check_cell(x_cur + 1, y_cur) and not visited[(x_cur + 1) + y_cur * self._width]:
                neighbors.append(
                    [[x_cur + 1, y_cur], [x_cur, y_cur]].copy())
        get_neighbors(cur_cell[0], cur_cell[1])
        while neighbors:
            # getting a random neighbor index
            index = randint(0, len(neighbors) - 1)
            # current not merged neigbor
            next_cell = [neighbors[index][0][0], neighbors[index][0][1]]
            # merged neighbor of did not merged
            cur_cell = [neighbors[index][1][0], neighbors[index][1][1]]
            # remove it from list
            del neighbors[index]
            # if we visited this neighbor we skip it
            if visited[next_cell[0] + next_cell[1] * self._width]:
                continue
            # remove wall to merge neihbor
            self._remove_walls(cur_cell[0], cur_cell[1],
                               next_cell[0], next_cell[1])
            # mark as visited
            visited[next_cell[0] + next_cell[1] * self._width] = True
            # push new neigbours from new merged
            get_neighbors(next_cell[0], next_cell[1])

    def _file_gen(self, file_name):
        file = ''
        try:
            file = open(file_name, "r")
        except Exception:
            raise
        content = file.read()
        file.close()
        lines = []
        tmp_str = ''
        for i in content:
            if i == '\n':
                lines.append(tmp_str)
                tmp_str = ''
                continue
            tmp_str += i
        self._height = len(lines) // 2
        self._width = len(lines[0]) // 2

        self._cells = [self.Cell(col, row)
                       for row in range(self._height) for col in range(self._width)]
        for i in range(1, len(lines), 2):
            for j in range(1, len(lines[i]), 2):
                if lines[i][j + 1] == ' ':
                    self._remove_walls(j // 2, i // 2, j // 2 + 1, i // 2)
                if lines[i + 1][j] == ' ':
                    self._remove_walls(j // 2, i // 2, j // 2, i // 2 + 1)

    def __init__(self, arg1, arg2):
        self._cells = []
        self._height = 0
        self._width = 0
        if arg1 == 1:
            style = arg2[2]
            # styel -> style of creating map
            # our map
            self._cells = [self.Cell(col, row)
                           for row in range(arg2[1]) for col in range(arg2[0])]
            self._width = arg2[0]
            self._height = arg2[1]

            if style == 'dfs':
                self._dfs_gen()
            if style == 'mst':
                self._mst_gen()
        else:
            self._file_gen(arg2)

    def get_map(self):
        map_str = '-' * (2 * self._width + 1) + '\n'
        for i in range(self._height):
            map_str += '|'
            tmp = '|'
            for j in range(self._width):
                if not self._cells[j + i * self._width].get_walls_status()['right'] and j != self._width - 1:
                    map_str += '  '
                else:
                    map_str += ' |'
                if not self._cells[j + i * self._width].get_walls_status()['bottom'] and i != self._height - 1:
                    tmp += ' -'
                else:
                    tmp += '--'
            map_str += '\n' + (tmp if i != self._height -
                               1 else ('-' * (2 * self._width + 1))) + '\n'
        return map_str

    def walker(self, start_x, start_y, finish_x, finish_y):
        start_cell = [start_x, start_y]
        finish_cell = [finish_x, finish_y]
        walker_way = [False] * (self._width * self._height)
        visited = [False] * (self._width * self._height)
        cur_cell = start_cell.copy()
        stack = []

        stack.append(start_cell.copy())
        # visited[start_x + start_y * self._width] = True
        final_path = []

        def path_finder(x, y, path):
            def check_cell(x_cur, y_cur):
                if x_cur >= 0 and x_cur < self._width and y_cur >= 0 and y_cur < self._height:
                    return True
                return False
            if not check_cell(x, y) or visited[x + y * self._width]:
                return
            visited[x + y * self._width] = True
            if path[len(path) - 1] == finish_cell:
                final_path = path.copy()
                return
            if not self._cells[x + y * self._width].get_walls_status()['top']:
                new_path1 = path.copy()
                new_path1.append([x, y - 1])
                path_finder(x, y - 1, new_path1)
            if not self._cells[x + y * self._width].get_walls_status()['bottom']:
                new_path2 = path.copy()
                new_path2.append([x, y + 1])
                path_finder(x, y + 1, new_path2)
            if not self._cells[x + y * self._width].get_walls_status()['left']:
                new_path3 = path.copy()
                new_path3.append([x - 1, y])
                path_finder(x - 1, y, new_path3)
            if not self._cells[x + y * self._width].get_walls_status()['right']:
                new_path4 = path.copy()
                new_path4.append([x + 1, y])
                path_finder(x + 1, y, new_path4)

        path_finder(start_x, start_y, stack)
        print(len(final_path))

        for i in final_path:
            walker_way[i[0] + i[1] * self._width] = True

        map_str = '-' * (2 * self._width + 1) + '\n'
        for i in range(self._height):
            map_str += '|'
            tmp = '|'
            for j in range(self._width):
                if i == start_y and j == start_x:
                    if not self._cells[j + i * self._width].get_walls_status()['right'] and j != self._width - 1:
                        map_str += ('S*' if walker_way[j +
                                    i * self._width] else 'S ')
                    else:
                        map_str += 'S|'
                elif i == finish_y and j == finish_x:
                    if not self._cells[j + i * self._width].get_walls_status()['right'] and j != self._width - 1:
                        map_str += ('F*' if walker_way[j +
                                    i * self._width] else 'F ')
                    else:
                        map_str += 'F|'
                else:
                    if not self._cells[j + i * self._width].get_walls_status()['right'] and j != self._width - 1:
                        map_str += ('**' if walker_way[j +
                                    i * self._width] else '  ')
                    else:
                        map_str += ' |'
                if not self._cells[j + i * self._width].get_walls_status()['bottom'] and i != self._height - 1:
                    tmp += ('*' if walker_way[j +
                            i * self._width] else ' ') + '-'
                else:
                    tmp += '--'
            map_str += '\n' + (tmp if i != self._height -
                               1 else ('-' * (2 * self._width + 1))) + '\n'

        return map_str
