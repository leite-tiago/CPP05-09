# CPP Module 07 - Guia de Defesa

## 📚 Conceitos Fundamentais

### O que são Templates em C++?
Templates são um mecanismo que permite escrever código genérico que funciona com diferentes tipos de dados. É uma forma de **programação genérica** onde o compilador gera código específico para cada tipo usado.

**Vantagens:**
- Reutilização de código
- Type-safety em tempo de compilação
- Sem overhead de runtime (diferente de polimorfismo)
- Código mais limpo e manutenível

**Sintaxe básica:**
```cpp
template <typename T>
T functionName(T param) {
    // código genérico
}
```

---

## 🎯 Exercise 00: Function Templates

### Implementação
Três templates de função simples:
- **swap**: troca valores de duas variáveis
- **min**: retorna o menor valor (ou o segundo se iguais)
- **max**: retorna o maior valor (ou o segundo se iguais)

### Pontos-chave para defesa:

**1. Por que usar `T const &` no retorno de min/max?**
- Evita cópias desnecessárias (eficiência)
- Permite uso com tipos complexos/grandes
- Mantém const-correctness

**2. Por que retornar o segundo valor se forem iguais?**
- É a especificação do exercício
- Garante comportamento consistente e previsível

**3. Por que templates estão no header?**
- Templates precisam estar visíveis no ponto de instanciação
- O compilador precisa do código completo para gerar as versões específicas
- Exceção: explicit instantiation (não usada aqui)

**4. O que significa `::`?**
- Operador de resolução de escopo
- `::swap` significa usar a função do escopo global (não std::swap)

### Exemplo de uso:
```cpp
int a = 2, b = 3;
::swap(a, b);           // a=3, b=2
::min(a, b);           // retorna 2
::max(a, b);           // retorna 3
```

---

## 🔄 Exercise 01: Iter

### Implementação
Template de função que itera sobre um array aplicando uma função a cada elemento.

```cpp
template <typename T, typename F>
void iter(T* array, size_t length, F func)
```

### Pontos-chave para defesa:

**1. Por que dois parâmetros template (T e F)?**
- **T**: tipo dos elementos do array
- **F**: tipo da função/functor a ser aplicada
- Permite máxima flexibilidade (funções normais, templates, lambdas*)

**2. Como funciona com funções template?**
```cpp
template <typename T>
void print(T const & x) {
    std::cout << x << std::endl;
}

// Uso:
iter(array, length, print<int>);  // instanciação explícita
```

**3. Suporte a const e non-const:**
- Se a função recebe `T&` → pode modificar elementos
- Se a função recebe `T const &` → só leitura
- O template deduz automaticamente

**4. Por que usar `size_t` para length?**
- Tipo padrão para tamanhos em C++
- Garante que é não-negativo
- Compatível com sizeof e arrays

### Casos de uso:
- Aplicar função a todos elementos
- Modificar elementos in-place
- Imprimir/processar arrays genéricos

---

## 📦 Exercise 02: Array Class Template

### Implementação
Classe template que encapsula um array dinâmico com gerenciamento automático de memória.

### Arquitetura:

```cpp
template <typename T>
class Array {
private:
    T* _array;              // ponteiro para array dinâmico
    unsigned int _size;     // tamanho do array

public:
    Array();                           // construtor default
    Array(unsigned int n);             // construtor com tamanho
    Array(Array const & src);          // copy constructor
    ~Array();                          // destrutor
    Array & operator=(Array const &);  // assignment operator
    T & operator[](unsigned int);      // subscript operator
    unsigned int size() const;         // getter de tamanho
};
```

### Pontos-chave para defesa:

**1. Orthodox Canonical Form (OCF)**
As 4 funções obrigatórias:
- **Default constructor**: inicializa array vazio
- **Copy constructor**: cria cópia profunda
- **Assignment operator**: atribui com cópia profunda
- **Destructor**: libera memória com `delete[]`

**2. Por que `new T[n]()`?**
```cpp
_array = new T[n]();
```
- `new T[n]` → aloca array de n elementos
- `()` → inicialização por valor (value-initialization)
- Para tipos primitivos: zero-initialized
- Para classes: construtor default chamado
- **Essencial**: garante estado válido inicial

**3. Deep Copy vs Shallow Copy**

**Shallow Copy (errado):**
```cpp
_array = rhs._array;  // apenas copia ponteiro!
```
- Ambos objetos apontam para mesma memória
- Destruir um invalida o outro
- Double delete → crash

**Deep Copy (correto):**
```cpp
_array = new T[_size];
for (unsigned int i = 0; i < _size; i++)
    _array[i] = rhs._array[i];
```
- Aloca nova memória
- Copia valores elemento por elemento
- Objetos independentes

**4. Operador [] - duas versões**

```cpp
// Non-const: permite leitura E escrita
T & operator[](unsigned int index) {
    if (index >= _size)
        throw std::exception();
    return _array[index];
}

// Const: apenas leitura
T const & operator[](unsigned int index) const {
    if (index >= _size)
        throw std::exception();
    return _array[index];
}
```
- Versão non-const: objetos normais
- Versão const: objetos const (const-correctness)
- Ambas verificam bounds e lançam exceção

**5. Verificação de bounds**
```cpp
if (index >= _size)
    throw std::exception();
```
- Índice negativo: convertido para unsigned grande → pega
- Índice >= size: fora dos limites
- `std::exception`: exceção padrão (pode usar derivadas também)

**6. Gerenciamento de Memória**

