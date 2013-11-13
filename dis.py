#!/usr/bin/python
# -*- encoding: utf8 -*-

import random, itertools, time
import numpy as np
import sys, pygame

pygame.init()
pygame.key.set_repeat(200, 10)

FPS = 30
fpsClock = pygame.time.Clock()

DECK_WIDTH = 300
DECK_HEIGHT = 100
ROOM_MAX_ASPECT_RATIO = 4
ROOM_MAX_AREA = 100
CORRIDOR_MIN_WIDTH = 1
CORRIDOR_MAX_WIDTH = 4
CORRIDOR_MIN_DISTANCE = 4
CORRIDOR_CONNECT_DISTANCE = 8
CORRIDOR_FORK_CHANCE = 0.5
CORRIDOR_SPAWN_POINTS = 4
CORRIDOR_SPAWN_POINT_MARGIN = 20
CORRIDOR_MIN_LENGTH = 0
CORRIDOR_MIN_LENGTH_PER_WIDTH = 2
CORRIDOR_MAX_LENGTH_PER_WIDTH = 8

WALL_DRAW_OFFSET = 0.1

HORIZONTAL = LEFT = 0
VERTICAL = UP = TOP = 1
RIGHT = 2
DOWN = BOTTOM = 3

class Rect(list):
    def __init__(self, left, top, right = None, bottom = None):
        list.__init__(self, [left, top, left + 1, top + 1])
        if right is not None:
            self.right = right
        if bottom is not None:
            self.bottom = bottom
    
    def __str__(self):
        return "Rect: (left = {0}, top = {1}, right = {2}, bottom = {3})".format(*self)
    
    def __setitem__(self, index, value):
        list.__setitem__(self, index, value)
        assert self.left <= self.right and self.top <= self.bottom
    
    def get_wall(direction):
        return Wall(self.right if direction == RIGHT else self.left, self.bottom if direction == BOTTOM else self.top, direction, self.size[(i+1) % 2], None)
    
    @property
    def squares(self):
        result = []
        for i in range(self.left, self.right):
            for j in range(self.top, self.bottom):
                result.append((i, j))
        return result
    
    @property
    def left(self):
        return self[0]
    @left.setter
    def left(self, value):
        self[0] = value
    
    @property
    def top(self):
        return self[1]
    @top.setter
    def top(self, value):
        self[1] = value
        
    @property
    def right(self):
        return self[2]
    @right.setter
    def right(self, value):
        self[2] = value
        
    @property
    def bottom(self):
        return self[3]
    @bottom.setter
    def bottom(self, value):
        self[3] = value
        
    @property
    def area(self):
        return self.width * self.height
    
    @property
    def size(self):
        return self.width, self.height
    
    @property
    def width(self):
        return (self.right - self.left)
    
    @property
    def height(self):
        return (self.bottom - self.top)
    
    @property
    def aspect(self):
        if self.width == self.height:
            return 1.0
        elif self.width > self.height:
            return 1.0 * self.width / self.height
        else:
            return 1.0 * self.height / self.width
    
    def intersects(self, other):
        assert isinstance(other, Room) or isinstance(other, Rect)
        if isinstance(other, Room):
            return any([self.intersects(rect) for rect in other.rects])
        else:
            return self.left < other.right and other.left < self.right and self.top < other.bottom and other.top < self.bottom

