DY = 128;  % Num outputs, calc'd in parallel
DX = 128;  % Num inputs, = latency
dtype = 'int8';

numTimeSteps = 100;  % Number of time steps in the timeseries
timeStep = 1;  % Time interval between each step
time = (0:numTimeSteps-1) * timeStep;  % Create the time vector

mat_t = randi([-2,2],DX,DY);
x = randi([-2,2],numTimeSteps, DY);

%% Write matrix as C header

fileID = fopen('matrix.h', 'w');
fprintf(fileID, '#ifndef MATRIX_H\n#define MATRIX_H\n\n #define DTYPE %s\n', dtype);
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


sim("mm", numTimeSteps-1);

y_sim = cell2mat(ans.y_tso.Data);
y_sim = reshape(y_sim, [DY,numTimeSteps])';

error = nnz(y_exp - y_sim);

disp("Error:");
disp(error)
