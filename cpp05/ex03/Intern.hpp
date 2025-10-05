/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:40:00 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/05 22:30:38 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>

class AForm;

class Intern {
	public:
		Intern();
		Intern(Intern const &other);
		Intern &operator=(Intern const &other);
		~Intern();

		AForm *makeForm(std::string const &formName, std::string const &target) const;

		class UnknownFormException : public std::exception {
			public:
				const char *what() const throw();
		};
};