class Room:
    def __init__(self, type, *args):
        self.type = type
        self.rects = list(args)
        self.doors = []
    
    def __str__(self):
        result = "  Room: (area = {0})\n".format(self.area)
        for rect in self.rects:
            result += rect.__str__()
        return result
    
    @property
    def walls(self):
        result = []
        for rect in self.rects:
            for i in range(4):
                if not any([rect[i] == other_rect[(i + 2) % 4] for other_rect in self.rects]):
                    result.append(Wall(rect.right if i == RIGHT else rect.left, rect.bottom if i == BOTTOM else rect.top, i, rect.size[(i+1) % 2], self))
                else:
                    if i == 0:
                        for y in range(rect.top, rect.bottom):
                            if not any([(rect.left - 1, y) in other_rect.squares for other_rect in self.rects]):
                                result.append(Wall(rect.left, y, i, 1, self))
                    if i == 1:
                        for x in range(rect.left, rect.right):
                            if not any([(x, rect.top - 1) in other_rect.squares for other_rect in self.rects]):
                                result.append(Wall(x, rect.top, i, 1, self))
                    if i == 2:
                        for y in range(rect.top, rect.bottom):
                            if not any([(rect.right, y) in other_rect.squares for other_rect in self.rects]):
                                result.append(Wall(rect.right, y, i, 1, self))
                    if i == 3:
                        for x in range(rect.left, rect.right):
                            if not any([(x, rect.bottom) in other_rect.squares for other_rect in self.rects]):
                                result.append(Wall(x, rect.bottom, i, 1, self))
                                    
                            
                    
        return result
    
    @property
    def squares(self):
        return list(itertools.chain(*[rect.squares for rect in self.rects]))
    
    @property
    def area(self):
        return sum([rect.area for rect in self.rects])
    
    def intersects(self, other):
        assert isinstance(other, Room) or isinstance(other, Rect)
        return any([other.intersects(rect) for rect in self.rects])


class Wall:
    def __init__(self, x, y, orientation, length, room):
        self.x = x
        self.y = y
        self.orientation = orientation
        self.length = length
        self.room = room
    
    def __str__(self):
        return "Wall: (x = {0}, y = {1}, orientation = {2}, length = {3})".format(self.x, self.y, self.orientation, self.length)
    
    def __sub__(self, other):
        """Cuts other wall from this wall and returns the rest
        
        The walls must have opposite orientations. The result is a list of one
        or two walls.
        """
        assert isinstance(other, wall)
        assert abs(self.orientation - other.orientation) == 2
        if self.orientation % 2 == 0:
            if self.x != other.x:
                # walls are not aligned:
                return [self]
            elif self.y >= other.y + other.length or other.y >= self.y + self.length:
                # walls do not overlap:
                return [self]
            elif other.y < self.y and other.y + other.length > self.y + self.length:
                # other wall includes this wall:
                return []
            elif other.y < self.y < other.y + other.length:
                # other wall includes top end of this wall:
                return [Wall(self.x, other.y + other.length, self.orientation, self.y + self.length - (other.y + other.length), self.room)]
            elif other.y < self.y + self.length < other.y + other.length:
                # other wall includes bottom end of this wall:
                return [Wall(self.x, self.y, self.orientation, other.y - self.y, self.room)]
            else:
                # other wall cuts this wall in two:
                return [Wall(self.x, other.y + other.length, self.orientation, self.y + self.length - (other.y + other.length), self.room),
                        Wall(self.x, self.y, self.orientation, other.y - self.y, self.room)]
        else:
            if self.y!= other.y:
                # walls are not aligned:
                return [self]
            elif self.x >= other.x + other.length or other.x >= self.x + self.length:
                # walls do not overlap:
                return [self]
            elif other.x < self.x and other.x + other.length > self.x + self.length:
                # other wall includes this wall:
                return []
            elif other.x < self.x < other.x + other.length:
                # other wall includes top end of this wall:
                return [Wall(self.x, other.x + other.length, self.orientation, self.x + self.length - (other.x + other.length), self.room)]
            elif other.x < self.x + self.length < other.x + other.length:
                # other wall includes bottom end of this wall:
                return [Wall(self.x, self.x, self.orientation, other.x - self.x, self.room)]
            else:
                # other wall cuts this wall in two:
                return [Wall(self.x, other.x + other.length, self.orientation, self.x + self.length - (other.x + other.length), self.room),
                        Wall(self.x, self.x, self.orientation, other.x - self.x, self.room)]


class Door:
    def __init__(self, type, x, y, orientation, width, room1 = None, room2 = None):
        self.type = type
        self.x = x
        self.y = y
        self.orientation = orientation
        self.width = width
        self.room1 = room1
        self.room2 = room2

    def __str__(self):
        return "Door: (type = {0}, x = {1}, y = {2}, orientation = {3}, width = {4})".format(self.type, self.x, self.y, self.orientation, self.width)
    

class CorridorBuilder:
    def __init__(self, x, y, direction, width):
        self.x = x
        self.y = y
        self.direction = direction
        self.width = width


