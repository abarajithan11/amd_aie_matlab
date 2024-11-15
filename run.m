% Define dimensions
M = 8;  % Number of rows for the matrix
K = 8;  % Number of columns for the matrix (also the size of each vector in the timeseries)
numTimeSteps = 100;  % Number of time steps in the timeseries
timeStep = 1;  % Time interval between each step
time = (0:numTimeSteps-1) * timeStep;  % Create the time vector


A = randi([-10,10], M, K);

x = randi([-10,10],numTimeSteps, K);

% Loop through each time step, multiply the matrix with the vector, and store the result

x_ts = timeseries(x, time);
y = zeros(numTimeSteps, M);

for i = 1:numTimeSteps
    % Get the vector at the current time step
    vectorAtTimeStep = x_ts.Data(i, :).';

    % Multiply the matrix A by the vector
    y(i, :) = (A * vectorAtTimeStep).';
end

% Create the output timeseries object
y_ts = timeseries(y, time);

% Display the results
disp('Matrix A:');
disp(A);
disp('Input:');
disp(x_ts.Data);
disp('Output:');
disp(y_ts.Data);



% % Parameters
% K = 3;                  % Size of each vector at each time step
% numTimeSteps = 100;     % Number of time steps
% timeStep = 0.1;         % Time interval between each step
% 
% % Define the time vector
% time = (0:numTimeSteps-1) * timeStep;
% 
% % Generate random data (each row is a K-element vector for each time step)
% data = randn(numTimeSteps, K);
% 
% % Create the timeseries object
% ts = timeseries(data, time);
% 
% % Display the timeseries to verify
% disp('Generated timeseries object:');
% disp(ts);
