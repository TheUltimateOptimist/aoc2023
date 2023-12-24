from  heapq import heappop, heappush
from util import read

grid = read().split("\n")

for i in range(len(grid)):
    ints = []
    for j in range(len(grid[0])):
        ints.append(int(grid[i][j]))
    grid[i] = ints 

visited = set()
pq = [(0, 0, 0, 0, 0, 0)]

while pq:
    loss, row, col, drow, dcol, n = heappop(pq) 
    if row == len(grid) - 1 and col == len(grid[0]) - 1:
        print(f"result = {loss}")
        break

    if (row, col, drow, dcol, n) in visited:
        continue
    
    visited.add((row, col, drow, dcol, n))

    for ndrow, ndcol in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
        nn = 1
        if ndrow == -drow and ndcol == -dcol:
            continue
        if ndrow == drow and ndcol == dcol:
            if n >= 3:
                continue
            nn = n + 1
        nrow = row + ndrow
        ncol = col + ndcol
        if nrow >= 0 and nrow < len(grid) and ncol >= 0 and ncol < len(grid[0]):
            heappush(pq, (loss + grid[nrow][ncol], nrow, ncol, ndrow, ndcol, nn))