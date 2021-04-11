# Bedrock
Bedrock is an agent oriented modular, extendable and integration friendly algorithms framework built with clean architecture and SOLID principles at the forefront. 

# Overview

In Bedrock algorithms are represented as agents which can visit and act upon various types of structures. A structure can be thought of as an abstract representation of typical data structures such as graphs, linked lists etc.

The choice of an agent oriented architecture comes with a number of key benefits:

* Under Bedrock, all algorithms become mathematically verifiable. In essence, if one can characterize the behaviour of a given agent, one knows that the agent will NEVER take any action that is outside it's allowed action set. This implies that one can always construct a verfiable decision tree of agent behaviour regardless of the underlying structure an agent could happen to be interacting with.
* Structures can be composed together in a modular fashion thus increasing expressibility and reusability
* Agent oriented design allows for more uniform and generalized parallelization of structure access and mutation. 
* Agents can spawn other agents as required to accomplish a given goal. This enables an interesting mechanism of algorithm composition.
* A given agent of some type may be designed with only limited knowledge of a given structure type thus reducing agent complexity. If an agent needs to complete a goal which requires additional knowledge, the agent may spawn another agent equipped with the desired knowledge/capability.
* Agents allow for a more abstract encapsulation and decoupling of algorithm behaviours. For example, bedrock includes a special type of agent called a hopper. The hopper simply knows how to move from one location to another on a given structure. Again this agent can be used in conjunction with other agents to accomplish a wider set of goals.

# Architecture