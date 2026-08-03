# 📈 Modern C++ Binomial Option Pricer (CRR Model)

[![C++ Standard](https://img.shields.io/badge/C%2B%2B-17%2F20-blue.svg)](https://en.cppreference.com/w/cpp/compiler_support)
[![Build Standard](https://img.shields.io/badge/Build-CMake%203.15%2B-brightgreen.svg)](https://cmake.org/)
[![Model](https://img.shields.io/badge/Model-Cox--Ross--Rubinstein-orange.svg)]()

A modern, high-performance C++ library for pricing financial options (**European and American**) based on the **Cox-Ross-Rubinstein (CRR)** binomial tree model, as detailed in *Chapter 13* of the textbook *Options, Futures, and Other Derivatives* by John C. Hull.

---

## 🚀 Key Features

* **Decoupled Object-Oriented Architecture:** Strict separation of concerns between market data (`MarketData`), cash flow logic (`Payoff`), contract specifications (`Option`), and the numerical solver (`BinomialTreeEngine`).
* **$\mathcal{O}(N)$ Memory Optimization:** Backward induction is performed in-place on a single contiguous vector (`std::vector<double>`), avoiding the $\mathcal{O}(N^2)$ memory footprint of a 2D matrix and maximizing CPU cache-hit rates (cache-friendly design).
* **Native Greeks Calculation:** Free $\mathcal{O}(1)$ evaluation of **Delta ($\Delta$)**, **Gamma ($\Gamma$)**, and **Theta ($\Theta$)** by capturing tree nodes at time steps $t_0$, $t_1$, and $t_2$.
* **American Option Support:** Evaluates the optimal early exercise condition at every node of the tree:
  $$V_{i,j} = \max\left(\text{Payoff}(S_{i,j}), \; e^{-r\Delta t}\left[p V_{i+1,j+1} + (1-p) V_{i+1,j}\right]\right)$$
* **Continuous Dividend Yield Support:** Incorporates a continuous dividend yield $q$ (or cost of carry) into the risk-neutral probability formulation.

---

## 📁 Project Structure

```text
binomial-pricer/
├── CMakeLists.txt          # C++17/20 build configuration
├── README.md               # Project documentation
├── include/
│   ├── MarketData.hpp          # Market parameters struct (S0, r, q, sigma)
│   ├── Payoff.hpp              # Abstract interface & concrete payoffs (Call/Put)
│   ├── Option.hpp              # Option contract class (Maturity, Style, Payoff)
│   └── BinomialTreeEngine.hpp  # CRR pricing engine & Greeks solver
├── src/
│   ├── Payoff.cpp
│   ├── Option.cpp
│   └── BinomialTreeEngine.cpp
├── tests/
│   └── test_binomial.cpp       # Unit tests (Put-Call parity, Hull Ch.13 benchmarks)
└── examples/
    └── main.cpp                # Usage demonstration
```

---

## 🧮 Mathematical Background (Cox-Ross-Rubinstein)

The calibration parameters for a time step $\Delta t = \frac{T}{N}$ are defined as:

* Upward factor ($u$): $u = e^{\sigma\sqrt{\Delta t}}$
* Downward factor ($d$): $d = \frac{1}{u} = e^{-\sigma\sqrt{\Delta t}}$
* Risk-neutral probability ($p$):

$$p = \frac{e^{(r-q)\Delta t} - d}{u - d}$$

**Greeks Extraction from the Tree:**

* $\Delta$ (Delta): $\frac{V_{1,1} - V_{1,0}}{S_{1,1} - S_{1,0}}$
* $\Gamma$ (Gamma): $\frac{\frac{V_{2,2} - V_{2,1}}{S_{2,2} - S_{2,1}} - \frac{V_{2,1} - V_{2,0}}{S_{2,1} - S_{2,0}}}{0.5 \times (S_{2,2} - S_{2,0})}$
* $\Theta$ (Theta): $\frac{V_{2,1} - V_{0,0}}{2\Delta t}$ (annualized)

---

## 🛠️ Building the Project

The project uses CMake (version 3.15+) and requires a compiler supporting C++17 or higher (GCC, Clang, or MSVC).

```bash
# 1. Clone the repository and create the build directory
git clone https://github.com/your-username/binomial-pricer.git
cd binomial-pricer
mkdir build && cd build

# 2. Generate build files in Release mode (-O3 optimizations enabled)
cmake .. -DCMAKE_BUILD_TYPE=Release

# 3. Build the project
cmake --build .
```