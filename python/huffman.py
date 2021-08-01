from heapq import heapify, heappop, heappush

class Node:
    def __init__(self, ch, freq, left = None, right = None):
        self.ch = ch
        self.freq = freq
        self.left = left
        self.right = right

    def __lt__(self, other):
        return self.freq < other.freq

    def __str__(self) -> str:
        s = ""
        if self.ch is not None:
            s += f" Letter: {self.ch}"
        if self.left is not None:
            s += f"  0: {self.left}"
        if self.right is not None:
            s += f"  1: {self.right}"
        return s + "\n"

def printHuffmanCodes(tree, bits:str = ""):
    current = tree
    if current is None:
        return
    if current.ch is not None:
        print(f"{current.ch} = {bits}")
    if current.left is not None:
        printHuffmanCodes(current.left, bits + "1")
    if current.right is not None:
        printHuffmanCodes(current.right, bits + "0")

def getHuffmanTree(text:str):
    if len(text) == 0:
        return None
    freq = {ch: text.count(ch) for ch in set(text)}
    pq = [Node(k, v) for k, v in freq.items()]
    heapify(pq)
    while len(pq) > 1:
        left, right = heappop(pq), heappop(pq)
        newFreq = left.freq + right.freq
        heappush(pq, Node(None, newFreq, left, right))
    root = pq[0]
    return root

def main():
    msg = "ADBADEDBBDD"
    print(msg)
    tree = getHuffmanTree(msg)
    printHuffmanCodes(tree)

    msg = "hello world"
    print(msg)
    tree = getHuffmanTree(msg)
    printHuffmanCodes(tree)

if __name__ == "__main__":
    main()
