/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:57:11 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/05 22:19:27 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "AForm.hpp"

class PresidentialPardonForm : public AForm {
	public:
		PresidentialPardonForm();
		PresidentialPardonForm(std::string const &target);
		PresidentialPardonForm(PresidentialPardonForm const &other);
		PresidentialPardonForm &operator=(PresidentialPardonForm const &other);
		~PresidentialPardonForm();
	private:
		void performAction() const; // prints pardon message
};

