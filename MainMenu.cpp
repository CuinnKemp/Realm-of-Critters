#include "MainMenu.h"

extern sf::Window *window;

MainMenu::MainMenu() {
  winclose = new sf::RectangleShape();
  font = new sf::Font();
  image = new sf::Texture();
  bg = new sf::Sprite();

  set_values();
}

MainMenu::~MainMenu() {
  delete winclose;
  delete font;
  delete image;
  delete bg;
}

void MainMenu::set_values() {
  window->create(sf::VideoMode(1920, 1080), "Menu SFML",
                 sf::Style::Titlebar | sf::Style::Close);
  window->setPosition(sf::Vector2i(0, 0));

  pos = 0;
  pressed = theselect = false;
  font->loadFromFile("OfMiceAndCats.ttf");
  image->loadFromFile("./menu-sci-fi-game.png");

  bg->setTexture(*image);

  pos_mouse = {0, 0};
  mouse_coord = {0, 0};

  options = {"Game Name", "Play", "Options", "About", "Quit"};
  texts.resize(5);
  coords = {{590, 40}, {610, 191}, {590, 282}, {600, 370}, {623, 457}};
  sizes = {20, 28, 24, 24, 24};

  for (std::size_t i{}; i < texts.size(); ++i) {
    texts[i].setFont(*font);
    texts[i].setString(options[i]);
    texts[i].setCharacterSize(sizes[i]);
    texts[i].setOutlineColor(sf::Color::Black);
    texts[i].setPosition(coords[i]);
  }
  texts[1].setOutlineThickness(4);
  pos = 1;

  winclose->setSize(sf::Vector2f(23, 26));
  winclose->setPosition(1178, 39);
  winclose->setFillColor(sf::Color::Transparent);
}

void MainMenu::loop_events() {
  sf::Event event;
  while (window->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window->close();
    }

    pos_mouse = sf::Mouse::getPosition(*window);
    // mouse_coord = window->mapPixelToCoords(pos_mouse);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed) {
      if (pos < 4) {
        ++pos;
        pressed = true;
        texts[pos].setOutlineThickness(4);
        texts[pos - 1].setOutlineThickness(0);
        pressed = false;
        theselect = false;
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed) {
      if (pos > 1) {
        --pos;
        pressed = true;
        texts[pos].setOutlineThickness(4);
        texts[pos + 1].setOutlineThickness(0);
        pressed = false;
        theselect = false;
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect) {
      theselect = true;
      if (pos == 4) {
        window->close();
      }
      std::cout << options[pos] << '\n';
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (winclose->getGlobalBounds().contains(mouse_coord)) {
        // std::cout << "Close the window!" << '\n';
        window->close();
      }
    }
  }
}

void MainMenu::draw_all() {
  /* window->clear();
  window->draw(*bg);
  for (auto t : texts) {
    window->draw(t);
  } */
  window->display();
}

void MainMenu::run_main_menu() {
  while (window->isOpen()) {
    loop_events();
    draw_all();
  }
}