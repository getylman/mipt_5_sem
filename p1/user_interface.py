import labyrinth_map


class LabyrinthUser:
    def __init__(self):
        pass

    def create_labyrinth(self, arg1, arg2):
        self._labyrinth = labyrinth_map.LabyrinthMap(arg1, arg2)
        self._start_x = 0
        self._start_y = 0
        self._finish_x = self._labyrinth._width - 1
        self._finish_y = self._labyrinth._height - 1

    def print_labyrinth(self):
        print(self._labyrinth.get_map())

    def save_labyrinth(self, file_name):
        file = ''
        try:
            file = open(file_name, "w")
        except Exception:
            raise
        file.write(self._labyrinth.get_map())
        file.close()

    def set_start_and_finish(self, start_x, start_y, finish_x, finish_y):
        self._start_x = start_x
        self._start_y = start_y
        self._finish_x = finish_x
        self._finish_y = finish_y

    def solve_the_labyrinth(self):
        print(self._labyrinth.walker(self._start_x,
              self._start_y, self._finish_x, self._finish_y))
