#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <stdexcept>

#include "../jim/queue.h"

namespace ctci {
    namespace ch3 {
        enum class AnimalType { Dog, Cat };

        class Animal {
            protected:
                std::string name;
                AnimalType type;
            
            public:
                Animal(std::string name) { this->name = name; }

                AnimalType getType() { return type; }
        };

        class Dog : public Animal {
            public:
                Dog(std::string name)
                : Animal(name) {
                    this->type = AnimalType::Dog;
                }
        };

        class Cat : public Animal {
            public:
                Cat(std::string name)
                : Animal(name) {
                    this->type = AnimalType::Cat;
                }
        };

        class AnimalShelter {
            protected:
                ctci::jim::Queue<Animal*> animals;

                // Skipped animals are animals that got skipped over due to
                // their type. They get first priority in dequeueAny().
                ctci::jim::Queue<Animal*> skippedAnimals;

            public:
                void enqueue(Animal* a) {
                    animals.add(a);
                }

                Animal* dequeueAny() {
                    if (!skippedAnimals.isEmpty()) {
                        return skippedAnimals.remove();
                    }

                    if (!animals.isEmpty()) {
                        return animals.remove();
                    }

                    throw std::runtime_error("No dogs available!");
                }

                Dog* dequeueDog() {
                    if (!skippedAnimals.isEmpty() &&
                        skippedAnimals.peek()->getType() == AnimalType::Dog) {
                            return static_cast<Dog*>(skippedAnimals.remove());
                    }

                    while (!animals.isEmpty()) {
                        if (animals.peek()->getType() != AnimalType::Dog) {
                            skippedAnimals.add(animals.remove());
                        } else {
                            return static_cast<Dog*>(animals.remove());
                        }
                    }

                    throw std::runtime_error("No dogs available!");
                }

                Cat* dequeueCat() {
                    if (!skippedAnimals.isEmpty() &&
                        skippedAnimals.peek()->getType() == AnimalType::Cat) {
                            return static_cast<Cat*>(skippedAnimals.remove());
                    }

                    while (!animals.isEmpty()) {
                        if (animals.peek()->getType() != AnimalType::Cat) {
                            skippedAnimals.add(animals.remove());
                        } else {
                            return static_cast<Cat*>(animals.remove());
                        }
                    }

                    throw std::runtime_error("No cats available!");
                }
        };

        int main(int argc, char** argv) {
            // dequeueAny returns oldest animal.
            {
                AnimalShelter shelter;
                shelter.enqueue(new Dog("Rex"));
                shelter.enqueue(new Cat("Whiskers"));
                Animal* a = shelter.dequeueAny();
                if (a->getType() != AnimalType::Dog) throw std::runtime_error("Test failed.");
            }

            // dequeueDog skips cats to find oldest dog.
            {
                AnimalShelter shelter;
                shelter.enqueue(new Cat("Whiskers"));
                shelter.enqueue(new Dog("Rex"));
                shelter.enqueue(new Dog("Ox"));
                Dog* d = shelter.dequeueDog();
                if (d->getType() != AnimalType::Dog) throw std::runtime_error("Test failed.");
            }

            // dequeueCat skips dogs to find oldest cat.
            {
                AnimalShelter shelter;
                shelter.enqueue(new Dog("Rex"));
                shelter.enqueue(new Cat("Whiskers"));
                shelter.enqueue(new Cat("Luna"));
                Cat* c = shelter.dequeueCat();
                if (c->getType() != AnimalType::Cat) throw std::runtime_error("Test failed.");
            }

            // Skipped animals are returned by dequeueAny before animals queue.
            {
                AnimalShelter shelter;
                shelter.enqueue(new Cat("Whiskers"));
                shelter.enqueue(new Dog("Rex"));
                shelter.dequeueDog(); // skips Whiskers into skippedAnimals
                Animal* a = shelter.dequeueAny(); // should return Whiskers
                if (a->getType() != AnimalType::Cat) throw std::runtime_error("Test failed.");
            }

            // Throws when no dog available.
            {
                AnimalShelter shelter;
                shelter.enqueue(new Cat("Whiskers"));
                bool threw = false;
                try { shelter.dequeueDog(); } catch (std::runtime_error&) { threw = true; }
                if (!threw) throw std::runtime_error("Test failed.");
            }

            // Throws when no cat available.
            {
                AnimalShelter shelter;
                shelter.enqueue(new Dog("Rex"));
                bool threw = false;
                try { shelter.dequeueCat(); } catch (std::runtime_error&) { threw = true; }
                if (!threw) throw std::runtime_error("Test failed.");
            }

            // skippedAnimals stays homogeneous: dequeueCat clears cats before
            // going to animals, so [Cat, Dog] ordering is never reachable.
            // Verify multiple dequeueDog calls correctly drain cats via skippedAnimals.
            {
                AnimalShelter shelter;
                shelter.enqueue(new Cat("Whiskers"));
                shelter.enqueue(new Dog("Rex"));
                shelter.enqueue(new Cat("Luna"));
                shelter.enqueue(new Dog("Ox"));
                // dequeueDog: skip Whiskers->skipped, return Rex. skipped=[Whiskers], animals=[Luna,Ox]
                // dequeueDog: skipped front=Whiskers(cat), go to animals. Skip Luna->skipped=[Whiskers,Luna]. Return Ox.
                shelter.dequeueDog();
                shelter.dequeueDog();
                // skipped=[Whiskers,Luna]. dequeueCat should return Whiskers (oldest cat).
                Cat* c = shelter.dequeueCat();
                if (c->getType() != AnimalType::Cat) throw std::runtime_error("Test failed.");
            }

            std::cout << "All tests passed.\n";
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch3::main(argc, argv);
}