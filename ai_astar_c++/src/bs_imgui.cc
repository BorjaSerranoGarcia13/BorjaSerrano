#include "../include/bs_imgui.h"

BsImgui::BsImgui() {
	enabled_ = 1;
}

BsImgui::~BsImgui() {

}

void BsImgui::init(sf::RenderWindow& window) {
	ImGui::SFML::Init(window);
}

void BsImgui::event(sf::Event event) {
	ImGui::SFML::ProcessEvent(event);
}

void BsImgui::update(sf::RenderWindow& window, sf::Clock clock) {
	ImGui::SFML::Update(window, clock.restart());
}

void BsImgui::end(sf::RenderWindow& window) {
	ImGui::End();
	ImGui::SFML::Render(window);
}