**No Assignment Operator:**
```cpp
if (_array != NULL)
    delete[] _array;  // libera memória antiga

_array = new T[_size];  // aloca nova memória
```

**No Destructor:**
```cpp
if (_array != NULL)
    delete[] _array;  // libera memória
```

**⚠️ IMPORTANTE:** Sempre `delete[]` com arrays, não apenas `delete`!

**7. Self-assignment check**
```cpp
if (this != &rhs) {
    // código de atribuição
}
```
- Evita problemas com `a = a`
- Previne delete da própria memória antes de copiar

---

## 🔍 Perguntas Comuns na Defesa

### Gerais sobre Templates

**Q: Quando o código do template é compilado?**
A: No ponto de instanciação. O compilador gera código específico para cada tipo usado.

**Q: Templates causam code bloat?**
A: Podem causar, pois cada tipo gera código separado. Mas o compilador otimiza duplicatas.

**Q: Diferença entre `typename` e `class` em templates?**
A: Nenhuma para declarar parâmetros de template. `typename` é mais moderno e claro.

**Q: Por que não posso colocar implementação em .cpp?**
A: O compilador precisa ver a implementação completa para instanciar o template. Templates devem estar em headers (ou usar explicit instantiation).

### Exercise 00

**Q: Por que usar referências const no retorno?**
A: Eficiência (evita cópias) e permite uso com tipos grandes/complexos.

**Q: E se eu quiser modificar o valor retornado por min/max?**
A: Não pode, retorna const. Se precisar, teria que fazer cast (má prática) ou redesenhar.

### Exercise 01

**Q: Como iter sabe se a função modifica ou não os elementos?**
A: Não sabe. Depende da assinatura da função passada. Template é flexível.

**Q: Funciona com lambdas do C++11?**
A: Sim, mas não pode usar no projeto (C++98 only).

### Exercise 02

**Q: Por que não usar std::vector?**
A: STL containers são proibidos nos módulos 00-07. O objetivo é aprender a implementar.

**Q: Como garantir que não há memory leaks?**
A:
```bash
leaks -atExit -- ./program
# ou
valgrind --leak-check=full ./program
```

**Q: O que acontece se `new` falhar?**
A: Lança `std::bad_alloc`. Não tratamos aqui (comportamento padrão ok).

**Q: Por que `unsigned int` para size?**
A: Tamanhos nunca são negativos. Unsigned evita valores inválidos.

**Q: Diferença entre `size()` e `capacity()`?**
A: Nosso Array não tem capacity. Size é o tamanho fixo alocado.

---

## 🧪 Como Demonstrar Durante a Defesa

### 1. Compilação
```bash
make
# Mostrar que compila sem warnings
```

### 2. Executar testes
```bash
./whatever  # ex00
./iter      # ex01
./array     # ex02
```

### 3. Mostrar ausência de leaks
```bash
leaks -atExit -- ./array
```

### 4. Explicar código
- Abra cada arquivo .hpp
- Explique linha por linha se pedido
- Destaque decisões de design

### 5. Modificações possíveis
Esteja preparado para:
- Adicionar nova função template
- Modificar comportamento existente
- Adicionar teste específico
- Explicar alternativas de implementação

---

## 💡 Dicas para a Defesa

### ✅ DO:
- Explique com clareza e confiança
- Use exemplos concretos
- Desenhe diagramas de memória se ajudar
- Admita se não souber algo e proponha investigar
- Mostre que entende profundamente, não apenas copiou

### ❌ DON'T:
- Não finja saber se não souber
- Não critique o avaliador ou subject
- Não seja arrogante
- Não complique o que é simples
- Não ignore flags de compilação

---

## 📖 Conceitos C++98 Importantes

### 1. RAII (Resource Acquisition Is Initialization)
- Recursos adquiridos no construtor
- Liberados no destrutor
- Garante segurança automática

### 2. Const Correctness
- Métodos const não modificam objeto
- Referências const não permitem modificação
- Importante para segurança de tipos

### 3. Exception Safety
- Basic guarantee: sem leaks se exceção ocorrer
- Strong guarantee: estado consistente
- Nothrow guarantee: nunca lança exceção

### 4. Template Instantiation
- Implícita: compilador deduz tipos
- Explícita: `function<int>(...)`
- Cada tipo usado gera código separado

---

## 🎓 Recursos para Estudar

### Conceitos:
- Templates em C++
- Generic Programming
- Orthodox Canonical Form
- RAII
- Deep vs Shallow Copy
- Const Correctness

### Comandos úteis:
```bash
# Compilar manualmente
c++ -Wall -Wextra -Werror -std=c++98 file.cpp -o program

# Verificar leaks (macOS)
leaks -atExit -- ./program

# Verificar leaks (Linux)
valgrind --leak-check=full ./program

# Limpar e recompilar
make fclean && make
```

---

## ✨ Resumo Final

**Templates são:**
- Código genérico reutilizável
- Type-safe em tempo de compilação
- Eficientes (sem overhead de runtime)
- Devem estar em headers

**Seus três exercícios:**
1. **ex00**: Funções template básicas (swap, min, max)
2. **ex01**: Função template que itera arrays
3. **ex02**: Classe template de array com gerenciamento automático

**Pontos críticos:**
- ✅ Compilação com flags corretas
- ✅ C++98 standard (sem C++11+)
- ✅ Sem memory leaks
- ✅ Deep copy funcional
- ✅ Exception handling correto
- ✅ Const correctness

**Boa sorte na defesa! 🚀**

---

*Última atualização: 18 Outubro 2025*
