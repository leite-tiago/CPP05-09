#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <exception>
# include <algorithm>
# include <limits>

class Span
{
	private:
		unsigned int _maxSize;
		std::vector<int> _numbers;

	public:
		// Orthodox Canonical Form
		Span();
		Span(unsigned int n);
		Span(const Span& other);
		Span& operator=(const Span& other);
		~Span();

		// Member functions
		void addNumber(int number);
		int shortestSpan() const;
		int longestSpan() const;

		// Template member function to add range of iterators
		template <typename Iterator>
		void addRange(Iterator begin, Iterator end)
		{
			while (begin != end)
			{
				addNumber(*begin);
				++begin;
			}
		}

		// Exceptions
		class SpanFullException : public std::exception
		{
			public:
				virtual const char* what() const throw()
				{
					return "Span is full, cannot add more numbers";
				}
		};

		class NoSpanException : public std::exception
		{
			public:
				virtual const char* what() const throw()
				{
					return "Not enough numbers to calculate span";
				}
		};
};

#endif
