from collections import deque
import time
import string
import psutil


def generate_adjacent_words(word, word_set):
    adjacent_words = []
    for i in range(len(word)):
        for letter in string.ascii_lowercase:
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
        print("The word was not found in the dictionary")
        return None

    queue = deque([[start]])
    visited = set([start])

    while queue:
        way = queue.popleft()
        current_word = way[-1]

        if current_word == end:
            print(f"{start_word} ---> {end_word}:")
            print("Chain:", end='')
            for step in way:
                print(f" -> {step}", end='')
            return way

        for neighbor in adjacency_list[current_word]:
            if neighbor not in visited:
                visited.add(neighbor)
                new_way = list(way)
                new_way.append(neighbor)
                queue.append(new_way)
    print("The chain does not exist")
    return None


process = psutil.Process()
start_word = input()
end_word = input()
start_time = time.time()
file = open("english_words.txt", "r", encoding="utf-8")
word_list = file.read()
words = word_list.split()
adj_list = build_adjacency_list(words)
chain = bfs(adj_list, start_word, end_word)
file.close()
end_time = time.time()
execution_time = end_time - start_time
print('\n')
print(f"Program execution time: {execution_time} seconds")
print(f"Memory consumption: {process.memory_info().rss} bytes")


