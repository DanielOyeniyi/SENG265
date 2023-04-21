#!/usr/bin/env python
import random as rd
from enum import Enum
from typing import NamedTuple

class ShapeKind(Enum):
    """Suported shape kinds"""
    CIRCLE = 0
    RECTANGLE = 1
    ELLIPSE = 2

    def __str__(self) -> str:
        return f'{self.value}'

class NumberRange:
    """
    A simple integer/float range with minimum and maxium values
    no type hints as nmin and nmax can either be an int or float
    """
    def __init__(self, start, end):
        self.start = start 
        self.end = end 

    def __str__(self) -> str:
        return f'({self.start}, {self.end})'

    def get_random(self):
        """returns a random int/float within the number range"""
        if (type(self.start) == int and type(self.end) == int):
            return rd.randint(self.start, self.end)
        return round(rd.uniform(self.start, self.end),1)

class Color(NamedTuple):
    """Store rgb values in a tuple"""
    Red: int
    Green: int
    Blue: int

    def __str__(self) -> str:
        return f'rgb({self.Red}, {self.Green}, {self.Blue})'
    
class EllipseShape:
    """A ellipse shape representing a SVG circle element"""
    ecnt: int = 0

    @classmethod
    def get_ellipse_count(cls) -> int:
        """returns the number of EllipseShapes created"""
        return EllipseShape.ecnt

    def __init__(self, cx: int, cy: int, rx: int, ry: int, color: Color, op: float):
        self.cx: int = cx
        self.cy: int = cy
        self.rx: int = rx
        self.ry: int = ry
        self.color: Color = color
        self.op: float = op
        EllipseShape.ecnt += 1

    def svg_element(self):
        """return the object as an svg ellipse string"""
        return f'<ellipse cx="{self.cx}" cy="{self.cy}" rx="{self.rx}" ry="{self.ry}"' \
               f'fill="{self.color}" fill-opacity="{self.op}"></ellipse>' 

class RectangleShape:
    """A rectangle shape representing a SVG circle element"""
    rcnt: int = 0

    @classmethod
    def get_rectangle_count(cls) -> int:
        """returns the number of RectangleShapes created"""
        return RectangleShape.rcnt

    def __init__(self, x: int, y: int, width: int, height: int, color: Color, op: float):
        self.x: int = x
        self.y: int = y
        self.width: int = width
        self.height: int = height
        self.color: Color = color
        self.op: float = op
        RectangleShape.rcnt += 1

    def svg_element(self):
        """return the object as an svg rectangle string"""
        return f'<rect x="{self.x}" y="{self.y}" width="{self.width}" height="{self.height}"' \
               f'fill="{self.color}" fill-opacity="{self.op}"></rect>' 

class CircleShape:
    """A circle shape representing a SVG circle element"""
    ccnt: int = 0

    @classmethod
    def get_circle_count(cls) -> int:
        """returns the number of CircleShapes created"""
        return CircleShape.ccnt

    def __init__(self, cx: int, cy: int, r: int, color: Color, op: float):
        self.cx: int = cx
        self.cy: int = cy
        self.r: int = r
        self.color: Color = color
        self.op: float = op
        CircleShape.ccnt += 1

    def svg_element(self):
        """return the object as an svg circle string"""
        return f'<circle cx="{self.cx}" cy="{self.cy}" r="{self.r}" fill="{self.color}" fill-opacity="{self.op}"></circle>' 

class PyArtConfig: 
    """Input Configuration to guide the generation of random shapes"""

    def  __init__(self, SHA: list , X: NumberRange, Y: NumberRange, RAD: NumberRange, RX: NumberRange, 
                  RY: NumberRange, W: NumberRange, H:NumberRange, R:NumberRange, G:NumberRange, 
                  B: NumberRange, OP: NumberRange):
        self.SHA: list = SHA
        self.X: NumberRange = X
        self.Y: NumberRange = Y
        self.RAD: NumberRange = RAD
        self.RX: NumberRange = RX
        self.RY: NumberRange = RY
        self.W: NumberRange = W
        self.H:NumberRange = H
        self.R:NumberRange = R
        self.G:NumberRange = G 
        self.B: NumberRange = B
        self.OP: NumberRange = OP

    def __str__(self) -> str:
        """prints the properites of the PyArtConfig"""
        return f'\nUser-defined art configuration\n' \
               f'Shape types = ({", ".join(self.SHA)})\n' \
               f'X(Xmin, Xmax) = {self.X}\n' \
               f'Y(Ymin, Ymax) = {self.Y}\n' \
               f'RAD(RADmin, RADmax) = {self.RAD}\n' \
               f'RX(RXmin, RXmax) = {self.RX}\n' \
               f'RY(RYmin, RYmax) = {self.RY}\n' \
               f'W(Wmin, Wmax) = {self.W}\n' \
               f'H(Hmin, Hmax) = {self.H}\n' \
               f'R(Rmin, Rmax) = {self.R}\n' \
               f'G(Gmin, Gmax) = {self.G}\n' \
               f'B(Bmin, Bmax) = {self.B}\n' \
               f'OP(OPmin, OPmax) = {self.OP}\n' \
               

