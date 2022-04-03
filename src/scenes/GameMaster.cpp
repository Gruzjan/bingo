#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>
#include <smk/Rectangle.hpp>
#include <smk/Vertex.hpp>
#include <smk/VertexArray.hpp>
#include <smk/Text.hpp>

#include "headers/GameMaster.hpp"
#include "headers/Button.hpp"
#include "headers/SceneManager.hpp"

#include <iostream>
#include <map>
#include <string>
#include <locale>
#include <codecvt>
#include <algorithm>

GameMaster::GameMaster(smk::Window &window) : window(window) {
  this->inputBox = new InputBox(500, 150, 800, 50, window, 48);
  inputBox->setColor(smk::Color::RGB(0.6, 0.4, 0.6));
  page = 0;
  words = 
  { {"Krzesla", 0}
  , {"Dzieci", 0}
  , {"Slychac klucze", 0}
  , {"Panie technik", 0}
  , {"Zapowiedzial kartkowke", 0}
  , {"Film", 0}
  , {"Nie psuj mi...", 0}
  , {"Mazak nie dziala", 0}
  , {"Gracjanek", 0}
  , {"Wlochaty", 0}
  , {"Miki", 0}
  , {"Puszcza muzyke w tle", 0}
  , {"Problem z pendrivem", 0}
  , {"Bawi sie w wychowawce", 0}
  , {"Grzybowski incydent", 0}
  , {"Grzybowski incydent v2", 0}
  };
  for (const auto &key : words) {
      wordKeys.push_back(key.first);
  }
}

std::vector<std::string> pagination(
    std::vector<std::string> vec, 
    int i, 
    std::string filter
) {
    std::vector<std::string> filteredItems;
    for (auto x : vec) {
        // So much hussle for lowercasing string...
        std::string lowerStr = x;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        std::string lowerFilter = filter;
        std::transform(lowerFilter.begin(), lowerFilter.end(), lowerFilter.begin(), ::tolower);

        if (lowerStr.find(lowerFilter) != std::string::npos) {
            filteredItems.push_back(x);
        }
    }

    int steps = 5;
    int begin = 0 + (steps * i);
    int end = 0 + (steps * (i + 1));

    if (end < (int)filteredItems.size()) 
        return std::vector<std::string>(
            filteredItems.begin() + begin, filteredItems.begin() + end);

    return std::vector<std::string>(filteredItems.begin() + begin, filteredItems.end());
}

void GameMaster::draw() {
    //====== SCENE TITLE ======
    smk::Text sceneTitle = smk::Text(font, "Game Master");
    sceneTitle.SetPosition(window.width() / 2 - 110, 30);
    sceneTitle.SetColor(smk::Color::Red);
    window.Draw(sceneTitle);

    //====== MAIN BOX ======
    Button box(500, 200, 1000, 800, window);
    box.draw();

    //====== WORDLIST GEN ======
    int i = 1; // Sorry for that...
    std::vector<std::string> paginatedVector = 
        pagination(wordKeys, page, inputBox->getInputString());

    for (auto key : paginatedVector) {
        std::map<std::string, bool>::iterator it = words.find(key); 
        Button word(500, 100 + (150 * i), 1000, 100, window);

        if (it->second) word.setColor(smk::Color::Green);
        else word.setColor(smk::Color::Red);

        word.onClick([&] {
            it->second = !it->second;
        });

        smk::Text caption = smk::Text(font, key);
        caption.SetPosition(word.getX(), word.getY());

        word.draw();
        window.Draw(caption);
        i++; 
    }

    //====== NAVIGATION ======
    if (page > 0) {
        Button backBtn(500, 1000, 100, 100, window);
        backBtn.setColor(smk::Color::Cyan);
        backBtn.onClick([&] {
            page--;
        });

        smk::Text caption = smk::Text(font, "<-");
        caption.SetPosition(backBtn.getX(), backBtn.getY());
        caption.SetColor(smk::Color::Black);

        backBtn.draw();
        window.Draw(caption);
    }
    if ((page + 1) * 5 < (int)wordKeys.size()) {
        Button nextBtn(1400, 1000, 100, 100, window);
        nextBtn.setColor(smk::Color::Cyan);
        nextBtn.onClick([&] {
            page++;
        });

        smk::Text caption = smk::Text(font, "->");
        caption.SetPosition(nextBtn.getX(), nextBtn.getY());
        caption.SetColor(smk::Color::Black);

        nextBtn.draw();
        window.Draw(caption);
    }
    smk::Text pageNumber = smk::Text(
        font, 
        std::to_string(page + 1) 
        + " from " 
        + std::to_string((int(wordKeys.size()) / 5) + 1)
    );
    pageNumber.SetPosition(950, 1000);
    window.Draw(pageNumber);

    //====== NAVIGATION ======
    Button menuBtn(0, 0, 100, 70, window);
    menuBtn.setColor(smk::Color::Cyan);
    menuBtn.onClick([&] {
        SceneManager::updateName("GameMenuScene");
    });
    smk::Text backText = smk::Text(font, "|<-");
    backText.SetColor(smk::Color::Black);
    menuBtn.draw();
    window.Draw(backText);

    //====== SEARCH FILTER ======
    inputBox->onClick();
    inputBox->writeListener([&] {
        page = 0;
    });

    //====== CLEAR ======
    Button clearBtn(1300, 150, 200, 50, window);
    clearBtn.setColor(smk::Color::Cyan);
    clearBtn.onClick([&] {
        inputBox->setInputText(L"");
    });

    smk::Text clearText = smk::Text(font, "Clear");
    clearText.SetPosition(clearBtn.getX(), clearBtn.getY());
    clearText.SetColor(smk::Color::Black);

    clearBtn.draw();
    window.Draw(clearText);

    //====== CLEAR ======
    smk::Text codeText = smk::Text(font, "ABCDEF");
    codeText.SetColor(smk::Color::Yellow);
    codeText.SetPosition(120, 10);
    window.Draw(codeText);

    inputBox->drawText();

    // For some reason nothing renders when inputBox
    // is being drawn first
    // Me from the future: 
    // Ok so this happend because "draw" function 
    // implemented some stuff for Game Creation scene
    // which was not present in the current scene
    // Changing that to "drawRaw" to just render UIElement
    inputBox->drawRaw();
}

void GameMaster::restart() {};

std::string GameMaster::getName() {
    return this->name;
}
