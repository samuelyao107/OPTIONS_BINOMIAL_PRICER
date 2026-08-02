# 📈 Modern C++ Binomial Option Pricer (CRR Model)

[![C++ Standard](https://img.shields.io/badge/C%2B%2B-17%2F20-blue.svg)](https://en.cppreference.com/w/cpp/compiler_support)
[![Build Standard](https://img.shields.io/badge/Build-CMake%203.15%2B-brightgreen.svg)](https://cmake.org/)
[![Model](https://img.shields.io/badge/Model-Cox--Ross--Rubinstein-orange.svg)]()

Une bibliothèque C++ moderne et performante pour la valorisation d'options financières (**Européennes et Américaines**) basée sur le modèle d'arbre binomial de **Cox-Ross-Rubinstein (CRR)**, tel que décrit dans le *Chapitre 13* de l'ouvrage de référence *Options, Futures, and Other Derivatives* (John C. Hull).

---

## 🚀 Caractéristiques Principales

* **Architecture Orientée Objet Découplée :** Séparation stricte entre les données de marché (`MarketData`), la logique des flux de trésorerie (`Payoff`), le contrat (`Option`) et le moteur de calcul (`BinomialTreeEngine`).
* **Optimisation Mémoire en $\mathcal{O}(N)$ :** Remontée de l'arbre (*Backward Induction*) effectuée sur un seul vecteur contigu (`std::vector<double>`), évitant l'empreinte mémoire d'une matrice 2D en $\mathcal{O}(N^2)$ et maximisant le taux de succès du cache CPU (*Cache-friendly*).
* **Calcul Natif des Grecs :** Évaluation gratuite en $\mathcal{O}(1)$ du **Delta ($\Delta$)**, **Gamma ($\Gamma$)** et **Theta ($\Theta$)** par capture des nœuds aux pas de temps $t_0$, $t_1$ et $t_2$.
* **Options Américaines :** Prise en compte de la condition d'exercice anticipé optimale à chaque nœud de l'arbre :
  $$V_{i,j} = \max\left(\text{Payoff}(S_{i,j}), \; e^{-r\Delta t}\left[p V_{i+1,j+1} + (1-p) V_{i+1,j}\right]\right)$$
* **Support des Dividendes Continus :** Intégration du taux de dividende continu $q$ (ou coût d'emport) dans la probabilité risque-neutre.

---

## 📁 Structure du Projet

```text
binomial-pricer/
├── CMakeLists.txt          # Configuration de build C++17/20
├── README.md               # Documentation
├── include/
│   ├── MarketData.hpp          # Structure des paramètres de marché (S0, r, q, sigma)
│   ├── Payoff.hpp              # Interface abstraite & dérivées (Call/Put)
│   ├── Option.hpp              # Définition du contrat (Maturité, Style, Payoff)
│   └── BinomialTreeEngine.hpp  # Moteur de valorisation CRR & Grecs
├── src/
│   ├── Payoff.cpp
│   ├── Option.cpp
│   └── BinomialTreeEngine.cpp
├── tests/
│   └── test_binomial.cpp       # Tests unitaires (Parité Call-Put, exemples Hull Ch.13)
└── examples/
    └── main.cpp                # Exemple d'utilisation