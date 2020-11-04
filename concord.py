import re
import time

from dictionary_avl import Dictionary



def main():
    
    stopFile = open("stop_words.txt","r")
    stopWordDict = Dictionary()

    for line in stopFile:
        #stopWordDict[line.lower().strip("\n")] = []
        stopWordDict.insert(line.lower().strip("\n"))

    hwFile = open("data.txt","r")
    wordConcordanceDict = Dictionary()
    lineNum = 1

    for line in hwFile:
        wordList = re.split(" |\n|\.|\"|\)|\(", line)
        for word in wordList:
            word.strip(' ')
            if (len(word) != 0) and word.lower() not in stopWordDict:
                #if word in wordConcordanceDict:
                    #wordConcordanceDict[word].append(lineNum)
                begin = time.time()
                wordConcordanceDict.insert(word, lineNum)
                end = time.time()
                #else:
                    #wordConcordanceDict[word] = [lineNum]
        lineNum = lineNum + 1

    #for word in sorted(wordConcordanceDict):
        #print (word," : ",wordConcordanceDict[word])
    wordConcordanceDict.printd()

    print(f"Total runtime of the program is {end - begin}") 

if __name__ == "__main__":
    main()

 
    