class RandomShape:
    """Generates a random shape based on the PyArtConfig"""
    CNT: int = -1 # the number of random shapes created, shape 1 corresponds to count 0 

    @classmethod
    def get_Shape_count(cls) -> int: 
        """returns the number of RandomShapes created"""
        return RandomShape.CNT

    def __init__(self, config: PyArtConfig):
        RandomShape.CNT += 1
        self.SHA: ShapeKind = ShapeKind[rd.choice(config.SHA)]
        self.X: int = config.X.get_random()
        self.Y: int = config.Y.get_random()
        self.RAD: int = config.RAD.get_random()
        self.RX: int = config.RX.get_random()
        self.RY: int = config.RY.get_random()
        self.W: int = config.W.get_random()
        self.H: int = config.H.get_random()
        self.R: int = config.R.get_random()
        self.G: int = config.G.get_random() 
        self.B: int = config.B.get_random()
        self.OP: float = config.OP.get_random()

    def __str__(self) -> str:
        """prints the properites of the RandomShape"""
        return f'\nProperties of Random Shape\n' \
               f'Shape = {self.SHA}\n' \
               f'X = {self.X}\n' \
               f'Y = {self.Y}\n' \
               f'RAD = {self.RAD}\n' \
               f'RX = {self.RX}\n' \
               f'RY = {self.RY}\n' \
               f'W = {self.W}\n' \
               f'H = {self.H}\n' \
               f'R = {self.R}\n' \
               f'G = {self.G}\n' \
               f'B = {self.B}\n' \
               f'OP = {self.OP}\n' \

    def as_Part2_line(self) -> str: 
        """prints the properties in the format specified in part2 of the a4 writeup"""
        return f'{RandomShape.CNT : >4}{self.SHA : >4}{self.X : >4}{self.Y : >4}' \
               f'{self.RAD : >4}{self.RX : >4}{self.RY : >4}{self.W : >4}' \
               f'{self.H : >4}{self.R : >4}{self.G : >4}{self.B : >4}{self.OP : >4}\n' \

    def as_svg(self) -> str:
        """prints the RandomShape as an svg script"""
        color: Color = Color(self.R, self.G, self.B)
        if self.SHA.name == 'CIRCLE':
            c: CircleShape = CircleShape(self.X, self.Y, self.RAD, color, self.OP)
            return c.svg_element()

        elif self.SHA.name == 'RECTANGLE':
            r: RectangleShape = RectangleShape(self.X, self.Y, self.W, self.H, color, self.OP)
            return r.svg_element()

        else: 
            e: EllipseShape = EllipseShape(self.X, self.Y, self.RX, self.RY, color, self.OP)
            return e.svg_element()

class HtmlDocument:
    """
    An HTML document that allow appending SVG content
    inspired by Seng265 slides by Hausi Muller
    """
    TAB: str = "    " #HTML indent tag (default: four spaces) 
 
    def __init__(self, file_name: str, win_title: str) -> None:
        self.win_title: str = win_title
        self.__tabs: int = 0
        self.__file: IO = open(file_name, "w")
        self.__write_head()

    def increase_indent(self) -> None:
        """Increases the number of tab characters used for indentation"""
        self.__tabs += 1

    def decrease_indent(self) -> None:
        """Decreases the number of tab characters used for indentation"""
        self.__tabs -= 1

    def append(self, content: str) -> None:
        """Appends the given HTML content to this document"""
        ts: str = HtmlDocument.TAB * self.__tabs
        self.__file.write(f'{ts}{content}\n')

    def __write_head(self) -> None:
        """Appends the HTML preamble to this document"""
        self.append('<html>')
        self.append('<head>')
        self.increase_indent()
        self.append(f'<title>{self.win_title}</title>')
        self.decrease_indent()
        self.append('</head>')

    def close_document(self) -> None:
        """closes the document"""
        self.append('</html>')
        self.__file.close()

    def __write_comment(self, comment: str) -> None:
        """Appends an HTML comment to this document"""
        self.append(f'<!--{comment}-->')

    def open_body_scope(self) -> None:
        """Opens a body scope in the document"""
        self.append('<body>')
        self.increase_indent()

    def close_body_scope(self) -> None:
        """closes the body scope in the document"""
        self.decrease_indent()
        self.append('</body>')

    def open_svg_scope(self, width: int, height: int) -> None:
        """ opens an svg scope in the document"""
        self.__write_comment('Define SVG drawing box')
        self.append(f'<svg width="{width}" height="{height}">')
        self.increase_indent()

    def close_svg_scope(self) -> None:
        """closes the svg scope in the document"""
        self.decrease_indent()
        self.append('</svg>')

    def gen_art(self, config: PyArtConfig, number: int) -> None:
        """generates art by creating (number) random shapes"""
        for x in range(number):
            shape:RandomShape = RandomShape(config)
            self.append(shape.as_svg())


def gen_random_table(config: PyArtConfig, number: int) -> None:
    """generates then prints a table representing (number) of random shapes created"""
    print(f'{"CNT" : <4}{"SHA" : <4}{"X" : <4}{"Y":<4}{"RAD" : <4}{"RX" : <4}' \
            f'{"RY" : <4}{"W" : <4}{"H" : <4}{"R" : <4}{"G" : <4}{"B" : <4}{"OP" : <4}')
    
    for x in range(number):
        shape:RandomShape = RandomShape(config)
        print(shape.as_Part2_line())

def main():
    doc: HtmlDocument= HtmlDocument("a43.html", "My art")
    doc.open_body_scope()
    doc.open_svg_scope(500, 300)

    config: PyArtConfig = PyArtConfig(['RECTANGLE','CIRCLE', 'ELLIPSE'], NumberRange(0,500), NumberRange(0,300),
                          NumberRange(1,5), NumberRange(5,10), NumberRange(10,30),
                          NumberRange(10,15), NumberRange(30,80), NumberRange(150,255),
                          NumberRange(0,90), NumberRange(0,95), NumberRange(0.3,0.9))
    doc.gen_art(config, 800)
    doc.close_svg_scope()
    doc.close_body_scope()
    doc.close_document()


if __name__ == '__main__':
    main()
