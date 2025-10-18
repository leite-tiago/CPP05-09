# 📚 C++ Module 08 - Guia de Defesa

## 🎯 Visão Geral do Projeto

Este módulo foca em **Templates, Containers STL, Iterators e Algorithms**. O objetivo é aprender a usar a Standard Template Library (STL) do C++ de forma eficiente.

---

## 📋 Estrutura do Projeto

```
cpp08/
├── ex00/  # Easy find - Template function com STL algorithm
├── ex01/  # Span - Classe que calcula spans usando STL
└── ex02/  # MutantStack - Stack iterável
```

---

## 🔍 Exercise 00: Easy find

### Conceitos-Chave

#### **Template Functions**
- Permite criar funções genéricas que funcionam com diferentes tipos
- Definido com `template <typename T>`
- O compilador gera código específico para cada tipo usado

#### **STL Algorithms**
- `std::find()` - Procura elemento em container
- Retorna iterador para o elemento ou `end()` se não encontrado
- Include: `<algorithm>`

### Implementação

```cpp
template <typename T>
typename T::iterator easyfind(T& container, int value)
{
    typename T::iterator it = std::find(container.begin(), container.end(), value);

    if (it == container.end())
        throw NotFoundException();

    return it;
}
```

### Perguntas Esperadas

**P: Por que usar `typename T::iterator`?**
- R: `typename` é necessário para informar ao compilador que `T::iterator` é um tipo, não uma variável estática.

**P: Por que não fazer busca manual?**
- R: O subject exige uso de STL algorithms. `std::find` é otimizado e testado.

**P: Funciona com que containers?**
- R: Todos os containers sequenciais: `vector`, `list`, `deque`, etc. Não funciona com associativos (map, set).

**P: Por que não funciona com containers associativos?**
- R: O subject especifica "you don't have to handle associative containers". Além disso, containers associativos têm formas próprias de busca (`.find()` member function).

---

## 📊 Exercise 01: Span

### Conceitos-Chave

#### **STL Containers**
- `std::vector<int>` - Container dinâmico para armazenar inteiros
- `.push_back()` - Adiciona elemento
- `.size()` - Retorna quantidade de elementos

#### **STL Algorithms Usados**
1. `std::sort()` - Ordena container
2. `std::min_element()` - Encontra menor elemento
3. `std::max_element()` - Encontra maior elemento

### Implementação

#### shortestSpan()
```cpp
int Span::shortestSpan() const
{
    if (_numbers.size() < 2)
        throw NoSpanException();

    std::vector<int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end());

    int minSpan = std::numeric_limits<int>::max();

    for (size_t i = 1; i < sorted.size(); ++i)
    {
        int span = sorted[i] - sorted[i - 1];
        if (span < minSpan)
            minSpan = span;
    }

    return minSpan;
}
```

#### longestSpan()
```cpp
int Span::longestSpan() const
{
    if (_numbers.size() < 2)
        throw NoSpanException();

    int min = *std::min_element(_numbers.begin(), _numbers.end());
    int max = *std::max_element(_numbers.begin(), _numbers.end());

    return max - min;
}
```

#### addRange()
```cpp
template <typename Iterator>
void addRange(Iterator begin, Iterator end)
{
    while (begin != end)
    {
        addNumber(*begin);
        ++begin;
    }
}
```

### Perguntas Esperadas

**P: Por que não apenas subtrair os dois menores números para shortestSpan()?**
- R: Exemplo: [1, 5, 6, 100]. Os dois menores são 1 e 5 (span=4), mas o shortest span real é entre 5 e 6 (span=1). É necessário ordenar e verificar TODOS os pares adjacentes.

**P: Complexidade de shortestSpan vs longestSpan?**
- R:
  - `shortestSpan()`: O(n log n) devido ao sort
  - `longestSpan()`: O(n) - apenas duas passagens lineares

**P: Por que usar template para addRange()?**
- R: Para aceitar qualquer tipo de iterador (vector::iterator, list::iterator, ponteiros, etc).

**P: O que é Orthodox Canonical Form?**
- R: É a forma canônica ortodoxa em C++. Toda classe deve ter:
  1. Construtor padrão
  2. Construtor de cópia
  3. Operador de atribuição
  4. Destrutor

**P: Por que testar com 10,000+ números?**
- R: O subject exige. Testa performance e garante que o código escala bem.

---

## 🧬 Exercise 02: Mutated abomination

### Conceitos-Chave

