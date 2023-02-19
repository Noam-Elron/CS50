import re


def main():
    text = input("Enter text: ")
    # Sentences, words, letters.
    s = sentences(text)[:-1]  # Returns list of sentences
    w = words(s)  # Returns number of words
    l = chars(text)  # Returns number of characters

    print(calculate_grade(s, w, l))


def sentences(text) -> list:
    # Split only when theres either !?. * instead of + because otherwise it wont split last sentence and keeps its character.
    sentence_list = re.split('[!?.]\s*', text)
    return sentence_list


def words(sentences) -> int:
    word_count = 0
    for sentence in sentences:
        words_list = re.split('\s', sentence)  # Split list any time theres a whitespace character.
        # print(words_list)
        word_count += len(words_list)

    return word_count


def chars(text) -> int:
    char_list = re.split('[a-zA-Z]', text)
    # print(char_list)
    # print(len(char_list[:-1])) # Length of list containing all the whitespace(not including last punctuation mark because that wont be split)
    return len(char_list)-1


def calculate_grade(s, w, c) -> str:
    # Average number of letters per 100 words.
    avg_let_per_words = (c / w) * 100
    # Average number of sentences per 100 words.
    avg_sen_per_words = (len(s) / w) * 100
    level = 0.0588 * avg_let_per_words - 0.296 * avg_sen_per_words - 15.8

    if round(level) < 1:
        return "Before Grade 1"
    elif (round(level) >= 16):
        return "Grade 16+"

    return f"Grade {round(level)}"


if __name__ == "__main__":
    main()