class Deck:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.rooms = []
        self.squares = []
        self.doors = []
        self.markers = [] # for debugging
        for i in range(self.x):
            col = []
            for j in range(self.y):
                col.append(None)
            self.squares.append(col)
        self.create()
    
    def __str__(self):
        result = "Deck: (x = {0}, y = {1})\n".format(self.x, self.y)
        for room in self.rooms:
            result += room.__str__() + "\n"
        return result
    
    def refresh_squares(self):
        for room in self.rooms:
            for x,y in room.squares:
                self.squares[x][y] = room
    
    def add_room(self, room):
        self.rooms.append(room)
        for x,y in room.squares:
            self.squares[x][y] = room
    
    def delete_room(self, room):
        self.rooms.remove(room)
        for x,y in room.squares:
            self.squares[x][y] = None
    
    def join_rooms(self, room1, room2):
        self.delete_room(room1)
        self.delete_room(room2)
        room1.rects.extend(room2.rects)
        self.add_room(room1)
    
    def create(self):
        t = time.time()
        print "drill corridors...",
        cbs = []
        for i in range(CORRIDOR_SPAWN_POINTS):
            x = random.randint(CORRIDOR_SPAWN_POINT_MARGIN, self.x - CORRIDOR_SPAWN_POINT_MARGIN)
            y = random.randint(CORRIDOR_SPAWN_POINT_MARGIN, self.y - CORRIDOR_SPAWN_POINT_MARGIN)
            d = random.randint(0,1)
            cbs.append(CorridorBuilder(x, y , d, CORRIDOR_MAX_WIDTH))
            cbs.append(CorridorBuilder(x, y, d + 2, CORRIDOR_MAX_WIDTH))
            self.doors.append(Door("door", x, y, d, CORRIDOR_MAX_WIDTH))
        while len(cbs) > 0:
            new_cbs = []
            for cb in cbs:
                length = random.randint(CORRIDOR_MIN_LENGTH + CORRIDOR_MIN_LENGTH_PER_WIDTH * cb.width, CORRIDOR_MIN_LENGTH + CORRIDOR_MAX_LENGTH_PER_WIDTH * cb.width)
                if cb.direction == 0:
                    rect = Rect(cb.x - length, cb.y, cb.x, cb.y + cb.width)
                    rect_padding = Rect(cb.x - length - CORRIDOR_MIN_DISTANCE, cb.y - CORRIDOR_MIN_DISTANCE, cb.x, cb.y + cb.width + CORRIDOR_MIN_DISTANCE)
                    rect_connector = Rect(cb.x - length - CORRIDOR_CONNECT_DISTANCE, cb.y - CORRIDOR_MIN_DISTANCE, cb.x, cb.y + cb.width + CORRIDOR_MIN_DISTANCE)
                    cb.x -= length
                elif cb.direction == 1:
                    rect = Rect(cb.x, cb.y - length, cb.x + cb.width, cb.y)
                    rect_padding = Rect(cb.x - CORRIDOR_MIN_DISTANCE, cb.y - length - CORRIDOR_MIN_DISTANCE, cb.x + cb.width + CORRIDOR_MIN_DISTANCE, cb.y)
                    rect_connector = Rect(cb.x - CORRIDOR_MIN_DISTANCE, cb.y - length - CORRIDOR_CONNECT_DISTANCE, cb.x + cb.width + CORRIDOR_MIN_DISTANCE, cb.y)
                    cb.y -= length
                elif cb.direction == 2:
                    rect = Rect(cb.x, cb.y, cb.x + length, cb.y + cb.width)
                    rect_padding = Rect(cb.x, cb.y - CORRIDOR_MIN_DISTANCE, cb.x + length + CORRIDOR_MIN_DISTANCE, cb.y + cb.width + CORRIDOR_MIN_DISTANCE)
                    rect_connector = Rect(cb.x, cb.y - CORRIDOR_MIN_DISTANCE, cb.x + length + CORRIDOR_CONNECT_DISTANCE, cb.y + cb.width + CORRIDOR_MIN_DISTANCE)
                    cb.x += length
                elif cb.direction == 3:
                    rect = Rect(cb.x, cb.y, cb.x + cb.width, cb.y + length)
                    rect_padding = Rect(cb.x - CORRIDOR_MIN_DISTANCE, cb.y, cb.x + cb.width + CORRIDOR_MIN_DISTANCE, cb.y + length + CORRIDOR_MIN_DISTANCE)
                    rect_connector = Rect(cb.x - CORRIDOR_MIN_DISTANCE, cb.y, cb.x + cb.width + CORRIDOR_MIN_DISTANCE, cb.y + length + CORRIDOR_CONNECT_DISTANCE)
                    cb.y += length
                
                if rect_padding[0] < 0 or rect_padding[1] < 0 or rect_padding[2] > self.x or rect_padding[3] > self.y:
                    # too close to space:
                    cbs.remove(cb)
                    continue
                elif not all([self.squares[x][y] is None for x,y in rect_padding.squares]):
                    # not enough padding
                    cbs.remove(cb)
                    continue
                else:
                    # create the new corridor segment and a door:
                    new_corridor = Room("corridor", rect)
                    self.add_room(new_corridor)
                    self.doors.append(Door("door", cb.x, cb.y, cb.direction, cb.width))
                    
                    # spawn additional corridor builders:
                    new_width = random.randint(CORRIDOR_MIN_WIDTH, cb.width)
                    if random.random() <= CORRIDOR_FORK_CHANCE:
                        if cb.direction % 2 == 0:
                            # horizontal corridor, upward fork:
                            new_cb = CorridorBuilder(cb.x - cb.direction / 2 * new_width, cb.y, 1, new_width)
                            new_cbs.append(new_cb)
                            self.doors.append(Door("door", new_cb.x, new_cb.y, new_cb.direction, new_cb.width))
                        else:
                            # vertical corridor, left fork:
                            new_cb = CorridorBuilder(cb.x, cb.y - cb.direction / 2 * new_width, 0, new_width)
                            new_cbs.append(new_cb)
                            self.doors.append(Door("door", new_cb.x, new_cb.y, new_cb.direction, new_cb.width))
                    if random.random() <= CORRIDOR_FORK_CHANCE:
                        if cb.direction % 2 == 0:
                            # horizontal corridor, downward fork:
                            new_cb = CorridorBuilder(cb.x - cb.direction / 2 * new_width, cb.y + cb.width, 3, new_width)
                            new_cbs.append(new_cb)
                            self.doors.append(Door("door", new_cb.x, new_cb.y, new_cb.direction, new_cb.width))
                        else:
                            # vertical corridor, right fork:
                            new_cb = CorridorBuilder(cb.x + cb.width, cb.y - cb.direction / 2 * new_width, 2, new_width)
                            new_cbs.append(new_cb)
                            self.doors.append(Door("door", new_cb.x, new_cb.y, new_cb.direction, new_cb.width))
            cbs.extend(new_cbs)
        print time.time() - t, "seconds"
        
        t = time.time()
        print "fill free space with rooms...",
        for i in range(self.x * self.y):
            x = i % self.x
            y = i / self.x
            rect = Rect(x, y)
            if all([self.squares[x][y] is None for x,y in rect.squares]):
                rect[2] += 1
                rect[3] += 1
                while rect[2] <= self.x and rect[3] <= self.y and all([self.squares[x][y] is None for x,y in rect.squares]) and rect.aspect <= ROOM_MAX_ASPECT_RATIO:
                    rect[2] += 1
                    rect[3] += 1
                rect[2] -= 1
                rect[3] -= 1
                while rect[2] <= self.x and rect[3] <= self.y and all([self.squares[x][y] is None for x,y in rect.squares]) and rect.aspect <= ROOM_MAX_ASPECT_RATIO:
                    rect[2] += 1
                rect[2] -= 1
                while rect[2] <= self.x and rect[3] <= self.y and all([self.squares[x][y] is None for x,y in rect.squares]) and rect.aspect <= ROOM_MAX_ASPECT_RATIO:
                    rect[3] += 1
                rect[3] -= 1
                if rect.area > 0:
                    self.add_room(Room("room", rect))
        print time.time() - t, "seconds"
        
        t = time.time()
        print "split large rooms...",
        while max([room.area for room in self.rooms if room.type == "room"]) > ROOM_MAX_AREA:
            for room in self.rooms:
                if room.type == "room" and room.area > ROOM_MAX_AREA:
                    self.delete_room(room)
                    rect = room.rects[0]
                    x, y = rect.size
                    if x > y:
                        split = random.randint(x/3, x*2/3)
                        room1 = Room("room", Rect(rect[0], rect[1], rect[0] + split, rect[3]))
                        room2 = Room("room", Rect(rect[0] + split, rect[1], rect[2], rect[3]))
                    else:
                        split = random.randint(y/3, y*2/3)
                        room1 = Room("room", Rect(rect[0], rect[1], rect[2], rect[1] + split))
                        room2 = Room("room", Rect(rect[0], rect[1] + split, rect[2], rect[3]))
                    self.add_room(room1)
                    self.add_room(room2)
        print time.time() - t, "seconds"
        
        t = time.time()
        print "turn narrow rooms into corridors...",
        for room in self.rooms:
            if len(room.rects) == 1:
                if room.rects[0].width == 1:
                    room.type = "corridor"
                    if room.rects[0].top != 0:
                        self.doors.append(Door("door", room.rects[0].left, room.rects[0].top, 1, 1))
                    if room.rects[0].bottom < self.y:
                        self.doors.append(Door("door", room.rects[0].left, room.rects[0].bottom, 1, 1))
                elif room.rects[0].height == 1:
                    room.type = "corridor"
                    if room.rects[0].left != 0:
                        self.doors.append(Door("door", room.rects[0].left, room.rects[0].top, 0, 1))
                    if room.rects[0].right < self.x:
                        self.doors.append(Door("door", room.rects[0].right, room.rects[0].top, 0, 1))
        print time.time() - t, "seconds"
        
        t = time.time()
        print "temporarily connect doors to adjacent rooms...",
        for door in self.doors:
            if door.orientation % 2 == 0:
                s1x, s1y = (door.x - 1, door.y)
                s2x, s2y = (door.x, door.y)
            else:
                s1x, s1y = (door.x, door.y - 1)
                s2x, s2y = (door.x, door.y)
            door.room1 = self.squares[s1x][s1y]
            door.room2 = self.squares[s2x][s2y]
            door.room1.doors.append(door)
            door.room2.doors.append(door)
        print time.time() - t, "seconds"
        
        t = time.time()
        print "randomly join some rooms...",
        counter = 0
        while counter < 50:
            small_rooms = [room for room in self.rooms if room.type == "room" and room.area < 50]
            if len(small_rooms) == 0:
                break
            room = random.choice(small_rooms)
            rect = random.choice(room.rects)
            if rect.width > rect.height:
                direction = random.choice([1, 3])
            else:
                direction = random.choice([0, 2])
            direction = random.randint(0, 3)
            if direction == 0:
                if rect[0] == 0:
                    continue
                x = rect[0] - 1
                y = random.randint(rect[1], rect[3] - 1)
            elif direction == 1:
                if rect[1] == 0:
                    continue
                x = random.randint(rect[0], rect[2] - 1)
                y = rect[1] - 1
            elif direction == 2:
                if rect[2] >= self.x - 1:
                    continue
                x = rect[2] + 1
                y = random.randint(rect[1], rect[3] - 1)
            elif direction == 3:
                if rect[3] >= self.y - 1:
                    continue
                x = random.randint(rect[0], rect[2] - 1)
                y = rect[3] + 1
            next_room = self.squares[x][y]
            if next_room.type == "room" and next_room is not room:
                counter += 1
                self.join_rooms(room, next_room)
        print time.time() - t, "seconds"
        
        t = time.time()
        print "place some more doors...",
        for i in range(3):
            for room in self.rooms:
                if len(room.doors) < 2 and room.type == "room":
                    rect = random.choice(room.rects)
                    direction = random.randint(0, 3)
                    if direction == 0:
                        if rect[0] == 0:
                            continue
                        x = rect[0]
                        y = random.randint(rect[1], rect[3] - 1)
                    elif direction == 1:
                        if rect[1] == 0:
                            continue
                        x = random.randint(rect[0], rect[2] - 1)
                        y = rect[1]
                    elif direction == 2:
                        if rect[2] >= self.x - 1:
                            continue
                        x = rect[2]
                        y = random.randint(rect[1], rect[3] - 1)
                    elif direction == 3:
                        if rect[3] >= self.y - 1:
                            continue
                        x = random.randint(rect[0], rect[2] - 1)
                        y = rect[3]
                    door = Door("door", x, y, direction, 1)
                    self.doors.append(door)
        print time.time() - t, "seconds"
        
        t = time.time()
        print "shrink large doors...",
        for door in self.doors:
            if door.width > 1:
                if door.orientation % 2 == 0:
                    s1x, s1y = (door.x, door.y)
                    s2x, s2y = (door.x - 1, door.y)
                    room1 = self.squares[s1x][s1y]
                    room2 = self.squares[s2x][s2y]
                    for i in range(1, door.width):
                        s1x, s1y = (door.x, door.y + i)
                        s2x, s2y = (door.x - 1, door.y + i)
                        room1a = self.squares[s1x][s1y]
                        room2a = self.squares[s2x][s2y]
                        if (room1a is not room1) or (room2a is not room2):
                            door.width = i
                            break
                else:
                    s1x, s1y = (door.x, door.y)
                    s2x, s2y = (door.x, door.y - 1)
                    room1 = self.squares[s1x][s1y]
                    room2 = self.squares[s2x][s2y]
                    for i in range(1, door.width):
                        s1x, s1y = (door.x + i, door.y)
                        s2x, s2y = (door.x + i, door.y - 1)
                        room1a = self.squares[s1x][s1y]
                        room2a = self.squares[s2x][s2y]
                        if (room1a is not room1) or (room2a is not room2):
                            door.width = i
                            break
        print time.time() - t, "seconds"
        
        t = time.time()
        print "connect doors to rooms (and vice versa)...",
        for room in self.rooms:
            room.doors = []
        broken_doors = []
        for door in self.doors:
            if door.orientation == 0:
                s1x, s1y = (door.x, door.y)
                s2x, s2y = (door.x - 1, door.y)
            elif door.orientation == 1:
                s1x, s1y = (door.x, door.y)
                s2x, s2y = (door.x, door.y - 1)
            elif door.orientation == 2:
                s1x, s1y = (door.x - 1, door.y)
                s2x, s2y = (door.x, door.y)
            else:
                s1x, s1y = (door.x, door.y - 1)
                s2x, s2y = (door.x, door.y)
            door.room1 = self.squares[s1x][s1y]
            door.room2 = self.squares[s2x][s2y]
            if door.room1 is door.room2:
                broken_doors.append(door)
            else:
                door.room1.doors.append(door)
                door.room2.doors.append(door)
        for door in broken_doors:
            self.doors.remove(door)
        print time.time() - t, "seconds"
        
        #~ t = time.time()
        #~ print "some checks...",
        #~ for room in self.rooms:
            #~ for door in room.doors:
                #~ assert door in self.doors
        #~ for door in self.doors:
            #~ assert door in door.room1.doors
            #~ assert door in door.room2.doors
        #~ print time.time() - t, "seconds"
        
        t = time.time()
        print "remove redundant doors...",
        redundant_doors = set()
        for room in self.rooms:
            neighbours = set()
            for door in room.doors:
                if door.room1 is not room:
                    if door.room1 not in neighbours:
                        neighbours.add(door.room1)
                    else:
                        redundant_doors.add(door)
                else:
                    if door.room2 not in neighbours:
                        neighbours.add(door.room2)
                    else:
                        redundant_doors.add(door)
        for door in redundant_doors:
            self.doors.remove(door)
            door.room1.doors.remove(door)
            door.room2.doors.remove(door)
        print time.time() - t, "seconds"


