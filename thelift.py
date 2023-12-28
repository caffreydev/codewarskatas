import codewars_test as test

# https://www.codewars.com/kata/58905bfa1decb981da00009e/train/python

class Dinglemouse(object):
    floor = 0
    queues = []
    capacity = 0
    height = 0
    lift_occupants = []
    floors_visited = [0]
    direction = 'up'

    def __init__(self, queues, capacity):
        queues_list = []
        for queue in queues:
            queues_list.append(list(queue))
        self.queues = queues_list
        self.capacity = capacity
        self.height = len(queues)
        self.floor = 0
        self.lift_occupants = []
        self.floors_visited = [0]
        self.direction = 'up'

    def check_complete(self):
        if len(self.lift_occupants): return False
        for queue in self.queues:
            if len(queue): return False
        return True
    
    def update_direction(self):
        if self.direction == 'up':
            if self.floor == self.height - 1:
                self.direction == 'down'
                return
            for occupant in self.lift_occupants:
                if occupant > self.floor:
                    return
            for i in range(self.floor + 1, self.height - 1):
                if len(self.queues[i]): 
                    return
            self.direction == 'down'
            return
        if self.direction == 'down':
            if self.floor == 0:
                self.direction == 'up'
                return
            for occupant in self.lift_occupants:
                if occupant < self.floor:
                    return
            for i in range(self.floor):
                if len(self.queues[i]): 
                    return
            self.direction == 'up'
            return
                
    def empty_out(self):
        index = 0
        n = len(self.lift_occupants)
        while index < n:
            if self.lift_occupants[index] == self.floor:
                del self.lift_occupants[index]
                n -= 1
            else:
                index += 1
                
    def fill_up(self):
        queue = self.queues[self.floor]
        index = 0
        while (len(self.lift_occupants) < self.capacity and len(queue) and index < len(queue)):
            if self.direction == 'up':
                if queue[index] > self.floor:
                    self.lift_occupants.append(queue[index])
                    del queue[index]
                    index -= 1
            if self.direction == 'down':
                if queue[index] < self.floor:
                    self.lift_occupants.append(queue[index])
                    del queue[index]
                    index -= 1
            index += 1
    
    def update_floor(self, floor):
        self.floor = floor
        self.floors_visited.append(floor)
    def next_floor(self):
        floor_to_check = self.floor
        if self.direction == 'up':
            while floor_to_check < self.height - 1:
                floor_to_check += 1
                if floor_to_check in self.lift_occupants:
                    self.update_floor(floor_to_check)
                    return
                queue = self.queues[floor_to_check]

                for i in range(floor_to_check + 1, self.height):
                    if i in queue:
                        self.update_floor(floor_to_check)
                        return
            for i in range(self.height - 1, self.floor, -1):
                if len(self.queues[i]):
                    self.update_floor(i)
                    return 
        if self.direction == 'down':
            while floor_to_check > 0:
                floor_to_check -= 1
                if floor_to_check in self.lift_occupants:
                    self.update_floor(floor_to_check)
                    return
                queue = self.queues[floor_to_check]
                for i in range(floor_to_check - 1, -1, -1):
                    if i in queue:
                        self.update_floor(floor_to_check)
                        return
            for i in range(self.floor):
                if len(self.queues[i]):
                    self.update_floor(i)
                    return 
        self.direction = 'up' if self.direction == 'down' else 'down'
        self.fill_up()
        self.next_floor()

        
        
    def theLift(self):
        while True:
            self.empty_out()
            if self.check_complete():
                break
            self.fill_up()
            self.update_direction()
            self.fill_up()
            self.next_floor()

        if self.floor:
            self.floors_visited.append(0)
        return self.floors_visited                 
                    
        
        
@test.describe("The Lift")
def the_lift():
    
    @test.it("Example")
    def example():
        
        # Floors:    G     1      2        3     4      5      6         Answers:
        tests = [[ ( (),   (),    (5,5,5), (),   (),    (),    () ),     [0, 2, 5, 0]          ],
                 [ ( (),   (),    (1,1),   (),   (),    (),    () ),     [0, 2, 1, 0]          ],
                 [ ( (),   (3,),  (4,),    (),   (5,),  (),    () ),     [0, 1, 2, 3, 4, 5, 0] ],
                 [ ( (),   (0,),  (),      (),   (2,),  (3,),  () ),     [0, 5, 4, 3, 2, 1, 0] ]]
          
        for queues, answer in tests:
            lift = Dinglemouse(queues, 5)
            test.assert_equals(lift.theLift(), answer)