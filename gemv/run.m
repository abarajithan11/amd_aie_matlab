DX = 32;  % Num inputs, = latency
DY = 32;  % Num outputs, calc'd in parallel
dtype = 'int8';

numTimeSteps = 100;  % Number of time steps in the timeseries
timeStep = 1;  % Time interval between each step
time = (0:numTimeSteps-1) * timeStep;  % Create the time vector

mat_t = randi([-2,2],DX,DY);
x = randi([-2,2],numTimeSteps, DX);

%% Write matrix as C header

fileID = fopen('matrix.h', 'w');
fprintf(fileID, '#ifndef MATRIX_H\n#define MATRIX_H\n\n');
fprintf(fileID, '#define DTYPE %s\n#define CONCAT(a,b) a##b\n#define IN_STREAM(T) CONCAT(input_stream_,T)\n#define OUT_STREAM(T) CONCAT(output_stream_,T)\n\n', dtype);
fprintf(fileID, 'alignas (32) const %s matrix[%d][%d] = {\n', dtype, DX, DY);

for i = 1:DX % Write each row of the matrix
    fprintf(fileID, '    {');
    fprintf(fileID, '%.6g, ', mat_t(i, 1:end-1)); % Write all but last element
    fprintf(fileID, '%.6g}', mat_t(i, end)); % Write last element
    if i < DX
        fprintf(fileID, ',\n'); % Add comma for all rows except the last one
    else
        fprintf(fileID, '\n'); % No comma for the last row
    end
end
fprintf(fileID, '};\n\n#endif // MATRIX_H\n');
fclose(fileID);

%% Compute expected

x_ts = timeseries(x, time);
y_exp = zeros(numTimeSteps, DY);

for i = 1:numTimeSteps
    vectorAtTimeStep = x_ts.Data(i, :).';
    y_exp(i, :) = (mat_t' * vectorAtTimeStep).';
end

%% Run sim

sim("mm", numTimeSteps-1);

y_sim = cell2mat(ans.y_tso.Data);
y_sim = reshape(y_sim, [DY,numTimeSteps])';

error = nnz(y_exp - y_sim);

disp("Error:");
disp(error)
