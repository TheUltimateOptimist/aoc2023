import sys

YEAR = "2023"

def read():
    folderName = sys.argv[0].split("/")[-2]
    day = str(int(folderName))
    filePath = f"{folderName}/test.txt"
    if (len(sys.argv) <= 1):
        filePath = f"{folderName}/adventofcode.com_{YEAR}_day_{day}_input.txt"
    with open(filePath, "r", encoding="ascii") as file:
        return file.read().strip()