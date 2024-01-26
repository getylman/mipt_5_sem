import re


def find_file_names(line):
    file_names = re.findall(r'\b[a-z0-9]+\.[a-z]{3}\b', line)
    return file_names


input_file = 'input.txt'
output_file = 'output.txt'

# Читаем файл input.txt
with open(input_file, 'r') as file:
    lines = file.readlines()

# Ищем имена файлов в каждой строке
file_names = []
for line in lines:
    found_names = find_file_names(line)
    file_names.extend(found_names)

# Записываем найденные имена в файл output.txt
with open(output_file, 'w') as file:
    for name in file_names:
        file.write(name + '\n')
