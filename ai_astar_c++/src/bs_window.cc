
#include "../include/bs_window.h"

void BsWindow::init(const unsigned int width, const unsigned int height, const std::string &title) {
  window_.create(sf::VideoMode(width, height), title);
}

void BsWindow::frame() {
  window_.display();
}

bool BsWindow::isOpened() {
  return window_.isOpen();
}

void BsWindow::destroy() {
  window_.close();
}

void BsWindow::clear() {
  window_.clear();
}

const unsigned int BsWindow::height() {
  return window_.getSize().y;
}

const unsigned int BsWindow::width() {
  return window_.getSize().x;
}

void BsWindow::setFramerateLimit(const unsigned int limit) {
  window_.setFramerateLimit(limit);
}

void BsWindow::setMouseVisibility(bool visible) {
  window_.setMouseCursorVisible(visible);
}
