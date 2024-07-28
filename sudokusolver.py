import codewars_test as test

def sudoku(puzzle):
    if check_complete(puzzle):
        return puzzle

    for i in range(9):
        for j in range(9):
            if puzzle[i][j] == 0:
                possibilities = check_options(puzzle, i, j)
                if len(possibilities) == 1:
                    puzzle[i][j] = next(iter(possibilities))
                    if check_complete(puzzle):
                        return puzzle
                elif len(possibilities) == 0:
                    raise Exception("Sorry, this sudoku is impossible to complete!")
                                 
    return sudoku(puzzle)

def check_complete(puzzle):
    for i in range(9):
        for j in range(9):
            if puzzle[i][j] == 0:
                return False
    return True      

def check_options(puzzle, row_num, col_num):
    row_options = check_row_for_num(puzzle, row_num)
    col_options = check_col_for_num(puzzle, col_num)
    grid_options = check_grid_for_num(puzzle, row_num, col_num)
    return row_options.intersection(col_options, grid_options)
        
def check_row_for_num(puzzle, row_num):
    options = set()
    for i in range(1, 10):
        present = False
        for j in range(9):
            if puzzle[row_num][j] == i:
                present = True
                continue
        if not present:
            options.add(i)
    
    return options

def check_col_for_num(puzzle, col_num):
    options = set()
    for i in range(1, 10):
        present = False
        for j in range(9):
            if puzzle[j][col_num] == i:
                present = True
                continue
        if not present:
            options.add(i)
    
    return options

def check_grid_for_num(puzzle, row_num, col_num):
    options = set()
    top_row = 0
    if row_num > 5:
        top_row = 6
    elif row_num > 2:
        top_row = 3
        
    left_col = 0
    if col_num > 5:
        left_col = 6
    elif col_num > 2:
        left_col = 3
        
    for i in range(1, 10):
        present = False
        for j in range(3):
            for k in range(3):
                if puzzle[top_row + j][left_col + k] == i:
                    present = True
                    continue       
        if not present:
            options.add(i)
    return options
  
test.describe('Sudoku')

puzzle = [[5,3,0,0,7,0,0,0,0],
          [6,0,0,1,9,5,0,0,0],
          [0,9,8,0,0,0,0,6,0],
          [8,0,0,0,6,0,0,0,3],
          [4,0,0,8,0,3,0,0,1],
          [7,0,0,0,2,0,0,0,6],
          [0,6,0,0,0,0,2,8,0],
          [0,0,0,4,1,9,0,0,5],
          [0,0,0,0,8,0,0,7,9]]

solution = [[5,3,4,6,7,8,9,1,2],
            [6,7,2,1,9,5,3,4,8],
            [1,9,8,3,4,2,5,6,7],
            [8,5,9,7,6,1,4,2,3],
            [4,2,6,8,5,3,7,9,1],
            [7,1,3,9,2,4,8,5,6],
            [9,6,1,5,3,7,2,8,4],
            [2,8,7,4,1,9,6,3,5],
            [3,4,5,2,8,6,1,7,9]]

test.it('Puzzle 1')
test.assert_equals(sudoku(puzzle), solution, "Incorrect solution for the following puzzle: " + str(puzzle));