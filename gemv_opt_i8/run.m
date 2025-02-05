DX = 32;  % Num inputs, = latency
DY = 16;  % Num outputs, calc'd in parallel
Q  = 4;   % number of splits along DX
dtype = 'int8';

numTimeSteps = 100;
timeStep = 1; 
time = (0:numTimeSteps-1) * timeStep; 
mat_concat = sprintf('m[%d],', 0:Q-1);  % Creates a string like 'm[0],m[1],...,m[N-1],'
mat_concat(end) = [];  % Remove the last comma

mat_t = randi([-2,2],DX,DY);
% mat_t = eye(DX);
% mat_t = zeros(DX,DY);
% mat_t(1,1) = 1;
x = randi([-2,2],numTimeSteps, DX);
% x = zeros(numTimeSteps, DX);
% x(1,1) = 15;

%% Write odd & even matrices as C header

rowsPerMat = DX / Q;
fileID = fopen('matrix.h', 'w');
fprintf(fileID, '#ifndef MATRIX_H\n#define MATRIX_H\n\n');
fprintf(fileID, '#define DTYPE %s\n', dtype);
fprintf(fileID, '#define Q %d\n', Q);
fprintf(fileID, '#define MQS %s\n', mat_concat);
fprintf(fileID, '#define CONCAT(a,b) a##b\n');
fprintf(fileID, '#define IN_STREAM(T) CONCAT(input_stream_,T)\n');
fprintf(fileID, '#define OUT_STREAM(T) CONCAT(output_stream_,T)\n\n');

fprintf(fileID, 'alignas(32) const %s matrix[%d][%d][%d] = {\n', dtype, Q, rowsPerMat, DY);

for q = 1:Q
    subMat = mat_t(q:Q:end, :);
    fprintf(fileID, '    { // matrix block %d\n', q-1);
    for i = 1:rowsPerMat
        fprintf(fileID, '        {');
        for j = 1:DY % Loop over each element in the row
            if j < DY % Add comma if not last
                fprintf(fileID, '%.6g, ', subMat(i, j));
            else
                fprintf(fileID, '%.6g', subMat(i, j));
            end
        end
        fprintf(fileID, '}');
        if i < rowsPerMat % Add comma if not last
            fprintf(fileID, ',\n');
        else
            fprintf(fileID, '\n');
        end
    end
    if q < Q % Add comma if not last
        fprintf(fileID, '    },\n');
    else
        fprintf(fileID, '    }\n');
    end
end

% Close the array and header guard.
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