#### **Herança de std::stack**
- `std::stack` é um container adapter
- Usa internamente um container (default: `std::deque`)
- Membro protegido `c` contém o container interno

#### **Iterators**
- Ponteiros generalizados para elementos em containers
- `begin()` - Primeiro elemento
- `end()` - Posição após último elemento
- `rbegin()` / `rend()` - Iteração reversa

### Implementação

```cpp
template <typename T>
class MutantStack : public std::stack<T>
{
public:
    typedef typename std::stack<T>::container_type::iterator iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;
    typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
    typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;

    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }

    const_iterator begin() const { return this->c.begin(); }
    const_iterator end() const { return this->c.end(); }

    reverse_iterator rbegin() { return this->c.rbegin(); }
    reverse_iterator rend() { return this->c.rend(); }

    const_reverse_iterator rbegin() const { return this->c.rbegin(); }
    const_reverse_iterator rend() const { return this->c.rend(); }
};
```

### Perguntas Esperadas

**P: O que é `this->c`?**
- R: `c` é o membro protegido de `std::stack` que contém o container interno (por default, `std::deque`).

**P: Por que std::stack não tem iteradores?**
- R: Design decision. Stack é um LIFO (Last In First Out). Ter iteradores violaria o conceito de stack, permitindo acesso a elementos do meio.

**P: O que significa "mutated abomination"?**
- R: É uma "mutação" do stack original. Uma "abominação" porque quebra o conceito puro de stack ao adicionar iteradores.

**P: Por que funciona converter para std::stack?**
```cpp
std::stack<int> s(mstack);
```
- R: MutantStack herda de std::stack, então pode ser usado como stack normal através de herança.

**P: Qual a diferença entre iterator e const_iterator?**
- R:
  - `iterator` - Permite modificar elementos (`*it = 42`)
  - `const_iterator` - Apenas leitura, não permite modificação

**P: O que é reverse_iterator?**
- R: Iterador que percorre o container na ordem inversa. `rbegin()` aponta para o último elemento, `rend()` para antes do primeiro.

**P: Por que typedef typename?**
- R: `typename` diz ao compilador que o que segue é um tipo dependente do template. `typedef` cria um alias para facilitar uso.

---

## 🛠️ Comandos de Compilação e Teste

### Compilação
```bash
# Ex00
cd ex00 && make
./easyfind

# Ex01
cd ex01 && make
./span

# Ex02
cd ex02 && make
./mutantstack
```

### Verificar Memory Leaks
```bash
# Ex00
leaks -atExit -- ./easyfind

# Ex01
leaks -atExit -- ./span

# Ex02
leaks -atExit -- ./mutantstack
```

**Resultado esperado:** `0 leaks for 0 total leaked bytes`

### Limpar
```bash
make fclean
```

---

## 🔑 Conceitos Importantes STL

### Containers

#### **Sequence Containers**
- `vector` - Array dinâmico, acesso rápido por índice
- `list` - Lista duplamente ligada, inserção/remoção rápida
- `deque` - Double-ended queue, rápido nas extremidades

#### **Container Adapters**
- `stack` - LIFO (Last In First Out)
- `queue` - FIFO (First In First Out)
- `priority_queue` - Fila com prioridade

#### **Associative Containers** (não usar em ex00)
- `map` - Pares chave-valor ordenados
- `set` - Conjunto ordenado de elementos únicos

### Iterators

```cpp
// Forward iteration
for (container::iterator it = cont.begin(); it != cont.end(); ++it)
    std::cout << *it << std::endl;

// Reverse iteration
for (container::reverse_iterator it = cont.rbegin(); it != cont.rend(); ++it)
    std::cout << *it << std::endl;
```

### Algorithms Comuns

```cpp
#include <algorithm>

std::find(begin, end, value);           // Busca elemento
std::sort(begin, end);                  // Ordena
std::min_element(begin, end);           // Encontra mínimo
std::max_element(begin, end);           // Encontra máximo
std::count(begin, end, value);          // Conta ocorrências
std::copy(begin, end, dest);            // Copia elementos
std::fill(begin, end, value);           // Preenche com valor
```

---

## ⚠️ Erros Comuns a Evitar

### 1. **Esquecer typename em templates**
```cpp
// ❌ ERRADO
template <typename T>
T::iterator func(T& container);

// ✅ CORRETO
template <typename T>
typename T::iterator func(T& container);
```

### 2. **Implementar funções em header sem template**
```cpp
// ❌ ERRADO (em .hpp sem ser template)
int calculate() { return 42; }

// ✅ CORRETO (em .cpp)
// OU como template no .hpp
```

