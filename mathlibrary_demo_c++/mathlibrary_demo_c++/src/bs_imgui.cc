#include "bs_imgui.h"

BsImgui::BsImgui() {
	enabled_ = 1;

    structure_ = false;
    login_ = false;
    test_int_ = false;
    test_float_ = false;
    test_bool_ = false;

    use_login_ = false;
}

BsImgui::~BsImgui() {

}

void BsImgui::init(sf::RenderWindow& window) {
	ImGui::SFML::Init(window);
}

void BsImgui::event(sf::Event event) {
	ImGui::SFML::ProcessEvent(event);
}

void BsImgui::update(sf::RenderWindow& window, sf::Clock clock, BsDataBase database) {
	ImGui::SFML::Update(window, clock.restart());

    ImGui::Begin("Base Data");
    if (ImGui::MenuItem("STRUCTURE ##1")) {
        if (structure_) {structure_ = false;}
        else { structure_ = true; }
    }
    if (structure_) {
        ImGui::Text("");
        ImGui::Text("Tables: ");
        ImGui::Text("");
        if (ImGui::MenuItem(database.tables[0].c_str())) {
            if (login_) { login_ = false; }
            else { login_ = true; }
        }
        if (login_) {
            ImGui::Text("");
            ImGui::Text(database.table_login.c_str());
            ImGui::Text("");
            for (int i = 0; i < kTotalLogin; ++i) {
                if (database.username_login_[i] != "\0") {
                    ImGui::Text("-- %s", database.username_login_[i].c_str());
                    ImGui::SameLine();
                    ImGui::Text("%s ",database.password_login_[i].c_str());
                    ImGui::Text("");
                }
            }
        }
        ImGui::Text("");
        ImGui::Text("");
        if (ImGui::MenuItem(database.tables[1].c_str())) {
            if (test_int_) { test_int_ = false; }
            else { test_int_ = true; }
        }
        if (test_int_) {
            ImGui::Text("");
            ImGui::Text(database.table_int.c_str());
            ImGui::Text("");
            for (int i = 0; i < 4; ++i) {    
                if (database.test_int[i] != "\0") {
                    ImGui::Text("-- %s",database.test_int[i].c_str());
                    if (i % 2 == 0) { ImGui::SameLine(); }
                    else { ImGui::Text(""); }
                }
            }
        }
        ImGui::Text(""); ImGui::Text("");
        if (ImGui::MenuItem(database.tables[2].c_str())) {
            if (test_float_) { test_float_ = false; }
            else { test_float_ = true; }
        }
        if (test_float_) {
            ImGui::Text("");
            ImGui::Text(database.table_float.c_str());
            ImGui::Text("");
            for (int i = 0; i < kTotalFloat; ++i) {
                if (database.test_float[i] != "\0") {
                    ImGui::Text("-- %s", database.test_float[i].c_str());
                    if (i % 2 == 0) { ImGui::SameLine(); }
                    else { ImGui::Text(""); }
                }
            }
        }
        ImGui::Text(""); ImGui::Text("");
        if (ImGui::MenuItem(database.tables[3].c_str())) {
            if (test_bool_) { test_bool_ = false; }
            else { test_bool_ = true; }
        }        
        if (test_bool_) {
            ImGui::Text("");
            ImGui::Text(database.table_bool.c_str());
            ImGui::Text("");
            for (int i = 0; i < kTotalBool; ++i) {
                if (database.test_bool[i] != "\0") {
                    ImGui::Text("-- %s",database.test_bool[i].c_str());
                    if (i % 2 == 0) { ImGui::SameLine(); }
                    else { ImGui::Text(""); }
                }
            }
        }
        ImGui::Text("");
        ImGui::Text("");
    }

    ImGui::Text("");
    ImGui::Text("");
    if (ImGui::Button("Check Users ##1")) {
        use_login_ = true;
    }
    if (use_login_) {
        ImGui::Text("Login");
        ImGui::InputText("Username##1", &username_, IM_ARRAYSIZE(&username_));
        ImGui::InputText("Password##2", &password_, IM_ARRAYSIZE(&password_));
        if (ImGui::Button(" Check ##1") && username_[0] != '\0') {
            for (int i = 0; i < kTotalLogin; ++i) {
                if (username_ == database.username_login_[i]) {
                    if (password_ == database.password_login_[i]) {
                        logged = "LOGGED";
                    }
                }
            }
        }
        if (ImGui::Button(" Clear Log ##1")) {
            logged = "Not Logged In";
            username_[0] = '\0';
            password_[0] = '\0';
        }
        ImGui::Text("%s", logged.c_str());
        ImGui::Text("");

        ImGui::Text("Sign");
        ImGui::InputText("Username##3", &username_sign_, IM_ARRAYSIZE(&username_sign_));
        ImGui::InputText("Password##4", &password_sign_, IM_ARRAYSIZE(&password_sign_));

        if (BsDataBase::s_total_col_ < kTotalLogin) {
            if (ImGui::Button(" Check ##2")) {
                bool username_exists_ = false;
                for (int i = 0; i < kTotalLogin; ++i) {
                    if (username_sign_ == database.username_login_[i]) {
                        username_exists_ = true;
                        logged2 = "Username invalid";
                    }
                }
                if (username_exists_ == false) {
                    char buffer[200];
                    std::string a = username_sign_;
                    std::string b = password_sign_;
                    std::string database_update = "INSERT INTO Login (Username, Password) VALUES ('" + a + "','" + b + "');";
                    strcpy_s(buffer, sizeof buffer, database_update.c_str());
                    if (a[0] != '\0' && b[0] != '\0') {
                        database.insertData(buffer);
                        username_sign_[0] = '\0';
                        password_sign_[0] = '\0';
                    }
                    logged2 = "Done";
                }
            }
        }
        else {
            if (ImGui::Button(" Login FULL ##1")) {
                logged2 = "Login is full";
            }
        }
        ImGui::Text("%s", logged2.c_str());
    }
}

void BsImgui::end(sf::RenderWindow& window) {
	ImGui::End();
	ImGui::SFML::Render(window);
}