def draw_deck(deck, surface, scale, dx, dy):
    width, height = surface.get_size()
    def tx(x):
        return scale * x + width / 2 - scale * deck.x / 2 + dx
    def ty(y):
        return scale * y + height / 2 - scale * deck.y / 2 + dy
        
    # deck background:
    #~ pygame.draw.rect(surface, (0, 0, 0), (tx(0), ty(0), scale * deck.x, scale * deck.y))
    #~ pygame.draw.rect(surface, (100, 100, 100), (tx(0), ty(0), scale * self.x, scale * self.y), 1)
    
    # rooms background:
    for room in deck.rooms:
        if room.type == "corridor":
            bg_color = (100, 100, 100)
        elif room.type == "special":
            bg_color = (0, 100, 100)
        else:
            bg_color = (60, 60, 60)
        for rect in room.rects:
            pygame.draw.rect(surface, bg_color, (tx(rect[0]), ty(rect[1]), scale * (rect[2] - rect[0]) + 1, scale * (rect[3] - rect[1]) + 1))
            #~ pygame.draw.rect(surface, (150, 150, 150), (tx(rect[0]), ty(rect[1]), scale * (rect[2] - rect[0]) + 1, scale * (rect[3] - rect[1]) + 1), 1)
    
    # walls:
    for room in deck.rooms:
        for wall in room.walls:
            if wall.orientation == 0:
                pygame.draw.line(surface, (150, 150, 150), (tx(wall.x + WALL_DRAW_OFFSET), ty(wall.y)), (tx(wall.x + WALL_DRAW_OFFSET), ty(wall.y + wall.length)), 2)
            elif wall.orientation == 1:
                pygame.draw.line(surface, (150, 150, 150), (tx(wall.x), ty(wall.y + WALL_DRAW_OFFSET)), (tx(wall.x + wall.length), ty(wall.y + WALL_DRAW_OFFSET)), 2)
            elif wall.orientation == 2:
                pygame.draw.line(surface, (150, 150, 150), (tx(wall.x - WALL_DRAW_OFFSET), ty(wall.y)), (tx(wall.x - WALL_DRAW_OFFSET), ty(wall.y + wall.length)), 2)
            elif wall.orientation == 3:
                pygame.draw.line(surface, (150, 150, 150), (tx(wall.x), ty(wall.y - WALL_DRAW_OFFSET)), (tx(wall.x + wall.length), ty(wall.y - WALL_DRAW_OFFSET)), 2)
    
    # grid:
    alpha_surface = surface.convert_alpha()
    for i in range(deck.x + 1):
        pygame.draw.line(alpha_surface, (255, 255, 255, 30), (tx(i), ty(0)), (tx(i), ty(deck.y)))
    for i in range(deck.y + 1):
        pygame.draw.line(alpha_surface, (255, 255, 255, 30), (tx(0), ty(i)), (tx(deck.x), ty(i)))
    surface.blit(alpha_surface,(0,0))
    
    # doors:
    for door in deck.doors:
        if door.orientation % 2 == 0:
            pygame.draw.rect(surface, (0, 0, 0), (tx(door.x) - scale * 0.2, ty(door.y) + scale * 0.1, scale * 0.4, scale * door.width - scale * 0.2))
        else:
            pygame.draw.rect(surface, (0, 0, 0), (tx(door.x) + scale * 0.1, ty(door.y) - scale * 0.2, scale * door.width - scale * 0.2, scale * 0.4))

    # missing squares (debug):
    for x in range(deck.x):
        for y in range(deck.y):
            if deck.squares[x][y] is None:
                pygame.draw.line(surface, (0, 255, 0), (tx(x), ty(y)), (tx(x + 1), ty(y + 1)), 2)
                
    # markers (debug):
    for x, y in deck.markers:
        pygame.draw.line(surface, (255, 0, 0), (tx(x), ty(y)), (tx(x + 1), ty(y + 1)), 2)
    


