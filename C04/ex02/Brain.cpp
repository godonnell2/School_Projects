#include "Brain.hpp"
#include <iostream>

Brain::Brain() {
	std::cout << "Brain Default constructor called." << std::endl;
	for (int i = 0; i < 100; i++)
		ideas[i] = "Empty idea";
}

Brain::Brain(const Brain& other) {
	std::cout << "Brain Copy constructor called." << std::endl;
	for (int i = 0; i < 100; i++)
		ideas[i] = other.ideas[i];
}

Brain& Brain::operator=(const Brain& other) {
	std::cout << "Brain Assignment operator called." << std::endl;
	if (this != &other) {
		for (int i = 0; i < 100; i++)
			ideas[i] = other.ideas[i];
	}
	return *this;
}

Brain::~Brain() {
	std::cout << "Brain Destructor called." << std::endl;
}

void Brain::setIdea(int index, const std::string& idea) {
	if (index >= 0 && index < 100)
		ideas[index] = idea;
}

std::string Brain::getIdea(int index) const {
	if (index >= 0 && index < 100)
		return ideas[index];
	return "Invalid index";
}