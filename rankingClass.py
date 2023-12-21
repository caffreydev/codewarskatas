import math
# TODO: create the User class
# it must support rank, progress, and the inc_progress(rank) method
class User:
    def __init__(self):
        self.rank = -8
        self.progress = 0
    
    def inc_progress(self, level):
        if level == 0 or level < -8 or level > 8 or level != math.floor(level):
            raise Exception("Fool, this rank is wrong")
        
        
        if self.rank == 8:
            return
        
        d = level - self.rank
        if level > 0 and self.rank < 0:
            d -= 1
        elif self.rank > 0 and level < 0:
            d += 1
        
        if d < -1:
            return
        elif d == -1:
            points = 1
        elif d == 0:
            points = 3
        else:
            points = 10 * d ** 2
        
        progressUpdated = self.progress + points
        
        while progressUpdated >= 100:
            if self.rank == -1:
                self.rank = 1
            else:
                self.rank += 1
            progressUpdated -= 100
        if self.rank >= 8:
            self.rank = 8
            self.progress = 0
            return
        self.progress = progressUpdated