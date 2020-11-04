import re
from dictionary_avl import Dictionary
#for binary
#from dictionary_binary import Dictionary

import time

def main():
    stopFile = open("stopwords.txt", "r")
    stopWordDict = Dictionary()

    for line in stopFile:
        stopWordDict.insert(line.lower().strip("\n"))

    hwFile = open("data2.txt", "r")
    wordConcordanceDict = Dictionary()
    lineNum = 1

    for line in hwFile:
        wordList = re.split("[^a-zA-Z0-9']+", line)
        for word in wordList:
            word.strip(' ')
            if (len(word) != 0) and word.lower() not in stopWordDict:
                wordConcordanceDict.insert(word, lineNum)
        lineNum = lineNum + 1

    wordConcordanceDict.printd()

    #time taken for search
    t_start = time.time()
    wordConcordanceDict.search("word")
    t_end = time.time()
    print(t_end - t_start)
if __name__ == "__main__":
    main()
