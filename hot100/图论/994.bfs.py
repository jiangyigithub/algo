from typing import List

class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        row, col, time = len(grid), len(grid[0]), 0
        directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
        queue = []
        # add the rotten orange to the queue
        for i in range(row):
            for j in range(col):
                if grid[i][j] == 2:
                    queue.append((i, j, time))
        # bfs
        while queue:
            i, j, time = queue.pop(0)
            for di, dj in directions:
                if 0 <= i + di < row and 0 <= j + dj < col and grid[i + di][j + dj] == 1:
                    grid[i + di][j + dj] = 2
                    queue.append((i + di, j + dj, time + 1))
        # if there are still fresh oranges, return -1
        for row in grid:
            if 1 in row: return -1

        return time

# Structure to hold test case information
class TestCase:
    def __init__(self, grid: List[List[int]], expected: int):
        self.grid = grid
        self.expected = expected

# Function to run test cases
def runTests():
    # Create test cases
    testCases = [
        TestCase([
            [2, 1, 1, 0],
            [1, 1, 0, 1],
            [0, 0, 1, 2]
        ], 2),
        
        TestCase([
            [2, 1, 1, 2, 1, 1],
            [1, 1, 2, 0, 1, 1],
            [1, 0, 0, 2, 0, 1],
            [2, 0, 1, 0, 1, 1],
            [1, 1, 1, 2, 1, 1]
        ], 3),
        
        TestCase([
            [2, 2, 2],
            [2, 2, 2],
            [2, 2, 2]
        ], 0),
        
        TestCase([
            [1, 1, 1, 1],
            [1, 1, 1, 1],
            [1, 1, 1, 1]
        ], -1),
        
        TestCase([
            [0]
        ], 0),
        
        TestCase([
            [2]
        ], 0)
    ]

    sol = Solution()
    for i, testCase in enumerate(testCases):
        # Make a deep copy of the grid to preserve the original grid for each test case
        grid_copy = [row[:] for row in testCase.grid]
        result = sol.orangesRotting(grid_copy)
        print(f"Test Case {i + 1}:")
        print(f"Grid:")
        for row in testCase.grid:
            print(row)
        print(f"Expected Result: {testCase.expected}")
        print(f"Actual Result: {result}")
        print(f"Test {'Passed' if result == testCase.expected else 'Failed'}\n")

if __name__ == "__main__":
    runTests()
