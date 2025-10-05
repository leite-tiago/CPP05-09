/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:40:05 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/05 22:30:38 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern() {}
Intern::Intern(Intern const &other) { (void)other; }
Intern &Intern::operator=(Intern const &other) { (void)other; return *this; }
Intern::~Intern() {}

const char *Intern::UnknownFormException::what() const throw() { return "Intern: unknown form name"; }

typedef AForm *(Intern::*Creator)(std::string const &target) const;

namespace {
	struct FormEntry { const char *name; AForm *(*create)(std::string const &target); };

	AForm *createShrub(std::string const &target) { return new ShrubberyCreationForm(target); }
	AForm *createRobo(std::string const &target) { return new RobotomyRequestForm(target); }
	AForm *createPardon(std::string const &target) { return new PresidentialPardonForm(target); }

	const FormEntry entries[] = {
		{"shrubbery creation", &createShrub},
		{"robotomy request", &createRobo},
		{"presidential pardon", &createPardon}
	};
	const size_t entryCount = sizeof(entries)/sizeof(entries[0]);
}

AForm *Intern::makeForm(std::string const &formName, std::string const &target) const {
	for (size_t i = 0; i < entryCount; ++i) {
		if (formName == entries[i].name) {
			AForm *f = entries[i].create(target);
			std::cout << "Intern creates " << f->getName() << std::endl;
			return f;
		}
	}
	std::cout << "Intern cannot create form: '" << formName << "' (unknown)" << std::endl;
	throw UnknownFormException();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:21:53 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/05 22:21:54 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

