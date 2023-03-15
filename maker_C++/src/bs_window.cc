
/**
 * Author: Borja Serrano <serranoga@esat-alumni.com>
 * Filename: bs_backgorund.cc
 *
 * Implementation: background class
 */

#include <esat/window.h>
#include <esat/time.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/time.h>
#include <esat/sprite.h>

#include <stdio.h>

#include "bs_window.h"

void bsWindow::init(unsigned int width, unsigned int height) {
  esat::WindowInit(width, height);
}

void bsWindow::frame() {
  esat::WindowFrame();
}

bool bsWindow::isOpened() {
  return esat::WindowIsOpened();
}

unsigned int bsWindow::height() {
  return esat::WindowHeight();
}

unsigned int bsWindow::width() {
  return esat::WindowWidth();
}

void bsWindow::setMouseVisibility(bool visible) {
  esat::WindowSetMouseVisibility(visible);
}
