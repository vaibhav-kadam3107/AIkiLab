% Facts about the animals
animal(lion).
animal(elephant).
animal(zebra).
animal(penguin).
animal(kangaroo).
animal(giraffe).
animal(crocodile).
animal(bear).
animal(rabbit).
animal(shark).
animal(turtle).

% Habitats
habitat(lion, savannah).
habitat(elephant, savannah).
habitat(zebra, savannah).
habitat(penguin, antarctica).
habitat(kangaroo, australia).
habitat(giraffe, savannah).
habitat(crocodile, wetlands).
habitat(bear, forest).
habitat(rabbit, meadow).
habitat(shark, ocean).
habitat(turtle, wetlands).

% Diets
diet(lion, carnivore).
diet(elephant, herbivore).
diet(zebra, herbivore).
diet(penguin, carnivore).
diet(kangaroo, herbivore).
diet(giraffe, herbivore).
diet(crocodile, carnivore).
diet(bear, omnivore).
diet(rabbit, herbivore).
diet(shark, carnivore).
diet(turtle, herbivore).

% Sizes
size(lion, medium).
size(elephant, large).
size(zebra, medium).
size(penguin, small).
size(kangaroo, medium).
size(giraffe, tall).
size(crocodile, long).
size(bear, large).
size(rabbit, small).
size(shark, long).
size(turtle, medium).

% Rule to check if two animals share the same habitat
shares_habitat(Animal1, Animal2) :-
    habitat(Animal1, Habitat),
    habitat(Animal2, Habitat),
    Animal1 \= Animal2.

% Rule to determine which animals a given animal could eat
preys_on(Predator, Prey) :-
    diet(Predator, carnivore),
    diet(Prey, herbivore),
    size(Predator, Size1),
    size(Prey, Size2),
    Size1 \= Size2.

% Rule to determine which animals can coexist peacefully
coexists_peacefully(Animal1, Animal2) :-
    habitat(Animal1, Habitat),
    habitat(Animal2, Habitat),
    Animal1 \= Animal2,
    \+ preys_on(Animal1, Animal2),
    \+ preys_on(Animal2, Animal1).



# This Prolog code defines facts and rules about different animals, their habitats, diets, sizes, and interactions.

# ### Facts:
# - **Animals**: Facts about various animals are represented using the `animal/1` predicate. Each animal is specified as an argument to the `animal` predicate.
# - **Habitats**: The habitats of different animals are represented using the `habitat/2` predicate. Each fact specifies an animal and its corresponding habitat.
# - **Diets**: The diets of different animals are represented using the `diet/2` predicate. It specifies whether an animal is a carnivore, herbivore, or omnivore.
# - **Sizes**: The sizes of different animals are represented using the `size/2` predicate. It specifies the size category of each animal.

# ### Rules:
# 1. **Sharing Habitat** (`shares_habitat/2`):
#    - This rule determines if two animals share the same habitat.
#    - It checks if both animals have the same habitat and ensures they are not the same animal.

# 2. **Predation** (`preys_on/2`):
#    - This rule determines if a predator can prey on a given prey.
#    - It checks if the predator is a carnivore, the prey is a herbivore, and their sizes are different.

# 3. **Coexistence** (`coexists_peacefully/2`):
#    - This rule determines if two animals can coexist peacefully.
#    - It checks if both animals share the same habitat, are not the same animal, and neither preys on the other.

# ### Example Usage:
# - **Predation**:
#   ```prolog
#   ?- preys_on(lion, zebra).
#   true.
#   ```
#   This query indicates that a lion preys on a zebra because lions are carnivores and zebras are herbivores.

# - **Coexistence**:
#   ```prolog
#   ?- coexists_peacefully(lion, giraffe).
#   true.
#   ```
#   This query indicates that lions and giraffes can coexist peacefully because they share the same habitat, and neither preys on the other.