# Bedrock
Bedrock is an agent oriented modular, extendable and integration friendly algorithm framework built with clean architecture and SOLID principles at the forefront. 

# Overview

The key idea behind Bedrock is that algorithms are represented as agents which can visit and act upon various types of structures, where a structure can be thought of as an abstract representation of typical data structures such as graphs, linked lists etc.  

The choice of an agent oriented architecture comes with a number of benefits:

* Structures can be composed together in a modular fashion thus increasing expressibility and reusability
* Agent oriented design allows for more uniform and generalized parallelization of structure access and mutation. 
* Agents can spawn other agents as required to accomplish a given goal. This enables an interesting mechanism for algorithm composition.
* A given agent of some type may be designed with only limited knowledge of a given structure type thus reducing agent complexity. (If an agent requires additional knowledge of the structure it is working on then it can spawn another agent equipped with the desired knowledge/capability)

# Architecture