### 3. **Busca manual em vez de STL algorithm**
```cpp
// ❌ ERRADO para ex00
for (typename T::iterator it = cont.begin(); it != cont.end(); ++it)
    if (*it == value) return it;

// ✅ CORRETO
return std::find(cont.begin(), cont.end(), value);
```

### 4. **shortestSpan incorreto**
```cpp
// ❌ ERRADO
int min1 = *std::min_element(...);
int min2 = *std::min_element(...); // Como pegar o segundo menor?
return min2 - min1;

// ✅ CORRETO
std::sort(sorted.begin(), sorted.end());
// Verificar TODOS os spans adjacentes
```

---

## 📝 Checklist de Defesa

### Antes da Defesa
- [ ] Todos os exercícios compilam sem warnings
- [ ] Sem memory leaks (testado com leaks/valgrind)
- [ ] Sem uso de "using namespace"
- [ ] Sem uso de funções proibidas (printf, alloc, free)
- [ ] Orthodox Canonical Form implementado (ex01, ex02)
- [ ] Usa STL algorithms apropriadamente

### Durante a Defesa

#### **Ex00**
- [ ] Explica o que são templates
- [ ] Explica por que usar std::find
- [ ] Demonstra funcionamento com diferentes containers
- [ ] Explica tratamento de erros (exception)

#### **Ex01**
- [ ] Explica Orthodox Canonical Form
- [ ] Explica diferença entre shortestSpan e longestSpan
- [ ] Demonstra addRange com iteradores
- [ ] Explica por que precisa ordenar para shortestSpan

#### **Ex02**
- [ ] Explica herança de std::stack
- [ ] Explica o que é `this->c`
- [ ] Demonstra uso de iteradores
- [ ] Compara comportamento com std::list

---

## 💡 Dicas para Modificações Durante Defesa

Se pedirem modificação, possíveis requests:

### Ex00: "Adicione suporte para buscar último elemento"
```cpp
template <typename T>
typename T::iterator easyfind_last(T& container, int value)
{
    typename T::reverse_iterator rit = std::find(
        container.rbegin(), container.rend(), value);

    if (rit == container.rend())
        throw NotFoundException();

    // Converter reverse_iterator para iterator
    return (++rit).base();
}
```

### Ex01: "Adicione método para obter mediana"
```cpp
int Span::median() const
{
    if (_numbers.empty())
        throw NoSpanException();

    std::vector<int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end());

    size_t mid = sorted.size() / 2;
    return sorted[mid];
}
```

### Ex02: "Adicione método para limpar stack mantendo primeiro elemento"
```cpp
void keepFirst()
{
    if (this->empty())
        return;

    T first = this->top();
    while (!this->empty())
        this->pop();
    this->push(first);
}
```

---

## 🎓 Recursos Adicionais

### Documentação
- [cppreference.com](https://en.cppreference.com/) - Referência completa C++
- [cplusplus.com](https://cplusplus.com/) - Tutoriais e exemplos

### Conceitos para Estudar
- **Templates**: Programação genérica
- **STL**: Standard Template Library
- **Iterators**: Padrão de design Iterator
- **RAII**: Resource Acquisition Is Initialization
- **Orthodox Canonical Form**: Regra dos 4 (C++98)

---

## ✅ Resultado Esperado

**Compilação:**
```bash
c++ -Wall -Wextra -Werror -std=c++98 ...
# 0 warnings, 0 errors
```

**Memory Leaks:**
```bash
Process XXXXX: 0 leaks for 0 total leaked bytes.
```

**Testes:**
- Ex00: Busca funciona em vector, list, deque
- Ex01: shortestSpan=2, longestSpan=14 (exemplo do subject)
- Ex02: Saída idêntica entre MutantStack e std::list

---

## 🏆 Pontos-Chave para Impressionar

1. **Conhecimento de STL**: Demonstre familiaridade com containers e algorithms
2. **Entenda Trade-offs**: Explique complexidade (O(n) vs O(n log n))
3. **Templates**: Mostre que entende programação genérica
4. **Memory Management**: Enfatize ausência de leaks
5. **Design Patterns**: Mencione Iterator pattern (ex02)

---

## 🚀 Boa Sorte na Defesa!

**Lembre-se:**
- Respire fundo
- Explique seu raciocínio
- Se não souber, admita e tente deduzir
- Demonstre entusiasmo pelo código

**"O código não mente, mas pode ser mal interpretado. Seja claro."**