if __name__ == "__main__":
    x, y = DECK_WIDTH, DECK_HEIGHT
    deck = Deck(x, y)
    
    screen = pygame.display.set_mode((0,0), pygame.FULLSCREEN)
    width, height = screen.get_size()
    scale = min(1.0 * width / x, 1.0 * height / y) * 0.9
    dx, dy = 0, 0
    drag = False
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                #~ print event
                if event.key == 113:
                    sys.exit()
                elif event.unicode == '+':
                    scale *= 1.1
                elif event.unicode == '-':
                    scale /= 1.1
                elif event.key == 274:
                    dy += 10
                elif event.key == 273:
                    dy -= 10
                elif event.key == 275:
                    dx += 10
                elif event.key == 276:
                    dx -= 10
                elif event.key == 278:
                    scale = min(1.0 * width / x, 1.0 * height / y) * 0.9
                    dx = 0
                    dy = 0
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == 4:
                    scale *= 1.1
                elif event.button == 5:
                    scale /= 1.1
            elif event.type == pygame.MOUSEMOTION:
                if event.buttons[0] == 1:
                    dx += event.rel[0]
                    dy += event.rel[1]
        
        #~ screen.blit(bg, (0, 0))
        screen.fill((0, 0, 0))
        draw_deck(deck, screen, scale, dx, dy)
        
        pygame.display.flip()
        fpsClock.tick(FPS)

