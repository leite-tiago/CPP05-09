/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:45:15 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/05 20:20:04 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : _name("Default"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150), _target("default") {}

AForm::AForm(std::string const &name, int gradeToSign, int gradeToExecute, std::string const &target)
    : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute), _target(target)
{
    if (gradeToSign < MAX_GRADE || gradeToExecute < MAX_GRADE)
        throw GradeTooHighException();
    if (gradeToSign > MIN_GRADE || gradeToExecute > MIN_GRADE)
        throw GradeTooLowException();
}

AForm::AForm(AForm const &other)
    : _name(other._name), _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute), _target(other._target)
{}

AForm &AForm::operator=(AForm const &other)
{
    if (this != &other) {
        _isSigned = other._isSigned;
        _target = other._target; // target can be reassigned logically
    }
    return *this;
}

AForm::~AForm() {}

std::string const &AForm::getName() const { return _name; }
bool AForm::getIsSigned() const { return _isSigned; }
int  AForm::getGradeToSign() const { return _gradeToSign; }
int  AForm::getGradeToExecute() const { return _gradeToExecute; }
const std::string &AForm::getTarget() const { return _target; }

void AForm::beSigned(Bureaucrat const &bureaucrat)
{
    if (bureaucrat.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _isSigned = true;
}

void AForm::execute(Bureaucrat const &executor) const
{
    if (!_isSigned)
        throw NotSignedException();
    if (executor.getGrade() > _gradeToExecute)
        throw GradeTooLowException();
    performAction();
}

const char* AForm::GradeTooHighException::what() const throw() { return "Grade too high!"; }
const char* AForm::GradeTooLowException::what() const throw() { return "Grade too low!"; }
const char* AForm::NotSignedException::what() const throw() { return "Form not signed!"; }

std::ostream &operator<<(std::ostream &os, AForm const &form)
{
    os << "Form '" << form.getName() << "' (sign grade " << form.getGradeToSign()
       << ", exec grade " << form.getGradeToExecute() << ", signed: "
       << (form.getIsSigned() ? "yes" : "no") << ")";
    return os;
}
