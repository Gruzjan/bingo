#include <iostream>

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>
#include <smk/Rectangle.hpp>
#include <smk/Vertex.hpp>
#include <smk/VertexArray.hpp>

#include "classes/button.cpp"

smk::Window menu() {
  // Open a new window.
  auto window = smk::Window(640, 480, "scena1");

  // Create circle_red.
  auto circle_red = smk::Shape::Circle(200);
  auto square = smk::Shape::Square();

  square.SetPosition(30, 30);
  square.SetScaleX(20);
  square.SetScaleY(10);

  circle_red.SetColor(smk::Color::Red);
  circle_red.SetPosition(320, 240);

  Button test(150, 150, 100, 40, window);
  Button test2(250, 250, 100, 40, window);

  // Create circle_blue.
  auto circle_blue = smk::Shape::Circle(100, 5 /* subdivision */);
  circle_blue.SetColor(smk::Color::Blue);
  circle_blue.SetPosition(320, 240);

  window.ExecuteMainLoop([&] {
    window.PoolEvents();
    window.Clear(smk::Color::Black);

   test.onHover([&] {
     window.Draw(circle_red);
   });

  if (window.input().IsMousePressed(GLFW_MOUSE_BUTTON_1)) {
      window.Draw(circle_blue);
  }

   test2.onClick([&] {
     window.Draw(circle_red);
   });

    window.Draw(test.getButton());
    window.Draw(test2.getButton());

    window.Display();
  });

  return window;
}
