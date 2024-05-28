female(babita).
female(kareena).
female(karishma).
female(sara).
male(saif).
male(taimur).
male(aarav).
male(randhir).
male(raj).


parent(babita,kareena).
parent(randhir,kareena).
parent(randhir,karishma).
parent(saif,taimur).
parent(kareena,taimur).
parent(kareena,sara).
parent(karishma,raj).
parent(sara,aarav).


husband(X,Y):- parent(X,Z),parent(Y,Z),male(X).
wife(X,Y):- parent(X,Z),parent(Y,Z),female(X).
mother(X,Y):- parent(X,Y),female(X).
father(X,Y):- parent(X,Y),male(X).
son(X,Y):- male(X),parent(Y,X).
daughter(X,Y):- female(X),parent(Y,X).
haschild(X):- parent(X,_).
sister(X,Y):- parent(Z,X),parent(Z,Y),female(X),X\==Y.
brother(X,Y):-parent(Z,X),parent(Z,Y),male(X),X\==Y.


paternal_uncle(X,Y):- father(Z,Y),brother(X,Z).
maternal_uncle(X,Y):- mother(Z,Y),brother(X,Z).
paternal_aunt(X,Y):- father(Z,Y),sister(X,Z).
maternal_aunt(X,Y):- mother(Z,Y),sister(X,Z).
niece(X,Y):- female(X),parent(Z,X),parent(W,Z),parent(W,Y),Z\==Y.
nephew(X,Y):- male(X),parent(Z,X),parent(W,Z),parent(W,Y),Z\==Y.
grandfather(X,Y):- parent(X,Z),parent(Z,Y),male(X).
grandmother(X,Y):- parent(X,Z),parent(Z,Y),female(X).
cousin_brother(X,Y):-
male(X),parent(Z,Y),parent(W,X),parent(T,W),parent(T,Z),Z\==W,X\==Y.
cousin_sister(X,Y):-
female(X),parent(Z,Y),parent(W,X),parent(T,W),parent(T,Z),Z\==W,X\==Y.
soninlaw(X,Y):- husband(X,Z),parent(Y,Z).
fatherinlaw(X,Y):- husband(Y,Z),parent(X,Z).
daughterinlaw(X,Y):- wife(X,Z),parent(Y,Z).
brotherinlaw(X,Y):- husband(X,Z),parent(W,Y),parent(W,Z),Y\==Z.
sisterinlaw(X,Y):- wife(X,Z),parent(W,Y),parent(W,Z),Y\==Z.
predecessor(X,Y):- parent(X,Y).
predecessor(X,Y):- parent(X,Z),predecessor(Z,Y).


# This Prolog code defines predicates for familial relationships and their inference. Here's a detailed breakdown of each section:

# ### Facts:
# - **Gender**: Facts about individuals' genders are represented using the `female/1` and `male/1` predicates.
# - **Parental Relationships**: Parental relationships are represented using the `parent/2` predicate, where the first argument is the parent, and the second argument is the child.

# ### Rules:
# 1. **Spousal Relationships**:
#    - `husband/2` and `wife/2` predicates determine spousal relationships based on shared children.
#    - They check if two individuals share at least one child and one of them is male/female, respectively.

# 2. **Parental Relationships**:
#    - `mother/2` and `father/2` predicates determine maternal and paternal relationships between individuals.
#    - They directly check if an individual is the parent of another individual.

# 3. **Sibling Relationships**:
#    - `brother/2` and `sister/2` predicates determine sibling relationships based on having the same parent(s).
#    - They ensure that two individuals share at least one parent but are not the same individual.

# 4. **Uncle and Aunt Relationships**:
#    - `paternal_uncle/2` and `maternal_uncle/2` predicates determine paternal and maternal uncle relationships based on the father's or mother's brother.
#    - `paternal_aunt/2` and `maternal_aunt/2` predicates determine paternal and maternal aunt relationships based on the father's or mother's sister.

# 5. **Niece and Nephew Relationships**:
#    - `niece/2` and `nephew/2` predicates determine niece and nephew relationships based on the child's gender and parent(s).

# 6. **Grandparent Relationships**:
#    - `grandfather/2` and `grandmother/2` predicates determine grandparent relationships based on parental relationships.

# 7. **Cousin Relationships**:
#    - `cousin_brother/2` and `cousin_sister/2` predicates determine cousin relationships based on shared grandparents.

# 8. **In-law Relationships**:
#    - `soninlaw/2`, `fatherinlaw/2`, `daughterinlaw/2`, `brotherinlaw/2`, and `sisterinlaw/2` predicates determine various in-law relationships based on marital status and parental relationships.

# 9. **Predecessor Relationships**:
#    - `predecessor/2` predicate determines predecessor relationships based on parent-child relationships. It recursively finds ancestors of an individual.

# These rules and facts allow querying various familial relationships and inferring them based on the provided data.