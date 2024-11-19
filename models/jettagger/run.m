
dtype = 'int8';

sizes = [16,128,64,64,16];

for i = 1:(length(sizes)-1)
    fileID = fopen(strcat('layer_', num2str(i),'.cpp'), 'w');
    fprintf(fileID, '#include <adf.h>\n#include <aie_api/aie.hpp>\n#include <aie_api/aie_adf.hpp>\n#include "inc.h"\nalignas (32) const %s matrix [%d][%d] = {5};\n#include "GemV.cpp"', dtype, sizes(i), sizes(i+1));
    fclose(fileID);
    disp(i);
end


fileID = fopen('inc.h', 'w');
fprintf(fileID, '#define DTYPE %s\n#define CONCAT(a,b) a##b\n#define IN_STREAM(T) CONCAT(input_stream_,T)\n#define OUT_STREAM(T) CONCAT(output_stream_,T)\n\n', dtype);
fclose(fileID);

numTimeSteps = 100;
timeStep = 1;
time = (0:numTimeSteps-1) * timeStep;

x = randi([-2,2],numTimeSteps, sizes(1));
x_ts = timeseries(x, time);

sim("mm", numTimeSteps-1);