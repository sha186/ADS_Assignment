import re
import sys
from dictionary_binary import Dictionary
def main():
	stopFile = open("stop_words.txt","r")
	stopWordDict = Dictionary()

	for line in stopFile:
		stopWordDict.insert(line.lower().strip("\n"))

	hwFile = open("data.txt","r")
	wordConDict = Dictionary()
	lineNum = 1

	for line in hwFile:
		wordList = re.split("[^a-zA-Z0-9']+", line)
		for word in wordList:
			word.strip(' ')
			if (len(word) != 0) and word.lower() not in stopWordDict:
				wordConDict.insert(word, lineNum)
		lineNum = lineNum + 1

	original_stdout = sys.stdout
	with open('output.txt', 'w') as f:
		sys.stdout = f
		wordConDict.printd()
		sys.stdout = original_stdout


if __name__ == "__main__":
	main()
