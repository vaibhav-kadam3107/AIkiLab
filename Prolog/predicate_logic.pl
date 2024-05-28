% Facts: Define parent-child relationships.
parent(ram, priya).
parent(ram, anil).
parent(priya, amita).
parent(anil, anjali).
parent(shyam, ram).
parent(shyam, priya).


% Rules: Define sibling and grandparent relationships.
sibling(X, Y) :-
    parent(Z, X),
    parent(Z, Y),
    X \= Y.


grandparent(X, Y) :-
    parent(X, Z),
    parent(Z, Y).



/*Facts:
Facts in Prolog represent statements about relationships or properties that are assumed to be true. In this code, the facts establish parent-child relationships:
parent(ram, priya).: Indicates that Ram is the parent of Priya.
parent(ram, anil).: Indicates that Ram is the parent of Anil.
parent(priya, amita).: Indicates that Priya is the parent of Amita.
parent(anil, anjali).: Indicates that Anil is the parent of Anjali.
parent(shyam, ram).: Indicates that Shyam is the parent of Ram.
parent(shyam, priya).: Indicates that Shyam is the parent of Priya.
Rules:
Rules define relationships or properties based on other relationships or properties. They consist of a head and a body separated by :-. If the body of the rule succeeds, the head is considered true.
sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.:
This rule defines siblings. It states that X and Y are siblings if there exists a Z such that Z is the parent of both X and Y, and X is not the same as Y.
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).:
This rule defines grandparents. It states that X is the grandparent of Y if there exists a Z such that X is the parent of Z and Z is the parent of Y.
Example Usage:
Query: sibling(ram, priya).

Explanation: This query checks if Ram and Priya are siblings. Since Ram and Priya have different parents, the query returns false.
Query: grandparent(ram, amita).

Explanation: This query checks if Ram is the grandparent of Amita. Since Priya (Ram's child) is the parent of Amita, the query returns true.
Query: sibling(anil, anjali).

Explanation: This query checks if Anil and Anjali are siblings. Since they have the same parent (Ram), the query returns true.
Working:
The code establishes parent-child relationships using facts.
It defines rules to determine sibling and grandparent relationships based on the parent-child relationships.
Users can query the relationships to find out if certain individuals are siblings or grandparents according to the defined rules.*/