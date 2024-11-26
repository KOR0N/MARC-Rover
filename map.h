//
// Created by flasque on 19/10/2024.
//

#ifndef UNTITLED1_MAP_H
#define UNTITLED1_MAP_H

#define COST_UNDEF 65535
/**
 * @brief Enum for the possible soils of the map
 */
typedef enum e_soil
{
    BASE_STATION,
    PLAIN,
    ERG,
    REG,
    CREVASSE
} t_soil;

/**
 * @brief Array of costs for the soils
 */
static const int _soil_cost[5] = {0, 1, 2, 4, 10000};

/**
 * @brief Structure for the map

 */
typedef struct s_map
{
    t_soil  **soils;
    int     **costs;
    int     x_max;
    int     y_max;
} t_map;

/**
 * @brief Function to generate a map
 * @param x, y : the size of the map
 * @return the map
 */
char* GenerateMap(int x, int y);




/**
 * @brief Function to initialise the map from a file
 * @param filename : the name of the file
 * @return the map
 */
t_map createMapFromFile(char *);

/**
 * @brief Function to initialise the map from a char
 * @param mapChar : the name of the map
 * @return the map
 */
t_map createMapFromChar(char *, int x, int y);

/**
 * @brief Function that generates terrain based on probability
 * @param void
 * @return int corresponding to a type of terrain
 */
int GetSoil();

/**
 * @brief Function to create a standard training map (11x11 with only plains and base station in the middle)
 * @param none
 * @return a standard map
 */
 t_map createTrainingMap();

/**
 * @brief display the map with characters
 * @param map : the map to display
 */
void displayMap(t_map);


#endif //UNTITLED1_MAP_H
