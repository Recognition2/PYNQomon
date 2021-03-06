clear variables;
close all;

pokefilename = '/home/gregory/Downloads/pokemon.png';
poke_c_file = '../pokemon.h';
pokeID = fopen(poke_c_file, 'w+');

fprintf(pokeID,...
'/// Generated by MATLAB\n\n#ifndef POKE_MATLAB_C_H\n#define POKE_MATLAB_C_H \n#include "app_config.hpp"\n\n');

pokesize = [56,48];
fprintf(pokeID, 'const p16 pokesize = {%d, %d};\n', pokesize(1), pokesize(2));
fprintf(pokeID, 'const u32 pokemon[%d][%d] = {\n', pokesize(1), pokesize(2));
pokefile = imread(pokefilename);

for i = 1:pokesize(1)
    for j = 1:pokesize(2)
        pokepx = pokefile(j,i,:);
        r = pokepx(1);
        g = pokepx(2);
        b = pokepx(3);
 %       if (r == 1)
 %           r = 0;
 %       end
 %       if (g == 1)
 %           g = 0;
 %       end
 %       if (b == 1)
 %           b = 0;
 %       end
        
        fprintf(pokeID, '0xFF%02X%02X%02X, ', b, g, r);
    end
    fprintf(pokeID, '\n'); 
end


fprintf(pokeID, '};\n\n\n#endif\n');
res = fclose(pokeID)



