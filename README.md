# Optimization_of_waiting_time_using_genetic_algorithm

The main steps of applying
GA to any problem have been presented as follows.
- **Step 1**: Code the problem as a binary chromosome
- **Step 2**: Choose the size of a chromosome population N
- **Step 3**.Select genetic operators as crossover probability pc and the mutation probability pm.
- **Step 4**: Define a fitness function.
- **Step 5**: Randomly generate an initial population of N
- **Step 6**: Calculate the fitness of each individual chromosome:
- **Step 7**: Select a pair of chromosomes to generate next generation.
- **Step 8**: Create a pair of offspring chromosomes
- **Step 9**: Place the created offspring chromosomes in the new population.
- **Step 10**: Replace the initial (parent) chromosome population with the new (offspring) population.
- **Step 11**: Go to Step 6, and repeat the process

**Few parameters used in Algorithem**
- HC_DFi : destination floor of HCi
-  maxHC_DF↑ : maximum destination floor of upHCs greater than CFn
- maxHC↓ : maximum down HC
- minHC_DF↓ : minimum destination floor of down HCs less than CFn
- m inH C↑ : minimum up HC
- CAR_DF: matrix of car destination floors (if car is stopped, it is equal to CF)
- Y: maximum of the destination floors of up HCs less than CFn
- Z: minimum of the destination floors of down HCs greater than CFn

- MAX = max( HC_DF , CAR_DF, HC )↑ ↓
- MIN = minMIN=min( HC_DF , HC )

### Algorithm used if Lift will initially go up

-![up_algo](https://user-images.githubusercontent.com/93584728/170873952-8a48fb8e-fcf6-4afc-9a7d-5e60f117cc3f.png)

### Algorithm used if Lift will initially go down

-![down_algo](https://user-images.githubusercontent.com/93584728/170874009-a6705dc2-c989-4b8d-bce9-a79dfc6be688.png)

### Time parameters
![test_data1](https://user-images.githubusercontent.com/93584728/170874755-05e64cc9-89ef-4616-8f5b-f562e7904262.png)


### Test Data
![test_da](https://user-images.githubusercontent.com/93584728/170874817-e2a7c56b-1737-4951-bef5-47fd412806ab.png)


## Result According to Genatic Algorithem for above given data
-![output_ga](https://user-images.githubusercontent.com/93584728/170874126-c52ba6f5-cf59-4b00-8515-f2a9a2ee378b.png)

## Result According to Above code for above given data
-![output](https://user-images.githubusercontent.com/93584728/170874165-2bf7e774-4e89-4240-b862-f4415c452333.png)


