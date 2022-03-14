#include <iostream>
#pragma once
class Cell
{
private:
	std::string text = "a";
	bool checked = false;
public:
	std::string getText() {
		return text;
	}
	void setText(std::string newText) {
		text = newText;
	}
	void check() {
		checked = !checked;
	}
};
