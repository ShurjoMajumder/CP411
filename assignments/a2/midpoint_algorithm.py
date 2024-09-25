# Author: Shurjo Majumder
# Date: 25-Sep-2024
# ID: 169035249
# Assignment: CP411-A2

# Reference code:
# * https://rosettacode.org/wiki/Bitmap/Midpoint_circle_algorithm#Python
# * https://rosettacode.org/wiki/Bitmap/Python


class Bitmap:
    def __init__(self, width = 40, height = 40, background=0):
        # assert width > 0 and height > 0 and type(background) == Colour
        self.width = width
        self.height = height
        self.background = background
        self.map = [
            [
                0 for _ in range(width)
            ]
            for _ in range(height)
        ]

    def set(self, x, y, colour=1):
        # assert type(colour) == Colour
        self.map[y][x] = colour
 
    def get(self, x, y):
        return self.map[y][x]

    def circle(self, x0, y0, radius, colour=1):
        f = 1 - radius
        ddf_x = 1
        ddf_y = -2 * radius
        x = 0
        y = radius
        self.set(x0, y0 + radius, colour)
        self.set(x0, y0 - radius, colour)
        self.set(x0 + radius, y0, colour)
        self.set(x0 - radius, y0, colour)

        while x < y:
            if f >= 0:
                y -= 1
                ddf_y += 2
                f += ddf_y
            x += 1
            ddf_x += 2
            f += ddf_x
            self.set(x0 + x, y0 + y, colour)
            self.set(x0 - x, y0 + y, colour)
            self.set(x0 + x, y0 - y, colour)
            self.set(x0 - x, y0 - y, colour)
            self.set(x0 + y, y0 + x, colour)
            self.set(x0 - y, y0 + x, colour)
            self.set(x0 + y, y0 - x, colour)
            self.set(x0 - y, y0 - x, colour)


if __name__ == "__main__":
    bm = Bitmap(40, 40, background=0)
    bm.circle(x0=20, y0=20, radius=10, colour=1)

    with open("./assets/pixel_data.txt", 'w') as pixel_data:
        for (x, row) in enumerate(bm.map):
            for (y, item) in enumerate(row):
                if item == 1:
                    print(f"{x - 20} {y - 20}", file=pixel_data)
