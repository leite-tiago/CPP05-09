/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:55:46 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/05 22:19:27 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <iostream>

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreation", 145, 137, "default") {}
ShrubberyCreationForm::ShrubberyCreationForm(std::string const &target)
	: AForm("ShrubberyCreation", 145, 137, target) {}
ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &other) : AForm(other) {}
ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &other) { AForm::operator=(other); return *this; }
ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::performAction() const {
	std::ofstream ofs((getTarget() + "_shrubbery").c_str());
	if (!ofs.is_open()) {
		std::cerr << "Failed to create shrubbery file" << std::endl;
		return;
	}
	ofs << "      /\\n";
	ofs << "     /  \\\n";
	ofs << "    /++++\\n";
	ofs << "   /  ()  \\\n";
	ofs << "  /__----__\\n";
	ofs << "     ||||\n";
	ofs << "     ||||\n";
	ofs.close();
}

