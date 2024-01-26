class Cell:
    def __init__(self, x, y):
        self.x, self.y = x, y
        self.walls = {'top': True, 'right': True, 'bottom': True, 'left': True}

    # function to gate the status of current cell
    def get_walls_status(self):
        return self.walls.copy()

    # function to break a wall by direction
    def brake_wall(self, direction):
        self.walls[direction] = False
