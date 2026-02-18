# Cave Generation Cellular Automata

![green and blue world grid generated with cellular automata](https://shthub.org/u/benjamin/cave_cellular_automata2.png?raw)

## Explanation

This is a barebones implementation of the cellular automata cave generation algorithm detailed [here](https://www.roguebasin.com/index.php/Cellular_Automata_Method_for_Generating_Random_Cave-Like_Levels).

The algorithm starts with a random grid of cells, where each cell is either a ``1`` or a ``0``. The grid is then iteratively smoothed by checking the 3x3 neighborhood of each cell using modular arithmetic to wrap around the edges of the grid. This makes the resulting texture seamless when tiled.

## Building

```bash
cc -o cave main.c && ./cave;
```

## Future Improvements

The roguebasin article mentions that the algorithm can be improved by checking the 5x5 neighborhood of each cell instead to make less detatched "caves". In my case I have embraced the spotty nature of the resulting texture by printing the output in green and blue to make each tile look like either a patch of grass or pool of water. Perhaps it is possible to have more than two types of terrain or apply more complex rules for smoothing. It would be nice to see an implementation that looks better at higher resolutions.
