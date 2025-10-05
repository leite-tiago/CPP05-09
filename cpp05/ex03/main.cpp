/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 21:08:33 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/05 22:30:38 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include <iostream>
#include <string>
#include <sstream>
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

static void printResult(const std::string &name, bool pass, const std::string &detail = "")
{
    std::cout << (pass ? "[OK]   " : "[FAIL] ") << name;
    if (!pass && !detail.empty())
        std::cout << " -> " << detail;
    std::cout << std::endl;
}

int main() {
    int total = 0;
    int passed = 0;
    const std::string HIGH_MSG = "Grade too high!";
    const std::string LOW_MSG  = "Grade too low!";

    // 1: Shrubbery ctor
    ++total; {
        try { ShrubberyCreationForm f("home"); bool ok = f.getGradeToSign()==145 && f.getGradeToExecute()==137 && !f.getIsSigned(); if (ok) ++passed; printResult("ShrubberyCtor", ok); }
        catch (std::exception &e) { printResult("ShrubberyCtor", false, e.what()); }
    }
    // 2: Robotomy ctor
    ++total; {
        try { RobotomyRequestForm f("Bender"); bool ok = f.getGradeToSign()==72 && f.getGradeToExecute()==45 && !f.getIsSigned(); if (ok) ++passed; printResult("RobotomyCtor", ok); }
        catch (std::exception &e) { printResult("RobotomyCtor", false, e.what()); }
    }
    // 3: Presidential ctor
    ++total; {
        try { PresidentialPardonForm f("Arthur Dent"); bool ok = f.getGradeToSign()==25 && f.getGradeToExecute()==5 && !f.getIsSigned(); if (ok) ++passed; printResult("PresidentialCtor", ok); }
        catch (std::exception &e) { printResult("PresidentialCtor", false, e.what()); }
    }
    // 4: beSigned success
    ++total; {
        try { Bureaucrat b("Signer", 50); RobotomyRequestForm f("Marvin"); while (b.getGrade() > f.getGradeToSign()) b.incrementGrade(); f.beSigned(b); bool ok = f.getIsSigned(); if (ok) ++passed; printResult("RobotomyBeSignedSuccess", ok); }
        catch (std::exception &e) { printResult("RobotomyBeSignedSuccess", false, e.what()); }
    }
    // 5: beSigned fail (Presidential needs 25)
    ++total; {
        try { Bureaucrat b("LowGrade", 50); PresidentialPardonForm f("Ford Prefect"); f.beSigned(b); printResult("PresidentialBeSignedFail", false, "No exception"); }
        catch (std::exception &e) { bool ok = std::string(e.what()) == LOW_MSG; if (ok) ++passed; printResult("PresidentialBeSignedFail", ok, e.what()); }
    }
    // 6: signForm wrapper success (Shrubbery needs 145) bureaucrat 100 ok
    ++total; {
        try { Bureaucrat b("Wrapper", 100); ShrubberyCreationForm f("garden"); b.signForm(f); bool ok = f.getIsSigned(); if (ok) ++passed; printResult("ShrubberySignSuccess", ok); }
        catch (std::exception &e) { printResult("ShrubberySignSuccess", false, e.what()); }
    }
    // 7: signForm wrapper fail (Robotomy needs 72; bureaucrat 100)
    ++total; {
        try { Bureaucrat b("WrapperLow", 100); RobotomyRequestForm f("HAL9000"); b.signForm(f); bool ok = !f.getIsSigned(); if (ok) ++passed; printResult("RobotomySignFail", ok); }
        catch (std::exception &e) { printResult("RobotomySignFail", false, e.what()); }
    }
    // 8: Execute success (Shrubbery)
    ++total; {
        try { Bureaucrat exec("ExecGuy", 100); ShrubberyCreationForm f("yard"); exec.signForm(f); exec.executeForm(f); bool ok = f.getIsSigned(); if (ok) ++passed; printResult("ShrubberyExecuteSuccess", ok); }
        catch (std::exception &e) { printResult("ShrubberyExecuteSuccess", false, e.what()); }
    }
    // 9: Execute fail (not signed) using direct execute to capture exception
    ++total; {
        try { Bureaucrat exec("ExecGuy2", 1); PresidentialPardonForm f("Trillian"); f.execute(exec); printResult("ExecuteNotSignedFail", false, "No exception"); }
        catch (std::exception &e) { bool ok = std::string(e.what()) == "Form not signed!"; if (ok) ++passed; printResult("ExecuteNotSignedFail", ok, e.what()); }
    }
    // 10: Execute fail (low grade) using direct execute
    ++total; {
        try { Bureaucrat low("LowExec", 100); RobotomyRequestForm f("R2D2"); Bureaucrat high("High", 40); high.signForm(f); f.execute(low); printResult("ExecuteLowGradeFail", false, "No exception"); }
        catch (std::exception &e) { bool ok = std::string(e.what()) == LOW_MSG; if (ok) ++passed; printResult("ExecuteLowGradeFail", ok, e.what()); }
    }
    // 11: operator<< works
    ++total; {
        try { ShrubberyCreationForm f("park"); Bureaucrat b("Signer2", 100); b.signForm(f); std::ostringstream oss; oss << f; std::string expected = "Form 'ShrubberyCreation' (sign grade 145, exec grade 137, signed: yes)"; bool ok = (oss.str() == expected); if (ok) ++passed; printResult("FormOstreamOperator", ok, oss.str()); }
        catch (std::exception &e) { printResult("FormOstreamOperator", false, e.what()); }
    }

    // 12: Intern creates robotomy
    ++total; {
        try { Intern intern; AForm *f = intern.makeForm("robotomy request", "Bender"); bool ok = f && f->getGradeToSign()==72; if (ok) ++passed; printResult("InternCreateRobotomy", ok); delete f; }
        catch (std::exception &e) { printResult("InternCreateRobotomy", false, e.what()); }
    }
    // 13: Intern creates shrubbery
    ++total; {
        try { Intern intern; AForm *f = intern.makeForm("shrubbery creation", "garden" ); bool ok = f && f->getGradeToExecute()==137; if (ok) ++passed; printResult("InternCreateShrubbery", ok); delete f; }
        catch (std::exception &e) { printResult("InternCreateShrubbery", false, e.what()); }
    }
    // 14: Intern creates pardon
    ++total; {
        try { Intern intern; AForm *f = intern.makeForm("presidential pardon", "Arthur Dent" ); bool ok = f && f->getGradeToSign()==25; if (ok) ++passed; printResult("InternCreatePardon", ok); delete f; }
        catch (std::exception &e) { printResult("InternCreatePardon", false, e.what()); }
    }
    // 15: Intern unknown form
    ++total; {
        try { Intern intern; AForm *f = intern.makeForm("coffee request", "Me" ); (void)f; printResult("InternCreateUnknown", false, "No exception"); }
        catch (std::exception &e) { bool ok = std::string(e.what()) == "Intern: unknown form name"; if (ok) ++passed; printResult("InternCreateUnknown", ok, e.what()); }
    }

    std::cout << "==============================" << std::endl;
    std::cout << "Passed " << passed << "/" << total << " tests" << std::endl;
    std::cout << "==============================" << std::endl;
    return (passed == total) ? 0 : 1;
}
