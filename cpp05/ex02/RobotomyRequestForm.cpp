/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:56:04 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/05 22:19:27 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include <iostream>

RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequest", 72, 45, "default") { std::srand(std::time(NULL)); }
RobotomyRequestForm::RobotomyRequestForm(std::string const &target) : AForm("RobotomyRequest", 72, 45, target) { std::srand(std::time(NULL)); }
RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &other) : AForm(other) { std::srand(std::time(NULL)); }
RobotomyRequestForm &RobotomyRequestForm::operator=(RobotomyRequestForm const &other) { AForm::operator=(other); return *this; }
RobotomyRequestForm::~RobotomyRequestForm() {}

void RobotomyRequestForm::performAction() const {
	std::cout << "* drilling noises *" << std::endl;
	if (std::rand() % 2)
		std::cout << getTarget() << " has been robotomized successfully!" << std::endl;
	else
		std::cout << "Robotomy failed on " << getTarget() << "..." << std::endl;
}

