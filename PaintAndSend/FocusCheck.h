#include <vector>

#pragma once
/*Check if is element in this class focused on mouse position and return this element*/
template <class T>
class FocusCheck
{
	std::vector<T*> vec;

public:
	FocusCheck() {

	}
	~FocusCheck() {

	}

	/*Add element to class*/
	void addElement(T* ti) {
		vec.push_back(ti);
	}

	/*Check if is in focus*/
	T* checkFocus(int mouseX, int mouseY) {
		for (int i = 0; i < vec.size(); i++) {
			if (vec[i]->isFocused(mouseX, mouseY))
				return vec[i];
		}

		return nullptr;
	}
};

