// сигнатура
DrawText(Point p, std::string text); // x, y определяют верхний левый угол первой буквы
DrawLine(Point p1, Point p2);
ClearGlyph(int x, int y, int width, int height); // параметрами задается прямоугольник, который занимает глиф


// где и как предполагается использовать
Character::Draw(gui) {
    gui.drawText({x, y}, std::string(1, symbol));
}

Button::Draw(gui) {
    gui.DrawButton(x, y, width, height);
}

DrawButton(gui, x, y, width, height) {
    gui.DrawLine({x, y}, {x + width, y});
    gui.DrawLine({x, y}, {x, y + height});
    gui.DrawLine({x + width, y}, {x + width, y + height});
    gui.DrawLine({x, y + height}, {x + width, y + height});
}

Glyph::ClearGlyph(gui) {
    gui.ClearGlyph(x, y, width, height);
}