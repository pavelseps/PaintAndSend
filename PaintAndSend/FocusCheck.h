#include <vector>

#pragma once
template <class T>
class FocusCheck
{
	std::vector<T*> vec;

public:
	FocusCheck() {

	}
	~FocusCheck() {

	}

	void setTextInput(T* ti) {
		vec.push_back(ti);
	}

	T* checkFocus(int mouseX, int mouseY) {
		for (int i = 0; i < vec.size(); i++) {
			if (vec[i]->isFocused(mouseX, mouseY))
				return vec[i];
		}

		return nullptr;
	}
};

