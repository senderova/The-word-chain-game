from collections import deque
import time

russian_alphabet = "йцукенгшщзхъфывапролджэячсмитьбю"


def generate_adjacent_words(word, word_set):
    adjacent_words = []
    for i in range(len(word)):
        for letter in russian_alphabet:
            if letter != word[i]:
                new_word = word[:i] + letter + word[i + 1:]
                if new_word in word_set:
                    adjacent_words.append(new_word)
    return adjacent_words


def build_adjacency_list(words_list):
    word_set = set(words_list)
    adjacency_list = {word: generate_adjacent_words(word, word_set) for word in words}
    return adjacency_list


def bfs(adjacency_list, start, end):
    if start not in adjacency_list or end not in adjacency_list:
        print("Слово не найдено в словаре")
        return None

    queue = deque([[start]])
    visited = set([start])

    while queue:
        way = queue.popleft()
        current_word = way[-1]

        if current_word == end:
            print(f"{start_word} ---> {end_word}:")
            print("Цепочка:", end='')
            for step in way:
                print(f" -> {step}", end='')
            return way

        for neighbor in adjacency_list[current_word]:
            if neighbor not in visited:
                visited.add(neighbor)
                new_way = list(way)
                new_way.append(neighbor)
                queue.append(new_way)
    print("Цепочки не существует")
    return None


print("Добро пожаловать в игру Из мухи в слона!")
print("Программа строит цепочку из слов, от начального к конечному, заменяя на каждом шаге по одной букве")
print("Используются четырехбуквенные русские слова")
print("Введите начальное слово цепочки (русское слово из 4 букв):")
start_word = input()
print("Введите конечное слово цепочки (русское слово из 4 букв):")
end_word = input()
start_time = time.time()
file = open("words.txt", "r", encoding="utf-8")
word_list = file.read()
words = word_list.split()
adj_list = build_adjacency_list(words)
chain = bfs(adj_list, start_word, end_word)
file.close()
end_time = time.time()
execution_time = end_time - start_time
print('\n')
print(f"Время выполнения программы: {execution_time} секунд")
