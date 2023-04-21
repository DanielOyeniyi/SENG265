#!/usr/bin/env python
from typing import NamedTuple

class Color(NamedTuple):
    """Store rgb values in a tuple"""
    Red: int
    Green: int
    Blue: int

    def __str__(self) -> str:
        return f'rgb({self.Red}, {self.Green}, {self.Blue})'

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
        return f'<circle cx="{self.cx}" cy="{self.cy}" r="{self.r}" fill="{self.color}"' \
               f'fill-opacity="{self.op}"></circle>' 

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

    def gen_art(self) -> None:
        """generates the art depicted in figure 1 of the a4-art-writeup.pdf"""
        circle1: CircleShape = CircleShape(50, 50, 50, Color(255,0,0), 1.0)
        circle2: CircleShape = CircleShape(150, 50, 50, Color(255,0,0), 1.0)
        circle3: CircleShape = CircleShape(250, 50, 50, Color(255,0,0), 1.0)
        circle4: CircleShape = CircleShape(350, 50, 50, Color(255,0,0), 1.0)
        circle5: CircleShape = CircleShape(450, 50, 50, Color(255,0,0), 1.0)
        circle6: CircleShape = CircleShape(50, 250, 50, Color(0,0,255), 1.0)
        circle7: CircleShape = CircleShape(150, 250, 50, Color(0,0,255), 1.0)
        circle8: CircleShape = CircleShape(250, 250, 50, Color(0,0,255), 1.0)
        circle9: CircleShape = CircleShape(350, 250, 50, Color(0,0,255), 1.0)
        circle10: CircleShape = CircleShape(450, 250, 50, Color(0,0,255), 1.0)

        self.append(circle1.svg_element())
        self.append(circle2.svg_element())
        self.append(circle3.svg_element())
        self.append(circle4.svg_element())
        self.append(circle5.svg_element())
        self.append(circle6.svg_element())
        self.append(circle7.svg_element())
        self.append(circle8.svg_element())
        self.append(circle9.svg_element())
        self.append(circle10.svg_element())

def main():
    doc: HtmlDocument= HtmlDocument("a41.html", "My art")
    doc.open_body_scope()
    doc.open_svg_scope(500, 300)
    doc.gen_art()
    doc.close_svg_scope()
    doc.close_body_scope()
    doc.close_document()

if __name__ == '__main__':
    main()


