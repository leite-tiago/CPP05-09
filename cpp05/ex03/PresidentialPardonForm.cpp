/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:56:54 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/05 22:19:27 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"
#include <iostream>

PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialPardon", 25, 5, "default") {}
PresidentialPardonForm::PresidentialPardonForm(std::string const &target) : AForm("PresidentialPardon", 25, 5, target) {}
PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &other) : AForm(other) {}
PresidentialPardonForm &PresidentialPardonForm::operator=(PresidentialPardonForm const &other) { AForm::operator=(other); return *this; }
PresidentialPardonForm::~PresidentialPardonForm() {}

void PresidentialPardonForm::performAction() const {
	std::cout << getTarget() << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}

