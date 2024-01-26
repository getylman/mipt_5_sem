class FileProcessor:
    def __init__(self, input_file, output_file):
        self.input_file = input_file
        self.output_file = output_file
        self.dot = '.'
        self.files = []
        self.symbol = '\n'

    def write(self):
        with open(self.output_file, 'w') as cout:
            for file in self.files:
                cout.write(file + self.symbol)

    def process_files(self):
        first = 'hlm'
        second = 'brhl'
        with open(self.input_file, 'r') as cin:
            for line in cin:
                for line in line.split():
                    if (self.dot not in line) or (line.startswith(self.dot)) or (not line.islower()):
                        continue
                    if line.endswith(self.dot):
                        line = line[:-1]
                        if self.dot not in line:
                            continue
                    if (line.rsplit(self.dot, 1)[1] == first) or (line.rsplit(self.dot, 1)[1] == second):
                        self.files.append(line)
        self.write()


processor = FileProcessor("input.txt", "output.txt")
processor.process_files()
